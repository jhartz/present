/*
 * Present - Date/Time Library
 *
 * Definition of the Date structure and declarations of the corresponding
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

#include "present/internal/present-date-data.h"

#ifndef _PRESENT_DATE_H_
#define _PRESENT_DATE_H_

/*
 * Forward Declaraions
 */

struct DayDelta;
struct MonthDelta;

/*
 * Helper Struct Definitions
 */

/**
 * Struct containing a year and a week of the year.
 *
 * This is used as the return value for functions that return a week of the
 * year since a date's "week of the year" may be of a different year than the
 * date's actual year.
 */
struct PresentWeekYear {
    int_week_of_year week;
    int_year year;
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
    /**
     * This will be true if there were any errors when creating this Date.
     *
     * @copydoc has_error_epilogue
     */
    present_bool has_error;

    /**
     * If there were any errors when creating this Date, then one or more
     * of these fields will be set.
     *
     * @copydoc errors_epilogue
     */
    struct {
        unsigned int month_out_of_range         : 1,
                     day_out_of_range           : 1,
                     week_of_year_out_of_range  : 1,
                     day_of_week_out_of_range   : 1;
    } errors;

    /* Internal data representation */
    struct PresentDateData data_;

#ifdef __cplusplus
    /** @copydoc Date_from_year */
    static Date create(int_year year);

    /** @copydoc Date_from_year_month */
    static Date create(int_year year, int_month month);

    /** @copydoc Date_from_year_month_day */
    static Date create(int_year year, int_month month, int_day day);

    /** @copydoc Date_from_year_day */
    static Date from_year_day(
        int_year year,
        int_day_of_year day_of_year);

    /** @copydoc Date_from_year_week_day */
    static Date from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week);

    /** @copydoc Date_year */
    int_year year() const;

    /** @copydoc Date_month */
    int_month month() const;

    /** @copydoc Date_day */
    int_day day() const;

    /** @copydoc Date_day_of_year */
    int_day_of_year day_of_year() const;

    /** @copydoc Date_week_of_year */
    PresentWeekYear week_of_year() const;

    /** @copydoc Date_day_of_week */
    int_day_of_week day_of_week() const;

    /** @copydoc Date_difference */
    DayDelta difference(const Date & other) const;
    /** @copydoc Date_absolute_difference */
    DayDelta absolute_difference(const Date & other) const;

    /** @copydoc Date_add_DayDelta */
    Date & operator+=(const DayDelta & delta);
    /** @copydoc Date_add_MonthDelta */
    Date & operator+=(const MonthDelta & delta);
    /** @copydoc Date_subtract_DayDelta */
    Date & operator-=(const DayDelta & delta);
    /** @copydoc Date_subtract_MonthDelta */
    Date & operator-=(const MonthDelta & delta);

    /** @see Date::operator+=(const DayDelta & delta) */
    friend const Date operator+(const Date & lhs, const DayDelta & rhs);
    /** @see Date::operator+=(const DayDelta & delta) */
    friend const Date operator+(const DayDelta & lhs, const Date & rhs);

    /** @see Date::operator+=(const MonthDelta & delta) */
    friend const Date operator+(const Date & lhs, const MonthDelta & rhs);
    /** @see Date::operator+=(const MonthDelta & delta) */
    friend const Date operator+(const MonthDelta & lhs, const Date & rhs);

    /** @see Date::operator-=(const DayDelta & delta) */
    friend const Date operator-(const Date & lhs, const DayDelta & rhs);

    /** @see Date::operator-=(const MonthDelta & delta) */
    friend const Date operator-(const Date & lhs, const MonthDelta & rhs);

    /** @copydoc Date_compare */
    static int compare(const Date & lhs, const Date & rhs);

    /** @copydoc Date_equal */
    friend bool operator==(const Date & lhs, const Date & rhs);
    friend bool operator!=(const Date & lhs, const Date & rhs);

    /** @copydoc Date_less_than */
    friend bool operator<(const Date & lhs, const Date & rhs);
    /** @copydoc Date_less_than_or_equal */
    friend bool operator<=(const Date & lhs, const Date & rhs);
    /** @copydoc Date_greater_than */
    friend bool operator>(const Date & lhs, const Date & rhs);
    /** @copydoc Date_greater_than_or_equal */
    friend bool operator>=(const Date & lhs, const Date & rhs);
#endif
};

/*
 * C Method Declarations
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
Date_from_year(int_year year);

/**
 * @copydoc Date_from_year
 * @param[out] result A pointer to a struct Date for the result.
 */
PRESENT_API void
Date_ptr_from_year(struct Date * const result, int_year year);

/**
 * Create a new Date based on a year and a month. The day will be set to the
 * first of the month.
 *
 * If the month is out of range, the Date will have @p has_error and @p errors
 * set.
 *
 * @copydoc check_for_error_date
 *
 * @param year The year.
 * @param month The month of the year (1 to 12, inclusive).
 */
PRESENT_API struct Date
Date_from_year_month(int_year year, int_month month);

/**
 * @copydoc Date_from_year_month
 * @param[out] result A pointer to a struct Date for the result.
 */
PRESENT_API void
Date_ptr_from_year_month(
        struct Date * const result,
        int_year year,
        int_month month);

/**
 * Create a new Date based on a year, a month, and a day.
 *
 * If the month or the day is out of range, the Date will have @p has_error and
 * @p errors set.
 *
 * @copydoc check_for_error_date
 *
 * @param year The year.
 * @param month The month of the year (1 to 12, inclusive).
 * @param day The day of the month (1 to either 28, 29, 30, or 31, inclusive,
 * depending on the month).
 */
PRESENT_API struct Date
Date_from_year_month_day(int_year year, int_month month, int_day day);

/**
 * @copydoc Date_from_year_month_day
 * @param[out] result A pointer to a struct Date for the result.
 */
PRESENT_API void
Date_ptr_from_year_month_day(
        struct Date * const result,
        int_year year,
        int_month month,
        int_day day);

/**
 * Create a new Date from either a year (1 argument), a year and a month (2
 * arguments), or a year/month/day (3 arguments).
 *
 * @copydoc check_for_error_date
 *
 * @see Date_from_year
 * @see Date_from_year_month
 * @see Date_from_year_month_day
 */
#define Date_create(...)    \
    PRESENT_OVERLOAD_MAX_3(__VA_ARGS__, \
        Date_from_year_month_day,       \
        Date_from_year_month,           \
        Date_from_year,                 \
        dummy)(__VA_ARGS__)

/**
 * Create a new Date from either a year (2 arguments), a year and a month (3
 * arguments), or a year/month/day (4 arguments). The first argumen is a pointer
 * to a struct Date for the result.
 *
 * @copydoc check_for_error_date
 *
 * @see Date_ptr_from_year
 * @see Date_ptr_from_year_month
 * @see Date_ptr_from_year_month_day
 */
#define Date_ptr_create(result, ...)    \
    PRESENT_OVERLOAD_MAX_3(__VA_ARGS__, \
        Date_ptr_from_year_month_day,   \
        Date_ptr_from_year_month,       \
        Date_ptr_from_year,             \
        dummy)(result, __VA_ARGS__)

/**
 * Create a new Date based on a year and the day of that year.
 *
 * @param year The year.
 * @param day_of_year The day of the year.
 */
PRESENT_API struct Date
Date_from_year_day(int_year year, int_day_of_year day_of_year);

/**
 * @copydoc Date_from_year_day
 * @param[out] result A pointer to a struct Date for the result.
 */
PRESENT_API void
Date_ptr_from_year_day(
        struct Date * const result,
        int_year year,
        int_day_of_year day_of_year);

/**
 * Create a new Date based on a year, a week of that year, and a day of the
 * week. Weeks of the year are determined in the same way that the ISO8601
 * standard defines week numbers. For more info, see:
 * https://en.wikipedia.org/wiki/ISO_week_date
 *
 * If the week of the year or the day of the week is out of range, the Date will
 * have @p has_error and @p errors set.
 *
 * @copydoc check_for_error_date
 *
 * @param year The year.
 * @param week_of_year The week of the year (1 to 52 or 53, inclusive,
 * depending on the year).
 * @param day_of_week The day of the week (1 to 7, inclusive). See
 * present/internal/types.h for constants for each day of the week.
 */
PRESENT_API struct Date
Date_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week);

/**
 * @copydoc Date_from_year_week_day
 * @param[out] result A pointer to a struct Date for the result.
 */
PRESENT_API void
Date_ptr_from_year_week_day(
        struct Date * const result,
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week);

/**
 * Get the year of a Date.
 */
PRESENT_API int_year
Date_year(const struct Date * const self);

/**
 * Get the month of a Date (1 to 12, inclusive).
 */
PRESENT_API int_month
Date_month(const struct Date * const self);

/**
 * Get the day of month of a Date (1 to 31, inclusive).
 */
PRESENT_API int_day
Date_day(const struct Date * const self);

/**
 * Get the day of the year of a Date (1 to 366, inclusive).
 */
PRESENT_API int_day_of_year
Date_day_of_year(const struct Date * const self);

/**
 * Get the week of the year of a Date (1 to 53, inclusive), and the year
 * corresponding to that week.
 *
 * @see PresentWeekYear
 */
PRESENT_API struct PresentWeekYear
Date_week_of_year(const struct Date * const self);

/**
 * Get the day of the week of a Date (1 to 7, inclusive, with 1 being Monday,
 * 2 being Tuesday, ..., 6 being Saturday, and 7 being Sunday).
 */
PRESENT_API int_day_of_week
Date_day_of_week(const struct Date * const self);

/**
 * Get the difference between two Date instances.
 */
PRESENT_API struct DayDelta
Date_difference(
        const struct Date * const self,
        const struct Date * const other);

/**
 * Get the absolute difference between two Date instances.
 */
PRESENT_API struct DayDelta
Date_absolute_difference(
        const struct Date * const self,
        const struct Date * const other);

/**
 * Add a @ref DayDelta to a Date.
 */
PRESENT_API void
Date_add_DayDelta(
        struct Date * const self,
        const struct DayDelta * const delta);

/**
 * Add a @ref MonthDelta to a Date.
 */
PRESENT_API void
Date_add_MonthDelta(
        struct Date * const self,
        const struct MonthDelta * const delta);

/**
 * Subtract a @ref DayDelta from a Date.
 */
PRESENT_API void
Date_subtract_DayDelta(
        struct Date * const self,
        const struct DayDelta * const delta);

/**
 * Subtract a @ref MonthDelta from a Date.
 */
PRESENT_API void
Date_subtract_MonthDelta(
        struct Date * const self,
        const struct MonthDelta * const delta);

/**
 * Compare two Date instances.
 *
 * If lhs < rhs, then a negative integer will be returned.
 * If lhs == rhs, then 0 will be returned.
 * If lhs > rhs, then a positive integer will be returned.
 */
PRESENT_API int
Date_compare(
        const struct Date * const lhs,
        const struct Date * const rhs);

/**
 * Determine whether two Date instances are equal (lhs == rhs).
 */
PRESENT_API present_bool
Date_equal(const struct Date * const lhs, const struct Date * const rhs);

/**
 * Determine whether a Date is earlier than another Date (lhs < rhs).
 */
PRESENT_API present_bool
Date_less_than(const struct Date * const lhs, const struct Date * const rhs);

/**
 * Determine whether a Date is earlier than or the same as another Date
 * (lhs <= rhs).
 */
PRESENT_API present_bool
Date_less_than_or_equal(
        const struct Date * const lhs,
        const struct Date * const rhs);

/**
 * Determine whether a Date is later than another Date (lhs > rhs).
 */
PRESENT_API present_bool
Date_greater_than(
        const struct Date * const lhs,
        const struct Date * const rhs);

/**
 * Determine whether a Date is later than or the same as another Date
 * (lhs >= rhs).
 */
PRESENT_API present_bool
Date_greater_than_or_equal(
        const struct Date * const lhs,
        const struct Date * const rhs);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_DATE_H_ */

