//
// nutrt-byteorder.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>

#ifndef COCONUT_RUNTIME_BYTEORDER_HPP
#define COCONUT_RUNTIME_BYTEORDER_HPP

namespace coconut
{ namespace runtime
{ namespace byteorder
{
	
#pragma mark -
	
typedef struct { std::uint32_t v; } fswp_t;
typedef struct { std::uint64_t v; } dswp_t;
	
template <typename T>
inline void swpi(T & x)
{ char & raw = reinterpret_cast<char &>(x); std::reverse(&raw, &raw + sizeof(T)); }

template <typename T>
inline T swpc(T x)
{ swpi(x); return x; }
	
#pragma mark -
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint16_t swpc16(const volatile std::uint16_t x)
{ return ___COCONUT_bswap16(x); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int16_t swpcs16(std::int16_t & x)
{ return ___COCONUT_bswap16(x); }

#pragma mark -
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t swpc32(const volatile std::uint32_t x)
{ return ___COCONUT_bswap32(x); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int32_t swpcs32(std::int32_t & x)
{ return ___COCONUT_bswap32(x); }
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint64_t swpc64(const volatile std::uint64_t x)
{ return ___COCONUT_bswap64(x); }

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::int64_t swpcs64(std::int64_t & x)
{ return ___COCONUT_bswap64(x); }

#pragma mark -
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void r16be(const std::uint8_t (&r)[2], std::uint16_t & out)
{
	std::uint16_t x = 0;
	x |= weak_cast<std::uint16_t>(r[0]) << 8;
	x |= r[1];
	out = x;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void rs16be(const std::uint8_t (&r)[2], std::int16_t & out)
{
	std::uint16_t x = 0;
	x |= weak_cast<std::uint16_t>(r[0]) << 8;
	x |= r[1];
	out = x;
}
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void r32be(const std::uint8_t (&r)[4], std::uint32_t & out)
{
	std::uint32_t x = 0;
	x |= weak_cast<std::uint32_t>(r[0]) << 24;
	x |= weak_cast<std::uint32_t>(r[1]) << 16;
	x |= weak_cast<std::uint32_t>(r[2]) << 8;
	x |= r[3];
	out = x;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void rs32be(const std::uint8_t (&r)[4], std::int32_t & out)
{
	std::uint32_t x = 0;
	x |= weak_cast<std::uint32_t>(r[0]) << 24;
	x |= weak_cast<std::uint32_t>(r[1]) << 16;
	x |= weak_cast<std::uint32_t>(r[2]) << 8;
	x |= r[3];
	out = x;
}
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void r64be(const std::uint8_t (&r)[8], std::uint64_t & out)
{
	std::uint64_t x = 0;
	x |= weak_cast<std::uint64_t>(r[0]) << 56;
	x |= weak_cast<std::uint64_t>(r[1]) << 48;
	x |= weak_cast<std::uint64_t>(r[2]) << 40;
	x |= weak_cast<std::uint64_t>(r[3]) << 32;
	x |= r[4] << 24;
	x |= r[5] << 16;
	x |= r[6] << 8;
	x |= r[7];
	out = x;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void rs64be(const std::uint8_t (&r)[8], std::int64_t & out)
{
	std::uint64_t x = 0;
	x |= weak_cast<std::uint64_t>(r[0]) << 56;
	x |= weak_cast<std::uint64_t>(r[1]) << 48;
	x |= weak_cast<std::uint64_t>(r[2]) << 40;
	x |= weak_cast<std::uint64_t>(r[3]) << 32;
	x |= r[4] << 24;
	x |= r[5] << 16;
	x |= r[6] << 8;
	x |= r[7];
	out = x;
}
	
#pragma mark -
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void r16le(const std::uint8_t (&r)[2], std::uint16_t & out)
{
	std::uint16_t x = 0;
	x |= weak_cast<std::uint16_t>(r[1]) << 8;
	x |= r[0];
	out = x;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void rs16le(const std::uint8_t (&r)[2], std::int16_t & out)
{
	std::uint16_t x = 0;
	x |= weak_cast<std::uint16_t>(r[1]) << 8;
	x |= r[0];
	out = x;
}
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void r32le(const std::uint8_t (&r)[4], std::uint32_t & out)
{
	std::uint32_t x = 0;
	x |= weak_cast<std::uint32_t>(r[3]) << 24;
	x |= weak_cast<std::uint32_t>(r[2]) << 16;
	x |= weak_cast<std::uint32_t>(r[1]) << 8;
	x |= r[0];
	out = x;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void rs32le(const std::uint8_t (&r)[4], std::int32_t & out)
{
	std::uint32_t x = 0;
	x |= weak_cast<std::uint32_t>(r[3]) << 24;
	x |= weak_cast<std::uint32_t>(r[2]) << 16;
	x |= weak_cast<std::uint32_t>(r[1]) << 8;
	x |= r[0];
	out = x;
}
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void r64le(const std::uint8_t (&r)[8], std::uint64_t & out)
{
	std::uint64_t x = 0;
	x |= weak_cast<std::uint64_t>(r[7]) << 56;
	x |= weak_cast<std::uint64_t>(r[6]) << 48;
	x |= weak_cast<std::uint64_t>(r[5]) << 40;
	x |= weak_cast<std::uint64_t>(r[4]) << 32;
	x |= r[3] << 24;
	x |= r[2] << 16;
	x |= r[1] << 8;
	x |= r[0];
	out = x;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void rs64le(const std::uint8_t (&r)[8], std::int64_t & out)
{
	std::uint64_t x = 0;
	x |= weak_cast<std::uint64_t>(r[7]) << 56;
	x |= weak_cast<std::uint64_t>(r[6]) << 48;
	x |= weak_cast<std::uint64_t>(r[5]) << 40;
	x |= weak_cast<std::uint64_t>(r[4]) << 32;
	x |= r[3] << 24;
	x |= r[2] << 16;
	x |= r[1] << 8;
	x |= r[0];
	out = x;
}

#pragma mark -
#pragma mark -
#pragma mark -
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void w16be(std::uint16_t in, std::uint8_t (&w)[2])
{
	w[0] = ((in >> 8) & 0xFF);
	w[1] = (in & 0xFF);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void w32be(std::uint32_t in, std::uint8_t (&w)[4])
{
	w[0] = ((in & 0xFF000000UL) >> 24);
	w[1] = ((in & 0x00FF0000UL) >> 16);
	w[2] = ((in & 0x0000FF00UL) >> 8);
	w[3] = ((in & 0x000000FFUL));
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void w64be(std::uint64_t in, std::uint8_t (&w)[8])
{
	w[0] = ((in & 0xFF00000000000000ULL) >> 56);
	w[1] = ((in & 0x00FF000000000000ULL) >> 48);
	w[2] = ((in & 0x0000FF0000000000ULL) >> 40);
	w[3] = ((in & 0x000000FF00000000ULL) >> 32);
	w[4] = ((in & 0x00000000FF000000ULL) >> 24);
	w[5] = ((in & 0x0000000000FF0000ULL) >> 16);
	w[6] = ((in & 0x000000000000FF00ULL) >> 8);
	w[7] = ((in & 0x00000000000000FFULL));
}
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void w16le(std::uint16_t in, std::uint8_t (&w)[2])
{
	w[0] = (in & 0xFF);
	w[1] = ((in >> 8) & 0xFF);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void w32le(std::uint32_t in, std::uint8_t (&w)[4])
{
	w[0] = ((in & 0x000000FFUL));
	w[1] = ((in & 0x0000FF00UL) >> 8);
	w[2] = ((in & 0x00FF0000UL) >> 16);
	w[3] = ((in & 0xFF000000UL) >> 24);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void w64le(std::uint64_t in, std::uint8_t (&w)[8])
{
	w[0] = ((in & 0x00000000000000FFULL));
	w[1] = ((in & 0x000000000000FF00ULL) >> 8);
	w[2] = ((in & 0x0000000000FF0000ULL) >> 16);
	w[3] = ((in & 0x00000000FF000000ULL) >> 24);
	w[4] = ((in & 0x000000FF00000000ULL) >> 32);
	w[5] = ((in & 0x0000FF0000000000ULL) >> 40);
	w[6] = ((in & 0x00FF000000000000ULL) >> 48);
	w[7] = ((in & 0xFF00000000000000ULL) >> 56);
}
	
#pragma mark -
#pragma mark -
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint16_t be2h16(std::uint16_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapBigToHostInt16(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return swpc16(x);
#else
	return x;
#endif
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t be2h32(std::uint32_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapBigToHostInt32(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return swpc32(x);
#else
	return x;
#endif
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint64_t be2h64(std::uint64_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapBigToHostInt64(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return swpc64(x);
#else
	return x;
#endif
}
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint16_t h2be16(std::uint16_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapHostToBigInt16(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return swpc16(x);
#else
	return x;
#endif
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t h2be32(std::uint32_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapHostToBigInt32(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return swpc32(x);
#else
	return x;
#endif
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint64_t h2be64(std::uint64_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapHostToBigInt64(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return swpc64(x);
#else
	return x;
#endif
}
	
#pragma mark -
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint16_t le2h16(std::uint16_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapLittleToHostInt16(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return x;
#else
	return swapc16(x);
#endif
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t le2h32(std::uint32_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapLittleToHostInt32(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return x;
#else
	return swapc32(x);
#endif
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint64_t le2h64(std::uint64_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapLittleToHostInt64(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return x;
#else
	return swapc64(x);
#endif
}
	
#pragma mark -

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint16_t h2le16(std::uint16_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapHostToLittleInt16(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return x;
#else
	return swapc16(x);
#endif
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint32_t h2le32(std::uint32_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapHostToLittleInt32(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return x;
#else
	return swapc32(x);
#endif
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::uint64_t h2le64(std::uint64_t x)
{
#if defined(__APPLE__) && !defined(__clang__)
	return OSSwapHostToLittleInt64(x);
#elif COCONUT_ARCH_LITTLE_ENDIAN
	return x;
#else
	return swapc64(x);
#endif
}

#pragma mark -
	
}}} /* EONS */

#endif /* !COCONUT_RUNTIME_BYTEORDER_HPP */

/* EOF */