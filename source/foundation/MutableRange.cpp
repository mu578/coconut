//
// MutableRange.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/MutableRange.hpp>

using namespace coconut;

MutableRange::MutableRange() :
	Range()
{ setClassKind(MutableRangeClass, true); }

MutableRange::MutableRange(const MutableRange & rg) :
	Range(ref_cast<Range>(rg))
{ setClassKind(MutableRangeClass, true); }

MutableRange::MutableRange(const Range & rg) :
	Range(rg)
{ setClassKind(MutableRangeClass, true); }

MutableRange::MutableRange(std::size_t location, std::size_t length) :
	Range(location, length)
{ setClassKind(MutableRangeClass, true); }

MutableRange::~MutableRange()
{ setClassKind(MutableRangeClass, true); }

#pragma mark -

MutableRange & MutableRange::setLocation(std::size_t location)
{ ___M_impl.set_location(location); return *this;}

MutableRange & MutableRange::setLength(std::size_t length)
{ ___M_impl.set_length(length); return *this; }

/* EOF */