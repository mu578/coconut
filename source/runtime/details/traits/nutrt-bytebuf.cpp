//
// nutrt-bytebuf.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-bytebuf.hpp>
#include <coconut/runtime/details/traits/nutrt-upath.hpp>
#include <coconut/runtime/details/traits/nutrt-irange.hpp>
#include <coconut/runtime/details/traits/nutrt-uri.hpp>

#include <coconut/runtime/details/nutrt-base64.hpp>
#include <coconut/runtime/details/nutrt-byteorder.hpp>
#include <coconut/runtime/details/nutrt-hash.hpp>

using namespace coconut::runtime;
using namespace coconut::runtime::traits;

bytebuf::bytebuf()
: ___M_bytes()
{ /* NOP */ }

bytebuf::bytebuf(const bytebuf & dat)
: ___M_bytes(dat.___M_bytes)
{ /* NOP */ }

bytebuf::bytebuf(bytebuf && dat) noexcept
: ___M_bytes(std::move(dat.___M_bytes))
{ /* NOP */ }

bytebuf::bytebuf(const bytebuf & dat, bool b64dec)
: ___M_bytes(dat.___M_bytes)
{ if (b64dec) { b64_decode(); } }

bytebuf::bytebuf(bytebuf && dat, bool b64dec) noexcept
: ___M_bytes(std::move(dat.___M_bytes))
{ if (b64dec) { b64_decode(); } }

bytebuf::bytebuf(std::size_t capacity)
: ___M_bytes(capacity)
{ /* NOP */ }

bytebuf::bytebuf(const std::uint8_t * membytes, std::size_t length, bool b64dec)
: ___M_bytes()
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i]);
		}
		if (b64dec) {
			b64_decode();
		}
	}
}

bytebuf::bytebuf(const char * membytes, std::size_t length, bool b64dec)
: ___M_bytes()
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i]);
		}
		if (b64dec) {
			b64_decode();
		}
	}
}

bytebuf::bytebuf(const std::uint16_t * membytes, std::size_t length, packing_option option)
: ___M_bytes()
{
	if (membytes) {
		for (std::size_t i = 0 ; i < length ; i++) {
			push_back(membytes[i], option);
		}
	}
}

bytebuf::bytebuf(const std::uint32_t * membytes, std::size_t length, packing_option option)
: ___M_bytes()
{
	if (membytes) {
		for (std::size_t i = 0 ; i < length ; i++) {
			push_back(membytes[i], option);
		}
	}
}

bytebuf::bytebuf(const std::uint64_t * membytes, std::size_t length, packing_option option)
: ___M_bytes()
{
	if (membytes) {
		for (std::size_t i = 0 ; i < length ; i++) {
			push_back(membytes[i], option);
		}
	}
}

bytebuf::bytebuf(const std::int16_t * membytes, std::size_t length, packing_option option)
: ___M_bytes()
{
	if (membytes) {
		for (std::size_t i = 0 ; i < length ; i++) {
			push_back(membytes[i], option);
		}
	}
}

bytebuf::bytebuf(const std::int32_t * membytes, std::size_t length, packing_option option)
: ___M_bytes()
{
	if (membytes) {
		for (std::size_t i = 0 ; i < length ; i++) {
			push_back(membytes[i], option);
		}
	}
}

bytebuf::bytebuf(const std::int64_t * membytes, std::size_t length, packing_option option)
: ___M_bytes()
{
	if (membytes) {
		for (std::size_t i = 0 ; i < length ; i++) {
			push_back(membytes[i], option);
		}
	}
}

bytebuf::bytebuf(stream::ifstream & in_binary)
: ___M_bytes()
{
	if (in_binary.is_open()) {
		rb_fin(in_binary);
	}
}

bytebuf::bytebuf(const upath & path, bool b64dec)
: ___M_bytes()
{
	stream::ifstream in_binary(path.to_utf8_string());
	if (in_binary.is_open()) {
		rb_fin(in_binary);
		in_binary.close();
		if (b64dec) {
			b64_decode();
		}
	}
}

bytebuf::bytebuf(const uri & url, bool b64dec)
: ___M_bytes()
{
	if (url.is_file_url()) {
		upath path(url.path());
		stream::ifstream in_binary(path.to_utf8_string());
		if (in_binary.is_open()) {
			rb_fin(in_binary);
			in_binary.close();
			if (b64dec) {
				b64_decode();
			}
		}
	}
}

bytebuf::bytebuf(stream::ifstream & in_binary, std::size_t location, std::size_t length)
: ___M_bytes()
{
	if (in_binary.is_open()) {
		rb_fin(in_binary, location, length);
	}
}

bytebuf::~bytebuf()
{ ___M_bytes.clear(); }

#pragma mark -

void bytebuf::unpack(const std::uint8_t (&in)[2], std::uint16_t & out, unpacking_option option)
{
	if (option == unpacking_littleendian) {
		byteorder::r16le(in, out);
	} else {
		byteorder::r16be(in, out);
	}
}

void bytebuf::unpack(const std::uint8_t (&in)[4], std::uint32_t & out, unpacking_option option)
{
	if (option == unpacking_littleendian) {
		byteorder::r32le(in, out);
	} else {
		byteorder::r32be(in, out);
	}
}

void bytebuf::unpack(const std::uint8_t (&in)[8], std::uint64_t & out, unpacking_option option)
{
	if (option == unpacking_littleendian) {
		byteorder::r64le(in, out);
	} else {
		byteorder::r64be(in, out);
	}
}

#pragma mark -

void bytebuf::unpack(const std::uint8_t (&in)[2], std::int16_t & out, unpacking_option option)
{
	if (option == unpacking_littleendian) {
		byteorder::rs16le(in, out);
	} else {
		byteorder::rs16be(in, out);
	}
}

void bytebuf::unpack(const std::uint8_t (&in)[4], std::int32_t & out, unpacking_option option)
{
	if (option == unpacking_littleendian) {
		byteorder::rs32le(in, out);
	} else {
		byteorder::rs32be(in, out);
	}
}

void bytebuf::unpack(const std::uint8_t (&in)[8], std::int64_t & out, unpacking_option option)
{
	if (option == unpacking_littleendian) {
		byteorder::rs64le(in, out);
	} else {
		byteorder::rs64be(in, out);
	}
}

#pragma mark -

void bytebuf::pack(const std::uint16_t & in, std::uint8_t (&out)[2], packing_option option)
{
	if (option == packing_littleendian) {
		byteorder::w16le(in, out);
	} else {
		byteorder::w16be(in, out);
	}
}

void bytebuf::pack(const std::uint32_t & in, std::uint8_t (&out)[4], packing_option option)
{
	if (option == packing_littleendian) {
		byteorder::w32le(in, out);
	} else {
		byteorder::w32be(in, out);
	}
}

void bytebuf::pack(const std::uint64_t & in, std::uint8_t (&out)[8], packing_option option)
{
	if (option == packing_littleendian) {
		byteorder::w64le(in, out);
	} else {
		byteorder::w64be(in, out);
	}
}

#pragma mark -

void bytebuf::pack(const std::int16_t & in, std::uint8_t (&out)[2], packing_option option)
{
	if (option == packing_littleendian) {
		byteorder::w16le(in, out);
	} else {
		byteorder::w16be(in, out);
	}
}

void bytebuf::pack(const std::int32_t & in, std::uint8_t (&out)[4], packing_option option)
{
	if (option == packing_littleendian) {
		byteorder::w32le(in, out);
	} else {
		byteorder::w32be(in, out);
	}
}

void bytebuf::pack(const std::int64_t & in, std::uint8_t (&out)[8], packing_option option)
{
	if (option == packing_littleendian) {
		byteorder::w64le(in, out);
	} else {
		byteorder::w64be(in, out);
	}
}

#pragma mark -

bool bytebuf::rb_fin(stream::ifstream & in_binary)
{
	bool result = false;
	std::size_t blocksize = 256;
	std::size_t chunksize = 0;
	std::streampos insize = 0;
	char * buffer = nullptr;
	
	___M_bytes.clear();
	in_binary.seekg(0, in_binary.end);
	insize = in_binary.tellg();
	in_binary.clear();
	in_binary.seekg(0, in_binary.beg);
	if (insize) {
		if (insize >= 1024 * 1024) {
			blocksize = 1024;
		} else if (insize >= 1024 * 512) {
			blocksize = 512;
		}
		buffer = new char[blocksize];
		if (buffer != nullptr) {
			std::memset(buffer, 0, blocksize);
			while (!in_binary.eof()) {
				in_binary.read(buffer, static_cast<std::streamsize>(blocksize));
				std::streamsize cnt = in_binary.gcount();
				if (cnt) {
					chunksize = static_cast<std::size_t>(cnt);
					for (std::size_t i = 0; i < chunksize; i++) {
						___M_bytes.push_back(weak_cast<std::uint8_t>(buffer[i]));
					}
					result = true;
				}
			}
			delete [] buffer;
			buffer = nullptr;
		}
	}
	return result;
}

bool bytebuf::rb_fin(stream::ifstream & in_binary, std::size_t location, std::size_t length)
{
	bool result = false;
	std::size_t blocksize = 0;
	std::size_t chunksize = 0;
	std::streampos insize = 0;
	char * buffer = nullptr;
	
	___M_bytes.clear();
	in_binary.seekg(0, in_binary.end);
	insize = in_binary.tellg();
	in_binary.clear();
	in_binary.seekg(0, in_binary.beg);
	if (insize && location < static_cast<std::size_t>(insize)) {
		if ((location + length) > static_cast<std::size_t>(insize)) {
			blocksize = static_cast<std::size_t>(insize) - location;
		} else {
			blocksize = length;
		}
		buffer = new char[blocksize];
		if (buffer != nullptr) {
			in_binary.clear();
			in_binary.seekg(static_cast<stream::ifstream::off_type>(location), in_binary.beg);
			in_binary.read(buffer, static_cast<std::streamsize>(blocksize));
			std::streamsize cnt = in_binary.gcount();
			if (cnt) {
				chunksize = static_cast<std::size_t>(cnt);
				for (std::size_t i = 0; i < chunksize; i++) {
					___M_bytes.push_back(weak_cast<std::uint8_t>(buffer[i]));
				}
				result = true;
			}
			delete [] buffer;
			buffer = nullptr;
		}
	}
	return result;
}

bool bytebuf::wb_fout(stream::ofstream & out_binary) const
{
	bool result = false;
	if (out_binary.is_open()) {
		std::size_t sz = ___M_bytes.size();
		if (sz) {
			const void * bytes = raw();
			if (bytes) {
				std::streampos before = out_binary.tellp();
				out_binary.write(static_cast<const char *>(bytes), static_cast<std::streamsize>(sz));
				if ((out_binary.tellp() - before) == static_cast<std::streamoff>(sz)) {
					result = true;
				}
			}
		}
	}
	return result;
}

bool bytebuf::wb_fout(stream::ofstream & out_binary, std::size_t location, std::size_t length) const
{
	bool result = false;
	if (out_binary.is_open()) {
		std::vector<std::uint8_t> buf;
		get_bytes(buf, location, length);
		std::size_t sz = buf.size();
		if (sz) {
			const void * bytes = buf.data();
			if (bytes) {
				std::streampos before = out_binary.tellp();
				out_binary.write(weak_cast<const char *>(bytes), static_cast<std::streamsize>(sz));
				if ((out_binary.tellp() - before) == static_cast<std::streamoff>(sz)) {
					result = true;
				}
			}
		}
	}
	return result;
}

#pragma mark -

bytebuf & bytebuf::operator = (const bytebuf & dat)
{
	if (this == &dat) {
		return *this;
	}
	___M_bytes.clear();
	for (const_iterator it = dat.cbegin(); it != dat.cend(); ++it) {
		___M_bytes.push_back((*it));
	}
	return *this;
}

#pragma mark -

int bytebuf::compare(const bytebuf & other_dat) const
{
	if (this == &other_dat) {
		return cmp_same;
	} else if (size() < other_dat.size()) {
		return cmp_ascending;
	} else if (size() > other_dat.size()) {
		return cmp_descending;
	}
	return std::memcmp(raw(), other_dat.raw(), size());
}

#pragma mark -

void bytebuf::set(std::uint8_t v)
{
	clear();
	push_back(v);
}

void bytebuf::set(char v)
{
	clear();
	push_back(v);
}

#pragma mark -

void bytebuf::set(std::uint16_t v, packing_option option)
{
	clear();
	push_back(v, option);
}

void bytebuf::set(std::uint32_t v, packing_option option)
{
	clear();
	push_back(v, option);
}

void bytebuf::set(std::uint64_t v, packing_option option)
{
	clear();
	push_back(v, option);
}

void bytebuf::set(std::int16_t v, packing_option option)
{
	clear();
	push_back(v, option);
}

void bytebuf::set(std::int32_t v, packing_option option)
{
	clear();
	push_back(v, option);
}

void bytebuf::set(std::int64_t v, packing_option option)
{
	clear();
	push_back(v, option);
}

#pragma mark -

void bytebuf::set(const std::uint8_t * membytes, std::size_t length, bool b64dec)
{
	clear();
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i]);
		}
		if (b64dec) {
			b64_decode();
		}
	}
}

void bytebuf::set(const char * membytes, std::size_t length, bool b64dec)
{
	clear();
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i]);
		}
		if (b64dec) {
			b64_decode();
		}
	}
}

#pragma mark -

void bytebuf::set(const std::uint16_t * membytes, std::size_t length, packing_option option)
{
	clear();
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

void bytebuf::set(const std::uint32_t * membytes, std::size_t length, packing_option option)
{
	clear();
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

void bytebuf::set(const std::uint64_t * membytes, std::size_t length, packing_option option)
{
	clear();
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

#pragma mark -

void bytebuf::set(const std::int16_t * membytes, std::size_t length, packing_option option)
{
	clear();
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

void bytebuf::set(const std::int32_t * membytes, std::size_t length, packing_option option)
{
	clear();
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

void bytebuf::set(const std::int64_t * membytes, std::size_t length, packing_option option)
{
	clear();
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

#pragma mark -

void bytebuf::put(const std::uint8_t v, std::size_t index)
{
	if (index < ___M_bytes.size()) {
		___M_bytes[index] = v;
	}
}

void bytebuf::put(const char v, std::size_t index)
{
	if (index < ___M_bytes.size()) {
		___M_bytes[index] = weak_cast<std::uint8_t>(v);
	}
}

#pragma mark -

const std::uint8_t bytebuf::at(std::size_t index) const
{
	if (index < ___M_bytes.size()) {
		return ___M_bytes.at(index);
	}
	return 0x00;
}

#pragma mark -

std::size_t bytebuf::size() const
{
	return ___M_bytes.size();
}

#pragma mark -

std::uint8_t * bytebuf::raw() const
{
	return weak_cast<std::uint8_t *>(___M_bytes.data());
}

const std::vector<std::uint8_t> & bytebuf::bytes() const
{
	return ___M_bytes;
}

#pragma mark -

bool bytebuf::get_raw(std::uint8_t * membytes, std::size_t length) const
{
	return get_raw(membytes, 0, length);
}

bool bytebuf::get_raw(std::uint8_t * membytes, std::size_t location, std::size_t length) const
{
	bool result = false;
	if (membytes) {
		std::vector<std::uint8_t> bv;
		get_bytes(bv, location, length);
		std::uint8_t * rawBytes = bv.data();
		std::size_t len = bv.size();
		if (rawBytes && len) {
			std::memmove(membytes, rawBytes, len);
			result = true;
		}
	}
	return result;
}

bool bytebuf::get_raw(char * membytes, std::size_t length) const
{
	return get_raw(weak_cast<std::uint8_t *>(membytes), 0, length);
}

bool bytebuf::get_raw(char * membytes, std::size_t location, std::size_t length) const
{
	return get_raw(weak_cast<std::uint8_t *>(membytes), location, length);
}

#pragma mark -

bool bytebuf::get_bytes(std::vector<std::uint8_t> & bv) const
{
	return get_bytes(bv, 0, ___M_bytes.size());
}

bool bytebuf::get_bytes(std::vector<std::uint8_t> & bv, std::size_t length) const
{
	return get_bytes(bv, 0, length);
}

bool bytebuf::get_bytes(std::vector<std::uint8_t> & bv, std::size_t location, std::size_t length) const
{
	bool result = false;
	std::size_t sz = ___M_bytes.size();
	if (sz) {
		std::size_t loc, len, max;
		
		irange src(0, sz);
		irange rg(location, length);
		irange dest = src.intxn(rg);
		
		loc = dest.location();
		len = dest.length();
		max = dest.max();
		
		if (loc && len) {
			for (const_iterator it = ___M_bytes.cbegin() + static_cast<difference_type>(loc); it != ___M_bytes.cbegin() + static_cast<difference_type>(max); ++it) {
				bv.push_back((*it));
			}
			result = true;
		}
	}
	return result;
}

#pragma mark -

void bytebuf::push_front(std::uint8_t v)
{
	___M_bytes.insert(___M_bytes.begin(), v);
}

void bytebuf::push_front(char v)
{
	___M_bytes.insert(___M_bytes.begin(), weak_cast<std::uint8_t>(v));
}

#pragma mark -

void bytebuf::push_front(std::uint16_t v, packing_option option)
{
	std::uint8_t pk[2];
	bytebuf::pack(v, pk, option);
	push_front(pk, 2);
}

void bytebuf::push_front(std::uint32_t v, packing_option option)
{
	std::uint8_t pk[4];
	bytebuf::pack(v, pk, option);
	push_front(pk, 4);
}

void bytebuf::push_front(std::uint64_t v, packing_option option)
{
	std::uint8_t pk[8];
	bytebuf::pack(v, pk, option);
	push_front(pk, 8);
}

#pragma mark -

void bytebuf::push_front(std::int16_t v, packing_option option)
{
	std::uint8_t pk[2];
	bytebuf::pack(v, pk, option);
	push_front(pk, 2);
}

void bytebuf::push_front(std::int32_t v, packing_option option)
{
	std::uint8_t pk[4];
	bytebuf::pack(v, pk, option);
	push_front(pk, 4);
}

void bytebuf::push_front(std::int64_t v, packing_option option)
{
	std::uint8_t pk[8];
	bytebuf::pack(v, pk, option);
	push_front(pk, 8);
}

#pragma mark -

void bytebuf::push_front(const std::uint8_t * membytes, std::size_t length)
{
	if (membytes && length) {
		___M_bytes.insert(___M_bytes.begin(), membytes, membytes + length);
	}
}

void bytebuf::push_front(const char * membytes, std::size_t length)
{
	if (membytes && length) {
		___M_bytes.insert(___M_bytes.begin(), membytes, membytes + length);
	}
}

#pragma mark -

void bytebuf::push_front(const std::uint16_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_front(membytes[i], option);
		}
	}
}

void bytebuf::push_front(const std::uint32_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_front(membytes[i], option);
		}
	}
}

void bytebuf::push_front(const std::uint64_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_front(membytes[i], option);
		}
	}
}

#pragma mark -

void bytebuf::push_front(const std::int16_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_front(membytes[i], option);
		}
	}
}

void bytebuf::push_front(const std::int32_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_front(membytes[i], option);
		}
	}
}

void bytebuf::push_front(const std::int64_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_front(membytes[i], option);
		}
	}
}

#pragma mark -

void bytebuf::push_back(std::uint8_t v)
{ ___M_bytes.push_back(v); }

void bytebuf::push_back(char v)
{ ___M_bytes.push_back(weak_cast<std::uint8_t>(v)); }

#pragma mark -

void bytebuf::push_back(std::uint16_t v, packing_option option)
{
	std::uint8_t pk[2];
	bytebuf::pack(v, pk, option);
	push_back(pk, 2);
}

void bytebuf::push_back(std::uint32_t v, packing_option option)
{
	std::uint8_t pk[4];
	bytebuf::pack(v, pk, option);
	push_back(pk, 4);
}

void bytebuf::push_back(std::uint64_t v, packing_option option)
{
	std::uint8_t pk[8];
	bytebuf::pack(v, pk, option);
	push_back(pk, 8);
}

#pragma mark -

void bytebuf::push_back(std::int16_t v, packing_option option)
{
	std::uint8_t pk[2];
	bytebuf::pack(v, pk, option);
	push_back(pk, 2);
}

void bytebuf::push_back(std::int32_t v, packing_option option)
{
	std::uint8_t pk[4];
	bytebuf::pack(v, pk, option);
	push_back(pk, 4);
}

void bytebuf::push_back(std::int64_t v, packing_option option)
{
	std::uint8_t pk[8];
	bytebuf::pack(v, pk, option);
	push_back(pk, 8);
}

#pragma mark -

void bytebuf::push_back(const std::uint8_t * membytes, std::size_t length)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i]);
		}
	}
}

void bytebuf::push_back(const char * membytes, std::size_t length)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i]);
		}
	}
}

#pragma mark -

void bytebuf::push_back(const std::uint16_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

void bytebuf::push_back(const std::uint32_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

void bytebuf::push_back(const std::uint64_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

#pragma mark -

void bytebuf::push_back(const std::int16_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

void bytebuf::push_back(const std::int32_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

void bytebuf::push_back(const std::int64_t * membytes, std::size_t length, packing_option option)
{
	if (membytes && length) {
		for (std::size_t i = 0; i < length; i++) {
			push_back(membytes[i], option);
		}
	}
}

#pragma mark -

void bytebuf::replace(const std::uint8_t * membytes, std::size_t location, std::size_t length)
{
	if (length) {
		if ((location + length) <= ___M_bytes.size()) {
			for (std::size_t i = location, j = 0; i < (location + length) && j < length; i++, j++) {
				___M_bytes[i] = membytes[j];
			}
		}
	}
}

#pragma mark -

void bytebuf::remove(std::size_t index)
{ remove(index, 1); }

void bytebuf::remove(std::size_t location, std::size_t length)
{
	if (length) {
		if ((location + length) <= ___M_bytes.size()) {
			___M_bytes.erase(
				___M_bytes.begin() + static_cast<difference_type>(location),
				___M_bytes.begin() + static_cast<difference_type>(location + length)
			);
		}
	}
}

void bytebuf::remove_last()
{ ___M_bytes.pop_back(); }

#pragma mark -

void bytebuf::reverse()
{ std::reverse(___M_bytes.begin(), ___M_bytes.end()); }

#pragma mark -

std::string bytebuf::to_string() const
{
	std::vector<char> out;
	get_base64(out, chunksplit_none);
	return std::string(out.cbegin(), out.cend());
}
	
#pragma mark -
	
std::size_t bytebuf::hash_code() const
{
	std::string h = hash_sha1();
	if (h.size()) {
		std::size_t x;
		std::stringstream ss;
		ss << std::hex << h;
		ss >> x;
		return x;
	}
	return 0;
}

#pragma mark -

std::string bytebuf::to_b64string(chunksplit_option option) const
{
	std::string out;
	if (___M_bytes.size()) {
		base64::encode(___M_bytes.begin(), ___M_bytes.end(), std::back_inserter(out), option);
	}
	return out;
}

void bytebuf::b64_encode(chunksplit_option option)
{
	if (___M_bytes.size()) {
		std::vector<char> out;
		base64::encode(___M_bytes.begin(), ___M_bytes.end(), std::back_inserter(out), option);
		___M_bytes.clear();
		___M_bytes.assign(out.begin(), out.end());
		out.clear();
	}
}

void bytebuf::b64_decode()
{
	if (___M_bytes.size()) {
		std::vector<char> out;
		base64::decode(___M_bytes.begin(), ___M_bytes.end(), std::back_inserter(out));
		___M_bytes.clear();
		___M_bytes.assign(out.begin(), out.end());
		out.clear();
	}
}

bool bytebuf::get_base64(std::vector<char> & out, chunksplit_option option) const
{
	bool result = false;
	base64::encode(___M_bytes.begin(), ___M_bytes.end(), std::back_inserter(out), option);
	if (out.size()) {
		result = true;
	}
	return result;
}

#pragma mark -

std::string bytebuf::hash_sha1() const
{
	if (___M_bytes.size()) {
		hash::sha1 h;
		h.add(___M_bytes.data(), ___M_bytes.size());
		return { h.hex().data() };
	}
	return {};
}

std::string bytebuf::hash_sha256() const
{
	if (___M_bytes.size()) {
		hash::sha256 h;
		h.add(___M_bytes.data(), ___M_bytes.size());
		return { h.hex().data() };
	}
	return {};
}

#pragma mark -

void bytebuf::clear()
{ ___M_bytes.clear(); }

void bytebuf::reset()
{ ___M_bytes.clear(); }

#pragma mark -

bool bytebuf::write(stream::ofstream & out_binary) const
{ return wb_fout(out_binary); }

bool bytebuf::write(const upath & path, bool atomically) const
{
	COCONUT_UNUSED(atomically);
	bool result = false;
	stream::ofstream out_binary(path.to_utf8_string());
	if (out_binary.is_open()) {
		result = wb_fout(out_binary);
		out_binary.close();
	}
	return result;
}

bool bytebuf::write(const uri & url, bool atomically) const
{
	COCONUT_UNUSED(atomically);
	bool result = false;
	if (url.is_file_url()) {
		upath path(url.path());
		stream::ofstream out_binary(path.to_utf8_string());
		if (out_binary.is_open()) {
			result = wb_fout(out_binary);
			out_binary.close();
		}
	}
	return result;
}

#pragma mark -

const std::uint8_t & bytebuf::operator [] (std::size_t index) const { return ___M_bytes[index]; }

bytebuf & bytebuf::operator + (std::uint8_t v) { push_back(v); return *this; };
bytebuf & bytebuf::operator += (std::uint8_t v) { push_back(v); return *this; };

bytebuf & bytebuf::operator + (char v) { push_back(v); return *this; };
bytebuf & bytebuf::operator += (char v) { push_back(v); return *this; };

#pragma mark -

bytebuf::iterator bytebuf::begin() { return ___M_bytes.begin(); }
bytebuf::iterator bytebuf::end() { return ___M_bytes.end(); }

bytebuf::const_iterator bytebuf::begin() const { return ___M_bytes.begin(); }
bytebuf::const_iterator bytebuf::end() const { return ___M_bytes.end(); }

bytebuf::const_iterator bytebuf::cbegin() const { return ___M_bytes.cbegin(); }
bytebuf::const_iterator bytebuf::cend() const { return ___M_bytes.cend(); }

bytebuf::reverse_iterator bytebuf::rbegin() { return ___M_bytes.rbegin(); }
bytebuf::reverse_iterator bytebuf::rend() { return ___M_bytes.rend(); }

bytebuf::const_reverse_iterator bytebuf::rbegin() const { return ___M_bytes.rbegin(); }
bytebuf::const_reverse_iterator bytebuf::rend() const { return ___M_bytes.rend(); }

bytebuf::const_reverse_iterator bytebuf::crbegin() const { return ___M_bytes.crbegin(); }
bytebuf::const_reverse_iterator bytebuf::crend() const { return ___M_bytes.crend(); }

/* EOF */