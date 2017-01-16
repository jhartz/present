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

/** Initialize a new MonthDelta based on the number of months. */
static void
init_month_delta(struct MonthDelta * const result, int_month_delta months)
{
    assert(result != NULL);
    CLEAR(result);

    result->data_.delta_months = months;
}


struct MonthDelta
MonthDelta_from_months(int_month_delta months)
{
    struct MonthDelta result;
    init_month_delta(&result, months);
    return result;
}

void
MonthDelta_ptr_from_months(
        struct MonthDelta * const result,
        int_month_delta months)
{
    init_month_delta(result, months);
}

struct MonthDelta
MonthDelta_from_years(int_year_delta years)
{
    struct MonthDelta result;
    init_month_delta(&result, years * MONTHS_IN_YEAR);
    return result;
}

void
MonthDelta_ptr_from_years(
        struct MonthDelta * const result,
        int_year_delta years)
{
    init_month_delta(result, years * MONTHS_IN_YEAR);
}

struct MonthDelta
MonthDelta_zero()
{
    struct MonthDelta result;
    init_month_delta(&result, 0);
    return result;
}

void
MonthDelta_ptr_zero(struct MonthDelta * const result)
{
    init_month_delta(result, 0);
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

