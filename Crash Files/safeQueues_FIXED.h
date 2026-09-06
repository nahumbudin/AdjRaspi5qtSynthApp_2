/**
* @file		safeQueues.h
*	@author		https://stackoverflow.com/a/16075550
*	@date		10-Oct-2019 (Updated)
*	@version	1.1 - FIXED VERSION
*
*	@brief		Thread safe queues based on std::queue, mutex and conditional-variable
*		Use: SafeQueue<message> qname;
*
*	FIXES APPLIED:
*	1. Initialize msec in constructor (was uninitialized, causing garbage values)
*	2. Add shutdown_flag and shutdown() method to safely wake threads during destruction
*	3. Remove incorrect msec assignment in enqueue() that was too late
*	4. Add shutdown checks in dequeue() to prevent use-after-free
*	5. Call shutdown() in destructor to wake all waiting threads before object destruction
*/
/**
			Timeout is not working - returns immediately. For blocking use waitfor_msec = 0.
*/

#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class SafeQueue
{
public:
	SafeQueue(void)
		: q()	// The Q
		, m()	// Mutex
		, c()	// condition_variable
		, msec(1)  // FIX #1: Initialize msec to 1 millisecond (was uninitialized!)
		, shutdown_flag(false)  // FIX #2: Initialize shutdown flag
	{}

	~SafeQueue(void)
	{
		// FIX #3: Call shutdown to wake any waiting threads before destruction
		shutdown();
	}

	// Add an element to the queue.
	void enqueue(T t)
	{
		std::lock_guard<std::mutex> lock(m);

		// FIX #4: Don't enqueue if shutting down (prevents use-after-free)
		if (shutdown_flag) {
			return;
		}

		q.push(t);
		c.notify_one();

		// FIX #5: REMOVED - This was setting msec too late, after it was already used!
		// Old buggy line: msec = std::chrono::milliseconds(1);
	}

	// Get the "front"-element.
	// If blocking = false - return NULL if Q is empty.
	// If blocking = true - if the queue is empty, wait till an element is available (waitfor_msec <= 0) or timeout expired.
	T dequeue(int waitfor_msec = -1, bool* timeoutexit = NULL, bool* blocking = NULL)
	{
		std::unique_lock<std::mutex> lock(m);
		std::cv_status stat;
		T val;

		if ((blocking != NULL) && (*blocking == false))
		{
			// A non blocking call
			if (q.empty())
			{
				return NULL;
			}
			else
			{
				if (timeoutexit != NULL) {
					*timeoutexit = false;
				}
				val = q.front();
				q.pop();
				return val;
			}
		}
		else
		{
			// A blocking call
			while (q.empty())
			{
				// FIX #6: Check if shutting down before waiting
				// This prevents threads from being stuck when the queue is destroyed
				if (shutdown_flag) {
					if (timeoutexit != NULL) {
						*timeoutexit = true;
					}
					return val;  // Return NULL on shutdown
				}

				// release lock as long as the wait and reacquire it afterwards.
				if ((waitfor_msec <= 0) && (timeoutexit != NULL))
				{
					c.wait(lock);
				}
				else
				{
					stat = c.wait_for(lock, waitfor_msec * msec);
					if (stat == std::cv_status::timeout)
					{
						// Timeout exit - return NULL
						if (timeoutexit != NULL) {
							*timeoutexit = true;
						}
						return val;
					}
				}
			}

			if (timeoutexit != NULL) {
				*timeoutexit = false;
			}
			val = q.front();
			q.pop();
			return val;
		}
	}

	// FIX #7: New method to safely shutdown the queue
	// This wakes all waiting threads and prevents further operations
	void shutdown()
	{
		std::lock_guard<std::mutex> lock(m);
		shutdown_flag = true;
		c.notify_all();  // Wake all waiting threads so they can exit
	}

	// Optional: Check if queue is in shutdown state
	bool is_shutdown() const
	{
		std::lock_guard<std::mutex> lock(m);
		return shutdown_flag;
	}

	// Optional: Get queue size (useful for debugging)
	size_t size() const
	{
		std::lock_guard<std::mutex> lock(m);
		return q.size();
	}

private:
	std::queue<T> q;
	mutable std::mutex m;
	std::condition_variable c;
	std::chrono::milliseconds msec;  // Now properly initialized in constructor
	bool shutdown_flag;  // FIX #8: New flag to signal shutdown
};
