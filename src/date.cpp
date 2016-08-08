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

#include "present/date.h"

Date Date::create(int_year year) {
    return Date_create_from_year(year);
}

Date Date::create(int_year year, int_month month) {
    return Date_create_from_year_month(year, month);
}

Date Date::create(int_year year, int_month month, int_day day) {
    return Date_create_from_year_month_day(year, month, day);
}

Date Date::create_from_year_week(int_year year, int_week_of_year week_of_year) {
    return Date_create_from_year_week(year, week_of_year);
}

Date Date::create_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week) {
    return Date_create_from_year_week_day(year, week_of_year, day_of_week);
}

Date Date::today() {
    return Date_today();
}

Date Date::yesterday() {
    return Date_yesterday();
}

Date Date::tomorrow() {
    return Date_tomorrow();
}

int_year Date::get_year() const {
    return Date_get_year(this);
}

int_month Date::get_month() const {
    return Date_get_month(this);
}

int_day Date::get_day() const {
    return Date_get_day(this);
}

int_day_of_year Date::get_day_of_year() const {
    return Date_get_day_of_year(this);
}

int_week_of_year Date::get_week_of_year() const {
    return Date_get_week_of_year(this);
}

int_day_of_week Date::get_day_of_week() const {
    return Date_get_day_of_week(this);
}

Date & Date::operator+=(const MonthDelta & delta) {
    Date_add_month_delta(this, &delta);
    return *this;
}

Date & Date::operator-=(const MonthDelta & delta) {
    Date_subtract_month_delta(this, &delta);
    return *this;
}

const Date operator+(const Date & lhs, const MonthDelta & rhs) {
    return (Date(lhs) += rhs);
}

const Date operator-(const Date & lhs, const MonthDelta & rhs) {
    return (Date(lhs) -= rhs);
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

