//
// nutrt-numeric.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-numeric.hpp>
#include <coconut/runtime/details/nutrt-algorithms.hpp>

using namespace coconut::runtime;
using namespace coconut::runtime::traits;

numeric::numeric()
{ ___M_type = numeric_zero; }

numeric::numeric(const numeric & num)
{
	switch (num.___M_type)
	{
		case numeric_float :
			___M_val_float = num.___M_val_float;
		break;
		case numeric_double :
			___M_val_double = num.___M_val_double;
		break;
		case numeric_long_double :
			___M_val_long_double = num.___M_val_long_double;
		break;
		case numeric_bool :
			___M_val_bool = num.___M_val_bool;
		break;
		case numeric_char :
			___M_val_char = num.___M_val_char;
		break;
		case numeric_short :
			___M_val_short = num.___M_val_short;
		break;
		case numeric_int :
			___M_val_int = num.___M_val_int;
		break;
		case numeric_long :
			___M_val_long = num.___M_val_long;
		break;
		case numeric_long_long :
			___M_val_long_long = num.___M_val_long_long;
		break;
		case numeric_unsigned_char :
			___M_val_unsigned_char = num.___M_val_unsigned_char;
		break;
		case numeric_unsigned_short :
			___M_val_unsigned_short = num.___M_val_unsigned_short;
		break;
		case numeric_unsigned_int :
			___M_val_unsigned_int = num.___M_val_unsigned_int;
		break;
		case numeric_unsigned_long :
			___M_val_unsigned_long = num.___M_val_unsigned_long;
		break;
		case numeric_unsigned_long_long :
			___M_val_unsigned_long_long = num.___M_val_unsigned_long_long;
		break;
	}
	___M_type = num.___M_type;
	___M_signed = num.___M_signed;
	___M_floating = num.___M_floating;
}

numeric::numeric(const float & value)
{
	___M_val_float = value;
	___M_type = numeric_float;
	___M_signed = true;
	___M_floating = true;
}

numeric::numeric(const double & value)
{
	___M_val_double = value;
	___M_type = numeric_double;
	___M_signed = true;
	___M_floating = true;
}

numeric::numeric(const long double & value)
{
	___M_val_long_double = value;
	___M_type = numeric_long_double;
	___M_signed = true;
	___M_floating = false;
}

numeric::numeric(const bool & value)
{
	___M_val_bool = value;
	___M_type = numeric_bool;
	___M_signed = false;
	___M_floating = false;
}

numeric::numeric(const char & value)
{
	___M_val_char = value;
	___M_type = numeric_char;
	___M_signed = true;
	___M_floating = false;
}

numeric::numeric(const short & value)
{
	___M_val_short = value;
	___M_type = numeric_short;
	___M_signed = true;
	___M_floating = false;
}

numeric::numeric(const int & value)
{
	___M_val_int = value;
	___M_type = numeric_int;
	___M_signed = true;
	___M_floating = false;
}

numeric::numeric(const long & value)
{
	___M_val_long = value;
	___M_type = numeric_long;
	___M_signed = true;
	___M_floating = false;
}

numeric::numeric(const long long & value)
{
	___M_val_long_long = value;
	___M_type = numeric_long_long;
	___M_signed = true;
	___M_floating = false;
}

numeric::numeric(const unsigned char & value)
{
	___M_val_unsigned_char = value;
	___M_type = numeric_unsigned_char;
	___M_signed = false;
	___M_floating = false;
}

numeric::numeric(const unsigned short & value)
{
	___M_val_unsigned_short = value;
	___M_type = numeric_unsigned_short;
	___M_signed = false;
	___M_floating = false;
}

numeric::numeric(const unsigned int & value)
{
	___M_val_unsigned_int = value;
	___M_type = numeric_unsigned_int;
	___M_signed = false;
	___M_floating = false;
}

numeric::numeric(const unsigned long & value)
{
	___M_val_unsigned_long = value;
	___M_type = numeric_unsigned_long;
	___M_signed = false;
	___M_floating = false;
}

numeric::numeric(const unsigned long long & value)
{
	___M_val_unsigned_long_long = value;
	___M_type = numeric_unsigned_long_long;
	___M_signed = false;
	___M_floating = false;
}

numeric::~numeric()
{ /* NOP */ }

#pragma mark -

numeric & numeric::operator = (const numeric & num)
{
	if (this == &num) {
		return *this;
	}
	switch (num.___M_type)
	{
		case numeric_float :
			___M_val_float = num.___M_val_float;
		break;
		case numeric_double :
			___M_val_double = num.___M_val_double;
		break;
		case numeric_long_double :
			___M_val_long_double = num.___M_val_long_double;
		break;
		case numeric_bool :
			___M_val_bool = num.___M_val_bool;
		break;
		case numeric_char :
			___M_val_char = num.___M_val_char;
		break;
		case numeric_short :
			___M_val_short = num.___M_val_short;
		break;
		case numeric_int :
			___M_val_int = num.___M_val_int;
		break;
		case numeric_long :
			___M_val_long = num.___M_val_long;
		break;
		case numeric_long_long :
			___M_val_long_long = num.___M_val_long_long;
		break;
		case numeric_unsigned_char :
			___M_val_unsigned_char = num.___M_val_unsigned_char;
		break;
		case numeric_unsigned_short :
			___M_val_unsigned_short = num.___M_val_unsigned_short;
		break;
		case numeric_unsigned_int :
			___M_val_unsigned_int = num.___M_val_unsigned_int;
		break;
		case numeric_unsigned_long :
			___M_val_unsigned_long = num.___M_val_unsigned_long;
		break;
		case numeric_unsigned_long_long :
			___M_val_unsigned_long_long = num.___M_val_unsigned_long_long;
		break;
	}
	___M_type = num.___M_type;
	___M_signed = num.___M_signed;
	___M_floating = num.___M_floating;
	
	return *this;
}

#pragma mark -

int numeric::compare(const numeric & other_num) const
{
	if (this == &other_num) {
		return cmp_same;
	}
	if (___M_signed) {
		if (___M_floating) {
			if (to_double() < other_num.to_double()) {
				return cmp_ascending;
			} else if (to_double() > other_num.to_double()) {
				return cmp_descending;
			}
			return cmp_same;
		} else {
			if (to_long_long() < other_num.to_long_long()) {
				return cmp_ascending;
			} else if (to_long_long() > other_num.to_long_long()) {
				return cmp_descending;
			}
			return cmp_same;
		}
	} else {
		if (to_unsigned_long_long() < other_num.to_unsigned_long_long()) {
			return cmp_ascending;
		} else if (to_unsigned_long_long() > other_num.to_unsigned_long_long()) {
			return cmp_descending;
		}
		return cmp_same;
	}
	return cmp_same;
}

#pragma mark -

numeric numeric::by_adding(const numeric & other_num) const
{
	if (___M_signed) {
		if (___M_floating || other_num.___M_floating) {
			return {to_double() + other_num.to_double()};
		}
		long long n = to_long_long();
		if (other_num.___M_signed) {
			n += other_num.to_long_long();
		} else {
			n += other_num.to_unsigned_long_long();
		}
		return {n};
	} else {
		unsigned long long n = to_unsigned_long_long();
		if (other_num.___M_signed) {
			n += other_num.to_long_long();
		} else {
			n += other_num.to_unsigned_long_long();
		}
		return {n};
	}
	return {};
}

numeric numeric::by_subtracting(const numeric & other_num) const
{
	if (___M_signed) {
		if (___M_floating || other_num.___M_floating) {
			return {to_double() - other_num.to_double()};
		}
		long long n = to_long_long();
		if (other_num.___M_signed) {
			n -= other_num.to_long_long();
		} else {
			n -= other_num.to_unsigned_long_long();
		}
		return {n};
	} else {
		unsigned long long n = to_unsigned_long_long();
		if (other_num.___M_signed) {
			n -= other_num.to_long_long();
		} else {
			n -= other_num.to_unsigned_long_long();
		}
		return {n};
	}
	return {};
}

numeric numeric::by_dividing(const numeric & other_num) const
{
	if (___M_signed) {
		if (___M_floating || other_num.___M_floating) {
			return {to_double() / other_num.to_double()};
		}
		long long n = to_long_long();
		if (other_num.___M_signed) {
			n /= other_num.to_long_long();
		} else {
			n /= other_num.to_unsigned_long_long();
		}
		return {n};
	} else {
		unsigned long long n = to_unsigned_long_long();
		if (other_num.___M_signed) {
			n /= other_num.to_long_long();
		} else {
			n /= other_num.to_unsigned_long_long();
		}
		return {n};
	}
	return {};
}

numeric numeric::by_multiplying(const numeric & other_num) const
{
	if (___M_signed) {
		if (___M_floating || other_num.___M_floating) {
			return {to_double() * other_num.to_double()};
		}
		long long n = to_long_long();
		if (other_num.___M_signed) {
			n *= other_num.to_long_long();
		} else {
			n *= other_num.to_unsigned_long_long();
		}
		return {n};
	} else {
		unsigned long long n = to_unsigned_long_long();
		if (other_num.___M_signed) {
			n *= other_num.to_long_long();
		} else {
			n *= other_num.to_unsigned_long_long();
		}
		return {n};
	}
	return {};
}

numeric numeric::by_incrementing(int n) const
{
	if (n == 0) { n++; }
	if (___M_signed) {
		if (___M_floating) {
			return {to_double() + n};
		}
		return {to_long_long() + n};
	}
	return {to_unsigned_long_long() + n};
}

numeric numeric::by_decrementing(int n) const
{
	if (n == 0) { n++; }
	if (___M_signed) {
		if (___M_floating) {
			return {to_double() - n};
		}
		return {to_long_long() - n};
	}
	return {to_unsigned_long_long() - n};
}

#pragma mark -

float numeric::to_float() const
{ return get<float>(); }

double numeric::to_double() const
{ return get<double>(); }

long double numeric::to_long_double() const
{ return get<long double>(); }

#pragma mark -

bool numeric::to_bool() const
{
	if (___M_type == numeric_bool) {
		return get<bool>();
	}
	if (___M_signed) {
		if (___M_floating) {
			return get<double>() > 0.0 ? true : false;
		}
		return get<long long>() > 0 ? true : false;
	}
	return get<unsigned long long>() > 0 ? true : false;
}

#pragma mark -

char numeric::to_char() const
{ return get<char>(); }

short numeric::to_short() const
{ return get<short>(); }

int numeric::to_int() const
{ return get<int>(); }

long numeric::to_long() const
{ return get<long>(); }

long long numeric::to_long_long() const
{ return get<long long>(); }

#pragma mark -

unsigned char numeric::to_unsigned_char() const
{ return get<unsigned char>(); }

unsigned short numeric::to_unsigned_short() const
{ return get<unsigned short>(); }

unsigned int numeric::to_unsigned_int() const
{ return get<unsigned int>(); }

unsigned long numeric::to_unsigned_long() const
{ return get<unsigned long>(); }

unsigned long long numeric::to_unsigned_long_long() const
{ return get<unsigned long long>(); }

#pragma mark -

std::string numeric::to_string() const
{
	switch (___M_type)
	{
		case numeric_float :
			return algorithms::to_string<std::string::value_type>(___M_val_float, 6);
		case numeric_double :
			return algorithms::to_string<std::string::value_type>(___M_val_double, 24);
		case numeric_long_double :
			return algorithms::to_string<std::string::value_type>(___M_val_long_double, 36);
		case numeric_bool :
			return algorithms::to_string<std::string::value_type>(___M_val_bool);
		case numeric_char :
			return algorithms::to_string<std::string::value_type>(___M_val_char);
		case numeric_short :
			return algorithms::to_string<std::string::value_type>(___M_val_short);
		case numeric_int :
			return algorithms::to_string<std::string::value_type>(___M_val_int);
		case numeric_long :
			return algorithms::to_string<std::string::value_type>(___M_val_long);
		case numeric_long_long :
			return algorithms::to_string<std::string::value_type>(___M_val_long_long);
		case numeric_unsigned_char :
			return algorithms::to_string<std::string::value_type>(___M_val_unsigned_char);
		case numeric_unsigned_short :
			return algorithms::to_string<std::string::value_type>(___M_val_unsigned_short);
		case numeric_unsigned_int :
			return algorithms::to_string<std::string::value_type>(___M_val_unsigned_int);
		case numeric_unsigned_long :
			return algorithms::to_string<std::string::value_type>(___M_val_unsigned_long);
		case numeric_unsigned_long_long :
			return algorithms::to_string<std::string::value_type>(___M_val_unsigned_long_long);
	}
	return u8"0";
}

std::size_t numeric::hash_code() const
{
	if (___M_signed) {
		if (___M_floating) {
			return std::hash<double>()(to_double() + static_cast<double>(___M_type));
		}
		return std::hash<long long>()(to_long_long() + static_cast<long long>(___M_type));
	}
	return std::hash<unsigned long long>()(to_long_long() + static_cast<unsigned long long>(___M_type));
}

#pragma mark -

double numeric::to_real() const
{ return to_double(); }

std::int64_t numeric::to_integer() const
{
#if COCONUT_LONG_AND_PTR_AS_64
	return to_long();
#else
	return to_long_long();
#endif
}

std::uint64_t numeric::to_unsigned_integer() const
{
#if COCONUT_LONG_AND_PTR_AS_64
	return to_unsigned_long();
#else
	return to_unsigned_long_long();
#endif
}

#pragma mark -

bool numeric::is_signed() const { return ___M_signed; };
bool numeric::is_floating() const { return ___M_floating; };

#pragma mark -

std::uint16_t numeric::type() const { return ___M_type; };

/* EOF */