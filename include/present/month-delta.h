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
 * C++ Class / C Struct Definition
 */

struct PRESENT_API MonthDelta {
    struct PresentMonthDeltaData data_;

#ifdef __cplusplus
    static MonthDelta from_months(int_month_delta month_delta);

    static MonthDelta from_years(int_year_delta year_delta);

    static MonthDelta zero();

    int_month_delta get_months() const;

    int_year_delta get_years() const;

    double get_years_decimal() const;

    bool is_negative() const;

    void negate();

    MonthDelta operator-() const;

    MonthDelta & operator++();
    MonthDelta operator++(int);
    MonthDelta & operator--();
    MonthDelta operator--(int);

    MonthDelta & operator*=(const int &);
    MonthDelta & operator/=(const int &);

    friend const MonthDelta operator*(const MonthDelta &, const int &);
    friend const MonthDelta operator/(const MonthDelta &, const int &);

    MonthDelta & operator+=(const MonthDelta &);
    MonthDelta & operator-=(const MonthDelta &);

    friend const MonthDelta operator+(const MonthDelta &, const MonthDelta &);
    friend const MonthDelta operator-(const MonthDelta &, const MonthDelta &);

    friend bool operator==(const MonthDelta &, const MonthDelta &);
    friend bool operator!=(const MonthDelta &, const MonthDelta &);

    friend bool operator<(const MonthDelta &, const MonthDelta &);
    friend bool operator<=(const MonthDelta &, const MonthDelta &);
    friend bool operator>(const MonthDelta &, const MonthDelta &);
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

PRESENT_API struct MonthDelta
MonthDelta_from_months(int_month_delta month_delta);

PRESENT_API struct MonthDelta
MonthDelta_from_years(int_year_delta year_delta);

PRESENT_API struct MonthDelta
MonthDelta_zero();

PRESENT_API int_month_delta
MonthDelta_get_months(const struct MonthDelta * const self);

PRESENT_API int_year_delta
MonthDelta_get_years(const struct MonthDelta * const self);

PRESENT_API bool
MonthDelta_is_negative(const struct MonthDelta * const self);

PRESENT_API void
MonthDelta_negate(struct MonthDelta * const self);

PRESENT_API double
MonthDelta_get_years_decimal(const struct MonthDelta * const self);

PRESENT_API void
MonthDelta_multiply_by(struct MonthDelta * const self, int scaleFactor);

PRESENT_API void
MonthDelta_divide_by(struct MonthDelta * const self, int scaleFactor);

PRESENT_API void
MonthDelta_add_month_delta(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToAdd);

PRESENT_API void
MonthDelta_subtract_month_delta(
        struct MonthDelta * const self,
        const struct MonthDelta * const monthDeltaToSubtract);

PRESENT_API bool
MonthDelta_equal(
        const struct MonthDelta * const,
        const struct MonthDelta * const);

PRESENT_API bool
MonthDelta_less_than(
        const struct MonthDelta * const,
        const struct MonthDelta * const);

PRESENT_API bool
MonthDelta_less_than_or_equal(
        const struct MonthDelta * const,
        const struct MonthDelta * const);

PRESENT_API bool
MonthDelta_greater_than(
        const struct MonthDelta * const,
        const struct MonthDelta * const);

PRESENT_API bool
MonthDelta_greater_than_or_equal(
        const struct MonthDelta * const,
        const struct MonthDelta * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_MONTH_DELTA_H_ */

