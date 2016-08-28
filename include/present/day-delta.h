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
 * Enum Definitions
 */

enum PresentDayDeltaError {
    DayDelta_ERROR_NONE = 0
};

/*
 * C++ Class / C Struct Definition
 */

/**
 * Class or struct representing a positive or negative delta of a number of
 * days or weeks.
 */
struct PRESENT_API DayDelta {
    enum PresentDayDeltaError error;
    struct PresentDayDeltaData data_;

#ifdef __cplusplus
    /** @see DayDelta_from_days */
    static DayDelta from_days(int_delta days);

    /** @see DayDelta_from_weeks */
    static DayDelta from_weeks(int_delta weeks);

    /** @see DayDelta_zero */
    static DayDelta zero();

    /** @see DayDelta_get_days */
    int_delta get_days() const;

    /** @see DayDelta_get_weeks */
    int_delta get_weeks() const;

    /** @see DayDelta_get_weeks_decimal */
    double get_weeks_decimal() const;

    /** @see DayDelta_get_time_delta */
    TimeDelta get_time_delta() const;

    /** @see DayDelta_is_negative */
    bool is_negative() const;

    /** @see DayDelta_negate */
    void negate();

    DayDelta operator-() const;

    /** Add one day to the DayDelta. */
    DayDelta & operator++();
    /** Add one day to the DayDelta. */
    DayDelta operator++(int);
    /** Subtract one day from the DayDelta. */
    DayDelta & operator--();
    /** Subtract one day from the DayDelta. */
    DayDelta operator--(int);

    /** @see DayDelta_multiply_by */
    DayDelta & operator*=(const int &);
    /** @see DayDelta_divide_by */
    DayDelta & operator/=(const int &);

    friend const DayDelta operator*(const DayDelta &, const int &);
    friend const DayDelta operator/(const DayDelta &, const int &);

    /** @see DayDelta_add_day_delta */
    DayDelta & operator+=(const DayDelta &);
    /** @see DayDelta_subtract_day_delta */
    DayDelta & operator-=(const DayDelta &);

    friend const DayDelta operator+(const DayDelta &, const DayDelta &);
    friend const DayDelta operator-(const DayDelta &, const DayDelta &);

    /** @see DayDelta_equal */
    friend bool operator==(const DayDelta &, const DayDelta &);
    friend bool operator!=(const DayDelta &, const DayDelta &);

    /** @see DayDelta_less_than */
    friend bool operator<(const DayDelta &, const DayDelta &);
    /** @see DayDelta_less_than_or_equal */
    friend bool operator<=(const DayDelta &, const DayDelta &);
    /** @see DayDelta_greater_than */
    friend bool operator>(const DayDelta &, const DayDelta &);
    /** @see DayDelta_greater_than_or_equal */
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

