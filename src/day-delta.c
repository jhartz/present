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

#include "present.h"

#include "utils/constants.h"
#include "utils/impl-utils.h"
#include "utils/time-utils.h"

/** Initialize a new DayDelta based on the number of days. */
static void
init_day_delta(struct DayDelta * const result, int_delta days)
{
    assert(result != NULL);
    CLEAR(result);
    result->data_.delta_days = days;
}


struct DayDelta
DayDelta_from_days(int_delta days)
{
    struct DayDelta result;
    init_day_delta(&result, days);
    return result;
}

void
DayDelta_ptr_from_days(struct DayDelta * const result, int_delta days)
{
    init_day_delta(result, days);
}

struct DayDelta
DayDelta_from_weeks(int_delta weeks)
{
    struct DayDelta result;
    init_day_delta(&result, weeks * DAYS_IN_WEEK);
    return result;
}

void
DayDelta_ptr_from_weeks(struct DayDelta * const result, int_delta weeks)
{
    init_day_delta(result, weeks * DAYS_IN_WEEK);
}

struct DayDelta
DayDelta_zero(void)
{
    struct DayDelta result;
    init_day_delta(&result, 0);
    return result;
}

void
DayDelta_ptr_zero(struct DayDelta * const result)
{
    init_day_delta(result, 0);
}

int_delta
DayDelta_days(const struct DayDelta * const self)
{
    assert(self != NULL);

    return self->data_.delta_days;
}

int_delta
DayDelta_weeks(const struct DayDelta * const self)
{
    assert(self != NULL);

    return self->data_.delta_days / DAYS_IN_WEEK;
}

double
DayDelta_weeks_decimal(const struct DayDelta * const self)
{
    assert(self != NULL);

    return ((double)self->data_.delta_days) / (double)DAYS_IN_WEEK;
}

struct TimeDelta
DayDelta_to_TimeDelta(const struct DayDelta * const self)
{
    assert(self != NULL);

    return TimeDelta_from_days(self->data_.delta_days);
}

present_bool
DayDelta_is_negative(const struct DayDelta * const self)
{
    assert(self != NULL);

    return self->data_.delta_days < 0;
}

void
DayDelta_negate(struct DayDelta * const self)
{
    assert(self != NULL);

    self->data_.delta_days = -self->data_.delta_days;
}

void
DayDelta_multiply_by(struct DayDelta * const self, long scale_factor)
{
    assert(self != NULL);

    self->data_.delta_days *= scale_factor;
}

void
DayDelta_divide_by(struct DayDelta * const self, long scale_factor)
{
    assert(self != NULL);

    self->data_.delta_days /= scale_factor;
}

void
DayDelta_add(
        struct DayDelta * const self,
        const struct DayDelta * const other)
{
    assert(self != NULL);
    assert(other != NULL);

    self->data_.delta_days += other->data_.delta_days;
}

void
DayDelta_subtract(
        struct DayDelta * const self,
        const struct DayDelta * const other)
{
    assert(self != NULL);
    assert(other != NULL);

    self->data_.delta_days -= other->data_.delta_days;
}

short
DayDelta_compare(
        const struct DayDelta * const lhs,
        const struct DayDelta * const rhs)
{
    assert(lhs != NULL);
    assert(rhs != NULL);

    return STRUCT_COMPARE(delta_days, 0);
}

short
DayDelta_compare_to_TimeDelta(
        const struct DayDelta * const lhs,
        const struct TimeDelta * const rhs)
{
    return -TimeDelta_compare_to_DayDelta(rhs, lhs);
}

STRUCT_COMPARISON_OPERATORS(DayDelta)

STRUCT_COMPARISON_OPERATORS_WITH_OTHER_STRUCT(DayDelta, TimeDelta)

