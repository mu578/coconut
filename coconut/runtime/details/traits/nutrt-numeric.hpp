//
// nutrt-numeric.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>

#ifndef COCONUT_RUNTIME_NUMERIC_HPP
#define COCONUT_RUNTIME_NUMERIC_HPP

namespace coconut
{ namespace runtime
{ namespace traits
{

/**
 * The numeric class offers a container as any C scalar (numeric) type.
 * Note that numeric class does preserve the type it is created with ;
 * except for arithmetic operations, the largest family container is used ;
 * thus, it does not guard against any overflows. The numeric class is
 * as lightweight as possible, meaning strongly optimized, no pointer
 * tagging-dirt twist.
 */
COCONUT_PRIVATE class COCONUT_VISIBLE numeric COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.numeric, numeric)
	
public:
	numeric();
	numeric(const numeric & num);
	numeric(const float & value);
	numeric(const double & value);
	numeric(const long double & value);
	numeric(const bool & value);
	numeric(const char & value);
	numeric(const short & value);
	numeric(const int & value);
	numeric(const long & value);
	numeric(const long long & value);
	numeric(const unsigned char & value);
	numeric(const unsigned short & value);
	numeric(const unsigned int & value);
	numeric(const unsigned long & value);
	numeric(const unsigned long long & value);
	~numeric();

public:
	numeric & operator = (const numeric & num);
	int compare(const numeric & other_num) const;

public:
	numeric by_adding(const numeric & other_num) const;
	numeric by_subtracting(const numeric & other_num) const;
	
	numeric by_dividing(const numeric & other_num) const;
	numeric by_multiplying(const numeric & other_num) const;
	
	numeric by_incrementing(int n = 0) const;
	numeric by_decrementing(int n = 0) const;
	
private:
	template <typename T>
	T get(void * no_param = nullptr) const
	{
		COCONUT_UNUSED(no_param);
		T result = 0;
		switch (___M_type)
		{
			case numeric_float :
				return weak_cast<T>(___M_val_float);
			case numeric_double :
				return weak_cast<T>(___M_val_double);
			case numeric_long_double :
				return weak_cast<T>(___M_val_long_double);
			case numeric_bool :
				return weak_cast<T>(___M_val_bool);
			case numeric_char :
				return weak_cast<T>(___M_val_char);
			case numeric_short :
				return weak_cast<T>(___M_val_short);
			case numeric_int :
				return weak_cast<T>(___M_val_int);
			case numeric_long :
				return weak_cast<T>(___M_val_long);
			case numeric_long_long :
				return weak_cast<T>(___M_val_long_long);
			case numeric_unsigned_char :
				return weak_cast<T>(___M_val_unsigned_char);
			case numeric_unsigned_short :
				return weak_cast<T>(___M_val_unsigned_short);
			case numeric_unsigned_int :
				return weak_cast<T>(___M_val_unsigned_int);
			case numeric_unsigned_long :
				return weak_cast<T>(___M_val_unsigned_long);
			case numeric_unsigned_long_long :
				return weak_cast<T>(___M_val_unsigned_long_long);
		}
		return result;
	}

public:
	float to_float() const;
	double to_double() const;
	long double to_long_double() const;
	
	bool to_bool() const;
	
	char to_char() const;
	short to_short() const;
	int to_int() const;
	long to_long() const;
	long long to_long_long() const;
	
	unsigned char to_unsigned_char() const;
	unsigned short to_unsigned_short() const;
	unsigned int to_unsigned_int() const;
	unsigned long to_unsigned_long() const;
	unsigned long long to_unsigned_long_long() const;
	
	std::string to_string() const;
	std::size_t hash_code() const;
	
	double to_real() const;
	std::int64_t to_integer() const;
	std::uint64_t to_unsigned_integer() const;
	
	bool is_signed() const;
	bool is_floating() const;
	
	std::uint16_t type() const;

private:
	/* private traits */
	
	using item_type = void;
	using this_type = numeric;
	
private:
	union
	{
		float ___M_val_float;
		double ___M_val_double;
		long double ___M_val_long_double;
		bool ___M_val_bool;
		
		char ___M_val_char;
		short ___M_val_short;
		int ___M_val_int;
		long ___M_val_long;
		long long ___M_val_long_long;
		
		unsigned char ___M_val_unsigned_char;
		unsigned short ___M_val_unsigned_short;
		unsigned int ___M_val_unsigned_int;
		unsigned long ___M_val_unsigned_long;
		unsigned long long ___M_val_unsigned_long_long;
	};
	
private:
	std::uint16_t ___M_type;
	bool ___M_signed;
	bool ___M_floating;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_NUMERIC_HPP */

/* EOF */