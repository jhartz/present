/*
 * Present - Date/Time Library
 *
 * Implementation of the Date methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>
#include <stddef.h>

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-date-data.h"

#include "impl-constants.h"
#include "impl-utils.h"

#include "present/date.h"

struct Date
Date_create_from_year(int_year year) {

}

struct Date
Date_create_from_year_month(int_year year, int_month month) {

}

struct Date
Date_create_from_year_month_day(int_year year, int_month month, int_day day) {

}

struct Date
Date_create_from_year_week(int_year year, int_week_of_year week_of_year) {

}

struct Date
Date_create_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week) {

}

int_year
Date_get_year(const struct Date * const self) {

}

int_month
Date_get_month(const struct Date * const self) {

}

int_day
Date_get_day(const struct Date * const self) {

}

int_day_of_year
Date_get_day_of_year(const struct Date * const self) {

}

int_week_of_year
Date_get_week_of_year(const struct Date * const self) {

}

int_day_of_week
Date_get_day_of_week(const struct Date * const self) {

}

void
Date_add_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta) {

}

void
Date_subtract_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta) {

}

bool
Date_equal(const struct Date * const lhs, const struct Date * const rhs) {

}

STRUCT_INEQUALITY_OPERATORS(Date, year, month, day)

