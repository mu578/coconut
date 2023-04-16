//
// nutrt-indexset.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-indexset.hpp>
#include <coconut/runtime/details/traits/nutrt-irange.hpp>

using namespace coconut::runtime;
using namespace coconut::runtime::traits;

indexset::indexset()
: ___M_len(0)
, ___M_ranges()
{ ___M_ranges.push_back(irange(0, 0)); }

indexset::indexset(const indexset & idxset)
: ___M_len(idxset.___M_len)
, ___M_ranges(idxset.___M_ranges.cbegin(), idxset.___M_ranges.cend())
{ /* NOP */ }

indexset::indexset(const irange & rg)
: ___M_len(0)
, ___M_ranges()
{
	___M_len = rg.length() == 0 ? 0 : 1;
	___M_ranges.push_back(rg);
}

indexset::indexset(std::size_t loc, std::size_t len)
: ___M_len(0)
, ___M_ranges()
{
	___M_len = len == 0 ? 0 : 1;
	___M_ranges.push_back(irange(loc, len));
}

indexset::indexset(std::size_t idx)
: ___M_len(1)
, ___M_ranges()
{
	___M_ranges.push_back(irange(idx, ___M_len));
}

indexset::~indexset()
{ /* NOP */ }

#pragma mark -

std::size_t indexset::pos_greater_eq_loc(const std::vector<irange> & rgs, std::size_t location)
{
	std::vector<irange>::const_iterator it;
	for (it = rgs.cbegin(); it != rgs.cend(); ++it) {
		std::size_t idx = static_cast<std::size_t>(
			std::distance(rgs.cbegin(), it)
		);
		if (location < rgs[idx].max()) {
			return idx;
		}
	}
	return NotFound;
}

std::size_t indexset::pos_greater_less_loc(const std::vector<irange> & rgs, std::size_t location)
{
	std::vector<irange>::const_reverse_iterator it;
	for (it = rgs.crbegin(); it != rgs.crend(); ++it) {
		std::size_t idx = static_cast<std::size_t>(
			std::distance(it, rgs.crend() -1)
		);
		if (rgs[idx].location() <= location) {
			return idx;
		}
	}
	return NotFound;
}

void indexset::remove_range_at_pos(std::vector<irange> & rgs, std::size_t position)
{
	rgs.erase(rgs.begin() + static_cast<difference_type>(position));
}

void indexset::insert_range_at_pos(std::vector<irange> & rgs, const irange & rg, std::size_t position)
{
	rgs.insert(rgs.begin() + static_cast<difference_type>(position), rg);
}

std::size_t indexset::find_pos_for_index(const std::vector<irange> & rgs, std::size_t index)
{
	std::size_t cnt = rgs.size();
	std::size_t end = cnt;
	std::size_t beg = 0;
	std::size_t pos = 0;
	for (pos = (end / 2); end != beg; pos = ((end + beg) / 2)) {
		if (index < rgs[pos].location()) {
			end = pos;
		} else if (index > rgs[pos].max()) {
			beg = pos + 1;
		} else {
			break;
		}
	}
	while (pos < cnt && index >= rgs[pos].max()) {
		pos++;
	}
	return pos;
}

#pragma mark -

indexset & indexset::operator = (const indexset & idxset)
{
	if (this == &idxset) {
		return *this;
	}
	___M_ranges.assign(idxset.___M_ranges.cbegin(), idxset.___M_ranges.cend());
	return *this;
}

#pragma mark -

int indexset::compare(const indexset & other_idxset) const
{
	if (this == &other_idxset) {
		return cmp_same;
	} else if (___M_len < other_idxset.___M_len) {
		return cmp_ascending;
	} else if (___M_len > other_idxset.___M_len) {
		return cmp_descending;
	}
	
	for (std::size_t i = 0 ; i < ___M_len ; i++) {
		int cmp = ___M_ranges[i].compare(other_idxset.___M_ranges[i]);
		if (cmp != cmp_same) {
			return cmp;
		}
	}
	return cmp_same;
}

#pragma mark -

std::string indexset::to_string() const
{ return u8""; }

#pragma mark -

std::size_t indexset::count() const
{
	std::size_t count = 0;
	for (std::size_t i = 0 ; i < ___M_len ; i++) {
		count += ___M_ranges[i].length();
	}
	return count;
}

std::size_t indexset::count_in(const irange & rg) const
{
	std::size_t count = 0;
	for (std::size_t i = 0 ; i < ___M_len ; i++) {
		count += ___M_ranges[i].intxn(rg).length();
	}
	return count;
}

std::size_t indexset::count_in(std::size_t loc, std::size_t len) const
{ return count_in(irange(loc, len)); }

#pragma mark -

bool indexset::contains(const indexset & idxset) const
{ return false; }

bool indexset::contains(const irange & rg) const
{ return false; }

bool indexset::contains(std::size_t loc, std::size_t len) const
{ return false; }

bool indexset::contains(std::size_t idx) const
{ return false; }

#pragma mark -

std::size_t indexset::first_index() const
{ return 0; }

std::size_t indexset::last_index() const
{ return 0; }

#pragma mark -

std::size_t indexset::greater(std::size_t idx) const
{ return 0; }

std::size_t indexset::greater_equal(std::size_t idx) const
{ return 0; }

std::size_t indexset::less(std::size_t idx) const
{ return 0; }

std::size_t indexset::less_equal(std::size_t idx) const
{ return 0; }

#pragma mark -

bool indexset::intersects(const irange & rg) const
{ return false; }

bool indexset::intersects(std::size_t loc, std::size_t len) const
{ return false; }

#pragma mark -

void indexset::add(const indexset & idxset)
{ /* NOP */ }

void indexset::add(const irange & rg)
{ /* NOP */ }

void indexset::add(std::size_t loc, std::size_t len)
{ /* NOP */ }

void indexset::add(std::size_t idx)
{ /* NOP */ }

#pragma mark -

void indexset::remove()
{ /* NOP */ }

void indexset::remove(const indexset & idxset)
{ /* NOP */ }

void indexset::remove(const irange & rg)
{ /* NOP */ }

void indexset::remove(std::size_t loc, std::size_t len)
{ /* NOP */ }

void indexset::remove(std::size_t idx)
{ /* NOP */ }

/* EOF */