/*
 * Present - Date/Time Library
 *
 * Implementation of the DayDelta methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>
#include <stddef.h>

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-day-delta-data.h"

#include "impl-constants.h"
#include "impl-utils.h"

#include "present/time-delta.h"

#include "present/day-delta.h"

struct DayDelta
DayDelta_from_days(int_delta days) {
    CONSTRUCTOR_HEAD(DayDelta);

    struct PresentDayDeltaData data;
    data.delta_days = days;
    CONSTRUCTOR_RETURN(DayDelta, data);
}

struct DayDelta
DayDelta_from_weeks(int_delta weeks) {
    CONSTRUCTOR_HEAD(DayDelta);

    struct PresentDayDeltaData data;
    data.delta_days = weeks * DAYS_IN_WEEK;
    CONSTRUCTOR_RETURN(DayDelta, data);
}

struct DayDelta
DayDelta_zero() {
    CONSTRUCTOR_HEAD(DayDelta);

    struct PresentDayDeltaData data;
    data.delta_days = 0;
    CONSTRUCTOR_RETURN(DayDelta, data);
}

int_delta
DayDelta_get_days(const struct DayDelta * const self) {
    assert(self != NULL);
    return self->data_.delta_days;
}

int_delta
DayDelta_get_weeks(const struct DayDelta * const self) {
    assert(self != NULL);
    return self->data_.delta_days / DAYS_IN_WEEK;
}

double
DayDelta_get_weeks_decimal(const struct DayDelta * const self) {
    assert(self != NULL);
    return ((double)self->data_.delta_days) / (double)DAYS_IN_WEEK;
}

struct TimeDelta
DayDelta_get_time_delta(const struct DayDelta * const self) {
    return TimeDelta_from_days(self->data_.delta_days);
}

bool
DayDelta_is_negative(const struct DayDelta * const self) {
    assert(self != NULL);
    return self->data_.delta_days < 0;
}

void
DayDelta_negate(struct DayDelta * const self) {
    assert(self != NULL);
    self->data_.delta_days = -self->data_.delta_days;
}

void
DayDelta_multiply_by(struct DayDelta * const self, int scaleFactor) {
    assert(self != NULL);
    self->data_.delta_days *= scaleFactor;
}

void
DayDelta_divide_by(struct DayDelta * const self, int scaleFactor) {
    assert(self != NULL);
    self->data_.delta_days /= scaleFactor;
}

void
DayDelta_add_day_delta(
        struct DayDelta * const self,
        const struct DayDelta * const dayDeltaToAdd) {
    assert(self != NULL);
    assert(dayDeltaToAdd != NULL);
    self->data_.delta_days += dayDeltaToAdd->data_.delta_days;
}

void
DayDelta_subtract_day_delta(
        struct DayDelta * const self,
        const struct DayDelta * const dayDeltaToSubtract) {
    assert(self != NULL);
    assert(dayDeltaToSubtract != NULL);
    self->data_.delta_days -= dayDeltaToSubtract->data_.delta_days;
}

bool
DayDelta_equal(
        const struct DayDelta * const lhs,
        const struct DayDelta * const rhs) {
    assert(lhs != NULL);
    assert(rhs != NULL);
    return (lhs->data_.delta_days == rhs->data_.delta_days);
}

STRUCT_INEQUALITY_OPERATORS(DayDelta, delta_days)

