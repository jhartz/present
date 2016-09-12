/*
 * Present - Date/Time Library
 *
 * Definition of the TimeDelta structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <time.h>

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-time-delta-data.h"

#ifndef _PRESENT_TIME_DELTA_H_
#define _PRESENT_TIME_DELTA_H_

/*
 * Forward Declarations
 */

struct DayDelta;

/*
 * Enum Definitions
 */

enum PresentTimeDeltaError {
    TimeDelta_ERROR_NONE = 0
};

/*
 * C++ Class / C Struct Definition
 */

/**
 * Class or struct representing a positive or negative delta of a number of
 * nanoseconds, seconds, minutes, hours, days, or weeks.
 */
struct PRESENT_API TimeDelta {
    enum PresentTimeDeltaError error;
    struct PresentTimeDeltaData data_;

#ifdef __cplusplus
    /** @copydoc TimeDelta_from_nanoseconds */
    static TimeDelta from_nanoseconds(int_delta nanoseconds);

    /** @copydoc TimeDelta_from_microseconds */
    static TimeDelta from_microseconds(int_delta microseconds);

    /** @copydoc TimeDelta_from_milliseconds */
    static TimeDelta from_milliseconds(int_delta milliseconds);

    /** @copydoc TimeDelta_from_seconds */
    static TimeDelta from_seconds(int_delta seconds);

    /** @copydoc TimeDelta_from_minutes */
    static TimeDelta from_minutes(int_delta minutes);

    /** @copydoc TimeDelta_from_hours */
    static TimeDelta from_hours(int_delta hours);

    /** @copydoc TimeDelta_from_days */
    static TimeDelta from_days(int_delta days);

    /** @copydoc TimeDelta_from_weeks */
    static TimeDelta from_weeks(int_delta weeks);

    /** @copydoc TimeDelta_zero */
    static TimeDelta zero();

    /** @copydoc TimeDelta_get_nanoseconds */
    int_delta get_nanoseconds() const;

    /** @copydoc TimeDelta_get_microseconds */
    int_delta get_microseconds() const;
    /** @copydoc TimeDelta_get_microseconds_decimal */
    double get_microseconds_decimal() const;

    /** @copydoc TimeDelta_get_milliseconds */
    int_delta get_milliseconds() const;
    /** @copydoc TimeDelta_get_milliseconds_decimal */
    double get_milliseconds_decimal() const;

    /** @copydoc TimeDelta_get_seconds */
    int_delta get_seconds() const;
    /** @copydoc TimeDelta_get_seconds_decimal */
    double get_seconds_decimal() const;

    /** @copydoc TimeDelta_get_minutes */
    int_delta get_minutes() const;
    /** @copydoc TimeDelta_get_minutes_decimal */
    double get_minutes_decimal() const;

    /** @copydoc TimeDelta_get_hours */
    int_delta get_hours() const;
    /** @copydoc TimeDelta_get_hours_decimal */
    double get_hours_decimal() const;

    /** @copydoc TimeDelta_get_days */
    int_delta get_days() const;
    /** @copydoc TimeDelta_get_days_decimal */
    double get_days_decimal() const;

    /** @copydoc TimeDelta_get_weeks */
    int_delta get_weeks() const;
    /** @copydoc TimeDelta_get_weeks_decimal */
    double get_weeks_decimal() const;

    /** @copydoc TimeDelta_get_day_delta_truncated */
    DayDelta get_day_delta_truncated() const;

    /** @copydoc TimeDelta_get_day_delta_rounded */
    DayDelta get_day_delta_rounded() const;

    /** @copydoc TimeDelta_get_day_delta_abs_ceil */
    DayDelta get_day_delta_abs_ceil() const;

    /** @copydoc TimeDelta_is_negative */
    bool is_negative() const;

    /** @copydoc TimeDelta_negate */
    void negate();

    /**
     * Return the negated version of this TimeDelta.
     * @see TimeDelta::negate
     */
    TimeDelta operator-() const;

    /** @copydoc TimeDelta_multiply_by */
    TimeDelta & operator*=(const int & scale_factor);
    /** @copydoc TimeDelta_multiply_by_decimal */
    TimeDelta & operator*=(const double & scale_factor);
    /** @copydoc TimeDelta_divide_by */
    TimeDelta & operator/=(const int & scale_factor);
    /** @copydoc TimeDelta_divide_by_decimal */
    TimeDelta & operator/=(const double & scale_factor);

    /** @see TimeDelta::operator*=(const int & scale_factor) */
    friend const TimeDelta operator*(
            const TimeDelta & delta,
            const int & scale_factor);
    /** @see TimeDelta::operator*=(const double & scale_factor) */
    friend const TimeDelta operator*(
            const TimeDelta & delta,
            const double & scale_factor);
    /** @see TimeDelta::operator/=(const int & scale_factor) */
    friend const TimeDelta operator/(
            const TimeDelta & delta,
            const int & scale_factor);
    /** @see TimeDelta::operator/=(const double & scale_factor) */
    friend const TimeDelta operator/(
            const TimeDelta & delta,
            const double & scale_factor);

    /** @copydoc TimeDelta_add_time_delta */
    TimeDelta & operator+=(const TimeDelta & other);
    /** @copydoc TimeDelta_subtract_time_delta */
    TimeDelta & operator-=(const TimeDelta & other);

    /** @see TimeDelta::operator+=(const TimeDelta & other) */
    friend const TimeDelta operator+(
            const TimeDelta & lhs,
            const TimeDelta & rhs);
    /** @see TimeDelta::operator-=(const TimeDelta & other) */
    friend const TimeDelta operator-(
            const TimeDelta & lhs,
            const TimeDelta & rhs);

    /** @copydoc TimeDelta_compare */
    static int compare(const TimeDelta & lhs, const TimeDelta & rhs);

    /** @copydoc TimeDelta_equal */
    friend bool operator==(const TimeDelta & lhs, const TimeDelta & rhs);
    friend bool operator!=(const TimeDelta & lhs, const TimeDelta & rhs);

    /** @copydoc TimeDelta_less_than */
    friend bool operator<(const TimeDelta & lhs, const TimeDelta & rhs);
    /** @copydoc TimeDelta_less_than_or_equal */
    friend bool operator<=(const TimeDelta & lhs, const TimeDelta & rhs);
    /** @copydoc TimeDelta_greater_than */
    friend bool operator>(const TimeDelta & lhs, const TimeDelta & rhs);
    /** @copydoc TimeDelta_greater_than_or_equal */
    friend bool operator>=(const TimeDelta & lhs, const TimeDelta & rhs);
#endif
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a new TimeDelta based on a positive or negative number of
 * nanoseconds.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_nanoseconds(int_delta nanoseconds);

/**
 * Create a new TimeDelta based on a positive or negative number of
 * microseconds.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_microseconds(int_delta microseconds);

/**
 * Create a new TimeDelta based on a positive or negative number of
 * milliseconds.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_milliseconds(int_delta milliseconds);

/**
 * Create a new TimeDelta based on a positive or negative number of seconds.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_seconds(int_delta seconds);

/**
 * Create a new TimeDelta based on a positive or negative number of minutes.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_minutes(int_delta minutes);

/**
 * Create a new TimeDelta based on a positive or negative number of hours.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_hours(int_delta hours);

/**
 * Create a new TimeDelta based on a positive or negative number of days.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_days(int_delta days);

/**
 * Create a new TimeDelta based on a positive or negative number of weeks.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_weeks(int_delta weeks);

/**
 * Create a new TimeDelta initialized to zero time.
 */
PRESENT_API struct TimeDelta
TimeDelta_zero();

/**
 * Get the number of nanoseconds represented by a TimeDelta.
 */
PRESENT_API int_delta
TimeDelta_get_nanoseconds(const struct TimeDelta * const self);

/**
 * Get the number of microseconds represented by a TimeDelta. If the TimeDelta
 * does not represent an exact number of microseconds, the return value will
 * be truncated.
 */
PRESENT_API int_delta
TimeDelta_get_microseconds(const struct TimeDelta * const self);

/**
 * Get the number of microseconds represented by a TimeDelta, with a
 * fractional part if necessary.
 */
PRESENT_API double
TimeDelta_get_microseconds_decimal(const struct TimeDelta * const self);

/**
 * Get the number of milliseconds represented by a TimeDelta. If the TimeDelta
 * does not represent an exact number of milliseconds, the return value will
 * be truncated.
 */
PRESENT_API int_delta
TimeDelta_get_milliseconds(const struct TimeDelta * const self);

/**
 * Get the number of milliseconds represented by a TimeDelta, with a
 * fractional part if necessary.
 */
PRESENT_API double
TimeDelta_get_milliseconds_decimal(const struct TimeDelta * const self);

/**
 * Get the number of seconds represented by a TimeDelta. If the TimeDelta does
 * not represent an exact number of seconds, the returned value will be
 * truncated.
 */
PRESENT_API int_delta
TimeDelta_get_seconds(const struct TimeDelta * const self);

/**
 * Get the number of seconds represented by a TimeDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
TimeDelta_get_seconds_decimal(const struct TimeDelta * const self);

/**
 * Get the number of minutes represented by a TimeDelta. If the TimeDelta does
 * not represent an exact number of minutes, the returned value will be
 * truncated.
 */
PRESENT_API int_delta
TimeDelta_get_minutes(const struct TimeDelta * const self);

/**
 * Get the number of minutes represented by a TimeDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
TimeDelta_get_minutes_decimal(const struct TimeDelta * const self);

/**
 * Get the number of hours represented by a TimeDelta. If the TimeDelta does
 * not represent an exact number of hours, the returned value will be
 * truncated.
 */
PRESENT_API int_delta
TimeDelta_get_hours(const struct TimeDelta * const self);

/**
 * Get the number of hours represented by a TimeDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
TimeDelta_get_hours_decimal(const struct TimeDelta * const self);

/**
 * Get the number of days represented by a TimeDelta. If the TimeDelta does
 * not represent an exact number of days, the returned value will be
 * truncated.
 */
PRESENT_API int_delta
TimeDelta_get_days(const struct TimeDelta * const self);

/**
 * Get the number of days represented by a TimeDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
TimeDelta_get_days_decimal(const struct TimeDelta * const self);

/**
 * Get the number of weeks represented by a TimeDelta. If the TimeDelta does
 * not represent an exact number of weeks, the returned value will be
 * truncated.
 */
PRESENT_API int_delta
TimeDelta_get_weeks(const struct TimeDelta * const self);

/**
 * Get the number of weeks represented by a TimeDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
TimeDelta_get_weeks_decimal(const struct TimeDelta * const self);

/**
 * Convert a TimeDelta into a @ref DayDelta, rounding towards zero if the
 * TimeDelta does not represent an exact number of days.
 */
PRESENT_API struct DayDelta
TimeDelta_get_day_delta_truncated(const struct TimeDelta * const self);

/**
 * Convert a TimeDelta into a @ref DayDelta, rounding to the nearest day if
 * the TimeDelta does not represent an exact number of days.
 */
PRESENT_API struct DayDelta
TimeDelta_get_day_delta_rounded(const struct TimeDelta * const self);

/**
 * Convert a TimeDelta into a @ref DayDelta, rounding away from zero if the
 * TimeDelta does not represent an exact number of days.
 */
PRESENT_API struct DayDelta
TimeDelta_get_day_delta_abs_ceil(const struct TimeDelta * const self);

/**
 * Determine whether a TimeDelta is negative.
 */
PRESENT_API present_bool
TimeDelta_is_negative(const struct TimeDelta * const self);

/**
 * Negate a TimeDelta, making it negative if it was positive or positive if it
 * was negative.
 */
PRESENT_API void
TimeDelta_negate(struct TimeDelta * const self);

/**
 * Scale a TimeDelta by multiplying it by an integer scale factor.
 */
PRESENT_API void
TimeDelta_multiply_by(struct TimeDelta * const self, const int scale_factor);

/**
 * Scale a TimeDelta by multiplying it by a floating point scale factor.
 */
PRESENT_API void
TimeDelta_multiply_by_decimal(
        struct TimeDelta * const self,
        const double scale_factor);

/**
 * Scale a TimeDelta by dividing it by an integer scale factor.
 */
PRESENT_API void
TimeDelta_divide_by(struct TimeDelta * const self, const int scale_factor);

/**
 * Scale a TimeDelta by dividing it by a floating point scale factor.
 */
PRESENT_API void
TimeDelta_divide_by_decimal(
        struct TimeDelta * const self,
        const double scale_factor);

/**
 * Add another TimeDelta to a TimeDelta.
 */
PRESENT_API void
TimeDelta_add_time_delta(
        struct TimeDelta * const self,
        const struct TimeDelta * const other);

/**
 * Subtract another TimeDelta from a TimeDelta.
 */
PRESENT_API void
TimeDelta_subtract_time_delta(
        struct TimeDelta * const self,
        const struct TimeDelta * const other);

/**
 * Compare two TimeDelta instances.
 *
 * If lhs < rhs, then a negative integer will be returned.
 * If lhs == rhs, then 0 will be returned.
 * If lhs > rhs, then a positive integer will be returned.
 */
PRESENT_API int
TimeDelta_compare(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs);

/**
 * Determine whether two TimeDelta instances are equal (lhs == rhs).
 */
PRESENT_API present_bool
TimeDelta_equal(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs);

/**
 * Determine whether a TimeDelta is less than another TimeDelta (lhs < rhs).
 */
PRESENT_API present_bool
TimeDelta_less_than(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs);

/**
 * Determine whether a TimeDelta is less than or equal to another TimeDelta
 * (lhs <= rhs).
 */
PRESENT_API present_bool
TimeDelta_less_than_or_equal(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs);

/**
 * Determine whether a TimeDelta is greater than another TimeDelta (lhs > rhs).
 */
PRESENT_API present_bool
TimeDelta_greater_than(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs);

/**
 * Determine whether a TimeDelta is greater than or equal to another TimeDelta
 * (lhs >= rhs).
 */
PRESENT_API present_bool
TimeDelta_greater_than_or_equal(
        const struct TimeDelta * const lhs,
        const struct TimeDelta * const rhs);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_TIME_DELTA_H_ */

