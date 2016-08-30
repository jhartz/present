/*
 * Present - Date/Time Library
 *
 * Implementation of the ClockTime methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>
#include <math.h>
#include <stddef.h>

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-clock-time-data.h"

#include "impl-constants.h"
#include "impl-utils.h"

#include "present/time-delta.h"

#include "present/clock-time.h"

/**
 * Create a new ClockTime instance based on its data parameters.
 */
static struct ClockTime
new_clock_time(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond) {

    CONSTRUCTOR_HEAD(ClockTime);

    if (hour == 24) hour = 0;
    if (hour < 0 || hour > 24) {
        CONSTRUCTOR_ERROR_RETURN(ClockTime, HOUR_OUT_OF_RANGE);
    }
    if (minute < 0 || minute >= 60) {
        CONSTRUCTOR_ERROR_RETURN(ClockTime, MINUTE_OUT_OF_RANGE);
    }
    /* 61 because of leap seconds :( */
    if (second < 0 || second >= 61) {
        CONSTRUCTOR_ERROR_RETURN(ClockTime, SECOND_OUT_OF_RANGE);
    }
    if (nanosecond < 0 || nanosecond >= NANOSECONDS_IN_SECOND) {
        CONSTRUCTOR_ERROR_RETURN(ClockTime, NANOSECOND_OUT_OF_RANGE);
    }

    struct PresentClockTimeData data;
    data.hour = hour;
    data.minute = minute;
    data.second = second;
    data.nanosecond = nanosecond;
    CONSTRUCTOR_RETURN(ClockTime, data);
}

/**
 * Check the bounds on data.{nanosecond,second,minute,hour} and modify or
 * wraps around as necessary.
 */
void check_clock_time(struct ClockTime * const self) {
#define d self->data_
    if (d.nanosecond >= NANOSECONDS_IN_SECOND) {
        d.second += d.nanosecond / NANOSECONDS_IN_SECOND;
        d.nanosecond %= NANOSECONDS_IN_SECOND;
    }
    while (d.nanosecond < 0) {
        d.second -= 1;
        d.nanosecond += NANOSECONDS_IN_SECOND;
    }

    if (d.second >= 60) {
        d.minute += d.second / 60;
        d.second %= 60;
    }
    while (d.second < 0) {
        d.minute -= 1;
        d.second += 60;
    }

    if (d.minute >= 60) {
        d.hour += d.minute / 60;
        d.minute %= 60;
    }
    while (d.minute < 0) {
        d.hour -= 1;
        d.minute += 60;
    }

    if (d.hour >= 24) {
        d.hour %= 24;
    }
    while (d.hour < 0) {
        d.hour += 24;
    }
#undef d
}

struct ClockTime
ClockTime_create_from_hour(int_hour hour) {
    return new_clock_time(hour, 0, 0, 0);
}

struct ClockTime
ClockTime_create_from_hour_minute(int_hour hour, int_minute minute) {
    return new_clock_time(hour, minute, 0, 0);
}

struct ClockTime
ClockTime_create_from_hour_minute_second(
        int_hour hour,
        int_minute minute,
        int_second second) {
    return new_clock_time(hour, minute, second, 0);
}

struct ClockTime
ClockTime_create_from_hour_minute_second_nanosecond(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond) {
    return new_clock_time(hour, minute, second, nanosecond);
}

struct ClockTime
ClockTime_create_with_decimal_seconds(
        int_hour hour,
        int_minute minute,
        double second) {
    int_second secondInt = (int_second) second;
    second = (second - secondInt) * (double) NANOSECONDS_IN_SECOND;
    return new_clock_time(hour, minute, secondInt,
            (int_nanosecond) round(second));
}

struct ClockTime
ClockTime_midnight() {
    return new_clock_time(0, 0, 0, 0);
}

struct ClockTime
ClockTime_noon() {
    return new_clock_time(12, 0, 0, 0);
}

int_hour
ClockTime_get_hour(const struct ClockTime * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.hour;
}

int_minute
ClockTime_get_minute(const struct ClockTime * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.minute;
}

int_second
ClockTime_get_second(const struct ClockTime * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.second;
}

int_nanosecond
ClockTime_get_nanosecond(const struct ClockTime * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.nanosecond;
}

double
ClockTime_get_second_decimal(const struct ClockTime * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return (self->data_.second +
            ((double)self->data_.nanosecond / (double)NANOSECONDS_IN_SECOND));
}

struct TimeDelta
ClockTime_time_since_midnight(const struct ClockTime * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    struct TimeDelta delta = TimeDelta_from_seconds(
            self->data_.second +
            self->data_.minute * SECONDS_IN_MINUTE +
            self->data_.hour * SECONDS_IN_HOUR);
    struct TimeDelta nsDelta = TimeDelta_from_nanoseconds(
            self->data_.nanosecond);
    TimeDelta_add_time_delta(&delta, &nsDelta);
    return delta;
}

void
ClockTime_add_time_delta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.second += delta->data_.delta_seconds;
    self->data_.nanosecond += delta->data_.delta_nanoseconds;

    check_clock_time(self);
}

void
ClockTime_subtract_time_delta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.second -= delta->data_.delta_seconds;
    self->data_.nanosecond -= delta->data_.delta_nanoseconds;

    check_clock_time(self);
}

STRUCT_COMPARISON_OPERATORS(ClockTime, hour, minute, second, nanosecond)

