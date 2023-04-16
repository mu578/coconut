//
// nutrt-hash-sha_base.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/nutrt-hash.hpp>
#include <coconut/runtime/details/nutrt-byteorder.hpp>

using namespace coconut::runtime;

#include <source/runtime/builtins/nutrt-hash_sha_base.hxx>

#pragma mark -

// //////////////////////////////////////////////////////////
// @based on sha1.cpp, sha256.cpp
// Copyright (c) 2014 Stephan Brumme. All rights reserved.
// @see http://create.stephan-brumme.com/disclaimer.html
//

hash::sha_base::sha_base()
: ___M_blocksize(0)
, ___M_digestsize(0)
, ___M_nbytes(0)
, ___M_bufsize(0)
, ___M_buf(nullptr)
, ___M_bufextra(nullptr)
, ___M_hash(nullptr)
{ /* NOP */ }

hash::sha_base::sha_base(std::size_t blocksize, std::size_t digestsize)
: ___M_blocksize(blocksize)
, ___M_digestsize(digestsize)
, ___M_nbytes(0)
, ___M_bufsize(0)
, ___M_buf(nullptr)
, ___M_bufextra(nullptr)
, ___M_hash(nullptr)
{
	___M_buf = new std::uint8_t[___M_blocksize];
	___M_bufextra = new std::uint8_t[___M_blocksize];
	___M_hash = new std::uint32_t[___M_digestsize];
}

hash::sha_base::~sha_base()
{
	if (___M_buf) {
		delete [] ___M_buf;
		___M_buf = nullptr;
	}
	if (___M_bufextra) {
		delete [] ___M_bufextra;
		___M_bufextra = nullptr;
	}
	if (___M_hash) {
		delete [] ___M_hash;
		___M_hash = nullptr;
	}
}

#pragma mark -

void hash::sha_base::add(const void * bytes, std::size_t length)
{
	const std::uint8_t * current = weak_cast<const std::uint8_t *>(bytes);

	if (___M_bufsize > 0) {
		while (length > 0 && ___M_bufsize < ___M_blocksize) {
			___M_buf[___M_bufsize++] = *current++;
			length--;
		}
	}

	if (___M_bufsize == ___M_blocksize) {
		process_block(___M_buf);
		___M_nbytes += ___M_blocksize;
		___M_bufsize = 0;
	}
	
	if (length == 0) {
		return;
	}

	while (length >= ___M_blocksize) {
		process_block(current);
		current += ___M_blocksize;
		___M_nbytes += ___M_blocksize;
		length -= ___M_blocksize;
	}

	while (length > 0) {
		___M_buf[___M_bufsize++] = *current++;
		length--;
	}
}

const std::vector<char> hash::sha_base::hex(bool uppercase)
{
	std::string result;
	static const char dec2hex_lc[] = "0123456789abcdef";
	static const char dec2hex_uc[] = "0123456789ABCDEF";
	const char * dec2hex = uppercase ? dec2hex_uc : dec2hex_lc;

	std::vector<std::uint32_t> old_hash(___M_digestsize);
	std::vector<char> hash_buf(___M_digestsize * 8 + 1);
	std::size_t offset = 0;
	
	for (std::size_t i = 0; i < ___M_digestsize; i++) {
		old_hash[i] = ___M_hash[i];
	}
	
	process_buffer();
	
	for (std::size_t i = 0; i < ___M_digestsize; i++) {
		hash_buf[offset++] = dec2hex[(___M_hash[i] >> 28) & 15];
		hash_buf[offset++] = dec2hex[(___M_hash[i] >> 24) & 15];
		hash_buf[offset++] = dec2hex[(___M_hash[i] >> 20) & 15];
		hash_buf[offset++] = dec2hex[(___M_hash[i] >> 16) & 15];
		hash_buf[offset++] = dec2hex[(___M_hash[i] >> 12) & 15];
		hash_buf[offset++] = dec2hex[(___M_hash[i] >> 8) & 15];
		hash_buf[offset++] = dec2hex[(___M_hash[i] >> 4) & 15];
		hash_buf[offset++] = dec2hex[___M_hash[i] & 15];
		___M_hash[i] = old_hash[i];
	}
	hash_buf[offset] = 0;
	hash_buf.resize(offset);
	hash_buf.pop_back();
	
	return hash_buf;
}

const std::vector<std::uint8_t> hash::sha_base::raw()
{
	std::vector<std::uint32_t> old_hash(___M_digestsize);
	std::vector<std::uint8_t> hash_buf(___M_digestsize * sizeof(std::uint32_t));
	std::size_t offset = 0;
	std::size_t i;
	
	for (i = 0; i < ___M_digestsize; i++) {
		old_hash[i] = ___M_hash[i];
	}
	
	process_buffer();

	for (i = 0 ; i < ___M_digestsize ; i++) {
		std::uint32_t v = ___M_hash[i];
		hash_buf[offset + 0] = (v & 0xFF000000) >> 24;
		hash_buf[offset + 1] = (v & 0x00FF0000) >> 16;
		hash_buf[offset + 2] = (v & 0x0000FF00) >> 8;
		hash_buf[offset + 3] = (v & 0x000000FF);
		offset += sizeof(std::uint32_t);
	}

	for (i = 0; i < ___M_digestsize; i++) {
		___M_hash[i] = old_hash[i];
	}

	return hash_buf;
}

#pragma mark -

void hash::sha_base::process_buffer()
{
	std::size_t padded_len;
	std::size_t i;
	std::size_t lower11bits;
	std::uint64_t msgbits;
	std::uint8_t * add_len;
	
	padded_len = ___M_bufsize * 8;
	padded_len++;
	lower11bits = padded_len & 511;

	std::memset(___M_bufextra, 0, ___M_blocksize);
	
	if (lower11bits <= 448) {
		padded_len += 448 - lower11bits;
	} else {
		padded_len += 512 + 448 - lower11bits;
	}
	padded_len /= 8;
	
	if (___M_bufsize < ___M_blocksize) {
		___M_buf[___M_bufsize] = 128;
	} else {
		___M_bufextra[0] = 128;
	}
	
	for (i = ___M_bufsize + 1; i < ___M_blocksize; i++) {
		___M_buf[i] = 0;
	}
	
	for (; i < padded_len; i++) {
		___M_bufextra[i - ___M_blocksize] = 0;
	}
	
	msgbits = 8 * (___M_nbytes + ___M_bufsize);
	
	if (padded_len < ___M_blocksize) {
		add_len = ___M_buf + padded_len;
	} else {
		add_len = ___M_bufextra + padded_len - ___M_blocksize;
	}
	
	*add_len++ = (msgbits >> 56) & 0xFF;
	*add_len++ = (msgbits >> 48) & 0xFF;
	*add_len++ = (msgbits >> 40) & 0xFF;
	*add_len++ = (msgbits >> 32) & 0xFF;
	*add_len++ = (msgbits >> 24) & 0xFF;
	*add_len++ = (msgbits >> 16) & 0xFF;
	*add_len++ = (msgbits >> 8) & 0xFF;
	*add_len = msgbits & 0xFF;

	process_block(___M_buf);

	if (padded_len > ___M_blocksize) {
		process_block(___M_bufextra);
	}
}

const std::vector<char> hash::sha1_hex(const void * bytes, std::size_t len)
{
	sha1 h;
	h.add(bytes, len);
	return h.hex();
}

const std::vector<char> hash::sha1_hex(stream::imstream & in_binary)
{
	sha1 h;
	builtins::___F_hash_sha_hex(in_binary, &h);
	return h.hex();
}

const std::vector<char> hash::sha1_hex(stream::ifstream & in_binary)
{
	sha1 h;
	if (in_binary.is_open()) {
		builtins::___F_hash_sha_hex(in_binary, &h);
	}
	return h.hex();
}

#pragma mark -

const std::vector<std::uint8_t> hash::sha1_raw(const void * bytes, std::size_t len)
{
	sha1 h;
	h.add(bytes, len);
	return h.raw();
}

const std::vector<std::uint8_t> hash::sha1_raw(stream::imstream & in_binary)
{
	sha1 h;
	builtins::___F_hash_sha_hex(in_binary, &h);
	return h.raw();
}

const std::vector<std::uint8_t> hash::sha1_raw(stream::ifstream & in_binary)
{
	sha1 h;
	if (in_binary.is_open()) {
		builtins::___F_hash_sha_hex(in_binary, &h);
	}
	return h.raw();
}

#pragma mark -

const std::vector<char> hash::sha256_hex(const void * bytes, std::size_t len)
{
	sha256 h;
	h.add(bytes, len);
	return h.hex();
}

const std::vector<char> hash::sha256_hex(stream::imstream & in_binary)
{
	sha256 h;
	builtins::___F_hash_sha_hex(in_binary, &h);
	return h.hex();
}

const std::vector<char> hash::sha256_hex(stream::ifstream & in_binary)
{
	sha256 h;
	if (in_binary.is_open()) {
		builtins::___F_hash_sha_hex(in_binary, &h);
	}
	return h.hex();
}

#pragma mark -

const std::vector<std::uint8_t> hash::sha256_raw(const void * bytes, std::size_t len)
{
	sha256 h;
	h.add(bytes, len);
	return h.raw();
}

const std::vector<std::uint8_t> hash::sha256_raw(stream::imstream & in_binary)
{
	sha256 h;
	builtins::___F_hash_sha_hex(in_binary, &h);
	return h.raw();
}

const std::vector<std::uint8_t> hash::sha256_raw(stream::ifstream & in_binary)
{
	sha256 h;
	if (in_binary.is_open()) {
		builtins::___F_hash_sha_hex(in_binary, &h);
	}
	return h.raw();
}

/* EOF */