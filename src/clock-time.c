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

#include "present.h"

#include "utils/constants.h"
#include "utils/impl-utils.h"
#include "utils/time-calls.h"

/**
 * Create a new ClockTime instance based on its data parameters.
 */
static struct ClockTime
new_clock_time(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond)
{
    struct PresentClockTimeData data;
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

    data.seconds = second +
        minute * SECONDS_IN_MINUTE +
        hour * SECONDS_IN_HOUR;
    data.nanoseconds = nanosecond;
    CONSTRUCTOR_RETURN(ClockTime, data);
}

/**
 * Check the bounds on data.{nanosecond,second} and modify or wrap around if
 * necessary.
 */
static void
check_clock_time(struct ClockTime * const self)
{
#define d self->data_
    if (d.nanoseconds >= NANOSECONDS_IN_SECOND) {
        d.seconds += d.nanoseconds / NANOSECONDS_IN_SECOND;
        d.nanoseconds %= NANOSECONDS_IN_SECOND;
    }
    while (d.nanoseconds < 0) {
        d.seconds -= 1;
        d.nanoseconds += NANOSECONDS_IN_SECOND;
    }

    if (d.seconds >= SECONDS_IN_DAY) {
        d.seconds %= SECONDS_IN_DAY;
    }
    while (d.seconds < 0) {
        d.seconds += SECONDS_IN_DAY;
    }
#undef d
}

struct ClockTime
ClockTime_from_hour(int_hour hour)
{
    return new_clock_time(hour, 0, 0, 0);
}

struct ClockTime
ClockTime_from_hour_minute(int_hour hour, int_minute minute)
{
    return new_clock_time(hour, minute, 0, 0);
}

struct ClockTime
ClockTime_from_hour_minute_second(
        int_hour hour,
        int_minute minute,
        int_second second)
{
    return new_clock_time(hour, minute, second, 0);
}

struct ClockTime
ClockTime_from_hour_minute_second_nanosecond(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond)
{
    return new_clock_time(hour, minute, second, nanosecond);
}

struct ClockTime
ClockTime_create_with_decimal_seconds(
        int_hour hour,
        int_minute minute,
        double second)
{
    int_second second_int;

    second_int = (int_second) second;
    second = (second - second_int) * (double) NANOSECONDS_IN_SECOND;
    return new_clock_time(hour, minute, second_int,
            (int_nanosecond) present_round(second));
}

struct ClockTime
ClockTime_midnight()
{
    return new_clock_time(0, 0, 0, 0);
}

struct ClockTime
ClockTime_noon()
{
    return new_clock_time(12, 0, 0, 0);
}

int_hour
ClockTime_hour(const struct ClockTime * const self)
{
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.seconds / SECONDS_IN_HOUR;
}

int_minute
ClockTime_minute(const struct ClockTime * const self)
{
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.seconds % SECONDS_IN_HOUR / SECONDS_IN_MINUTE;
}

int_second
ClockTime_second(const struct ClockTime * const self)
{
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.seconds % SECONDS_IN_MINUTE;
}

int_nanosecond
ClockTime_nanosecond(const struct ClockTime * const self)
{
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.nanoseconds;
}

double
ClockTime_second_decimal(const struct ClockTime * const self)
{
    assert(self != NULL);
    assert(self->error == 0);

    return (self->data_.seconds % SECONDS_IN_MINUTE) +
           ((double)self->data_.nanoseconds / (double)NANOSECONDS_IN_SECOND);
}

struct TimeDelta
ClockTime_time_since_midnight(const struct ClockTime * const self)
{
    struct TimeDelta delta, ns_delta;

    assert(self != NULL);
    assert(self->error == 0);

    delta = TimeDelta_from_seconds(self->data_.seconds);
    ns_delta = TimeDelta_from_nanoseconds(self->data_.nanoseconds);
    TimeDelta_add(&delta, &ns_delta);
    return delta;
}

void
ClockTime_add_TimeDelta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta)
{
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.seconds += delta->data_.delta_seconds;
    self->data_.nanoseconds += delta->data_.delta_nanoseconds;

    check_clock_time(self);
}

void
ClockTime_subtract_TimeDelta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta)
{
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.seconds -= delta->data_.delta_seconds;
    self->data_.nanoseconds -= delta->data_.delta_nanoseconds;

    check_clock_time(self);
}

int
ClockTime_compare(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs)
{
    assert(lhs != NULL);
    assert(lhs->error == 0);
    assert(rhs != NULL);
    assert(rhs->error == 0);

    return
        STRUCT_COMPARE(seconds,
            STRUCT_COMPARE(nanoseconds, 0));
}

STRUCT_COMPARISON_OPERATORS(ClockTime)

