/*
 * Present - Date/Time Library
 *
 * Implementation of the TimeDelta methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>
#include <stddef.h>

#include "present.h"

#include "utils/constants.h"
#include "utils/impl-utils.h"
#include "utils/time-utils.h"

/**
 * This macro alters delta_nanoseconds if necessary to ensure that its
 * absolute value is less than NANOSECONDS_IN_SECOND, then ensures that
 * the signs of delta_seconds and delta_nanoseconds match (if either is
 * nonzero).
 */
#define CHECK_DATA(data)    \
    do {                                                                    \
        if (data.delta_nanoseconds > NANOSECONDS_IN_SECOND) {               \
            data.delta_seconds +=                                           \
                data.delta_nanoseconds / NANOSECONDS_IN_SECOND;             \
            data.delta_nanoseconds %= NANOSECONDS_IN_SECOND;                \
        } else if (data.delta_nanoseconds < -NANOSECONDS_IN_SECOND) {       \
            data.delta_seconds -=                                           \
                (-data.delta_nanoseconds) / NANOSECONDS_IN_SECOND;          \
            data.delta_nanoseconds = -(                                     \
                (-data.delta_nanoseconds) % NANOSECONDS_IN_SECOND);         \
        }                                                                   \
        if (data.delta_seconds > 0 && data.delta_nanoseconds < 0) {         \
            data.delta_seconds -= 1;                                        \
            data.delta_nanoseconds += NANOSECONDS_IN_SECOND;                \
        }                                                                   \
        if (data.delta_seconds < 0 && data.delta_nanoseconds > 0) {         \
            data.delta_seconds += 1;                                        \
            data.delta_nanoseconds -= NANOSECONDS_IN_SECOND;                \
        }                                                                   \
        if (data.delta_seconds > 0) assert(data.delta_nanoseconds >= 0);    \
        if (data.delta_seconds < 0) assert(data.delta_nanoseconds <= 0);    \
    } while (0)

/** Initialize a new TimeDelta based on seconds and nanoseconds. */
static void
init_time_delta(
        struct TimeDelta * const result,
        int_delta seconds,
        int_delta nanoseconds)
{
    assert(result != NULL);
    CLEAR(result);

    result->data_.delta_seconds = seconds;
    result->data_.delta_nanoseconds = nanoseconds;
    if (nanoseconds) {
        CHECK_DATA(result->data_);
    }
}


struct TimeDelta
TimeDelta_from_nanoseconds(int_delta nanoseconds)
{
    struct TimeDelta result;
    init_time_delta(&result, 0, nanoseconds);
    return result;
}

void
TimeDelta_ptr_from_nanoseconds(
        struct TimeDelta * const result,
        int_delta nanoseconds)
{
    init_time_delta(result, 0, nanoseconds);
}

struct TimeDelta
TimeDelta_from_microseconds(int_delta microseconds)
{
    struct TimeDelta result;
    init_time_delta(&result, 0, microseconds * NANOSECONDS_IN_MICROSECOND);
    return result;
}

void
TimeDelta_ptr_from_microseconds(
        struct TimeDelta * const result,
        int_delta microseconds)
{
    init_time_delta(result, 0, microseconds * NANOSECONDS_IN_MICROSECOND);
}

struct TimeDelta
TimeDelta_from_milliseconds(int_delta milliseconds)
{
    struct TimeDelta result;
    init_time_delta(&result, 0, milliseconds * NANOSECONDS_IN_MILLISECOND);
    return result;
}

void
TimeDelta_ptr_from_milliseconds(
        struct TimeDelta * const result,
        int_delta milliseconds)
{
    init_time_delta(result, 0, milliseconds * NANOSECONDS_IN_MILLISECOND);
}

struct TimeDelta
TimeDelta_from_seconds(int_delta seconds)
{
    struct TimeDelta result;
    init_time_delta(&result, seconds, 0);
    return result;
}

void
TimeDelta_ptr_from_seconds(struct TimeDelta * const result, int_delta seconds)
{
    init_time_delta(result, seconds, 0);
}

struct TimeDelta
TimeDelta_from_minutes(int_delta minutes)
{
    struct TimeDelta result;
    init_time_delta(&result, minutes * SECONDS_IN_MINUTE, 0);
    return result;
}

void
TimeDelta_ptr_from_minutes(struct TimeDelta * const result, int_delta minutes)
{
    init_time_delta(result, minutes * SECONDS_IN_MINUTE, 0);
}

struct TimeDelta
TimeDelta_from_hours(int_delta hours)
{
    struct TimeDelta result;
    init_time_delta(&result, hours * SECONDS_IN_HOUR, 0);
    return result;
}

void
TimeDelta_ptr_from_hours(struct TimeDelta * const result, int_delta hours)
{
    init_time_delta(result, hours * SECONDS_IN_HOUR, 0);
}

struct TimeDelta
TimeDelta_from_days(int_delta days)
{
    struct TimeDelta result;
    init_time_delta(&result, days * SECONDS_IN_DAY, 0);
    return result;
}

void
TimeDelta_ptr_from_days(struct TimeDelta * const result, int_delta days)
{
    init_time_delta(result, days * SECONDS_IN_DAY, 0);
}

struct TimeDelta
TimeDelta_from_weeks(int_delta weeks)
{
    struct TimeDelta result;
    init_time_delta(&result, weeks * SECONDS_IN_WEEK, 0);
    return result;
}

void
TimeDelta_ptr_from_weeks(struct TimeDelta * const result, int_delta weeks)
{
    init_time_delta(result, weeks * SECONDS_IN_WEEK, 0);
}

struct TimeDelta
TimeDelta_zero(void)
{
    struct TimeDelta result;
    init_time_delta(&result, 0, 0);
    return result;
}

void
TimeDelta_ptr_zero(struct TimeDelta * const result)
{
    init_time_delta(result, 0, 0);
}

int_delta
TimeDelta_nanoseconds(const struct TimeDelta * const self)
{
    assert(self != NULL);

    return (self->data_.delta_seconds * NANOSECONDS_IN_SECOND +
            self->data_.delta_nanoseconds);
}

int_delta
TimeDelta_microseconds(const struct TimeDelta * const self)
{
    assert(self != NULL);

    return (self->data_.delta_seconds * MICROSECONDS_IN_SECOND +
            self->data_.delta_nanoseconds / NANOSECONDS_IN_MICROSECOND);
}

double
TimeDelta_microseconds_decimal(const struct TimeDelta * const self)
{
    assert(self != NULL);

    return (self->data_.delta_seconds * MICROSECONDS_IN_SECOND +
            (double)(self->data_.delta_nanoseconds) /
            (double)NANOSECONDS_IN_MICROSECOND);
}

int_delta
TimeDelta_milliseconds(const struct TimeDelta * const self)
{
    assert(self != NULL);

    return (self->data_.delta_seconds * MILLISECONDS_IN_SECOND +
            self->data_.delta_nanoseconds / NANOSECONDS_IN_MILLISECOND);
}

double
TimeDelta_milliseconds_decimal(const struct TimeDelta * const self)
{
    assert(self != NULL);

    return (self->data_.delta_seconds * MILLISECONDS_IN_SECOND +
            (double)(self->data_.delta_nanoseconds) /
            (double)NANOSECONDS_IN_MILLISECOND);
}

int_delta
TimeDelta_seconds(const struct TimeDelta * const self)
{
    assert(self != NULL);

    return self->data_.delta_seconds;
}

double
TimeDelta_seconds_decimal(const struct TimeDelta * const self)
{
    assert(self != NULL);

    return (self->data_.delta_seconds +
            (double)(self->data_.delta_nanoseconds) /
            (double)NANOSECONDS_IN_SECOND);
}

int_delta
TimeDelta_minutes(const struct TimeDelta * const self)
{
    return TimeDelta_seconds(self) / SECONDS_IN_MINUTE;
}

double
TimeDelta_minutes_decimal(const struct TimeDelta * const self)
{
    return TimeDelta_seconds_decimal(self) / (double)SECONDS_IN_MINUTE;
}

int_delta
TimeDelta_hours(const struct TimeDelta * const self)
{
    return TimeDelta_seconds(self) / SECONDS_IN_HOUR;
}

double
TimeDelta_hours_decimal(const struct TimeDelta * const self)
{
    return TimeDelta_seconds_decimal(self) / (double)SECONDS_IN_HOUR;
}

int_delta
TimeDelta_days(const struct TimeDelta * const self)
{
    return TimeDelta_seconds(self) / SECONDS_IN_DAY;
}

double
TimeDelta_days_decimal(const struct TimeDelta * const self)
{
    return TimeDelta_seconds_decimal(self) / (double)SECONDS_IN_DAY;
}

int_delta
TimeDelta_weeks(const struct TimeDelta * const self)
{
    return TimeDelta_seconds(self) / SECONDS_IN_WEEK;
}

double
TimeDelta_weeks_decimal(const struct TimeDelta * const self)
{
    return TimeDelta_seconds_decimal(self) / (double)SECONDS_IN_WEEK;
}

struct DayDelta
TimeDelta_to_DayDelta_truncated(const struct TimeDelta * const self)
{
    struct DayDelta day_delta;

    assert(self != NULL);

    if (self->data_.delta_seconds >= 0) {
        return DayDelta_from_days(self->data_.delta_seconds / SECONDS_IN_DAY);
    } else {
        /* Truncation in integer division with negative operands is
           implementation-dependent before C99, so we'll just use positives */
        day_delta = DayDelta_from_days(
                (-self->data_.delta_seconds) / SECONDS_IN_DAY);
        DayDelta_negate(&day_delta);
        return day_delta;
    }
}

struct DayDelta
TimeDelta_to_DayDelta_rounded(const struct TimeDelta * const self)
{
    assert(self != NULL);

    return DayDelta_from_days((int_delta)present_round(
                ((double)self->data_.delta_seconds) /
                (double)SECONDS_IN_DAY));
}

struct DayDelta
TimeDelta_to_DayDelta_abs_ceil(const struct TimeDelta * const self)
{
    struct DayDelta day_delta;

    assert(self != NULL);

    if (self->data_.delta_seconds % SECONDS_IN_DAY == 0) {
        return DayDelta_from_days(self->data_.delta_seconds / SECONDS_IN_DAY);
    } else if (self->data_.delta_seconds >= 0) {
        return DayDelta_from_days(self->data_.delta_seconds / SECONDS_IN_DAY +
                1);
    } else {
        /* Truncation in integer division with negative operands is
           implementation-dependent before C99, so we'll just use positives */
        day_delta = DayDelta_from_days(
                (-self->data_.delta_seconds) / SECONDS_IN_DAY + 1);
        DayDelta_negate(&day_delta);
        return day_delta;
    }
}

present_bool
TimeDelta_is_negative(const struct TimeDelta * const self)
{
    assert(self != NULL);

    return self->data_.delta_seconds < 0 || self->data_.delta_nanoseconds < 0;
}

void
TimeDelta_negate(struct TimeDelta * const self)
{
    assert(self != NULL);

    self->data_.delta_seconds = -self->data_.delta_seconds;
    self->data_.delta_nanoseconds = -self->data_.delta_nanoseconds;
}

void
TimeDelta_multiply_by(struct TimeDelta * const self, const int scale_factor)
{
    assert(self != NULL);

    self->data_.delta_seconds *= scale_factor;
    self->data_.delta_nanoseconds *= scale_factor;

    CHECK_DATA(self->data_);
}

void
TimeDelta_multiply_by_decimal(
        struct TimeDelta * const self,
        const double scale_factor)
{
    double seconds;

    assert(self != NULL);

    seconds = (double)self->data_.delta_seconds * scale_factor;
    self->data_.delta_seconds = (int_delta)seconds;
    self->data_.delta_nanoseconds *= scale_factor;

    /* When scaling the seconds, we may have a fractional part that needs to
       be stored in the nanoseconds */
    self->data_.delta_nanoseconds +=
        (seconds - (double)self->data_.delta_seconds) *
        (double)NANOSECONDS_IN_SECOND;

    CHECK_DATA(self->data_);
}

void
TimeDelta_divide_by(struct TimeDelta * const self, const int scale_factor)
{
    int_delta orig_seconds;

    assert(self != NULL);
    assert(scale_factor != 0);

    /* Start by scaling just the seconds portion */
    orig_seconds = self->data_.delta_seconds;
    self->data_.delta_seconds /= scale_factor;

    /* When scaling down, there may be fractional seconds that could be
       represented as nanoseconds. Add this to the nanoseconds (which we
       haven't scaled yet) */
    self->data_.delta_nanoseconds += (orig_seconds % scale_factor) *
        NANOSECONDS_IN_SECOND;

    /* Now we can scale the nanoseconds */
    self->data_.delta_nanoseconds /= scale_factor;

    CHECK_DATA(self->data_);
}

void
TimeDelta_divide_by_decimal(
        struct TimeDelta * const self,
        const double scale_factor)
{
    assert(self != NULL);
    assert(scale_factor != 0.0);

    /* Simplify our lives by reusing the float multiplication implementation */
    TimeDelta_multiply_by_decimal(self, 1.0/scale_factor);
}

void
TimeDelta_add(
        struct TimeDelta * const self,
        const struct TimeDelta * const other)
{
    assert(self != NULL);
    assert(other != NULL);

    self->data_.delta_seconds += other->data_.delta_seconds;
    self->data_.delta_nanoseconds += other->data_.delta_nanoseconds;

    CHECK_DATA(self->data_);
}

void
TimeDelta_add_DayDelta(
        struct TimeDelta * const self,
        const struct DayDelta * const other)
{
    assert(self != NULL);
    assert(other != NULL);

    self->data_.delta_seconds += other->data_.delta_days * SECONDS_IN_DAY;

    CHECK_DATA(self->data_);
}

void
TimeDelta_subtract(
        struct TimeDelta * const self,
        const struct TimeDelta * const other)
{
    assert(self != NULL);
    assert(other != NULL);

    self->data_.delta_seconds -= other->data_.delta_seconds;
    self->data_.delta_nanoseconds -= other->data_.delta_nanoseconds;

    CHECK_DATA(self->data_);
}

void
TimeDelta_subtract_DayDelta(
        struct TimeDelta * const self,
        const struct DayDelta * const other)
{
    assert(self != NULL);
    assert(other != NULL);

    self->data_.delta_seconds -= other->data_.delta_days * SECONDS_IN_DAY;

    CHECK_DATA(self->data_);
}

int
TimeDelta_compare(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs)
{
    assert(lhs != NULL);
    assert(rhs != NULL);

    return
        STRUCT_COMPARE(delta_seconds,
            STRUCT_COMPARE(delta_nanoseconds, 0));
}

STRUCT_COMPARISON_OPERATORS(TimeDelta)

