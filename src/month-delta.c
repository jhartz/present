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
#include "present/utils/utils.h"
#include "present/impl/present-month-delta-data.h"

#include "impl-constants.h"
#include "impl-utils.h"

#include "present/month-delta.h"

struct MonthDelta
MonthDelta_from_months(int_month_delta month_delta) {
    CONSTRUCTOR_HEAD(MonthDelta);

    struct PresentMonthDeltaData data;
    data.delta_months = month_delta;
    CONSTRUCTOR_RETURN(MonthDelta, data);
}

struct MonthDelta
MonthDelta_from_years(int_year_delta year_delta) {
    CONSTRUCTOR_HEAD(MonthDelta);

    struct PresentMonthDeltaData data;
    data.delta_months = year_delta * MONTHS_IN_YEAR;
    CONSTRUCTOR_RETURN(MonthDelta, data);
}

struct MonthDelta
MonthDelta_zero() {
    CONSTRUCTOR_HEAD(MonthDelta);

    struct PresentMonthDeltaData data;
    data.delta_months = 0;
    CONSTRUCTOR_RETURN(MonthDelta, data);
}

int_month_delta
MonthDelta_get_months(const struct MonthDelta * const self) {
    assert(self != NULL);
    return self->data_.delta_months;
}

int_year_delta
MonthDelta_get_years(const struct MonthDelta * const self) {
    assert(self != NULL);
    return self->data_.delta_months / MONTHS_IN_YEAR;
}

double
MonthDelta_get_years_decimal(const struct MonthDelta * const self) {
    assert(self != NULL);
    return ((double)self->data_.delta_months) / (double)MONTHS_IN_YEAR;
}

bool
MonthDelta_is_negative(const struct MonthDelta * const self) {
    assert(self != NULL);
    return self->data_.delta_months < 0;
}

void
MonthDelta_negate(struct MonthDelta * const self) {
    assert(self != NULL);
    self->data_.delta_months = -self->data_.delta_months;
}

void
MonthDelta_multiply_by(struct MonthDelta * const self, int scaleFactor) {
    assert(self != NULL);
    self->data_.delta_months *= scaleFactor;
}

void
MonthDelta_divide_by(struct MonthDelta * const self, int scaleFactor) {
    assert(self != NULL);
    self->data_.delta_months /= scaleFactor;
}

void
MonthDelta_add_month_delta(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToAdd) {
    assert(self != NULL);
    assert(monthDeltaToAdd != NULL);
    self->data_.delta_months += monthDeltaToAdd->data_.delta_months;
}

void
MonthDelta_subtract_month_delta(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToSubtract) {
    assert(self != NULL);
    assert(monthDeltaToSubtract != NULL);
    self->data_.delta_months -= monthDeltaToSubtract->data_.delta_months;
}

bool
MonthDelta_equal(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs) {
    assert(lhs != NULL);
    assert(rhs != NULL);
    return (lhs->data_.delta_months == rhs->data_.delta_months);
}

STRUCT_INEQUALITY_OPERATORS(MonthDelta, delta_months)

