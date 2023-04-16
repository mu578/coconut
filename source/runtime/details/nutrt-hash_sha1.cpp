//
// nutrt-hash-sha1.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/nutrt-hash.hpp>
#include <coconut/runtime/details/nutrt-byteorder.hpp>

using namespace coconut::runtime;

#include <source/runtime/builtins/nutrt-hash_sha1_func.hxx>

hash::sha1::sha1()
: sha_base(512 / 8, 5)
{ reset(); }

hash::sha1::~sha1()
{ /* NOP */ }

#pragma mark -

void hash::sha1::reset()
{
	___M_nbytes = 0;
	___M_bufsize = 0;
	___M_hash[0] = 0x67452301;
	___M_hash[1] = 0xEFCDAB89;
	___M_hash[2] = 0x98BADCFE;
	___M_hash[3] = 0x10325476;
	___M_hash[4] = 0xC3D2E1F0;
}

#pragma mark -

void hash::sha1::process_block(const void * block)
{
	const std::uint32_t * input = weak_cast<const std::uint32_t *>(block);
	std::uint32_t words[80];
	std::size_t i = 0;
	std::uint32_t a = ___M_hash[0];
	std::uint32_t b = ___M_hash[1];
	std::uint32_t c = ___M_hash[2];
	std::uint32_t d = ___M_hash[3];
	std::uint32_t e = ___M_hash[4];
	
	for (; i < 16; i++) {
		words[i] = runtime::byteorder::h2be32(input[i]);
	}
	
	for (i = 16; i < 80; i++) {
		words[i] = builtins::___F_hash_sha1_rot(words[i - 3]
			^ words[i - 8]
			^ words[i - 14]
			^ words[i - 16],
		1);
	}
	
	for (i = 0; i < 4; i++) {
		std::size_t offset = 5 * i;
		e += builtins::___F_hash_sha1_rot(a, 5)
			+ builtins::___F_hash_sha1_f1(b, c, d)
			+ words[offset + 0] + 0x5A827999;
		b = builtins::___F_hash_sha1_rot(b, 30);
		d += builtins::___F_hash_sha1_rot(e, 5)
			+ builtins::___F_hash_sha1_f1(a, b, c)
			+ words[offset + 1] + 0x5A827999;
		a = builtins::___F_hash_sha1_rot(a, 30);
		c += builtins::___F_hash_sha1_rot(d, 5)
			+ builtins::___F_hash_sha1_f1(e, a, b)
			+ words[offset + 2] + 0x5A827999;
		e = builtins::___F_hash_sha1_rot(e, 30);
		b += builtins::___F_hash_sha1_rot(c, 5)
			+ builtins::___F_hash_sha1_f1(d, e, a)
			+ words[offset + 3] + 0x5A827999;
		d = builtins::___F_hash_sha1_rot(d, 30);
		a += builtins::___F_hash_sha1_rot(b, 5)
			+ builtins::___F_hash_sha1_f1(c, d, e)
			+ words[offset + 4] + 0x5A827999;
		c = builtins::___F_hash_sha1_rot(c, 30);
	}
	
	for (i = 4; i < 8; i++) {
		std::size_t offset = 5 * i;
		e += builtins::___F_hash_sha1_rot(a, 5)
			+ builtins::___F_hash_sha1_f2(b, c, d)
			+ words[offset + 0] + 0x6ED9EBA1;
		b = builtins::___F_hash_sha1_rot(b, 30);
		d += builtins::___F_hash_sha1_rot(e, 5)
			+ builtins::___F_hash_sha1_f2(a, b, c)
			+ words[offset + 1] + 0x6ED9EBA1;
		a = builtins::___F_hash_sha1_rot(a, 30);
		c += builtins::___F_hash_sha1_rot(d, 5)
			+ builtins::___F_hash_sha1_f2(e, a, b)
			+ words[offset + 2] + 0x6ED9EBA1;
		e = builtins::___F_hash_sha1_rot(e, 30);
		b += builtins::___F_hash_sha1_rot(c, 5)
			+ builtins::___F_hash_sha1_f2(d, e, a)
			+ words[offset + 3] + 0x6ED9EBA1;
		d = builtins::___F_hash_sha1_rot(d, 30);
		a += builtins::___F_hash_sha1_rot(b, 5)
			+ builtins::___F_hash_sha1_f2(c, d, e)
			+ words[offset + 4] + 0x6ED9EBA1;
		c = builtins::___F_hash_sha1_rot(c, 30);
	}
	
	for (i = 8; i < 12; i++) {
		std::size_t offset = 5 * i;
		e += builtins::___F_hash_sha1_rot(a, 5)
			+ builtins::___F_hash_sha1_f3(b, c, d)
			+ words[offset + 0] + 0x8F1BBCDC;
		b = builtins::___F_hash_sha1_rot(b, 30);
		d += builtins::___F_hash_sha1_rot(e, 5)
			+ builtins::___F_hash_sha1_f3(a, b, c)
			+ words[offset + 1] + 0x8F1BBCDC;
		a = builtins::___F_hash_sha1_rot(a, 30);
		c += builtins::___F_hash_sha1_rot(d, 5)
			+ builtins::___F_hash_sha1_f3(e, a, b)
			+ words[offset + 2] + 0x8F1BBCDC;
		e = builtins::___F_hash_sha1_rot(e, 30);
		b += builtins::___F_hash_sha1_rot(c, 5)
			+ builtins::___F_hash_sha1_f3(d, e, a)
			+ words[offset + 3] + 0x8F1BBCDC;
		d = builtins::___F_hash_sha1_rot(d, 30);
		a += builtins::___F_hash_sha1_rot(b, 5)
			+ builtins::___F_hash_sha1_f3(c, d, e)
			+ words[offset + 4] + 0x8F1BBCDC;
		c = builtins::___F_hash_sha1_rot(c, 30);
	}
	
	for (i = 12; i < 16; i++) {
		std::size_t offset = 5 * i;
		e += builtins::___F_hash_sha1_rot(a, 5)
			+ builtins::___F_hash_sha1_f2(b, c, d)
			+ words[offset + 0] + 0xCA62C1D6;
		b = builtins::___F_hash_sha1_rot(b, 30);
		d += builtins::___F_hash_sha1_rot(e, 5)
			+ builtins::___F_hash_sha1_f2(a, b, c)
			+ words[offset + 1] + 0xCA62C1D6;
		a = builtins::___F_hash_sha1_rot(a, 30);
		c += builtins::___F_hash_sha1_rot(d, 5)
			+ builtins::___F_hash_sha1_f2(e, a, b)
			+ words[offset + 2] + 0xCA62C1D6;
		e = builtins::___F_hash_sha1_rot(e, 30);
		b += builtins::___F_hash_sha1_rot(c, 5)
			+ builtins::___F_hash_sha1_f2(d, e, a)
			+ words[offset + 3] + 0xCA62C1D6;
		d = builtins::___F_hash_sha1_rot(d, 30);
		a += builtins::___F_hash_sha1_rot(b, 5)
			+ builtins::___F_hash_sha1_f2(c, d, e)
			+ words[offset + 4] + 0xCA62C1D6;
		c = builtins::___F_hash_sha1_rot(c, 30);
	}
	
	___M_hash[0] += a;
	___M_hash[1] += b;
	___M_hash[2] += c;
	___M_hash[3] += d;
	___M_hash[4] += e;
}

/* EOF */