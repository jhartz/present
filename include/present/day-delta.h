/*
 * Present - Date/Time Library
 *
 * Definition of the DayDelta structure and declarations of the corresponding
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

#include "present/internal/present-day-delta-data.h"

#ifndef _PRESENT_DAY_DELTA_H_
#define _PRESENT_DAY_DELTA_H_

/*
 * Forward Declarations
 */

struct TimeDelta;

/*
 * C++ Class / C Struct Definition
 */

/**
 * Class or struct representing a positive or negative delta of a number of
 * days or weeks.
 */
struct PRESENT_API DayDelta {
    /* Internal data representation */
    struct PresentDayDeltaData data_;

#ifdef __cplusplus
    /** @copydoc DayDelta_from_days */
    static DayDelta from_days(int_delta days);

    /** @copydoc DayDelta_from_weeks */
    static DayDelta from_weeks(int_delta weeks);

    /** @copydoc DayDelta_zero */
    static DayDelta zero();

    /** @copydoc DayDelta_days */
    int_delta days() const;

    /** @copydoc DayDelta_weeks */
    int_delta weeks() const;

    /** @copydoc DayDelta_weeks_decimal */
    double weeks_decimal() const;

    /** @copydoc DayDelta_to_TimeDelta */
    TimeDelta to_TimeDelta() const;

    /** @copydoc DayDelta_is_negative */
    bool is_negative() const;

    /** @copydoc DayDelta_negate */
    void negate();

    /**
     * Return the negated version of this DayDelta.
     * @see DayDelta::negate
     */
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
    DayDelta & operator*=(const long & scale_factor);
    /** @copydoc DayDelta_divide_by */
    DayDelta & operator/=(const long & scale_factor);

    /** @see DayDelta::operator*=(const long & scale_factor) */
    friend const DayDelta operator*(
            const DayDelta & delta,
            const long & scale_factor);
    /** @see DayDelta::operator/=(const long & scale_factor) */
    friend const DayDelta operator/(
            const DayDelta & delta,
            const long & scale_factor);

    /** @copydoc DayDelta_add */
    DayDelta & operator+=(const DayDelta & other);
    /** @copydoc DayDelta_subtract */
    DayDelta & operator-=(const DayDelta & other);

    /** @see DayDelta::operator+=(const DayDelta & other) */
    friend const DayDelta operator+(
            const DayDelta & lhs,
            const DayDelta & rhs);
    /** @see DayDelta::operator-=(const DayDelta & other) */
    friend const DayDelta operator-(
            const DayDelta & lhs,
            const DayDelta & rhs);

    /** @copydoc DayDelta_compare */
    static short compare(const DayDelta & lhs, const DayDelta & rhs);

    /** @copydoc DayDelta_compare_to_TimeDelta */
    static short compare(const DayDelta & lhs, const TimeDelta & rhs);
    /** @see DayDelta::compare(const DayDelta & lhs, const TimeDelta & rhs) */
    static short compare(const TimeDelta & lhs, const DayDelta & rhs);

    /** @copydoc DayDelta_equal */
    friend bool operator==(const DayDelta & lhs, const DayDelta & rhs);
    /** @copydoc DayDelta_equal_TimeDelta */
    friend bool operator==(const DayDelta & lhs, const TimeDelta & rhs);

    friend bool operator!=(const DayDelta & lhs, const DayDelta & rhs);
    friend bool operator!=(const DayDelta & lhs, const TimeDelta & rhs);

    /** @copydoc DayDelta_less_than */
    friend bool operator<(const DayDelta & lhs, const DayDelta & rhs);
    /** @copydoc DayDelta_less_than_TimeDelta */
    friend bool operator<(const DayDelta & lhs, const TimeDelta & rhs);

    /** @copydoc DayDelta_less_than_or_equal */
    friend bool operator<=(const DayDelta & lhs, const DayDelta & rhs);
    /** @copydoc DayDelta_less_than_or_equal_TimeDelta */
    friend bool operator<=(const DayDelta & lhs, const TimeDelta & rhs);

    /** @copydoc DayDelta_greater_than */
    friend bool operator>(const DayDelta & lhs, const DayDelta & rhs);
    /** @copydoc DayDelta_greater_than_TimeDelta */
    friend bool operator>(const DayDelta & lhs, const TimeDelta & rhs);

    /** @copydoc DayDelta_greater_than_or_equal */
    friend bool operator>=(const DayDelta & lhs, const DayDelta & rhs);
    /** @copydoc DayDelta_greater_than_or_equal_TimeDelta */
    friend bool operator>=(const DayDelta & lhs, const TimeDelta & rhs);
#endif
};

/*
 * C Method Declarations
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
 * @copydoc DayDelta_from_days
 * @param[out] result A pointer to a struct DayDelta for the result.
 */
PRESENT_API void
DayDelta_ptr_from_days(struct DayDelta * const result, int_delta days);

/**
 * Create a new DayDelta based on a positive or negative number of weeks.
 */
PRESENT_API struct DayDelta
DayDelta_from_weeks(int_delta weeks);

/**
 * @copydoc DayDelta_from_weeks
 * @param[out] result A pointer to a struct DayDelta for the result.
 */
PRESENT_API void
DayDelta_ptr_from_weeks(struct DayDelta * const result, int_delta weeks);

/**
 * Create a new DayDelta initialized to zero days.
 */
PRESENT_API struct DayDelta
DayDelta_zero(void);

/**
 * @copydoc DayDelta_zero
 * @param[out] result A pointer to a struct DayDelta for the result.
 */
PRESENT_API void
DayDelta_ptr_zero(struct DayDelta * const result);

/**
 * Get the number of days represented by a DayDelta.
 */
PRESENT_API int_delta
DayDelta_days(const struct DayDelta * const self);

/**
 * Get the number of weeks represented by a DayDelta. If the DayDelta does not
 * represent an exact number of weeks, the number of weeks will be truncated.
 */
PRESENT_API int_delta
DayDelta_weeks(const struct DayDelta * const self);

/**
 * Get the number of weeks represented by a DayDelta, with a fractional part if
 * necessary.
 */
PRESENT_API double
DayDelta_weeks_decimal(const struct DayDelta * const self);

/**
 * Convert a DayDelta into an equivalent @ref TimeDelta.
 */
PRESENT_API struct TimeDelta
DayDelta_to_TimeDelta(const struct DayDelta * const self);

/**
 * Determine whether a DayDelta is negative.
 */
PRESENT_API present_bool
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
DayDelta_multiply_by(struct DayDelta * const self, long scale_factor);

/**
 * Scale a DayDelta by dividing it by a scale factor.
 */
PRESENT_API void
DayDelta_divide_by(struct DayDelta * const self, long scale_factor);

/**
 * Add another DayDelta to a DayDelta.
 * The second DayDelta parameter is added to the first.
 */
PRESENT_API void
DayDelta_add(
        struct DayDelta * const self,
        const struct DayDelta * const other);

/**
 * Subtract another DayDelta from a DayDelta.
 * The second DayDelta parameter is added to the first.
 */
PRESENT_API void
DayDelta_subtract(
        struct DayDelta * const self,
        const struct DayDelta * const other);

/**
 * Compare two DayDelta instances.
 *
 * - If lhs < rhs, then a negative integer will be returned.
 * - If lhs == rhs, then 0 will be returned.
 * - If lhs > rhs, then a positive integer will be returned.
 */
PRESENT_API short
DayDelta_compare(
        const struct DayDelta * const lhs,
        const struct DayDelta * const rhs);

/**
 * Compare a DayDelta to a TimeDelta.
 *
 * - If lhs < rhs, then a negative integer will be returned.
 * - If lhs == rhs, then 0 will be returned.
 * - If lhs > rhs, then a positive integer will be returned.
 */
PRESENT_API short
DayDelta_compare_to_TimeDelta(
        const struct DayDelta * const lhs,
        const struct TimeDelta * const rhs);

/**
 * Determine whether two DayDelta instances are equal (lhs == rhs).
 */
PRESENT_API present_bool
DayDelta_equal(
        const struct DayDelta * const lhs,
        const struct DayDelta * const rhs);

/**
 * Determine whether a DayDelta equals a TimeDelta (lhs == rhs).
 */
PRESENT_API present_bool
DayDelta_equal_TimeDelta(
        const struct DayDelta * const lhs,
        const struct TimeDelta * const rhs);

/**
 * Determine whether a DayDelta is less than another DayDelta (lhs < rhs).
 */
PRESENT_API present_bool
DayDelta_less_than(
        const struct DayDelta * const lhs,
        const struct DayDelta * const rhs);

/**
 * Determine whether a DayDelta is less than a TimeDelta (lhs < rhs).
 */
PRESENT_API present_bool
DayDelta_less_than_TimeDelta(
        const struct DayDelta * const lhs,
        const struct TimeDelta * const rhs);

/**
 * Determine whether a DayDelta is less than or equal to another DayDelta
 * (lhs <= rhs).
 */
PRESENT_API present_bool
DayDelta_less_than_or_equal(
        const struct DayDelta * const lhs,
        const struct DayDelta * const rhs);

/**
 * Determine whether a DayDelta is less than or equal to a TimeDelta
 * (lhs <= rhs).
 */
PRESENT_API present_bool
DayDelta_less_than_or_equal_TimeDelta(
        const struct DayDelta * const lhs,
        const struct TimeDelta * const rhs);

/**
 * Determine whether a DayDelta is greater than another DayDelta (lhs > rhs).
 */
PRESENT_API present_bool
DayDelta_greater_than(
        const struct DayDelta * const lhs,
        const struct DayDelta * const rhs);

/**
 * Determine whether a DayDelta is greater than a TimeDelta (lhs > rhs).
 */
PRESENT_API present_bool
DayDelta_greater_than_TimeDelta(
        const struct DayDelta * const lhs,
        const struct TimeDelta * const rhs);

/**
 * Determine whether a DayDelta is greater than or equal to another DayDelta
 * (lhs >= rhs).
 */
PRESENT_API present_bool
DayDelta_greater_than_or_equal(
        const struct DayDelta * const lhs,
        const struct DayDelta * const rhs);

/**
 * Determine whether a DayDelta is greater than or equal to a TimeDelta
 * (lhs >= rhs).
 */
PRESENT_API present_bool
DayDelta_greater_than_or_equal_TimeDelta(
        const struct DayDelta * const lhs,
        const struct TimeDelta * const rhs);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_DAY_DELTA_H_ */

