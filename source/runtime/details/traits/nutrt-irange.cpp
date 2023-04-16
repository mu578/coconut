//
// nutrt-irange.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-irange.hpp>
#include <coconut/runtime/details/nutrt-algorithms.hpp>

using namespace coconut::runtime;
using namespace coconut::runtime::traits;

irange::irange()
: ___M_loc(0)
, ___M_len(0)
{ /* NOP */ }

irange::irange(const irange & rg)
: ___M_loc(rg.___M_loc)
, ___M_len(rg.___M_len)
{ /* NOP */ }

irange::irange(irange && rg) noexcept
: ___M_loc(rg.___M_loc)
, ___M_len(rg.___M_len)
{ /* NOP */ }

irange::irange(const std::string & rg_string)
: ___M_loc(0)
, ___M_len(0)
{
	try {
		std::regex regex
		{
			R"(\{\"\#\{range\}\": \{\"location\": ([0-9]+), \"length\": ([0-9]+)\}\})",
			std::regex::icase
		};
		std::smatch match;
		std::ssub_match sub_match;
		if (std::regex_match(rg_string, match, regex)) {
			if (match.size() == 3) {
				sub_match = match[1];
				___M_loc = algorithms::to_numeric<std::size_t>(sub_match.str());
				sub_match = match[2];
				___M_len = algorithms::to_numeric<std::size_t>(sub_match.str());
			}
		}
	}
	catch (std::regex_error e) { /* NOP */ }
}

irange::irange(std::size_t location, std::size_t length)
: ___M_loc(location)
, ___M_len(length)
{ /* NOP */ }

irange::~irange()
{ /* NOP */ }

#pragma mark -

irange & irange::operator = (const irange & rg)
{
	if (this == &rg) {
		return *this;
	}
	___M_loc = rg.___M_loc;
	___M_len = rg.___M_len;
	
	return *this;
}

int irange::compare(const irange & other_rg) const
{
	if (this == &other_rg) {
		return cmp_same;
	} else if (___M_loc == other_rg.___M_loc && ___M_len == other_rg.___M_len) {
		return cmp_same;
	} else if (max() < other_rg.max()) {
		return cmp_ascending;
	}
	return cmp_descending; 
}

std::string irange::to_string() const
{
	return algorithms::format
	(
		u8"{\"#{range}\": {\"location\": %" PRIu64 ", \"length\": %" PRIu64 "}}}",
		___M_loc,
		___M_len
	 );
}

#pragma mark -

std::size_t irange::location() const
{ return ___M_loc; }

std::size_t irange::length() const
{ return ___M_len; }

void irange::set_location(std::size_t location)
{ ___M_loc = location; }

void irange::set_length(std::size_t length)
{ ___M_len = length; }

#pragma mark -

bool irange::iszero() const
{ return (___M_loc == 0 && ___M_len == 0); }

std::size_t irange::max() const
{ return ___M_loc + ___M_len; }

#pragma mark -

bool irange::in(std::size_t location) const
{ return (location >= ___M_loc && location < (___M_loc + ___M_len)); }

const irange irange::intxn(const irange & other_rg) const
{
	std::size_t mininum = std::min(max(), other_rg.max());
	std::size_t loc = std::max(location(), other_rg.location());
	return (mininum < loc) ? irange(0, 0) : irange(loc, mininum - loc);

/*
	irange intxn;
	size_t new_loc, new_len;
	
	if (max() < other_rg.location() || other_rg.max() < location()) {
		return intxn;
	}
	
	new_loc = std::max(location(), other_rg.location());
	new_len = std::min(max(), other_rg.max()) - intxn.location();
	
	intxn.set_location(new_loc);
	intxn.set_length(new_len);
	
	return intxn;
*/
}

const irange irange::merge(const irange & other_rg) const
{
	std::size_t maximum = std::max(max(), other_rg.max());
	std::size_t loc = std::min(location(), other_rg.location());
	return irange(loc, maximum - loc);

/*
	irange uni;
	size_t new_loc, new_len;
	
	new_loc = std::min(location(), other_rg.location());
	new_len = std::max(max(), other_rg.max());
	
	uni.set_location(new_loc);
	uni.set_length(new_len);
	
	return uni;
*/
}

#pragma mark -

irange::iterator irange::begin() { return ___M_loc; }
irange::iterator irange::end() { return ___M_loc + ___M_len; }

irange::const_iterator irange::begin() const { return ___M_loc; }
irange::const_iterator irange::end() const { return ___M_loc + ___M_len; }

irange::const_iterator irange::cbegin() const { return ___M_loc; }
irange::const_iterator irange::cend() const { return ___M_loc + ___M_len; }

irange::reverse_iterator irange::rbegin() { return ___M_loc + ___M_len; }
irange::reverse_iterator irange::rend() { return ___M_loc; }

irange::const_reverse_iterator irange::rbegin() const { return ___M_loc + ___M_len; }
irange::const_reverse_iterator irange::rend() const { return ___M_loc; }

irange::const_reverse_iterator irange::crbegin() const { return ___M_loc + ___M_len; }
irange::const_reverse_iterator irange::crend() const { return ___M_loc; }

/* EOF */