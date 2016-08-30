/*
 * Present - Date/Time Library
 *
 * Tests for the ClockTime C++ class and C-compatible methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "catch.hpp"

#include "present/clock-time.h"

/**
 * Shortcut macro to compare hour/minute/second/nanosecond all in one.
 * Expects that the ClockTime is "c".
 */
#define IS(test_hour, test_minute, test_second, test_nanosecond)    \
    REQUIRE(c.error == ClockTime_ERROR_NONE);                       \
    REQUIRE(c.data_.hour == test_hour);                             \
    REQUIRE(c.data_.minute == test_minute);                         \
    REQUIRE(c.data_.second == test_second);                         \
    REQUIRE(c.data_.nanosecond == test_nanosecond);

// Tests for the C-compatible methods
// (where most of the implementation is)

TEST_CASE("ClockTime_create... functions", "[clock-time]") {
    // ClockTime_create_from_hour

    ClockTime c = ClockTime_create_from_hour(0);
    IS(0, 0, 0, 0);
    c = ClockTime_create_from_hour(1);
    IS(1, 0, 0, 0);
    c = ClockTime_create_from_hour(23);
    IS(23, 0, 0, 0);
    c = ClockTime_create_from_hour(24); // 24:00 should go to 00:00
    IS(0, 0, 0, 0);
    c = ClockTime_create_from_hour(25);
    REQUIRE(c.error == ClockTime_ERROR_HOUR_OUT_OF_RANGE);
    c = ClockTime_create_from_hour(-1);
    REQUIRE(c.error == ClockTime_ERROR_HOUR_OUT_OF_RANGE);

    // ClockTime_create_from_hour_minute

    c = ClockTime_create_from_hour_minute(0, 0);
    IS(0, 0, 0, 0);
    c = ClockTime_create_from_hour_minute(0, 1);
    IS(0, 1, 0, 0);
    c = ClockTime_create_from_hour_minute(0, 59);
    IS(0, 59, 0, 0);
    c = ClockTime_create_from_hour_minute(0, 60);
    REQUIRE(c.error == ClockTime_ERROR_MINUTE_OUT_OF_RANGE);
    c = ClockTime_create_from_hour_minute(0, -1);
    REQUIRE(c.error == ClockTime_ERROR_MINUTE_OUT_OF_RANGE);

    // ClockTime_create_from_hour_minute_second

    c = ClockTime_create_from_hour_minute_second(0, 0, 0);
    IS(0, 0, 0, 0);
    c = ClockTime_create_from_hour_minute_second(0, 0, 1);
    IS(0, 0, 1, 0);
    c = ClockTime_create_from_hour_minute_second(0, 0, 59);
    IS(0, 0, 59, 0);
    c = ClockTime_create_from_hour_minute_second(0, 0, 60); // leap second
    IS(0, 0, 60, 0);
    c = ClockTime_create_from_hour_minute_second(0, 0, 61);
    REQUIRE(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);
    c = ClockTime_create_from_hour_minute_second(0, 0, -1);
    REQUIRE(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);

    // ClockTime_create_from_hour_minute_second_nanosecond

    c = ClockTime_create_from_hour_minute_second_nanosecond(0, 0, 0, 0);
    IS(0, 0, 0, 0);
    c = ClockTime_create_from_hour_minute_second_nanosecond(0, 0, 0, 1);
    IS(0, 0, 0, 1);
    c = ClockTime_create_from_hour_minute_second_nanosecond(0, 0, 0, 999999999);
    IS(0, 0, 0, 999999999);
    c = ClockTime_create_from_hour_minute_second_nanosecond(0, 0, 0, 1000000000);
    REQUIRE(c.error == ClockTime_ERROR_NANOSECOND_OUT_OF_RANGE);
    c = ClockTime_create_from_hour_minute_second_nanosecond(0, 0, 0, -1);
    REQUIRE(c.error == ClockTime_ERROR_NANOSECOND_OUT_OF_RANGE);

    // ClockTime_create (macro)

    c = ClockTime_create(5);
    IS(5, 0, 0, 0);
    c = ClockTime_create(5, 6);
    IS(5, 6, 0, 0);
    c = ClockTime_create(5, 6, 7);
    IS(5, 6, 7, 0);
    c = ClockTime_create(5, 6, 7, 8);
    IS(5, 6, 7, 8);

    // ClockTime_create_with_decimal_seconds

    c = ClockTime_create_with_decimal_seconds(1, 2, 3);
    IS(1, 2, 3, 0);
    c = ClockTime_create_with_decimal_seconds(1, 2, 3.5);
    IS(1, 2, 3, 500000000.0);
    c = ClockTime_create_with_decimal_seconds(1, 2, 59.9);
    IS(1, 2, 59, 900000000.0);
    c = ClockTime_create_with_decimal_seconds(1, 2, 60);    // leap second
    IS(1, 2, 60, 0);
    c = ClockTime_create_with_decimal_seconds(1, 2, 61);
    REQUIRE(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);
    c = ClockTime_create_with_decimal_seconds(1, 2, -1);
    REQUIRE(c.error == ClockTime_ERROR_SECOND_OUT_OF_RANGE);

    // ClockTime_midnight, ClockTime_noon

    c = ClockTime_midnight();
    IS(0, 0, 0, 0);
    c = ClockTime_noon();
    IS(12, 0, 0, 0);
}

// Tests for items in the C++ class but not in the C-compatible methods
// (operator overloading)
