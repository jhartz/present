/*
 * Present - Date/Time Library
 *
 * Definition of the MonthDelta structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-month-delta-data.h"

#ifndef _PRESENT_MONTH_DELTA_H_
#define _PRESENT_MONTH_DELTA_H_

/*
 * Forward Declarations
 */


/*
 * Enum Definitions
 */

enum PresentMonthDeltaError {
    MonthDelta_ERROR_NONE = 0
};

/*
 * C++ Class / C Struct Definition
 */

/**
 * Class or struct representing a positive or negative delta of a number of
 * months or years.
 */
struct PRESENT_API MonthDelta {
    enum PresentMonthDeltaError error;
    struct PresentMonthDeltaData data_;

#ifdef __cplusplus
    /** @see MonthDelta_from_months */
    static MonthDelta from_months(int_month_delta month_delta);

    /** @see MonthDelta_from_years */
    static MonthDelta from_years(int_year_delta year_delta);

    /** @see MonthDelta_zero */
    static MonthDelta zero();

    /** @see MonthDelta_get_months */
    int_month_delta get_months() const;

    /** @see MonthDelta_get_years */
    int_year_delta get_years() const;

    /** @see MonthDelta_get_years_decimal */
    double get_years_decimal() const;

    /** @see MonthDelta_is_negative */
    bool is_negative() const;

    /** @see MonthDelta_negate */
    void negate();

    MonthDelta operator-() const;

    /** Add one month to the MonthDelta. */
    MonthDelta & operator++();
    /** Add one month to the MonthDelta. */
    MonthDelta operator++(int);
    /** Subtract one month from the MonthDelta. */
    MonthDelta & operator--();
    /** Subtract one month from the MonthDelta. */
    MonthDelta operator--(int);

    /** @see MonthDelta_multiply_by */
    MonthDelta & operator*=(const int &);
    /** @see MonthDelta_divide_by */
    MonthDelta & operator/=(const int &);

    friend const MonthDelta operator*(const MonthDelta &, const int &);
    friend const MonthDelta operator/(const MonthDelta &, const int &);

    /** @see MonthDelta_add_month_delta */
    MonthDelta & operator+=(const MonthDelta &);
    /** @see MonthDelta_subtract_month_delta */
    MonthDelta & operator-=(const MonthDelta &);

    friend const MonthDelta operator+(const MonthDelta &, const MonthDelta &);
    friend const MonthDelta operator-(const MonthDelta &, const MonthDelta &);

    /** @see MonthDelta_equal */
    friend bool operator==(const MonthDelta &, const MonthDelta &);
    friend bool operator!=(const MonthDelta &, const MonthDelta &);

    /** @see MonthDelta_less_than */
    friend bool operator<(const MonthDelta &, const MonthDelta &);
    /** @see MonthDelta_less_than_or_equal */
    friend bool operator<=(const MonthDelta &, const MonthDelta &);
    /** @see MonthDelta_greater_than */
    friend bool operator>(const MonthDelta &, const MonthDelta &);
    /** @see MonthDelta_greater_than_or_equal */
    friend bool operator>=(const MonthDelta &, const MonthDelta &);

    PRESENT_BOILERPLATE_CONSTRUCTORS(MonthDelta)
#endif
};

/*
 * C Method Definitions
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
 * Create a new MonthDelta based on a positive or negative number of years.
 */
PRESENT_API struct MonthDelta
MonthDelta_from_years(int_year_delta year_delta);

/**
 * Create a new MonthDelta initialized to zero months.
 */
PRESENT_API struct MonthDelta
MonthDelta_zero();

/**
 * Get the number of months represented by a MonthDelta.
 */
PRESENT_API int_month_delta
MonthDelta_get_months(const struct MonthDelta * const self);

/**
 * Get the number of years represented by a MonthDelta. If the MonthDelta does
 * not represent an exact number of years, the number of years will be
 * truncated.
 */
PRESENT_API int_year_delta
MonthDelta_get_years(const struct MonthDelta * const self);

/**
 * Get the number of years represented by a MonthDelta, with a fractional part
 * if necessary.
 */
PRESENT_API double
MonthDelta_get_years_decimal(const struct MonthDelta * const self);

/**
 * Determine whether a MonthDelta is negative.
 */
PRESENT_API bool
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
MonthDelta_multiply_by(struct MonthDelta * const self, int scaleFactor);

/**
 * Scale a MonthDelta by dividing it by a scale factor.
 */
PRESENT_API void
MonthDelta_divide_by(struct MonthDelta * const self, int scaleFactor);

/**
 * Add another MonthDelta to a MonthDelta.
 */
PRESENT_API void
MonthDelta_add_month_delta(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToAdd);

/**
 * Subtract another MonthDelta from a MonthDelta.
 */
PRESENT_API void
MonthDelta_subtract_month_delta(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToSubtract);

/**
 * Determine whether two MonthDelta instances are equal.
 */
PRESENT_API bool
MonthDelta_equal(
        const struct MonthDelta * const,
        const struct MonthDelta * const);

/**
 * Determine whether a MonthDelta is less than another MonthDelta.
 */
PRESENT_API bool
MonthDelta_less_than(
        const struct MonthDelta * const,
        const struct MonthDelta * const);

/**
 * Determine whether a MonthDelta is less than or equal to another MonthDelta.
 */
PRESENT_API bool
MonthDelta_less_than_or_equal(
        const struct MonthDelta * const,
        const struct MonthDelta * const);

/**
 * Determine whether a MonthDelta is greater than another MonthDelta.
 */
PRESENT_API bool
MonthDelta_greater_than(
        const struct MonthDelta * const,
        const struct MonthDelta * const);

/**
 * Determine whether a MonthDelta is greater than or equal to another
 * MonthDelta.
 */
PRESENT_API bool
MonthDelta_greater_than_or_equal(
        const struct MonthDelta * const,
        const struct MonthDelta * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_MONTH_DELTA_H_ */

