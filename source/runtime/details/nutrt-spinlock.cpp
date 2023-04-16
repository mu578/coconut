//
// nutrt-spinlock.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/nutrt-spinlock.hpp>

using namespace coconut::runtime;

spinlock::spinlock()
: ___M_cycle(0)
, ___M_loop(0)
, ___M_lock(ATOMIC_FLAG_INIT)
, ___M_out(false)
{ /* NOP */ }

spinlock::~spinlock()
{
	___M_out = true;
	___M_cycle = 0;
	___M_loop = 0;
}

void spinlock::lock()
{
	if (___M_out.load()) { return; }
	___M_cycle = 8;
	while (--___M_cycle) {
		___M_loop = 300;
		while (--___M_loop) {
			if (!___M_lock.test_and_set(std::memory_order_acquire)) {
				//std::cerr << "spinlock ___M_loop: " << ___M_loop << " spinlock ___M_cycle: " << ___M_cycle << std::endl;
				return;
			}
		}
		std::this_thread::yield();
	}
}

bool spinlock::try_lock() {
	if (___M_out.load()) { return false; }
	return !___M_lock.test_and_set(std::memory_order_acquire);
}

void spinlock::unlock()
{
	if (___M_out.load()) { return; }
	___M_lock.clear(std::memory_order_release);
}

/* EOF */