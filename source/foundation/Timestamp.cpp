//
// Timestamp.cpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Timestamp.hpp>
#include <coconut/foundation/Date.hpp>

using namespace coconut;

Timestamp::Timestamp() :
	Object(TimestampClass),
	___M_impl(Date::absoluteTime(TimeUnitNanoSeconds))
{ /* NOP */ }

Timestamp::Timestamp(const Timestamp & tms) :
	Object(TimestampClass),
	___M_impl(tms.___M_impl)
{ /* NOP */ }

Timestamp::Timestamp(Timestamp && tms) noexcept :
	Object(TimestampClass),
	___M_impl(tms.___M_impl)
{ /* NOP */ }

Timestamp::Timestamp(const Date & dtm) :
	Object(TimestampClass),
	___M_impl(dtm.timeIntervalSinceReference(TimeReferenceSinceJanuary1970, TimeUnitNanoSeconds))
{ /* NOP */ }

Timestamp::Timestamp(TimeInterval nanoseconds) :
	Object(TimestampClass),
	___M_impl(nanoseconds)
{ /* NOP */ }

Timestamp::Timestamp(TimeInterval interval, TimeUnitOption unit_opt) :
	Object(TimestampClass),
	___M_impl(Date::convertTime(interval, unit_opt, TimeUnitNanoSeconds))
{ /* NOP */ }

Timestamp::~Timestamp()
{ /* NOP */ }

#pragma mark -

const Timestamp distantFuture()
{ return Timestamp(Date::distantFuture()); }

const Timestamp distantPast()
{ return Timestamp(Date::distantPast()); }

const Timestamp Timestamp::now()
{ return Timestamp(); }

#pragma mark -

std::size_t Timestamp::hash() const
{ return std::hash<long long>()(longLongValue()); }

#pragma mark -

Owning<Any> Timestamp::copy() const
{ return ptr_create<Timestamp>(*this); }

#pragma mark -

ComparisonResult Timestamp::compare(const Any & ref) const
{
	if (isIdenticalTo(ref)) {
		return OrderedSame;
	}
	if (ref.isKindOf(*this)) {
		if (___M_impl < ref_cast<Timestamp>(ref).___M_impl) {
			return OrderedAscending;
		} else if (ref_cast<Timestamp>(ref).___M_impl < ___M_impl) {
			return OrderedDescending;
		}
		return OrderedSame;
	}
	return OrderedDescending;
}

#pragma mark -

std::string Timestamp::stringValue() const
{ return runtime::algorithms::to_string<std::string::value_type>(longLongValue()); }

double Timestamp::doubleValue() const
{ return ___M_impl; }

long long Timestamp::longLongValue() const
{ return weak_cast<long long>(___M_impl); }

#pragma mark -

TimeInterval Timestamp::time() const
{ return ___M_impl; }

TimeInterval Timestamp::time(TimeUnitOption unit_opt) const
{ return Date::convertTime(___M_impl, TimeUnitNanoSeconds, unit_opt); }

const Date Timestamp::date() const
{ return Date(___M_impl, TimeUnitNanoSeconds, TimeReferenceSinceJanuary1970); }

#pragma mark -

const Timestamp Timestamp::timestampByAddingTimeInterval(TimeInterval nanoseconds) const
{ return Timestamp(___M_impl + nanoseconds); }

const Timestamp Timestamp::timestampByAddingTimeInterval(TimeInterval interval, TimeUnitOption unit_opt) const
{
	TimeInterval nanoseconds = Date::convertTime(
		interval,
		unit_opt,
		TimeUnitNanoSeconds
	);
	return timestampByAddingTimeInterval(nanoseconds);
}

#pragma mark -

const Timestamp & Timestamp::earlierTimestamp(const Timestamp & tms) const
{ return (longLongValue() > tms.longLongValue()) ? tms : *this; }

const Timestamp & Timestamp::laterTimestamp(const Timestamp & tms) const
{ return (tms.longLongValue() > longLongValue()) ? tms : *this; }

#pragma mark -

TimeInterval Timestamp::elapsed() const
{ return Date::absoluteTime(TimeUnitNanoSeconds) - ___M_impl; }

TimeInterval Timestamp::elapsed(TimeUnitOption unit_opt) const
{
	return Date::convertTime(
		elapsed(),
		TimeUnitNanoSeconds,
		unit_opt
	);
}

bool Timestamp::isElapsed(TimeInterval nanoseconds) const
{ return elapsed() > ___M_impl + nanoseconds; }

bool Timestamp::isElapsed(TimeInterval interval, TimeUnitOption unit_opt) const
{
	TimeInterval nanoseconds = Date::convertTime(
		interval,
		unit_opt,
		TimeUnitNanoSeconds
	);
	return elapsed(nanoseconds);
}

#pragma mark -

bool Timestamp::after(const Timestamp & tms) const
{ return longLongValue() > tms.longLongValue(); }

bool Timestamp::before(const Timestamp & tms) const
{ return tms.longLongValue() > longLongValue(); }

/* EOF */