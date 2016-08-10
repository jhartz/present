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
#include <string.h>

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-date-data.h"

#include "impl-constants.h"
#include "impl-utils.h"

#include "present/day-delta.h"
#include "present/month-delta.h"

#include "present/date.h"

/**
 * Make sure that year, month, and day are valid, and set day_of_year and
 * day_of_week to their correct values.
 */
static void checkDateData(struct PresentDateData * const data) {
    struct tm info;
    memset((void *)&info, 0, sizeof(struct tm));

    info.tm_year = (int)data->year - STRUCT_TM_YEAR_OFFSET;
    info.tm_mon = (int)data->month - STRUCT_TM_MONTH_OFFSET;
    info.tm_mday = (int)data->day;
    info.tm_isdst = -1;
    assert(mktime(&info) != -1);

    data->year = (int_year)info.tm_year + STRUCT_TM_YEAR_OFFSET;
    data->month = (int_month)info.tm_mon + STRUCT_TM_MONTH_OFFSET;
    data->day = (int_day)info.tm_mday;
    data->day_of_year = (int_day_of_year)info.tm_yday;
    data->day_of_week = (int_day_of_week)info.tm_wday;
    if (data->day_of_week == DAY_OF_WEEK_SUNDAY_COMPAT) {
        data->day_of_week = DAY_OF_WEEK_SUNDAY;
    }
}

/**
 * Create a new Date instance based on its data parameters.
 */
static struct Date
newDate(int_year year, int_month month, int_day day) {
    assert(month >= 1 && month <= 12);
    assert(day >= 1 && day <= 31);

    struct PresentDateData data;
    data.year = year;
    data.month = month;
    data.day = day;
    checkDateData(&data);
    WRAP_DATA_AND_RETURN(Date, data);
}

/**
 * Determine whether a given year is a leap year.
 */
#define IS_LEAP_YEAR(year)                      \
    ((year % 4 == 0 && year % 100 != 0) ||      \
     (year % 400 == 0))

/**
 * Day of the year that each month starts on
 * (dependent on whether it's a leap year)
 */
static const int_day_of_year DAY_OF_START_OF_MONTH[2][13] = {
    {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
    {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
};

struct Date
Date_create_from_year(int_year year) {
    return newDate(year, 1, 1);
}

struct Date
Date_create_from_year_month(int_year year, int_month month) {
    return newDate(year, month, 1);
}

struct Date
Date_create_from_year_month_day(int_year year, int_month month, int_day day) {
    return newDate(year, month, day);
}

struct Date
Date_create_from_year_day(int_year year, int_day_of_year day_of_year) {
    assert(day_of_year > 0);
    assert(IS_LEAP_YEAR(year) ? (day_of_year <= 366) : (day_of_year <= 365));

    return newDate(year, 0, (int_day)(day_of_year));
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
    assert(self != NULL);
    return self->data_.year;
}

int_month
Date_get_month(const struct Date * const self) {
    assert(self != NULL);
    return self->data_.month;
}

int_day
Date_get_day(const struct Date * const self) {
    assert(self != NULL);
    return self->data_.day;
}

int_day_of_year
Date_get_day_of_year(const struct Date * const self) {
    assert(self != NULL);
    return self->data_.day_of_year;
}

int_week_of_year
Date_get_week_of_year(const struct Date * const self) {

}

int_day_of_week
Date_get_day_of_week(const struct Date * const self) {
    assert(self != NULL);
    return self->data_.day_of_week;
}

void
Date_add_day_delta(
        struct Date * const self,
        const struct DayDelta * const delta) {
    assert(self != NULL);
    assert(delta != NULL);
    self->data_.day += delta->data_.delta_days;
    checkDateData(&self->data_);
}

void
Date_add_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta) {
    assert(self != NULL);
    assert(delta != NULL);
    self->data_.month += delta->data_.delta_months;
    checkDateData(&self->data_);
}

void
Date_subtract_day_delta(
        struct Date * const self,
        const struct DayDelta * const delta) {
    assert(self != NULL);
    assert(delta != NULL);
    self->data_.day -= delta->data_.delta_days;
    checkDateData(&self->data_);
}

void
Date_subtract_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta) {
    assert(self != NULL);
    assert(delta != NULL);
    self->data_.month -= delta->data_.delta_months;
    checkDateData(&self->data_);
}

bool
Date_equal(const struct Date * const lhs, const struct Date * const rhs) {
    assert(lhs != NULL);
    assert(rhs != NULL);
    return (lhs->data_.year == rhs->data_.year &&
            lhs->data_.month == rhs->data_.month &&
            lhs->data_.day == rhs->data_.day);
}

STRUCT_INEQUALITY_OPERATORS(Date, year, month, day)

