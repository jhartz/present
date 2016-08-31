/*
 * Present - Date/Time Library
 *
 * Tests for the ClockTime C++ class and C-compatible methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "catch.hpp"

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
 * tests the C "Date_create_..." methods).
 */
TEST_CASE("Date::create... methods", "[date]") {
    // create_from_year

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

    // create_from_year_month

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

    // create_from_year_month_day

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

    // create_from_year_day

    d = Date::create_from_year_day(2000, 1);
    IS(2000, 1, 1);
    d = Date::create_from_year_day(2000, 2);
    IS(2000, 1, 2);
    d = Date::create_from_year_day(2000, 31);
    IS(2000, 1, 31);
    d = Date::create_from_year_day(2000, 32);
    IS(2000, 2, 1);
    d = Date::create_from_year_day(2000, 60);
    IS(2000, 2, 29);
    d = Date::create_from_year_day(2000, 365);
    IS(2000, 12, 30);
    d = Date::create_from_year_day(2000, 366);
    IS(2000, 12, 31);

    // create_from_year_week

    // TODO

    // create_from_year_week_day

    // TODO
}
