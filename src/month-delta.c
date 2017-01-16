/*
 * Present - Date/Time Library
 *
 * Implementation of the MonthDelta methods
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

struct MonthDelta
MonthDelta_from_months(int_month_delta month_delta)
{
    struct PresentMonthDeltaData data;
    CONSTRUCTOR_HEAD(MonthDelta);

    data.delta_months = month_delta;
    CONSTRUCTOR_RETURN(MonthDelta, data);
}

struct MonthDelta
MonthDelta_from_years(int_year_delta year_delta)
{
    struct PresentMonthDeltaData data;
    CONSTRUCTOR_HEAD(MonthDelta);

    data.delta_months = year_delta * MONTHS_IN_YEAR;
    CONSTRUCTOR_RETURN(MonthDelta, data);
}

struct MonthDelta
MonthDelta_zero()
{
    struct PresentMonthDeltaData data;
    CONSTRUCTOR_HEAD(MonthDelta);

    data.delta_months = 0;
    CONSTRUCTOR_RETURN(MonthDelta, data);
}

int_month_delta
MonthDelta_months(const struct MonthDelta * const self)
{
    assert(self != NULL);

    return self->data_.delta_months;
}

int_year_delta
MonthDelta_years(const struct MonthDelta * const self)
{
    assert(self != NULL);

    return self->data_.delta_months / MONTHS_IN_YEAR;
}

double
MonthDelta_years_decimal(const struct MonthDelta * const self)
{
    assert(self != NULL);

    return ((double)self->data_.delta_months) / (double)MONTHS_IN_YEAR;
}

present_bool
MonthDelta_is_negative(const struct MonthDelta * const self)
{
    assert(self != NULL);

    return self->data_.delta_months < 0;
}

void
MonthDelta_negate(struct MonthDelta * const self)
{
    assert(self != NULL);

    self->data_.delta_months = -self->data_.delta_months;
}

void
MonthDelta_multiply_by(struct MonthDelta * const self, int scaleFactor)
{
    assert(self != NULL);

    self->data_.delta_months *= scaleFactor;
}

void
MonthDelta_divide_by(struct MonthDelta * const self, int scaleFactor)
{
    assert(self != NULL);

    self->data_.delta_months /= scaleFactor;
}

void
MonthDelta_add(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToAdd)
{
    assert(self != NULL);
    assert(monthDeltaToAdd != NULL);

    self->data_.delta_months += monthDeltaToAdd->data_.delta_months;
}

void
MonthDelta_subtract(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToSubtract)
{
    assert(self != NULL);
    assert(monthDeltaToSubtract != NULL);

    self->data_.delta_months -= monthDeltaToSubtract->data_.delta_months;
}

int
MonthDelta_compare(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs)
{
    assert(lhs != NULL);
    assert(rhs != NULL);

    return STRUCT_COMPARE(delta_months, 0);
}

STRUCT_COMPARISON_OPERATORS(MonthDelta)

