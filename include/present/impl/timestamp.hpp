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
Timestamp::create(const time_t timestamp)
{
    return Timestamp_from_time_t(timestamp);
}

inline Timestamp
Timestamp::create(const struct tm & tm, const TimeDelta & timeZoneOffset)
{
    return Timestamp_from_struct_tm(tm, &timeZoneOffset);
}

inline Timestamp
Timestamp::create_utc(const struct tm & tm)
{
    return Timestamp_from_struct_tm_utc(tm);
}

inline Timestamp
Timestamp::create_local(const struct tm & tm)
{
    return Timestamp_from_struct_tm_local(tm);
}

inline Timestamp
Timestamp::create(
        const Date & date,
        const ClockTime & clockTime,
        const TimeDelta & timeZoneOffset)
{
    return Timestamp_create(&date, &clockTime, &timeZoneOffset);
}

inline Timestamp
Timestamp::create_utc(const Date & date, const ClockTime & clockTime)
{
    return Timestamp_create_utc(&date, &clockTime);
}

inline Timestamp
Timestamp::create_local(const Date & date, const ClockTime & clockTime)
{
    return Timestamp_create_local(&date, &clockTime);
}

inline Timestamp
Timestamp::now()
{
    return Timestamp_now();
}

inline Timestamp
Timestamp::epoch()
{
    return Timestamp_epoch();
}

inline time_t
Timestamp::get_time_t() const
{
    return Timestamp_get_time_t(this);
}

inline struct tm
Timestamp::get_struct_tm(const TimeDelta & timeZoneOffset) const
{
    return Timestamp_get_struct_tm(this, &timeZoneOffset);
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
Timestamp::get_date(const TimeDelta & timeZoneOffset) const
{
    return Timestamp_get_date(this, &timeZoneOffset);
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
Timestamp::get_clock_time(const TimeDelta & timeZoneOffset) const
{
    return Timestamp_get_clock_time(this, &timeZoneOffset);
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

inline int
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

