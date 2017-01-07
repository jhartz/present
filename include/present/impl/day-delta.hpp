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
    return DayDelta_from_days(days);
}

inline DayDelta
DayDelta::from_weeks(int_delta weeks)
{
    return DayDelta_from_weeks(weeks);
}

inline DayDelta
DayDelta::zero()
{
    return DayDelta_zero();
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
    assert(this->error == 0);

    DayDelta copy(*this);
    copy.negate();
    return copy;
}

inline DayDelta &
DayDelta::operator++()
{
    assert(this->error == 0);

    this->data_.delta_days += 1;
    return *this;
}

inline DayDelta
DayDelta::operator++(int)
{
    assert(this->error == 0);

    DayDelta copy(*this);
    operator++();
    return copy;
}

inline DayDelta &
DayDelta::operator--()
{
    assert(this->error == 0);

    this->data_.delta_days -= 1;
    return *this;
}

inline DayDelta
DayDelta::operator--(int)
{
    assert(this->error == 0);

    DayDelta copy(*this);
    operator--();
    return copy;
}

inline DayDelta &
DayDelta::operator*=(const int & scale_factor)
{
    DayDelta_multiply_by(this, scale_factor);
    return *this;
}

inline DayDelta &
DayDelta::operator/=(const int & scale_factor)
{
    DayDelta_divide_by(this, scale_factor);
    return *this;
}

inline const DayDelta
operator*(const DayDelta & lhs, const int & rhs)
{
    return (DayDelta(lhs) *= rhs);
}

inline const DayDelta
operator/(const DayDelta & lhs, const int & rhs)
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

inline int
DayDelta::compare(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_compare(&lhs, &rhs);
}

inline bool
operator==(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_equal(&lhs, &rhs);
}

inline bool
operator!=(const DayDelta & lhs, const DayDelta & rhs)
{
    return !(lhs == rhs);
}

inline bool
operator<(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_less_than(&lhs, &rhs);
}

inline bool
operator<=(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_less_than_or_equal(&lhs, &rhs);
}

inline bool
operator>(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_greater_than(&lhs, &rhs);
}

inline bool
operator>=(const DayDelta & lhs, const DayDelta & rhs)
{
    return DayDelta_greater_than_or_equal(&lhs, &rhs);
}

