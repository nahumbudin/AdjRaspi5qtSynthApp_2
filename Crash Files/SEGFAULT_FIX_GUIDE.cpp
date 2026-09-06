/**
 * SEGMENTATION FAULT FIX - IMPLEMENTATION GUIDE
 * ==============================================
 * 
 * CRASH ANALYSIS SUMMARY:
 * The segmentation fault occurs because the SafeQueue<snd_seq_event*> object
 * is destroyed while 3 MIDI input threads are still actively using it.
 * 
 * ROOT CAUSE: Use-After-Free
 * - SafeQueue is destroyed (memory filled with patterns like 0x5555, 0x5F5F)
 * - 3 threads (IDs: 2, 3, 4) simultaneously try to enqueue() MIDI events
 * - Threads access destroyed deque internals, crash when writing to 0x5555
 * 
 * EVIDENCE FROM DEBUGGER:
 * - SafeQueue address: 0x555500E170A8 (93825084463656)
 * - Corrupted _M_map: 0x4FF5FF5FF5FF5FFF (freed memory pattern)
 * - Crash address __p: 0x5555 (21845) - classic freed memory marker
 * - msec value: 8742381210945547334 (uninitialized garbage)
 * - All 3 threads stuck at same allocator construct() call
 * - mutex.__owner = 4979 (proves mutex was locked AFTER corruption)
 * 
 * REQUIRED FIXES:
 * ===============
 */

/** 
 * FIX #1: Replace safeQueues.h with the fixed version
 * ----------------------------------------------------
 * Location: libAdjRaspi5Synth2/LibAPI/safeQueues.h (or similar path)
 * 
 * The original SafeQueue has critical bugs:
 * 1. Uninitialized msec member variable (causes garbage value)
 * 2. No shutdown mechanism to wake waiting threads
 * 3. No checks to prevent operations during destruction
 * 
 * ACTION: Replace the original safeQueues.h with safeQueues_FIXED.h
 * The fixed version includes:
 * - Proper msec initialization in constructor
 * - shutdown_flag member variable
 * - shutdown() method that wakes all waiting threads
 * - Checks in enqueue/dequeue to prevent use-after-free
 */

/**
 * FIX #2: Update AlsaMidiSequencerInputClient destructor
 * -------------------------------------------------------
 * Location: libAdjRaspi5Synth2/LibAPI/AlsaMidiSequencerInputClient.cpp
 * 
 * The destructor must follow this EXACT sequence:
 */

// ORIGINAL (BUGGY) - DO NOT USE:
// ~AlsaMidiSequencerInputClient() {
//     delete alsa_seq_client_rx_queue;  // ❌ WRONG - threads still running!
// }

// FIXED VERSION - USE THIS:
~AlsaMidiSequencerInputClient() {
	// CRITICAL: Follow this order exactly!

	// STEP 1: Signal threads to stop
	midi_in_client_thread_is_running = false;

	// STEP 2: Shutdown the queue to wake any threads waiting in dequeue()
	if (alsa_seq_client_rx_queue) {
		alsa_seq_client_rx_queue->shutdown();
	}

	// STEP 3: Join the thread - WAIT for it to completely finish
	// DO NOT proceed until thread has exited!
	if (midi_client_in_thread) {
		pthread_join(midi_client_in_thread, nullptr);
		midi_client_in_thread = 0;
	}

	// STEP 4: Only NOW is it safe to delete the queue
	if (alsa_seq_client_rx_queue) {
		delete alsa_seq_client_rx_queue;
		alsa_seq_client_rx_queue = nullptr;
	}

	// Close ALSA sequencer
	if (midi_in_seq) {
		snd_seq_close(midi_in_seq);
		midi_in_seq = nullptr;
	}
}

/**
 * FIX #3: Update midi_in_seq_client_thread() to check shutdown flag
 * ------------------------------------------------------------------
 * Location: libAdjRaspi5Synth2/LibAPI/AlsaMidiSequencerInputClient.cpp
 * 
 * The thread function must check the running flag before enqueuing:
 */

void AlsaMidiSequencerInputClient::midi_in_seq_client_thread()
{
	snd_seq_event_t *event = nullptr;

	while (midi_in_client_thread_is_running) {
		// Poll or wait for MIDI events from ALSA
		int result = snd_seq_event_input(midi_in_seq, &event);

		if (result < 0) {
			// Error handling
			if (result == -EAGAIN || result == -ENOSPC) {
				continue;
			}
			// Fatal error
			break;
		}

		// CRITICAL: Check flag BEFORE enqueue to prevent use-after-free
		if (event && midi_in_client_thread_is_running) {
			alsa_seq_client_rx_queue->enqueue(event);
		}
	}

	// Thread is exiting - safe to join now
}

/**
 * FIX #4: Add proper initialization in constructor
 * -------------------------------------------------
 * Ensure the constructor initializes the queue before starting threads:
 */

AlsaMidiSequencerInputClient::AlsaMidiSequencerInputClient(const char* name)
	: client_name(name)
	, client_id(-1)
	, midi_in_seq(nullptr)
	, alsa_seq_client_rx_queue(nullptr)  // Start as nullptr
	, midi_client_in_thread(0)
	, midi_in_client_thread_is_running(false)
{
	// Open ALSA sequencer first
	if (snd_seq_open(&midi_in_seq, "default", SND_SEQ_OPEN_INPUT, 0) < 0) {
		// Handle error
		return;
	}

	// Create the queue BEFORE starting threads
	alsa_seq_client_rx_queue = new SafeQueue<snd_seq_event*>();

	// NOW start the thread
	midi_in_client_thread_is_running = true;
	pthread_create(&midi_client_in_thread, nullptr, thread_wraper, this);
}

/**
 * FIX #5: Optional - Add stop() method for explicit shutdown
 * -----------------------------------------------------------
 * This allows explicit shutdown without waiting for destructor:
 */

void AlsaMidiSequencerInputClient::stop()
{
	if (!midi_in_client_thread_is_running) {
		return;  // Already stopped
	}

	// Same sequence as destructor
	midi_in_client_thread_is_running = false;

	if (alsa_seq_client_rx_queue) {
		alsa_seq_client_rx_queue->shutdown();
	}

	if (midi_client_in_thread) {
		pthread_join(midi_client_in_thread, nullptr);
		midi_client_in_thread = 0;
	}
}

/**
 * TESTING CHECKLIST:
 * ==================
 * After applying fixes, verify:
 * 
 * 1. ✓ No segfaults when closing MIDI devices
 * 2. ✓ No segfaults during application shutdown
 * 3. ✓ Multiple MIDI input clients can be created/destroyed safely
 * 4. ✓ Thread joins complete within reasonable time (not hanging)
 * 5. ✓ No memory leaks (check with valgrind if possible)
 * 6. ✓ MIDI events are still processed correctly
 * 
 * VERIFICATION:
 * =============
 * Before the fix: 3 threads crash at 0x5555 in allocator
 * After the fix: Clean shutdown, threads exit gracefully
 * 
 * The key is: SHUTDOWN → JOIN → DELETE (in that exact order!)
 */

/**
 * DEBUGGING TIPS:
 * ===============
 * If you still see crashes after applying fixes:
 * 
 * 1. Add debug logging to track shutdown sequence:
 *    printf("Step 1: Setting running flag to false\n");
 *    printf("Step 2: Calling queue shutdown\n");
 *    printf("Step 3: Joining thread...\n");
 *    printf("Step 3: Thread joined successfully\n");
 *    printf("Step 4: Deleting queue\n");
 * 
 * 2. Check if there are OTHER SafeQueue instances or threads
 * 
 * 3. Verify the thread actually checks midi_in_client_thread_is_running
 * 
 * 4. Use thread sanitizer: compile with -fsanitize=thread
 * 
 * 5. Check for other code that might delete the client object prematurely
 */

/**
 * ADDITIONAL CONSIDERATIONS:
 * ==========================
 * 
 * 1. If AlsaMidiSequencerInputClient is used in multiple places,
 *    ensure ALL instances follow proper shutdown
 * 
 * 2. Consider using std::atomic<bool> for midi_in_client_thread_is_running
 *    for stronger memory ordering guarantees
 * 
 * 3. Consider using std::thread instead of pthread for better C++ integration
 * 
 * 4. The fixed SafeQueue is now safe, but the dequeue() thread should still
 *    check the return value for nullptr when shutdown occurs
 */
