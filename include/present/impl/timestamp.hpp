/*
 * Present - Date/Time Library
 *
 * Implementation of the Timestamp C++ methods
 *
 * This file is included from "present.h", and is NOT meant to be included
 * from anywhere else.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

inline Timestamp
Timestamp::create(const time_t time)
{
    Timestamp result;
    Timestamp_ptr_from_time_t(&result, time);
    return result;
}

inline Timestamp
Timestamp::create(const struct tm & tm, const TimeDelta & time_zone_offset)
{
    Timestamp result;
    Timestamp_ptr_from_struct_tm(&result, tm, &time_zone_offset);
    return result;
}

inline Timestamp
Timestamp::create_utc(const struct tm & tm)
{
    Timestamp result;
    Timestamp_ptr_from_struct_tm_utc(&result, tm);
    return result;
}

inline Timestamp
Timestamp::create_local(const struct tm & tm)
{
    Timestamp result;
    Timestamp_ptr_from_struct_tm_local(&result, tm);
    return result;
}

inline Timestamp
Timestamp::create(
        const Date & date,
        const ClockTime & clock_time,
        const TimeDelta & time_zone_offset)
{
    Timestamp result;
    Timestamp_ptr_create(&result, &date, &clock_time, &time_zone_offset);
    return result;
}

inline Timestamp
Timestamp::create_utc(const Date & date, const ClockTime & clock_time)
{
    Timestamp result;
    Timestamp_ptr_create_utc(&result, &date, &clock_time);
    return result;
}

inline Timestamp
Timestamp::create_local(const Date & date, const ClockTime & clock_time)
{
    Timestamp result;
    Timestamp_ptr_create_local(&result, &date, &clock_time);
    return result;
}

inline Timestamp
Timestamp::now()
{
    Timestamp result;
    Timestamp_ptr_now(&result);
    return result;
}

inline Timestamp
Timestamp::epoch()
{
    Timestamp result;
    Timestamp_ptr_epoch(&result);
    return result;
}

inline time_t
Timestamp::get_time_t() const
{
    return Timestamp_get_time_t(this);
}

inline struct tm
Timestamp::get_struct_tm(const TimeDelta & time_zone_offset) const
{
    return Timestamp_get_struct_tm(this, &time_zone_offset);
}

inline struct tm
Timestamp::get_struct_tm_utc() const
{
    return Timestamp_get_struct_tm_utc(this);
}

inline struct tm
Timestamp::get_struct_tm_local() const
{
    return Timestamp_get_struct_tm_local(this);
}

inline Date
Timestamp::get_date(const TimeDelta & time_zone_offset) const
{
    return Timestamp_get_date(this, &time_zone_offset);
}

inline Date
Timestamp::get_date_utc() const
{
    return Timestamp_get_date_utc(this);
}

inline Date
Timestamp::get_date_local() const
{
    return Timestamp_get_date_local(this);
}

inline ClockTime
Timestamp::get_clock_time(const TimeDelta & time_zone_offset) const
{
    return Timestamp_get_clock_time(this, &time_zone_offset);
}

inline ClockTime
Timestamp::get_clock_time_utc() const
{
    return Timestamp_get_clock_time_utc(this);
}

inline ClockTime
Timestamp::get_clock_time_local() const
{
    return Timestamp_get_clock_time_local(this);
}

inline TimeDelta
Timestamp::difference(const Timestamp & other) const
{
    return Timestamp_difference(this, &other);
}

inline TimeDelta
Timestamp::absolute_difference(const Timestamp & other) const
{
    return Timestamp_absolute_difference(this, &other);
}

inline Timestamp &
Timestamp::operator+=(const TimeDelta & delta)
{
    Timestamp_add_TimeDelta(this, &delta);
    return *this;
}

inline Timestamp &
Timestamp::operator+=(const DayDelta & delta)
{
    Timestamp_add_DayDelta(this, &delta);
    return *this;
}

inline Timestamp &
Timestamp::operator+=(const MonthDelta & delta)
{
    Timestamp_add_MonthDelta(this, &delta);
    return *this;
}

inline Timestamp &
Timestamp::operator-=(const TimeDelta & delta)
{
    Timestamp_subtract_TimeDelta(this, &delta);
    return *this;
}

inline Timestamp &
Timestamp::operator-=(const DayDelta & delta)
{
    Timestamp_subtract_DayDelta(this, &delta);
    return *this;
}

inline Timestamp &
Timestamp::operator-=(const MonthDelta & delta)
{
    Timestamp_subtract_MonthDelta(this, &delta);
    return *this;
}

inline const Timestamp
operator+(const Timestamp & lhs, const TimeDelta & rhs)
{
    return (Timestamp(lhs) += rhs);
}
inline const Timestamp
operator+(const TimeDelta & lhs, const Timestamp & rhs)
{
    return (Timestamp(rhs) += lhs);
}

inline const Timestamp
operator+(const Timestamp & lhs, const DayDelta & rhs)
{
    return (Timestamp(lhs) += rhs);
}
inline const Timestamp
operator+(const DayDelta & lhs, const Timestamp & rhs)
{
    return (Timestamp(rhs) += lhs);
}

inline const Timestamp
operator+(const Timestamp & lhs, const MonthDelta & rhs)
{
    return (Timestamp(lhs) += rhs);
}
inline const Timestamp
operator+(const MonthDelta & lhs, const Timestamp & rhs)
{
    return (Timestamp(rhs) += lhs);
}

inline const Timestamp
operator-(const Timestamp & lhs, const TimeDelta & rhs)
{
    return (Timestamp(lhs) -= rhs);
}

inline const Timestamp
operator-(const Timestamp & lhs, const DayDelta & rhs)
{
    return (Timestamp(lhs) -= rhs);
}

inline const Timestamp
operator-(const Timestamp & lhs, const MonthDelta & rhs)
{
    return (Timestamp(lhs) -= rhs);
}

inline short
Timestamp::compare(const Timestamp & lhs, const Timestamp & rhs)
{
    return Timestamp_compare(&lhs, &rhs);
}

inline bool
operator==(const Timestamp & lhs, const Timestamp & rhs)
{
    return Timestamp_equal(&lhs, &rhs);
}

inline bool
operator!=(const Timestamp & lhs, const Timestamp & rhs)
{
    return !(lhs == rhs);
}

inline bool
operator<(const Timestamp & lhs, const Timestamp & rhs)
{
    return Timestamp_less_than(&lhs, &rhs);
}

inline bool
operator<=(const Timestamp & lhs, const Timestamp & rhs)
{
    return Timestamp_less_than_or_equal(&lhs, &rhs);
}

inline bool
operator>(const Timestamp & lhs, const Timestamp & rhs)
{
    return Timestamp_greater_than(&lhs, &rhs);
}

inline bool
operator>=(const Timestamp & lhs, const Timestamp & rhs)
{
    return Timestamp_greater_than_or_equal(&lhs, &rhs);
}

