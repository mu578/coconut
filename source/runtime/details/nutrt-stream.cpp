//
// nutrt-stream.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/nutrt-stream.hpp>
#include <coconut/runtime/details/nutrt-types.hpp>
#include <coconut/runtime/details/nutrt-unicode.hpp>

using namespace coconut::runtime;

#include <source/runtime/builtins/nutrt-unicode_wide.hxx>
#include <source/runtime/builtins/nutrt-stream_convpath.hxx>

stream::ifstream::ifstream()
: std::ifstream()
{ /* NOP */ }

stream::ifstream::ifstream(const std::string & utf8_path, std::ios_base::open_mode mode)
: std::ifstream(builtins::___F_stream_convpath(utf8_path).c_str(), mode)
{ /* NOP */ }

stream::ifstream::ifstream(const std::u16string & utf16_path, std::ios_base::open_mode mode)
: std::ifstream(builtins::___F_stream_convpath(utf16_path).c_str(), mode)
{ /* NOP */ }

stream::ifstream::~ifstream()
{ /* NOP */ }

void stream::ifstream::open(const std::string & utf8_path, std::ios_base::open_mode mode)
{ std::ifstream::open(builtins::___F_stream_convpath(utf8_path).c_str(), mode); }

void stream::ifstream::open(const std::u16string & utf16_path, std::ios_base::open_mode mode)
{ std::ifstream::open(builtins::___F_stream_convpath(utf16_path).c_str(), mode); }

#pragma mark -

stream::ofstream::ofstream()
: std::ofstream()
{ /* NOP */ }

stream::ofstream::ofstream(const std::string & utf8_path, std::ios_base::open_mode mode)
: std::ofstream(builtins::___F_stream_convpath(utf8_path).c_str(), mode)
{ /* NOP */ }

stream::ofstream::ofstream(const std::u16string & utf16_path, std::ios_base::open_mode mode)
: std::ofstream(builtins::___F_stream_convpath(utf16_path).c_str(), mode)
{ /* NOP */ }

stream::ofstream::~ofstream()
{ /* NOP */ }

void stream::ofstream::open(const std::string & utf8_path, std::ios_base::open_mode mode)
{ std::ofstream::open(builtins::___F_stream_convpath(utf8_path).c_str(), mode); }

void stream::ofstream::open(const std::u16string & utf16_path, std::ios_base::open_mode mode)
{ std::ofstream::open(builtins::___F_stream_convpath(utf16_path).c_str(), mode); }

#pragma mark -

stream::fstream::fstream() :
	std::fstream()
{ /* NOP */ }

stream::fstream::fstream(const std::string & utf8_path, std::ios_base::open_mode mode)
: std::fstream(builtins::___F_stream_convpath(utf8_path).c_str(), mode)
{ /* NOP */ }

stream::fstream::fstream(const std::u16string & utf16_path, std::ios_base::open_mode mode)
: std::fstream(builtins::___F_stream_convpath(utf16_path).c_str(), mode)
{ /* NOP */ }

stream::fstream::~fstream()
{ /* NOP */ }

void stream::fstream::open(const std::string & utf8_path, std::ios_base::open_mode mode)
{ std::fstream::open(builtins::___F_stream_convpath(utf8_path).c_str(), mode); }

void stream::fstream::open(const std::u16string & utf16_path, std::ios_base::open_mode mode)
{ std::fstream::open(builtins::___F_stream_convpath(utf16_path).c_str(), mode); }

#pragma mark -

stream::imstreambuf::imstreambuf()
: std::streambuf()
, _M_head(0)
, _M_size(0)
, _M_tail(0)
, _M_curr(0)
{ /* NOP */ }

stream::imstreambuf::imstreambuf(imstreambuf &)
: std::streambuf()
, _M_head(0)
, _M_size(0)
, _M_tail(0)
, _M_curr(0)
{ /* NOP */ }

stream::imstreambuf::imstreambuf(const char * membytes, std::size_t size)
: std::streambuf()
, _M_head(weak_cast<char *>(membytes))
, _M_size(size)
, _M_tail(_M_head + size)
, _M_curr(_M_head)
{ setg(_M_head, _M_curr, _M_tail); }

stream::imstreambuf::imstreambuf(const std::uint8_t * membytes, std::size_t size)
: std::streambuf()
, _M_head(weak_cast<char *>(membytes))
, _M_size(size)
, _M_tail(_M_head + size)
, _M_curr(_M_head)
{ setg(_M_head, _M_curr, _M_tail); }

stream::imstreambuf::~imstreambuf()
{ 
	_M_head = nullptr;
	_M_size = 0;
	_M_tail = nullptr;
	_M_curr = nullptr;
}

void stream::imstreambuf::setmem(const char * membytes, std::size_t size)
{
	_M_head = weak_cast<char *>(membytes);
	_M_size = size;
	_M_tail = _M_head + size;
	_M_curr = _M_head;
	setg(_M_head, _M_curr, _M_tail);
}

void stream::imstreambuf::setmem(const std::uint8_t * membytes, std::size_t size)
{
	_M_head = weak_cast<char *>(membytes);
	_M_size = size;
	_M_tail = _M_head + size;
	_M_curr = _M_head;
	setg(_M_head, _M_curr, _M_tail);
}

const char * stream::imstreambuf::membytes()
{ return _M_head; }

std::size_t stream::imstreambuf::memsize()
{ return _M_size; }

std::streambuf::int_type stream::imstreambuf::uflow()
{
	if (_M_curr == _M_tail) {
		return std::streambuf::traits_type::eof();
	}
	return *_M_curr++;
}

std::streambuf::int_type stream::imstreambuf::underflow()
{
	if (_M_curr == _M_tail) {
		return std::streambuf::traits_type::eof();
	}
	return *_M_curr;
}

std::streamsize stream::imstreambuf::showmanyc()
{
	// assert(std::less_equal<const char *>()(_M_curr, _M_tail));
	return _M_tail - _M_curr;
}

std::streambuf::int_type stream::imstreambuf::pbackfail(std::streambuf::int_type ch)
{
	if (_M_curr == _M_head || (ch != std::streambuf::traits_type::eof() && ch != _M_curr[-1])) {
		return std::streambuf::traits_type::eof();
	}
	return *--_M_curr;
}

std::size_t stream::imstreambuf::output_bytes()
{ return weak_cast<std::size_t>(pptr() - pbase()); }

std::streambuf::pos_type stream::imstreambuf::seekoff(
	std::streambuf::off_type off,
	std::ios_base::seekdir dir,
	std::ios_base::openmode which
) {
	COCONUT_UNUSED(which);
	off_type offset = (std::ios::beg == dir) ? off :
		(std::ios::end == dir) ? (weak_cast<off_type>(_M_size) - off) : (gptr() - _M_head) + off;
	setg(_M_head, _M_head + offset, _M_head + _M_size);
	return gptr() - _M_head;
}

#pragma mark -

stream::imstream::imstream()
: std::istream(&_M_buf)
, _M_buf(weak_cast<std::uint8_t *>(nullptr), 0)
{ /* NOP */ }

stream::imstream::imstream(imstream & im)
: std::istream(&_M_buf)
, _M_buf()
{ _M_buf.setmem(im._M_buf.membytes(), im._M_buf.memsize()); }

stream::imstream::imstream(const char * membytes, std::size_t size)
: std::istream(&_M_buf)
, _M_buf(membytes, size)
{ /* NOP */ }

stream::imstream::imstream(const std::uint8_t * membytes, std::size_t size)
: std::istream(&_M_buf)
, _M_buf(membytes, size)
{ /* NOP */ }

stream::imstream::~imstream()
{ /* NOP */ }

/* EOF */