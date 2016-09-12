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

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-timestamp-data.h"

#include "present-constants.h"
#include "present-syscalls.h"
#include "present-utils.h"

#include "present/clock-time.h"
#include "present/date.h"
#include "present/day-delta.h"
#include "present/month-delta.h"
#include "present/time-delta.h"

#include "present/timestamp.h"

/** Convert a struct tm to a Date. */
static struct Date
struct_tm_to_date(const struct tm tm) {
    struct tm tmCopy = tm;
    /* Throw it through mktime to fix any weirdness */
    assert(present_mktime(&tmCopy) != -1);

    return Date_from_year_month_day(
            tmCopy.tm_year + STRUCT_TM_YEAR_OFFSET,
            tmCopy.tm_mon + STRUCT_TM_MONTH_OFFSET,
            tmCopy.tm_mday);
}

/** Convert a struct tm to a ClockTime. */
static struct ClockTime
struct_tm_to_clock_time(const struct tm tm) {
    struct tm tmCopy = tm;
    /* Throw it through mktime to fix any weirdness */
    assert(present_mktime(&tmCopy) != -1);

    return ClockTime_from_hour_minute_second(
            tmCopy.tm_hour,
            tmCopy.tm_min,
            tmCopy.tm_sec);
}

/** Convert a Date and ClockTime to a struct tm. */
static struct tm
convert_to_struct_tm(
        const struct Date * const date,
        const struct ClockTime * const clockTime) {
    struct tm tm;
    memset((void *) &tm, 0, sizeof(struct tm));

    tm.tm_sec = (int) ClockTime_get_second(clockTime);
    tm.tm_min = (int) ClockTime_get_minute(clockTime);
    tm.tm_hour = (int) ClockTime_get_hour(clockTime);
    tm.tm_mday = (int) Date_get_day(date);
    tm.tm_mon = (int) Date_get_month(date) - STRUCT_TM_MONTH_OFFSET;
    tm.tm_year = (int) Date_get_year(date) - STRUCT_TM_YEAR_OFFSET;
    tm.tm_isdst = -1;
    assert(present_mktime(&tm) != -1);

    return tm;
}

/** Convert a time_t to a UNIX timestamp. */
int_timestamp
time_t_to_timestamp(const time_t timestamp) {
    /* TODO: We're just assuming that time_t is already a UNIX timestamp */
    return (int_timestamp) timestamp;
}

/** Convert a UNIX timestamp to a time_t. */
time_t
timestamp_to_time_t(const int_timestamp timestamp_seconds) {
    /* TODO: We're just assuming that time_t is a UNIX timestamp */
    return (time_t) timestamp_seconds;
}

/**
 * Check additional_nanoseconds to make sure it is a positive integer less
 * than NANOSECONDS_IN_SECOND.
 */
#define CHECK_DATA(data)                                        \
    if (data.additional_nanoseconds < 0) {                      \
        data.timestamp_seconds -= 1;                            \
        data.additional_nanoseconds += NANOSECONDS_IN_SECOND;   \
    }                                                           \
    if (data.additional_nanoseconds >= NANOSECONDS_IN_SECOND) { \
        data.timestamp_seconds += 1;                            \
        data.additional_nanoseconds -= NANOSECONDS_IN_SECOND;   \
    }


/** Create a new Timestamp instance based on its data parameters. */
static struct Timestamp
new_timestamp(
        int_timestamp timestamp_seconds,
        int_timestamp additional_nanoseconds) {
    CONSTRUCTOR_HEAD(Timestamp);
    struct PresentTimestampData data;
    data.timestamp_seconds = timestamp_seconds;
    data.additional_nanoseconds = additional_nanoseconds;
    CONSTRUCTOR_RETURN(Timestamp, data);
}

/** Create a Timestamp with an "invalid ClockTime" error. */
static struct Timestamp
invalid_clock_time() {
    CONSTRUCTOR_HEAD(Timestamp);
    CONSTRUCTOR_ERROR_RETURN(Timestamp, INVALID_CLOCK_TIME);
}

/** Create a Timestamp with an "invalid Date" error. */
static struct Timestamp
invalid_date() {
    CONSTRUCTOR_HEAD(Timestamp);
    CONSTRUCTOR_ERROR_RETURN(Timestamp, INVALID_DATE);
}

struct Timestamp
Timestamp_from_time_t(const time_t timestamp) {
    return new_timestamp(time_t_to_timestamp(timestamp), 0);
}

struct Timestamp
Timestamp_from_struct_tm(
        const struct tm tm,
        const struct TimeDelta * const timeZoneOffset) {
    struct Date date = struct_tm_to_date(tm);
    struct ClockTime clockTime = struct_tm_to_clock_time(tm);
    return Timestamp_create(&date, &clockTime, timeZoneOffset);
}

struct Timestamp
Timestamp_from_struct_tm_utc(const struct tm tm) {
    struct Date date = struct_tm_to_date(tm);
    struct ClockTime clockTime = struct_tm_to_clock_time(tm);
    return Timestamp_create_utc(&date, &clockTime);
}

struct Timestamp
Timestamp_from_struct_tm_local(const struct tm tm) {
    struct tm tmCopy = tm;
    /* Throw it right through mktime */
    time_t timestamp = present_mktime(&tmCopy);
    assert(timestamp != -1);
    return new_timestamp(time_t_to_timestamp(timestamp), 0);
}

struct Timestamp
Timestamp_create(
        const struct Date * const date,
        const struct ClockTime * const clockTime,
        const struct TimeDelta * const timeZoneOffset) {
    assert(date != NULL);
    assert(date->error == 0);
    assert(clockTime != NULL);
    assert(clockTime->error == 0);

    /* Make sure the Date and ClockTime aren't erroneous */
    if (date->error) {
        return invalid_date();
    }
    if (clockTime->error) {
        return invalid_clock_time();
    }

    /* First, pretend it's just UTC */
    struct Timestamp t = Timestamp_create_utc(date, clockTime);
    /* Now, subtract the UTC offset (since we're technically converting
       TO UTC) */
    /* TODO: Is subtracting correct? */
    Timestamp_subtract_time_delta(&t, timeZoneOffset);
    return t;
}

struct Timestamp
Timestamp_create_utc(
        const struct Date * const date,
        const struct ClockTime * const clockTime) {
    assert(date != NULL);
    assert(date->error == 0);
    assert(clockTime != NULL);
    assert(clockTime->error == 0);

    /** Day of the year that each month starts on (in non-leap years). */
    static const int_day_of_year DAY_OF_START_OF_MONTH[13] = {
        0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };

    /* Make sure the Date and ClockTime aren't erroneous */
    if (date->error) {
        return invalid_date();
    }
    if (clockTime->error) {
        return invalid_clock_time();
    }

    /* First, the hard part... determining the number of days since the UNIX
       epoch, taking leap years into account */
    int_timestamp year = Date_get_year(date),
                  month = Date_get_month(date),
                  daysSinceEpoch = Date_get_day(date);
    daysSinceEpoch += DAY_OF_START_OF_MONTH[month];
    daysSinceEpoch += 365 * (year - 1970);
    /* Every 4 years is a leap year */
    daysSinceEpoch += (year - 1968) / 4;
    /* Except the turn of the century */
    daysSinceEpoch -= (year - 1900) / 100;
    /* Except every 4th century */
    daysSinceEpoch += (year - 1600) / 400;
    /* If it's still January or February of this year, though, we don't need to
       include the extra for this year yet */
    if (IS_LEAP_YEAR(year) && month <= 2) {
        daysSinceEpoch--;
    }

    /* This is a more useful form of the clock time */
    struct TimeDelta timeSinceMidnight =
        ClockTime_time_since_midnight(clockTime);

    return new_timestamp(
            daysSinceEpoch * SECONDS_IN_DAY +
            TimeDelta_get_seconds(&timeSinceMidnight),
            TimeDelta_get_nanoseconds(&timeSinceMidnight));
}

struct Timestamp
Timestamp_create_local(
        const struct Date * const date,
        const struct ClockTime * const clockTime) {
    assert(date != NULL);
    assert(date->error == 0);
    assert(clockTime != NULL);
    assert(clockTime->error == 0);

    /* Make sure the Date and ClockTime aren't erroneous */
    if (date->error) {
        return invalid_date();
    }
    if (clockTime->error) {
        return invalid_clock_time();
    }

    return Timestamp_from_struct_tm_local(
            convert_to_struct_tm(date, clockTime));
}

struct Timestamp
Timestamp_now() {
    struct present_now_struct now = present_now();
    return new_timestamp(time_t_to_timestamp(now.sec), now.nsec);
}

struct Timestamp
Timestamp_epoch() {
    return new_timestamp(0, 0);
}

time_t
Timestamp_get_time_t(const struct Timestamp * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return timestamp_to_time_t(self->data_.timestamp_seconds);
}

struct tm
Timestamp_get_struct_tm(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(timeZoneOffset != NULL);
    assert(timeZoneOffset->error == 0);

    struct Timestamp copy = *self;
    /* TODO: should we be adding or subtracting? */
    Timestamp_add_time_delta(&copy, timeZoneOffset);
    return Timestamp_get_struct_tm_utc(&copy);
}

struct tm
Timestamp_get_struct_tm_utc(const struct Timestamp * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    time_t timestamp = timestamp_to_time_t(self->data_.timestamp_seconds);
    struct tm result;
    present_gmtime(&timestamp, &result);
    return result;
}

struct tm
Timestamp_get_struct_tm_local(const struct Timestamp * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    time_t timestamp = timestamp_to_time_t(self->data_.timestamp_seconds);
    struct tm result;
    present_localtime(&timestamp, &result);
    return result;
}

struct Date
Timestamp_get_date(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(timeZoneOffset != NULL);
    assert(timeZoneOffset->error == 0);

    return struct_tm_to_date(Timestamp_get_struct_tm(self, timeZoneOffset));
}

struct Date
Timestamp_get_date_utc(const struct Timestamp * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return struct_tm_to_date(Timestamp_get_struct_tm_utc(self));
}

struct Date
Timestamp_get_date_local(const struct Timestamp * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return struct_tm_to_date(Timestamp_get_struct_tm_local(self));
}

struct ClockTime
Timestamp_get_clock_time(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset) {
    assert(self != NULL);
    assert(self->error == 0);

    return struct_tm_to_clock_time(
            Timestamp_get_struct_tm(self, timeZoneOffset));
}

struct ClockTime
Timestamp_get_clock_time_utc(const struct Timestamp * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return struct_tm_to_clock_time(Timestamp_get_struct_tm_utc(self));
}

struct ClockTime
Timestamp_get_clock_time_local(const struct Timestamp * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return struct_tm_to_clock_time(Timestamp_get_struct_tm_local(self));
}

struct TimeDelta
Timestamp_get_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(other != NULL);
    assert(other->error == 0);

    struct TimeDelta delta = TimeDelta_from_seconds(
            self->data_.timestamp_seconds - other->data_.timestamp_seconds);
    struct TimeDelta nsDelta = TimeDelta_from_nanoseconds(
            self->data_.additional_nanoseconds -
            other->data_.additional_nanoseconds);
    TimeDelta_add_time_delta(&delta, &nsDelta);
    return delta;
}

struct TimeDelta
Timestamp_get_absolute_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(other != NULL);
    assert(other->error == 0);

    struct TimeDelta delta = Timestamp_get_difference(self, other);
    if (TimeDelta_is_negative(&delta)) {
        TimeDelta_negate(&delta);
    }
    return delta;
}

void
Timestamp_add_time_delta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.timestamp_seconds += delta->data_.delta_seconds;
    self->data_.additional_nanoseconds += delta->data_.delta_nanoseconds;
    CHECK_DATA(self->data_)
}

void
Timestamp_add_day_delta(
        struct Timestamp * const self,
        const struct DayDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.timestamp_seconds += delta->data_.delta_days * SECONDS_IN_DAY;
}

void
Timestamp_add_month_delta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    time_t timestamp = timestamp_to_time_t(self->data_.timestamp_seconds);
    struct tm tm;
    present_localtime(&timestamp, &tm);
    tm.tm_mon += delta->data_.delta_months;
    self->data_.timestamp_seconds = present_mktime(&tm);
    assert(self->data_.timestamp_seconds != -1);
}

void
Timestamp_subtract_time_delta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.timestamp_seconds -= delta->data_.delta_seconds;
    self->data_.additional_nanoseconds -= delta->data_.delta_nanoseconds;
    CHECK_DATA(self->data_)
}

void
Timestamp_subtract_day_delta(
        struct Timestamp * const self,
        const struct DayDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    self->data_.timestamp_seconds -= delta->data_.delta_days * SECONDS_IN_DAY;
}

void
Timestamp_subtract_month_delta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta) {
    assert(self != NULL);
    assert(self->error == 0);
    assert(delta != NULL);
    assert(delta->error == 0);

    time_t timestamp = timestamp_to_time_t(self->data_.timestamp_seconds);
    struct tm tm;
    present_localtime(&timestamp, &tm);
    tm.tm_mon -= delta->data_.delta_months;
    self->data_.timestamp_seconds = present_mktime(&tm);
    assert(self->data_.timestamp_seconds != -1);
}

int
Timestamp_compare(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs) {
    assert(lhs != NULL);
    assert(lhs->error == 0);
    assert(rhs != NULL);
    assert(rhs->error == 0);

    return
        STRUCT_COMPARE(timestamp_seconds,
            STRUCT_COMPARE(additional_nanoseconds, 0));
}

STRUCT_COMPARISON_OPERATORS(Timestamp)

