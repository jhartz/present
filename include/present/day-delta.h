/*
 * Present - Date/Time Library
 *
 * Definition of the DayDelta structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-day-delta-data.h"

#ifndef _PRESENT_DAY_DELTA_H_
#define _PRESENT_DAY_DELTA_H_

/*
 * Forward Declarations
 */

struct TimeDelta;

/*
 * C++ Class / C Struct Definition
 */

struct PRESENT_API DayDelta {
    enum {
        DayDelta_ERROR_NONE = 0;
    } error;
    struct PresentDayDeltaData data_;

#ifdef __cplusplus
    static DayDelta from_days(int_delta days);

    static DayDelta from_weeks(int_delta weeks);

    static DayDelta zero();

    int_delta get_days() const;

    int_delta get_weeks() const;

    double get_weeks_decimal() const;

    TimeDelta get_time_delta() const;

    bool is_negative() const;

    void negate();

    DayDelta operator-() const;

    DayDelta & operator++();
    DayDelta operator++(int);
    DayDelta & operator--();
    DayDelta operator--(int);

    DayDelta & operator*=(const int &);
    DayDelta & operator/=(const int &);

    friend const DayDelta operator*(const DayDelta &, const int &);
    friend const DayDelta operator/(const DayDelta &, const int &);

    DayDelta & operator+=(const DayDelta &);
    DayDelta & operator-=(const DayDelta &);

    friend const DayDelta operator+(const DayDelta &, const DayDelta &);
    friend const DayDelta operator-(const DayDelta &, const DayDelta &);

    friend bool operator==(const DayDelta &, const DayDelta &);
    friend bool operator!=(const DayDelta &, const DayDelta &);

    friend bool operator<(const DayDelta &, const DayDelta &);
    friend bool operator<=(const DayDelta &, const DayDelta &);
    friend bool operator>(const DayDelta &, const DayDelta &);
    friend bool operator>=(const DayDelta &, const DayDelta &);

    PRESENT_BOILERPLATE_CONSTRUCTORS(DayDelta)
#endif
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

PRESENT_API struct DayDelta
DayDelta_from_days(int_delta days);

PRESENT_API struct DayDelta
DayDelta_from_weeks(int_delta weeks);

PRESENT_API struct DayDelta
DayDelta_zero();

PRESENT_API int_delta
DayDelta_get_days(const struct DayDelta * const self);

PRESENT_API int_delta
DayDelta_get_weeks(const struct DayDelta * const self);

PRESENT_API double
DayDelta_get_weeks_decimal(const struct DayDelta * const self);

PRESENT_API struct TimeDelta
DayDelta_get_time_delta(const struct DayDelta * const self);

PRESENT_API bool
DayDelta_is_negative(const struct DayDelta * const self);

PRESENT_API void
DayDelta_negate(struct DayDelta * const self);

PRESENT_API void
DayDelta_multiply_by(struct DayDelta * const self, int scaleFactor);

PRESENT_API void
DayDelta_divide_by(struct DayDelta * const self, int scaleFactor);

PRESENT_API void
DayDelta_add_day_delta(
        struct DayDelta * const self,
        const struct DayDelta * const dayDeltaToAdd);

PRESENT_API void
DayDelta_subtract_day_delta(
        struct DayDelta * const self,
        const struct DayDelta * const dayDeltaToSubtract);

PRESENT_API bool
DayDelta_equal(
        const struct DayDelta * const,
        const struct DayDelta * const);

PRESENT_API bool
DayDelta_less_than(
        const struct DayDelta * const,
        const struct DayDelta * const);

PRESENT_API bool
DayDelta_less_than_or_equal(
        const struct DayDelta * const,
        const struct DayDelta * const);

PRESENT_API bool
DayDelta_greater_than(
        const struct DayDelta * const,
        const struct DayDelta * const);

PRESENT_API bool
DayDelta_greater_than_or_equal(
        const struct DayDelta * const,
        const struct DayDelta * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_DAY_DELTA_H_ */

