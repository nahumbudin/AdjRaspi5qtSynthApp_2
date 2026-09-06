/**
*	@file		alsaMidiSequencerClient.cpp
*	@author		Nahum Budin
*	@date		12-May-2024
*	@version	1.3 - FIXED VERSION
*					1. Code refactoring and notation.
*					2. CRITICAL FIX: Proper thread shutdown to prevent use-after-free
*					3. CRITICAL FIX: Constructor initialization order
*					4. CRITICAL FIX: pthread_join in destructor
*
*	@brief		ALSA MIDI input client. Pushes ALSA midi input data into alsa_seq_client_rx_queue
*				https://ccrma.stanford.edu/~craig/articles/linuxmidi/alsa-1.0/
*
*	History:\n
*
*			version 1.3		2025 (FIXED)
*					1. Fixed use-after-free crash at 0x5555
*					2. Added pthread_join() to wait for thread exit
*					3. Fixed constructor initialization order
*					4. Added shutdown check before enqueue
*
*			version	1.2		12-May-2024
*					1. Code refactoring and notation.
*
*			version	1.1		6-Feb-2021
*					1. Code refactoring and notation.
*					2. Adding Rx Q as a parameter
*
*			version 1.0		13-Dec--2019 (revised version from old libAdjHeartRaspiFlSynthMultiCore_3_1 Dec 2017)
*/

#include <pthread.h>

#include "alsaMidiSequencerClient.h"
#include "../Misc/priorities.h"

AlsaMidiSequencerInputClient::AlsaMidiSequencerInputClient(std::string name, SafeQueue<snd_seq_event_t*> *rxq)
{
	client_name = name;

	// FIX #1: Set the queue BEFORE starting the thread
	// Original bug: Thread could start and try to use queue before it was set!
	alsa_seq_client_rx_queue = rxq;

	// Now start the thread (it will use the queue we just set)
	start_midi_in_seq_client_thread();
}

AlsaMidiSequencerInputClient::~AlsaMidiSequencerInputClient()
{
	// FIX #2: CRITICAL - Proper shutdown sequence to prevent use-after-free

	// STEP 1: Signal thread to stop
	midi_in_client_thread_is_running = false;

	// STEP 2: Wake the thread if it's waiting in the queue
	// (This requires the fixed SafeQueue with shutdown() method)
	if (alsa_seq_client_rx_queue) {
		alsa_seq_client_rx_queue->shutdown();
	}

	// STEP 3: CRITICAL - Wait for the thread to completely finish
	// Original bug: Missing pthread_join() allowed thread to keep running
	// after destructor returned, causing use-after-free when queue was destroyed
	if (midi_client_in_thread) {
		pthread_join(midi_client_in_thread, nullptr);
		midi_client_in_thread = 0;
	}

	// STEP 4: NOW it's safe to close the sequencer
	// Thread has exited, no one is using the resources anymore
	close_seq();

	// Note: We don't delete alsa_seq_client_rx_queue here because it's
	// owned by the caller who passed it in the constructor
}

void AlsaMidiSequencerInputClient::start_midi_in_seq_client_thread()
{
	int ret, err, policy;
	pthread_attr_t tattr;
	struct sched_param params;

	// initialized with default attributes
	ret = pthread_attr_init(&tattr);
	// safe to get existing scheduling param
	ret = pthread_attr_getschedparam(&tattr, &params);
	// set the priority; others are unchanged
	params.sched_priority = sched_get_priority_max(SCHED_RR) - _THREAD_PRIORITY_MIDI_IN;
	ret = pthread_attr_setinheritsched(&tattr, PTHREAD_EXPLICIT_SCHED);
	policy = SCHED_RR;
	ret = pthread_attr_setschedpolicy(&tattr, policy);
	// setting the new scheduling param
	ret = pthread_attr_setschedparam(&tattr, &params);
	err = errno;
	//	ret = pthread_setschedparam(updatThreadId, SCHED_RR, &params);
	if (ret != 0)
	{
		// Print the error
		fprintf(stderr, "ALSA MIDI sequencer: Unsuccessful in setting Midi In Seq Client %s thread realtime prio\n", client_name.c_str());
	}

	midi_in_client_thread_is_running = true;
	ret = pthread_create(&midi_client_in_thread, &tattr, &AlsaMidiSequencerInputClient::thread_wraper, this); // open in thread
	if (ret == -1) {
		fprintf(stderr, "ALSA MIDI sequencer: Unable to create MIDI input Seq Client %s thread.", client_name.c_str());
		exit(1);
	}
	pthread_setname_np(midi_client_in_thread, "midi_in_seq_client_thread ");
}

void AlsaMidiSequencerInputClient::stop_midi_in_seq_client_thread()
{
	// FIX #3: This method is now just a helper that sets the flag
	// The actual join happens in the destructor
	midi_in_client_thread_is_running = false;
}

snd_seq_t* AlsaMidiSequencerInputClient::open_seq()
{

	snd_seq_t* seq_handle;
	snd_seq_port_info_t* port_info;
	snd_seq_client_info_t* client_info;
	int port_id;

	int ret = snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_INPUT, 0);
	if (ret != 0)
	{
		fprintf(stderr, "ALSA MIDI sequencer: Error opening ALSA sequencer %s.\n", client_name.c_str());
		return NULL;
	}

	snd_seq_set_client_name(seq_handle, client_name.c_str());
	if ((port_id = snd_seq_create_simple_port(seq_handle,
		client_name.c_str(),
		SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
		SND_SEQ_PORT_TYPE_APPLICATION)) < 0) {
			fprintf(stderr, "ALSA MIDI sequencer: Error creating sequencer port %s.\n", client_name.c_str());
		return NULL;
	}

	client_id = snd_seq_client_id(seq_handle);

	return(seq_handle);
}


void AlsaMidiSequencerInputClient::close_seq()
{
	if (midi_in_seq)
	{
		snd_seq_close(midi_in_seq);
		midi_in_seq = nullptr;  // Added: Clear pointer after closing
	}
}

std::string AlsaMidiSequencerInputClient::get_client_name()
{
	return client_name;
}

int AlsaMidiSequencerInputClient::get_client_id()
{
	return client_id;
}

void* AlsaMidiSequencerInputClient::thread_wraper(void* object)
{
	reinterpret_cast<AlsaMidiSequencerInputClient*>(object)->midi_in_seq_client_thread();
	return 0;
}

void* AlsaMidiSequencerInputClient::midi_in_seq_client_thread()
{
	snd_seq_t* midi_in = open_seq();  
	int npfd;
	struct pollfd* pfd;
	snd_seq_event_t* ev, * qev;

	npfd = snd_seq_poll_descriptors_count(midi_in, POLLIN);
	pfd = (struct pollfd*)alloca(npfd * sizeof(struct pollfd));
	snd_seq_poll_descriptors(midi_in, pfd, npfd, POLLIN);

	while (midi_in_client_thread_is_running)
	{
		if (poll(pfd, npfd, 1000) > 0) { // 100000

			do {
				int ret = snd_seq_event_input(midi_in, &ev);

				// Check if event input was successful and ev is not NULL
				if (ret > 0 && ev != NULL)
				{
					qev = new snd_seq_event_t();
					memcpy(qev, ev, sizeof(snd_seq_event_t));

					// FIX #4: Check if still running before enqueue
					// Prevents enqueue after shutdown signal
					if (midi_in_client_thread_is_running && alsa_seq_client_rx_queue) {
						alsa_seq_client_rx_queue->enqueue(qev);
					} else {
						// Thread is shutting down, clean up the event
						delete qev;
					}

					/*
									switch (ev->type) {
										case SND_SEQ_EVENT_CONTROLLER:
											fprintf(stderr, "Control event on Channel %2d: %5d       \r",
												ev->data.control.channel, ev->data.control.value);
											break;
										case SND_SEQ_EVENT_PITCHBEND:
											fprintf(stderr, "Pitchbender event on Channel %2d: %5d   \r",
												ev->data.control.channel, ev->data.control.value);
											break;
										case SND_SEQ_EVENT_NOTEON:
											fprintf(stderr, "Note On event on Channel %2d: %5d       \r",
												ev->data.control.channel, ev->data.note.note);
											break;
										case SND_SEQ_EVENT_NOTEOFF:
											fprintf(stderr, "Note Off event on Channel %2d: %5d      \r",
												ev->data.control.channel, ev->data.note.note);
											break;
									}
					*/
					snd_seq_free_event(ev);
				}
				else if (ret < 0)
				{
					// Error occurred
					fprintf(stderr, "ALSA MIDI sequencer: Error reading event: %s\n", snd_strerror(ret));
					break; // Exit the do-while loop on error
				}
				// If ret == 0 or ev == NULL, just skip this iteration
			} while (snd_seq_event_input_pending(midi_in, 0) > 0);
		}
	}

	// Thread is exiting cleanly
	return NULL;
}
