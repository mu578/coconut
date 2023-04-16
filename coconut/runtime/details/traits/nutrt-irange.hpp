//
// nutrt-irange.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>
#include <coconut/runtime/details/nutrt-iterators.hpp>
#include <coconut/runtime/details/nutrt-allocators.hpp>

#ifndef COCONUT_RUNTIME_IRANGE_HPP
#define COCONUT_RUNTIME_IRANGE_HPP

namespace coconut
{ namespace runtime
{ namespace traits
{

COCONUT_PRIVATE class COCONUT_VISIBLE irange COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.irange, irange)
	
public:
	irange();
	irange(const irange & rg);
	irange(irange && rg) noexcept;
	irange(const std::string & rg_string);
	irange(std::size_t location, std::size_t length);
	~irange();

public:
	irange & operator = (const irange & rg);
	int compare(const irange & other_rg) const;
	
	std::size_t location() const;
	std::size_t length() const;
	
	void set_location(std::size_t location);
	void set_length(std::size_t length);
	
	bool iszero() const;
	std::size_t max() const;
	
	bool in(std::size_t location) const;
	const irange intxn(const irange & other_rg) const;
	const irange merge(const irange & other_rg) const;
	
	std::string to_string() const;

	
private:
	/* private traits */
	
	using item_type = std::size_t;
	using this_type = irange;
	
	using iter_type = iterators::integer_facet<
		item_type
		, this_type
	>;
	
	using const_iter_type = iterators::const_integer_facet<
		item_type
		, this_type
	>;
	
	using iter_reverse_type = iterators::integer_reverse_facet<
		item_type
		, this_type
	>;
	
	
	using const_iter_reverse_type = iterators::const_integer_reverse_facet<
		item_type
		, this_type
	>;

public:
	/* type_traits */
	
	typedef iter_type iterator;
	typedef const_iter_type const_iterator;
	
	typedef iter_reverse_type reverse_iterator;
	typedef const_iter_reverse_type const_reverse_iterator;
	
	typedef iter_type::value_type value_type;
	typedef iter_type::size_type size_type;
	typedef iter_type::difference_type difference_type;
	
	typedef iter_type::reference reference;
	typedef iter_type::const_reference const_reference;
	typedef iter_type::pointer pointer;
	typedef iter_type::const_pointer const_pointer;
	
	typedef allocators::builtins<this_type> allocator_type;

public:
	/* type_iterator */
	
	iterator begin();
	iterator end();
	
	const_iterator begin() const;
	const_iterator end() const;
	
	const_iterator cbegin() const;
	const_iterator cend() const;
	
	reverse_iterator rbegin();
	reverse_iterator rend();
	
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;
	
private:
	std::size_t ___M_loc;
	std::size_t ___M_len;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_IRANGE_HPP */

/* EOF */