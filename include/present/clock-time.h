/*
 * Present - Date/Time Library
 *
 * Definition of the ClockTime structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <time.h>

#include "present/utils/header-utils.h"
#include "present/utils/types.h"
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
    /** @copydoc ClockTime_from_hour */
    static ClockTime create(int_hour hour);

    /** @copydoc ClockTime_from_hour_minute */
    static ClockTime create(int_hour hour, int_minute minute);

    /** @copydoc ClockTime_from_hour_minute_second */
    static ClockTime create(
        int_hour hour,
        int_minute minute,
        int_second second);

    /** @copydoc ClockTime_from_hour_minute_second_nanosecond */
    static ClockTime create(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond);

    /** @copydoc ClockTime_create_with_decimal_seconds */
    static ClockTime create_with_decimal_seconds(
            int_hour hour,
            int_minute minute,
            double second);

    /** @copydoc ClockTime_midnight */
    static ClockTime midnight();

    /** @copydoc ClockTime_noon */
    static ClockTime noon();

    /** @copydoc ClockTime_hour */
    int_hour hour() const;

    /** @copydoc ClockTime_minute */
    int_minute minute() const;

    /** @copydoc ClockTime_second */
    int_second second() const;

    /** @copydoc ClockTime_nanosecond */
    int_nanosecond nanosecond() const;

    /** @copydoc ClockTime_second_decimal */
    double second_decimal() const;

    /** @copydoc ClockTime_time_since_midnight */
    TimeDelta time_since_midnight() const;

    /** @copydoc ClockTime_add_TimeDelta */
    ClockTime & operator+=(const TimeDelta & delta);
    /** @copydoc ClockTime_subtract_TimeDelta */
    ClockTime & operator-=(const TimeDelta & delta);

    /** @see ClockTime::operator+=(const TimeDelta & delta) */
    friend const ClockTime operator+(
            const ClockTime & lhs,
            const TimeDelta & rhs);
    /** @see ClockTime::operator+=(const TimeDelta & delta) */
    friend const ClockTime operator+(
            const TimeDelta & lhs,
            const ClockTime & rhs);

    /** @see ClockTime::operator-=(const TimeDelta & delta) */
    friend const ClockTime operator-(
            const ClockTime & lhs,
            const TimeDelta & rhs);

    /** @copydoc ClockTime_compare */
    static int compare(const ClockTime & lhs, const ClockTime & rhs);

    /** @copydoc ClockTime_equal */
    friend bool operator==(const ClockTime & lhs, const ClockTime & rhs);
    friend bool operator!=(const ClockTime & lhs, const ClockTime & rhs);

    /** @copydoc ClockTime_less_than */
    friend bool operator<(const ClockTime & lhs, const ClockTime & rhs);
    /** @copydoc ClockTime_less_than_or_equal */
    friend bool operator<=(const ClockTime & lhs, const ClockTime & rhs);
    /** @copydoc ClockTime_greater_than */
    friend bool operator>(const ClockTime & lhs, const ClockTime & rhs);
    /** @copydoc ClockTime_greater_than_or_equal */
    friend bool operator>=(const ClockTime & lhs, const ClockTime & rhs);
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
ClockTime_from_hour(int_hour hour);

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
ClockTime_from_hour_minute(int_hour hour, int_minute minute);

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
ClockTime_from_hour_minute_second(
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
ClockTime_from_hour_minute_second_nanosecond(
        int_hour hour,
        int_minute minute,
        int_second second,
        int_nanosecond nanosecond);

/**
 * Create a new ClockTime from either an hour (1 argument), an hour and a
 * minute (2 arguments), an hour/minute/second (3 arguments), or an
 * hour/minute/second/nanosecond (4 arguments).
 *
 * @see ClockTime_from_hour
 * @see ClockTime_from_hour_minute
 * @see ClockTime_from_hour_minute_second
 * @see ClockTime_from_hour_minute_second_nanosecond
 */
#define ClockTime_create(...)    \
    PRESENT_OVERLOAD_MAX_4(__VA_ARGS__,                 \
        ClockTime_from_hour_minute_second_nanosecond,   \
        ClockTime_from_hour_minute_second,              \
        ClockTime_from_hour_minute,                     \
        ClockTime_from_hour,                            \
        dummy)(__VA_ARGS__)

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
 * Get the hour component of a ClockTime (0 to 23, inclusive).
 */
PRESENT_API int_hour
ClockTime_hour(const struct ClockTime * const self);

/**
 * Get the minute component of a ClockTime (0 to 59, inclusive).
 */
PRESENT_API int_minute
ClockTime_minute(const struct ClockTime * const self);

/**
 * Get the second component of a ClockTime (0 to 59, inclusive).
 */
PRESENT_API int_second
ClockTime_second(const struct ClockTime * const self);

/**
 * Get the nanosecond component of a ClockTime (less than 10^9, the number of
 * nanoseconds in a second).
 */
PRESENT_API int_nanosecond
ClockTime_nanosecond(const struct ClockTime * const self);

/**
 * Get the second component of a ClockTime as a decimal, based on both the
 * second and nanosecond components.
 */
PRESENT_API double
ClockTime_second_decimal(const struct ClockTime * const self);

/**
 * Get a @ref TimeDelta with the time since midnight of a ClockTime.
 */
PRESENT_API struct TimeDelta
ClockTime_time_since_midnight(const struct ClockTime * const self);

/**
 * Add a @ref TimeDelta to a ClockTime.
 *
 * If the result goes above 23:59:59.999... or below 00:00, the ClockTime will
 * wrap around.
 */
PRESENT_API void
ClockTime_add_TimeDelta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta);

/**
 * Subtract a @ref TimeDelta from a ClockTime.
 *
 * If the result goes above 23:59:59.999... or below 00:00, the ClockTime will
 * wrap around.
 */
PRESENT_API void
ClockTime_subtract_TimeDelta(
        struct ClockTime * const self,
        const struct TimeDelta * const delta);

/**
 * Compare two ClockTime instances.
 *
 * If lhs < rhs, then a negative integer will be returned.
 * If lhs == rhs, then 0 will be returned.
 * If lhs > rhs, then a positive integer will be returned.
 */
PRESENT_API int
ClockTime_compare(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs);

/**
 * Determine whether two ClockTime instances are equal (lhs == rhs).
 */
PRESENT_API present_bool
ClockTime_equal(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs);

/**
 * Determine whether a ClockTime is earlier than another ClockTime (lhs < rhs).
 */
PRESENT_API present_bool
ClockTime_less_than(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs);

/**
 * Determine whether a ClockTime is earlier than or or the same as another
 * ClockTime (lhs <= rhs).
 */
PRESENT_API present_bool
ClockTime_less_than_or_equal(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs);

/**
 * Determine whether a ClockTime is later than another ClockTime (lhs > rhs).
 */
PRESENT_API present_bool
ClockTime_greater_than(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs);

/**
 * Determine whether a ClockTime is later than or the same as another
 * ClockTime (lhs >= rhs).
 */
PRESENT_API present_bool
ClockTime_greater_than_or_equal(
        const struct ClockTime * const lhs,
        const struct ClockTime * const rhs);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_CLOCK_TIME_H_ */

