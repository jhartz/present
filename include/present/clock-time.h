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
 * Enum Definitions
 */

enum PresentClockTimeError {
    ClockTime_ERROR_NONE = 0
    , ClockTime_ERROR_HOUR_OUT_OF_RANGE
    , ClockTime_ERROR_MINUTE_OUT_OF_RANGE
    , ClockTime_ERROR_SECOND_OUT_OF_RANGE
    , ClockTime_ERROR_NANOSECOND_OUT_OF_RANGE
};

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
    enum PresentClockTimeError error;
    struct PresentClockTimeData data_;

#ifdef __cplusplus
    /** @see ClockTime_create_from_hour */
    static ClockTime create(int_hour hour);

    /** @see ClockTime_create_from_hour_minute */
    static ClockTime create(int_hour hour, int_minute minute);

    /** @see ClockTime_create_from_hour_minute_second */
    static ClockTime create(
        int_hour hour,
        int_minute minute,
        int_second second);

    /** @see ClockTime_create_from_hour_minute_second_nanosecond */
    static ClockTime create(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond);

    /** @see ClockTime_create_with_decimal_seconds */
    static ClockTime create(int_hour hour, int_minute minute, double second);

    /** @see ClockTime_midnight */
    static ClockTime midnight();

    /** @see ClockTime_noon */
    static ClockTime noon();

    /** @see ClockTime_get_hour */
    int_hour get_hour() const;

    /** @see ClockTime_get_minute */
    int_minute get_minute() const;

    /** @see ClockTime_get_second */
    int_second get_second() const;

    /** @see ClockTime_get_nanosecond */
    int_nanosecond get_nanosecond() const;

    /** @see ClockTime_get_second_decimal */
    double get_second_decimal() const;

    /** @see ClockTime_add_time_delta */
    ClockTime & operator+=(const TimeDelta &);
    /** @see ClockTime_subtract_time_delta */
    ClockTime & operator-=(const TimeDelta &);

    friend const ClockTime operator+(const ClockTime &, const TimeDelta &);
    friend const ClockTime operator-(const ClockTime &, const TimeDelta &);

    /** @see ClockTime_equal */
    friend bool operator==(const ClockTime &, const ClockTime &);
    friend bool operator!=(const ClockTime &, const ClockTime &);

    /** @see ClockTime_less_than */
    friend bool operator<(const ClockTime &, const ClockTime &);
    /** @see ClockTime_less_than_or_equal */
    friend bool operator<=(const ClockTime &, const ClockTime &);
    /** @see ClockTime_greater_than */
    friend bool operator>(const ClockTime &, const ClockTime &);
    /** @see ClockTime_greater_than_or_equal */
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

/**
 * Create a new ClockTime based on an hour of the day.
 *
 * If any parameter is out of range, a ClockTime will be returned with "error"
 * set.
 *
 * @param hour The hour of the day (0 to 23, inclusive).
 */
PRESENT_API struct ClockTime
ClockTime_create_from_hour(int_hour hour);

/**
 * Create a new ClockTime based on an hour and a minute.
 *
 * If any parameter is out of range, a ClockTime will be returned with "error"
 * set.
 *
 * @param hour The hour of the day (0 to 23, inclusive).
 * @param minute The minute of the hour (0 to 59, inclusive).
 */
PRESENT_API struct ClockTime
ClockTime_create_from_hour_minute(int_hour hour, int_minute minute);

/**
 * Create a new ClockTime based on an hour, a minute, and a second.
 *
 * If any parameter is out of range, a ClockTime will be returned with "error"
 * set.
 *
 * @param hour The hour of the day (0 to 23, inclusive).
 * @param minute The minute of the hour (0 to 59, inclusive).
 * @param second The second of the minute (0 to 59, inclusive, or possibly 60
 * in the case of a leap second).
 */
PRESENT_API struct ClockTime
ClockTime_create_from_hour_minute_second(
        int_hour hour,
        int_minute minute,
        int_second second);

/**
 * Create a new ClockTime based on an hour, a minute, a second, and a
 * nanosecond.
 *
 * @param hour The hour of the day (0 to 23, inclusive).
 * @param minute The minute of the hour (0 to 59, inclusive).
 * @param second The second of the minute (0 to 59, inclusive, or possibly 60
 * in the case of a leap second).
 * @param nanosecond The nanosecond (0 to 10^9-1, inclusive, i.e. no bigger
 * than the number of nanoseconds in a second).
 */
PRESENT_API struct ClockTime
ClockTime_create_from_hour_minute_second_nanosecond(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond);

/**
 * Create a new ClockTime from either an hour (1 argument), an hour and a
 * minute (2 arguments), an hour/minute/second (3 arguments), or an
 * hour/minute/second/nanosecond (4 arguments).
 *
 * @see ClockTime_create_from_hour
 * @see ClockTime_create_from_hour_minute
 * @see ClockTime_create_from_hour_minute_second
 * @see ClockTime_create_from_hour_minute_second_nanosecond
 */
#define ClockTime_create(...)    \
    PRESENT_OVERLOAD_MAX_4(__VA_ARGS__, \
        ClockTime_create_from_hour_minute_second_nanosecond,    \
        ClockTime_create_from_hour_minute_second,   \
        ClockTime_create_from_hour_minute,  \
        ClockTime_create_from_hour)(__VA_ARGS__)

/**
 * Create a new ClockTime based on an hour, a minute, and a decimal second.
 *
 * @param hour The hour of the day (0 to 23, inclusive).
 * @param minute The minute of the hour (0 to 59, inclusive).
 * @param second The second of the minute (0 up to, but not including, 60).
 */
PRESENT_API struct ClockTime
ClockTime_create_with_decimal_seconds(
        int_hour hour,
        int_minute minute,
        double second);

/**
 * Create a new ClockTime initialized to midnight (00:00).
 */
PRESENT_API struct ClockTime
ClockTime_midnight();

/**
 * Create a new ClockTime initialized to noon (12:00).
 */
PRESENT_API struct ClockTime
ClockTime_noon();

/**
 * Get the hour component of a ClockTime.
 */
PRESENT_API int_hour
ClockTime_get_hour(const struct ClockTime * const self);

/**
 * Get the minute component of a ClockTime.
 */
PRESENT_API int_minute
ClockTime_get_minute(const struct ClockTime * const self);

/**
 * Get the second component of a ClockTime.
 */
PRESENT_API int_second
ClockTime_get_second(const struct ClockTime * const self);

/**
 * Get the nanosecond component of a ClockTime.
 */
PRESENT_API int_nanosecond
ClockTime_get_nanosecond(const struct ClockTime * const self);

/**
 * Get the second component of a ClockTime as a decimal, based on both the
 * second and nanosecond components.
 */
PRESENT_API double
ClockTime_get_second_decimal(const struct ClockTime * const self);

/**
 * Add a @ref TimeDelta to a ClockTime.
 *
 * If the result goes above 23:59:59.999... or below 00:00, the ClockTime will
 * wrap around.
 */
PRESENT_API void
ClockTime_add_time_delta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta);

/**
 * Subtract a @ref TimeDelta from a ClockTime.
 *
 * If the result goes above 23:59:59.999... or below 00:00, the ClockTime will
 * wrap around.
 */
PRESENT_API void
ClockTime_subtract_time_delta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta);

/**
 * Determine whether two ClockTime instances are equal.
 */
PRESENT_API bool
ClockTime_equal(const struct ClockTime * const, const struct ClockTime * const);

/**
 * Determine whether a ClockTime is less than another ClockTime.
 */
PRESENT_API bool
ClockTime_less_than(
        const struct ClockTime * const,
        const struct ClockTime * const);

/**
 * Determine whether a ClockTime is less than or equal to another ClockTime.
 */
PRESENT_API bool
ClockTime_less_than_or_equal(
        const struct ClockTime * const,
        const struct ClockTime * const);

/**
 * Determine whether a ClockTime is greater than another ClockTime.
 */
PRESENT_API bool
ClockTime_greater_than(
        const struct ClockTime * const,
        const struct ClockTime * const);

/**
 * Determine whether a ClockTime is greater than or equal to another ClockTime.
 */
PRESENT_API bool
ClockTime_greater_than_or_equal(
        const struct ClockTime * const,
        const struct ClockTime * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_CLOCK_TIME_H_ */

