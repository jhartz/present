/*
 * Present - Date/Time Library
 *
 * Definition of the Date structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-date-data.h"

#ifndef _PRESENT_DATE_H_
#define _PRESENT_DATE_H_

/*
 * Forward Declaraions
 */

struct DayDelta;
struct MonthDelta;

/*
 * Enum Definitions
 */

enum PresentDateError {
    Date_ERROR_NONE = 0
    , Date_ERROR_YEAR_OUT_OF_RANGE
    , Date_ERROR_MONTH_OUT_OF_RANGE
    , Date_ERROR_DAY_OUT_OF_RANGE
    , Date_ERROR_DAY_OF_YEAR_OUT_OF_RANGE
    , Date_ERROR_WEEK_OF_YEAR_OUT_OF_RANGE
    , Date_ERROR_DAY_OF_WEEK_OUT_OF_RANGE
};

/*
 * C++ Class / C Struct Definition
 */

/**
 * Class or struct representing a calendar date.
 *
 * This includes a year, a month, and a day. There is no time-of-day stored
 * with the date, nor a time zone.
 */
struct PRESENT_API Date {
    enum PresentDateError error;
    struct PresentDateData data_;

#ifdef __cplusplus
    /** @see Date_create_from_year */
    static Date create(int_year year);

    /** @see Date_create_from_year_month */
    static Date create(int_year year, int_month month);

    /** @see Date_create_from_year_month_day */
    static Date create(int_year year, int_month month, int_day day);

    /** @see Date_create_from_year_day */
    static Date create_from_year_day(
        int_year year,
        int_day_of_year day_of_year);

    /** @see Date_create_from_year_week */
    static Date create_from_year_week(
        int_year year,
        int_week_of_year week_of_year);

    /** @see Date_create_from_year_week_day */
    static Date create_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week);

    /** @see Date_get_year */
    int_year get_year() const;

    /** @see Date_get_month */
    int_month get_month() const;

    /** @see Date_get_day */
    int_day get_day() const;

    /** @see Date_get_day_of_year */
    int_day_of_year get_day_of_year() const;

    /** @see Date_get_week_of_year */
    int_week_of_year get_week_of_year() const;

    /** @see Date_get_day_of_week */
    int_day_of_week get_day_of_week() const;

    /** @see Date_get_difference */
    DayDelta get_difference(const Date & other) const;
    /** @see Date_get_absolute_difference */
    DayDelta get_absolute_difference(const Date & other) const;

    /** @see Date_add_day_delta */
    Date & operator+=(const DayDelta &);
    /** @see Date_add_month_delta */
    Date & operator+=(const MonthDelta &);
    /** @see Date_subtract_day_delta */
    Date & operator-=(const DayDelta &);
    /** @see Date_subtract_month_delta */
    Date & operator-=(const MonthDelta &);

    friend const Date operator+(const Date &, const DayDelta &);
    friend const Date operator+(const Date &, const MonthDelta &);
    friend const Date operator-(const Date &, const DayDelta &);
    friend const Date operator-(const Date &, const MonthDelta &);

    /** @see Date_equal */
    friend bool operator==(const Date &, const Date &);
    friend bool operator!=(const Date &, const Date &);

    /** @see Date_less_than */
    friend bool operator<(const Date &, const Date &);
    /** @see Date_less_than_or_equal */
    friend bool operator<=(const Date &, const Date &);
    /** @see Date_greater_than */
    friend bool operator>(const Date &, const Date &);
    /** @see Date_greater_than_or_equal */
    friend bool operator>=(const Date &, const Date &);

    PRESENT_BOILERPLATE_CONSTRUCTORS(Date)
#endif
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

PRESENT_API struct Date
Date_create_from_year(int_year year);

PRESENT_API struct Date
Date_create_from_year_month(int_year year, int_month month);

PRESENT_API struct Date
Date_create_from_year_month_day(int_year year, int_month month, int_day day);

#define Date_create(...)    \
    PRESENT_OVERLOAD_MAX_3(__VA_ARGS__, \
        Date_create_from_year_month_day,    \
        Date_create_from_year_month,    \
        Date_create_from_year)(__VA_ARGS__)

PRESENT_API struct Date
Date_create_from_year_day(int_year year, int_day_of_year day_of_year);

PRESENT_API struct Date
Date_create_from_year_week(int_year year, int_week_of_year week_of_year);

PRESENT_API struct Date
Date_create_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week);

PRESENT_API int_year
Date_get_year(const struct Date * const self);

PRESENT_API int_month
Date_get_month(const struct Date * const self);

PRESENT_API int_day
Date_get_day(const struct Date * const self);

PRESENT_API int_day_of_year
Date_get_day_of_year(const struct Date * const self);

PRESENT_API int_week_of_year
Date_get_week_of_year(const struct Date * const self);

PRESENT_API int_day_of_week
Date_get_day_of_week(const struct Date * const self);

PRESENT_API struct DayDelta
Date_get_difference(
        const struct Date * const self,
        const struct Date * const other);

PRESENT_API struct DayDelta
Date_get_absolute_difference(
        const struct Date * const self,
        const struct Date * const other);

PRESENT_API void
Date_add_day_delta(
        struct Date * const self,
        const struct DayDelta * const delta);

PRESENT_API void
Date_add_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta);

PRESENT_API void
Date_subtract_day_delta(
        struct Date * const self,
        const struct DayDelta * const delta);

PRESENT_API void
Date_subtract_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta);

PRESENT_API bool
Date_equal(const struct Date * const, const struct Date * const);

PRESENT_API bool
Date_less_than(const struct Date * const, const struct Date * const);

PRESENT_API bool
Date_less_than_or_equal(const struct Date * const, const struct Date * const);

PRESENT_API bool
Date_greater_than(const struct Date * const, const struct Date * const);

PRESENT_API bool
Date_greater_than_or_equal(
        const struct Date * const,
        const struct Date * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_DATE_H_ */

