//
// Number.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_NUMBER_HPP
#define COCONUT_FOUNDATION_NUMBER_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE Number COCONUT_FINAL : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Number, Object.Number)
		
	public:
		Number();
		Number(const Number & num);
		Number & operator = (const Number & num) = default;
		Number(Number && num) noexcept;
		Number(const float & value);
		Number(const double & value);
		Number(const long double & value);
		Number(const bool & value);
		Number(const char & value);
		Number(const short & value);
		Number(const int & value);
		Number(const long & value);
		Number(const long long & value);
		Number(const unsigned char & value);
		Number(const unsigned short & value);
		Number(const unsigned int & value);
		Number(const unsigned long & value);
		Number(const unsigned long long & value);
		virtual ~Number();
		
		virtual std::size_t hash() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual ComparisonResult compare(const Any & ref) const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::string stringValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual float floatValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual double doubleValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual long double longDoubleValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual bool boolValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual char charValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual short shortValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual int intValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual long longValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual long long longLongValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned char unsignedCharValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned short unsignedShortValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned int unsignedIntValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned long unsignedLongValue() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual unsigned long long unsignedLongLongValue() const
		COCONUT_FINAL_OVERRIDE;
	
	public:
		double realValue() const;
		std::int64_t integerValue() const;
		std::uint64_t unsignedIntegerValue() const;
	
	public:
		bool isUnsigned() const;
		bool isReal() const;
		
		NumberType type() const;
	
	private:
		friend const Number operator +  (const Number & left, const Number & right);
		friend const Number operator -  (const Number & left, const Number & right);
		friend const Number operator *  (const Number & left, const Number & right);
		friend const Number operator /  (const Number & left, const Number & right);
		
		friend const Number & operator ++ (Number & left);
		friend const Number & operator ++ (Number & left, int n);
		friend const Number & operator -- (Number & left);
		friend const Number & operator -- (Number & left, int n);
		
	private:
		typedef runtime::traits::numeric impl_trait;
	
	private:
		impl_trait ___M_impl;
	};
	
	bool operator == (const Number & left, const Number & right);
	bool operator != (const Number & left, const Number & right);
	bool operator <  (const Number & left, const Number & right);
	bool operator <= (const Number & left, const Number & right);
	bool operator >  (const Number & left, const Number & right);
	bool operator >= (const Number & left, const Number & right);
	
	const Number operator +  (const Number & left, const Number & right);
	const Number operator -  (const Number & left, const Number & right);
	const Number operator *  (const Number & left, const Number & right);
	const Number operator /  (const Number & left, const Number & right);
	
	const Number & operator ++ (Number & left);
	const Number & operator ++ (Number & left, int n);
	const Number & operator -- (Number & left);
	const Number & operator -- (Number & left, int n);
}

#endif /* !COCONUT_FOUNDATION_NUMBER_HPP */

/* EOF */