/*
 * Present - Date/Time Library
 *
 * Implementation of the MonthDelta C++ class
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>

#include "present/utils/types.h"
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

int_month_delta MonthDelta::months() const {
    return MonthDelta_months(this);
}

int_year_delta MonthDelta::years() const {
    return MonthDelta_years(this);
}

double MonthDelta::years_decimal() const {
    return MonthDelta_years_decimal(this);
}

bool MonthDelta::is_negative() const {
    return MonthDelta_is_negative(this);
}

void MonthDelta::negate() {
    MonthDelta_negate(this);
}

MonthDelta MonthDelta::operator-() const {
    assert(this->error == 0);

    MonthDelta copy(*this);
    copy.negate();
    return copy;
}

MonthDelta & MonthDelta::operator++() {
    assert(this->error == 0);

    this->data_.delta_months += 1;
    return *this;
}

MonthDelta MonthDelta::operator++(int) {
    assert(this->error == 0);

    MonthDelta copy(*this);
    operator++();
    return copy;
}

MonthDelta & MonthDelta::operator--() {
    assert(this->error == 0);

    this->data_.delta_months -= 1;
    return *this;
}

MonthDelta MonthDelta::operator--(int) {
    assert(this->error == 0);

    MonthDelta copy(*this);
    operator--();
    return copy;
}

MonthDelta & MonthDelta::operator*=(const int & scale_factor) {
    MonthDelta_multiply_by(this, scale_factor);
    return *this;
}

MonthDelta & MonthDelta::operator/=(const int & scale_factor) {
    MonthDelta_divide_by(this, scale_factor);
    return *this;
}

const MonthDelta operator*(const MonthDelta & lhs, const int & rhs) {
    return (MonthDelta(lhs) *= rhs);
}

const MonthDelta operator/(const MonthDelta & lhs, const int & rhs) {
    return (MonthDelta(lhs) /= rhs);
}

MonthDelta & MonthDelta::operator+=(const MonthDelta & other) {
    MonthDelta_add(this, &other);
    return *this;
}

MonthDelta & MonthDelta::operator-=(const MonthDelta & other) {
    MonthDelta_subtract(this, &other);
    return *this;
}

const MonthDelta operator+(const MonthDelta & lhs, const MonthDelta & rhs) {
    return (MonthDelta(lhs) += rhs);
}

const MonthDelta operator-(const MonthDelta & lhs, const MonthDelta & rhs) {
    return (MonthDelta(lhs) -= rhs);
}

int MonthDelta::compare(const MonthDelta & lhs, const MonthDelta & rhs) {
    return MonthDelta_compare(&lhs, &rhs);
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

