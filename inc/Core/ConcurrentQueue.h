/************************************************************************
*
* Flood Project © (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "Core/Memory.h"
#include <deque>
#include <algorithm>

NAMESPACE_CORE_BEGIN

//-----------------------------------//

struct Mutex;
struct Condition;

/**
 * Concurrent queue that is safe to use even with multiple producers
 * and consumers. This class is based from code located at website:
 * http://www.justsoftwaresolutions.co.uk/threading/implementing-a-
 * thread-safe-queue-using-condition-variables.html
 */

template<typename T> class ConcurrentQueue
{
public:

	ConcurrentQueue()
	{
		mutex = MutexCreate(AllocatorGetThis());
		cond = ConditionCreate(AllocatorGetThis());
	}

	//-----------------------------------//

	~ConcurrentQueue()
	{
		MutexDestroy(mutex);
		ConditionDestroy(cond);
	}

	//-----------------------------------//

	void push_front(const T& value)
	{
		MutexLock(mutex);
		queue.push_front(value);
		MutexUnlock(mutex);
		
		ConditionWakeOne(cond);
	}

	//-----------------------------------//

	void push_back(const T& value)
	{
		MutexLock(mutex);
		queue.push_back(value);
		MutexUnlock(mutex);
		
		ConditionWakeOne(cond);
	}

	//-----------------------------------//

	bool empty() const
	{
		MutexLock(mutex);
		bool empty = queue.empty();
		MutexUnlock(mutex);
		
		return empty;
	}

	//-----------------------------------//

	bool try_pop_front(T& popped_value)
	{
		MutexLock(mutex);
		
		if( queue.empty() )
		{
			MutexUnlock(mutex);
			return false;
		}

		popped_value = queue.front();
		queue.pop_front();
		
		MutexUnlock(mutex);

		return true;
	}

	//-----------------------------------//

	void wait_and_pop_front(T& popped_value)
	{
		MutexLock(mutex);
	
		while( queue.empty() )
			ConditionWait(cond, mutex);
	
		popped_value = queue.front();
		queue.pop_front();

		MutexUnlock(mutex);
	}

	//-----------------------------------//

	bool find(const T& value)
	{
		MutexLock(mutex);

		typename std::deque<T>::const_iterator it;
		it = std::find(queue.begin(), queue.end(), value);
		bool found = it != queue.end();

		MutexUnlock(mutex);

		return found;
	}

	//-----------------------------------//

protected:

	std::deque<T> queue;

	Mutex* mutex;
	Condition* cond;
};

//-----------------------------------//

NAMESPACE_CORE_END