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

#include "present.h"

#include "utils/constants.h"
#include "utils/impl-utils.h"
#include "utils/time-utils.h"

/**
 * Get the week number of the last week of a given year (either 52 or 53).
 */
static int_week_of_year
last_week_of_year(int_year year)
{
    int_week_of_year week;
    time_t time;
    struct tm tm;
    int_day_of_week day_of_week;

    /* https://en.wikipedia.org/wiki/ISO_week_date#Weeks_per_year */
    week = 52;

    /* Get some information on Jan. 1 of this year */
    time = unix_timestamp_to_time_t(to_unix_timestamp(year, 1, 1, 0, 0, 0));
    time_t_to_struct_tm(&time, &tm);

    day_of_week = tm.tm_wday;
    if (day_of_week == DAY_OF_WEEK_SUNDAY_COMPAT) {
        day_of_week = DAY_OF_WEEK_SUNDAY;
    }

    /* If the year starts on a Thursday, it has 53 weeks */
    if (day_of_week == DAY_OF_WEEK_THURSDAY) {
        week = 53;
    }

    /* If this year is a leap year, and it starts on a Wednesday,
       it has 53 weeks */
    if (IS_LEAP_YEAR(year) && day_of_week == DAY_OF_WEEK_WEDNESDAY) {
        week = 53;
    }

    return week;
}

/**
 * Make sure that year, month, and day are valid, and set day_of_year and
 * day_of_week to their correct values.
 */
static void
check_date_data(struct PresentDateData * const data)
{
    time_t time;
    struct tm tm;

    time = unix_timestamp_to_time_t(to_unix_timestamp(
            data->year, data->month, data->day, 0, 0, 0));
    time_t_to_struct_tm(&time, &tm);

    data->year = (int_year)tm.tm_year + STRUCT_TM_YEAR_OFFSET;
    data->month = (int_month)tm.tm_mon + STRUCT_TM_MONTH_OFFSET;
    data->day = (int_day)tm.tm_mday;
    data->day_of_year = (int_day_of_year)tm.tm_yday +
        STRUCT_TM_DAY_OF_YEAR_OFFSET;
    data->day_of_week = (int_day_of_week)tm.tm_wday;
    if (data->day_of_week == DAY_OF_WEEK_SUNDAY_COMPAT) {
        data->day_of_week = DAY_OF_WEEK_SUNDAY;
    }
}

/**
 * Initialize a new Date instance based on its data parameters.
 */
static void
init_date(
        struct Date * const result,
        int_year year,
        int_month month,
        int_day day)
{
    static const int_day DAYS_PER_MONTH[13] = {
        0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    int_day days_in_month;

    assert(result != NULL);
    CLEAR(result);

    if (month < 1 || month > 12) {
        result->has_error = 1;
        result->errors.month_out_of_range = 1;
    }

    days_in_month = (IS_LEAP_YEAR(year) && month == 2) ? 29 :
        DAYS_PER_MONTH[month];
    if (day < 1 || day > days_in_month) {
        result->has_error = 1;
        result->errors.day_out_of_range = 1;
    }

    if (!result->has_error) {
        result->data_.year = year;
        result->data_.month = month;
        result->data_.day = day;
        check_date_data(&result->data_);
    }
}

/**
 * Initialize a new Date instance based on its data parameters, without
 * checking any bounds.
 */
static void
init_date_no_bounds_check(
        struct Date * const result,
        int_year year,
        int_month month,
        int_day day)
{
    assert(result != NULL);
    CLEAR(result);

    result->data_.year = year;
    result->data_.month = month;
    result->data_.day = day;
    check_date_data(&result->data_);
}


struct Date
Date_from_year(int_year year)
{
    struct Date result;
    init_date(&result, year, 1, 1);
    return result;
}

void
Date_ptr_from_year(struct Date * const result, int_year year)
{
    init_date(result, year, 1, 1);
}

struct Date
Date_from_year_month(int_year year, int_month month)
{
    struct Date result;
    init_date(&result, year, month, 1);
    return result;
}

void
Date_ptr_from_year_month(
        struct Date * const result,
        int_year year,
        int_month month)
{
    init_date(result, year, month, 1);
}

struct Date
Date_from_year_month_day(int_year year, int_month month, int_day day)
{
    struct Date result;
    init_date(&result, year, month, day);
    return result;
}

void
Date_ptr_from_year_month_day(
        struct Date * const result,
        int_year year,
        int_month month,
        int_day day)
{
    init_date(result, year, month, day);
}

struct Date
Date_from_year_day(int_year year, int_day_of_year day_of_year)
{
    struct Date result;
    init_date_no_bounds_check(&result, year, 1, (int_day)(day_of_year));
    return result;
}

void
Date_ptr_from_year_day(
        struct Date * const result,
        int_year year,
        int_day_of_year day_of_year)
{
    init_date_no_bounds_check(result, year, 1, (int_day)(day_of_year));
}

struct Date
Date_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week)
{
    struct Date result;
    Date_ptr_from_year_week_day(&result, year, week_of_year, day_of_week);
    return result;
}

void
Date_ptr_from_year_week_day(
        struct Date * const result,
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week)
{
    time_t time;
    struct tm tm;
    int_day_of_week jan_4_day_of_week;
    int_day_of_year ordinal_date;

    assert(result != NULL);
    CLEAR(result);

    if (week_of_year < 1 || week_of_year > last_week_of_year(year)) {
        result->has_error = 1;
        result->errors.week_of_year_out_of_range = 1;
    }

    if (day_of_week == DAY_OF_WEEK_SUNDAY_COMPAT) {
        day_of_week = DAY_OF_WEEK_SUNDAY;
    }
    if (day_of_week < 1 || day_of_week > 7) {
        result->has_error = 1;
        result->errors.day_of_week_out_of_range = 1;
    }

    if (!result->has_error) {
        /* Get the weekday of Jan. 4 of this year */
        time = unix_timestamp_to_time_t(to_unix_timestamp(
                year, 1, 4, 0, 0, 0));
        time_t_to_struct_tm(&time, &tm);

        jan_4_day_of_week = tm.tm_wday;
        if (jan_4_day_of_week == DAY_OF_WEEK_SUNDAY_COMPAT) {
            jan_4_day_of_week = DAY_OF_WEEK_SUNDAY;
        }
        assert(jan_4_day_of_week >= 1 && jan_4_day_of_week <= 7);

        /* Calculate the date using voodoo magic
           https://en.wikipedia.org/wiki/ISO_week_date#Calculating_a_date_given_the_year.2C_week_number_and_weekday
         */
        ordinal_date = week_of_year * 7 + day_of_week - (jan_4_day_of_week + 3);
        if (ordinal_date < 1) {
            year -= 1;
            ordinal_date += DAYS_IN_YEAR(year);
        }
        if (ordinal_date > DAYS_IN_YEAR(year)) {
            ordinal_date -= DAYS_IN_YEAR(year);
            year += 1;
        }

        Date_ptr_from_year_day(result, year, ordinal_date);
    }
}

int_year
Date_year(const struct Date * const self)
{
    assert(self != NULL);
    assert(self->has_error == 0);

    return self->data_.year;
}

int_month
Date_month(const struct Date * const self)
{
    assert(self != NULL);
    assert(self->has_error == 0);

    return self->data_.month;
}

int_day
Date_day(const struct Date * const self)
{
    assert(self != NULL);
    assert(self->has_error == 0);

    return self->data_.day;
}

int_day_of_year
Date_day_of_year(const struct Date * const self)
{
    assert(self != NULL);
    assert(self->has_error == 0);

    return self->data_.day_of_year;
}

struct PresentWeekYear
Date_week_of_year(const struct Date * const self)
{
    int_year year;
    int_week_of_year week;
    struct PresentWeekYear p;

    assert(self != NULL);
    assert(self->has_error == 0);

    /* Caculate the week number using pure voodoo magic
       https://en.wikipedia.org/wiki/ISO_week_date#Calculating_the_week_number_of_a_given_date
       */
    year = self->data_.year;
    week = (self->data_.day_of_year - self->data_.day_of_week + 10) / 7;

    if (week == 0) {
        /* It's the last week of the previous year */
        year -= 1;
        week = last_week_of_year(year);
    }
    if (week > last_week_of_year(year)) {
        /* It's the first week of the next year */
        year += 1;
        week = 1;
    }

    p.week = week;
    p.year = year;
    return p;
}

int_day_of_week
Date_day_of_week(const struct Date * const self)
{
    assert(self != NULL);
    assert(self->has_error == 0);

    return self->data_.day_of_week;
}

struct DayDelta
Date_difference(
        const struct Date * const self,
        const struct Date * const other)
{
    struct ClockTime noon;
    struct Timestamp self_timestamp, other_timestamp;
    struct TimeDelta time_delta;

    assert(self != NULL);
    assert(self->has_error == 0);
    assert(other != NULL);
    assert(other->has_error == 0);

    noon = ClockTime_noon();
    self_timestamp = Timestamp_create_utc(self, &noon);
    other_timestamp = Timestamp_create_utc(other, &noon);
    time_delta = Timestamp_difference(&self_timestamp, &other_timestamp);
    return TimeDelta_to_DayDelta_truncated(&time_delta);
}

struct DayDelta
Date_absolute_difference(
        const struct Date * const self,
        const struct Date * const other)
{
    struct DayDelta delta;

    assert(self != NULL);
    assert(self->has_error == 0);
    assert(other != NULL);
    assert(other->has_error == 0);

    delta = Date_difference(self, other);
    if (DayDelta_is_negative(&delta)) {
        DayDelta_negate(&delta);
    }
    return delta;
}

void
Date_add_DayDelta(
        struct Date * const self,
        const struct DayDelta * const delta)
{
    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    self->data_.day += delta->data_.delta_days;
    check_date_data(&self->data_);
}

void
Date_add_MonthDelta(
        struct Date * const self,
        const struct MonthDelta * const delta)
{
    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    self->data_.month += delta->data_.delta_months;
    check_date_data(&self->data_);
}

void
Date_subtract_DayDelta(
        struct Date * const self,
        const struct DayDelta * const delta)
{
    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    self->data_.day -= delta->data_.delta_days;
    check_date_data(&self->data_);
}

void
Date_subtract_MonthDelta(
        struct Date * const self,
        const struct MonthDelta * const delta)
{
    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    self->data_.month -= delta->data_.delta_months;
    check_date_data(&self->data_);
}

short
Date_compare(
        const struct Date * const lhs,
        const struct Date * const rhs)
{
    assert(lhs != NULL);
    assert(lhs->has_error == 0);
    assert(rhs != NULL);
    assert(rhs->has_error == 0);

    return
        STRUCT_COMPARE(year,
            STRUCT_COMPARE(month,
                STRUCT_COMPARE(day, 0)));
}

STRUCT_COMPARISON_OPERATORS(Date)

