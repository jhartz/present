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

#include "present/clock-time.h"
#include "present/day-delta.h"
#include "present/month-delta.h"
#include "present/time-delta.h"
#include "present/timestamp.h"

#include "present/date.h"

/**
 * Make sure that year, month, and day are valid, and set day_of_year and
 * day_of_week to their correct values.
 */
static void check_date_data(struct PresentDateData * const data) {
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
new_date(int_year year, int_month month, int_day day) {
    CONSTRUCTOR_HEAD(Date);

    if (month >= 1 && month <= 12) {
        CONSTRUCTOR_ERROR_RETURN(Date, MONTH_OUT_OF_RANGE);
    }
    if (day >= 1 && day <= 31) {
        CONSTRUCTOR_ERROR_RETURN(Date, DAY_OUT_OF_RANGE);
    }

    struct PresentDateData data;
    data.year = year;
    data.month = month;
    data.day = day;
    check_date_data(&data);
    CONSTRUCTOR_RETURN(Date, data);
}

struct Date
Date_create_from_year(int_year year) {
    return new_date(year, 1, 1);
}

struct Date
Date_create_from_year_month(int_year year, int_month month) {
    return new_date(year, month, 1);
}

struct Date
Date_create_from_year_month_day(int_year year, int_month month, int_day day) {
    return new_date(year, month, day);
}

struct Date
Date_create_from_year_day(int_year year, int_day_of_year day_of_year) {
    return new_date(year, 0, (int_day)(day_of_year));
}

struct Date
Date_create_from_year_week(int_year year, int_week_of_year week_of_year) {
    // TODO
}

struct Date
Date_create_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week) {
    // TODO
}

int_year
Date_get_year(const struct Date * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.year;
}

int_month
Date_get_month(const struct Date * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.month;
}

int_day
Date_get_day(const struct Date * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.day;
}

int_day_of_year
Date_get_day_of_year(const struct Date * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.day_of_year;
}

int_week_of_year
Date_get_week_of_year(const struct Date * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    // TODO
}

int_day_of_week
Date_get_day_of_week(const struct Date * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return self->data_.day_of_week;
}

struct DayDelta
Date_get_difference(
        const struct Date * const self,
        const struct Date * const other) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(other != NULL);
    assert(other->error == 0);

    struct ClockTime noon = ClockTime_noon();
    struct Timestamp selfTimestamp = Timestamp_create_utc(self, &noon);
    struct Timestamp otherTimestamp = Timestamp_create_utc(other, &noon);
    struct TimeDelta timeDelta = Timestamp_get_difference(
            &selfTimestamp, &otherTimestamp);
    return TimeDelta_get_day_delta_truncated(&timeDelta);
}

struct DayDelta
Date_get_absolute_difference(
        const struct Date * const self,
        const struct Date * const other) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(other != NULL);
    assert(other->error == 0);

    struct DayDelta delta = Date_get_difference(self, other);
    if (DayDelta_is_negative(&delta)) {
        DayDelta_negate(&delta);
    }
    return delta;
}

void
Date_add_day_delta(
        struct Date * const self,
        const struct DayDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.day += delta->data_.delta_days;
    check_date_data(&self->data_);
}

void
Date_add_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.month += delta->data_.delta_months;
    check_date_data(&self->data_);
}

void
Date_subtract_day_delta(
        struct Date * const self,
        const struct DayDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.day -= delta->data_.delta_days;
    check_date_data(&self->data_);
}

void
Date_subtract_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.month -= delta->data_.delta_months;
    check_date_data(&self->data_);
}

STRUCT_COMPARISON_OPERATORS(Date, year, month, day)

