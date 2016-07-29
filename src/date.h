/*
 * Present - Date/Time Library
 *
 * Definition of the Date structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "types.h"
#include "util.h"
#include "impl/date-data.h"

#ifndef _PRESENT_DATE_H_
#define _PRESENT_DATE_H_

/*
 * Forward Declaraions
 */
struct MonthDelta;

/*
 * C++ Class / C Struct Definition
 */

struct Date {
#ifdef __cplusplus
    static Date create(int_year year);

    static Date create(int_year year, int_month month);

    static Date create(int_year year, int_month month, int_day day);

    static Date create_from_year_week(int_year year, int_week_of_year week_of_year);

    static Date create_from_year_week_day(int_year year, int_week_of_year week_of_year, int_day_of_week day_of_week);

    int_year get_year() const;

    int_month get_month() const;

    int_day get_day() const;

    int_day_of_year get_day_of_year() const;

    int_week_of_year get_week_of_year() const;

    int_day_of_week get_day_of_week() const;

    Date & operator+=(const MonthDelta &);
    Date & operator-=(const MonthDelta &);

    friend const Date operator+(const Date &, const MonthDelta &);
    friend const Date operator-(const Date &, const MonthDelta &);

    friend bool operator==(const Date &, const Date &);
    friend bool operator!=(const Date &, const Date &);

    Date(const Date &);
    Date & operator=(const Date &);

private:
    Date();
#endif

    struct DateData my_data;
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

struct Date
Date_create_from_year(
        int_year    year);

struct Date
Date_create_from_year_month(
        int_year    year,
        int_month   month);

struct Date
Date_create_from_year_month_day(
        int_year    year,
        int_month   month,
        int_day     day);

struct Date
Date_create_from_year_week(
        int_year    year,
        int_week_of_year    week_of_year);

struct Date
Date_create_from_year_week_day(
        int_year    year,
        int_week_of_year    week_of_year,
        int_day_of_week     day_of_week);

#define Date_create(...)    \
    OVERLOAD_MAX_3(__VA_ARGS__, \
            Date_create_from_year_month_day,    \
            Date_create_from_year_month,    \
            Date_create_from_year)(__VA_ARGS__)

int_year
Date_get_year(struct Date date);

int_month
Date_get_month(struct Date date);

int_day
Date_get_day(struct Date date);

int_day_of_year
Date_get_day_of_year(struct Date date);

int_week_of_year
Date_get_week_of_year(struct Date date);

int_day_of_week
Date_get_day_of_week(struct Date date);

void
Date_add_month_delta(struct Date * const date, const struct MonthDelta * const delta);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_DATE_H_ */

