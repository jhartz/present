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

#include "impl-constants.h"
#include "impl-utils.h"

#include "present/clock-time.h"
#include "present/date.h"
#include "present/day-delta.h"
#include "present/month-delta.h"
#include "present/time-delta.h"

#include "present/timestamp.h"

/**
 * Determine whether a given year is a leap year.
 */
#define IS_LEAP_YEAR(year)                      \
    ((year % 4 == 0 && year % 100 != 0) ||      \
     (year % 400 == 0))

/**
 * Day of the year that each month starts on (in non-leap years).
 */
static const int_day_of_year DAY_OF_START_OF_MONTH[13] = {
    0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};

// Internal struct used to hold both a Date and a ClockTime
struct DateAndClockTime {
    struct Date date;
    struct ClockTime clockTime;
};

/**
 * Convert a struct tm to a Date and ClockTime.
 */
static struct DateAndClockTime
convertFromStructTm(const struct tm tm) {
    struct tm tmCopy = tm;
    // Throw it through mktime to fix any weirdness
    assert(mktime(&tmCopy) != -1);

    struct DateAndClockTime ret = {
        Date_create_from_year_month_day(
                tmCopy.tm_year + STRUCT_TM_YEAR_OFFSET,
                tmCopy.tm_mon + STRUCT_TM_MONTH_OFFSET,
                tmCopy.tm_mday),
        ClockTime_create_from_hour_minute_second(
                tmCopy.tm_hour,
                tmCopy.tm_min,
                tmCopy.tm_sec)
    };
    return ret;
}

/**
 * Convert a Date and ClockTime to a struct tm.
 */
static struct tm
convertToStructTm(
        const struct Date * const date,
        const struct ClockTime * const clockTime) {
    struct tm tm;
    memset((void *)&tm, 0, sizeof(struct tm));

    tm.tm_sec = (int) ClockTime_get_second(clockTime);
    tm.tm_min = (int) ClockTime_get_minute(clockTime);
    tm.tm_hour = (int) ClockTime_get_hour(clockTime);
    tm.tm_mday = (int) Date_get_day(date);
    tm.tm_mon = (int) Date_get_month(date) - STRUCT_TM_MONTH_OFFSET;
    tm.tm_year = (int) Date_get_year(date) - STRUCT_TM_YEAR_OFFSET;
    tm.tm_isdst = -1;
    assert(mktime(&tm) != -1);

    return tm;
}

/**
 * Create a new Timestamp instance based on its data parameters.
 */
static struct Timestamp
newTimestamp(int_timestamp timestamp, int_nanosecond nanoseconds) {
    CONSTRUCTOR_HEAD(Timestamp);
    struct PresentTimestampData data;
    data.timestamp = timestamp;
    data.nanoseconds = nanoseconds;
    CONSTRUCTOR_RETURN(Timestamp, data);
}

/**
 * Create a Timestamp with an "invalid ClockTime" error.
 */
static struct Timestamp
invalidClockTime() {
    CONSTRUCTOR_HEAD(Timestamp);
    CONSTRUCTOR_ERROR_RETURN(Timestamp, INVALID_CLOCK_TIME);
}

/**
 * Create a Timestamp with an "invalid Date" error.
 */
static struct Timestamp
invalidDate() {
    CONSTRUCTOR_HEAD(Timestamp);
    CONSTRUCTOR_ERROR_RETURN(Timestamp, INVALID_DATE);
}

struct Timestamp
Timestamp_create_from_time_t(const time_t timestamp) {
    // Assuming that time_t is a UNIX timestamp
    return newTimestamp((int_timestamp) timestamp, 0);
}

struct Timestamp
Timestamp_create_from_struct_tm(
        const struct tm tm,
        const struct TimeDelta * const timeZoneOffset) {
    struct DateAndClockTime ret = convertFromStructTm(tm);
    return Timestamp_create(&ret.date, &ret.clockTime, timeZoneOffset);
}

struct Timestamp
Timestamp_create_from_struct_tm_utc(const struct tm tm) {
    struct DateAndClockTime ret = convertFromStructTm(tm);
    return Timestamp_create_utc(&ret.date, &ret.clockTime);
}

struct Timestamp
Timestamp_create_from_struct_tm_local(const struct tm tm) {
    struct tm tmCopy = tm;
    // Throw it right through mktime
    time_t timestamp = mktime(&tmCopy);
    assert(timestamp != -1);
    return Timestamp_create_from_time_t(timestamp);
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

    // Make sure the Date and ClockTime aren't erroneous
    if (date->error) {
        return invalidDate();
    }
    if (clockTime->error) {
        return invalidClockTime();
    }

    // First, pretend it's just UTC
    struct Timestamp t = Timestamp_create_utc(date, clockTime);
    // Now, subtract the UTC offset (since we're technically converting TO UTC)
    // TODO: Is subtracting correct?
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

    // Make sure the Date and ClockTime aren't erroneous
    if (date->error) {
        return invalidDate();
    }
    if (clockTime->error) {
        return invalidClockTime();
    }

    // First, the hard part... determining the number of days since
    // the UNIX epoch, taking leap years into account
    int_timestamp year = Date_get_year(date),
                  month = Date_get_month(date),
                  daysSinceEpoch = Date_get_day(date);
    daysSinceEpoch += DAY_OF_START_OF_MONTH[month];
    daysSinceEpoch += 365 * (year - 1970);
    // Every 4 years is a leap year
    daysSinceEpoch += (year - 1968) / 4;
    // Except the turn of the century
    daysSinceEpoch -= (year - 1900) / 100;
    // Except every 4th century
    daysSinceEpoch += (year - 1600) / 400;
    // If it's still January or February of this year, though, we don't need to
    // include the extra for this year yet
    if (IS_LEAP_YEAR(year) && month <= 2) {
        daysSinceEpoch--;
    }

    // This is a more useful form of the clock time
    struct TimeDelta timeSinceMidnight =
        ClockTime_time_since_midnight(clockTime);

    return newTimestamp(
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

    // Make sure the Date and ClockTime aren't erroneous
    if (date->error) {
        return invalidDate();
    }
    if (clockTime->error) {
        return invalidClockTime();
    }

    return Timestamp_create_from_struct_tm_local(
            convertToStructTm(date, clockTime));
}

struct Timestamp
Timestamp_now() {
    return Timestamp_create_from_time_t(time(NULL));
}

struct Timestamp
Timestamp_epoch() {
    return Timestamp_create_from_time_t((time_t) 0);
}

time_t
Timestamp_get_time_t(const struct Timestamp * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return (time_t) self->data_.timestamp;
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
    // TODO: should we be adding or subtracting?
    Timestamp_add_time_delta(&copy, timeZoneOffset);
    return Timestamp_get_struct_tm_utc(&copy);
}

struct tm
Timestamp_get_struct_tm_utc(const struct Timestamp * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return *gmtime((time_t *) &self->data_.timestamp);
}

struct tm
Timestamp_get_struct_tm_local(const struct Timestamp * const self) {
    assert(self != NULL);
    assert(self->error == 0);

    return *localtime((time_t *) &self->data_.timestamp);
}

struct Date
Timestamp_get_date(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset) {

}

struct Date
Timestamp_get_date_utc(const struct Timestamp * const self) {

}

struct Date
Timestamp_get_date_local(const struct Timestamp * const self) {

}

struct ClockTime
Timestamp_get_clock_time(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset) {

}

struct ClockTime
Timestamp_get_clock_time_utc(const struct Timestamp * const self) {

}

struct ClockTime
Timestamp_get_clock_time_local(const struct Timestamp * const self) {

}

struct TimeDelta
Timestamp_get_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other) {

}

struct TimeDelta
Timestamp_get_absolute_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other) {

}

void
Timestamp_add_time_delta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta) {

}

void
Timestamp_add_day_delta(
        struct Timestamp * const self,
        const struct DayDelta * const delta) {

}

void
Timestamp_add_month_delta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta) {

}

void
Timestamp_subtract_time_delta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta) {

}

void
Timestamp_subtract_day_delta(
        struct Timestamp * const self,
        const struct DayDelta * const delta) {

}

void
Timestamp_subtract_month_delta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta) {

}

STRUCT_COMPARISON_OPERATORS(Timestamp, timestamp, nanoseconds)

