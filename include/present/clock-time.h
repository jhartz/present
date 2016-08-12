/*
 * Present - Date/Time Library
 *
 * Definition of the ClockTime structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-clock-time-data.h"

#ifndef _PRESENT_CLOCK_TIME_H_
#define _PRESENT_CLOCK_TIME_H_

/*
 * Forward Declarations
 */

struct TimeDelta;

/*
 * C++ Class / C Struct Definition
 */

/**
 * Class or struct representing a time as seen on a clock.
 *
 * This includes hours, minutes, and seconds (up to nanosecond precision).
 * There is no date information stored with the time, nor a time zone (so a
 * ClockTime instance is NOT tied to a specific time zone).
 */
struct PRESENT_API ClockTime {
    enum {
        ClockTime_ERROR_NONE = 0;
        ClockTime_ERROR_HOUR_OUT_OF_RANGE;
        ClockTime_ERROR_MINUTE_OUT_OF_RANGE;
        ClockTime_ERROR_SECOND_OUT_OF_RANGE;
        ClockTime_ERROR_NANOSECOND_OUT_OF_RANGE;
    } error;
    struct PresentClockTimeData data_;

#ifdef __cplusplus
    static ClockTime create(int_hour hour);

    static ClockTime create(int_hour hour, int_minute minute);

    static ClockTime create(
        int_hour hour,
        int_minute minute,
        int_second second);

    static ClockTime create(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond);

    static ClockTime create(int_hour hour, int_minute minute, double second);

    static ClockTime midnight();

    static ClockTime noon();

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

    PRESENT_BOILERPLATE_CONSTRUCTORS(ClockTime)
#endif
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

PRESENT_API struct ClockTime
ClockTime_create_from_hour(int_hour hour);

PRESENT_API struct ClockTime
ClockTime_create_from_hour_minute(int_hour hour, int_minute minute);

PRESENT_API struct ClockTime
ClockTime_create_from_hour_minute_second(
        int_hour hour,
        int_minute minute,
        int_second second);

PRESENT_API struct ClockTime
ClockTime_create_from_hour_minute_second_nanosecond(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond);

#define ClockTime_create(...)    \
    PRESENT_OVERLOAD_MAX_4(__VA_ARGS__, \
        ClockTime_create_from_hour_minute_second_nanosecond,    \
        ClockTime_create_from_hour_minute_second,   \
        ClockTime_create_from_hour_minute,  \
        ClockTime_create_from_hour)(__VA_ARGS__)

PRESENT_API struct ClockTime
ClockTime_create_with_decimal_seconds(
        int_hour hour,
        int_minute minute,
        double second);

PRESENT_API struct ClockTime
ClockTime_midnight();

PRESENT_API struct ClockTime
ClockTime_noon();

PRESENT_API int_hour
ClockTime_get_hour(const struct ClockTime * const self);

PRESENT_API int_minute
ClockTime_get_minute(const struct ClockTime * const self);

PRESENT_API int_second
ClockTime_get_second(const struct ClockTime * const self);

PRESENT_API int_nanosecond
ClockTime_get_nanosecond(const struct ClockTime * const self);

PRESENT_API double
ClockTime_get_second_decimal(const struct ClockTime * const self);

PRESENT_API void
ClockTime_add_time_delta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta);

PRESENT_API void
ClockTime_subtract_time_delta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta);

PRESENT_API bool
ClockTime_equal(const struct ClockTime * const, const struct ClockTime * const);

PRESENT_API bool
ClockTime_less_than(
        const struct ClockTime * const,
        const struct ClockTime * const);

PRESENT_API bool
ClockTime_less_than_or_equal(
        const struct ClockTime * const,
        const struct ClockTime * const);

PRESENT_API bool
ClockTime_greater_than(
        const struct ClockTime * const,
        const struct ClockTime * const);

PRESENT_API bool
ClockTime_greater_than_or_equal(
        const struct ClockTime * const,
        const struct ClockTime * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_CLOCK_TIME_H_ */

