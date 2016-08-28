/*
 * Present - Date/Time Library
 *
 * Definition of the TimeDelta structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

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
    /** @see TimeDelta_from_nanoseconds */
    static TimeDelta from_nanoseconds(int_delta nanoseconds);

    /** @see TimeDelta_from_seconds */
    static TimeDelta from_seconds(int_delta seconds);

    /** @see TimeDelta_from_minutes */
    static TimeDelta from_minutes(int_delta minutes);

    /** @see TimeDelta_from_hours */
    static TimeDelta from_hours(int_delta hours);

    /** @see TimeDelta_from_days */
    static TimeDelta from_days(int_delta days);

    /** @see TimeDelta_from_weeks */
    static TimeDelta from_weeks(int_delta weeks);

    /** @see TimeDelta_zero */
    static TimeDelta zero();

    /** @see TimeDelta_get_nanoseconds */
    int_delta get_nanoseconds() const;

    /** @see TimeDelta_get_seconds */
    int_delta get_seconds() const;

    /** @see TimeDelta_get_seconds_decimal */
    double get_seconds_decimal() const;

    /** @see TimeDelta_get_minutes */
    int_delta get_minutes() const;

    /** @see TimeDelta_get_minutes_decimal */
    double get_minutes_decimal() const;

    /** @see TimeDelta_get_hours */
    int_delta get_hours() const;

    /** @see TimeDelta_get_hours_decimal */
    double get_hours_decimal() const;

    /** @see TimeDelta_get_days */
    int_delta get_days() const;

    /** @see TimeDelta_get_days_decimal */
    double get_days_decimal() const;

    /** @see TimeDelta_get_weeks */
    int_delta get_weeks() const;

    /** @see TimeDelta_get_weeks_decimal */
    double get_weeks_decimal() const;

    /** @see TimeDelta_get_day_delta_truncated */
    DayDelta get_day_delta_truncated() const;

    /** @see TimeDelta_get_day_delta_rounded */
    DayDelta get_day_delta_rounded() const;

    /** @see TimeDelta_get_day_delta_abs_ceil */
    DayDelta get_day_delta_abs_ceil() const;

    /** @see TimeDelta_is_negative */
    bool is_negative() const;

    /** @see TimeDelta_negate */
    void negate();

    TimeDelta operator-() const;

    /** @see TimeDelta_multiply_by */
    TimeDelta & operator*=(const int &);
    /** @see TimeDelta_multiply_by_decimal */
    TimeDelta & operator*=(const double &);
    /** @see TimeDelta_divide_by */
    TimeDelta & operator/=(const int &);
    /** @see TimeDelta_divide_by_decimal */
    TimeDelta & operator/=(const double &);

    friend const TimeDelta operator*(const TimeDelta &, const int &);
    friend const TimeDelta operator*(const TimeDelta &, const double &);
    friend const TimeDelta operator/(const TimeDelta &, const int &);
    friend const TimeDelta operator/(const TimeDelta &, const double &);

    /** @see TimeDelta_add_time_delta */
    TimeDelta & operator+=(const TimeDelta &);
    /** @see TimeDelta_subtract_time_delta */
    TimeDelta & operator-=(const TimeDelta &);

    friend const TimeDelta operator+(const TimeDelta &, const TimeDelta &);
    friend const TimeDelta operator-(const TimeDelta &, const TimeDelta &);

    /** @see TimeDelta_equal */
    friend bool operator==(const TimeDelta &, const TimeDelta &);
    friend bool operator!=(const TimeDelta &, const TimeDelta &);

    /** @see TimeDelta_less_than */
    friend bool operator<(const TimeDelta &, const TimeDelta &);
    /** @see TimeDelta_less_than_or_equal */
    friend bool operator<=(const TimeDelta &, const TimeDelta &);
    /** @see TimeDelta_greater_than */
    friend bool operator>(const TimeDelta &, const TimeDelta &);
    /** @see TimeDelta_greater_than_or_equal */
    friend bool operator>=(const TimeDelta &, const TimeDelta &);

    /*
     * This constructor exists so that DayDeltas can be used wherever a
     * TimeDelta is expected (since DayDeltas are a subset of TimeDeltas).
     */
    TimeDelta(const DayDelta & dayDelta);

    PRESENT_BOILERPLATE_CONSTRUCTORS(TimeDelta)
#endif
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

PRESENT_API struct TimeDelta
TimeDelta_from_nanoseconds(int_delta nanoseconds);

PRESENT_API struct TimeDelta
TimeDelta_from_seconds(int_delta seconds);

PRESENT_API struct TimeDelta
TimeDelta_from_minutes(int_delta minutes);

PRESENT_API struct TimeDelta
TimeDelta_from_hours(int_delta hours);

PRESENT_API struct TimeDelta
TimeDelta_from_days(int_delta days);

PRESENT_API struct TimeDelta
TimeDelta_from_weeks(int_delta weeks);

PRESENT_API struct TimeDelta
TimeDelta_zero();

PRESENT_API int_delta
TimeDelta_get_nanoseconds(const struct TimeDelta * const self);

PRESENT_API int_delta
TimeDelta_get_seconds(const struct TimeDelta * const self);

PRESENT_API double
TimeDelta_get_seconds_decimal(const struct TimeDelta * const self);

PRESENT_API int_delta
TimeDelta_get_minutes(const struct TimeDelta * const self);

PRESENT_API double
TimeDelta_get_minutes_decimal(const struct TimeDelta * const self);

PRESENT_API int_delta
TimeDelta_get_hours(const struct TimeDelta * const self);

PRESENT_API double
TimeDelta_get_hours_decimal(const struct TimeDelta * const self);

PRESENT_API int_delta
TimeDelta_get_days(const struct TimeDelta * const self);

PRESENT_API double
TimeDelta_get_days_decimal(const struct TimeDelta * const self);

PRESENT_API int_delta
TimeDelta_get_weeks(const struct TimeDelta * const self);

PRESENT_API double
TimeDelta_get_weeks_decimal(const struct TimeDelta * const self);

PRESENT_API struct DayDelta
TimeDelta_get_day_delta_truncated(const struct TimeDelta * const self);

PRESENT_API struct DayDelta
TimeDelta_get_day_delta_rounded(const struct TimeDelta * const self);

PRESENT_API struct DayDelta
TimeDelta_get_day_delta_abs_ceil(const struct TimeDelta * const self);

PRESENT_API bool
TimeDelta_is_negative(const struct TimeDelta * const self);

PRESENT_API void
TimeDelta_negate(struct TimeDelta * const self);

PRESENT_API void
TimeDelta_multiply_by(struct TimeDelta * const self, const int scaleFactor);

PRESENT_API void
TimeDelta_multiply_by_decimal(
        struct TimeDelta * const self,
        const double scaleFactor);

PRESENT_API void
TimeDelta_divide_by(struct TimeDelta * const self, const int scaleFactor);

PRESENT_API void
TimeDelta_divide_by_decimal(
        struct TimeDelta * const self,
        const double scaleFactor);

PRESENT_API void
TimeDelta_add_time_delta(
        struct TimeDelta * const self,
        const struct TimeDelta * const timeDeltaToAdd);

PRESENT_API void
TimeDelta_subtract_time_delta(
        struct TimeDelta * const self,
        const struct TimeDelta * const timeDeltaToSubtract);

PRESENT_API bool
TimeDelta_equal(const struct TimeDelta * const, const struct TimeDelta * const);

PRESENT_API bool
TimeDelta_less_than(
        const struct TimeDelta * const,
        const struct TimeDelta * const);

PRESENT_API bool
TimeDelta_less_than_or_equal(
        const struct TimeDelta * const,
        const struct TimeDelta * const);

PRESENT_API bool
TimeDelta_greater_than(
        const struct TimeDelta * const,
        const struct TimeDelta * const);

PRESENT_API bool
TimeDelta_greater_than_or_equal(
        const struct TimeDelta * const,
        const struct TimeDelta * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_TIME_DELTA_H_ */

