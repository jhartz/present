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

struct MonthDelta;

/*
 * C++ Class / C Struct Definition
 */

struct PRESENT_API Date {
    struct PresentDateData my_data;

#ifdef __cplusplus
    static Date create(int_year year);

    static Date create(int_year year, int_month month);

    static Date create(int_year year, int_month month, int_day day);

    static Date create_from_year_week(
        int_year year,
        int_week_of_year week_of_year);

    static Date create_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week);

    static Date today();

    static Date yesterday();

    static Date tomorrow();

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

    friend bool operator<(const Date &, const Date &);
    friend bool operator<=(const Date &, const Date &);
    friend bool operator>(const Date &, const Date &);
    friend bool operator>=(const Date &, const Date &);


    Date(const Date & other) : my_data(other.my_data) {}
    Date & operator=(const Date & other) {
        this->my_data = other.my_data;
        return *this;
    }

private:
    explicit Date(PresentDateData & data) : my_data(data) {}
    Date();
#endif
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

PRESENT_API
struct Date
    Date_create_from_year(
        int_year year);

PRESENT_API
struct Date
    Date_create_from_year_month(
        int_year year,
        int_month month);

PRESENT_API
struct Date
    Date_create_from_year_month_day(
        int_year year,
        int_month month,
        int_day day);

PRESENT_API
struct Date
    Date_create_from_year_week(
        int_year year,
        int_week_of_year week_of_year);

PRESENT_API
struct Date
    Date_create_from_year_week_day(
        int_year year,
        int_week_of_year week_of_year,
        int_day_of_week day_of_week);

#define Date_create(...)    \
    OVERLOAD_MAX_3(__VA_ARGS__, \
        Date_create_from_year_month_day,    \
        Date_create_from_year_month,    \
        Date_create_from_year)(__VA_ARGS__)

PRESENT_API
struct Date
    Date_today();

PRESENT_API
struct Date
    Date_yesterday();

PRESENT_API
struct Date
    Date_tomorrow();

PRESENT_API
int_year
    Date_get_year(
        const struct Date * const self);

PRESENT_API
int_month
    Date_get_month(
        const struct Date * const self);

PRESENT_API
int_day Date_get_day(
        const struct Date * const self);

PRESENT_API
int_day_of_year
    Date_get_day_of_year(
        const struct Date * const self);

PRESENT_API
int_week_of_year
    Date_get_week_of_year(
        const struct Date * const self);

PRESENT_API
int_day_of_week
    Date_get_day_of_week(
        const struct Date * const self);

PRESENT_API
void    Date_add_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta);

PRESENT_API
void    Date_subtract_month_delta(
        struct Date * const self,
        const struct MonthDelta * const delta);

PRESENT_API
bool    Date_equal(
        const struct Date * const,
        const struct Date * const);

PRESENT_API
bool    Date_less_than(
        const struct Date * const,
        const struct Date * const);

PRESENT_API
bool    Date_less_than_or_equal(
        const struct Date * const,
        const struct Date * const);

PRESENT_API
bool    Date_greater_than(
        const struct Date * const,
        const struct Date * const);

PRESENT_API
bool    Date_greater_than_or_equal(
        const struct Date * const,
        const struct Date * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_DATE_H_ */

