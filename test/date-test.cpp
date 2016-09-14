/*
 * Present - Date/Time Library
 *
 * Tests for the ClockTime C++ class and C-compatible methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "catch.hpp"

#include "present/day-delta.h"

#include "present/date.h"

/**
 * Shortcut macro to compare year, month, and day all in one.
 * Expects that the Date is "d".
 */
#define IS(test_year, test_month, test_day) \
    REQUIRE(d.error == Date_ERROR_NONE);    \
    CHECK(d.data_.year == test_year);       \
    CHECK(d.data_.month == test_month);     \
    CHECK(d.data_.day == test_day);

/**
 * This test case tests all the overloads of the "create" method (which also
 * tests the C "Date_from_..." functions).
 */
TEST_CASE("Date creators", "[date]") {
    // from_year

    Date d = Date::create(0);
    IS(0, 1, 1);
    d = Date::create(1);
    IS(1, 1, 1);
    d = Date::create(1999);
    IS(1999, 1, 1);
    d = Date::create(2003);
    IS(2003, 1, 1);
    d = Date::create(2040);
    IS(2040, 1, 1);
    d = Date::create(9999);
    IS(9999, 1, 1);

    // from_year_month

    d = Date::create(1999, 1);
    IS(1999, 1, 1);
    d = Date::create(1999, 2);
    IS(1999, 2, 1);
    d = Date::create(1999, 12);
    IS(1999, 12, 1);
    d = Date::create(1999, 13);
    CHECK(d.error == Date_ERROR_MONTH_OUT_OF_RANGE);
    d = Date::create(1999, 0);
    CHECK(d.error == Date_ERROR_MONTH_OUT_OF_RANGE);

    // from_year_month_day

    d = Date::create(1999, 1, 1);
    IS(1999, 1, 1);
    d = Date::create(1999, 1, 2);
    IS(1999, 1, 2);
    d = Date::create(1999, 1, 0);
    CHECK(d.error == Date_ERROR_DAY_OUT_OF_RANGE);
    // Jan.
    d = Date::create(1999, 1, 31);
    IS(1999, 1, 31);
    d = Date::create(1999, 1, 32);
    CHECK(d.error == Date_ERROR_DAY_OUT_OF_RANGE);
    // Feb. (without and with leap years)
    d = Date::create(1999, 2, 28);
    IS(1999, 2, 28);
    d = Date::create(1999, 2, 29);
    CHECK(d.error == Date_ERROR_DAY_OUT_OF_RANGE);
    d = Date::create(2000, 2, 28);
    IS(2000, 2, 28);
    d = Date::create(2000, 2, 29);
    IS(2000, 2, 29);
    d = Date::create(2000, 2, 30);
    CHECK(d.error == Date_ERROR_DAY_OUT_OF_RANGE);
    // Apr.
    d = Date::create(1999, 4, 30);
    IS(1999, 4, 30);
    d = Date::create(1999, 4, 31);
    CHECK(d.error == Date_ERROR_DAY_OUT_OF_RANGE);

    // from_year_day

    d = Date::from_year_day(2000, 1);
    IS(2000, 1, 1);
    d = Date::from_year_day(2000, 2);
    IS(2000, 1, 2);
    d = Date::from_year_day(2000, 31);
    IS(2000, 1, 31);
    d = Date::from_year_day(2000, 32);
    IS(2000, 2, 1);
    d = Date::from_year_day(2000, 60);
    IS(2000, 2, 29);
    d = Date::from_year_day(2000, 365);
    IS(2000, 12, 30);
    d = Date::from_year_day(2000, 366);
    IS(2000, 12, 31);

    // from_year_week_day
    // Each of these has a matching test for week_of_year and
    // day_of_week down in the "week_of_year and day_of_week
    // edge cases" test case.

    d = Date::from_year_week_day(2016, 31, DAY_OF_WEEK_WEDNESDAY);
    IS(2016, 8, 3);

    // In 2004, the first week of the year started in the end of 2003
    d = Date::from_year_week_day(2004, 1, DAY_OF_WEEK_MONDAY);
    IS(2003, 12, 29);

    // But not in 2007
    d = Date::from_year_week_day(2007, 1, DAY_OF_WEEK_MONDAY);
    IS(2007, 1, 1);

    // The last week of 2005 was week 52
    d = Date::from_year_week_day(2005, 52, DAY_OF_WEEK_MONDAY);
    IS(2005, 12, 26);

    // It rolls over into 2006
    d = Date::from_year_week_day(2005, 52, DAY_OF_WEEK_SUNDAY);
    IS(2006, 1, 1);

    // Even if we use the wrong Sunday
    d = Date::from_year_week_day(2005, 52, DAY_OF_WEEK_SUNDAY_COMPAT);
    IS(2006, 1, 1);

    // 2005 didn't have a week 53
    d = Date::from_year_week_day(2005, 53, DAY_OF_WEEK_MONDAY);
    CHECK(d.error == Date_ERROR_WEEK_OF_YEAR_OUT_OF_RANGE);

    // 2009 did, though
    d = Date::from_year_week_day(2009, 53, DAY_OF_WEEK_MONDAY);
    IS(2009, 12, 28);

    // And it rolls over into 2010
    d = Date::from_year_week_day(2009, 53, DAY_OF_WEEK_FRIDAY);
    IS(2010, 1, 1);

    // But 2009 didn't have a week 54
    d = Date::from_year_week_day(2009, 54, DAY_OF_WEEK_MONDAY);
    CHECK(d.error == Date_ERROR_WEEK_OF_YEAR_OUT_OF_RANGE);

    // 1992 has a week 53, and it was a leap year starting on Wed.
    // It also spilled over into 1993
    d = Date::from_year_week_day(1992, 53, DAY_OF_WEEK_SUNDAY);
    IS(1993, 1, 3);

    // 1995 started on a Sunday, and does not have 53 weeks
    d = Date::from_year_week_day(1995, 53, DAY_OF_WEEK_MONDAY);
    CHECK(d.error == Date_ERROR_WEEK_OF_YEAR_OUT_OF_RANGE);

    // And nobody should have weeks less than 1
    d = Date::from_year_week_day(1999, 0, DAY_OF_WEEK_MONDAY);
    CHECK(d.error == Date_ERROR_WEEK_OF_YEAR_OUT_OF_RANGE);
    d = Date::from_year_week_day(1999, -1, DAY_OF_WEEK_MONDAY);
    CHECK(d.error == Date_ERROR_WEEK_OF_YEAR_OUT_OF_RANGE);

    // Nor days of the week outside 0 to 7
    d = Date::from_year_week_day(2007, 1, 8);
    CHECK(d.error == Date_ERROR_DAY_OF_WEEK_OUT_OF_RANGE);
    d = Date::from_year_week_day(2007, 1, -1);
    CHECK(d.error == Date_ERROR_DAY_OF_WEEK_OUT_OF_RANGE);
}

TEST_CASE("Date accessors", "[date]") {
    Date d1 = Date::create(1857, 1, 1);
    Date d2 = Date::create(2011, 4, 19);
    Date d3 = Date::create(2000, 2, 29);
    Date d4 = Date::create(2000, 3, 1);
    Date d5 = Date::create(1995, 1, 1);

    // Check year
    CHECK(d1.year() == 1857);
    CHECK(d2.year() == 2011);
    CHECK(d3.year() == 2000);
    CHECK(d4.year() == 2000);
    CHECK(d5.year() == 1995);

    // Check month
    CHECK(d1.month() == 1);
    CHECK(d2.month() == 4);
    CHECK(d3.month() == 2);
    CHECK(d4.month() == 3);
    CHECK(d5.month() == 1);

    // Check day
    CHECK(d1.day() == 1);
    CHECK(d2.day() == 19);
    CHECK(d3.day() == 29);
    CHECK(d4.day() == 1);
    CHECK(d5.day() == 1);

    // Check day_of_year
    CHECK(d1.day_of_year() == 1);
    CHECK(d2.day_of_year() == 109);
    CHECK(d3.day_of_year() == 60);
    CHECK(d4.day_of_year() == 61);
    CHECK(d5.day_of_year() == 1);

    // Check week_of_year
    PresentWeekYear weekyear;

    weekyear = d1.week_of_year();
    CHECK(weekyear.week == 1);
    CHECK(weekyear.year == 1857);

    weekyear = d2.week_of_year();
    CHECK(weekyear.week == 16);
    CHECK(weekyear.year == 2011);

    weekyear = d3.week_of_year();
    CHECK(weekyear.week == 9);
    CHECK(weekyear.year == 2000);

    weekyear = d4.week_of_year();
    CHECK(weekyear.week == 9);
    CHECK(weekyear.year == 2000);

    weekyear = d5.week_of_year();
    CHECK(weekyear.week == 52);
    CHECK(weekyear.year == 1994);

    // Check day_of_week
    CHECK(d1.day_of_week() == DAY_OF_WEEK_THURSDAY);
    CHECK(d2.day_of_week() == DAY_OF_WEEK_TUESDAY);
    CHECK(d3.day_of_week() == DAY_OF_WEEK_TUESDAY);
    CHECK(d4.day_of_week() == DAY_OF_WEEK_WEDNESDAY);
    CHECK(d5.day_of_week() == DAY_OF_WEEK_SUNDAY);
}

TEST_CASE("Date 'week_of_year' and 'day_of_week' edge cases",
          "[date]") {
    // More tests for week_of_year and day_of_week
    // (all of these match the tests for from_year_week_day; see that section
    // for explanations of each)
    Date d = Date::create(2016, 8, 3);
    CHECK(d.week_of_year().week == 31);
    CHECK(d.week_of_year().year == 2016);
    CHECK(d.day_of_week() == DAY_OF_WEEK_WEDNESDAY);

    d = Date::create(2003, 12, 29);
    CHECK(d.week_of_year().week == 1);
    CHECK(d.week_of_year().year == 2004);
    CHECK(d.day_of_week() == DAY_OF_WEEK_MONDAY);

    d = Date::create(2007, 1, 1);
    CHECK(d.week_of_year().week == 1);
    CHECK(d.week_of_year().year == 2007);
    CHECK(d.day_of_week() == DAY_OF_WEEK_MONDAY);

    d = Date::create(2005, 12, 26);
    CHECK(d.week_of_year().week == 52);
    CHECK(d.week_of_year().year == 2005);
    CHECK(d.day_of_week() == DAY_OF_WEEK_MONDAY);

    d = Date::create(2006, 1, 1);
    CHECK(d.week_of_year().week == 52);
    CHECK(d.week_of_year().year == 2005);
    CHECK(d.day_of_week() == DAY_OF_WEEK_SUNDAY);

    d = Date::create(2009, 12, 28);
    CHECK(d.week_of_year().week == 53);
    CHECK(d.week_of_year().year == 2009);
    CHECK(d.day_of_week() == DAY_OF_WEEK_MONDAY);

    d = Date::create(2010, 1, 1);
    CHECK(d.week_of_year().week == 53);
    CHECK(d.week_of_year().year == 2009);
    CHECK(d.day_of_week() == DAY_OF_WEEK_FRIDAY);

    d = Date::create(1993, 1, 3);
    CHECK(d.week_of_year().week == 53);
    CHECK(d.week_of_year().year == 1992);
    CHECK(d.day_of_week() == DAY_OF_WEEK_SUNDAY);
}

TEST_CASE("Date 'difference' functions", "[date]") {
    Date d1 = Date::create(2010, 1, 1);
    Date d2 = Date::create(2010, 1, 2);

    DayDelta exp_diff = DayDelta::from_days(1);
    CHECK(d1.difference(d2) == -exp_diff);
    CHECK(d2.difference(d1) == exp_diff);
    CHECK(d1.absolute_difference(d2) == exp_diff);
    CHECK(d2.absolute_difference(d1) == exp_diff);
}
