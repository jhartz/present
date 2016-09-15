/*
 * Present - Date/Time Library
 *
 * Implementation of the Date C++ class
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-date-data.h"

#include "present/day-delta.h"

#include "present/date.h"

Date Date::create(int_year year) {
    return Date_from_year(year);
}

Date Date::create(int_year year, int_month month) {
    return Date_from_year_month(year, month);
}

Date Date::create(int_year year, int_month month, int_day day) {
    return Date_from_year_month_day(year, month, day);
}

Date Date::from_year_day(int_year year, int_day_of_year day_of_year) {
    return Date_from_year_day(year, day_of_year);
}

Date Date::from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week) {
    return Date_from_year_week_day(year, week_of_year, day_of_week);
}

int_year Date::year() const {
    return Date_year(this);
}

int_month Date::month() const {
    return Date_month(this);
}

int_day Date::day() const {
    return Date_day(this);
}

int_day_of_year Date::day_of_year() const {
    return Date_day_of_year(this);
}

struct PresentWeekYear Date::week_of_year() const {
    return Date_week_of_year(this);
}

int_day_of_week Date::day_of_week() const {
    return Date_day_of_week(this);
}

DayDelta Date::difference(const Date & other) const {
    return Date_difference(this, &other);
}

DayDelta Date::absolute_difference(const Date & other) const {
    return Date_absolute_difference(this, &other);
}

Date & Date::operator+=(const DayDelta & delta) {
    Date_add_DayDelta(this, &delta);
    return *this;
}

Date & Date::operator+=(const MonthDelta & delta) {
    Date_add_MonthDelta(this, &delta);
    return *this;
}

Date & Date::operator-=(const DayDelta & delta) {
    Date_subtract_DayDelta(this, &delta);
    return *this;
}

Date & Date::operator-=(const MonthDelta & delta) {
    Date_subtract_MonthDelta(this, &delta);
    return *this;
}

const Date operator+(const Date & lhs, const DayDelta & rhs) {
    return (Date(lhs) += rhs);
}
const Date operator+(const DayDelta & lhs, const Date & rhs) {
    return (Date(rhs) += lhs);
}

const Date operator+(const Date & lhs, const MonthDelta & rhs) {
    return (Date(lhs) += rhs);
}
const Date operator+(const MonthDelta & lhs, const Date & rhs) {
    return (Date(rhs) += lhs);
}

const Date operator-(const Date & lhs, const DayDelta & rhs) {
    return (Date(lhs) -= rhs);
}

const Date operator-(const Date & lhs, const MonthDelta & rhs) {
    return (Date(lhs) -= rhs);
}

int Date::compare(const Date & lhs, const Date & rhs) {
    return Date_compare(&lhs, &rhs);
}

bool operator==(const Date & lhs, const Date & rhs) {
    return Date_equal(&lhs, &rhs);
}

bool operator!=(const Date & lhs, const Date & rhs) {
    return !(lhs == rhs);
}

bool operator<(const Date & lhs, const Date & rhs) {
    return Date_less_than(&lhs, &rhs);
}

bool operator<=(const Date & lhs, const Date & rhs) {
    return Date_less_than_or_equal(&lhs, &rhs);
}

bool operator>(const Date & lhs, const Date & rhs) {
    return Date_greater_than(&lhs, &rhs);
}

bool operator>=(const Date & lhs, const Date & rhs) {
    return Date_greater_than_or_equal(&lhs, &rhs);
}

