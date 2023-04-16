//
// SortDescriptor.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/SortDescriptor.hpp>
#include <coconut/foundation/None.hpp>
#include <coconut/foundation/Number.hpp>
#include <coconut/foundation/String.hpp>

using namespace coconut;

SortDescriptor::SortDescriptor() :
	Object(SortDescriptorClass),
	___M_impl{ u8"<none>", u8"<none>", true }
{ /* NOP */ }

SortDescriptor::SortDescriptor(const SortDescriptor & sdr) :
	Object(SortDescriptorClass),
	___M_impl(sdr.___M_impl)
{ /* NOP */ }

SortDescriptor::SortDescriptor(SortDescriptor && sdr) noexcept :
	Object(SortDescriptorClass),
	___M_impl(std::move(sdr.___M_impl))
{ /* NOP */ }

SortDescriptor::SortDescriptor(const String & key, bool isasc) :
	Object(SortDescriptorClass),
	___M_impl{ key.stringValue(), u8"@compare:", isasc }
{ /* NOP */ }

SortDescriptor::SortDescriptor(const String & key, const String & selkey, bool isasc) :
	Object(SortDescriptorClass),
	___M_impl{ key.stringValue(), selkey.stringValue(), isasc }
{ /* NOP */ }

SortDescriptor::~SortDescriptor()
{ /* NOP */ }

#pragma mark -

Owning<Any> SortDescriptor::copy() const
{ return ptr_create<SortDescriptor>(*this); }

#pragma mark -

ComparisonResult SortDescriptor::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		if (std::get<0>(___M_impl) == std::get<0>(ref_cast<SortDescriptor>(ref).___M_impl) &&
			std::get<1>(___M_impl) == std::get<1>(ref_cast<SortDescriptor>(ref).___M_impl) &&
			std::get<2>(___M_impl) == std::get<2>(ref_cast<SortDescriptor>(ref).___M_impl)
		) { return OrderedSame; }
	}
	return OrderedDescending;
}

#pragma mark -

ComparisonResult SortDescriptor::compareObject(const Any & a, const Any & b) const
{
	Owning<Any> aa = a.valueForKeyPath(std::get<0>(___M_impl));
	Owning<Any> bb = b.valueForKeyPath(std::get<0>(___M_impl));
	if (aa && bb) {
		if (std::get<2>(___M_impl)) {
			if (std::get<1>(___M_impl) != u8"@compare:") {
				Owning<Any> sel_cmp = aa->valueForSelectorKey(std::get<1>(___M_impl), bb);
				return sel_cmp ? sel_cmp->intValue() : aa->compare(*bb);
			}
			return aa->compare(*bb);
		} else {
			if (std::get<1>(___M_impl) != u8"@compare:") {
				Owning<Any> sel_cmp = bb->valueForSelectorKey(std::get<1>(___M_impl), aa);
				return sel_cmp ? sel_cmp->intValue() : bb->compare(*aa);
			}
			return bb->compare(*aa);
		}
	}
	return OrderedDescending;
}

#pragma mark -

const SortDescriptor SortDescriptor::reversedSortDescriptor()
{ return SortDescriptor(std::get<0>(___M_impl), std::get<1>(___M_impl), !std::get<2>(___M_impl)); }

#pragma mark -

const String SortDescriptor::key() const
{ return {std::get<0>(___M_impl)}; }

const String SortDescriptor::selectorKey() const
{ return {std::get<1>(___M_impl)}; }

bool SortDescriptor::ascending() const
{ return std::get<2>(___M_impl); }

/* EOF */