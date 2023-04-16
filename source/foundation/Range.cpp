//
// Range.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Range.hpp>
#include <coconut/foundation/MutableRange.hpp>

using namespace coconut;

Range::Range() :
	Object(RangeClass),
	___M_impl()
{ /* NOP */ }

Range::Range(const Range & rg) :
	Object(RangeClass),
	___M_impl(rg.___M_impl)
{ /* NOP */ }

Range::Range(Range && rg) noexcept :
	Object(RangeClass),
	___M_impl(std::move(rg.___M_impl))
{ /* NOP */ }

Range::Range(std::size_t location, std::size_t length) :
	Object(RangeClass),
	___M_impl(location, length)
{ /* NOP */ }

Range::~Range()
{ /* NOP */ }

#pragma mark -

std::size_t Range::hash() const
{ return maxRange(); }

#pragma mark -

Owning<Any> Range::copy() const
{ return ptr_create<Range>(*this); }

Owning<Any> Range::mutableCopy() const
{ return ptr_create<MutableRange>(*this); }

#pragma mark -

ComparisonResult Range::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return ___M_impl.compare(ref_cast<Range>(ref).___M_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string Range::stringValue() const
{ return ___M_impl.to_string(); }

#pragma mark -

std::size_t Range::location() const
{ return ___M_impl.location(); }

std::size_t Range::length() const
{ return ___M_impl.length(); }

#pragma mark -

bool Range::isZeroRange() const
{ return ___M_impl.iszero(); }

std::size_t Range::maxRange() const
{ return ___M_impl.max(); }

#pragma mark -

bool Range::locationInRange(std::size_t location) const
{ return ___M_impl.in(location); }

const Range Range::intersectionRange(const Range & other_rg) const
{
	impl_trait rg = ___M_impl.intxn(other_rg.___M_impl);
	return Range(rg.location(), rg.length());
}

const Range Range::unionRange(const Range & other_rg) const
{
	impl_trait rg = ___M_impl.merge(other_rg.___M_impl);
	return Range(rg.location(), rg.length());
}

#pragma mark -

Range::iterator Range::begin() { return ___M_impl.begin(); }
Range::iterator Range::end() { return ___M_impl.end(); }

Range::const_iterator Range::begin() const { return ___M_impl.begin(); }
Range::const_iterator Range::end() const { return ___M_impl.end(); }

Range::const_iterator Range::cbegin() const { return ___M_impl.cbegin(); }
Range::const_iterator Range::cend() const { return ___M_impl.cend(); }

Range::reverse_iterator Range::rbegin() { return ___M_impl.rbegin(); }
Range::reverse_iterator Range::rend() { return ___M_impl.rend(); }

Range::const_reverse_iterator Range::rbegin() const { return ___M_impl.rbegin(); }
Range::const_reverse_iterator Range::rend() const { return ___M_impl.rend(); }

Range::const_reverse_iterator Range::crbegin() const { return ___M_impl.crbegin(); }
Range::const_reverse_iterator Range::crend() const { return ___M_impl.crend(); }

#pragma mark -

bool EqualRanges(const Range & rg1, const Range & rg2)
{ return rg1.isEqual(rg2); }

Range IntersectionRange(const Range & rg1, const Range & rg2)
{ return rg1.intersectionRange(rg2); }

bool LocationInRange(std::size_t location, const Range & rg)
{ return rg.locationInRange(location); }

Range MakeRange(std::size_t location, std::size_t length)
{ return Range(location, length); }

std::size_t MaxRange(const Range & rg)
{ return rg.maxRange(); }

Range UnionRange(const Range & rg1, const Range & rg2)
{ return rg1.unionRange(rg2); }
	
/* EOF */