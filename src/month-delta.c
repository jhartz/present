/*
 * Present - Date/Time Library
 *
 * Implementation of the MonthDelta methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-month-delta-data.h"

#include "present/month-delta.h"

struct MonthDelta
MonthDelta_from_months(int_month_delta month_delta) {

}

struct MonthDelta
MonthDelta_from_years(int_year_delta year_delta) {

}

struct MonthDelta
MonthDelta_zero() {

}

int_month_delta
MonthDelta_get_months(const struct MonthDelta * const self) {

}

int_year_delta
MonthDelta_get_years(const struct MonthDelta * const self) {

}

double
MonthDelta_get_years_decimal(const struct MonthDelta * const self) {

}

void
MonthDelta_multiply_by(struct MonthDelta * const self, int scaleFactor) {

}

void
MonthDelta_divide_by(struct MonthDelta * const self, int scaleFactor) {

}

void
MonthDelta_add_month_delta(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToAdd) {

}

void
MonthDelta_subtract_month_delta(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToSubtract) {

}

bool
MonthDelta_equal(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs) {

}

bool
MonthDelta_less_than(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs) {

}

bool
MonthDelta_less_than_or_equal(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs) {

}

bool
MonthDelta_greater_than(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs) {

}

bool
MonthDelta_greater_than_or_equal(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs) {

}

