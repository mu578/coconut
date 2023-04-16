//
// nutrt-datetime.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/traits/nutrt-datetime.hpp>
#include <coconut/runtime/details/traits/nutrt-formatter.hpp>
#include <coconut/runtime/details/traits/nutrt-locale.hpp>
#include <coconut/runtime/details/traits/nutrt-timezone.hpp>

using namespace coconut::runtime;
using namespace coconut::runtime::traits;

#include <source/runtime/builtins/nutrt-datetime_epoch.hxx>
#include <source/runtime/builtins/nutrt-datetime_format.hxx>

datetime::datetime()
: ___M_type(datekind_default)
, ___M_millitime(0.0)
{ /* NOP */ }

datetime::datetime(const datetime & dtm)
: ___M_type(dtm.___M_type)
, ___M_millitime(dtm.___M_millitime)
{ /* NOP */ }

datetime::datetime(double milliseconds, timeref_option ref_opt)
: ___M_type(datekind_default)
, ___M_millitime(0.0)
{
	switch (ref_opt)
	{
		case timeref_since_ref:
		{
			___M_millitime = milliseconds;
		}
		break;
		case timeref_since_now:
		{
			___M_millitime = datetime::reference_time(timeunit_milliseconds) + milliseconds;
		}
		break;
		case timeref_since_1970:
		{
			___M_millitime = -COCONUT_APPLE_EPOCH_MILLISECONDS + milliseconds;;
		}
		break;
		default:
			break;
	}
}

datetime::datetime(double interval, timeunit_option unit_opt, timeref_option ref_opt)
: ___M_type(datekind_default)
, ___M_millitime(0.0)
{
	double milliseconds = 0.0;
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		case timeunit_doubleseconds:
		{
			milliseconds = interval * 1000.0;
		}
		break;
		case timeunit_milliseconds:
		{
			milliseconds = interval;
		}
		break;
		case timeunit_microseconds:
		{
			milliseconds = interval / 1000.0;
		}
		break;
		case timeunit_nanoseconds:
		{
			milliseconds = interval / 1000000.0;
		}
		break;
		default:
			break;
	}
	
	switch (ref_opt)
	{
		case timeref_since_ref:
		{
			___M_millitime = milliseconds;
		}
		break;
		case timeref_since_now:
		{
			___M_millitime = datetime::reference_time(timeunit_milliseconds) + milliseconds;
		}
		break;
		case timeref_since_1970:
		{
			___M_millitime = -COCONUT_APPLE_EPOCH_MILLISECONDS + milliseconds;;
		}
		break;
		default:
			break;
	}
}

datetime::datetime(double interval, timeunit_option unit_opt, const datetime & dtm)
: ___M_type(datekind_default)
, ___M_millitime(0.0)
{
	double milliseconds = 0.0;
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		case timeunit_doubleseconds:
		{
			milliseconds = interval * 1000.0;
		}
		break;
		case timeunit_milliseconds:
		{
			milliseconds = interval;
		}
		break;
		case timeunit_microseconds:
		{
			milliseconds = interval / 1000.0;
		}
		break;
		case timeunit_nanoseconds:
		{
			milliseconds = interval / 1000000.0;
		}
		break;
		default:
			break;
	}
	
	___M_millitime = milliseconds - dtm.___M_millitime;
}

datetime::~datetime()
{ /* NOP */ }

#pragma mark -

double datetime::convert(double interval, timeunit_option unit_opt_in, timeunit_option unit_opt_out)
{
	double nanoseconds = 0.0;
	if (unit_opt_in == unit_opt_out) {
		return interval;
	}
	
	switch (unit_opt_in)
	{
		case timeunit_nanoseconds:
		{
			nanoseconds = interval;
		}
		break;
		case timeunit_microseconds:
		{
			nanoseconds = interval * 1000.0;;
		}
		break;
		case timeunit_milliseconds:
		{
			nanoseconds = interval * 1000000.0;
		}
		break;
		case timeunit_plainseconds:
		{
			nanoseconds = interval * 1000000000.0;
		}
		break;
		case timeunit_doubleseconds:
		{
			std::int64_t sec = weak_cast<std::int64_t>(interval);
			double ms = interval - sec;
			double milliseconds = (static_cast<double>(sec) * 1000.0) + ms;
			nanoseconds = milliseconds * 1000000.0;
		}
		break;
	}
	
	switch (unit_opt_out)
	{
		case timeunit_nanoseconds:
			return nanoseconds;
		case timeunit_microseconds:
			return nanoseconds / 1000.0;
		case timeunit_milliseconds:
			return nanoseconds / 1000000.0;
		case timeunit_plainseconds:
			return nanoseconds / 1000000000.0;
		case timeunit_doubleseconds:
		{
			std::int64_t ns = weak_cast<std::int64_t>(nanoseconds);
			std::int64_t sec = ns / 1000000000LL;
			std::int64_t ms = (ns >= 0 ? ns % 1000000000LL : -((-ns % 1000000000LL))) / 1000000LL ;
			return static_cast<double>(sec) + static_cast<double>(ms);
		}
	}
	return 0.0;
}

#pragma mark -

double datetime::absolute(timeunit_option unit_opt)
{
	double result = 0.0;
	switch (unit_opt)
	{
		case timeunit_nanoseconds:
		{
			result = static_cast<double>(builtins::datetime_nanotime());
		}
		break;
		case timeunit_microseconds:
		{
			result = static_cast<double>(builtins::datetime_microtime());
		}
		break;
		case timeunit_milliseconds:
		{
			result = static_cast<double>(builtins::datetime_millitime());
		}
		break;
		case timeunit_plainseconds:
		{
			result = static_cast<double>(builtins::datetime_millitime()) / 1000.0;
		}
		break;
		case timeunit_doubleseconds:
		{
			std::int64_t t = builtins::datetime_millitime();
			std::int64_t s = t / 1000LL;
			std::int64_t m = t >= 0 ? t % 1000LL : -((-t % 1000LL));
			result = static_cast<double>(s) +  static_cast<double>(m);
		}
		break;
		default:
			break;
	}
	return result;
}

#pragma mark -

std::string datetime::utc_now()
{
	return builtins::datetime_format_utc(
		datetime::timestamp_1970(timeunit_milliseconds)
	);
}

datetime datetime::utc_parse(const std::string & utc)
{
	double milliseconds = builtins::datetime_parse_utc(utc);
	datetime dtm(milliseconds, timeref_since_1970);
	return dtm;
}

#pragma mark -

bool datetime::get_now(std::pair<std::int64_t, std::int64_t> & tm)
{
	bool result = false;
	builtins::time_spec tms;
	tm.first = 0;
 	tm.second = 0;
	if (builtins::datetime_epoch(&tms)) {
		tm.first = static_cast<std::int64_t>(tms.tv_sec);
		tm.second = static_cast<std::int64_t>(tms.tv_nsec);
		result = true;
	}
	return result;
}

#pragma mark -

double datetime::timestamp_1970(timeunit_option unit_opt)
{
	double result = 0.0;
	std::pair<std::int64_t, std::int64_t> tm;
	
	if (datetime::get_now(tm)) {
		switch (unit_opt)
		{
			case timeunit_plainseconds:
			{
				result = static_cast<double>(tm.first);
			}
			break;
			case timeunit_doubleseconds:
			{
				result = static_cast<double>(tm.first) + static_cast<double>((tm.second / 1000000) / 1000.0);
			}
			break;
			case timeunit_milliseconds:
			{
				result = static_cast<double>(tm.first * 1000.0) + static_cast<double>((tm.second / 1000000));
			}
			break;
			case timeunit_microseconds:
			{
				result = static_cast<double>(tm.first * 1000000.0) + static_cast<double>((tm.second / 1000));
			}
			break;
			case timeunit_nanoseconds:
			{
				result = static_cast<double>(tm.first * 1000000000.0) + static_cast<double>(tm.second);
			}
			break;
			default:
				break;
		}
	}
	return result;
}

double datetime::reference_time(timeunit_option unit_opt)
{
	double result = 0.0;
	
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		{
			result = -COCONUT_APPLE_EPOCH_PLAINSECONDS + datetime::timestamp_1970(unit_opt);
		}
		break;
		case timeunit_doubleseconds:
		{
			result = -COCONUT_APPLE_EPOCH_DOUBLESECONDS + datetime::timestamp_1970(unit_opt);
		}
		break;
		case timeunit_milliseconds:
		{
			result = -COCONUT_APPLE_EPOCH_MILLISECONDS + datetime::timestamp_1970(unit_opt);
		}
		break;
		case timeunit_microseconds:
		{
			result = -COCONUT_APPLE_EPOCH_MICROSECONDS + datetime::timestamp_1970(unit_opt);
		}
		break;
		case timeunit_nanoseconds:
		{
			result = -COCONUT_APPLE_EPOCH_NANOSECONDS + datetime::timestamp_1970(unit_opt);
		}
		break;
		default:
			break;
	}
	return result;
}

#pragma mark -

datetime datetime::future()
{
	datetime dtm(COCONUT_FORTY_YEARS_MILLISECONDS, timeref_since_now);
	return dtm;
}

datetime datetime::past()
{
	datetime dtm(-COCONUT_FORTY_YEARS_MILLISECONDS, timeref_since_now);
	return dtm;
}

#pragma mark -

datetime & datetime::operator = (const datetime & dtm)
{
	if (this == &dtm) {
		return *this;
	}
	___M_type = dtm.___M_type;
	___M_millitime = dtm.___M_millitime;
	
	return *this;
}

#pragma mark -

int datetime::compare(const datetime & other_dtm) const
{
	if (this == &other_dtm) {
		return cmp_same;
	}
	double interval = time_interval_since(other_dtm);
	if (interval < 0.0) {
		return cmp_ascending;
	} else if (interval > 0.0) {
		return cmp_descending;
	}
	return cmp_same;
}

#pragma mark -

const datetime & datetime::earlier(const datetime & dtm) const
{
	return time_interval_since(dtm) < 0 ? *this : dtm;
}

const datetime & datetime::later(const datetime & dtm) const
{
	return time_interval_since(dtm) > 0 ? *this : dtm;
}

#pragma mark -

std::string datetime::to_string() const
{
	return builtins::datetime_format_utc(
		time_interval_since_1970()
	);
}

std::size_t datetime::hash_code() const
{
	return std::hash<double>()(___M_millitime + static_cast<double>(___M_type));
}

#pragma mark -

double datetime::time_interval_since(const datetime & dtm) const
{
	return ___M_millitime - dtm.___M_millitime;
}

double datetime::time_interval_since(const datetime & dtm, timeunit_option unit_opt) const
{
	double milliseconds = time_interval_since(dtm);
	double interval = 0.0;
	
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		case timeunit_doubleseconds:
		{
			interval = milliseconds / 1000.0;
		}
		break;
		case timeunit_milliseconds:
		{
			interval = milliseconds;
		}
		break;
		case timeunit_microseconds:
		{
			interval = milliseconds * 1000.0;
		}
		break;
		case timeunit_nanoseconds:
		{
			interval = milliseconds * 1000000.0;
		}
		break;
		default:
			break;
	}
	return interval;
}

double datetime::time_interval_since(timeref_option ref_opt, timeunit_option unit_opt) const
{
	double milliseconds = 0.0;
	double interval = 0.0;
	
	switch (ref_opt)
	{
		case timeref_since_ref:
		{
			milliseconds = time_interval_since_ref();
		}
		break;
		case timeref_since_now:
		{
			milliseconds = time_interval_since_now();
		}
		break;
		case timeref_since_1970:
		{
			milliseconds = time_interval_since_1970();
		}
		break;
		default:
			break;
	}
	
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		case timeunit_doubleseconds:
		{
			interval = milliseconds / 1000.0;
		}
		break;
		case timeunit_milliseconds:
		{
			interval = milliseconds;
		}
		break;
		case timeunit_microseconds:
		{
			interval = milliseconds * 1000.0;
		}
		break;
		case timeunit_nanoseconds:
		{
			interval = milliseconds * 1000000.0;
		}
		break;
		default:
			break;
	}
	return interval;
}

double datetime::time_interval_since_ref() const
{
	return ___M_millitime;
}

double datetime::time_interval_since_now() const
{
	return ___M_millitime - datetime::reference_time(timeunit_milliseconds);
}

double datetime::time_interval_since_1970() const
{
	return ___M_millitime + COCONUT_APPLE_EPOCH_MILLISECONDS;
}

#pragma mark -

datetime datetime::by_adding_time(double milliseconds) const
{
	return datetime(___M_millitime + milliseconds, timeref_since_ref);
}

datetime datetime::by_adding_time(double interval, timeunit_option unit_opt) const
{
	double milliseconds = 0.0;
	
	switch (unit_opt)
	{
		case timeunit_plainseconds:
		case timeunit_doubleseconds:
		{
			milliseconds = interval * 1000.0;
		}
		break;
		case timeunit_milliseconds:
		{
			milliseconds = interval;
		}
		break;
		case timeunit_microseconds:
		{
			milliseconds = interval / 1000.0;
		}
		break;
		case timeunit_nanoseconds:
		{
			milliseconds = interval / 1000000.0;
		}
		break;
		default:
			break;
	}
	return datetime(___M_millitime + milliseconds, timeref_since_ref);
}

/* EOF */