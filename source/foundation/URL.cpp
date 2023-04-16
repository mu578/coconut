//
// URL.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/URL.hpp>
#include <coconut/foundation/Array.hpp>
#include <coconut/foundation/MutableDictionary.hpp>
#include <coconut/foundation/Path.hpp>
#include <coconut/foundation/String.hpp>

using namespace coconut;

URL::URL() :
	Object(URLClass),
	___M_impl()
{ /* NOP */ }

URL::URL(const URL & url) :
	Object(URLClass),
	___M_impl(url.___M_impl, false)
{ /* NOP */ }

URL::URL(URL && url) noexcept :
	Object(URLClass),
	___M_impl(std::move(url.___M_impl), false)
{ /* NOP */ }

URL::URL(const Path & path) :
	Object(URLClass),
	___M_impl(path.stringValue(), true, false)
{ /* NOP */ }

URL::URL(const String & in) :
	Object(URLClass),
	___M_impl(in.stringValue())
{ /* NOP */ }

URL::URL(const String & in, const URL & url) :
	Object(URLClass),
	___M_impl(in.stringValue(), url.___M_impl, false)
{ /* NOP */ }

URL::URL(const String & scheme, const String & host, const String & path) :
	Object(URLClass),
	___M_impl(scheme.stringValue(), host.stringValue(), path.stringValue(), false)
{ /* NOP */ }

URL::URL(const char * utf8_url) :
	Object(URLClass),
	___M_impl(utf8_url)
{ /* NOP */ }

URL::URL(const char16_t * utf16_url) :
	Object(URLClass),
	___M_impl(utf16_url)
{ /* NOP */ }

URL::~URL()
{ /* NOP */ }

#pragma mark -

const String URL::percentEscapesEncode(const String & in, bool space_as_plus)
{ return {impl_trait::escape(in.stringValue(), space_as_plus)}; }

const String URL::percentEscapesDecode(const String & in, bool plus_as_space)
{ return {impl_trait::unescape(in.stringValue(), plus_as_space)}; }

#pragma mark -

Owning<Any> URL::copy() const
{ return ptr_create<URL>(*this); }

#pragma mark -

ComparisonResult URL::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return ___M_impl.compare(ref_cast<URL>(ref).___M_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string URL::stringValue() const
{ return ___M_impl.to_string(); }

#pragma mark -

bool URL::isFileURL() const
{ return ___M_impl.is_file_url(); }

#pragma mark -

const URL URL::normalizedURL() const
{
	URL ret;
	ret.___M_impl = impl_trait(___M_impl, true);
	return ret;
}

const String URL::specifier() const
{ return {___M_impl.specifier()}; }

#pragma mark -

const String URL::scheme() const
{ return {___M_impl.scheme()}; }

const String URL::host() const
{ return {___M_impl.scheme()}; }

std::size_t URL::port() const
{ return ___M_impl.port(); }

const String URL::user() const
{ return {___M_impl.user()}; }

const String URL::password() const
{ return {___M_impl.password()}; }

const String URL::path() const
{ return {___M_impl.path()}; }

const String URL::parameter() const
{ return {___M_impl.parameter()}; }

const String URL::query() const
{ return {___M_impl.query()}; }

const String URL::fragment() const
{ return {___M_impl.fragment()}; }

#pragma mark -

const Dictionary URL::queryParameters() const
{
	Dictionary::impl_trait buf;
	auto parameters = ___M_impl.parameters();
	for (auto & kv : parameters) {
		buf.insert(std::make_pair(ptr_create<String>(kv.first), ptr_create<String>(kv.second)));
	}
	return { buf.begin(), buf.end() };
}

#pragma mark -

const Path URL::fileSystemRepresentation() const
{ return {___M_impl.path()}; }

#pragma mark -

bool URL::operator == (const URL & other_url) const
{ return (compare(other_url) == OrderedSame); }

bool URL::operator != (const URL & other_url) const
{ return (compare(other_url) != OrderedSame); }

bool URL::operator < (const URL & other_url) const
{ return (compare(other_url) == OrderedAscending); }

bool URL::operator <= (const URL & other_url) const
{
	ComparisonResult cmp = compare(other_url);
	return (cmp == OrderedAscending || cmp == OrderedSame);
}

bool URL::operator > (const URL & other_url) const
{ return (compare(other_url) == OrderedDescending); }

bool URL::operator >= (const URL & other_url) const
{
	ComparisonResult cmp = compare(other_url);
	return (cmp == OrderedDescending || cmp == OrderedSame);
}

/* EOF */