/*
 * Present - Date/Time Library
 *
 * Definition of the TimeDelta structure and declarations of the corresponding
 * functions
 *
 * This file may be included individually ONLY if being used by a C compiler.
 * However, it is recommended (and required for C++ projects) to include
 * "present.h" rather than these individual header files.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <time.h>

#include "present/internal/cpp-guard.h"
#include "present/internal/header-utils.h"
#include "present/internal/types.h"

#include "present/internal/present-time-delta-data.h"

#ifndef _PRESENT_TIME_DELTA_H_
#define _PRESENT_TIME_DELTA_H_

/*
 * Forward Declarations
 */

struct DayDelta;

/*
 * C++ Class / C Struct Definition
 */

/**
 * Class or struct representing a positive or negative delta of a number of
 * nanoseconds, seconds, minutes, hours, days, or weeks.
 */
struct PRESENT_API TimeDelta {
    /* Internal data representation */
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

    /** @copydoc TimeDelta_nanoseconds */
    int_delta nanoseconds() const;

    /** @copydoc TimeDelta_microseconds */
    int_delta microseconds() const;
    /** @copydoc TimeDelta_microseconds_decimal */
    double microseconds_decimal() const;

    /** @copydoc TimeDelta_milliseconds */
    int_delta milliseconds() const;
    /** @copydoc TimeDelta_milliseconds_decimal */
    double milliseconds_decimal() const;

    /** @copydoc TimeDelta_seconds */
    int_delta seconds() const;
    /** @copydoc TimeDelta_seconds_decimal */
    double seconds_decimal() const;

    /** @copydoc TimeDelta_minutes */
    int_delta minutes() const;
    /** @copydoc TimeDelta_minutes_decimal */
    double minutes_decimal() const;

    /** @copydoc TimeDelta_hours */
    int_delta hours() const;
    /** @copydoc TimeDelta_hours_decimal */
    double hours_decimal() const;

    /** @copydoc TimeDelta_days */
    int_delta days() const;
    /** @copydoc TimeDelta_days_decimal */
    double days_decimal() const;

    /** @copydoc TimeDelta_weeks */
    int_delta weeks() const;
    /** @copydoc TimeDelta_weeks_decimal */
    double weeks_decimal() const;

    /** @copydoc TimeDelta_to_DayDelta_truncated */
    DayDelta to_DayDelta_truncated() const;

    /** @copydoc TimeDelta_to_DayDelta_rounded */
    DayDelta to_DayDelta_rounded() const;

    /** @copydoc TimeDelta_to_DayDelta_abs_ceil */
    DayDelta to_DayDelta_abs_ceil() const;

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

    /** @copydoc TimeDelta_add */
    TimeDelta & operator+=(const TimeDelta & other);
    /** @copydoc TimeDelta_add_DayDelta */
    TimeDelta & operator+=(const DayDelta & other);
    /** @copydoc TimeDelta_subtract */
    TimeDelta & operator-=(const TimeDelta & other);
    /** @copydoc TimeDelta_subtract_DayDelta */
    TimeDelta & operator-=(const DayDelta & other);

    /** @see TimeDelta::operator+=(const TimeDelta & other) */
    friend const TimeDelta operator+(
            const TimeDelta & lhs,
            const TimeDelta & rhs);
    /** @see TimeDelta::operator+=(const DayDelta & other) */
    friend const TimeDelta operator+(
            const TimeDelta & lhs,
            const DayDelta & rhs);
    /** @see TimeDelta::operator+=(const DayDelta & other) */
    friend const TimeDelta operator+(
            const DayDelta & lhs,
            const TimeDelta & rhs);
    /** @see TimeDelta::operator-=(const TimeDelta & other) */
    friend const TimeDelta operator-(
            const TimeDelta & lhs,
            const TimeDelta & rhs);
    /** @see TimeDelta::operator-=(const DayDelta & other) */
    friend const TimeDelta operator-(
            const TimeDelta & lhs,
            const DayDelta & rhs);
    /** @see TimeDelta::operator-=(const DayDelta & other) */
    friend const TimeDelta operator-(
            const DayDelta & lhs,
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
 * C Method Declarations
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
 * @copydoc TimeDelta_from_nanoseconds
 * @param[out] result A pointer to a struct TimeDelta for the result.
 */
PRESENT_API void
TimeDelta_ptr_from_nanoseconds(
        struct TimeDelta * const result,
        int_delta nanoseconds);

/**
 * Create a new TimeDelta based on a positive or negative number of
 * microseconds.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_microseconds(int_delta microseconds);

/**
 * @copydoc TimeDelta_from_microseconds
 * @param[out] result A pointer to a struct TimeDelta for the result.
 */
PRESENT_API void
TimeDelta_ptr_from_microseconds(
        struct TimeDelta * const result,
        int_delta microseconds);

/**
 * Create a new TimeDelta based on a positive or negative number of
 * milliseconds.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_milliseconds(int_delta milliseconds);

/**
 * @copydoc TimeDelta_from_milliseconds
 * @param[out] result A pointer to a struct TimeDelta for the result.
 */
PRESENT_API void
TimeDelta_ptr_from_milliseconds(
        struct TimeDelta * const result,
        int_delta milliseconds);

/**
 * Create a new TimeDelta based on a positive or negative number of seconds.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_seconds(int_delta seconds);

/**
 * @copydoc TimeDelta_from_seconds
 * @param[out] result A pointer to a struct TimeDelta for the result.
 */
PRESENT_API void
TimeDelta_ptr_from_seconds(struct TimeDelta * const result, int_delta seconds);

/**
 * Create a new TimeDelta based on a positive or negative number of minutes.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_minutes(int_delta minutes);

/**
 * @copydoc TimeDelta_from_minutes
 * @param[out] result A pointer to a struct TimeDelta for the result.
 */
PRESENT_API void
TimeDelta_ptr_from_minutes(struct TimeDelta * const result, int_delta minutes);

/**
 * Create a new TimeDelta based on a positive or negative number of hours.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_hours(int_delta hours);

/**
 * @copydoc TimeDelta_from_hours
 * @param[out] result A pointer to a struct TimeDelta for the result.
 */
PRESENT_API void
TimeDelta_ptr_from_hours(struct TimeDelta * const result, int_delta hours);

/**
 * Create a new TimeDelta based on a positive or negative number of days.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_days(int_delta days);

/**
 * @copydoc TimeDelta_from_days
 * @param[out] result A pointer to a struct TimeDelta for the result.
 */
PRESENT_API void
TimeDelta_ptr_from_days(struct TimeDelta * const result, int_delta days);

/**
 * Create a new TimeDelta based on a positive or negative number of weeks.
 */
PRESENT_API struct TimeDelta
TimeDelta_from_weeks(int_delta weeks);

/**
 * @copydoc TimeDelta_from_weeks
 * @param[out] result A pointer to a struct TimeDelta for the result.
 */
PRESENT_API void
TimeDelta_ptr_from_weeks(struct TimeDelta * const result, int_delta weeks);

/**
 * Create a new TimeDelta initialized to zero time.
 */
PRESENT_API struct TimeDelta
TimeDelta_zero();

/**
 * @copydoc TimeDelta_zero
 * @param[out] result A pointer to a struct TimeDelta for the result.
 */
PRESENT_API void
TimeDelta_ptr_zero(struct TimeDelta * const result);

/**
 * Get the number of nanoseconds represented by a TimeDelta.
 */
PRESENT_API int_delta
TimeDelta_nanoseconds(const struct TimeDelta * const self);

/**
 * Get the number of microseconds represented by a TimeDelta. If the TimeDelta
 * does not represent an exact number of microseconds, the return value will
 * be truncated.
 */
PRESENT_API int_delta
TimeDelta_microseconds(const struct TimeDelta * const self);

/**
 * Get the number of microseconds represented by a TimeDelta, with a
 * fractional part if necessary.
 */
PRESENT_API double
TimeDelta_microseconds_decimal(const struct TimeDelta * const self);

/**
 * Get the number of milliseconds represented by a TimeDelta. If the TimeDelta
 * does not represent an exact number of milliseconds, the return value will
 * be truncated.
 */
PRESENT_API int_delta
TimeDelta_milliseconds(const struct TimeDelta * const self);

/**
 * Get the number of milliseconds represented by a TimeDelta, with a
 * fractional part if necessary.
 */
PRESENT_API double
TimeDelta_milliseconds_decimal(const struct TimeDelta * const self);

/**
 * Get the number of seconds represented by a TimeDelta. If the TimeDelta does
 * not represent an exact number of seconds, the returned value will be
 * truncated.
 */
PRESENT_API int_delta
TimeDelta_seconds(const struct TimeDelta * const self);

/**
 * Get the number of seconds represented by a TimeDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
TimeDelta_seconds_decimal(const struct TimeDelta * const self);

/**
 * Get the number of minutes represented by a TimeDelta. If the TimeDelta does
 * not represent an exact number of minutes, the returned value will be
 * truncated.
 */
PRESENT_API int_delta
TimeDelta_minutes(const struct TimeDelta * const self);

/**
 * Get the number of minutes represented by a TimeDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
TimeDelta_minutes_decimal(const struct TimeDelta * const self);

/**
 * Get the number of hours represented by a TimeDelta. If the TimeDelta does
 * not represent an exact number of hours, the returned value will be
 * truncated.
 */
PRESENT_API int_delta
TimeDelta_hours(const struct TimeDelta * const self);

/**
 * Get the number of hours represented by a TimeDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
TimeDelta_hours_decimal(const struct TimeDelta * const self);

/**
 * Get the number of days represented by a TimeDelta. If the TimeDelta does
 * not represent an exact number of days, the returned value will be
 * truncated.
 */
PRESENT_API int_delta
TimeDelta_days(const struct TimeDelta * const self);

/**
 * Get the number of days represented by a TimeDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
TimeDelta_days_decimal(const struct TimeDelta * const self);

/**
 * Get the number of weeks represented by a TimeDelta. If the TimeDelta does
 * not represent an exact number of weeks, the returned value will be
 * truncated.
 */
PRESENT_API int_delta
TimeDelta_weeks(const struct TimeDelta * const self);

/**
 * Get the number of weeks represented by a TimeDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
TimeDelta_weeks_decimal(const struct TimeDelta * const self);

/**
 * Convert a TimeDelta into a @ref DayDelta, rounding towards zero if the
 * TimeDelta does not represent an exact number of days.
 */
PRESENT_API struct DayDelta
TimeDelta_to_DayDelta_truncated(const struct TimeDelta * const self);

/**
 * Convert a TimeDelta into a @ref DayDelta, rounding to the nearest day if
 * the TimeDelta does not represent an exact number of days.
 */
PRESENT_API struct DayDelta
TimeDelta_to_DayDelta_rounded(const struct TimeDelta * const self);

/**
 * Convert a TimeDelta into a @ref DayDelta, rounding away from zero if the
 * TimeDelta does not represent an exact number of days.
 */
PRESENT_API struct DayDelta
TimeDelta_to_DayDelta_abs_ceil(const struct TimeDelta * const self);

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
 * The second TimeDelta parameter is added to the first.
 */
PRESENT_API void
TimeDelta_add(
        struct TimeDelta * const self,
        const struct TimeDelta * const other);

/**
 * Add a DayDelta to a TimeDelta.
 * The DayDelta parameter is added to the TimeDelta.
 */
PRESENT_API void
TimeDelta_add_DayDelta(
        struct TimeDelta * const self,
        const struct DayDelta * const other);

/**
 * Subtract another TimeDelta from a TimeDelta.
 * The second TimeDelta parameter is subtracted from the first.
 */
PRESENT_API void
TimeDelta_subtract(
        struct TimeDelta * const self,
        const struct TimeDelta * const other);

/**
 * Subtract a DayDelta from a TimeDelta.
 * The DayDelta parameter is subtracted from the TimeDelta.
 */
PRESENT_API void
TimeDelta_subtract_DayDelta(
        struct TimeDelta * const self,
        const struct DayDelta * const other);

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

