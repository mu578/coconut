//
// Slice.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Slice.hpp>
#include <coconut/foundation/Range.hpp>

using namespace coconut;

Slice::Slice() :
	Object(SliceClass),
	___M_impl()
{ /* NOP */ }

Slice::Slice(const Slice & slc) :
	Object(SliceClass),
	___M_impl(slc.___M_impl)
{ /* NOP */ }

Slice::Slice(Slice && slc) noexcept :
	Object(SliceClass),
	___M_impl(std::move(slc.___M_impl))
{ /* NOP */ }

Slice::Slice(std::int64_t start, std::int64_t stop) :
	Slice(start, stop, 1)
{ /* NOP */ }

Slice::Slice(std::int64_t start, std::int64_t stop, std::int64_t step) :
	Object(SliceClass),
	___M_impl(start, stop, step)
{ /* NOP */ }

Slice::Slice(const Range & rg) :
	Slice(
		static_cast<std::int64_t>(rg.location()),
		static_cast<std::int64_t>(rg.length()),
		1
	)
{ /* NOP */ }

Slice::~Slice()
{ /* NOP */ }

#pragma mark -

std::size_t Slice::hash() const
{ return ___M_impl.start() + ___M_impl.stop() + ___M_impl.step(); }

#pragma mark -

Owning<Any> Slice::copy() const
{ return ptr_create<Slice>(*this); }

#pragma mark -

ComparisonResult Slice::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return ___M_impl.compare(ref_cast<Slice>(ref).___M_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string Slice::stringValue() const
{ return ___M_impl.to_string(); }

#pragma mark -

std::int64_t Slice::start() const
{ return ___M_impl.start(); }

std::int64_t Slice::stop() const
{ return ___M_impl.stop(); }

std::int64_t Slice::step() const
{ return ___M_impl.step(); }

#pragma mark -

void Slice::indexesForLength(std::size_t length) const
{ ___M_impl.do_indexes(length); }

#pragma mark -

Slice::iterator Slice::begin() { return ___M_impl.begin(); }
Slice::iterator Slice::end() { return ___M_impl.end(); }

Slice::const_iterator Slice::begin() const { return ___M_impl.begin(); }
Slice::const_iterator Slice::end() const { return ___M_impl.end(); }

Slice::const_iterator Slice::cbegin() const { return ___M_impl.cbegin(); }
Slice::const_iterator Slice::cend() const { return ___M_impl.cend(); }

Slice::reverse_iterator Slice::rbegin() { return ___M_impl.rbegin(); }
Slice::reverse_iterator Slice::rend() { return ___M_impl.rend(); }

Slice::const_reverse_iterator Slice::rbegin() const { return ___M_impl.rbegin(); }
Slice::const_reverse_iterator Slice::rend() const { return ___M_impl.rend(); }

Slice::const_reverse_iterator Slice::crbegin() const { return ___M_impl.crbegin(); }
Slice::const_reverse_iterator Slice::crend() const { return ___M_impl.crend(); }

/* EOF */