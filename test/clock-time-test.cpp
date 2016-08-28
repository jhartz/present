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

// Tests for the C-compatible methods
// (where most of the implementation is)

TEST_CASE("ClockTime create from hour", "[clock-time]") {
    ClockTime c = ClockTime_create_from_hour(0);
    REQUIRE(c.error == ClockTime_ERROR_NONE);
    REQUIRE(c.data_.hour == 0);
    REQUIRE(c.data_.minute == 0);
    REQUIRE(c.data_.second == 0);
    REQUIRE(c.data_.nanosecond == 0);

    c = ClockTime_create_from_hour(1);
    REQUIRE(c.error == ClockTime_ERROR_NONE);
    REQUIRE(c.data_.hour == 1);
    REQUIRE(c.data_.minute == 0);
    REQUIRE(c.data_.second == 0);
    REQUIRE(c.data_.nanosecond == 0);

    c = ClockTime_create_from_hour(23);
    REQUIRE(c.error == ClockTime_ERROR_NONE);
    REQUIRE(c.data_.hour == 23);
    REQUIRE(c.data_.minute == 0);
    REQUIRE(c.data_.second == 0);
    REQUIRE(c.data_.nanosecond == 0);

    // Special exception... 24:00 should go to 00:00
    c = ClockTime_create_from_hour(24);
    REQUIRE(c.error == ClockTime_ERROR_NONE);
    REQUIRE(c.data_.hour == 0);
    REQUIRE(c.data_.minute == 0);
    REQUIRE(c.data_.second == 0);
    REQUIRE(c.data_.nanosecond == 0);

    // Out-of-bounds
    c = ClockTime_create_from_hour(25);
    REQUIRE(c.error == ClockTime_ERROR_HOUR_OUT_OF_RANGE);

    c = ClockTime_create_from_hour(-1);
    REQUIRE(c.error == ClockTime_ERROR_HOUR_OUT_OF_RANGE);
}

// Tests for items in the C++ class but not in the C-compatible methods
// (operator overloading)
