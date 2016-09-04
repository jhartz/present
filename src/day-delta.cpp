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
#include "present/utils/utils.h"
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

int_delta DayDelta::get_days() const {
    return DayDelta_get_days(this);
}

int_delta DayDelta::get_weeks() const {
    return DayDelta_get_weeks(this);
}

double DayDelta::get_weeks_decimal() const {
    return DayDelta_get_weeks_decimal(this);
}

TimeDelta DayDelta::get_time_delta() const {
    return DayDelta_get_time_delta(this);
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

DayDelta & DayDelta::operator*=(const int & scaleFactor) {
    DayDelta_multiply_by(this, scaleFactor);
    return *this;
}

DayDelta & DayDelta::operator/=(const int & scaleFactor) {
    DayDelta_divide_by(this, scaleFactor);
    return *this;
}

const DayDelta operator*(const DayDelta & lhs, const int & rhs) {
    return (DayDelta(lhs) *= rhs);
}

const DayDelta operator/(const DayDelta & lhs, const int & rhs) {
    return (DayDelta(lhs) /= rhs);
}

DayDelta & DayDelta::operator+=(const DayDelta & dayDeltaToAdd) {
    DayDelta_add_day_delta(this, &dayDeltaToAdd);
    return *this;
}

DayDelta & DayDelta::operator-=(const DayDelta & dayDeltaToSubtract) {
    DayDelta_subtract_day_delta(this, &dayDeltaToSubtract);
    return *this;
}

const DayDelta operator+(const DayDelta & lhs, const DayDelta & rhs) {
    return (DayDelta(lhs) += rhs);
}

const DayDelta operator-(const DayDelta & lhs, const DayDelta & rhs) {
    return (DayDelta(lhs) -= rhs);
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

