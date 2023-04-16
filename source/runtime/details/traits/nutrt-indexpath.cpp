//
// nutrt-indexpath.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-indexpath.hpp>
#include <coconut/runtime/details/nutrt-stream.hpp>

using namespace coconut::runtime;
using namespace coconut::runtime::traits;

indexpath::indexpath()
: ___M_indexes()
{ /* NOP */ }

indexpath::indexpath(const indexpath & idxpath)
: ___M_indexes(idxpath.cbegin(), idxpath.cend())
{ /* NOP */ }

indexpath::indexpath(indexpath && idxpath) noexcept
: ___M_indexes(std::move(idxpath.___M_indexes))
{ /* NOP */ }

indexpath::indexpath(std::size_t index)
: ___M_indexes()
{ ___M_indexes.push_back(index); }

indexpath::indexpath(std::size_t * indexes, std::size_t length)
: ___M_indexes()
{
	for (std::size_t i = 0; i < length; i++) {
		___M_indexes.push_back(indexes[i]);
	}
}

indexpath::indexpath(const std::vector<std::size_t> & indexes)
: ___M_indexes(indexes.cbegin(), indexes.cend())
{ /* NOP */ }

indexpath::indexpath(const std::vector<std::size_t> & indexes, std::size_t numitems)
: ___M_indexes()
{
	std::size_t length = numitems;
	if (length > indexes.size()) {
		length = indexes.size();
	}
	for (std::size_t i = 0; i < length; i++) {
		___M_indexes.push_back(indexes[i]);
	}
}

indexpath::~indexpath()
{ /* NOP */ }

#pragma mark -

indexpath & indexpath::operator = (const indexpath & idxpath)
{
	if (this == &idxpath) {
		return *this;
	}
	___M_indexes.assign(idxpath.___M_indexes.cbegin(), idxpath.___M_indexes.cend());
	return *this;
}

#pragma mark -

int indexpath::compare(const indexpath & other_idxpath) const
{
	if (this == &other_idxpath) {
		return cmp_same;
	}
	
	if (___M_indexes.size() < other_idxpath.___M_indexes.size()) {
		return cmp_ascending;
	} else if (___M_indexes.size() > other_idxpath.___M_indexes.size()) {
		return cmp_descending;
	} else if (std::equal(
		___M_indexes.begin(),
		___M_indexes.end(),
		other_idxpath.___M_indexes.begin()
	)) {
		return cmp_same;
	}
	return cmp_descending;
}

#pragma mark -

std::size_t indexpath::index_at(std::size_t position) const
{
	if (___M_indexes.size() && position < ___M_indexes.size()) {
		return ___M_indexes[position];
	}
	return NotFound;
}

#pragma mark -

const std::vector<std::size_t> indexpath::indexes() const
{ return ___M_indexes; }

const std::size_t * indexpath::raw() const
{ return ___M_indexes.data(); }

#pragma mark -

indexpath indexpath::by_adding(std::size_t index) const
{
	std::vector<std::size_t> buf;
	if (___M_indexes.size()) {
		buf.assign(___M_indexes.cbegin(), ___M_indexes.cend());
	}
	buf.push_back(index);
	indexpath idxpath(buf.cbegin(), buf.cend());
	return idxpath;
}

indexpath indexpath::by_removing_last() const
{
	std::vector<std::size_t> buf;
	if (___M_indexes.size()) {
		buf.assign(___M_indexes.cbegin(), ___M_indexes.cend());
		buf.pop_back();
	}
	indexpath idxpath(buf.cbegin(), buf.cend());
	return idxpath;
}

#pragma mark -

std::size_t indexpath::size() const
{ return ___M_indexes.size(); }

#pragma mark -

std::string indexpath::to_string() const
{
	std::ostringstream oss;
	if (___M_indexes.size()) {
		std::copy(___M_indexes.cbegin(), ___M_indexes.cend() -1, std::ostream_iterator<std::size_t>(oss, ", "));
		oss << ___M_indexes.back();
	}
	return "[" + oss.str() + "]";
}

std::size_t indexpath::hash_code() const
{ return std::hash<std::string>()(to_string()); }

#pragma mark -

indexpath::iterator indexpath::begin() { return ___M_indexes.begin(); }
indexpath::iterator indexpath::end() { return ___M_indexes.end(); }

indexpath::const_iterator indexpath::begin() const { return ___M_indexes.begin(); }
indexpath::const_iterator indexpath::end() const { return ___M_indexes.end(); }

indexpath::const_iterator indexpath::cbegin() const { return ___M_indexes.cbegin(); }
indexpath::const_iterator indexpath::cend() const { return ___M_indexes.cend(); }

indexpath::reverse_iterator indexpath::rbegin() { return ___M_indexes.rbegin(); }
indexpath::reverse_iterator indexpath::rend() { return ___M_indexes.rend(); }

indexpath::const_reverse_iterator indexpath::rbegin() const { return ___M_indexes.rbegin(); }
indexpath::const_reverse_iterator indexpath::rend() const { return ___M_indexes.rend(); }

indexpath::const_reverse_iterator indexpath::crbegin() const { return ___M_indexes.crbegin(); }
indexpath::const_reverse_iterator indexpath::crend() const { return ___M_indexes.crend(); }

/* EOF */