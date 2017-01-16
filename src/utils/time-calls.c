/*
 * Present - Date/Time Library
 *
 * Implementation of wrappers around date/time syscalls and standard library
 * functions
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

#ifdef PRESENT_USE_PTHREAD
# include <pthread.h>
#endif

#include "utils/time-calls.h"

#ifdef PRESENT_USE_PTHREAD
static pthread_mutex_t syscall_access;
static int is_initialized = 0;

#define INITIALIZE                          \
    do {                                    \
        if (!is_initialized) {              \
            pthread_mutex_init(             \
                    &syscall_access, NULL); \
            is_initialized = 1;             \
        }                                   \
        pthread_mutex_lock(                 \
                &syscall_access);           \
    } while (0)

#define DONE                                \
    do {                                    \
        pthread_mutex_unlock(               \
                &syscall_access);           \
    } while (0)

#else

#define INITIALIZE
#define DONE

#endif

static int present_is_test_time_set = 0;
static struct PresentNowStruct present_test_time;

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

void
present_gmtime(const time_t * timep, struct tm * result)
{
    struct tm * value;

    INITIALIZE;
    value = gmtime(timep);
    memcpy(result, value, sizeof(struct tm));
    DONE;
}

void
present_localtime(const time_t * timep, struct tm * result)
{
    struct tm * value;

    INITIALIZE;
    value = localtime(timep);
    memcpy(result, value, sizeof(struct tm));
    DONE;
}

time_t
present_mktime(struct tm * tm)
{
    time_t value;

    INITIALIZE;
    value = mktime(tm);
    DONE;
    return value;
}

void
present_now(struct PresentNowStruct * result)
{
    assert(result != NULL);
#if defined(_POSIX_TIMERS) && !defined(__STRICT_ANSI__)
    struct timespec tp;
#endif

    INITIALIZE;
    if (present_is_test_time_set) {
        *result = present_test_time;
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
    DONE;
}

void
present_set_test_time(struct PresentNowStruct value)
{
    INITIALIZE;
    present_is_test_time_set = 1;
    present_test_time = value;
    DONE;
}

void
present_reset_test_time()
{
    INITIALIZE;
    present_is_test_time_set = 0;
    DONE;
}

