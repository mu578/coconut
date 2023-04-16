//
// nutrt-islice.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-islice.hpp>
#include <coconut/runtime/details/nutrt-algorithms.hpp>

using namespace coconut::runtime;
using namespace coconut::runtime::traits;

islice::islice()
: ___M_indexes()
, ___M_start(0)
, ___M_stop(0)
, ___M_step(1)
{ /* NOP */ }

islice::islice(const islice & slc)
: ___M_indexes(slc.___M_indexes)
, ___M_start(slc.___M_start)
, ___M_stop(slc.___M_stop)
, ___M_step(slc.___M_step)
{ /* NOP */ }

islice::islice(islice && slc) noexcept
: ___M_indexes(std::move(slc.___M_indexes))
, ___M_start(slc.___M_start)
, ___M_stop(slc.___M_stop)
, ___M_step(slc.___M_step)
{ /* NOP */ }

islice::islice(const std::string & slc_string)
: ___M_indexes()
, ___M_start(0)
, ___M_stop(0)
, ___M_step(1)
{
	try {
		std::regex regex
		{	R"(\{\"\#\{slice\}\": \{\"start\": ([0-9]+), \"stop\": ([0-9]+), \"step\": ([0-9]+)\}\})",
			std::regex::icase
		};
		std::smatch match;
		std::ssub_match sub_match;
		if (std::regex_match(slc_string, match, regex)) {
			if (match.size() == 4) {
				sub_match = match[1];
				___M_start = algorithms::to_numeric<std::int64_t>(sub_match.str());
				sub_match = match[2];
				___M_stop = algorithms::to_numeric<std::int64_t>(sub_match.str());
				sub_match = match[3];
				___M_step = algorithms::to_numeric<std::int64_t>(sub_match.str());
			}
		}
	}
	catch (std::regex_error e) { /* NOP */ }
}

islice::islice(std::int64_t start, std::int64_t stop)
: ___M_indexes()
, ___M_start(start)
, ___M_stop(stop)
, ___M_step(1)
{ /* NOP */ }

islice::islice(std::int64_t start, std::int64_t stop, std::int64_t step)
: ___M_indexes()
, ___M_start(start)
, ___M_stop(stop)
, ___M_step(step <= 0 ? 1 : step)
{ /* NOP */ }

islice::~islice()
{ /* NOP */ }

#pragma mark -

islice & islice::operator = (const islice & slc)
{
	if (this == &slc) {
		return *this;
	}
	___M_start = slc.___M_start;
	___M_stop = slc.___M_stop;
	___M_step = slc.___M_step;
	
	return *this;
}

int islice::compare(const islice & other_slc) const
{
	if (this == &other_slc) {
		return cmp_same;
	} else if (___M_start == other_slc.___M_start && ___M_stop == other_slc.___M_stop && ___M_step == other_slc.___M_step) {
		return cmp_same;
	}
	return cmp_descending; 
}

std::string islice::to_string() const
{
	return algorithms::format
	(
		u8"{\"#{slice}\": {\"start\": %" PRId64 ", \"stop\": %" PRId64 ", \"step\": %" PRId64 "}}}",
		___M_start,
		___M_stop,
		___M_step
	 );
}

#pragma mark -

std::int64_t islice::start() const
{ return ___M_start; }

std::int64_t islice::stop() const
{ return ___M_stop; }

std::int64_t islice::step() const
{ return ___M_step; }

void islice::set_start(std::int64_t start)
{ ___M_start = start; }

void islice::set_stop(std::int64_t stop)
{ ___M_stop = stop; }

void islice::set_step(std::int64_t step)
{ ___M_step = step == 0 ? 1 : step; }

#pragma mark -

void islice::do_indexes(std::size_t forlen) const
{
	std::int64_t start = ___M_start < 0 ? ___M_start + forlen : ___M_start;
	std::int64_t stop = start + (___M_stop < 0 ? ___M_stop + forlen : ___M_stop);
	std::int64_t step = ___M_step;
#if COCONUT_DEBUG
	std::cerr << " + start + : " << start << std::endl;
	std::cerr << " + stop  + : " << stop << std::endl;
#endif
	___M_indexes.clear();
	for(std::int64_t i = start; (i < stop && step > 0) || (i > stop && step < 0); i += step) {
		___M_indexes.push_back(weak_cast<std::size_t>(i));
	}
#if COCONUT_DEBUG
	for (const auto & idx : ___M_indexes) {
		std::cerr << " + idx  + : " << idx << std::endl;
	}
#endif
}

#pragma mark -

islice::iterator islice::begin() { return ___M_indexes.begin(); }
islice::iterator islice::end() { return ___M_indexes.end(); }

islice::const_iterator islice::begin() const { return ___M_indexes.begin(); }
islice::const_iterator islice::end() const { return ___M_indexes.end(); }

islice::const_iterator islice::cbegin() const { return ___M_indexes.cbegin(); }
islice::const_iterator islice::cend() const { return ___M_indexes.cend(); }

islice::reverse_iterator islice::rbegin() { return ___M_indexes.rbegin(); }
islice::reverse_iterator islice::rend() { return ___M_indexes.rend(); }

islice::const_reverse_iterator islice::rbegin() const { return ___M_indexes.rbegin(); }
islice::const_reverse_iterator islice::rend() const { return ___M_indexes.rend(); }

islice::const_reverse_iterator islice::crbegin() const { return ___M_indexes.crbegin(); }
islice::const_reverse_iterator islice::crend() const { return ___M_indexes.crend(); }

/* EOF */