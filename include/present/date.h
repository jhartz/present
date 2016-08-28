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

struct PRESENT_API Date {
    enum PresentDateError error;
    struct PresentDateData data_;

#ifdef __cplusplus
    static Date create(int_year year);

    static Date create(int_year year, int_month month);

    static Date create(int_year year, int_month month, int_day day);

    static Date create_from_year_day(
        int_year year,
        int_day_of_year day_of_year);

    static Date create_from_year_week(
        int_year year,
        int_week_of_year week_of_year);

    static Date create_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week);

    int_year get_year() const;

    int_month get_month() const;

    int_day get_day() const;

    int_day_of_year get_day_of_year() const;

    int_week_of_year get_week_of_year() const;

    int_day_of_week get_day_of_week() const;

    Date & operator+=(const DayDelta &);
    Date & operator+=(const MonthDelta &);
    Date & operator-=(const DayDelta &);
    Date & operator-=(const MonthDelta &);

    friend const Date operator+(const Date &, const DayDelta &);
    friend const Date operator+(const Date &, const MonthDelta &);
    friend const Date operator-(const Date &, const DayDelta &);
    friend const Date operator-(const Date &, const MonthDelta &);

    friend bool operator==(const Date &, const Date &);
    friend bool operator!=(const Date &, const Date &);

    friend bool operator<(const Date &, const Date &);
    friend bool operator<=(const Date &, const Date &);
    friend bool operator>(const Date &, const Date &);
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

