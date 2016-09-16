/*
 * Present - Date/Time Library
 *
 * Headers for wrappers around date/time syscalls and standard library
 * functions
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <time.h>

#ifndef _PRESENT_SYSCALLS_H_
#define _PRESENT_SYSCALLS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Return value for present_now. Identical to "struct timespec" on systems
 * that support it.
 */
struct PresentNowStruct {
    time_t  sec;    /* seconds since the epoch */
    long    nsec;   /* nanoseconds after sec */
};

/**
 * Reimplementation of round to support older versions of the math library
 * that don't have round.
 */
double present_round(double x);

/**
 * Wrapper around gmtime.
 *
 * Converts UNIX timestamp @p timep to a "struct tm" (in UTC) and stores the
 * result in @p result.
 */
void present_gmtime(const time_t * timep, struct tm * result);

/**
 * Wrapper around localtime.
 *
 * Converts UNIX timestamp @p timep to a "struct tm" (in local time) and
 * stores the result in @p result.
 */
void present_localtime(const time_t * timep, struct tm * result);

/**
 * Wrapper around mktime.
 *
 * Converts struct tm @p tm (in local time) to a UNIX timestamp.
 */
time_t present_mktime(struct tm * tm);

/**
 * Get the current system time.
 *
 * If a test time is set, this will return that. Otherwise, it is a wrapper
 * around clock_gettime (if supported) or time.
 */
struct PresentNowStruct present_now();

/**
 * Set a test time that will be returned by calls to present_now.
 */
void present_set_test_time(struct PresentNowStruct value);

/**
 * Reset a test time set previously by present_set_test_time.
 *
 * After calling this, present_now will resume returning the actual current
 * time.
 */
void present_reset_test_time();

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_SYSCALLS_H_ */
