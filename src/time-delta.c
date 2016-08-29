/*
 * Present - Date/Time Library
 *
 * Implementation of the TimeDelta methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>
#include <math.h>
#include <stddef.h>

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-time-delta-data.h"

#include "impl-constants.h"
#include "impl-utils.h"

#include "present/day-delta.h"

#include "present/time-delta.h"

/**
 * This macro alters delta_nanoseconds if necessary to ensure that its
 * absolute value is less than NANOSECONDS_IN_SECOND, then ensures that
 * the signs of delta_seconds and delta_nanoseconds match (if either is
 * nonzero).
 */
#define CHECK_DATA(data)    \
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
    if (data.delta_seconds < 0) assert(data.delta_nanoseconds <= 0);

struct TimeDelta
TimeDelta_from_nanoseconds(int_delta nanoseconds) {
    CONSTRUCTOR_HEAD(TimeDelta);

    struct PresentTimeDeltaData data;
    data.delta_seconds = 0;
    data.delta_nanoseconds = nanoseconds;
    CONSTRUCTOR_RETURN(TimeDelta, data);
}

struct TimeDelta
TimeDelta_from_seconds(int_delta seconds) {
    CONSTRUCTOR_HEAD(TimeDelta);

    struct PresentTimeDeltaData data;
    data.delta_seconds = seconds;
    data.delta_nanoseconds = 0;
    CONSTRUCTOR_RETURN(TimeDelta, data);
}

struct TimeDelta
TimeDelta_from_minutes(int_delta minutes) {
    CONSTRUCTOR_HEAD(TimeDelta);

    struct PresentTimeDeltaData data;
    data.delta_seconds = minutes * SECONDS_IN_MINUTE;
    data.delta_nanoseconds = 0;
    CONSTRUCTOR_RETURN(TimeDelta, data);
}

struct TimeDelta
TimeDelta_from_hours(int_delta hours) {
    CONSTRUCTOR_HEAD(TimeDelta);

    struct PresentTimeDeltaData data;
    data.delta_seconds = hours * SECONDS_IN_HOUR;
    data.delta_nanoseconds = 0;
    CONSTRUCTOR_RETURN(TimeDelta, data);
}

struct TimeDelta
TimeDelta_from_days(int_delta days) {
    CONSTRUCTOR_HEAD(TimeDelta);

    struct PresentTimeDeltaData data;
    data.delta_seconds = days * SECONDS_IN_DAY;
    data.delta_nanoseconds = 0;
    CONSTRUCTOR_RETURN(TimeDelta, data);
}

struct TimeDelta
TimeDelta_from_weeks(int_delta weeks) {
    CONSTRUCTOR_HEAD(TimeDelta);

    struct PresentTimeDeltaData data;
    data.delta_seconds = weeks * SECONDS_IN_WEEK;
    data.delta_nanoseconds = 0;
    CONSTRUCTOR_RETURN(TimeDelta, data);
}

struct TimeDelta
TimeDelta_zero() {
    CONSTRUCTOR_HEAD(TimeDelta);

    struct PresentTimeDeltaData data;
    data.delta_seconds = 0;
    data.delta_nanoseconds = 0;
    CONSTRUCTOR_RETURN(TimeDelta, data);
}

int_delta
TimeDelta_get_nanoseconds(const struct TimeDelta * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return (self->data_.delta_seconds * NANOSECONDS_IN_SECOND +
            self->data_.delta_nanoseconds);
}

int_delta
TimeDelta_get_seconds(const struct TimeDelta * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.delta_seconds;
}

double
TimeDelta_get_seconds_decimal(const struct TimeDelta * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return (self->data_.delta_seconds +
            (double)(self->data_.delta_nanoseconds) /
            (double)NANOSECONDS_IN_SECOND);
}

int_delta
TimeDelta_get_minutes(const struct TimeDelta * const self) {
    return TimeDelta_get_seconds(self) / SECONDS_IN_MINUTE;
}

double
TimeDelta_get_minutes_decimal(const struct TimeDelta * const self) {
    return TimeDelta_get_seconds_decimal(self) / (double)SECONDS_IN_MINUTE;
}

int_delta
TimeDelta_get_hours(const struct TimeDelta * const self) {
    return TimeDelta_get_seconds(self) / SECONDS_IN_HOUR;
}

double
TimeDelta_get_hours_decimal(const struct TimeDelta * const self) {
    return TimeDelta_get_seconds_decimal(self) / (double)SECONDS_IN_HOUR;
}

int_delta
TimeDelta_get_days(const struct TimeDelta * const self) {
    return TimeDelta_get_seconds(self) / SECONDS_IN_DAY;
}

double
TimeDelta_get_days_decimal(const struct TimeDelta * const self) {
    return TimeDelta_get_seconds_decimal(self) / (double)SECONDS_IN_DAY;
}

int_delta
TimeDelta_get_weeks(const struct TimeDelta * const self) {
    return TimeDelta_get_seconds(self) / SECONDS_IN_WEEK;
}

double
TimeDelta_get_weeks_decimal(const struct TimeDelta * const self) {
    return TimeDelta_get_seconds_decimal(self) / (double)SECONDS_IN_WEEK;
}

struct DayDelta
TimeDelta_get_day_delta_truncated(const struct TimeDelta * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    if (self->data_.delta_seconds >= 0) {
        return DayDelta_from_days(self->data_.delta_seconds / SECONDS_IN_DAY);
    } else {
        /* Truncation in integer division with negative operands is
           implementation-dependent before C99, so we'll just use positives */
        struct DayDelta dayDelta = DayDelta_from_days(
                (-self->data_.delta_seconds) / SECONDS_IN_DAY);
        DayDelta_negate(&dayDelta);
        return dayDelta;
    }
}

struct DayDelta
TimeDelta_get_day_delta_rounded(const struct TimeDelta * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return DayDelta_from_days((int_delta)round(
                ((double)self->data_.delta_seconds) /
                (double)SECONDS_IN_DAY));
}

struct DayDelta
TimeDelta_get_day_delta_abs_ceil(const struct TimeDelta * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    if (self->data_.delta_seconds % SECONDS_IN_DAY == 0) {
        return DayDelta_from_days(self->data_.delta_seconds / SECONDS_IN_DAY);
    } else if (self->data_.delta_seconds >= 0) {
        return DayDelta_from_days(self->data_.delta_seconds / SECONDS_IN_DAY +
                1);
    } else {
        /* Truncation in integer division with negative operands is
           implementation-dependent before C99, so we'll just use positives */
        struct DayDelta dayDelta = DayDelta_from_days(
                (-self->data_.delta_seconds) / SECONDS_IN_DAY + 1);
        DayDelta_negate(&dayDelta);
        return dayDelta;
    }
}

bool
TimeDelta_is_negative(const struct TimeDelta * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.delta_seconds < 0 || self->data_.delta_nanoseconds < 0;
}

void
TimeDelta_negate(struct TimeDelta * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    self->data_.delta_seconds = -self->data_.delta_seconds;
    self->data_.delta_nanoseconds = -self->data_.delta_nanoseconds;
}

void
TimeDelta_multiply_by(struct TimeDelta * const self, const int scaleFactor) {
    assert(self != NULL);
    assert(self->error == 0);

    self->data_.delta_seconds *= scaleFactor;
    self->data_.delta_nanoseconds *= scaleFactor;

    CHECK_DATA(self->data_)
}

void
TimeDelta_multiply_by_decimal(
        struct TimeDelta * const self,
        const double scaleFactor) {
    assert(self != NULL);
    assert(self->error == 0);

    const double seconds = (double)self->data_.delta_seconds * scaleFactor;
    self->data_.delta_seconds = (int_delta)seconds;
    self->data_.delta_nanoseconds *= scaleFactor;

    /* When scaling the seconds, we may have a fractional part that needs to
       be stored in the nanoseconds */
    self->data_.delta_nanoseconds +=
        (seconds - (double)self->data_.delta_seconds) *
        (double)NANOSECONDS_IN_SECOND;

    CHECK_DATA(self->data_)
}

void
TimeDelta_divide_by(struct TimeDelta * const self, const int scaleFactor) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(scaleFactor != 0);

    /* Start by scaling just the seconds portion */
    const int_delta origSeconds = self->data_.delta_seconds;
    self->data_.delta_seconds /= scaleFactor;

    /* When scaling down, there may be fractional seconds that could be
       represented as nanoseconds. Add this to the nanoseconds (which we
       haven't scaled yet) */
    self->data_.delta_nanoseconds += (origSeconds % scaleFactor) *
        NANOSECONDS_IN_SECOND;

    /* Now we can scale the nanoseconds */
    self->data_.delta_nanoseconds /= scaleFactor;

    CHECK_DATA(self->data_)
}

void
TimeDelta_divide_by_decimal(
        struct TimeDelta * const self,
        const double scaleFactor) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(scaleFactor != 0.0);

    /* Simplify our lives by reusing the float multiplication implementation */
    TimeDelta_multiply_by_decimal(self, 1.0/scaleFactor);
}

void
TimeDelta_add_time_delta(
        struct TimeDelta * const self,
        const struct TimeDelta * const timeDeltaToAdd) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(timeDeltaToAdd != NULL);
    assert(timeDeltaToAdd->error == 0);

    self->data_.delta_seconds += timeDeltaToAdd->data_.delta_seconds;
    self->data_.delta_nanoseconds += timeDeltaToAdd->data_.delta_nanoseconds;

    CHECK_DATA(self->data_)
}

void
TimeDelta_subtract_time_delta(
        struct TimeDelta * const self,
        const struct TimeDelta * const timeDeltaToSubtract) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(timeDeltaToSubtract != NULL);
    assert(timeDeltaToSubtract->error == 0);

    self->data_.delta_seconds -= timeDeltaToSubtract->data_.delta_seconds;
    self->data_.delta_nanoseconds -= timeDeltaToSubtract->data_.delta_nanoseconds;

    CHECK_DATA(self->data_)
}

STRUCT_COMPARISON_OPERATORS(TimeDelta, delta_seconds, delta_nanoseconds)

