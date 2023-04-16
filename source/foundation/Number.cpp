//
// Number.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Number.hpp>

using namespace coconut;

Number::Number() :
	Object(NumberClass),
	___M_impl()
{ /* NOP */ }

Number::Number(const Number & num) :
	Object(NumberClass),
	___M_impl(num.___M_impl)
{ /* NOP */ }

Number::Number(Number && num) noexcept :
	Object(NumberClass),
	___M_impl(std::move(num.___M_impl))
{ /* NOP */ }

Number::Number(const float & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const double & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const long double & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const bool & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const char & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const short & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const int & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const long & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const long long & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const unsigned char & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const unsigned short & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const unsigned int & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const unsigned long & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::Number(const unsigned long long & value) :
	Object(NumberClass),
	___M_impl(value)
{ /* NOP */ }

Number::~Number()
{ /* NOP */ }

#pragma mark -

std::size_t Number::hash() const
{ return ___M_impl.hash_code(); }

#pragma mark -

Owning<Any> Number::copy() const
{ return ptr_create<Number>(*this); }

#pragma mark -

ComparisonResult Number::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return ___M_impl.compare(ref_cast<Number>(ref).___M_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string Number::stringValue() const
{ return ___M_impl.to_string(); }

#pragma mark -

float Number::floatValue() const
{ return ___M_impl.to_float(); }

double Number::doubleValue() const
{ return ___M_impl.to_double(); }

long double Number::longDoubleValue() const
{ return ___M_impl.to_long_double(); }

bool Number::boolValue() const
{ return ___M_impl.to_bool(); }

char Number::charValue() const
{ return ___M_impl.to_char(); }

short Number::shortValue() const
{ return ___M_impl.to_short(); }

int Number::intValue() const
{ return ___M_impl.to_int(); }

long Number::longValue() const
{ return ___M_impl.to_long(); }

long long Number::longLongValue() const
{ return ___M_impl.to_long_long(); }

unsigned char Number::unsignedCharValue() const
{ return ___M_impl.to_unsigned_char(); }

unsigned short Number::unsignedShortValue() const
{ return ___M_impl.to_unsigned_short(); }

unsigned int Number::unsignedIntValue() const
{ return ___M_impl.to_unsigned_int(); }

unsigned long Number::unsignedLongValue() const
{ return ___M_impl.to_unsigned_long(); }

unsigned long long Number::unsignedLongLongValue() const
{ return ___M_impl.to_unsigned_long_long(); }

#pragma mark -

double Number::realValue() const
{ return ___M_impl.to_real(); }

std::int64_t Number::integerValue() const
{ return ___M_impl.to_integer(); }

std::uint64_t Number::unsignedIntegerValue() const
{ return ___M_impl.to_unsigned_integer(); }

#pragma mark -

bool Number::isUnsigned() const
{ return !___M_impl.is_signed(); }

bool Number::isReal() const
{ return ___M_impl.is_floating(); }

#pragma mark -

NumberType Number::type() const
{ return ___M_impl.type(); }

#pragma mark -

bool coconut::operator == (const Number & left, const Number & right)
{ return (left.compare(right) == OrderedSame); }

bool coconut::operator != (const Number & left, const Number & right)
{ return (left.compare(right) != OrderedSame); }

bool coconut::operator < (const Number & left, const Number & right)
{ return (left.compare(right) == OrderedAscending); }

bool coconut::operator <= (const Number & left, const Number & right)
{
	ComparisonResult cmp = left.compare(right);
	return (cmp == OrderedAscending || cmp == OrderedSame);
}

bool coconut::operator > (const Number & left, const Number & right)
{ return (left.compare(right) == OrderedDescending); }

bool coconut::operator >= (const Number & left, const Number & right)
{
	ComparisonResult cmp = left.compare(right);
	return (cmp == OrderedDescending || cmp == OrderedSame);
}

#pragma mark -

const Number coconut::operator +  (const Number & left, const Number & right)
{ Number n; n.___M_impl = left.___M_impl.by_adding(right.___M_impl); return n; }

const Number coconut::operator -  (const Number & left, const Number & right)
{ Number n; n.___M_impl = left.___M_impl.by_subtracting(right.___M_impl); return n; }

const Number coconut::operator *  (const Number & left, const Number & right)
{ Number n; n.___M_impl = left.___M_impl.by_multiplying(right.___M_impl); return n; }

const Number coconut::operator /  (const Number & left, const Number & right)
{ Number n; n.___M_impl = left.___M_impl.by_dividing(right.___M_impl); return n; }

#pragma mark -

const Number & coconut::operator ++ (Number & left)
{ left.___M_impl = left.___M_impl.by_incrementing(); return left; }

const Number & coconut::operator ++ (Number & left, int n)
{ left.___M_impl = left.___M_impl.by_incrementing(n); return left; }

const Number & coconut::operator -- (Number & left)
{ left.___M_impl = left.___M_impl.by_decrementing(); return left; }

const Number & coconut::operator -- (Number & left, int n)
{ left.___M_impl = left.___M_impl.by_decrementing(n); return left; }

/* EOF */