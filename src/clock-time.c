/*
 * Present - Date/Time Library
 *
 * Implementation of the ClockTime methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-clock-time-data.h"

#include "present/time-delta.h"

#include "present/clock-time.h"

struct ClockTime
ClockTime_create_from_hour(int_hour hour) {

}

struct ClockTime
ClockTime_create_from_hour_minute(int_hour hour, int_minute minute) {

}

struct ClockTime
ClockTime_create_from_hour_minute_second(
        int_hour hour,
        int_minute minute,
        int_second second) {

}

struct ClockTime
ClockTime_create_from_hour_minute_second_nanosecond(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond) {

}

struct ClockTime
ClockTime_create_with_decimal_seconds(
        int_hour hour,
        int_minute minute,
        double second) {

}

struct ClockTime
ClockTime_midnight() {

}

struct ClockTime
ClockTime_noon() {

}

struct ClockTime
ClockTime_now() {

}

int_hour
ClockTime_get_hour(const struct ClockTime * const self) {

}

int_minute
ClockTime_get_minute(const struct ClockTime * const self) {

}

int_second
ClockTime_get_second(const struct ClockTime * const self) {

}

int_nanosecond
ClockTime_get_nanosecond(const struct ClockTime * const self) {

}

double
ClockTime_get_second_decimal(const struct ClockTime * const self) {

}

void
ClockTime_add_time_delta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta) {

}

void
ClockTime_subtract_time_delta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta) {

}

bool
ClockTime_equal(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs) {

}

bool
ClockTime_less_than(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs) {

}

bool
ClockTime_less_than_or_equal(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs) {

}

bool
ClockTime_greater_than(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs) {

}

bool
ClockTime_greater_than_or_equal(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs) {

}

