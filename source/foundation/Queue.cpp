//
// Queue.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Queue.hpp>

using namespace coconut;

Queue::Queue() :
	Object(QueueClass),
	___M_impl()
{ /* NOP */ }

Queue::Queue(const Queue & que) :
	Object(QueueClass),
	___M_impl(que.___M_impl)
{ /* NOP */ }

Queue::Queue(Queue && que) noexcept :
	Object(QueueClass),
	___M_impl(std::move(que.___M_impl))
{ /* NOP */ }

Queue::~Queue()
{ /* NOP */ }

#pragma mark -

Owning<Any> Queue::copy() const
{ return ptr_create<Queue>(*this); }

#pragma mark -

std::size_t Queue::size() const
{ return ___M_impl.size(); }

#pragma mark -

void Queue::enqueue(const Owning<Any> & obj)
{ if (obj) { ___M_impl.push(obj); } }

const Owning<Any> Queue::dequeue()
{
	Owning<Any> head;
	if (___M_impl.size()) {
		head = ___M_impl.front();
		___M_impl.pop();
	}
	return head;
}

#pragma mark -

const Owning<Any> Queue::peek() const
{
	Owning<Any> first;
	if (___M_impl.size()) {
		first = ___M_impl.front();
	}
	return first;
}

#pragma mark -

void Queue::clear()
{
	impl_trait none;
	std::swap(___M_impl, none);
}

/* EOF */