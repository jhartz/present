/*
 * Present - Date/Time Library
 *
 * Implementation of the Date C++ methods
 *
 * This file is included from "present.h", and is NOT meant to be included
 * from anywhere else.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

inline Date
Date::create(int_year year)
{
    Date result;
    Date_ptr_from_year(&result, year);
    return result;
}

inline Date
Date::create(int_year year, int_month month)
{
    Date result;
    Date_ptr_from_year_month(&result, year, month);
    return result;
}

inline Date
Date::create(int_year year, int_month month, int_day day)
{
    Date result;
    Date_ptr_from_year_month_day(&result, year, month, day);
    return result;
}

inline Date
Date::from_year_day(int_year year, int_day_of_year day_of_year)
{
    Date result;
    Date_ptr_from_year_day(&result, year, day_of_year);
    return result;
}

inline Date
Date::from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week)
{
    Date result;
    Date_ptr_from_year_week_day(&result, year, week_of_year, day_of_week);
    return result;
}

inline int_year
Date::year() const
{
    return Date_year(this);
}

inline int_month
Date::month() const
{
    return Date_month(this);
}

inline int_day
Date::day() const
{
    return Date_day(this);
}

inline int_day_of_year
Date::day_of_year() const
{
    return Date_day_of_year(this);
}

inline struct PresentWeekYear
Date::week_of_year() const
{
    return Date_week_of_year(this);
}

inline int_day_of_week
Date::day_of_week() const
{
    return Date_day_of_week(this);
}

inline DayDelta
Date::difference(const Date & other) const
{
    return Date_difference(this, &other);
}

inline DayDelta
Date::absolute_difference(const Date & other) const
{
    return Date_absolute_difference(this, &other);
}

inline Date &
Date::operator+=(const DayDelta & delta)
{
    Date_add_DayDelta(this, &delta);
    return *this;
}

inline Date &
Date::operator+=(const MonthDelta & delta)
{
    Date_add_MonthDelta(this, &delta);
    return *this;
}

inline Date &
Date::operator-=(const DayDelta & delta)
{
    Date_subtract_DayDelta(this, &delta);
    return *this;
}

inline Date &
Date::operator-=(const MonthDelta & delta)
{
    Date_subtract_MonthDelta(this, &delta);
    return *this;
}

inline const Date
operator+(const Date & lhs, const DayDelta & rhs)
{
    return (Date(lhs) += rhs);
}
inline const Date
operator+(const DayDelta & lhs, const Date & rhs)
{
    return (Date(rhs) += lhs);
}

inline const Date
operator+(const Date & lhs, const MonthDelta & rhs)
{
    return (Date(lhs) += rhs);
}
inline const Date
operator+(const MonthDelta & lhs, const Date & rhs)
{
    return (Date(rhs) += lhs);
}

inline const Date
operator-(const Date & lhs, const DayDelta & rhs)
{
    return (Date(lhs) -= rhs);
}

inline const Date
operator-(const Date & lhs, const MonthDelta & rhs)
{
    return (Date(lhs) -= rhs);
}

inline int
Date::compare(const Date & lhs, const Date & rhs)
{
    return Date_compare(&lhs, &rhs);
}

inline bool
operator==(const Date & lhs, const Date & rhs)
{
    return Date_equal(&lhs, &rhs);
}

inline bool
operator!=(const Date & lhs, const Date & rhs)
{
    return !(lhs == rhs);
}

inline bool
operator<(const Date & lhs, const Date & rhs)
{
    return Date_less_than(&lhs, &rhs);
}

inline bool
operator<=(const Date & lhs, const Date & rhs)
{
    return Date_less_than_or_equal(&lhs, &rhs);
}

inline bool
operator>(const Date & lhs, const Date & rhs)
{
    return Date_greater_than(&lhs, &rhs);
}

inline bool
operator>=(const Date & lhs, const Date & rhs)
{
    return Date_greater_than_or_equal(&lhs, &rhs);
}

