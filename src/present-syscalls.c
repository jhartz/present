/*
 * Present - Date/Time Library
 *
 * Implementation of wrappers around date/time syscalls and standard library
 * functions
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <stddef.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "present-config.h"

#ifdef PRESENT_USE_PTHREAD
# include <pthread.h>
#endif

#include "present-syscalls.h"

#ifdef PRESENT_USE_PTHREAD
static pthread_mutex_t syscall_access;
int is_initialized = 0;

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
static struct present_now_struct present_test_time;

void present_gmtime(const time_t * timep, struct tm * result) {
    struct tm * value;

    INITIALIZE;
    value = gmtime(timep);
    memcpy(result, value, sizeof(struct tm));
    DONE;
}

void present_localtime(const time_t * timep, struct tm * result) {
    struct tm * value;

    INITIALIZE;
    value = localtime(timep);
    memcpy(result, value, sizeof(struct tm));
    DONE;
}

time_t present_mktime(struct tm * tm) {
    time_t value;

    INITIALIZE;
    value = mktime(tm);
    DONE;
    return value;
}

struct present_now_struct present_now() {
    struct present_now_struct value;
#ifdef _POSIX_TIMERS
    struct timespec tp;
#endif

    INITIALIZE;
    if (present_is_test_time_set) {
        value = present_test_time;
    } else {
#ifdef _POSIX_TIMERS
        clock_gettime(CLOCK_REALTIME, &tp);
        value.sec = tp.tv_sec;
        value.nsec = tp.tv_nsec;
#else
        value.sec = time(NULL);
        value.nsec = 0;
#endif
    }
    DONE;
    return value;
}

void present_set_test_time(struct present_now_struct value) {
    INITIALIZE;
    present_is_test_time_set = 1;
    present_test_time = value;
    DONE;
}

void present_reset_test_time() {
    INITIALIZE;
    present_is_test_time_set = 0;
    DONE;
}

