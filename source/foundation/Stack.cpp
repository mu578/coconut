//
// Stack.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Stack.hpp>

using namespace coconut;

Stack::Stack() :
	Object(StackClass),
	___M_impl()
{ /* NOP */ }

Stack::Stack(const Stack & stk) :
	Object(StackClass),
	___M_impl(stk.___M_impl)
{ /* NOP */ }

Stack::Stack(Stack && stk) noexcept :
	Object(StackClass),
	___M_impl(std::move(stk.___M_impl))
{ /* NOP */ }

Stack::~Stack()
{ /* NOP */ }

#pragma mark -

Owning<Any> Stack::copy() const
{ return ptr_create<Stack>(*this); }

#pragma mark -

std::size_t Stack::size() const
{ return ___M_impl.size(); }

#pragma mark -

void Stack::push(const Owning<Any> & obj)
{ if (obj) { ___M_impl.push(obj); } }

#pragma mark -

const Owning<Any> Stack::pop()
{
	Owning<Any> head;
	if (___M_impl.size()) {
		head = ___M_impl.top();
		___M_impl.pop();
	}
	return head;
}

#pragma mark -

const Owning<Any> Stack::peek() const
{
	Owning<Any> last;
	if (___M_impl.size()) {
		last = ___M_impl.top();
	}
	return last;
}

#pragma mark -

void Stack::clear()
{
	impl_trait none;
	std::swap(___M_impl, none);
}

/* EOF */