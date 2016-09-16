/*
 * Present - Date/Time Library
 *
 * Implementation of the DayDelta C++ class
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>

#include "present/utils/types.h"
#include "present/impl/present-day-delta-data.h"

#include "present/time-delta.h"

#include "present/day-delta.h"

DayDelta DayDelta::from_days(int_delta days) {
    return DayDelta_from_days(days);
}

DayDelta DayDelta::from_weeks(int_delta weeks) {
    return DayDelta_from_weeks(weeks);
}

DayDelta DayDelta::zero() {
    return DayDelta_zero();
}

int_delta DayDelta::days() const {
    return DayDelta_days(this);
}

int_delta DayDelta::weeks() const {
    return DayDelta_weeks(this);
}

double DayDelta::weeks_decimal() const {
    return DayDelta_weeks_decimal(this);
}

TimeDelta DayDelta::to_TimeDelta() const {
    return DayDelta_to_TimeDelta(this);
}

bool DayDelta::is_negative() const {
    return DayDelta_is_negative(this);
}

void DayDelta::negate() {
    DayDelta_negate(this);
}

DayDelta DayDelta::operator-() const {
    assert(this->error == 0);

    DayDelta copy(*this);
    copy.negate();
    return copy;
}

DayDelta & DayDelta::operator++() {
    assert(this->error == 0);

    this->data_.delta_days += 1;
    return *this;
}

DayDelta DayDelta::operator++(int) {
    assert(this->error == 0);

    DayDelta copy(*this);
    operator++();
    return copy;
}

DayDelta & DayDelta::operator--() {
    assert(this->error == 0);

    this->data_.delta_days -= 1;
    return *this;
}

DayDelta DayDelta::operator--(int) {
    assert(this->error == 0);

    DayDelta copy(*this);
    operator--();
    return copy;
}

DayDelta & DayDelta::operator*=(const int & scale_factor) {
    DayDelta_multiply_by(this, scale_factor);
    return *this;
}

DayDelta & DayDelta::operator/=(const int & scale_factor) {
    DayDelta_divide_by(this, scale_factor);
    return *this;
}

const DayDelta operator*(const DayDelta & lhs, const int & rhs) {
    return (DayDelta(lhs) *= rhs);
}

const DayDelta operator/(const DayDelta & lhs, const int & rhs) {
    return (DayDelta(lhs) /= rhs);
}

DayDelta & DayDelta::operator+=(const DayDelta & other) {
    DayDelta_add(this, &other);
    return *this;
}

DayDelta & DayDelta::operator-=(const DayDelta & other) {
    DayDelta_subtract(this, &other);
    return *this;
}

const DayDelta operator+(const DayDelta & lhs, const DayDelta & rhs) {
    return (DayDelta(lhs) += rhs);
}

const DayDelta operator-(const DayDelta & lhs, const DayDelta & rhs) {
    return (DayDelta(lhs) -= rhs);
}

int DayDelta::compare(const DayDelta & lhs, const DayDelta & rhs) {
    return DayDelta_compare(&lhs, &rhs);
}

bool operator==(const DayDelta & lhs, const DayDelta & rhs) {
    return DayDelta_equal(&lhs, &rhs);
}

bool operator!=(const DayDelta & lhs, const DayDelta & rhs) {
    return !(lhs == rhs);
}

bool operator<(const DayDelta & lhs, const DayDelta & rhs) {
    return DayDelta_less_than(&lhs, &rhs);
}

bool operator<=(const DayDelta & lhs, const DayDelta & rhs) {
    return DayDelta_less_than_or_equal(&lhs, &rhs);
}

bool operator>(const DayDelta & lhs, const DayDelta & rhs) {
    return DayDelta_greater_than(&lhs, &rhs);
}

bool operator>=(const DayDelta & lhs, const DayDelta & rhs) {
    return DayDelta_greater_than_or_equal(&lhs, &rhs);
}

