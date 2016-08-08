/*
 * Present - Date/Time Library
 *
 * Implementation of the TimeDelta methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-time-delta-data.h"

#include "present/time-delta.h"

struct TimeDelta
TimeDelta_from_nanoseconds(int_delta nanoseconds) {

}

struct TimeDelta
TimeDelta_from_seconds(int_delta seconds) {

}

struct TimeDelta
TimeDelta_from_minutes(int_delta minutes) {

}

struct TimeDelta
TimeDelta_from_hours(int_delta hours) {

}

struct TimeDelta
TimeDelta_from_days(int_delta days) {

}

struct TimeDelta
TimeDelta_from_weeks(int_delta weeks) {

}

struct TimeDelta
TimeDelta_zero() {

}

int_delta
TimeDelta_get_nanoseconds(const struct TimeDelta * const self) {

}

int_delta
TimeDelta_get_seconds(const struct TimeDelta * const self) {

}

double
TimeDelta_get_seconds_decimal(const struct TimeDelta * const self) {

}

int_delta
TimeDelta_get_minutes(const struct TimeDelta * const self) {

}

double
TimeDelta_get_minutes_decimal(const struct TimeDelta * const self) {

}

int_delta
TimeDelta_get_hours(const struct TimeDelta * const self) {

}

double
TimeDelta_get_hours_decimal(const struct TimeDelta * const self) {

}

int_delta
TimeDelta_get_days(const struct TimeDelta * const self) {

}

double
TimeDelta_get_days_decimal(const struct TimeDelta * const self) {

}

int_delta
TimeDelta_get_weeks(const struct TimeDelta * const self) {

}

double
TimeDelta_get_weeks_decimal(const struct TimeDelta * const self) {

}

void
TimeDelta_multiply_by(struct TimeDelta * const self, const int scaleFactor) {

}

void
TimeDelta_multiply_by_decimal(
        struct TimeDelta * const self,
        const double scaleFactor) {

}

void
TimeDelta_divide_by(struct TimeDelta * const self, const int scaleFactor) {

}

void
TimeDelta_divide_by_decimal(
        struct TimeDelta * const self,
        const double scaleFactor) {

}

void
TimeDelta_add_time_delta(
        struct TimeDelta * const self,
        const struct TimeDelta * const timeDeltaToAdd) {

}

void
TimeDelta_subtract_time_delta(
        struct TimeDelta * const self,
        const struct TimeDelta * const timeDeltaToSubtract) {

}

bool
TimeDelta_equal(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs) {

}

bool
TimeDelta_less_than(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs) {

}

bool
TimeDelta_less_than_or_equal(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs) {

}

bool
TimeDelta_greater_than(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs) {

}

bool
TimeDelta_greater_than_or_equal(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs) {

}

