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


/*
 * C++ Class / C Struct Definition
 */

struct PRESENT_API TimeDelta {
    struct PresentTimeDeltaData data_;

#ifdef __cplusplus
    static TimeDelta from_nanoseconds(int_delta nanoseconds);

    static TimeDelta from_seconds(int_delta seconds);

    static TimeDelta from_minutes(int_delta minutes);

    static TimeDelta from_hours(int_delta hours);

    static TimeDelta from_days(int_delta days);

    static TimeDelta from_weeks(int_delta weeks);

    static TimeDelta zero();

    int_delta get_nanoseconds() const;

    int_delta get_seconds() const;

    double get_seconds_decimal() const;

    int_delta get_minutes() const;

    double get_minutes_decimal() const;

    int_delta get_hours() const;

    double get_hours_decimal() const;

    int_delta get_days() const;

    double get_days_decimal() const;

    int_delta get_weeks() const;

    double get_weeks_decimal() const;

    bool is_negative() const;

    void negate();

    TimeDelta operator-() const;

    TimeDelta & operator*=(const int &);
    TimeDelta & operator*=(const double &);
    TimeDelta & operator/=(const int &);
    TimeDelta & operator/=(const double &);

    friend const TimeDelta operator*(const TimeDelta &, const int &);
    friend const TimeDelta operator*(const TimeDelta &, const double &);
    friend const TimeDelta operator/(const TimeDelta &, const int &);
    friend const TimeDelta operator/(const TimeDelta &, const double &);

    TimeDelta & operator+=(const TimeDelta &);
    TimeDelta & operator-=(const TimeDelta &);

    friend const TimeDelta operator+(const TimeDelta &, const TimeDelta &);
    friend const TimeDelta operator-(const TimeDelta &, const TimeDelta &);

    friend bool operator==(const TimeDelta &, const TimeDelta &);
    friend bool operator!=(const TimeDelta &, const TimeDelta &);

    friend bool operator<(const TimeDelta &, const TimeDelta &);
    friend bool operator<=(const TimeDelta &, const TimeDelta &);
    friend bool operator>(const TimeDelta &, const TimeDelta &);
    friend bool operator>=(const TimeDelta &, const TimeDelta &);

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

