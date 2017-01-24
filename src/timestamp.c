/*
 * Present - Date/Time Library
 *
 * Implementation of the Timestamp methods
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

/**
 * Convert a struct tm to a Date.
 *
 * Precondition: The struct tm must be valid (see @p clean_struct_tm).
 */
static void
struct_tm_to_date(const struct tm * const tm, struct Date * const date)
{
    Date_ptr_from_year_month_day(
            date,
            tm->tm_year + STRUCT_TM_YEAR_OFFSET,
            tm->tm_mon + STRUCT_TM_MONTH_OFFSET,
            tm->tm_mday);
}

/**
 * Convert a struct tm to a ClockTime.
 *
 * Precondition: The struct tm must be valid (see @p clean_struct_tm).
 */
static void
struct_tm_to_clock_time(
        const struct tm * const tm,
        struct ClockTime * const clock_time)
{
    ClockTime_ptr_from_hour_minute_second(
            clock_time,
            tm->tm_hour,
            tm->tm_min,
            tm->tm_sec);
}

/**
 * Check additional_nanoseconds to make sure it is a positive integer less
 * than NANOSECONDS_IN_SECOND.
 */
#define CHECK_DATA(data)                                            \
    do {                                                            \
        while (data.additional_nanoseconds < 0) {                   \
            data.timestamp_seconds -= 1;                            \
            data.additional_nanoseconds += NANOSECONDS_IN_SECOND;   \
        }                                                           \
        if (data.additional_nanoseconds >= NANOSECONDS_IN_SECOND) { \
            data.timestamp_seconds += data.additional_nanoseconds / \
                NANOSECONDS_IN_SECOND;                              \
            data.additional_nanoseconds %= NANOSECONDS_IN_SECOND;   \
        }                                                           \
    } while (0)

/**
 * Check a Date and a ClockTime to make sure they aren't erroneous (if so, set
 * the proper errors on "result").
 */
#define CHECK_DATE_AND_CLOCK_TIME(date, clock_time) \
    do {                                            \
        if ((date)->has_error) {                    \
            result->has_error = 1;                  \
            result->errors.invalid_date = 1;        \
        }                                           \
        if ((clock_time)->has_error) {              \
            result->has_error = 1;                  \
            result->errors.invalid_clock_time = 1;  \
        }                                           \
    } while (0)


/** Initialize a new Timestamp instance based on its data parameters. */
static void
init_timestamp(
        struct Timestamp * const result,
        int_timestamp timestamp_seconds,
        int_timestamp additional_nanoseconds)
{
    assert(result != NULL);
    CLEAR(result);

    result->data_.timestamp_seconds = timestamp_seconds;
    result->data_.additional_nanoseconds = additional_nanoseconds;
}

/**
 * Initialize a new Timestamp instance based on a Date and a ClockTime in UTC.
 */
static void
init_timestamp_from_date_and_clock_time_utc(
        struct Timestamp * const result,
        const struct Date * const date,
        const struct ClockTime * const clock_time)
{
    struct TimeDelta time_since_midnight;

    assert(result != NULL);
    assert(date != NULL);
    assert(clock_time != NULL);

    CLEAR(result);

    /* Make sure the Date and ClockTime aren't erroneous */
    CHECK_DATE_AND_CLOCK_TIME(date, clock_time);

    if (!result->has_error) {
        /* This is a more useful form of the clock time */
        time_since_midnight = ClockTime_time_since_midnight(clock_time);

        init_timestamp(
                result,
                to_unix_timestamp(
                        Date_year(date),
                        Date_month(date),
                        Date_day(date),
                        0, 0, 0) +
                    time_since_midnight.data_.delta_seconds,
                time_since_midnight.data_.delta_nanoseconds);
    }
}

/**
 * Initialize a new Timestamp instance based on a Date, a ClockTime, and a time
 * zone offset.
 */
static void
init_timestamp_from_date_and_clock_time(
        struct Timestamp * const result,
        const struct Date * const date,
        const struct ClockTime * const clock_time,
        const struct TimeDelta * const time_zone_offset)
{
    assert(result != NULL);
    assert(date != NULL);
    assert(clock_time != NULL);

    CLEAR(result);

    /* Make sure the Date and ClockTime aren't erroneous */
    CHECK_DATE_AND_CLOCK_TIME(date, clock_time);

    if (!result->has_error) {
        /* First, pretend it's just UTC */
        init_timestamp_from_date_and_clock_time_utc(result, date, clock_time);
        /* Now, subtract the UTC offset (since we're technically converting
           TO UTC) */
        Timestamp_subtract_TimeDelta(result, time_zone_offset);
    }
}

/**
 * Initialize a new Timestamp instance based on a "struct tm" in the system's
 * current local time zone.
 */
static void
init_timestamp_from_struct_tm_local(
        struct Timestamp * const result,
        const struct tm tm)
{
    struct tm tm_copy;
    time_t time;

    tm_copy = tm;
    /* Throw it right through mktime */
    time = struct_tm_to_time_t_local(&tm_copy);
    init_timestamp(result, time_t_to_unix_timestamp(time), 0);
}


struct Timestamp
Timestamp_from_time_t(const time_t time)
{
    struct Timestamp result;
    init_timestamp(&result, time_t_to_unix_timestamp(time), 0);
    return result;
}

void
Timestamp_ptr_from_time_t(
        struct Timestamp * const result,
        const time_t time)
{
    init_timestamp(result, time_t_to_unix_timestamp(time), 0);
}

struct Timestamp
Timestamp_from_struct_tm(
        const struct tm tm,
        const struct TimeDelta * const time_zone_offset)
{
    struct Timestamp result;
    Timestamp_ptr_from_struct_tm(&result, tm, time_zone_offset);
    return result;
}

void
Timestamp_ptr_from_struct_tm(
        struct Timestamp * const result,
        const struct tm tm,
        const struct TimeDelta * const time_zone_offset)
{
    struct Date date;
    struct ClockTime clock_time;
    struct tm tm_copy;

    tm_copy = tm;
    clean_struct_tm(&tm_copy);

    struct_tm_to_date(&tm_copy, &date);
    struct_tm_to_clock_time(&tm_copy, &clock_time);
    init_timestamp_from_date_and_clock_time(
            result, &date, &clock_time, time_zone_offset);
}

struct Timestamp
Timestamp_from_struct_tm_utc(const struct tm tm)
{
    struct Timestamp result;
    Timestamp_ptr_from_struct_tm_utc(&result, tm);
    return result;
}

void
Timestamp_ptr_from_struct_tm_utc(
        struct Timestamp * const result,
        const struct tm tm)
{
    struct Date date;
    struct ClockTime clock_time;
    struct tm tm_copy;

    tm_copy = tm;
    clean_struct_tm(&tm_copy);

    struct_tm_to_date(&tm_copy, &date);
    struct_tm_to_clock_time(&tm_copy, &clock_time);
    init_timestamp_from_date_and_clock_time_utc(result, &date, &clock_time);
}

struct Timestamp
Timestamp_from_struct_tm_local(const struct tm tm)
{
    struct Timestamp result;
    Timestamp_ptr_from_struct_tm_local(&result, tm);
    return result;
}

void
Timestamp_ptr_from_struct_tm_local(
        struct Timestamp * const result,
        const struct tm tm)
{
    init_timestamp_from_struct_tm_local(result, tm);
}

struct Timestamp
Timestamp_create(
        const struct Date * const date,
        const struct ClockTime * const clock_time,
        const struct TimeDelta * const time_zone_offset)
{
    struct Timestamp result;
    Timestamp_ptr_create(&result, date, clock_time, time_zone_offset);
    return result;
}

void
Timestamp_ptr_create(
        struct Timestamp * const result,
        const struct Date * const date,
        const struct ClockTime * const clock_time,
        const struct TimeDelta * const time_zone_offset)
{
    init_timestamp_from_date_and_clock_time(
            result, date, clock_time, time_zone_offset);
}

struct Timestamp
Timestamp_create_utc(
        const struct Date * const date,
        const struct ClockTime * const clock_time)
{
    struct Timestamp result;
    Timestamp_ptr_create_utc(&result, date, clock_time);
    return result;
}

void
Timestamp_ptr_create_utc(
        struct Timestamp * const result,
        const struct Date * const date,
        const struct ClockTime * const clock_time)
{
    init_timestamp_from_date_and_clock_time_utc(result, date, clock_time);
}

struct Timestamp
Timestamp_create_local(
        const struct Date * const date,
        const struct ClockTime * const clock_time)
{
    struct Timestamp result;
    Timestamp_ptr_create_local(&result, date, clock_time);
    return result;
}

void
Timestamp_ptr_create_local(
        struct Timestamp * const result,
        const struct Date * const date,
        const struct ClockTime * const clock_time)
{
    struct tm tm;

    assert(result != NULL);
    assert(date != NULL);
    assert(clock_time != NULL);

    CLEAR(result);

    /* Make sure the Date and ClockTime aren't erroneous */
    CHECK_DATE_AND_CLOCK_TIME(date, clock_time);

    if (!result->has_error) {
        CLEAR(&tm);
        tm.tm_year = Date_year(date) - STRUCT_TM_YEAR_OFFSET;
        tm.tm_mon = Date_month(date) - STRUCT_TM_MONTH_OFFSET;
        tm.tm_mday = Date_day(date);
        tm.tm_hour = ClockTime_hour(clock_time);
        tm.tm_min = ClockTime_minute(clock_time);
        tm.tm_sec = ClockTime_second(clock_time);
        tm.tm_isdst = -1;

        init_timestamp_from_struct_tm_local(
                result,
                tm);
    }
}

struct Timestamp
Timestamp_now(void)
{
    struct Timestamp result;
    Timestamp_ptr_now(&result);
    return result;
}

void
Timestamp_ptr_now(struct Timestamp * const result)
{
    struct PresentNowStruct now;
    present_now(&now);
    init_timestamp(result, time_t_to_unix_timestamp(now.sec), now.nsec);
}

struct Timestamp
Timestamp_epoch(void)
{
    struct Timestamp result;
    init_timestamp(&result, 0, 0);
    return result;
}

void
Timestamp_ptr_epoch(struct Timestamp * const result)
{
    init_timestamp(result, 0, 0);
}

time_t
Timestamp_get_time_t(const struct Timestamp * const self)
{
    assert(self != NULL);
    assert(self->has_error == 0);

    return unix_timestamp_to_time_t(self->data_.timestamp_seconds);
}

struct tm
Timestamp_get_struct_tm(
        const struct Timestamp * const self,
        const struct TimeDelta * const time_zone_offset)
{
    struct Timestamp copy;

    assert(self != NULL);
    assert(self->has_error == 0);
    assert(time_zone_offset != NULL);

    copy = *self;
    Timestamp_add_TimeDelta(&copy, time_zone_offset);
    return Timestamp_get_struct_tm_utc(&copy);
}

struct tm
Timestamp_get_struct_tm_utc(const struct Timestamp * const self)
{
    time_t time;
    struct tm result;

    assert(self != NULL);
    assert(self->has_error == 0);

    time = unix_timestamp_to_time_t(self->data_.timestamp_seconds);
    time_t_to_struct_tm(&time, &result);
    return result;
}

struct tm
Timestamp_get_struct_tm_local(const struct Timestamp * const self)
{
    time_t time;
    struct tm result;

    assert(self != NULL);
    assert(self->has_error == 0);

    time = unix_timestamp_to_time_t(self->data_.timestamp_seconds);
    time_t_to_struct_tm_local(&time, &result);
    return result;
}

struct Date
Timestamp_get_date(
        const struct Timestamp * const self,
        const struct TimeDelta * const time_zone_offset)
{
    struct tm tm;
    struct Date date;

    assert(self != NULL);
    assert(self->has_error == 0);
    assert(time_zone_offset != NULL);

    tm = Timestamp_get_struct_tm(self, time_zone_offset);
    struct_tm_to_date(&tm, &date);
    return date;
}

struct Date
Timestamp_get_date_utc(const struct Timestamp * const self)
{
    struct tm tm;
    struct Date date;

    assert(self != NULL);
    assert(self->has_error == 0);

    tm = Timestamp_get_struct_tm_utc(self);
    struct_tm_to_date(&tm, &date);
    return date;
}

struct Date
Timestamp_get_date_local(const struct Timestamp * const self)
{
    struct tm tm;
    struct Date date;

    assert(self != NULL);
    assert(self->has_error == 0);

    tm = Timestamp_get_struct_tm_local(self);
    struct_tm_to_date(&tm, &date);
    return date;
}

struct ClockTime
Timestamp_get_clock_time(
        const struct Timestamp * const self,
        const struct TimeDelta * const time_zone_offset)
{
    struct tm tm;
    struct ClockTime clock_time;

    assert(self != NULL);
    assert(self->has_error == 0);

    tm = Timestamp_get_struct_tm(self, time_zone_offset);
    struct_tm_to_clock_time(&tm, &clock_time);
    return clock_time;
}

struct ClockTime
Timestamp_get_clock_time_utc(const struct Timestamp * const self)
{
    struct tm tm;
    struct ClockTime clock_time;

    assert(self != NULL);
    assert(self->has_error == 0);

    tm = Timestamp_get_struct_tm_utc(self);
    struct_tm_to_clock_time(&tm, &clock_time);
    return clock_time;
}

struct ClockTime
Timestamp_get_clock_time_local(const struct Timestamp * const self)
{
    struct tm tm;
    struct ClockTime clock_time;

    assert(self != NULL);
    assert(self->has_error == 0);

    tm = Timestamp_get_struct_tm_local(self);
    struct_tm_to_clock_time(&tm, &clock_time);
    return clock_time;
}

struct TimeDelta
Timestamp_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other)
{
    struct TimeDelta delta, ns_delta;

    assert(self != NULL);
    assert(self->has_error == 0);
    assert(other != NULL);
    assert(other->has_error == 0);

    delta = TimeDelta_from_seconds(
            self->data_.timestamp_seconds - other->data_.timestamp_seconds);
    ns_delta = TimeDelta_from_nanoseconds(
            self->data_.additional_nanoseconds -
            other->data_.additional_nanoseconds);
    TimeDelta_add(&delta, &ns_delta);
    return delta;
}

struct TimeDelta
Timestamp_absolute_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other)
{
    struct TimeDelta delta;

    assert(self != NULL);
    assert(self->has_error == 0);
    assert(other != NULL);
    assert(other->has_error == 0);

    delta = Timestamp_difference(self, other);
    if (TimeDelta_is_negative(&delta)) {
        TimeDelta_negate(&delta);
    }
    return delta;
}

void
Timestamp_add_TimeDelta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta)
{
    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    self->data_.timestamp_seconds += delta->data_.delta_seconds;
    self->data_.additional_nanoseconds += delta->data_.delta_nanoseconds;
    CHECK_DATA(self->data_);
}

void
Timestamp_add_DayDelta(
        struct Timestamp * const self,
        const struct DayDelta * const delta)
{
    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    self->data_.timestamp_seconds += delta->data_.delta_days * SECONDS_IN_DAY;
}

void
Timestamp_add_MonthDelta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta)
{
    time_t time;
    struct tm tm;

    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    time = unix_timestamp_to_time_t(self->data_.timestamp_seconds);
    time_t_to_struct_tm(&time, &tm);
    tm.tm_mon += delta->data_.delta_months;
    self->data_.timestamp_seconds = time_t_to_unix_timestamp(to_unix_timestamp(
            tm.tm_year + STRUCT_TM_YEAR_OFFSET,
            tm.tm_mon + STRUCT_TM_MONTH_OFFSET,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec));
}

void
Timestamp_subtract_TimeDelta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta)
{
    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    self->data_.timestamp_seconds -= delta->data_.delta_seconds;
    self->data_.additional_nanoseconds -= delta->data_.delta_nanoseconds;
    CHECK_DATA(self->data_);
}

void
Timestamp_subtract_DayDelta(
        struct Timestamp * const self,
        const struct DayDelta * const delta)
{
    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    self->data_.timestamp_seconds -= delta->data_.delta_days * SECONDS_IN_DAY;
}

void
Timestamp_subtract_MonthDelta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta)
{
    time_t time;
    struct tm tm;

    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    time = unix_timestamp_to_time_t(self->data_.timestamp_seconds);
    time_t_to_struct_tm(&time, &tm);
    tm.tm_mon -= delta->data_.delta_months;
    self->data_.timestamp_seconds = time_t_to_unix_timestamp(to_unix_timestamp(
            tm.tm_year + STRUCT_TM_YEAR_OFFSET,
            tm.tm_mon + STRUCT_TM_MONTH_OFFSET,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec));
}

short
Timestamp_compare(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs)
{
    assert(lhs != NULL);
    assert(lhs->has_error == 0);
    assert(rhs != NULL);
    assert(rhs->has_error == 0);

    return
        STRUCT_COMPARE(timestamp_seconds,
            STRUCT_COMPARE(additional_nanoseconds, 0));
}

STRUCT_COMPARISON_OPERATORS(Timestamp)

