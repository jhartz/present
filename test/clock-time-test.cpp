/*
 * Present - Date/Time Library
 *
 * Tests for the ClockTime C++ class and C-compatible methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "catch.hpp"

#include "present/time-delta.h"

#include "present/clock-time.h"

/**
 * Shortcut macro to compare hour/minute/second/nanosecond all in one.
 * Expects that the ClockTime is "c".
 */
#define IS(test_hour, test_minute, test_second, test_nanosecond)    \
    REQUIRE(c.error == ClockTime_ERROR_NONE);                       \
    CHECK(c.data_.hour == test_hour);                             \
    CHECK(c.data_.minute == test_minute);                         \
    CHECK(c.data_.second == test_second);                         \
    CHECK(c.data_.nanosecond == test_nanosecond);


/**
 * This test case tests all the overloads of the "create" method (which also
 * tests the C "ClockTime_create_..." methods).
 */
TEST_CASE("ClockTime::create... methods", "[clock-time]") {
    // create_from_hour

    ClockTime c = ClockTime::create(0);
    IS(0, 0, 0, 0);
    c = ClockTime::create(1);
    IS(1, 0, 0, 0);
    c = ClockTime::create(23);
    IS(23, 0, 0, 0);
    c = ClockTime::create(24);  // 24:00 should go to 00:00
    IS(0, 0, 0, 0);
    c = ClockTime::create(25);
    REQUIRE(c.error == ClockTime_ERROR_HOUR_OUT_OF_RANGE);
    c = ClockTime::create(-1);
    REQUIRE(c.error == ClockTime_ERROR_HOUR_OUT_OF_RANGE);

    // create_from_hour_minute

    c = ClockTime::create(0, 0);
    IS(0, 0, 0, 0);
    c = ClockTime::create(0, 1);
    IS(0, 1, 0, 0);
    c = ClockTime::create(0, 59);
    IS(0, 59, 0, 0);
    c = ClockTime::create(0, 60);
    REQUIRE(c.error == ClockTime_ERROR_MINUTE_OUT_OF_RANGE);
    c = ClockTime::create(0, -1);
    REQUIRE(c.error == ClockTime_ERROR_MINUTE_OUT_OF_RANGE);

    // create_from_hour_minute_second

    c = ClockTime::create(0, 0, 0);
    IS(0, 0, 0, 0);
    c = ClockTime::create(0, 0, 1);
    IS(0, 0, 1, 0);
    c = ClockTime::create(0, 0, 59);
    IS(0, 0, 59, 0);
    c = ClockTime::create(0, 0, 60);    // leap second
    IS(0, 0, 60, 0);
    c = ClockTime::create(0, 0, 61);
    REQUIRE(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);
    c = ClockTime::create(0, 0, -1);
    REQUIRE(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);

    // create_from_hour_minute_second_nanosecond

    c = ClockTime::create(0, 0, 0, 0);
    IS(0, 0, 0, 0);
    c = ClockTime::create(0, 0, 0, 1);
    IS(0, 0, 0, 1);
    c = ClockTime::create(0, 0, 0, 999999999);
    IS(0, 0, 0, 999999999);
    c = ClockTime::create(0, 0, 0, 1000000000);
    REQUIRE(c.error == ClockTime_ERROR_NANOSECOND_OUT_OF_RANGE);
    c = ClockTime::create(0, 0, 0, -1);
    REQUIRE(c.error == ClockTime_ERROR_NANOSECOND_OUT_OF_RANGE);

    // ClockTime_create (macro - shortcut for C methods)

    c = ClockTime_create(5);
    IS(5, 0, 0, 0);
    c = ClockTime_create(5, 6);
    IS(5, 6, 0, 0);
    c = ClockTime_create(5, 6, 7);
    IS(5, 6, 7, 0);
    c = ClockTime_create(5, 6, 7, 8);
    IS(5, 6, 7, 8);

    // create_with_decimal_seconds

    c = ClockTime::create_with_decimal_seconds(1, 2, 3.0);
    IS(1, 2, 3, 0);
    c = ClockTime::create_with_decimal_seconds(1, 2, 3.5);
    IS(1, 2, 3, 500000000.0);
    c = ClockTime::create_with_decimal_seconds(1, 2, 59.9);
    IS(1, 2, 59, 900000000.0);
    c = ClockTime::create_with_decimal_seconds(1, 2, 60);   // leap second
    IS(1, 2, 60, 0);
    c = ClockTime::create_with_decimal_seconds(1, 2, 61);
    REQUIRE(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);
    c = ClockTime::create_with_decimal_seconds(1, 2, -1);
    REQUIRE(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);

    // midnight, noon

    c = ClockTime::midnight();
    IS(0, 0, 0, 0);
    c = ClockTime::noon();
    IS(12, 0, 0, 0);
}

TEST_CASE("ClockTime::get... functions", "[clock-time]") {
    ClockTime c1 = ClockTime::create(0, 0, 0, 0);
    ClockTime c2 = ClockTime::create(3, 5, 8, 400);

    CHECK(c1.get_hour() == 0);
    CHECK(c2.get_hour() == 3);

    CHECK(c1.get_minute() == 0);
    CHECK(c2.get_minute() == 5);

    CHECK(c1.get_second() == 0);
    CHECK(c2.get_second() == 8);

    CHECK(c1.get_nanosecond() == 0);
    CHECK(c2.get_nanosecond() == 400);

    CHECK(c1.get_second_decimal() == 0.0);
    CHECK(c2.get_second_decimal() == 8.0000004);
}

TEST_CASE("ClockTime::time_since_midnight function", "[clock-time]") {
    ClockTime c = ClockTime::create(0, 0, 0, 0);
    CHECK(c.time_since_midnight() == TimeDelta::zero());

    c = ClockTime::create(1, 15, 30);
    CHECK(c.time_since_midnight() == TimeDelta::from_seconds(4530));

    c = ClockTime::create(0, 0, 45, 7000);
    CHECK(c.time_since_midnight() == TimeDelta::from_nanoseconds(45000007000));
}

// Tests for items in the C++ class but not in the C-compatible methods
// (operator overloading)
