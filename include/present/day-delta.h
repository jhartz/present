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
    /** @copydoc DayDelta_from_days */
    static DayDelta from_days(int_delta days);

    /** @copydoc DayDelta_from_weeks */
    static DayDelta from_weeks(int_delta weeks);

    /** @copydoc DayDelta_zero */
    static DayDelta zero();

    /** @copydoc DayDelta_get_days */
    int_delta get_days() const;

    /** @copydoc DayDelta_get_weeks */
    int_delta get_weeks() const;

    /** @copydoc DayDelta_get_weeks_decimal */
    double get_weeks_decimal() const;

    /** @copydoc DayDelta_get_time_delta */
    TimeDelta get_time_delta() const;

    /** @copydoc DayDelta_is_negative */
    bool is_negative() const;

    /** @copydoc DayDelta_negate */
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

    /** @copydoc DayDelta_multiply_by */
    DayDelta & operator*=(const int &);
    /** @copydoc DayDelta_divide_by */
    DayDelta & operator/=(const int &);

    friend const DayDelta operator*(const DayDelta &, const int &);
    friend const DayDelta operator/(const DayDelta &, const int &);

    /** @copydoc DayDelta_add_day_delta */
    DayDelta & operator+=(const DayDelta &);
    /** @copydoc DayDelta_subtract_day_delta */
    DayDelta & operator-=(const DayDelta &);

    friend const DayDelta operator+(const DayDelta &, const DayDelta &);
    friend const DayDelta operator-(const DayDelta &, const DayDelta &);

    /** @copydoc DayDelta_equal */
    friend bool operator==(const DayDelta &, const DayDelta &);
    friend bool operator!=(const DayDelta &, const DayDelta &);

    /** @copydoc DayDelta_less_than */
    friend bool operator<(const DayDelta &, const DayDelta &);
    /** @copydoc DayDelta_less_than_or_equal */
    friend bool operator<=(const DayDelta &, const DayDelta &);
    /** @copydoc DayDelta_greater_than */
    friend bool operator>(const DayDelta &, const DayDelta &);
    /** @copydoc DayDelta_greater_than_or_equal */
    friend bool operator>=(const DayDelta &, const DayDelta &);
#endif
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a new DayDelta based on a positive or negative number of days.
 */
PRESENT_API struct DayDelta
DayDelta_from_days(int_delta days);

/**
 * Create a new DayDelta based on a positive or negative number of weeks.
 */
PRESENT_API struct DayDelta
DayDelta_from_weeks(int_delta weeks);

/**
 * Create a new DayDelta initialized to zero days.
 */
PRESENT_API struct DayDelta
DayDelta_zero();

/**
 * Get the number of days represented by a DayDelta.
 */
PRESENT_API int_delta
DayDelta_get_days(const struct DayDelta * const self);

/**
 * Get the number of weeks represented by a DayDelta. If the DayDelta does not
 * represent an exact number of weeks, the number of weeks will be truncated.
 */
PRESENT_API int_delta
DayDelta_get_weeks(const struct DayDelta * const self);

/**
 * Get the number of weeks represented by a DayDelta, with a fractional part if
 * necessary.
 */
PRESENT_API double
DayDelta_get_weeks_decimal(const struct DayDelta * const self);

/**
 * Convert a DayDelta into an equivalent @ref TimeDelta.
 */
PRESENT_API struct TimeDelta
DayDelta_get_time_delta(const struct DayDelta * const self);

/**
 * Determine whether a DayDelta is negative.
 */
PRESENT_API bool
DayDelta_is_negative(const struct DayDelta * const self);

/**
 * Negate a DayDelta, making it negative if it was positive or positive if it
 * was negative.
 */
PRESENT_API void
DayDelta_negate(struct DayDelta * const self);

/**
 * Scale a DayDelta by multiplying it by a scale factor.
 */
PRESENT_API void
DayDelta_multiply_by(struct DayDelta * const self, int scaleFactor);

/**
 * Scale a DayDelta by dividing it by a scale factor.
 */
PRESENT_API void
DayDelta_divide_by(struct DayDelta * const self, int scaleFactor);

/**
 * Add another DayDelta to a DayDelta.
 */
PRESENT_API void
DayDelta_add_day_delta(
        struct DayDelta * const self,
        const struct DayDelta * const dayDeltaToAdd);

/**
 * Subtract another DayDelta from a DayDelta.
 */
PRESENT_API void
DayDelta_subtract_day_delta(
        struct DayDelta * const self,
        const struct DayDelta * const dayDeltaToSubtract);

/**
 * Determine whether two DayDelta instances are equal.
 */
PRESENT_API bool
DayDelta_equal(
        const struct DayDelta * const,
        const struct DayDelta * const);

/**
 * Determine whether a DayDelta is less than another DayDelta.
 */
PRESENT_API bool
DayDelta_less_than(
        const struct DayDelta * const,
        const struct DayDelta * const);

/**
 * Determine whether a DayDelta is less than or equal to another DayDelta.
 */
PRESENT_API bool
DayDelta_less_than_or_equal(
        const struct DayDelta * const,
        const struct DayDelta * const);

/**
 * Determine whether a DayDelta is greater than another DayDelta.
 */
PRESENT_API bool
DayDelta_greater_than(
        const struct DayDelta * const,
        const struct DayDelta * const);

/**
 * Determine whether a DayDelta is greater than or equal to another DayDelta.
 */
PRESENT_API bool
DayDelta_greater_than_or_equal(
        const struct DayDelta * const,
        const struct DayDelta * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_DAY_DELTA_H_ */

