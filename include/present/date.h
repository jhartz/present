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
    , Date_ERROR_MONTH_OUT_OF_RANGE
    , Date_ERROR_DAY_OUT_OF_RANGE
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
    /** @copydoc Date_create_from_year */
    static Date create(int_year year);

    /** @copydoc Date_create_from_year_month */
    static Date create(int_year year, int_month month);

    /** @copydoc Date_create_from_year_month_day */
    static Date create(int_year year, int_month month, int_day day);

    /** @copydoc Date_create_from_year_day */
    static Date create_from_year_day(
        int_year year,
        int_day_of_year day_of_year);

    /** @copydoc Date_create_from_year_week */
    static Date create_from_year_week(
        int_year year,
        int_week_of_year week_of_year);

    /** @copydoc Date_create_from_year_week_day */
    static Date create_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week);

    /** @copydoc Date_get_year */
    int_year get_year() const;

    /** @copydoc Date_get_month */
    int_month get_month() const;

    /** @copydoc Date_get_day */
    int_day get_day() const;

    /** @copydoc Date_get_day_of_year */
    int_day_of_year get_day_of_year() const;

    /** @copydoc Date_get_week_of_year */
    int_week_of_year get_week_of_year() const;

    /** @copydoc Date_get_day_of_week */
    int_day_of_week get_day_of_week() const;

    /** @copydoc Date_get_difference */
    DayDelta get_difference(const Date & other) const;
    /** @copydoc Date_get_absolute_difference */
    DayDelta get_absolute_difference(const Date & other) const;

    /** @copydoc Date_add_day_delta */
    Date & operator+=(const DayDelta &);
    /** @copydoc Date_add_month_delta */
    Date & operator+=(const MonthDelta &);
    /** @copydoc Date_subtract_day_delta */
    Date & operator-=(const DayDelta &);
    /** @copydoc Date_subtract_month_delta */
    Date & operator-=(const MonthDelta &);

    friend const Date operator+(const Date &, const DayDelta &);
    friend const Date operator+(const Date &, const MonthDelta &);
    friend const Date operator-(const Date &, const DayDelta &);
    friend const Date operator-(const Date &, const MonthDelta &);

    /** @copydoc Date_equal */
    friend bool operator==(const Date &, const Date &);
    friend bool operator!=(const Date &, const Date &);

    /** @copydoc Date_less_than */
    friend bool operator<(const Date &, const Date &);
    /** @copydoc Date_less_than_or_equal */
    friend bool operator<=(const Date &, const Date &);
    /** @copydoc Date_greater_than */
    friend bool operator>(const Date &, const Date &);
    /** @copydoc Date_greater_than_or_equal */
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

/**
 * Create a new Date based on a year. The month and day will be set to
 * January 1.
 *
 * @param year The year.
 */
PRESENT_API struct Date
Date_create_from_year(int_year year);

/**
 * Create a new Date based on a year and a month. The day will be set to the
 * first of the month.
 *
 * If the month is out of range, a Date will be returned with "error" set.
 *
 * @param year The year.
 * @param month The month of the year (1 to 12, inclusive).
 */
PRESENT_API struct Date
Date_create_from_year_month(int_year year, int_month month);

/**
 * Create a new Date based on a year, a month, and a day.
 *
 * If the month or the day is out of range, a Date will be returned with
 * "error" set.
 *
 * @param year The year.
 * @param month The month of the year (1 to 12, inclusive).
 * @param day The day of the month (1 to either 28, 29, 30, or 31, inclusive,
 * depending on the month).
 */
PRESENT_API struct Date
Date_create_from_year_month_day(int_year year, int_month month, int_day day);

/**
 * Create a new Date from either a year (1 argument), a year and a month (2
 * arguments), or a year/month/day (3 arguments).
 *
 * @see Date_create_from_year
 * @see Date_create_from_year_month
 * @see Date_create_from_year_month_day
 */
#define Date_create(...)    \
    PRESENT_OVERLOAD_MAX_3(__VA_ARGS__,     \
        Date_create_from_year_month_day,    \
        Date_create_from_year_month,        \
        Date_create_from_year,              \
        dummy)(__VA_ARGS__)

/**
 * Create a new Date based on a year and the day of that year.
 *
 * @param year The year.
 * @param day_of_year The day of the year.
 */
PRESENT_API struct Date
Date_create_from_year_day(int_year year, int_day_of_year day_of_year);

/**
 * Create a new Date based on a year and the week of that year. Weeks of the
 * year are determined in the same way that the ISO8601 standard determines
 * week numbers.
 *
 * If the week of the year is out of range, a Date will be returned with
 * "error" set.
 *
 * @param year The year.
 * @param week_of_year The week of the year (TODO: what are the bounds?)
 */
PRESENT_API struct Date
Date_create_from_year_week(int_year year, int_week_of_year week_of_year);

/**
 * Create a new Date based on a year, a week of that year, and a day of the
 * week. Weeks of the year are determined in the same way that the ISO8601
 * standard defines week numbers.
 *
 * If the week of the year or the day of the week is out of range, a Date will
 * be returned with "error" set.
 *
 * @param year The year.
 * @param week_of_year The week of the year (TODO: what are the bounds?)
 * @param day_of_week The day of the week (1 to 7, inclusive). See
 * present/utils/types.h for constants for each day of the week.
 */
PRESENT_API struct Date
Date_create_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week);

/**
 * Get the year of a Date.
 */
PRESENT_API int_year
Date_get_year(const struct Date * const self);

/**
 * Get the month of a Date (1 to 12, inclusive).
 */
PRESENT_API int_month
Date_get_month(const struct Date * const self);

/**
 * Get the day of month of a Date (1 to 31, inclusive).
 */
PRESENT_API int_day
Date_get_day(const struct Date * const self);

/**
 * Get the day of the year of a Date (1 to 366, inclusive).
 */
PRESENT_API int_day_of_year
Date_get_day_of_year(const struct Date * const self);

/**
 * Get the week of the year of a Date.
 * TODO: What are the bounds?
 */
PRESENT_API int_week_of_year
Date_get_week_of_year(const struct Date * const self);

/**
 * Get the day of the week of a Date (1 to 7, inclusive, with 1 being Monday,
 * 2 being Tuesday, ..., 6 being Saturday, and 7 being Sunday).
 */
PRESENT_API int_day_of_week
Date_get_day_of_week(const struct Date * const self);

/**
 * Get the difference between two Date instances.
 */
PRESENT_API struct DayDelta
Date_get_difference(
        const struct Date * const self,
        const struct Date * const other);

/**
 * Get the absolute difference between two Date instances.
 */
PRESENT_API struct DayDelta
Date_get_absolute_difference(
        const struct Date * const self,
        const struct Date * const other);

/**
 * Add a @ref DayDelta to a Date.
 */
PRESENT_API void
Date_add_day_delta(
        struct Date * const self,
        const struct DayDelta * const delta);

/**
 * Add a @ref MonthDelta to a Date.
 */
PRESENT_API void
Date_add_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta);

/**
 * Subtract a @ref DayDelta from a Date.
 */
PRESENT_API void
Date_subtract_day_delta(
        struct Date * const self,
        const struct DayDelta * const delta);

/**
 * Subtract a @ref MonthDelta from a Date.
 */
PRESENT_API void
Date_subtract_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta);

/**
 * Determine whether two Date instances are equal.
 */
PRESENT_API bool
Date_equal(const struct Date * const, const struct Date * const);

/**
 * Determine whether a Date is earlier than another Date.
 */
PRESENT_API bool
Date_less_than(const struct Date * const, const struct Date * const);

/**
 * Determine whether a Date is earlier than or the same as another Date.
 */
PRESENT_API bool
Date_less_than_or_equal(const struct Date * const, const struct Date * const);

/**
 * Determine whether a Date is later than another Date.
 */
PRESENT_API bool
Date_greater_than(const struct Date * const, const struct Date * const);

/**
 * Determine whether a Date is later than or the same as another Date.
 */
PRESENT_API bool
Date_greater_than_or_equal(
        const struct Date * const,
        const struct Date * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_DATE_H_ */

