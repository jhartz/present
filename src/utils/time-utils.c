/*
 * Present - Date/Time Library
 *
 * Implementations of utility functions for dealing with dates and times
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "present-config.h"

#ifdef PRESENT_WRAP_STDLIB_CALLS
# include <pthread.h>
#endif

#include "utils/constants.h"
#include "utils/impl-utils.h"

#include "utils/time-utils.h"

#ifdef PRESENT_WRAP_STDLIB_CALLS
static pthread_mutex_t stdlib_call_lock = PTHREAD_MUTEX_INITIALIZER;

#define LOCK()                                  \
    do {                                        \
        pthread_mutex_lock(&stdlib_call_lock);  \
    } while (0)

#define UNLOCK()                                    \
    do {                                            \
        pthread_mutex_unlock(&stdlib_call_lock);    \
    } while (0)

#else

#define LOCK()
#define UNLOCK()

#endif

static int is_test_time_set = 0;
static struct PresentNowStruct test_time;

/**
 * Calculate the number of days that have occurred since the very beginning
 * (January 1st) of a base year.
 *
 * Precondition: The base year MUST be divisible by 400.
 */
static int_timestamp
days_since_base_year(
        const int_year base_year,
        int_year year,
        int_month month,
        int_day day)
{
    /** Day of the year that each month starts on (in non-leap years). */
    static const int_day_of_year DAY_OF_START_OF_MONTH[13] = {
        0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };

    int_timestamp offset_year;
    int_timestamp days_since_base;

    /* Fix irregularities in the month
       (we don't really care about irregularities in the day, since our final
       result is a number of days) */
    while (month <= 0) {
        month += 12;
        year -= 1;
    }
    if (month > 12) {
        year += (month - 1) / 12;
        month = (month - 1) % 12 + 1;
    }

    offset_year = year - base_year;

    /* Start conversion to number of days since base */
    days_since_base = day - 1;

    days_since_base += DAY_OF_START_OF_MONTH[month];
    days_since_base += 365 * offset_year;

    /* Every 4 years is a leap year */
    days_since_base += offset_year / 4;
    /* Except the turn of the century */
    days_since_base -= offset_year / 100;
    /* Except every 4th century */
    days_since_base += offset_year / 400;

    /* If it's still January or February of this year, though, we don't need
       to include the extra for this year yet */
    if (IS_LEAP_YEAR(year) && month <= 2) {
        days_since_base--;
    }

    /* This fix (i.e. hack) ensures compatibility with timegm behavior */
    if (offset_year < 0 && !IS_LEAP_YEAR(year)) {
        days_since_base--;
    }

    return days_since_base;
}

double
present_round(double x)
{
    double t;

    if (x >= 0.0) {
        t = floor(x);
        if (x - t >= 0.5) {
            t += 1.0;
        }
        return t;
    } else {
        t = floor(-x);
        if ((-x) - t >= 0.5) {
            t += 1.0;
        }
        return -t;
    }
}

/** Convert a time_t to a UNIX timestamp. */
int_timestamp
time_t_to_unix_timestamp(const time_t timestamp)
{
    /* TODO: We're just assuming that time_t is already a UNIX timestamp */
    return (int_timestamp) timestamp;
}

/** Convert a UNIX timestamp to a time_t. */
time_t
unix_timestamp_to_time_t(const int_timestamp timestamp_seconds)
{
    /* TODO: We're just assuming that time_t is a UNIX timestamp */
    return (time_t) timestamp_seconds;
}

int_timestamp
to_unix_timestamp(
        int_year year,
        int_month month,
        int_day day,
        int_hour hour,
        int_minute minute,
        int_second second)
{
    /* 1600 is the easiest base year that's divisible by 400 */
    static const int_year BASE_YEAR = 1600;
    const int_timestamp EPOCH_DAYS_SINCE_BASE_YEAR =
        days_since_base_year(
                BASE_YEAR,
                UNIX_EPOCH_YEAR,
                UNIX_EPOCH_MONTH,
                UNIX_EPOCH_DAY);

    int_timestamp days_since_epoch;
    
    days_since_epoch = days_since_base_year(BASE_YEAR, year, month, day) -
        EPOCH_DAYS_SINCE_BASE_YEAR;

    return days_since_epoch * SECONDS_IN_DAY
        + hour * SECONDS_IN_HOUR
        + minute * SECONDS_IN_MINUTE
        + second;
}

void
time_t_to_struct_tm(const time_t * timep, struct tm * result)
{
    struct tm * value;

    LOCK();
    value = gmtime(timep);
    assert(value != NULL);
    memcpy(result, value, sizeof(struct tm));
    UNLOCK();
}

time_t
struct_tm_to_time_t_local(struct tm * tm)
{
    time_t value;

    LOCK();
    value = mktime(tm);
    assert(value != (time_t) -1);
    UNLOCK();
    return value;
}

void
time_t_to_struct_tm_local(const time_t * timep, struct tm * result)
{
    struct tm * value;

    LOCK();
    value = localtime(timep);
    assert(value != NULL);
    memcpy(result, value, sizeof(struct tm));
    UNLOCK();
}

void
clean_struct_tm(struct tm * const tm)
{
    time_t time;

    time = unix_timestamp_to_time_t(to_unix_timestamp(
            tm->tm_year + STRUCT_TM_YEAR_OFFSET,
            tm->tm_mon + STRUCT_TM_MONTH_OFFSET,
            tm->tm_mday,
            tm->tm_hour,
            tm->tm_min,
            tm->tm_sec));
    time_t_to_struct_tm(&time, tm);
}

void
present_now(struct PresentNowStruct * result)
{
    assert(result != NULL);
#if defined(_POSIX_TIMERS) && !defined(__STRICT_ANSI__)
    struct timespec tp;
#endif

    LOCK();
    if (is_test_time_set) {
        *result = test_time;
    } else {
#if defined(_POSIX_TIMERS) && !defined(__STRICT_ANSI__)
        clock_gettime(CLOCK_REALTIME, &tp);
        result->sec = tp.tv_sec;
        result->nsec = tp.tv_nsec;
#else
        result->sec = time(NULL);
        result->nsec = 0;
#endif
    }
    UNLOCK();
}

void
present_set_test_time(struct PresentNowStruct value)
{
    LOCK();
    is_test_time_set = 1;
    test_time = value;
    UNLOCK();
}

void
present_reset_test_time()
{
    LOCK();
    is_test_time_set = 0;
    UNLOCK();
}

