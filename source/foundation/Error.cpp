//
// Error.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Error.hpp>

using namespace coconut;

Error::Error() :
	Object(ErrorClass),
	___M_impl{ u8"<none>", NotFound, {} }
{ /* NOP */ }

Error::Error(const Error & err) :
	Object(ErrorClass),
	___M_impl(err.___M_impl)
{ /* NOP */ }

Error::Error(Error && err) noexcept :
	Object(ErrorClass),
	___M_impl(std::move(err.___M_impl))
{ /* NOP */ }

Error::Error(std::size_t code) :
	Object(ErrorClass),
	___M_impl{ u8"<none>", code, {} }
{ /* NOP */ }

Error::Error(const String & domain, std::size_t code) :
	Object(ErrorClass),
	___M_impl{ domain, code, {} }
{ /* NOP */ }

Error::Error(const String & domain, std::size_t code, const Dictionary & userInfo) :
	Object(ErrorClass),
	___M_impl{ domain, code, userInfo }
{ /* NOP */ }

Error::~Error()
{ /* NOP */ }

#pragma mark -

std::size_t Error::hash() const
{ return std::get<0>(___M_impl).hash() + std::get<1>(___M_impl); }

#pragma mark -

Owning<Any> Error::copy() const
{ return ptr_create<Error>(*this); }

#pragma mark -

ComparisonResult Error::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		if (code() < ref_cast<Error>(ref).code()) {
			return OrderedAscending;
		} else if (code() > ref_cast<Error>(ref).code()) {
			return OrderedDescending;
		}
		return OrderedSame;
	}
	return OrderedDescending;
}

#pragma mark -

std::string Error::stringValue() const
{ return std::get<0>(___M_impl).stringValue(); }

std::size_t Error::code() const
{ return std::get<1>(___M_impl); }

const String Error::domain() const
{ return {std::get<0>(___M_impl)}; }

const Dictionary Error::userInfo() const
{ return {std::get<2>(___M_impl)}; }

/* EOF */