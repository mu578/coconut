//
// Data.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Data.hpp>
#include <coconut/foundation/Path.hpp>
#include <coconut/foundation/Range.hpp>
#include <coconut/foundation/String.hpp>
#include <coconut/foundation/URL.hpp>

using namespace coconut;

Data::Data() :
	Object(DataClass),
	___M_impl()
{ /* NOP */ }

Data::Data(const Data & dat) :
	Object(DataClass),
	___M_impl(dat.___M_impl)
{ /* NOP */ }

Data::Data(Data && dat) noexcept :
	Object(DataClass),
	___M_impl(std::move(dat.___M_impl))
{ /* NOP */ }

Data::Data(const Data & dat, bool b64_decode) :
	Object(DataClass),
	___M_impl(dat.___M_impl, b64_decode)
{ /* NOP */ }

Data::Data(Data && dat, bool b64_decode) noexcept :
	Object(DataClass),
	___M_impl(std::move(dat.___M_impl), b64_decode)
{ /* NOP */ }

Data::Data(const std::uint8_t * in, std::size_t length, bool b64_decode) :
	Object(DataClass),
	___M_impl(in, length, b64_decode)
{ /* NOP */ }

Data::Data(const char * in, std::size_t length, bool b64_decode) :
	Object(DataClass),
	___M_impl(in, length, b64_decode)
{ /* NOP */ }

Data::Data(const std::uint16_t * in, std::size_t length, DataPackingOption option) :
	Object(DataClass),
	___M_impl(in, length, option)
{ /* NOP */ }

Data::Data(const std::uint32_t * in, std::size_t length, DataPackingOption option) :
	Object(DataClass),
	___M_impl(in, length, option)
{ /* NOP */ }

Data::Data(const std::uint64_t * in, std::size_t length, DataPackingOption option) :
	Object(DataClass),
	___M_impl(in, length, option)
{ /* NOP */ }

Data::Data(const std::int16_t * in, std::size_t length, DataPackingOption option) :
	Object(DataClass),
	___M_impl(in, length, option)
{ /* NOP */ }

Data::Data(const std::int32_t * in, std::size_t length, DataPackingOption option) :
	Object(DataClass),
	___M_impl(in, length, option)
{ /* NOP */ }

Data::Data(const std::int64_t * in, std::size_t length, DataPackingOption option) :
	Object(DataClass),
	___M_impl(in, length, option)
{ /* NOP */ }

Data::Data(const Path & path, bool b64_decode) :
	Object(DataClass),
	___M_impl(path.___M_impl, b64_decode)
{ /* NOP */ }

Data::Data(const URL & url, bool b64_decode) :
	Object(DataClass),
	___M_impl(url.___M_impl, b64_decode)
{ /* NOP */ }

Data::~Data()
{ ___M_impl.clear(); }

#pragma mark -

std::size_t Data::hash() const
{ return ___M_impl.hash_code(); }

#pragma mark -

Owning<Any> Data::copy() const
{ return ptr_create<Data>(*this); }

#pragma mark -

ComparisonResult Data::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return ___M_impl.compare(ref_cast<Data>(ref).___M_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string Data::stringValue() const
{ return ___M_impl.to_string(); }

#pragma mark -

std::size_t Data::size() const
{ return ___M_impl.size(); }

#pragma mark -

const std::uint8_t * Data::bytes() const
{ return ___M_impl.raw(); }

#pragma mark -

bool Data::getBytes(std::uint8_t * buf, std::size_t length) const
{
	if (buf) {
		___M_impl.get_raw(buf, length);
		return true;
	}
	return false;
}

bool Data::getBytes(std::uint8_t * buf, const Range & rg) const
{
	if (buf) {
		___M_impl.get_raw(buf, rg.location(), rg.length());
		return true;
	}
	return false;
}

bool Data::getBytes(std::uint8_t * buf, std::size_t location, std::size_t length) const
{
	if (buf) {
		___M_impl.get_raw(buf, location, length);
		return true;
	}
	return false;
}

#pragma mark -

bool Data::getBytes(char * buf, std::size_t length) const
{
	if (buf) {
		___M_impl.get_raw(buf, length);
		return true;
	}
	return false;
}

bool Data::getBytes(char * buf, const Range & rg) const
{
	if (buf) {
		___M_impl.get_raw(buf, rg.location(), rg.length());
		return true;
	}
	return false;
}

bool Data::getBytes(char * buf, std::size_t location, std::size_t length) const
{
	if (buf) {
		___M_impl.get_raw(buf, location, length);
		return true;
	}
	return false;
}

#pragma mark -

bool Data::getBytes(std::vector<std::uint8_t> & bv) const
{
	___M_impl.get_bytes(bv);
	return (bv.size() != 0);
}

bool Data::getBytes(std::vector<std::uint8_t> & bv, std::size_t length) const
{
	___M_impl.get_bytes(bv, length);
	return (bv.size() == length);
}

bool Data::getBytes(std::vector<std::uint8_t> & bv, const Range & rg) const
{
	___M_impl.get_bytes(bv, rg.location(), rg.length());
	return (bv.size() == (rg.length() - rg.location()));
}

bool Data::getBytes(std::vector<std::uint8_t> & bv, std::size_t location, std::size_t length) const
{
	___M_impl.get_bytes(bv, location, length);
	return (bv.size() == (length - location));
}

#pragma mark -

const Data Data::base64EncodedData(ChunkSplitOption option) const
{
	std::vector<char> out;
	___M_impl.get_base64(out, option);
	return {out.begin(), out.end(), false};
}

#pragma mark -

const Data Data::subdataWithRange(const Range & rg) const
{
	std::vector<std::uint8_t> bv;
	getBytes(bv, rg);
	return {bv.data(), bv.size()};
}

const Data Data::subdataWithRange(std::size_t location, std::size_t length) const
{ return subdataWithRange(Range(location, length)); }

#pragma mark -

const std::string Data::sha1Value() const
{ return ___M_impl.hash_sha1(); }

const std::string Data::sha256Value() const
{ return ___M_impl.hash_sha256(); }

#pragma mark -

bool Data::writeToFile(const Path & path, bool atomically) const
{ return ___M_impl.write(path.___M_impl, atomically); }

bool Data::writeToURL(const URL & url, bool atomically) const
{
	if (url.isFileURL()) {
		return writeToFile(url.fileSystemRepresentation(), atomically);
	}
	return false;
}

#pragma mark -

const std::uint8_t Data::operator [] (std::size_t index) const
{ return ___M_impl.at(index); }

#pragma mark -

Data::iterator Data::begin() { return ___M_impl.begin(); }
Data::iterator Data::end() { return ___M_impl.end(); }

Data::const_iterator Data::begin() const { return ___M_impl.begin(); }
Data::const_iterator Data::end() const { return ___M_impl.end(); }

Data::const_iterator Data::cbegin() const { return ___M_impl.cbegin(); }
Data::const_iterator Data::cend() const { return ___M_impl.cend(); }

Data::reverse_iterator Data::rbegin() { return ___M_impl.rbegin(); }
Data::reverse_iterator Data::rend() { return ___M_impl.rend(); }

Data::const_reverse_iterator Data::rbegin() const { return ___M_impl.rbegin(); }
Data::const_reverse_iterator Data::rend() const { return ___M_impl.rend(); }

Data::const_reverse_iterator Data::crbegin() const { return ___M_impl.crbegin(); }
Data::const_reverse_iterator Data::crend() const { return ___M_impl.crend(); }

/* EOF */