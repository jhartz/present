/*
 * Present - Date/Time Library
 *
 * Implementation of the TimeDelta C++ class
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-time-delta-data.h"

#include "present/day-delta.h"

#include "present/time-delta.h"

TimeDelta TimeDelta::from_nanoseconds(int_delta nanoseconds) {
    return TimeDelta_from_nanoseconds(nanoseconds);
}

TimeDelta TimeDelta::from_microseconds(int_delta microseconds) {
    return TimeDelta_from_microseconds(microseconds);
}

TimeDelta TimeDelta::from_milliseconds(int_delta milliseconds) {
    return TimeDelta_from_milliseconds(milliseconds);
}

TimeDelta TimeDelta::from_seconds(int_delta seconds) {
    return TimeDelta_from_seconds(seconds);
}

TimeDelta TimeDelta::from_minutes(int_delta minutes) {
    return TimeDelta_from_minutes(minutes);
}

TimeDelta TimeDelta::from_hours(int_delta hours) {
    return TimeDelta_from_hours(hours);
}

TimeDelta TimeDelta::from_days(int_delta days) {
    return TimeDelta_from_days(days);
}

TimeDelta TimeDelta::from_weeks(int_delta weeks) {
    return TimeDelta_from_weeks(weeks);
}

TimeDelta TimeDelta::zero() {
    return TimeDelta_zero();
}

int_delta TimeDelta::nanoseconds() const {
    return TimeDelta_nanoseconds(this);
}

int_delta TimeDelta::microseconds() const {
    return TimeDelta_microseconds(this);
}

double TimeDelta::microseconds_decimal() const {
    return TimeDelta_microseconds_decimal(this);
}

int_delta TimeDelta::milliseconds() const {
    return TimeDelta_milliseconds(this);
}

double TimeDelta::milliseconds_decimal() const {
    return TimeDelta_milliseconds_decimal(this);
}

int_delta TimeDelta::seconds() const {
    return TimeDelta_seconds(this);
}

double TimeDelta::seconds_decimal() const {
    return TimeDelta_seconds_decimal(this);
}

int_delta TimeDelta::minutes() const {
    return TimeDelta_minutes(this);
}

double TimeDelta::minutes_decimal() const {
    return TimeDelta_minutes_decimal(this);
}

int_delta TimeDelta::hours() const {
    return TimeDelta_hours(this);
}

double TimeDelta::hours_decimal() const {
    return TimeDelta_hours_decimal(this);
}

int_delta TimeDelta::days() const {
    return TimeDelta_days(this);
}

double TimeDelta::days_decimal() const {
    return TimeDelta_days_decimal(this);
}

int_delta TimeDelta::weeks() const {
    return TimeDelta_weeks(this);
}

double TimeDelta::weeks_decimal() const {
    return TimeDelta_weeks_decimal(this);
}

DayDelta TimeDelta::to_DayDelta_truncated() const {
    return TimeDelta_to_DayDelta_truncated(this);
}

DayDelta TimeDelta::to_DayDelta_rounded() const {
    return TimeDelta_to_DayDelta_rounded(this);
}

DayDelta TimeDelta::to_DayDelta_abs_ceil() const {
    return TimeDelta_to_DayDelta_abs_ceil(this);
}

bool TimeDelta::is_negative() const {
    return TimeDelta_is_negative(this);
}

void TimeDelta::negate() {
    TimeDelta_negate(this);
}

TimeDelta TimeDelta::operator-() const {
    assert(this->error == 0);

    TimeDelta copy(*this);
    copy.negate();
    return copy;
}

TimeDelta & TimeDelta::operator*=(const int & scale_factor) {
    TimeDelta_multiply_by(this, scale_factor);
    return *this;
}

TimeDelta & TimeDelta::operator*=(const double & scale_factor) {
    TimeDelta_multiply_by_decimal(this, scale_factor);
    return *this;
}

TimeDelta & TimeDelta::operator/=(const int & scale_factor) {
    TimeDelta_divide_by(this, scale_factor);
    return *this;
}

TimeDelta & TimeDelta::operator/=(const double & scale_factor) {
    TimeDelta_divide_by_decimal(this, scale_factor);
    return *this;
}

const TimeDelta operator*(const TimeDelta & lhs, const int & rhs) {
    return (TimeDelta(lhs) *= rhs);
}

const TimeDelta operator*(const TimeDelta & lhs, const double & rhs) {
    return (TimeDelta(lhs) *= rhs);
}

const TimeDelta operator/(const TimeDelta & lhs, const int & rhs) {
    return (TimeDelta(lhs) /= rhs);
}

const TimeDelta operator/(const TimeDelta & lhs, const double & rhs) {
    return (TimeDelta(lhs) /= rhs);
}

TimeDelta & TimeDelta::operator+=(const TimeDelta & other) {
    TimeDelta_add(this, &other);
    return *this;
}

TimeDelta & TimeDelta::operator+=(const DayDelta & other) {
    TimeDelta_add_DayDelta(this, &other);
    return *this;
}

TimeDelta & TimeDelta::operator-=(const TimeDelta & other) {
    TimeDelta_subtract(this, &other);
    return *this;
}

TimeDelta & TimeDelta::operator-=(const DayDelta & other) {
    TimeDelta_subtract_DayDelta(this, &other);
    return *this;
}

const TimeDelta operator+(const TimeDelta & lhs, const TimeDelta & rhs) {
    return (TimeDelta(lhs) += rhs);
}

const TimeDelta operator+(const TimeDelta & lhs, const DayDelta & rhs) {
    return (TimeDelta(lhs) += rhs);
}

const TimeDelta operator+(const DayDelta & lhs, const TimeDelta & rhs) {
    TimeDelta lhs_time_delta = lhs.to_TimeDelta();
    return (lhs_time_delta += rhs);
}

const TimeDelta operator-(const TimeDelta & lhs, const TimeDelta & rhs) {
    return (TimeDelta(lhs) -= rhs);
}

const TimeDelta operator-(const TimeDelta & lhs, const DayDelta & rhs) {
    return (TimeDelta(lhs) -= rhs);
}

const TimeDelta operator-(const DayDelta & lhs, const TimeDelta & rhs) {
    TimeDelta lhs_time_delta = lhs.to_TimeDelta();
    return (lhs_time_delta -= rhs);
}

int TimeDelta::compare(const TimeDelta & lhs, const TimeDelta & rhs) {
    return TimeDelta_compare(&lhs, &rhs);
}

bool operator==(const TimeDelta & lhs, const TimeDelta & rhs) {
    return TimeDelta_equal(&lhs, &rhs);
}

bool operator!=(const TimeDelta & lhs, const TimeDelta & rhs) {
    return !(lhs == rhs);
}

bool operator<(const TimeDelta & lhs, const TimeDelta & rhs) {
    return TimeDelta_less_than(&lhs, &rhs);
}

bool operator<=(const TimeDelta & lhs, const TimeDelta & rhs) {
    return TimeDelta_less_than_or_equal(&lhs, &rhs);
}

bool operator>(const TimeDelta & lhs, const TimeDelta & rhs) {
    return TimeDelta_greater_than(&lhs, &rhs);
}

bool operator>=(const TimeDelta & lhs, const TimeDelta & rhs) {
    return TimeDelta_greater_than_or_equal(&lhs, &rhs);
}

