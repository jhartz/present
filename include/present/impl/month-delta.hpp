/*
 * Present - Date/Time Library
 *
 * Implementation of the MonthDelta C++ methods
 *
 * This file is included from "present.h", and is NOT meant to be included
 * from anywhere else.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>

inline MonthDelta
MonthDelta::from_months(int_month_delta months)
{
    return MonthDelta_from_months(months);
}

inline MonthDelta
MonthDelta::from_years(int_year_delta years)
{
    return MonthDelta_from_years(years);
}

inline MonthDelta
MonthDelta::zero()
{
    return MonthDelta_zero();
}

inline int_month_delta
MonthDelta::months() const
{
    return MonthDelta_months(this);
}

inline int_year_delta
MonthDelta::years() const
{
    return MonthDelta_years(this);
}

inline double
MonthDelta::years_decimal() const
{
    return MonthDelta_years_decimal(this);
}

inline bool
MonthDelta::is_negative() const
{
    return MonthDelta_is_negative(this);
}

inline void
MonthDelta::negate()
{
    MonthDelta_negate(this);
}

inline MonthDelta
MonthDelta::operator-() const
{
    MonthDelta copy(*this);
    copy.negate();
    return copy;
}

inline MonthDelta &
MonthDelta::operator++()
{
    this->data_.delta_months += 1;
    return *this;
}

inline MonthDelta
MonthDelta::operator++(int)
{
    MonthDelta copy(*this);
    operator++();
    return copy;
}

inline MonthDelta &
MonthDelta::operator--()
{
    this->data_.delta_months -= 1;
    return *this;
}

inline MonthDelta
MonthDelta::operator--(int)
{
    MonthDelta copy(*this);
    operator--();
    return copy;
}

inline MonthDelta &
MonthDelta::operator*=(const int & scale_factor)
{
    MonthDelta_multiply_by(this, scale_factor);
    return *this;
}

inline MonthDelta &
MonthDelta::operator/=(const int & scale_factor)
{
    MonthDelta_divide_by(this, scale_factor);
    return *this;
}

inline const MonthDelta
operator*(const MonthDelta & lhs, const int & rhs)
{
    return (MonthDelta(lhs) *= rhs);
}

inline const MonthDelta
operator/(const MonthDelta & lhs, const int & rhs)
{
    return (MonthDelta(lhs) /= rhs);
}

inline MonthDelta &
MonthDelta::operator+=(const MonthDelta & other)
{
    MonthDelta_add(this, &other);
    return *this;
}

inline MonthDelta &
MonthDelta::operator-=(const MonthDelta & other)
{
    MonthDelta_subtract(this, &other);
    return *this;
}

inline const MonthDelta
operator+(const MonthDelta & lhs, const MonthDelta & rhs)
{
    return (MonthDelta(lhs) += rhs);
}

inline const MonthDelta
operator-(const MonthDelta & lhs, const MonthDelta & rhs)
{
    return (MonthDelta(lhs) -= rhs);
}

inline int
MonthDelta::compare(const MonthDelta & lhs, const MonthDelta & rhs)
{
    return MonthDelta_compare(&lhs, &rhs);
}

inline bool
operator==(const MonthDelta & lhs, const MonthDelta & rhs)
{
    return MonthDelta_equal(&lhs, &rhs);
}

inline bool
operator!=(const MonthDelta & lhs, const MonthDelta & rhs)
{
    return !(lhs == rhs);
}

inline bool
operator<(const MonthDelta & lhs, const MonthDelta & rhs)
{
    return MonthDelta_less_than(&lhs, &rhs);
}

inline bool
operator<=(const MonthDelta & lhs, const MonthDelta & rhs)
{
    return MonthDelta_less_than_or_equal(&lhs, &rhs);
}

inline bool
operator>(const MonthDelta & lhs, const MonthDelta & rhs)
{
    return MonthDelta_greater_than(&lhs, &rhs);
}

inline bool
operator>=(const MonthDelta & lhs, const MonthDelta & rhs)
{
    return MonthDelta_greater_than_or_equal(&lhs, &rhs);
}

