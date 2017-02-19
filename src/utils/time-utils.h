/*
 * Present - Date/Time Library
 *
 * Declarations of utility functions for dealing with dates and times
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <time.h>

#include "present/internal/types.h"

#ifndef _PRESENT_TIME_UTILS_H_
#define _PRESENT_TIME_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct used for @p present_now. Identical to "struct timespec" on systems
 * that support it.
 */
struct PresentNowStruct {
    time_t  sec;    /* seconds since the epoch */
    long    nsec;   /* nanoseconds after sec */
};

/**
 * Reimplementation of @p round to support older versions of the math library
 * that don't have @p round.
 */
double
present_round(double x);

/** Convert a time_t to a UNIX timestamp. */
int_timestamp
time_t_to_unix_timestamp(const time_t timestamp);

/** Convert a UNIX timestamp to a time_t. */
time_t
unix_timestamp_to_time_t(const int_timestamp timestamp_seconds);

/**
 * Convert an instant in time to the number of seconds since the UNIX epoch
 * that represents that timestamp (in UTC).
 *
 * This is essentially a reimplementation of the nonstandard C @p timegm
 * function.
 */
int_timestamp
to_unix_timestamp(
        int_year year,
        int_month month,
        int_day day,
        int_hour hour,
        int_minute minute,
        int_second second);

/**
 * Convert a UNIX timestamp @p timep to a "struct tm" (in UTC) and store the
 * result in @p result.
 *
 * This is a wrapper around the @p gmtime function in the C standard library.
 *
 * If Present is not compiled with PRESENT_WRAP_STDLIB_CALLS, then this
 * function is not thread-safe.
 */
void
time_t_to_struct_tm(const time_t * timep, struct tm * result);

/**
 * Convert a struct tm @p tm (in local time) to a UNIX timestamp.
 *
 * This is a wrapper around the @p mktime function in the C standard library.
 * Prefer using @p to_unix_timestamp if possible.
 *
 * If Present is not compiled with PRESENT_WRAP_STDLIB_CALLS, then this
 * function is not thread-safe.
 */
time_t
struct_tm_to_time_t_local(struct tm * tm);

/**
 * Convert a UNIX timestamp @p timep to a "struct tm" (in local time) and store
 * the result in @p result.
 *
 * This is a wrapper around the @p localtime function in the C standard
 * library.
 *
 * If Present is not compiled with PRESENT_WRAP_STDLIB_CALLS, then this
 * function is not thread-safe.
 */
void
time_t_to_struct_tm_local(const time_t * timep, struct tm * result);

/**
 * Clean a struct tm, fixing any issues with date or time components that are
 * out of range.
 */
void
clean_struct_tm(struct tm * const tm);

/**
 * Get the current system time.
 *
 * If a test time is set, this will return that. Otherwise, it is a wrapper
 * around the @p clock_gettime function (if supported) or the @p time function
 * from the C standard library.
 *
 * @see present_set_test_time
 */
void
present_now(struct PresentNowStruct * result);

/**
 * Set a test time that will be returned by calls to @p present_now.
 *
 * @see present_now
 * @see present_reset_test_time
 */
void
present_set_test_time(struct PresentNowStruct value);

/**
 * Reset a test time set previously by @p present_set_test_time.
 *
 * After calling this, @p present_now will resume returning the actual current
 * time.
 *
 * @see present_now
 * @see present_set_test_time
 */
void
present_reset_test_time();

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_TIME_UTILS_H_ */

