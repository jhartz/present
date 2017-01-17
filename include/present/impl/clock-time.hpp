/*
 * Present - Date/Time Library
 *
 * Implementation of the ClockTime C++ methods
 *
 * This file is included from "present.h", and is NOT meant to be included
 * from anywhere else.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

inline ClockTime
ClockTime::create(int_hour hour)
{
    ClockTime result;
    ClockTime_ptr_from_hour(&result, hour);
    return result;
}

inline ClockTime
ClockTime::create(int_hour hour, int_minute minute)
{
    ClockTime result;
    ClockTime_ptr_from_hour_minute(&result, hour, minute);
    return result;
}

inline ClockTime
ClockTime::create(int_hour hour, int_minute minute, int_second second)
{
    ClockTime result;
    ClockTime_ptr_from_hour_minute_second(&result, hour, minute, second);
    return result;
}

inline ClockTime
ClockTime::create(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond)
{
    ClockTime result;
    ClockTime_ptr_from_hour_minute_second_nanosecond(
            &result,
            hour,
            minute,
            second,
            nanosecond);
    return result;
}

inline ClockTime
ClockTime::create_with_decimal_seconds(
        int_hour hour,
        int_minute minute,
        double second)
{
    ClockTime result;
    ClockTime_ptr_create_with_decimal_seconds(&result, hour, minute, second);
    return result;
}

inline ClockTime
ClockTime::midnight()
{
    ClockTime result;
    ClockTime_ptr_midnight(&result);
    return result;
}

inline ClockTime
ClockTime::noon()
{
    ClockTime result;
    ClockTime_ptr_noon(&result);
    return result;
}

inline int_hour
ClockTime::hour() const
{
    return ClockTime_hour(this);
}

inline int_minute
ClockTime::minute() const
{
    return ClockTime_minute(this);
}

inline int_second
ClockTime::second() const
{
    return ClockTime_second(this);
}

inline int_nanosecond
ClockTime::nanosecond() const
{
    return ClockTime_nanosecond(this);
}

inline double
ClockTime::second_decimal() const
{
    return ClockTime_second_decimal(this);
}

inline TimeDelta
ClockTime::time_since_midnight() const
{
    return ClockTime_time_since_midnight(this);
}

inline ClockTime &
ClockTime::operator+=(const TimeDelta & delta)
{
    ClockTime_add_TimeDelta(this, &delta);
    return *this;
}

inline ClockTime &
ClockTime::operator-=(const TimeDelta & delta)
{
    ClockTime_subtract_TimeDelta(this, &delta);
    return *this;
}

inline const ClockTime
operator+(const ClockTime & lhs, const TimeDelta & rhs)
{
    return (ClockTime(lhs) += rhs);
}
inline const ClockTime
operator+(const TimeDelta & lhs, const ClockTime & rhs)
{
    return (ClockTime(rhs) += lhs);
}

inline const ClockTime
operator-(const ClockTime & lhs, const TimeDelta & rhs)
{
    return (ClockTime(lhs) -= rhs);
}

inline int
ClockTime::compare(const ClockTime & lhs, const ClockTime & rhs)
{
    return ClockTime_compare(&lhs, &rhs);
}

inline bool
operator==(const ClockTime & lhs, const ClockTime & rhs)
{
    return ClockTime_equal(&lhs, &rhs);
}

inline bool
operator!=(const ClockTime & lhs, const ClockTime & rhs)
{
    return !(lhs == rhs);
}

inline bool
operator<(const ClockTime & lhs, const ClockTime & rhs)
{
    return ClockTime_less_than(&lhs, &rhs);
}

inline bool
operator<=(const ClockTime & lhs, const ClockTime & rhs)
{
    return ClockTime_less_than_or_equal(&lhs, &rhs);
}

inline bool
operator>(const ClockTime & lhs, const ClockTime & rhs)
{
    return ClockTime_greater_than(&lhs, &rhs);
}

inline bool
operator>=(const ClockTime & lhs, const ClockTime & rhs)
{
    return ClockTime_greater_than_or_equal(&lhs, &rhs);
}

