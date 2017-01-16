/*
 * Present - Date/Time Library
 *
 * Definition of the MonthDelta structure and declarations of the corresponding
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

#include "present/internal/present-month-delta-data.h"

#ifndef _PRESENT_MONTH_DELTA_H_
#define _PRESENT_MONTH_DELTA_H_

/*
 * Forward Declarations
 */

/*
 * C++ Class / C Struct Definition
 */

/**
 * Class or struct representing a positive or negative delta of a number of
 * months or years.
 */
struct PRESENT_API MonthDelta {
    /* Internal data representation */
    struct PresentMonthDeltaData data_;

#ifdef __cplusplus
    /** @copydoc MonthDelta_from_months */
    static MonthDelta from_months(int_month_delta month_delta);

    /** @copydoc MonthDelta_from_years */
    static MonthDelta from_years(int_year_delta year_delta);

    /** @copydoc MonthDelta_zero */
    static MonthDelta zero();

    /** @copydoc MonthDelta_months */
    int_month_delta months() const;

    /** @copydoc MonthDelta_years */
    int_year_delta years() const;

    /** @copydoc MonthDelta_years_decimal */
    double years_decimal() const;

    /** @copydoc MonthDelta_is_negative */
    bool is_negative() const;

    /** @copydoc MonthDelta_negate */
    void negate();

    /**
     * Return the negated version of this MonthDelta.
     * @see MonthDelta::negate
     */
    MonthDelta operator-() const;

    /** Add one month to the MonthDelta. */
    MonthDelta & operator++();
    /** Add one month to the MonthDelta. */
    MonthDelta operator++(int);
    /** Subtract one month from the MonthDelta. */
    MonthDelta & operator--();
    /** Subtract one month from the MonthDelta. */
    MonthDelta operator--(int);

    /** @copydoc MonthDelta_multiply_by */
    MonthDelta & operator*=(const int & scale_factor);
    /** @copydoc MonthDelta_divide_by */
    MonthDelta & operator/=(const int & scale_factor);

    /** @see MonthDelta::operator*=(const int & scale_factor) */
    friend const MonthDelta operator*(
            const MonthDelta & delta,
            const int & scale_factor);
    /** @see MonthDelta::operator/=(const int & scale_factor) */
    friend const MonthDelta operator/(
            const MonthDelta & delta,
            const int & scale_factor);

    /** @copydoc MonthDelta_add */
    MonthDelta & operator+=(const MonthDelta & other);
    /** @copydoc MonthDelta_subtract */
    MonthDelta & operator-=(const MonthDelta & other);

    /** @see MonthDelta::operator+=(const MonthDelta & other) */
    friend const MonthDelta operator+(
            const MonthDelta & lhs,
            const MonthDelta & rhs);
    /** @see MonthDelta::operator-=(const MonthDelta & other) */
    friend const MonthDelta operator-(
            const MonthDelta & lhs,
            const MonthDelta & rhs);

    /** @copydoc MonthDelta_compare */
    static int compare(const MonthDelta & lhs, const MonthDelta & rhs);

    /** @copydoc MonthDelta_equal */
    friend bool operator==(const MonthDelta &, const MonthDelta & rhs);
    friend bool operator!=(const MonthDelta &, const MonthDelta & rhs);

    /** @copydoc MonthDelta_less_than */
    friend bool operator<(const MonthDelta & lhs, const MonthDelta & rhs);
    /** @copydoc MonthDelta_less_than_or_equal */
    friend bool operator<=(const MonthDelta & lhs, const MonthDelta & rhs);
    /** @copydoc MonthDelta_greater_than */
    friend bool operator>(const MonthDelta & lhs, const MonthDelta & rhs);
    /** @copydoc MonthDelta_greater_than_or_equal */
    friend bool operator>=(const MonthDelta & lhs, const MonthDelta & rhs);
#endif
};

/*
 * C Method Declarations
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a new MonthDelta based on a positive or negative number of months.
 */
PRESENT_API struct MonthDelta
MonthDelta_from_months(int_month_delta month_delta);

/**
 * @copydoc MonthDelta_from_months
 * @param[out] result A pointer to a struct MonthDelta for the result.
 */
PRESENT_API void
MonthDelta_ptr_from_months(
        struct MonthDelta * const result,
        int_month_delta month_delta);

/**
 * Create a new MonthDelta based on a positive or negative number of years.
 */
PRESENT_API struct MonthDelta
MonthDelta_from_years(int_year_delta year_delta);

/**
 * @copydoc MonthDelta_from_years
 * @param[out] result A pointer to a struct MonthDelta for the result.
 */
PRESENT_API void
MonthDelta_ptr_from_years(
        struct MonthDelta * const result,
        int_year_delta year_delta);

/**
 * Create a new MonthDelta initialized to zero months.
 */
PRESENT_API struct MonthDelta
MonthDelta_zero();

/**
 * @copydoc MonthDelta_zero
 * @param[out] result A pointer to a struct MonthDelta for the result.
 */
PRESENT_API void
MonthDelta_ptr_zero(struct MonthDelta * const result);

/**
 * Get the number of months represented by a MonthDelta.
 */
PRESENT_API int_month_delta
MonthDelta_months(const struct MonthDelta * const self);

/**
 * Get the number of years represented by a MonthDelta. If the MonthDelta does
 * not represent an exact number of years, the number of years will be
 * truncated.
 */
PRESENT_API int_year_delta
MonthDelta_years(const struct MonthDelta * const self);

/**
 * Get the number of years represented by a MonthDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
MonthDelta_years_decimal(const struct MonthDelta * const self);

/**
 * Determine whether a MonthDelta is negative.
 */
PRESENT_API present_bool
MonthDelta_is_negative(const struct MonthDelta * const self);

/**
 * Negate a MonthDelta, making it negative if it was positive or positive if
 * it was negative.
 */
PRESENT_API void
MonthDelta_negate(struct MonthDelta * const self);

/**
 * Scale a MonthDelta by multiplying it by a scale factor.
 */
PRESENT_API void
MonthDelta_multiply_by(struct MonthDelta * const self, int scale_factor);

/**
 * Scale a MonthDelta by dividing it by a scale factor.
 */
PRESENT_API void
MonthDelta_divide_by(struct MonthDelta * const self, int scale_factor);

/**
 * Add another MonthDelta to a MonthDelta.
 * The second MonthDelta parameter is added to the first.
 */
PRESENT_API void
MonthDelta_add(
        struct MonthDelta * const self,
        const struct MonthDelta * const other);

/**
 * Subtract another MonthDelta from a MonthDelta.
 * The second MonthDelta parameter is subtracted from the first.
 */
PRESENT_API void
MonthDelta_subtract(
        struct MonthDelta * const self,
        const struct MonthDelta * const other);

/**
 * Compare two MonthDelta instances.
 *
 * If lhs < rhs, then a negative integer will be returned.
 * If lhs == rhs, then 0 will be returned.
 * If lhs > rhs, then a positive integer will be returned.
 */
PRESENT_API int
MonthDelta_compare(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs);

/**
 * Determine whether two MonthDelta instances are equal (lhs == rhs).
 */
PRESENT_API present_bool
MonthDelta_equal(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs);

/**
 * Determine whether a MonthDelta is less than another MonthDelta (lhs < rhs).
 */
PRESENT_API present_bool
MonthDelta_less_than(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs);

/**
 * Determine whether a MonthDelta is less than or equal to another MonthDelta
 * (lhs <= rhs).
 */
PRESENT_API present_bool
MonthDelta_less_than_or_equal(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs);

/**
 * Determine whether a MonthDelta is greater than another MonthDelta
 * (lhs > rhs).
 */
PRESENT_API present_bool
MonthDelta_greater_than(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs);

/**
 * Determine whether a MonthDelta is greater than or equal to another
 * MonthDelta (lhs >= rhs).
 */
PRESENT_API present_bool
MonthDelta_greater_than_or_equal(
        const struct MonthDelta * const lhs,
        const struct MonthDelta * const rhs);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_MONTH_DELTA_H_ */

