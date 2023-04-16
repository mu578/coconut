//
// Printifier.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/Types.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_PRINTIFIER_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_PRINTIFIER_HPP

namespace coconut
{
	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			!std::is_same<TypeT, String>::value &&
			!std::is_same<TypeT, Date>::value &&
			!std::is_same<TypeT, Data>::value &&
			!std::is_same<TypeT, Path>::value &&
			!std::is_same<TypeT, MutablePath>::value &&
			!std::is_same<TypeT, URL>::value &&
			!std::is_same<TypeT, Number>::value &&
			!std::is_same<TypeT, Timestamp>::value &&
			!std::is_same<TypeT, Array>::value &&
			!std::is_same<TypeT, MutableArray>::value &&
			!std::is_same<TypeT, Deque>::value &&
			!std::is_same<TypeT, OrderedSet>::value &&
			!std::is_same<TypeT, MutableOrderedSet>::value &&
			!std::is_same<TypeT, Set>::value &&
			!std::is_same<TypeT, MutableSet>::value &&
			!std::is_same<TypeT, Dictionary>::value &&
			!std::is_same<TypeT, MutableDictionary>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const TypeT & r)
		-> std::ostream &
	{
		using ::coconut::operator<<;

		if (r.isKindOf(StringClass)) {
			os << ref_cast<String>(r);
		} else if (r.isKindOf(NumberClass)) {
			os << ref_cast<Number>(r);
		} else if (r.isKindOf(PathClass)) {
			os << ref_cast<Path>(r);
		} else if (r.isKindOf(URLClass)) {
			os << ref_cast<URL>(r);
		} else if (r.isKindOf(DateClass)) {
			os << ref_cast<Date>(r);
		} else if (r.isKindOf(ArrayClass)) {
			os << ref_cast<Array>(r);
		} else if (r.isKindOf(DequeClass)) {
			os << ref_cast<Deque>(r);
		} else if (r.isKindOf(OrderedSetClass)) {
			os << ref_cast<OrderedSet>(r);
		} else if (r.isKindOf(SetClass)) {
			os << ref_cast<Set>(r);
		} else if (r.isKindOf(DictionaryClass)) {
			os << ref_cast<Dictionary>(r);
		} else if (r.isKindOf(DataClass)) {
			os << ref_cast<Data>(r);
		} else {
			os << r.stringValue();
		}
		return os;
	}
		
	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			!std::is_same<TypeT, String>::value &&
			!std::is_same<TypeT, Date>::value &&
			!std::is_same<TypeT, Data>::value &&
			!std::is_same<TypeT, Path>::value &&
			!std::is_same<TypeT, MutablePath>::value &&
			!std::is_same<TypeT, URL>::value &&
			!std::is_same<TypeT, Number>::value &&
			!std::is_same<TypeT, Timestamp>::value &&
			!std::is_same<TypeT, Array>::value &&
			!std::is_same<TypeT, MutableArray>::value &&
			!std::is_same<TypeT, Deque>::value &&
			!std::is_same<TypeT, OrderedSet>::value &&
			!std::is_same<TypeT, MutableOrderedSet>::value &&
			!std::is_same<TypeT, Set>::value &&
			!std::is_same<TypeT, MutableSet>::value &&
			!std::is_same<TypeT, Dictionary>::value &&
			!std::is_same<TypeT, MutableDictionary>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, Owning<TypeT> const & r)
		-> std::ostream &
	{ using ::coconut::operator<<; if (r) { os << *r; } return os; }
	
	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			(std::is_same<TypeT, String>::value ||
			std::is_same<TypeT, Path>::value ||
			std::is_same<TypeT, MutablePath>::value ||
			std::is_same<TypeT, URL>::value ||
			std::is_same<TypeT, Date>::value)
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const TypeT & r)
		-> std::ostream &
	{ using ::coconut::operator<<; os << '"' << r.stringValue() << '"'; return os; }

	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			(std::is_same<TypeT, String>::value ||
			std::is_same<TypeT, Path>::value ||
			std::is_same<TypeT, MutablePath>::value ||
			std::is_same<TypeT, URL>::value ||
			std::is_same<TypeT, Date>::value)
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, Owning<TypeT> const & r)
		-> std::ostream &
	{ using ::coconut::operator<<; if (r) { os << *r; } return os; }

	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			std::is_same<TypeT, Data>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const TypeT & r)
		-> std::ostream &
	{
		using ::coconut::operator<<;
		
		runtime::hexrep::format_option opt;
		
		opt.u_start = u8"<";
		opt.u_stop = u8">";
		opt.u_byte = u8"";
		opt.u_word = u8" ";
		opt.u_dword = u8"";
		opt.u_max = 24;
		opt.u_row = false;

		runtime::hexrep::format
		(
			os,
			ref_cast<Data>(r).cbegin(),
			ref_cast<Data>(r).cend(),
			&opt
		);
		
		return os;
	}
	
	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			std::is_same<TypeT, Data>::value
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, Owning<TypeT> const & r)
		-> std::ostream &
	{ using ::coconut::operator<<; if (r) { os << *r; } return os; }
	
	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			(std::is_same<TypeT, Number>::value ||
			std::is_same<TypeT, Timestamp>::value)
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const TypeT & r)
		-> std::ostream &
	{ using ::coconut::operator<<; os << r.stringValue(); return os; }

	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			(std::is_same<TypeT, Number>::value ||
			std::is_same<TypeT, Timestamp>::value)
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, Owning<TypeT> const & r)
		-> std::ostream &
	{ using ::coconut::operator<<; if (r) { os << *r; } return os; }
	
	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			(std::is_same<TypeT, Array>::value ||
			std::is_same<TypeT, MutableArray>::value ||
			std::is_same<TypeT, Deque>::value ||
			std::is_same<TypeT, OrderedSet>::value ||
			std::is_same<TypeT, MutableOrderedSet>::value ||
			std::is_same<TypeT, Set>::value ||
			std::is_same<TypeT, MutableSet>::value)
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const TypeT & r)
		-> std::ostream &
	{
		using ::coconut::operator<<;
		os << '[';
		for (auto it = r.cbegin(); it != r.cend(); ++it) {
			os << *it; if (std::next(it) != r.cend()) { os << ',' << ' '; }
		}
		os << ']';
		return os;
	}
		
	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			(std::is_same<TypeT, Array>::value ||
			std::is_same<TypeT, MutableArray>::value ||
			std::is_same<TypeT, Deque>::value ||
			std::is_same<TypeT, OrderedSet>::value ||
			std::is_same<TypeT, MutableOrderedSet>::value ||
			std::is_same<TypeT, Set>::value ||
			std::is_same<TypeT, MutableSet>::value)
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, Owning<TypeT> const & r)
		-> std::ostream &
	{ using ::coconut::operator<<; if (r) { os << *r; } return os; }

	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			(std::is_same<TypeT, Dictionary>::value ||
			std::is_same<TypeT, MutableDictionary>::value)
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, const TypeT & r)
		-> std::ostream &
	{
		using ::coconut::operator<<;
		os << '{';
		for (auto it = r.cbegin(); it != r.cend(); ++it) {
			os << (*it).first << ':' << ' ' << (*it).second; if (std::next(it) != r.cend()) { os << ',' << ' '; }
		}
		os << '}';
		return os;
	}
			
	template <typename TypeT,
		typename std::enable_if<
			std::is_base_of<Any, TypeT>::value &&
			(std::is_same<TypeT, Dictionary>::value ||
			std::is_same<TypeT, MutableDictionary>::value)
		>::type* = nullptr
	>
	inline auto operator << (std::ostream & os, Owning<TypeT> const & r)
		-> std::ostream &
	{ using ::coconut::operator<<; if (r) { os << *r; } return os; }
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_PRINTIFIER_HPP */

/* EOF */