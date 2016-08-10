/*
 * Present - Date/Time Library
 *
 * Implementation of the ClockTime methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>
#include <stddef.h>

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-clock-time-data.h"

#include "impl-constants.h"
#include "impl-utils.h"

#include "present/time-delta.h"

#include "present/clock-time.h"

// Create a new ClockTime instance based on its data parameters
static struct ClockTime
newClockTime(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond) {
    if (hour == 24) hour = 0;
    assert(hour >= 0 && hour < 24);
    assert(minute >= 0 && minute < 60);
    assert(second >= 0 && second < 61); // leap seconds :(
    assert(nanosecond >= 0 && nanosecond < NANOSECONDS_IN_SECOND);

    struct PresentClockTimeData data;
    data.hour = hour;
    data.minute = minute;
    data.second = second;
    data.nanosecond = nanosecond;
    WRAP_DATA_AND_RETURN(ClockTime, data);
}

// Check the bounds on data.{nanosecond,second,minute,hour} and modify or
// wraps around as necessary
void checkClockTime(struct ClockTime * const self) {
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
    return newClockTime(hour, 0, 0, 0);
}

struct ClockTime
ClockTime_create_from_hour_minute(int_hour hour, int_minute minute) {
    return newClockTime(hour, minute, 0, 0);
}

struct ClockTime
ClockTime_create_from_hour_minute_second(
        int_hour hour,
        int_minute minute,
        int_second second) {
    return newClockTime(hour, minute, second, 0);
}

struct ClockTime
ClockTime_create_from_hour_minute_second_nanosecond(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond) {
    return newClockTime(hour, minute, second, nanosecond);
}

struct ClockTime
ClockTime_create_with_decimal_seconds(
        int_hour hour,
        int_minute minute,
        double second) {
    return newClockTime(hour, minute, (int_second)second,
            (int_nanosecond)(second * (double)NANOSECONDS_IN_SECOND));
}

struct ClockTime
ClockTime_midnight() {
    return newClockTime(0, 0, 0, 0);
}

struct ClockTime
ClockTime_noon() {
    return newClockTime(12, 0, 0, 0);
}

int_hour
ClockTime_get_hour(const struct ClockTime * const self) {
    assert(self != NULL);
    return self->data_.hour;
}

int_minute
ClockTime_get_minute(const struct ClockTime * const self) {
    assert(self != NULL);
    return self->data_.minute;
}

int_second
ClockTime_get_second(const struct ClockTime * const self) {
    assert(self != NULL);
    return self->data_.second;
}

int_nanosecond
ClockTime_get_nanosecond(const struct ClockTime * const self) {
    assert(self != NULL);
    return self->data_.nanosecond;
}

double
ClockTime_get_second_decimal(const struct ClockTime * const self) {
    assert(self != NULL);
    return (self->data_.second +
            ((double)self->data_.nanosecond / (double)NANOSECONDS_IN_SECOND));
}

void
ClockTime_add_time_delta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta) {
    assert(self != NULL);
    assert(delta != NULL);

    self->data_.second += delta->data_.delta_seconds;
    self->data_.nanosecond += delta->data_.delta_nanoseconds;

    checkClockTime(self);
}

void
ClockTime_subtract_time_delta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta) {
    assert(self != NULL);
    assert(delta != NULL);

    self->data_.second -= delta->data_.delta_seconds;
    self->data_.nanosecond -= delta->data_.delta_nanoseconds;

    checkClockTime(self);
}

bool
ClockTime_equal(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs) {
    assert(lhs != NULL);
    assert(rhs != NULL);
    return (lhs->data_.hour == rhs->data_.hour &&
            lhs->data_.minute == rhs->data_.minute &&
            lhs->data_.second == rhs->data_.second &&
            lhs->data_.nanosecond == rhs->data_.nanosecond);
}

STRUCT_INEQUALITY_OPERATORS(ClockTime, hour, minute, second, nanosecond)

