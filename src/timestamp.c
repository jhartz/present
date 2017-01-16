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
#include "utils/time-calls.h"

/** Convert a struct tm to a Date. */
static struct Date
struct_tm_to_date(const struct tm tm)
{
    struct tm tm_copy;
    time_t mktime_returned;

    tm_copy = tm;
    /* Throw it through mktime to fix any weirdness */
    mktime_returned = present_mktime(&tm_copy);
    assert(mktime_returned != -1);

    return Date_from_year_month_day(
            tm_copy.tm_year + STRUCT_TM_YEAR_OFFSET,
            tm_copy.tm_mon + STRUCT_TM_MONTH_OFFSET,
            tm_copy.tm_mday);
}

/** Convert a struct tm to a ClockTime. */
static struct ClockTime
struct_tm_to_clock_time(const struct tm tm)
{
    struct tm tm_copy;
    time_t mktime_returned;

    tm_copy = tm;
    /* Throw it through mktime to fix any weirdness */
    mktime_returned = present_mktime(&tm_copy);
    assert(mktime_returned != -1);

    return ClockTime_from_hour_minute_second(
            tm_copy.tm_hour,
            tm_copy.tm_min,
            tm_copy.tm_sec);
}

/** Convert a Date and ClockTime to a struct tm. */
static struct tm
convert_to_struct_tm(
        const struct Date * const date,
        const struct ClockTime * const clockTime)
{
    struct tm tm;
    time_t mktime_returned;

    memset((void *) &tm, 0, sizeof(struct tm));
    tm.tm_sec = (int) ClockTime_second(clockTime);
    tm.tm_min = (int) ClockTime_minute(clockTime);
    tm.tm_hour = (int) ClockTime_hour(clockTime);
    tm.tm_mday = (int) Date_day(date);
    tm.tm_mon = (int) Date_month(date) - STRUCT_TM_MONTH_OFFSET;
    tm.tm_year = (int) Date_year(date) - STRUCT_TM_YEAR_OFFSET;
    tm.tm_isdst = -1;

    mktime_returned = present_mktime(&tm);
    assert(mktime_returned != -1);

    return tm;
}

/** Convert a time_t to a UNIX timestamp. */
static int_timestamp
time_t_to_timestamp(const time_t timestamp)
{
    /* TODO: We're just assuming that time_t is already a UNIX timestamp */
    return (int_timestamp) timestamp;
}

/** Convert a UNIX timestamp to a time_t. */
static time_t
timestamp_to_time_t(const int_timestamp timestamp_seconds)
{
    /* TODO: We're just assuming that time_t is a UNIX timestamp */
    return (time_t) timestamp_seconds;
}

/**
 * Check additional_nanoseconds to make sure it is a positive integer less
 * than NANOSECONDS_IN_SECOND.
 */
#define CHECK_DATA(data)                                            \
    while (data.additional_nanoseconds < 0) {                       \
        data.timestamp_seconds -= 1;                                \
        data.additional_nanoseconds += NANOSECONDS_IN_SECOND;       \
    }                                                               \
    while (data.additional_nanoseconds >= NANOSECONDS_IN_SECOND) {  \
        data.timestamp_seconds += 1;                                \
        data.additional_nanoseconds -= NANOSECONDS_IN_SECOND;       \
    }

/**
 * Check a Date and a ClockTime to make sure they aren't erroneous (if so, set
 * the proper errors on "result").
 */
#define CHECK_DATE_AND_CLOCK_TIME(date, clockTime)  \
    if ((date)->has_error) {                        \
        result->has_error = 1;                      \
        result->errors.invalid_date = 1;            \
    }                                               \
    if ((clockTime)->has_error) {                   \
        result->has_error = 1;                      \
        result->errors.invalid_clock_time = 1;      \
    }


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


struct Timestamp
Timestamp_from_time_t(const time_t timestamp)
{
    struct Timestamp result;
    init_timestamp(&result, time_t_to_timestamp(timestamp), 0);
    return result;
}

void
Timestamp_ptr_from_time_t(
        struct Timestamp * const result,
        const time_t timestamp)
{
    init_timestamp(result, time_t_to_timestamp(timestamp), 0);
}

struct Timestamp
Timestamp_from_struct_tm(
        const struct tm tm,
        const struct TimeDelta * const timeZoneOffset)
{
    struct Timestamp result;
    Timestamp_ptr_from_struct_tm(&result, tm, timeZoneOffset);
    return result;
}

void
Timestamp_ptr_from_struct_tm(
        struct Timestamp * const result,
        const struct tm tm,
        const struct TimeDelta * const timeZoneOffset)
{
    struct Date date;
    struct ClockTime clock_time;

    date = struct_tm_to_date(tm);
    clock_time = struct_tm_to_clock_time(tm);
    Timestamp_ptr_create(result, &date, &clock_time, timeZoneOffset);
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

    date = struct_tm_to_date(tm);
    clock_time = struct_tm_to_clock_time(tm);
    Timestamp_ptr_create_utc(result, &date, &clock_time);
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
    struct tm tm_copy;
    time_t timestamp;

    tm_copy = tm;
    /* Throw it right through mktime */
    timestamp = present_mktime(&tm_copy);
    assert(timestamp != -1);
    init_timestamp(result, time_t_to_timestamp(timestamp), 0);
}

struct Timestamp
Timestamp_create(
        const struct Date * const date,
        const struct ClockTime * const clockTime,
        const struct TimeDelta * const timeZoneOffset)
{
    struct Timestamp result;
    Timestamp_ptr_create(&result, date, clockTime, timeZoneOffset);
    return result;
}

void
Timestamp_ptr_create(
        struct Timestamp * const result,
        const struct Date * const date,
        const struct ClockTime * const clockTime,
        const struct TimeDelta * const timeZoneOffset)
{
    assert(result != NULL);
    assert(date != NULL);
    assert(clockTime != NULL);

    CLEAR(result);

    /* Make sure the Date and ClockTime aren't erroneous */
    CHECK_DATE_AND_CLOCK_TIME(date, clockTime)

    if (!result->has_error) {
        /* First, pretend it's just UTC */
        Timestamp_ptr_create_utc(result, date, clockTime);
        /* Now, subtract the UTC offset (since we're technically converting
           TO UTC) */
        Timestamp_subtract_TimeDelta(result, timeZoneOffset);
    }
}

struct Timestamp
Timestamp_create_utc(
        const struct Date * const date,
        const struct ClockTime * const clockTime)
{
    struct Timestamp result;
    Timestamp_ptr_create_utc(&result, date, clockTime);
    return result;
}

void
Timestamp_ptr_create_utc(
        struct Timestamp * const result,
        const struct Date * const date,
        const struct ClockTime * const clockTime)
{
    /** Day of the year that each month starts on (in non-leap years). */
    static const int_day_of_year DAY_OF_START_OF_MONTH[13] = {
        0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };

    int_timestamp year, month, days_since_epoch;
    struct TimeDelta time_since_midnight;

    assert(result != NULL);
    assert(date != NULL);
    assert(clockTime != NULL);

    CLEAR(result);

    /* Make sure the Date and ClockTime aren't erroneous */
    CHECK_DATE_AND_CLOCK_TIME(date, clockTime)

    if (!result->has_error) {
        /* First, the hard part... determining the number of days since the UNIX
           epoch, taking leap years into account */
        year = Date_year(date);
        month = Date_month(date);
        days_since_epoch = Date_day(date) - 1;

        days_since_epoch += DAY_OF_START_OF_MONTH[month];
        days_since_epoch += 365 * (year - 1970);
        /* Every 4 years is a leap year */
        days_since_epoch += (year - 1968) / 4;
        /* Except the turn of the century */
        days_since_epoch -= (year - 1900) / 100;
        /* Except every 4th century */
        days_since_epoch += (year - 1600) / 400;
        /* If it's still January or February of this year, though, we don't
           need to include the extra for this year yet */
        if (IS_LEAP_YEAR(year) && month <= 2) {
            days_since_epoch--;
        }

        /* This is a more useful form of the clock time */
        time_since_midnight = ClockTime_time_since_midnight(clockTime);

        init_timestamp(
            result,
            days_since_epoch * SECONDS_IN_DAY +
            time_since_midnight.data_.delta_seconds,
            time_since_midnight.data_.delta_nanoseconds);
    }
}

struct Timestamp
Timestamp_create_local(
        const struct Date * const date,
        const struct ClockTime * const clockTime)
{
    struct Timestamp result;
    Timestamp_ptr_create_local(&result, date, clockTime);
    return result;
}

void
Timestamp_ptr_create_local(
        struct Timestamp * const result,
        const struct Date * const date,
        const struct ClockTime * const clockTime)
{
    assert(result != NULL);
    assert(date != NULL);
    assert(clockTime != NULL);

    CLEAR(result);

    /* Make sure the Date and ClockTime aren't erroneous */
    CHECK_DATE_AND_CLOCK_TIME(date, clockTime)

    if (!result->has_error) {
        Timestamp_ptr_from_struct_tm_local(
            result,
            convert_to_struct_tm(date, clockTime));
    }
}

struct Timestamp
Timestamp_now()
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
    init_timestamp(result, time_t_to_timestamp(now.sec), now.nsec);
}

struct Timestamp
Timestamp_epoch()
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

    return timestamp_to_time_t(self->data_.timestamp_seconds);
}

struct tm
Timestamp_get_struct_tm(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset)
{
    struct Timestamp copy;

    assert(self != NULL);
    assert(self->has_error == 0);
    assert(timeZoneOffset != NULL);

    copy = *self;
    Timestamp_add_TimeDelta(&copy, timeZoneOffset);
    return Timestamp_get_struct_tm_utc(&copy);
}

struct tm
Timestamp_get_struct_tm_utc(const struct Timestamp * const self)
{
    time_t timestamp;
    struct tm result;

    assert(self != NULL);
    assert(self->has_error == 0);

    timestamp = timestamp_to_time_t(self->data_.timestamp_seconds);
    present_gmtime(&timestamp, &result);
    return result;
}

struct tm
Timestamp_get_struct_tm_local(const struct Timestamp * const self)
{
    time_t timestamp;
    struct tm result;

    assert(self != NULL);
    assert(self->has_error == 0);

    timestamp = timestamp_to_time_t(self->data_.timestamp_seconds);
    present_localtime(&timestamp, &result);
    return result;
}

struct Date
Timestamp_get_date(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset)
{
    assert(self != NULL);
    assert(self->has_error == 0);
    assert(timeZoneOffset != NULL);

    return struct_tm_to_date(Timestamp_get_struct_tm(self, timeZoneOffset));
}

struct Date
Timestamp_get_date_utc(const struct Timestamp * const self)
{
    assert(self != NULL);
    assert(self->has_error == 0);

    return struct_tm_to_date(Timestamp_get_struct_tm_utc(self));
}

struct Date
Timestamp_get_date_local(const struct Timestamp * const self)
{
    assert(self != NULL);
    assert(self->has_error == 0);

    return struct_tm_to_date(Timestamp_get_struct_tm_local(self));
}

struct ClockTime
Timestamp_get_clock_time(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset)
{
    assert(self != NULL);
    assert(self->has_error == 0);

    return struct_tm_to_clock_time(
            Timestamp_get_struct_tm(self, timeZoneOffset));
}

struct ClockTime
Timestamp_get_clock_time_utc(const struct Timestamp * const self)
{
    assert(self != NULL);
    assert(self->has_error == 0);

    return struct_tm_to_clock_time(Timestamp_get_struct_tm_utc(self));
}

struct ClockTime
Timestamp_get_clock_time_local(const struct Timestamp * const self)
{
    assert(self != NULL);
    assert(self->has_error == 0);

    return struct_tm_to_clock_time(Timestamp_get_struct_tm_local(self));
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
    CHECK_DATA(self->data_)
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
    time_t timestamp;
    struct tm tm;

    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    timestamp = timestamp_to_time_t(self->data_.timestamp_seconds);
    present_localtime(&timestamp, &tm);
    tm.tm_mon += delta->data_.delta_months;
    self->data_.timestamp_seconds = present_mktime(&tm);
    assert(self->data_.timestamp_seconds != -1);
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
    CHECK_DATA(self->data_)
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
    time_t timestamp;
    struct tm tm;

    assert(self != NULL);
    assert(self->has_error == 0);
    assert(delta != NULL);

    timestamp = timestamp_to_time_t(self->data_.timestamp_seconds);
    present_localtime(&timestamp, &tm);
    tm.tm_mon -= delta->data_.delta_months;
    self->data_.timestamp_seconds = present_mktime(&tm);
    assert(self->data_.timestamp_seconds != -1);
}

int
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

