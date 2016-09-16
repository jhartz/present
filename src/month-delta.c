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

#include "present/utils/types.h"
#include "present/impl/present-month-delta-data.h"

#include "present-constants.h"
#include "present-syscalls.h"
#include "present-utils.h"

#include "present/month-delta.h"

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
    assert(self->error == 0);

    return self->data_.delta_months;
}

int_year_delta
MonthDelta_years(const struct MonthDelta * const self)
{
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.delta_months / MONTHS_IN_YEAR;
}

double
MonthDelta_years_decimal(const struct MonthDelta * const self)
{
    assert(self != NULL);
    assert(self->error == 0);

    return ((double)self->data_.delta_months) / (double)MONTHS_IN_YEAR;
}

present_bool
MonthDelta_is_negative(const struct MonthDelta * const self)
{
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.delta_months < 0;
}

void
MonthDelta_negate(struct MonthDelta * const self)
{
    assert(self != NULL);
    assert(self->error == 0);

    self->data_.delta_months = -self->data_.delta_months;
}

void
MonthDelta_multiply_by(struct MonthDelta * const self, int scaleFactor)
{
    assert(self != NULL);
    assert(self->error == 0);

    self->data_.delta_months *= scaleFactor;
}

void
MonthDelta_divide_by(struct MonthDelta * const self, int scaleFactor)
{
    assert(self != NULL);
    assert(self->error == 0);

    self->data_.delta_months /= scaleFactor;
}

void
MonthDelta_add(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToAdd)
{
    assert(self != NULL);
    assert(self->error == 0);
    assert(monthDeltaToAdd != NULL);
    assert(monthDeltaToAdd->error == 0);

    self->data_.delta_months += monthDeltaToAdd->data_.delta_months;
}

void
MonthDelta_subtract(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToSubtract)
{
    assert(self != NULL);
    assert(self->error == 0);
    assert(monthDeltaToSubtract != NULL);
    assert(monthDeltaToSubtract->error == 0);

    self->data_.delta_months -= monthDeltaToSubtract->data_.delta_months;
}

int
MonthDelta_compare(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs)
{
    assert(lhs != NULL);
    assert(lhs->error == 0);
    assert(rhs != NULL);
    assert(rhs->error == 0);

    return STRUCT_COMPARE(delta_months, 0);
}

STRUCT_COMPARISON_OPERATORS(MonthDelta)

