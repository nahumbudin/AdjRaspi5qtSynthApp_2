/**
 * SIDE-BY-SIDE CODE COMPARISON
 * =============================
 * This file shows EXACTLY what to change in each location
 */

// ═══════════════════════════════════════════════════════════════════════════
// FILE: safeQueues.h - Constructor
// ═══════════════════════════════════════════════════════════════════════════

// ❌ BEFORE (BUGGY):
SafeQueue(void)
	: q()    // The Q
	, m()    // Mutex
	, c()    // condition_variable
{}

// ✅ AFTER (FIXED):
SafeQueue(void)
	: q()    // The Q
	, m()    // Mutex
	, c()    // condition_variable
	, msec(1)  // ← ADD THIS: Initialize msec to 1 millisecond
	, shutdown_flag(false)  // ← ADD THIS: Initialize shutdown flag
{}


// ═══════════════════════════════════════════════════════════════════════════
// FILE: safeQueues.h - Destructor
// ═══════════════════════════════════════════════════════════════════════════

// ❌ BEFORE (BUGGY):
~SafeQueue(void)
{}

// ✅ AFTER (FIXED):
~SafeQueue(void)
{
	shutdown();  // ← ADD THIS: Wake waiting threads before destruction
}


// ═══════════════════════════════════════════════════════════════════════════
// FILE: safeQueues.h - enqueue() method
// ═══════════════════════════════════════════════════════════════════════════

// ❌ BEFORE (BUGGY):
void enqueue(T t)
{
	std::lock_guard<std::mutex> lock(m);
	q.push(t);
	c.notify_one();
	msec = std::chrono::milliseconds(1);  // ← REMOVE: Too late, already used!
}

// ✅ AFTER (FIXED):
void enqueue(T t)
{
	std::lock_guard<std::mutex> lock(m);
	if (shutdown_flag) {  // ← ADD THIS: Don't enqueue if shutting down
		return;
	}
	q.push(t);
	c.notify_one();
	// msec line REMOVED
}


// ═══════════════════════════════════════════════════════════════════════════
// FILE: safeQueues.h - dequeue() method wait loop
// ═══════════════════════════════════════════════════════════════════════════

// ❌ BEFORE (BUGGY):
// A blocking call
while (q.empty())
{
	// release lock as long as the wait and reaquire it afterwards.
	if ((waitfor_msec <= 0) && (timeoutexit != NULL))
	{
		c.wait(lock);
	}
	else
	{
		stat = c.wait_for(lock, waitfor_msec * msec);
		if (stat == std::cv_status::timeout)
		{
			*timeoutexit = true;
			return val;
		}
	}
}

// ✅ AFTER (FIXED):
// A blocking call
while (q.empty())
{
	// ↓↓↓ ADD THIS ENTIRE BLOCK ↓↓↓
	// Check if shutting down
	if (shutdown_flag) {
		if (timeoutexit != NULL) {
			*timeoutexit = true;
		}
		return val;  // Return NULL on shutdown
	}
	// ↑↑↑ END OF ADDED BLOCK ↑↑↑

	// release lock as long as the wait and reaquire it afterwards.
	if ((waitfor_msec <= 0) && (timeoutexit != NULL))
	{
		c.wait(lock);
	}
	else
	{
		stat = c.wait_for(lock, waitfor_msec * msec);
		if (stat == std::cv_status::timeout)
		{
			*timeoutexit = true;
			return val;
		}
	}
}


// ═══════════════════════════════════════════════════════════════════════════
// FILE: safeQueues.h - Add new public method (before "private:")
// ═══════════════════════════════════════════════════════════════════════════

// ❌ BEFORE: Nothing here

// ✅ AFTER: ADD THIS METHOD
// Shutdown the queue - wake all waiting threads
void shutdown()
{
	std::lock_guard<std::mutex> lock(m);
	shutdown_flag = true;
	c.notify_all();  // Wake all waiting threads
}


// ═══════════════════════════════════════════════════════════════════════════
// FILE: safeQueues.h - Member variables (in "private:" section)
// ═══════════════════════════════════════════════════════════════════════════

// ❌ BEFORE:
private:
	std::queue<T> q;
	mutable std::mutex m;
	std::condition_variable c;
	std::chrono::milliseconds msec;
};

// ✅ AFTER:
private:
	std::queue<T> q;
	mutable std::mutex m;
	std::condition_variable c;
	std::chrono::milliseconds msec;
	bool shutdown_flag;  // ← ADD THIS member variable
};


// ═══════════════════════════════════════════════════════════════════════════
// FILE: AlsaMidiSequencerInputClient.cpp - Destructor
// ═══════════════════════════════════════════════════════════════════════════

// ❌ BEFORE (BUGGY - CAUSES CRASH):
~AlsaMidiSequencerInputClient()
{
	// Close ALSA
	if (midi_in_seq) {
		snd_seq_close(midi_in_seq);
	}

	// Delete queue
	delete alsa_seq_client_rx_queue;  // 💥 CRASH - Threads still running!
}

// ✅ AFTER (FIXED - SAFE):
~AlsaMidiSequencerInputClient()
{
	// ↓↓↓ ADD THIS ENTIRE BLOCK AT THE START ↓↓↓

	// STEP 1: Signal threads to stop
	midi_in_client_thread_is_running = false;

	// STEP 2: Wake threads waiting in queue
	if (alsa_seq_client_rx_queue) {
		alsa_seq_client_rx_queue->shutdown();
	}

	// STEP 3: Wait for thread to completely finish
	if (midi_client_in_thread) {
		pthread_join(midi_client_in_thread, nullptr);
		midi_client_in_thread = 0;
	}

	// ↑↑↑ END OF ADDED BLOCK ↑↑↑

	// STEP 4: NOW it's safe to delete the queue
	if (alsa_seq_client_rx_queue) {
		delete alsa_seq_client_rx_queue;
		alsa_seq_client_rx_queue = nullptr;
	}

	// Close ALSA
	if (midi_in_seq) {
		snd_seq_close(midi_in_seq);
		midi_in_seq = nullptr;
	}
}


// ═══════════════════════════════════════════════════════════════════════════
// FILE: AlsaMidiSequencerInputClient.cpp - Thread function
// ═══════════════════════════════════════════════════════════════════════════

// ❌ BEFORE (UNSAFE):
void AlsaMidiSequencerInputClient::midi_in_seq_client_thread()
{
	snd_seq_event_t *event = nullptr;

	while (midi_in_client_thread_is_running) {
		// Get MIDI event
		int result = snd_seq_event_input(midi_in_seq, &event);

		if (result < 0) {
			continue;  // Error handling
		}

		// Push to queue
		alsa_seq_client_rx_queue->enqueue(event);  // 💥 No check if shutting down!
	}
}

// ✅ AFTER (SAFE):
void AlsaMidiSequencerInputClient::midi_in_seq_client_thread()
{
	snd_seq_event_t *event = nullptr;

	while (midi_in_client_thread_is_running) {
		// Get MIDI event
		int result = snd_seq_event_input(midi_in_seq, &event);

		if (result < 0) {
			if (result == -EAGAIN || result == -ENOSPC) {
				continue;
			}
			break;  // Fatal error
		}

		// ↓ ADD CHECK: Only enqueue if still running
		if (event && midi_in_client_thread_is_running) {  // ← ADD CHECK HERE
			alsa_seq_client_rx_queue->enqueue(event);
		}
	}

	// Thread is exiting cleanly
}


// ═══════════════════════════════════════════════════════════════════════════
// OPTIONAL: Add debug logging to verify fix
// ═══════════════════════════════════════════════════════════════════════════

// Add to destructor for debugging:
~AlsaMidiSequencerInputClient()
{
	printf("[DEBUG] Destructor: Step 1 - Setting running flag to false\n");
	midi_in_client_thread_is_running = false;

	printf("[DEBUG] Destructor: Step 2 - Calling queue shutdown\n");
	if (alsa_seq_client_rx_queue) {
		alsa_seq_client_rx_queue->shutdown();
	}

	printf("[DEBUG] Destructor: Step 3 - Joining thread...\n");
	if (midi_client_in_thread) {
		pthread_join(midi_client_in_thread, nullptr);
		printf("[DEBUG] Destructor: Step 3 - Thread joined successfully\n");
		midi_client_in_thread = 0;
	}

	printf("[DEBUG] Destructor: Step 4 - Deleting queue\n");
	if (alsa_seq_client_rx_queue) {
		delete alsa_seq_client_rx_queue;
		alsa_seq_client_rx_queue = nullptr;
	}

	printf("[DEBUG] Destructor: Complete\n");

	// Close ALSA
	if (midi_in_seq) {
		snd_seq_close(midi_in_seq);
		midi_in_seq = nullptr;
	}
}

// Expected output when fix is working:
// [DEBUG] Destructor: Step 1 - Setting running flag to false
// [DEBUG] Destructor: Step 2 - Calling queue shutdown
// [DEBUG] Destructor: Step 3 - Joining thread...
// [DEBUG] Destructor: Step 3 - Thread joined successfully
// [DEBUG] Destructor: Step 4 - Deleting queue
// [DEBUG] Destructor: Complete


// ═══════════════════════════════════════════════════════════════════════════
// SUMMARY OF CHANGES
// ═══════════════════════════════════════════════════════════════════════════

/**
 * safeQueues.h (7 changes):
 * 1. Add msec(1) to constructor initializer list
 * 2. Add shutdown_flag(false) to constructor initializer list
 * 3. Add shutdown() call in destructor
 * 4. Add shutdown_flag check in enqueue()
 * 5. Remove msec assignment from enqueue()
 * 6. Add shutdown_flag check in dequeue() wait loop
 * 7. Add shutdown() public method
 * 8. Add shutdown_flag member variable
 * 
 * AlsaMidiSequencerInputClient.cpp (2 changes):
 * 1. Fix destructor with 4-step shutdown sequence
 * 2. Add running flag check before enqueue in thread function
 * 
 * Total: ~20 lines added, ~1 line removed, ~2 lines modified
 * Impact: CRITICAL - Fixes segmentation fault crash
 */
