//
// nutrt-spinlock.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/nutrt-defines.hpp>

#ifndef COCONUT_RUNTIME_SPINLOCK_HPP
#define COCONUT_RUNTIME_SPINLOCK_HPP

namespace coconut
{ namespace runtime
{

COCONUT_PRIVATE class COCONUT_VISIBLE COCONUT_ALIGNAS(64) spinlock COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.spinlock, spinlock)

public:
	spinlock();
	spinlock(spinlock &) = default;
	virtual ~spinlock();
	
public:
	void lock();
	bool try_lock();
	void unlock();

private:
	std::int16_t ___M_cycle;
	std::int16_t ___M_loop;
	std::atomic_flag ___M_lock;
	std::atomic<bool> ___M_out;
};

}} /* EONS */

#endif /* !COCONUT_RUNTIME_SPINLOCK_HPP */

/* EOF */