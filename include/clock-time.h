/*
 * Present - Date/Time Library
 *
 * Definition of the ClockTime structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present-utils/types.h"
#include "present-utils/utils.h"
#include "present-impl/clock-time-data.h"

#ifndef _PRESENT_CLOCK_TIME_H_
#define _PRESENT_CLOCK_TIME_H_

/*
 * Forward Declarations
 */

struct TimeDelta;

/*
 * C++ Class / C Struct Definition
 */

struct ClockTime {
#ifdef __cplusplus
    static ClockTime create(int_hour hour);

    static ClockTime create(int_hour hour, int_minute minute);

    static ClockTime create(int_hour hour, int_minute minute, int_second second);

    static ClockTime create(int_hour hour, int_minute minute, int_second second, int_nanosecond nanosecond);

    static ClockTime create(int_hour hour, int_minute minute, double second);

    static ClockTime midnight();

    static ClockTime noon();

    static ClockTime now();

    int_hour get_hour() const;

    int_minute get_minute() const;

    int_second get_second() const;

    int_nanosecond get_nanosecond() const;

    double get_second_decimal() const;

    ClockTime & operator+=(const TimeDelta &);
    ClockTime & operator-=(const TimeDelta &);

    friend const ClockTime operator+(const ClockTime &, const TimeDelta &);
    friend const ClockTime operator-(const ClockTime &, const TimeDelta &);

    friend bool operator==(const ClockTime &, const ClockTime &);
    friend bool operator!=(const ClockTime &, const ClockTime &);

    friend bool operator<(const ClockTime &, const ClockTime &);
    friend bool operator<=(const ClockTime &, const ClockTime &);
    friend bool operator>(const ClockTime &, const ClockTime &);
    friend bool operator>=(const ClockTime &, const ClockTime &);

    ClockTime(const ClockTime &);
    ClockTime & operator=(const ClockTime &);

private:
    ClockTime();
#endif

    struct ClockTimeData my_data;
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

struct ClockTime
ClockTime_create_from_hour(int_hour hour);

struct ClockTime
ClockTime_create_from_hour_minute(int_hour hour, int_minute minute);

struct ClockTime
ClockTime_create_from_hour_minute_second(int_hour hour, int_minute minute, int_second second);

struct ClockTime
ClockTime_create_from_hour_minute_second_nanosecond(int_hour hour, int_minute minute, int_second second, int_nanosecond nanosecond);

#define ClockTime_create(...)    \
    OVERLOAD_MAX_4(__VA_ARGS__, \
        ClockTime_create_from_hour_minute_second_nanosecond,    \
        ClockTime_create_from_hour_minute_second,   \
        ClockTime_create_from_hour_minute,  \
        ClockTime_create_from_hour)(__VA_ARGS__)

struct ClockTime
ClockTime_create_with_decimal_seconds(int_hour hour, int_minute minute, double second);

struct ClockTime
ClockTime_midnight();

struct ClockTime
ClockTime_noon();

struct ClockTime
ClockTime_now();

int_hour
ClockTime_get_hour(const struct ClockTime * const self);

int_minute
ClockTime_get_minute(const struct ClockTime * const self);

int_second
ClockTime_get_second(const struct ClockTime * const self);

int_nanosecond
ClockTime_get_nanosecond(const struct ClockTime * const self);

double
ClockTime_get_second_decimal(const struct ClockTime * const self);

void
ClockTime_add_time_delta(struct ClockTime * const self, struct TimeDelta * const delta);

void
ClockTime_subtract_time_delta(struct ClockTime * const self, struct TimeDelta * const delta);

bool
ClockTime_equal(const struct ClockTime * const, const struct ClockTime * const);

bool
ClockTime_less_than(const struct ClockTime * const, const struct ClockTime * const);

bool
ClockTime_less_than_or_equal(const struct ClockTime * const, const struct ClockTime * const);

bool
ClockTime_greater_than(const struct ClockTime * const, const struct ClockTime * const);

bool
ClockTime_greater_than_or_equal(const struct ClockTime * const, const struct ClockTime * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_CLOCK_TIME_H_ */

