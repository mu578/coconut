//
// Date.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Date.hpp>
#include <coconut/foundation/String.hpp>

using namespace coconut;

Date::Date() :
	Object(DateClass),
	___M_impl(0.0L, TimeReferenceSinceCurrentTime)
{ /* NOP */ }

Date::Date(const Date & dtm) :
	Object(DateClass),
	___M_impl(dtm.___M_impl)
{ /* NOP */ }

Date::Date(Date && dtm) noexcept :
	Object(DateClass),
	___M_impl(std::move(dtm.___M_impl))
{ /* NOP */ }

Date::Date(TimeInterval seconds, TimeReferenceOption ref_opt) :
	Object(DateClass),
	___M_impl(seconds, TimeUnitPlainSeconds, ref_opt)
{ /* NOP */ }

Date::Date(TimeInterval seconds, const Date & since) :
	Object(DateClass),
	___M_impl(seconds, TimeUnitPlainSeconds, since.___M_impl)
{ /* NOP */ }

Date::Date(TimeInterval interval, TimeUnitOption unit_opt, TimeReferenceOption ref_opt) :
	Object(DateClass),
	___M_impl(interval, unit_opt, ref_opt)
{ /* NOP */ }

Date::Date(TimeInterval interval, TimeUnitOption unit_opt, const Date & since) :
	Object(DateClass),
	___M_impl(interval, unit_opt, since.___M_impl)
{ /* NOP */ }

Date::~Date()
{ /* NOP */ }

#pragma mark -

const String Date::UTC()
{ return {impl_trait::utc_now()}; }

const String Date::UTC(const Date & dtm)
{ return {dtm.stringValue()}; }

#pragma mark -

const Date Date::fromUTC(const String & UTC)
{
	Date dtm(0.0L, TimeReferenceSinceReferenceDate, TimeUnitMilliSeconds);
	dtm.___M_impl = impl_trait::utc_parse(UTC.stringValue());
	return dtm;
}

#pragma mark -

TimeInterval Date::convertTime(TimeInterval interval, TimeUnitOption unit_opt_in, TimeUnitOption unit_opt_out)
{ return impl_trait::convert(interval, unit_opt_in, unit_opt_out); }

#pragma mark -

TimeInterval Date::absoluteTime(TimeUnitOption unit_opt)
{ return impl_trait::absolute(unit_opt); }

TimeInterval Date::timestamp(TimeUnitOption unit_opt, TimestampOption stamp_opt)
{
	if (stamp_opt == TimestampSinceReferenceDate) {
		return impl_trait::reference_time(unit_opt);
	}
	return impl_trait::timestamp_1970(unit_opt);
}

#pragma mark -

const Date Date::distantFuture()
{
	Date dtm(0.0L, TimeReferenceSinceReferenceDate, TimeUnitMilliSeconds);
	dtm.___M_impl = impl_trait::future();
	return dtm;
}

const Date Date::distantPast()
{
	Date dtm(0.0L, TimeReferenceSinceReferenceDate, TimeUnitMilliSeconds);
	dtm.___M_impl = impl_trait::past();
	return dtm;
}

#pragma mark -

const Date Date::now()
{ return {}; }

#pragma mark -

std::size_t Date::hash() const
{ return ___M_impl.hash_code(); }

#pragma mark -

Owning<Any> Date::copy() const
{ return ptr_create<Date>(*this); }

#pragma mark -

ComparisonResult Date::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		return ___M_impl.compare(ref_cast<Date>(ref).___M_impl);
	}
	return OrderedDescending;
}

#pragma mark -

std::string Date::stringValue() const
{ return ___M_impl.to_string(); }

double Date::doubleValue() const
{ return ___M_impl.time_interval_since_1970(); }

#pragma mark -

TimeInterval Date::timeIntervalSinceDate(const Date & dtm, TimeUnitOption unit_opt) const
{ return ___M_impl.time_interval_since(dtm.___M_impl, unit_opt); }

TimeInterval Date::timeIntervalSinceReference(TimeReferenceOption ref_opt, TimeUnitOption unit_opt) const
{ return ___M_impl.time_interval_since(ref_opt, unit_opt); }

#pragma mark -

const Date Date::dateByAddingTimeInterval(TimeInterval seconds) const
{
	Date dtm = Date(0.0L, TimeReferenceSinceReferenceDate, TimeUnitMilliSeconds);
	dtm.___M_impl = std::move(___M_impl.by_adding_time(seconds, TimeUnitPlainSeconds));
	return dtm;
}

const Date Date::dateByAddingTimeInterval(TimeInterval interval, TimeUnitOption unit_opt) const
{
	Date dtm = Date(0.0L, TimeReferenceSinceReferenceDate, TimeUnitMilliSeconds);
	dtm.___M_impl = std::move(___M_impl.by_adding_time(interval, unit_opt));
	return dtm;
}

#pragma mark -

const Date & Date::earlierDate(const Date & dtm) const
{ return timeIntervalSinceDate(dtm, TimeUnitMilliSeconds) < 0 ? *this : dtm; }

const Date & Date::laterDate(const Date & dtm) const
{ return timeIntervalSinceDate(dtm, TimeUnitMilliSeconds) > 0 ? *this : dtm; }

bool Date::after(const Date & dtm) const
{ return compare(dtm) == OrderedDescending; }

bool Date::before(const Date & dtm) const
{ return compare(dtm) == OrderedAscending; }

/* EOF */