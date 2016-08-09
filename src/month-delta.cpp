/*
 * Present - Date/Time Library
 *
 * Implementation of the MonthDelta C++ class
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-month-delta-data.h"

#include "present/month-delta.h"

MonthDelta MonthDelta::from_months(int_month_delta month_delta) {
    return MonthDelta_from_months(month_delta);
}

MonthDelta MonthDelta::from_years(int_year_delta year_delta) {
    return MonthDelta_from_years(year_delta);
}

MonthDelta MonthDelta::zero() {
    return MonthDelta_zero();
}

int_month_delta MonthDelta::get_months() const {
    return MonthDelta_get_months(this);
}

int_year_delta MonthDelta::get_years() const {
    return MonthDelta_get_years(this);
}

double MonthDelta::get_years_decimal() const {
    return MonthDelta_get_years_decimal(this);
}

bool MonthDelta::is_negative() const {
    return MonthDelta_is_negative(this);
}

void MonthDelta::negate() {
    MonthDelta_negate(this);
}

MonthDelta & MonthDelta::operator++() {
    this->data_.delta_months += 1;
    return *this;
}

MonthDelta MonthDelta::operator++(int) {
    MonthDelta copy(*this);
    operator++();
    return copy;
}

MonthDelta & MonthDelta::operator--() {
    this->data_.delta_months -= 1;
    return *this;
}

MonthDelta MonthDelta::operator--(int) {
    MonthDelta copy(*this);
    operator--();
    return copy;
}

MonthDelta & MonthDelta::operator*=(const int & scaleFactor) {
    MonthDelta_multiply_by(this, scaleFactor);
    return *this;
}

MonthDelta & MonthDelta::operator/=(const int & scaleFactor) {
    MonthDelta_divide_by(this, scaleFactor);
    return *this;
}

const MonthDelta operator*(const MonthDelta & lhs, const int & rhs) {
    return (MonthDelta(lhs) *= rhs);
}

const MonthDelta operator/(const MonthDelta & lhs, const int & rhs) {
    return (MonthDelta(lhs) /= rhs);
}

MonthDelta & MonthDelta::operator+=(const MonthDelta & monthDeltaToAdd) {
    MonthDelta_add_month_delta(this, &monthDeltaToAdd);
    return *this;
}

MonthDelta & MonthDelta::operator-=(const MonthDelta & monthDeltaToSubtract) {
    MonthDelta_subtract_month_delta(this, &monthDeltaToSubtract);
    return *this;
}

const MonthDelta operator+(const MonthDelta & lhs, const MonthDelta & rhs) {
    return (MonthDelta(lhs) += rhs);
}

const MonthDelta operator-(const MonthDelta & lhs, const MonthDelta & rhs) {
    return (MonthDelta(lhs) -= rhs);
}

bool operator==(const MonthDelta & lhs, const MonthDelta & rhs) {
    return MonthDelta_equal(&lhs, &rhs);
}

bool operator!=(const MonthDelta & lhs, const MonthDelta & rhs) {
    return !(lhs == rhs);
}

bool operator<(const MonthDelta & lhs, const MonthDelta & rhs) {
    return MonthDelta_less_than(&lhs, &rhs);
}

bool operator<=(const MonthDelta & lhs, const MonthDelta & rhs) {
    return MonthDelta_less_than_or_equal(&lhs, &rhs);
}

bool operator>(const MonthDelta & lhs, const MonthDelta & rhs) {
    return MonthDelta_greater_than(&lhs, &rhs);
}

bool operator>=(const MonthDelta & lhs, const MonthDelta & rhs) {
    return MonthDelta_greater_than_or_equal(&lhs, &rhs);
}

