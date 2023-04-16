//
// nutrt-upath.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-upath.hpp>
#include <coconut/runtime/details/traits/nutrt-ustring.hpp>

#include <coconut/runtime/details/nutrt-algorithms.hpp>
#include <coconut/runtime/details/nutrt-unicode.hpp>

using namespace coconut::runtime;
using namespace coconut::runtime::traits;

#include <source/runtime/builtins/nutrt-unicode_wide.hxx>
#include <source/runtime/builtins/nutrt-filesystem_info.hxx>
#include <source/runtime/builtins/nutrt-upath_absolute.hxx>
#include <source/runtime/builtins/nutrt-upath_detection.hxx>

upath::upath()
: ___M_components()
{ /* NOP */ }

upath::upath(const upath & path)
: ___M_components(path.___M_components)
{ /* NOP */ }

upath::upath(const ustring & path, dirsep_option option)
: upath(path.to_utf8(), encoding_utf8, option)
{ /* NOP */ }

upath::upath(const std::string & str_path, encoding_option encoding, dirsep_option option)
: ___M_components()
{
	std::string path;
	if (encoding != encoding_utf8) {
		ustring p(str_path, encoding);
		path = p.to_utf8();
	} else {
		path = str_path;
	}
	builtins::upath_parse(___M_components, path, option);
	
	for (const auto & comp : ___M_components) {
		std::cerr << "+ " << comp << std::endl;
	}
}

upath::upath(const std::u16string & str_path, encoding_option encoding, dirsep_option option)
: upath(unicode::utf16_to_utf8(str_path), encoding_utf8, option)
{ /* NOP */ }

upath::~upath()
{ /* NOP */ }

upath & upath::operator = (const upath & path)
{
	if (this == &path) {
		return *this;
	}
	___M_components = path.___M_components;
	return *this;
}

int upath::compare(const upath & other_path) const
{
	return ustring::compare_utf8(
		to_utf8_string(),
		other_path.to_utf8_string(),
		search_insensitive|search_nowidth
	);
}

std::string upath::to_string() const
{
	return to_utf8_string();
}

const upath upath::absolute(dirsep_option option) const
{
	// be smarter about separator
	// builtins::upath_absolute(to_utf8_string(option)),
	return upath(
		"",
		encoding_utf8,
		option
	);
}

const upath upath::basename() const
{
	return upath(
		___M_components.back(), encoding_utf8, dirsep_whack
	);
}

const upath upath::dirname(dirsep_option option) const
{
	std::vector<std::string> components(___M_components.begin(), ___M_components.end());
	if (components.size() > 1) {
		components.pop_back();
	}
	std::string sep;
	switch (option)
	{
		case dirsep_slack:
			sep.assign("\\");
		break;
		default:
			sep.assign("/");
		break;
	}
	return upath(
		algorithms::join(___M_components, sep), encoding_utf8, option
	);
}

const std::vector<std::string> upath::components() const
{ return ___M_components; }

const std::string upath::to_utf8_string(dirsep_option option) const
{
	std::string sep;
	switch (option)
	{
		case dirsep_slack:
			sep.assign("\\");
		break;
		default:
			sep.assign("/");
		break;
	}
	return algorithms::join(___M_components, sep);
}

const std::u16string upath::to_utf16_string(dirsep_option option) const
{ return unicode::utf8_to_utf16(to_utf8_string(option)); }

/* EOF */
