/*
 * Present - Date/Time Library
 *
 * Implementation of the DayDelta C++ methods
 *
 * This file is included from "present.h", and is NOT meant to be included
 * from anywhere else.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>

inline DayDelta
DayDelta::from_days(int_delta days)
{
    DayDelta result;
    DayDelta_ptr_from_days(&result, days);
    return result;
}

inline DayDelta
DayDelta::from_weeks(int_delta weeks)
{
    DayDelta result;
    DayDelta_ptr_from_weeks(&result, weeks);
    return result;
}

inline DayDelta
DayDelta::zero()
{
    DayDelta result;
    DayDelta_ptr_zero(&result);
    return result;
}

inline int_delta
DayDelta::days() const
{
    return DayDelta_days(this);
}

inline int_delta
DayDelta::weeks() const
{
    return DayDelta_weeks(this);
}

inline double
DayDelta::weeks_decimal() const
{
    return DayDelta_weeks_decimal(this);
}

inline TimeDelta
DayDelta::to_TimeDelta() const
{
    return DayDelta_to_TimeDelta(this);
}

inline bool
DayDelta::is_negative() const
{
    return DayDelta_is_negative(this);
}

inline void
DayDelta::negate()
{
    DayDelta_negate(this);
}

inline DayDelta
DayDelta::operator-() const
{
    DayDelta copy(*this);
    copy.negate();
    return copy;
}

inline DayDelta &
DayDelta::operator++()
{
    this->data_.delta_days += 1;
    return *this;
}

inline DayDelta
DayDelta::operator++(int)
{
    DayDelta copy(*this);
    operator++();
    return copy;
}

inline DayDelta &
DayDelta::operator--()
{
    this->data_.delta_days -= 1;
    return *this;
}

inline DayDelta
DayDelta::operator--(int)
{
    DayDelta copy(*this);
    operator--();
    return copy;
}

inline DayDelta &
DayDelta::operator*=(const long & scale_factor)
{
    DayDelta_multiply_by(this, scale_factor);
    return *this;
}

inline DayDelta &
DayDelta::operator/=(const long & scale_factor)
{
    DayDelta_divide_by(this, scale_factor);
    return *this;
}

inline const DayDelta
operator*(const DayDelta & lhs, const long & rhs)
{
    return (DayDelta(lhs) *= rhs);
}

inline const DayDelta
operator/(const DayDelta & lhs, const long & rhs)
{
    return (DayDelta(lhs) /= rhs);
}

inline DayDelta &
DayDelta::operator+=(const DayDelta & other)
{
    DayDelta_add(this, &other);
    return *this;
}

inline DayDelta &
DayDelta::operator-=(const DayDelta & other)
{
    DayDelta_subtract(this, &other);
    return *this;
}

inline const DayDelta
operator+(const DayDelta & lhs, const DayDelta & rhs)
{
    return (DayDelta(lhs) += rhs);
}

inline const DayDelta
operator-(const DayDelta & lhs, const DayDelta & rhs)
{
    return (DayDelta(lhs) -= rhs);
}

inline short
DayDelta::compare(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_compare(&lhs, &rhs);
}

inline short
DayDelta::compare(const DayDelta & lhs, const TimeDelta & rhs)
{
    return DayDelta_compare_to_TimeDelta(&lhs, &rhs);
}

inline short
DayDelta::compare(const TimeDelta & lhs, const DayDelta & rhs)
{
    return -DayDelta_compare_to_TimeDelta(&rhs, &lhs);
}

inline bool
operator==(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_equal(&lhs, &rhs);
}

inline bool
operator==(const DayDelta & lhs, const TimeDelta & rhs)
{
    return DayDelta_equal_TimeDelta(&lhs, &rhs);
}

inline bool
operator!=(const DayDelta & lhs, const DayDelta & rhs)
{
    return !(lhs == rhs);
}

inline bool
operator!=(const DayDelta & lhs, const TimeDelta & rhs)
{
    return !(lhs == rhs);
}

inline bool
operator<(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_less_than(&lhs, &rhs);
}

inline bool
operator<(const DayDelta & lhs, const TimeDelta & rhs)
{
    return DayDelta_less_than_TimeDelta(&lhs, &rhs);
}

inline bool
operator<=(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_less_than_or_equal(&lhs, &rhs);
}

inline bool
operator<=(const DayDelta & lhs, const TimeDelta & rhs)
{
    return DayDelta_less_than_or_equal_TimeDelta(&lhs, &rhs);
}

inline bool
operator>(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_greater_than(&lhs, &rhs);
}

inline bool
operator>(const DayDelta & lhs, const TimeDelta & rhs)
{
    return DayDelta_greater_than_TimeDelta(&lhs, &rhs);
}

inline bool
operator>=(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_greater_than_or_equal(&lhs, &rhs);
}

inline bool
operator>=(const DayDelta & lhs, const TimeDelta & rhs)
{
    return DayDelta_greater_than_or_equal_TimeDelta(&lhs, &rhs);
}

