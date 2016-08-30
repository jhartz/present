/*
 * Present - Date/Time Library
 *
 * Implementation of the ClockTime C++ class
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-clock-time-data.h"

#include "present/time-delta.h"

#include "present/clock-time.h"

ClockTime ClockTime::create(int_hour hour) {
    return ClockTime_create_from_hour(hour);
}

ClockTime ClockTime::create(int_hour hour, int_minute minute) {
    return ClockTime_create_from_hour_minute(hour, minute);
}

ClockTime ClockTime::create(
        int_hour hour,
        int_minute minute,
        int_second second) {
    return ClockTime_create_from_hour_minute_second(hour, minute, second);
}

ClockTime ClockTime::create(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond) {
    return ClockTime_create_from_hour_minute_second_nanosecond(
        hour,
        minute,
        second,
        nanosecond);
}

ClockTime ClockTime::create_with_decimal_seconds(
        int_hour hour,
        int_minute minute,
        double second) {
    return ClockTime_create_with_decimal_seconds(hour, minute, second);
}

ClockTime ClockTime::midnight() {
    return ClockTime_midnight();
}

ClockTime ClockTime::noon() {
    return ClockTime_noon();
}

int_hour ClockTime::get_hour() const {
    return ClockTime_get_hour(this);
}

int_minute ClockTime::get_minute() const {
    return ClockTime_get_minute(this);
}

int_second ClockTime::get_second() const {
    return ClockTime_get_second(this);
}

int_nanosecond ClockTime::get_nanosecond() const {
    return ClockTime_get_nanosecond(this);
}

double ClockTime::get_second_decimal() const {
    return ClockTime_get_second_decimal(this);
}

TimeDelta ClockTime::time_since_midnight() const {
    return ClockTime_time_since_midnight(this);
}

ClockTime & ClockTime::operator+=(const TimeDelta & delta) {
    ClockTime_add_time_delta(this, &delta);
    return *this;
}

ClockTime & ClockTime::operator-=(const TimeDelta & delta) {
    ClockTime_subtract_time_delta(this, &delta);
    return *this;
}

const ClockTime operator+(const ClockTime & lhs, const TimeDelta & rhs) {
    return (ClockTime(lhs) += rhs);
}

const ClockTime operator-(const ClockTime & lhs, const TimeDelta & rhs) {
    return (ClockTime(lhs) -= rhs);
}

bool operator==(const ClockTime & lhs, const ClockTime & rhs) {
    return ClockTime_equal(&lhs, &rhs);
}

bool operator!=(const ClockTime & lhs, const ClockTime & rhs) {
    return !(lhs == rhs);
}

bool operator<(const ClockTime & lhs, const ClockTime & rhs) {
    return ClockTime_less_than(&lhs, &rhs);
}

bool operator<=(const ClockTime & lhs, const ClockTime & rhs) {
    return ClockTime_less_than_or_equal(&lhs, &rhs);
}

bool operator>(const ClockTime & lhs, const ClockTime & rhs) {
    return ClockTime_greater_than(&lhs, &rhs);
}

bool operator>=(const ClockTime & lhs, const ClockTime & rhs) {
    return ClockTime_greater_than_or_equal(&lhs, &rhs);
}

