/*
 * Present - Date/Time Library
 *
 * Implementation of the Timestamp methods
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

struct Timestamp
Timestamp_create_from_time_t(const time_t timestamp) {

}

struct Timestamp
Timestamp_create_from_struct_tm(
        const struct tm tm,
        const struct TimeDelta * const timeZoneOffset) {

}

struct Timestamp
Timestamp_create_from_struct_tm_utc(const struct tm tm) {

}

struct Timestamp
Timestamp_create_from_struct_tm_local(const struct tm tm) {

}

struct Timestamp
Timestamp_create(
        const struct Date * const date,
        const struct ClockTime * const clockTime,
        const struct TimeDelta * const timeZoneOffset) {

}

struct Timestamp
Timestamp_create_utc(
        const struct Date * const date,
        const struct ClockTime * const clockTime) {

}

struct Timestamp
Timestamp_create_local(
        const struct Date * const date,
        const struct ClockTime * const clockTime) {

}

struct Timestamp
Timestamp_now() {

}

struct Timestamp
Timestamp_epoch() {

}

time_t
Timestamp_get_time_t(const struct Timestamp * const self) {

}

struct tm
Timestamp_get_struct_tm(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset) {

}

struct tm
Timestamp_get_struct_tm_utc(const struct Timestamp * const self) {

}

struct tm
Timestamp_get_struct_tm_local(const struct Timestamp * const self) {

}

struct Date
Timestamp_get_date(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset) {

}

struct Date
Timestamp_get_date_utc(const struct Timestamp * const self) {

}

struct Date
Timestamp_get_date_local(const struct Timestamp * const self) {

}

struct ClockTime
Timestamp_get_clock_time(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset) {

}

struct ClockTime
Timestamp_get_clock_time_utc(const struct Timestamp * const self) {

}

struct ClockTime
Timestamp_get_clock_time_local(const struct Timestamp * const self) {

}

struct TimeDelta
Timestamp_get_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other) {

}

struct TimeDelta
Timestamp_get_absolute_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other) {

}

void
Timestamp_add_time_delta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta) {

}

void
Timestamp_add_month_delta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta) {

}

void
Timestamp_subtract_time_delta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta) {

}

void
Timestamp_subtract_month_delta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta) {

}

bool
Timestamp_equal(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs) {

}

bool
Timestamp_less_than(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs) {

}

bool
Timestamp_less_than_or_equal(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs) {

}

bool
Timestamp_greater_than(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs) {

}

bool
Timestamp_greater_than_or_equal(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs) {

}

