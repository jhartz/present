/*
 * Present - Date/Time Library
 *
 * Implementation of the TimeDelta C++ methods
 *
 * This file is included from "present.h", and is NOT meant to be included
 * from anywhere else.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>

inline TimeDelta
TimeDelta::from_nanoseconds(int_delta nanoseconds)
{
    TimeDelta result;
    TimeDelta_ptr_from_nanoseconds(&result, nanoseconds);
    return result;
}

inline TimeDelta
TimeDelta::from_microseconds(int_delta microseconds)
{
    TimeDelta result;
    TimeDelta_ptr_from_microseconds(&result, microseconds);
    return result;
}

inline TimeDelta
TimeDelta::from_milliseconds(int_delta milliseconds)
{
    TimeDelta result;
    TimeDelta_ptr_from_milliseconds(&result, milliseconds);
    return result;
}

inline TimeDelta
TimeDelta::from_seconds(int_delta seconds)
{
    TimeDelta result;
    TimeDelta_ptr_from_seconds(&result, seconds);
    return result;
}

inline TimeDelta
TimeDelta::from_minutes(int_delta minutes)
{
    TimeDelta result;
    TimeDelta_ptr_from_minutes(&result, minutes);
    return result;
}

inline TimeDelta
TimeDelta::from_hours(int_delta hours)
{
    TimeDelta result;
    TimeDelta_ptr_from_hours(&result, hours);
    return result;
}

inline TimeDelta
TimeDelta::from_days(int_delta days)
{
    TimeDelta result;
    TimeDelta_ptr_from_days(&result, days);
    return result;
}

inline TimeDelta
TimeDelta::from_weeks(int_delta weeks)
{
    TimeDelta result;
    TimeDelta_ptr_from_weeks(&result, weeks);
    return result;
}

inline TimeDelta
TimeDelta::zero()
{
    TimeDelta result;
    TimeDelta_ptr_zero(&result);
    return result;
}

inline int_delta
TimeDelta::nanoseconds() const
{
    return TimeDelta_nanoseconds(this);
}

inline int_delta
TimeDelta::microseconds() const
{
    return TimeDelta_microseconds(this);
}

inline double
TimeDelta::microseconds_decimal() const
{
    return TimeDelta_microseconds_decimal(this);
}

inline int_delta
TimeDelta::milliseconds() const
{
    return TimeDelta_milliseconds(this);
}

inline double
TimeDelta::milliseconds_decimal() const
{
    return TimeDelta_milliseconds_decimal(this);
}

inline int_delta
TimeDelta::seconds() const
{
    return TimeDelta_seconds(this);
}

inline double
TimeDelta::seconds_decimal() const
{
    return TimeDelta_seconds_decimal(this);
}

inline int_delta
TimeDelta::minutes() const
{
    return TimeDelta_minutes(this);
}

inline double
TimeDelta::minutes_decimal() const
{
    return TimeDelta_minutes_decimal(this);
}

inline int_delta
TimeDelta::hours() const
{
    return TimeDelta_hours(this);
}

inline double
TimeDelta::hours_decimal() const
{
    return TimeDelta_hours_decimal(this);
}

inline int_delta
TimeDelta::days() const
{
    return TimeDelta_days(this);
}

inline double
TimeDelta::days_decimal() const
{
    return TimeDelta_days_decimal(this);
}

inline int_delta
TimeDelta::weeks() const
{
    return TimeDelta_weeks(this);
}

inline double
TimeDelta::weeks_decimal() const
{
    return TimeDelta_weeks_decimal(this);
}

inline DayDelta
TimeDelta::to_DayDelta_truncated() const
{
    return TimeDelta_to_DayDelta_truncated(this);
}

inline DayDelta
TimeDelta::to_DayDelta_rounded() const
{
    return TimeDelta_to_DayDelta_rounded(this);
}

inline DayDelta
TimeDelta::to_DayDelta_abs_ceil() const
{
    return TimeDelta_to_DayDelta_abs_ceil(this);
}

inline bool
TimeDelta::is_negative() const
{
    return TimeDelta_is_negative(this);
}

inline void
TimeDelta::negate()
{
    TimeDelta_negate(this);
}

inline TimeDelta
TimeDelta::operator-() const
{
    TimeDelta copy(*this);
    copy.negate();
    return copy;
}

inline TimeDelta &
TimeDelta::operator*=(const long & scale_factor)
{
    TimeDelta_multiply_by(this, scale_factor);
    return *this;
}

inline TimeDelta &
TimeDelta::operator*=(const double & scale_factor)
{
    TimeDelta_multiply_by_decimal(this, scale_factor);
    return *this;
}

inline TimeDelta &
TimeDelta::operator/=(const long & scale_factor)
{
    TimeDelta_divide_by(this, scale_factor);
    return *this;
}

inline TimeDelta &
TimeDelta::operator/=(const double & scale_factor)
{
    TimeDelta_divide_by_decimal(this, scale_factor);
    return *this;
}

inline const TimeDelta
operator*(const TimeDelta & lhs, const long & rhs)
{
    return (TimeDelta(lhs) *= rhs);
}

inline const TimeDelta
operator*(const TimeDelta & lhs, const double & rhs)
{
    return (TimeDelta(lhs) *= rhs);
}

inline const TimeDelta
operator/(const TimeDelta & lhs, const long & rhs)
{
    return (TimeDelta(lhs) /= rhs);
}

inline const TimeDelta
operator/(const TimeDelta & lhs, const double & rhs)
{
    return (TimeDelta(lhs) /= rhs);
}

inline TimeDelta &
TimeDelta::operator+=(const TimeDelta & other)
{
    TimeDelta_add(this, &other);
    return *this;
}

inline TimeDelta &
TimeDelta::operator+=(const DayDelta & other)
{
    TimeDelta_add_DayDelta(this, &other);
    return *this;
}

inline TimeDelta &
TimeDelta::operator-=(const TimeDelta & other)
{
    TimeDelta_subtract(this, &other);
    return *this;
}

inline TimeDelta &
TimeDelta::operator-=(const DayDelta & other)
{
    TimeDelta_subtract_DayDelta(this, &other);
    return *this;
}

inline const TimeDelta
operator+(const TimeDelta & lhs, const TimeDelta & rhs)
{
    return (TimeDelta(lhs) += rhs);
}

inline const TimeDelta
operator+(const TimeDelta & lhs, const DayDelta & rhs)
{
    return (TimeDelta(lhs) += rhs);
}

inline const TimeDelta
operator+(const DayDelta & lhs, const TimeDelta & rhs)
{
    TimeDelta lhs_time_delta = lhs.to_TimeDelta();
    return (lhs_time_delta += rhs);
}

inline const TimeDelta
operator-(const TimeDelta & lhs, const TimeDelta & rhs)
{
    return (TimeDelta(lhs) -= rhs);
}

inline const TimeDelta
operator-(const TimeDelta & lhs, const DayDelta & rhs)
{
    return (TimeDelta(lhs) -= rhs);
}

inline const TimeDelta
operator-(const DayDelta & lhs, const TimeDelta & rhs)
{
    TimeDelta lhs_time_delta = lhs.to_TimeDelta();
    return (lhs_time_delta -= rhs);
}

inline short
TimeDelta::compare(const TimeDelta & lhs, const TimeDelta & rhs)
{
    return TimeDelta_compare(&lhs, &rhs);
}

inline short
TimeDelta::compare(const TimeDelta & lhs, const DayDelta & rhs)
{
    return TimeDelta_compare_to_DayDelta(&lhs, &rhs);
}

inline short
TimeDelta::compare(const DayDelta & lhs, const TimeDelta & rhs)
{
    return -TimeDelta_compare_to_DayDelta(&rhs, &lhs);
}

inline bool
operator==(const TimeDelta & lhs, const TimeDelta & rhs)
{
    return TimeDelta_equal(&lhs, &rhs);
}

inline bool
operator==(const TimeDelta & lhs, const DayDelta & rhs)
{
    return TimeDelta_equal_DayDelta(&lhs, &rhs);
}

inline bool
operator!=(const TimeDelta & lhs, const TimeDelta & rhs)
{
    return !(lhs == rhs);
}

inline bool
operator!=(const TimeDelta & lhs, const DayDelta & rhs)
{
    return !(lhs == rhs);
}

inline bool
operator<(const TimeDelta & lhs, const TimeDelta & rhs)
{
    return TimeDelta_less_than(&lhs, &rhs);
}

inline bool
operator<(const TimeDelta & lhs, const DayDelta & rhs)
{
    return TimeDelta_less_than_DayDelta(&lhs, &rhs);
}

inline bool
operator<=(const TimeDelta & lhs, const TimeDelta & rhs)
{
    return TimeDelta_less_than_or_equal(&lhs, &rhs);
}

inline bool
operator<=(const TimeDelta & lhs, const DayDelta & rhs)
{
    return TimeDelta_less_than_or_equal_DayDelta(&lhs, &rhs);
}

inline bool
operator>(const TimeDelta & lhs, const TimeDelta & rhs)
{
    return TimeDelta_greater_than(&lhs, &rhs);
}

inline bool
operator>(const TimeDelta & lhs, const DayDelta & rhs)
{
    return TimeDelta_greater_than_DayDelta(&lhs, &rhs);
}

inline bool
operator>=(const TimeDelta & lhs, const TimeDelta & rhs)
{
    return TimeDelta_greater_than_or_equal(&lhs, &rhs);
}

inline bool
operator>=(const TimeDelta & lhs, const DayDelta & rhs)
{
    return TimeDelta_greater_than_or_equal_DayDelta(&lhs, &rhs);
}

