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

int_delta TimeDelta::get_nanoseconds() const {
    return TimeDelta_get_nanoseconds(this);
}

int_delta TimeDelta::get_microseconds() const {
    return TimeDelta_get_microseconds(this);
}

double TimeDelta::get_microseconds_decimal() const {
    return TimeDelta_get_microseconds_decimal(this);
}

int_delta TimeDelta::get_milliseconds() const {
    return TimeDelta_get_milliseconds(this);
}

double TimeDelta::get_milliseconds_decimal() const {
    return TimeDelta_get_milliseconds_decimal(this);
}

int_delta TimeDelta::get_seconds() const {
    return TimeDelta_get_seconds(this);
}

double TimeDelta::get_seconds_decimal() const {
    return TimeDelta_get_seconds_decimal(this);
}

int_delta TimeDelta::get_minutes() const {
    return TimeDelta_get_minutes(this);
}

double TimeDelta::get_minutes_decimal() const {
    return TimeDelta_get_minutes_decimal(this);
}

int_delta TimeDelta::get_hours() const {
    return TimeDelta_get_hours(this);
}

double TimeDelta::get_hours_decimal() const {
    return TimeDelta_get_hours_decimal(this);
}

int_delta TimeDelta::get_days() const {
    return TimeDelta_get_days(this);
}

double TimeDelta::get_days_decimal() const {
    return TimeDelta_get_days_decimal(this);
}

int_delta TimeDelta::get_weeks() const {
    return TimeDelta_get_weeks(this);
}

double TimeDelta::get_weeks_decimal() const {
    return TimeDelta_get_weeks_decimal(this);
}

DayDelta TimeDelta::get_day_delta_truncated() const {
    return TimeDelta_get_day_delta_truncated(this);
}

DayDelta TimeDelta::get_day_delta_rounded() const {
    return TimeDelta_get_day_delta_rounded(this);
}

DayDelta TimeDelta::get_day_delta_abs_ceil() const {
    return TimeDelta_get_day_delta_abs_ceil(this);
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

TimeDelta & TimeDelta::operator*=(const int & scaleFactor) {
    TimeDelta_multiply_by(this, scaleFactor);
    return *this;
}

TimeDelta & TimeDelta::operator*=(const double & scaleFactor) {
    TimeDelta_multiply_by_decimal(this, scaleFactor);
    return *this;
}

TimeDelta & TimeDelta::operator/=(const int & scaleFactor) {
    TimeDelta_divide_by(this, scaleFactor);
    return *this;
}

TimeDelta & TimeDelta::operator/=(const double & scaleFactor) {
    TimeDelta_divide_by_decimal(this, scaleFactor);
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

TimeDelta & TimeDelta::operator+=(const TimeDelta & timeDeltaToAdd) {
    TimeDelta_add_time_delta(this, &timeDeltaToAdd);
    return *this;
}

TimeDelta & TimeDelta::operator-=(const TimeDelta & timeDeltaToSubtract) {
    TimeDelta_subtract_time_delta(this, &timeDeltaToSubtract);
    return *this;
}

const TimeDelta operator+(const TimeDelta & lhs, const TimeDelta & rhs) {
    return (TimeDelta(lhs) += rhs);
}

const TimeDelta operator-(const TimeDelta & lhs, const TimeDelta & rhs) {
    return (TimeDelta(lhs) -= rhs);
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

