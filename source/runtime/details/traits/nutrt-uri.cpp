//
// nutrt-uri.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-uri.hpp>
#include <coconut/runtime/details/nutrt-algorithms.hpp>

using namespace coconut::runtime;
using namespace coconut::runtime::traits;

#include <source/runtime/builtins/nutrt-uri_escaping.hxx>
#include <source/runtime/builtins/nutrt-uri_joining.hxx>
#include <source/runtime/builtins/nutrt-uri_parsing.hxx>

uri::uri()
: ___M_components
{
	{ "string", "" },
	{ "specifier", "" },
	{ "scheme", "" },
	{ "user", "" },
	{ "password", "" },
	{ "host", "" },
	{ "port", "" },
	{ "path", "" },
	{ "parameter", "" },
	{ "query", "" },
	{ "fragment", "" }
}
, ___M_parameters()
, ___M_port(0)
, ___M_isfile_url(false)
, ___M_isvalid_url(false)
{ /* NOP */ }

uri::uri(const uri & url)
: ___M_components(url.___M_components)
, ___M_parameters(url.___M_parameters)
, ___M_port(url.___M_port)
, ___M_isfile_url(url.___M_isfile_url)
, ___M_isvalid_url(url.___M_isvalid_url)
{ /* NOP */ }

uri::uri(const uri & url, bool normalize)
: ___M_components(url.___M_components)
, ___M_parameters(url.___M_parameters)
, ___M_port(url.___M_port)
, ___M_isfile_url(url.___M_isfile_url)
, ___M_isvalid_url(url.___M_isvalid_url)
{
	if (normalize) {
		___M_components.clear();
		___M_components =
		{
			{ "string", "" },
			{ "specifier", "" },
			{ "scheme", "" },
			{ "user", "" },
			{ "password", "" },
			{ "host", "" },
			{ "port", "" },
			{ "path", "" },
			{ "parameter", "" },
			{ "query", "" },
			{ "fragment", "" }
		};
		___M_parameters.clear();
		___M_port = 0;
		___M_isvalid_url = parseit(
			url.to_string()
			, ___M_components
			, ___M_parameters
			, ___M_isfile_url
			, ___M_port
			, normalize
		);
		if (___M_isvalid_url && ___M_components.at("port").size()) {
			___M_port = algorithms::to_numeric<std::size_t>(___M_components.at("port"));
		}
	}
}

uri::uri(const std::string & str_url, const uri & url, bool normalize)
: ___M_components
{
	{ "string", "" },
	{ "specifier", "" },
	{ "scheme", "" },
	{ "user", "" },
	{ "password", "" },
	{ "host", "" },
	{ "port", "" },
	{ "path", "" },
	{ "parameter", "" },
	{ "query", "" },
	{ "fragment", "" }
}
, ___M_parameters()
, ___M_port(0)
, ___M_isfile_url(false)
, ___M_isvalid_url(false)
{
	std::string str_abs_url;
	if (joinit(str_url, url.to_string(), str_abs_url, normalize)) {
		___M_isvalid_url = parseit(
			str_abs_url
			, ___M_components
			, ___M_parameters
			, ___M_isfile_url
			, ___M_port
			, normalize
		);
		if (___M_isvalid_url && ___M_components.at("port").size()) {
			___M_port = algorithms::to_numeric<std::size_t>(___M_components.at("port"));
		}
	}
}

uri::uri(const std::string & str_url, const std::string & str_base_url, bool normalize)
: ___M_components
{
	{ "string", "" },
	{ "specifier", "" },
	{ "scheme", "" },
	{ "user", "" },
	{ "password", "" },
	{ "host", "" },
	{ "port", "" },
	{ "path", "" },
	{ "parameter", "" },
	{ "query", "" },
	{ "fragment", "" }
}
, ___M_parameters()
, ___M_port(0)
, ___M_isfile_url(false)
, ___M_isvalid_url(false)
{
	std::string str_abs_url;
	if (joinit(str_url, str_base_url, str_abs_url, normalize)) {
		___M_isvalid_url = parseit(
			str_abs_url
			, ___M_components
			, ___M_parameters
			, ___M_isfile_url
			, ___M_port
			, normalize
		);
		if (___M_isvalid_url && ___M_components.at("port").size()) {
			___M_port = algorithms::to_numeric<std::size_t>(___M_components.at("port"));
		}
	}
}

uri::uri(const std::string & str_url, bool is_filepath, bool normalize)
: ___M_components
{
	{ "string", "" },
	{ "specifier", "" },
	{ "scheme", "" },
	{ "user", "" },
	{ "password", "" },
	{ "host", "" },
	{ "port", "" },
	{ "path", "" },
	{ "parameter", "" },
	{ "query", "" },
	{ "fragment", "" }
}
, ___M_parameters()
, ___M_port(0)
, ___M_isfile_url(false)
, ___M_isvalid_url(false)
{
	if (is_filepath) {
		std::string abs_uri;
		if (builtins::uri_filetouri(str_url, abs_uri)) {
			___M_isfile_url = true;
			___M_isvalid_url = parseit(
				abs_uri
				, ___M_components
				, ___M_parameters
				, ___M_isfile_url
				, ___M_port
				, normalize
			);
		}
	} else {
		___M_isvalid_url = parseit(
			str_url
			, ___M_components
			, ___M_parameters
			, ___M_isfile_url
			, ___M_port
			, normalize
		);
	}
	if (___M_isvalid_url && ___M_components.at("port").size()) {
		___M_port = algorithms::to_numeric<std::size_t>(___M_components.at("port"));
	}
}

uri::uri(const std::string & scheme, const std::string & host, const std::string & path, bool normalize)
: ___M_components
{
	{ "string", "" },
	{ "specifier", "" },
	{ "scheme", "" },
	{ "user", "" },
	{ "password", "" },
	{ "host", "" },
	{ "port", "" },
	{ "path", "" },
	{ "parameter", "" },
	{ "query", "" },
	{ "fragment", "" }
}
, ___M_parameters()
, ___M_port(0)
, ___M_isfile_url(false)
, ___M_isvalid_url(false)
{
	std::string in = scheme;
	in += "://";
	in += host;
	in += path;
	___M_isvalid_url = parseit(
		in
		, ___M_components
		, ___M_parameters
		, ___M_isfile_url
		, ___M_port
		, normalize
	);
	if (___M_isvalid_url && ___M_components.at("port").size()) {
		___M_port = algorithms::to_numeric<std::size_t>(___M_components.at("port"));
	}
}

uri::uri(const std::string & str_url)
: uri(str_url, !builtins::uri_have_scheme(str_url), true)
{ /* NOP */ }

uri::uri(const char * str_url)
: uri(str_url, !builtins::uri_have_scheme(str_url), true)
{ /* NOP */ }

uri::uri(const char16_t * str_url)
: uri()
{ /* NOP */ }

uri::~uri()
{ /* NOP */ }

#pragma mark -

std::string uri::escape(const std::string & in, bool space_as_plus)
{ return builtins::uri_escape(in, space_as_plus); }

std::string uri::unescape(const std::string & in, bool plus_as_space)
{ return builtins::uri_escape(in, plus_as_space); }

bool uri::is_scheme(const std::string & scheme)
{ return builtins::uri_valid_scheme(scheme); }

#pragma mark -

bool uri::parseit(
	const std::string & str_url,
	std::map<std::string, std::string> & components,
	std::map<std::string, std::string> & parameters,
	bool & is_file,
	std::uint16_t & port,
	bool normalize
) {
	return builtins::uri_parse(
		str_url
		, components
		, parameters
		, is_file
		, port
		, normalize
	);
}

bool uri::joinit(
	const std::string & str_relative_url,
	const std::string & str_base_url,
	std::string & str_url,
	bool normalize
) {
	return builtins::uri_join(
		str_relative_url
		, str_base_url
		, str_url
		, normalize
	);
}

#pragma mark -

uri & uri::operator = (const uri & url)
{
	if (this == &url) {
		return *this;
	}
	
	___M_components = url.___M_components;
	___M_parameters = url.___M_parameters;
	___M_port = url.___M_port;
	___M_isfile_url = url.___M_isfile_url;
	___M_isvalid_url = url.___M_isvalid_url;
	
	return *this;
}

int uri::compare(const uri & other_url) const
{ return algorithms::icmp(to_string(), other_url.to_string()); }

#pragma mark -

std::string uri::to_string() const
{
	std::string abs;
	abs += ___M_components.at("scheme");
	abs += ":";
	abs += ___M_components.at("specifier");
	return abs;
}

#pragma mark -

bool uri::is_valid() const
{ return ___M_isvalid_url; }

bool uri::is_file_url() const
{ return ___M_isfile_url; }

#pragma mark -

const std::string & uri::specifier() const
{ return ___M_components.at("specifier"); }

#pragma mark -

const std::string & uri::scheme() const
{ return ___M_components.at("scheme"); }

const std::string & uri::user() const
{ return ___M_components.at("user"); }

const std::string & uri::password() const
{ return ___M_components.at("password"); }

const std::string & uri::host() const
{ return ___M_components.at("host"); }

std::uint16_t uri::port() const
{ return ___M_port; }

const std::string & uri::path() const
{ return ___M_components.at("path"); }

const std::string & uri::parameter() const
{ return ___M_components.at("parameter"); }

const std::string & uri::query() const
{ return ___M_components.at("query"); }

const std::string & uri::fragment() const
{ return ___M_components.at("fragment"); }

#pragma mark -

const std::map<std::string, std::string> & uri::components() const
{ return ___M_components; }

const std::map<std::string, std::string> & uri::parameters() const
{ return ___M_parameters; }

/* EOF */