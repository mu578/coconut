//
// IndexPath.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/IndexPath.hpp>

using namespace coconut;

IndexPath::IndexPath() :
	Object(IndexPathClass),
	___M_impl()
{ /* NOP */ }

IndexPath::IndexPath(const IndexPath & idxp) :
	Object(IndexPathClass),
	___M_impl(idxp.___M_impl)
{ /* NOP */ }

IndexPath::IndexPath(IndexPath && idxp) noexcept :
	Object(IndexPathClass),
	___M_impl(std::move(idxp.___M_impl))
{ /* NOP */ }

IndexPath::IndexPath(const std::initializer_list<std::size_t> & args) :
	Object(IndexPathClass),
	___M_impl(args.begin(), args.end())
{ /* NOP */ }

IndexPath::IndexPath(std::size_t index) :
	Object(IndexPathClass),
	___M_impl(index)
{ /* NOP */ }

IndexPath::~IndexPath()
{ /* NOP */ }

#pragma mark -

std::size_t IndexPath::hash() const
{ return ___M_impl.hash_code(); }

#pragma mark -

Owning<Any> IndexPath::copy() const
{ return ptr_create<IndexPath>(*this); }

#pragma mark -

ComparisonResult IndexPath::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return ___M_impl.compare(ref_cast<IndexPath>(ref).___M_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string IndexPath::stringValue() const
{ return ___M_impl.to_string(); }

#pragma mark -

std::size_t IndexPath::size() const
{ return ___M_impl.size(); }

#pragma mark -

std::size_t IndexPath::indexAtPosition(std::size_t node) const
{ return ___M_impl.index_at(node); }

#pragma mark -

const IndexPath IndexPath::indexPathByAddingIndex(std::size_t index) const
{
	IndexPath idxp;
	idxp.___M_impl = ___M_impl.by_adding(index);
	return idxp;
}

const IndexPath IndexPath::indexPathByRemovingLastIndex() const
{
	IndexPath idxp;
	idxp.___M_impl = ___M_impl.by_removing_last();
	return idxp;
}

#pragma mark -

bool IndexPath::getIndexes(std::vector<std::size_t> & indexes) const
{
	indexes.assign(___M_impl.cbegin(), ___M_impl.cend());
	return (indexes.size() > 0);
}

#pragma mark -

IndexPath::iterator IndexPath::begin() { return ___M_impl.begin(); }
IndexPath::iterator IndexPath::end() { return ___M_impl.end(); }

IndexPath::const_iterator IndexPath::begin() const { return ___M_impl.begin(); }
IndexPath::const_iterator IndexPath::end() const { return ___M_impl.end(); }

IndexPath::const_iterator IndexPath::cbegin() const { return ___M_impl.cbegin(); }
IndexPath::const_iterator IndexPath::cend() const { return ___M_impl.cend(); }

IndexPath::reverse_iterator IndexPath::rbegin() { return ___M_impl.rbegin(); }
IndexPath::reverse_iterator IndexPath::rend() { return ___M_impl.rend(); }

IndexPath::const_reverse_iterator IndexPath::rbegin() const { return ___M_impl.rbegin(); }
IndexPath::const_reverse_iterator IndexPath::rend() const { return ___M_impl.rend(); }

IndexPath::const_reverse_iterator IndexPath::crbegin() const { return ___M_impl.crbegin(); }
IndexPath::const_reverse_iterator IndexPath::crend() const { return ___M_impl.crend(); }

/* EOF */