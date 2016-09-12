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
 * Shortcut macro to compare seconds and nanoseconds all in one.
 * Expects that the ClockTime is "c".
 */
#define IS(test_seconds, test_nanoseconds)          \
    REQUIRE(c.error == ClockTime_ERROR_NONE);       \
    CHECK(c.data_.seconds == test_seconds);         \
    CHECK(c.data_.nanoseconds == test_nanoseconds);

/**
 * Shortcut macro to compare hour/minute/second/nanosecond.
 * Expects that the ClockTime is "c".
 */
#define IS_HMS(test_hour, test_minute, test_second, test_nanosecond)    \
    REQUIRE(c.error == ClockTime_ERROR_NONE);                           \
    CHECK(c.data_.seconds == test_hour*3600 +                           \
            test_minute*60 + test_second);                              \
    CHECK(c.data_.nanoseconds == test_nanosecond);


/**
 * This test case tests all the overloads of the "create" method (which also
 * tests the C "ClockTime_from_..." methods).
 */
TEST_CASE("ClockTime::create... methods", "[clock-time]") {
    // from_hour

    ClockTime c = ClockTime::create(0);
    IS_HMS(0, 0, 0, 0);
    c = ClockTime::create(1);
    IS_HMS(1, 0, 0, 0);
    c = ClockTime::create(23);
    IS_HMS(23, 0, 0, 0);
    c = ClockTime::create(24);  // 24:00 should go to 00:00
    IS_HMS(0, 0, 0, 0);
    c = ClockTime::create(25);
    CHECK(c.error == ClockTime_ERROR_HOUR_OUT_OF_RANGE);
    c = ClockTime::create(-1);
    CHECK(c.error == ClockTime_ERROR_HOUR_OUT_OF_RANGE);

    // from_hour_minute

    c = ClockTime::create(0, 0);
    IS_HMS(0, 0, 0, 0);
    c = ClockTime::create(0, 1);
    IS_HMS(0, 1, 0, 0);
    c = ClockTime::create(0, 59);
    IS_HMS(0, 59, 0, 0);
    c = ClockTime::create(0, 60);
    CHECK(c.error == ClockTime_ERROR_MINUTE_OUT_OF_RANGE);
    c = ClockTime::create(0, -1);
    CHECK(c.error == ClockTime_ERROR_MINUTE_OUT_OF_RANGE);

    // from_hour_minute_second

    c = ClockTime::create(0, 0, 0);
    IS_HMS(0, 0, 0, 0);
    c = ClockTime::create(0, 0, 1);
    IS_HMS(0, 0, 1, 0);
    c = ClockTime::create(0, 0, 59);
    IS_HMS(0, 0, 59, 0);
    c = ClockTime::create(0, 0, 60);    // leap second
    IS_HMS(0, 0, 60, 0);
    c = ClockTime::create(0, 0, 61);
    CHECK(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);
    c = ClockTime::create(0, 0, -1);
    CHECK(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);

    // from_hour_minute_second_nanosecond

    c = ClockTime::create(0, 0, 0, 0);
    IS_HMS(0, 0, 0, 0);
    c = ClockTime::create(0, 0, 0, 1);
    IS_HMS(0, 0, 0, 1);
    c = ClockTime::create(0, 0, 0, 999999999);
    IS_HMS(0, 0, 0, 999999999);
    c = ClockTime::create(0, 0, 0, 1000000000);
    CHECK(c.error == ClockTime_ERROR_NANOSECOND_OUT_OF_RANGE);
    c = ClockTime::create(0, 0, 0, -1);
    CHECK(c.error == ClockTime_ERROR_NANOSECOND_OUT_OF_RANGE);

    // ClockTime_create (macro - shortcut for C methods)

    c = ClockTime_create(5);
    IS_HMS(5, 0, 0, 0);
    c = ClockTime_create(5, 6);
    IS_HMS(5, 6, 0, 0);
    c = ClockTime_create(5, 6, 7);
    IS_HMS(5, 6, 7, 0);
    c = ClockTime_create(5, 6, 7, 8);
    IS_HMS(5, 6, 7, 8);

    // create_with_decimal_seconds

    c = ClockTime::create_with_decimal_seconds(1, 2, 3.0);
    IS_HMS(1, 2, 3, 0);
    c = ClockTime::create_with_decimal_seconds(1, 2, 3.5);
    IS_HMS(1, 2, 3, 500000000.0);
    c = ClockTime::create_with_decimal_seconds(1, 2, 59.9);
    IS_HMS(1, 2, 59, 900000000.0);
    c = ClockTime::create_with_decimal_seconds(1, 2, 60);   // leap second
    IS_HMS(1, 2, 60, 0);
    c = ClockTime::create_with_decimal_seconds(1, 2, 61);
    CHECK(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);
    c = ClockTime::create_with_decimal_seconds(1, 2, -1);
    CHECK(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);

    // midnight, noon

    c = ClockTime::midnight();
    IS_HMS(0, 0, 0, 0);
    c = ClockTime::noon();
    IS_HMS(12, 0, 0, 0);
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

TEST_CASE("ClockTime arithmetic operators", "[clock-time]") {
    TimeDelta d = TimeDelta::from_hours(2) + TimeDelta::from_minutes(4) +
        TimeDelta::from_seconds(6);

    ClockTime c = ClockTime::create(1, 3, 5, 0);
    c += d;
    IS_HMS(3, 7, 11, 0);

    c = ClockTime::create(10, 10, 10, 0);
    c -= d;
    IS_HMS(8, 6, 4, 0);

    c = ClockTime::create(10, 10, 10, 0);
    ClockTime c1 = c + d;
    ClockTime c2 = c - d;
    IS_HMS(10, 10, 10, 0);
    c = c1;
    IS_HMS(12, 14, 16, 0);
    c = c2;
    IS_HMS(8, 6, 4, 0);

    // Testing nanoseconds spilling into seconds
    c = ClockTime::create(0, 0, 0, 999999998);
    TimeDelta d2 = TimeDelta::from_nanoseconds(5);
    c += d2;
    IS_HMS(0, 0, 1, 3);

    c = ClockTime::create(0, 0, 1, 2);
    c -= d2;
    IS_HMS(0, 0, 0, 999999997);

    // Testing wrap-around
    c = ClockTime::create(23, 0, 0, 0);
    d = TimeDelta::from_hours(1);
    c += d;
    IS_HMS(0, 0, 0, 0);

    c = ClockTime::create(1, 0, 0, 0);
    d = TimeDelta::from_hours(2);
    c -= d;
    IS_HMS(23, 0, 0, 0);
}

TEST_CASE("ClockTime comparison operators", "[clock-time]") {
    ClockTime c1 = ClockTime::create(0, 0, 0, 0),
              c2 = ClockTime::create(0, 0, 0, 1),
              c3 = ClockTime::create(12, 13, 14, 15),
              c4 = ClockTime::create(12, 13, 14, 15);

    CHECK(c3 == c4);
    CHECK(!(c1 == c3));
    CHECK(c1 != c3);
    CHECK(c1 != c2);

    CHECK(c1 < c2);
    CHECK(c1 < c3);
    CHECK(c2 < c3);

    CHECK(c1 <= c2);
    CHECK(c1 <= c3);
    CHECK(c2 <= c3);
    CHECK(c3 <= c4);
    CHECK(c4 <= c3);

    CHECK(c2 > c1);
    CHECK(c3 > c1);
    CHECK(c3 > c2);

    CHECK(c2 >= c1);
    CHECK(c3 >= c1);
    CHECK(c3 >= c2);
    CHECK(c4 >= c3);
    CHECK(c3 >= c4);
}

