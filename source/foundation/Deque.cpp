//
// Deque.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Deque.hpp>
#include <coconut/foundation/Range.hpp>

using namespace coconut;

Deque::Deque() :
	Object(DequeClass),
	___M_impl()
{ /* NOP */ }

Deque::Deque(const Deque & deq) :
	Object(DequeClass),
	___M_impl(deq.___M_impl)
{ /* NOP */ }

Deque::Deque(Deque && deq) noexcept :
	Object(DequeClass),
	___M_impl(std::move(deq.___M_impl))
{ /* NOP */ }

Deque::Deque(const std::initializer_list< Owning<Any> > & args) :
	Deque(args.begin(), args.end(), CopyNone)
{ /* NOP */ }

Deque::Deque(const std::initializer_list<Any *> & args) :
	Object(DequeClass),
	___M_impl()
{
	for (Any * item : args) {
		if (dynamic_cast<Any *>(item) != nullptr) { ___M_impl.push_back(item->kindCopy()); }
	}
}

Deque::~Deque()
{ /* NOP */ }

#pragma mark -

Owning<Any> Deque::copy() const
{ return ptr_create<Deque>(cbegin(), cend(), CopyKind); }

#pragma mark -

ComparisonResult Deque::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		if (size() < ref_cast<Deque>(ref).size()) {
			return OrderedAscending;
		} else if (size() > ref_cast<Deque>(ref).size()) {
			return OrderedDescending;
		} else if (
			std::equal(cbegin(), cend(), ref_cast<Deque>(ref).cbegin(), [] (const Owning<Any> & a, const Owning<Any> & b) -> bool
			{
				if (a && b) { return (a->compare(*b) == OrderedSame); } return false;
			})
		) {
			return OrderedSame;
		}
	}
	return OrderedDescending;
}

#pragma mark -

std::size_t Deque::size() const
{ return ___M_impl.size(); }

#pragma mark -

const Owning<Any> Deque::first() const
{ return ___M_impl.front(); }

const Owning<Any> Deque::last() const
{ return ___M_impl.back(); }

#pragma mark -

void Deque::addFirst(const Owning<Any> & obj)
{ if (obj) { ___M_impl.push_front(obj); } }

void Deque::addLast(const Owning<Any> & obj)
{ if (obj) { ___M_impl.push_back(obj); } }

#pragma mark -

void Deque::insert(const Owning<Any> & obj, std::size_t at_idx)
{ if (obj) { ___M_impl.insert(begin() + static_cast<difference_type>(at_idx), obj); } }

#pragma mark -

void Deque::remove(std::size_t index)
{ ___M_impl.erase(begin() + static_cast<difference_type>(index)); }

void Deque::remove(const Range & in_rg)
{
	std::size_t sz = size();
	if (sz) {
		std::size_t loc, len, max;
		Range src(0, sz);
		Range dest = src.intersectionRange(in_rg);
		
		loc = dest.location();
		len = dest.length();
		max = dest.maxRange();
		
		if (loc && len) {
			___M_impl.erase(
				begin() + static_cast<difference_type>(loc),
				begin() + static_cast<difference_type>(max)
			);
		}
	}
}

#pragma mark -

void Deque::removeFirst()
{ ___M_impl.pop_front(); }

void Deque::removeLast()
{ ___M_impl.pop_back(); }

void Deque::removeAll()
{ ___M_impl.clear(); }

#pragma mark -

Deque::iterator Deque::begin() { return ___M_impl.begin(); }
Deque::iterator Deque::end() { return ___M_impl.end(); }

Deque::const_iterator Deque::begin() const { return ___M_impl.begin(); }
Deque::const_iterator Deque::end() const { return ___M_impl.end(); }

Deque::const_iterator Deque::cbegin() const { return ___M_impl.cbegin(); }
Deque::const_iterator Deque::cend() const { return ___M_impl.cend(); }

Deque::reverse_iterator Deque::rbegin() { return ___M_impl.rbegin(); }
Deque::reverse_iterator Deque::rend() { return ___M_impl.rend(); }

Deque::const_reverse_iterator Deque::rbegin() const { return ___M_impl.rbegin(); }
Deque::const_reverse_iterator Deque::rend() const { return ___M_impl.rend(); }

Deque::const_reverse_iterator Deque::crbegin() const { return ___M_impl.crbegin(); }
Deque::const_reverse_iterator Deque::crend() const { return ___M_impl.crend(); }

/* EOF */