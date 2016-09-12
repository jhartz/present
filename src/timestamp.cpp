/*
 * Present - Date/Time Library
 *
 * Implementation of the Timestamp C++ class
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-timestamp-data.h"

#include "present/clock-time.h"
#include "present/date.h"
#include "present/time-delta.h"

#include "present/timestamp.h"

Timestamp Timestamp::create(const time_t timestamp) {
    return Timestamp_from_time_t(timestamp);
}

Timestamp Timestamp::create(
        const struct tm & tm,
        const TimeDelta & timeZoneOffset) {
    return Timestamp_from_struct_tm(tm, &timeZoneOffset);
}

Timestamp Timestamp::create_utc(const struct tm & tm) {
    return Timestamp_from_struct_tm_utc(tm);
}

Timestamp Timestamp::create_local(const struct tm & tm) {
    return Timestamp_from_struct_tm_local(tm);
}

Timestamp Timestamp::create(
        const Date & date,
        const ClockTime & clockTime,
        const TimeDelta & timeZoneOffset) {
    return Timestamp_create(&date, &clockTime, &timeZoneOffset);
}

Timestamp Timestamp::create_utc(
        const Date & date,
        const ClockTime & clockTime) {
    return Timestamp_create_utc(&date, &clockTime);
}

Timestamp Timestamp::create_local(
        const Date & date,
        const ClockTime & clockTime) {
    return Timestamp_create_local(&date, &clockTime);
}

Timestamp Timestamp::now() {
    return Timestamp_now();
}

Timestamp Timestamp::epoch() {
    return Timestamp_epoch();
}

time_t Timestamp::get_time_t() const {
    return Timestamp_get_time_t(this);
}

struct tm Timestamp::get_struct_tm(const TimeDelta & timeZoneOffset) const {
    return Timestamp_get_struct_tm(this, &timeZoneOffset);
}

struct tm Timestamp::get_struct_tm_utc() const {
    return Timestamp_get_struct_tm_utc(this);
}

struct tm Timestamp::get_struct_tm_local() const {
    return Timestamp_get_struct_tm_local(this);
}

Date Timestamp::get_date(const TimeDelta & timeZoneOffset) const {
    return Timestamp_get_date(this, &timeZoneOffset);
}

Date Timestamp::get_date_utc() const {
    return Timestamp_get_date_utc(this);
}

Date Timestamp::get_date_local() const {
    return Timestamp_get_date_local(this);
}

ClockTime Timestamp::get_clock_time(const TimeDelta & timeZoneOffset) const {
    return Timestamp_get_clock_time(this, &timeZoneOffset);
}

ClockTime Timestamp::get_clock_time_utc() const {
    return Timestamp_get_clock_time_utc(this);
}

ClockTime Timestamp::get_clock_time_local() const {
    return Timestamp_get_clock_time_local(this);
}

TimeDelta Timestamp::get_difference(const Timestamp & other) const {
    return Timestamp_get_difference(this, &other);
}

TimeDelta Timestamp::get_absolute_difference(const Timestamp & other) const {
    return Timestamp_get_absolute_difference(this, &other);
}

Timestamp & Timestamp::operator+=(const TimeDelta & delta) {
    Timestamp_add_time_delta(this, &delta);
    return *this;
}

Timestamp & Timestamp::operator+=(const DayDelta & delta) {
    Timestamp_add_day_delta(this, &delta);
    return *this;
}

Timestamp & Timestamp::operator+=(const MonthDelta & delta) {
    Timestamp_add_month_delta(this, &delta);
    return *this;
}

Timestamp & Timestamp::operator-=(const TimeDelta & delta) {
    Timestamp_subtract_time_delta(this, &delta);
    return *this;
}

Timestamp & Timestamp::operator-=(const DayDelta & delta) {
    Timestamp_subtract_day_delta(this, &delta);
    return *this;
}

Timestamp & Timestamp::operator-=(const MonthDelta & delta) {
    Timestamp_subtract_month_delta(this, &delta);
    return *this;
}

const Timestamp operator+(const Timestamp & lhs, const TimeDelta & rhs) {
    return (Timestamp(lhs) += rhs);
}

const Timestamp operator+(const Timestamp & lhs, const DayDelta & rhs) {
    return (Timestamp(lhs) += rhs);
}

const Timestamp operator+(const Timestamp & lhs, const MonthDelta & rhs) {
    return (Timestamp(lhs) += rhs);
}

const Timestamp operator-(const Timestamp & lhs, const TimeDelta & rhs) {
    return (Timestamp(lhs) -= rhs);
}

const Timestamp operator-(const Timestamp & lhs, const DayDelta & rhs) {
    return (Timestamp(lhs) -= rhs);
}

const Timestamp operator-(const Timestamp & lhs, const MonthDelta & rhs) {
    return (Timestamp(lhs) -= rhs);
}

int Timestamp::compare(const Timestamp & lhs, const Timestamp & rhs) {
    return Timestamp_compare(&lhs, &rhs);
}

bool operator==(const Timestamp & lhs, const Timestamp & rhs) {
    return Timestamp_equal(&lhs, &rhs);
}

bool operator!=(const Timestamp & lhs, const Timestamp & rhs) {
    return !(lhs == rhs);
}

bool operator<(const Timestamp & lhs, const Timestamp & rhs) {
    return Timestamp_less_than(&lhs, &rhs);
}

bool operator<=(const Timestamp & lhs, const Timestamp & rhs) {
    return Timestamp_less_than_or_equal(&lhs, &rhs);
}

bool operator>(const Timestamp & lhs, const Timestamp & rhs) {
    return Timestamp_greater_than(&lhs, &rhs);
}

bool operator>=(const Timestamp & lhs, const Timestamp & rhs) {
    return Timestamp_greater_than_or_equal(&lhs, &rhs);
}

