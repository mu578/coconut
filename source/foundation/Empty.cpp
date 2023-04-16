//
// Empty.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Empty.hpp>

using namespace coconut;

Empty::Empty() :
	Object(EmptyClass)
{ /* NOP */ }

Empty::Empty(const Empty & emp) :
	Object(EmptyClass)
{ COCONUT_UNUSED(emp); }

Empty::~Empty()
{ /* NOP */ }

#pragma mark -

Owning<Any> Empty::copy() const
{ return ptr_create<Empty>(*this); }

ComparisonResult Empty::compare(const Any & ref) const
{
	if (isMemberOf(ref)) {
		return OrderedSame;
	}
	return OrderedDescending;
}

#pragma mark -

std::string Empty::stringValue() const
{ return u8"<empty>"; }

/* EOF */