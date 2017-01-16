/*
 * Present - Date/Time Library
 *
 * Tests for the ClockTime C++ class and C-compatible methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "catch.hpp"

#include "present.h"

/**
 * Shortcut macro to compare hour/minute/second/nanosecond.
 * Expects that the ClockTime is "c".
 */
#define IS(test_hour, test_minute, test_second, test_nanosecond)    \
    REQUIRE_FALSE(c.has_error);                                     \
    CHECK(c.data_.seconds == test_hour*3600 +                       \
            test_minute*60 + test_second);                          \
    CHECK(c.data_.nanoseconds == test_nanosecond);

/**
 * Shortcut macro to check if there's a certain error.
 * Expects that the ClockTime is "c".
 */
#define IS_ERROR(eRR_tYPE)      \
    CHECK(c.has_error);         \
    CHECK(c.errors.eRR_tYPE);


/**
 * This test case tests all the overloads of the "create" method (which also
 * tests the C "ClockTime_from_..." methods).
 */
TEST_CASE("ClockTime creators", "[clock-time]") {
    ClockTime c;

    // from_hour

    c = ClockTime::create(0);
    IS(0, 0, 0, 0);
    c = ClockTime::create(1);
    IS(1, 0, 0, 0);
    c = ClockTime::create(23);
    IS(23, 0, 0, 0);
    c = ClockTime::create(24);  // 24:00 should go to 00:00
    IS(0, 0, 0, 0);
    c = ClockTime::create(25);
    IS_ERROR(hour_out_of_range);
    c = ClockTime::create(-1);
    IS_ERROR(hour_out_of_range);

    c = ClockTime_from_hour(12);
    IS(12, 0, 0, 0);
    c = ClockTime_from_hour(-14);
    IS_ERROR(hour_out_of_range);

    ClockTime_ptr_from_hour(&c, 13);
    IS(13, 0, 0, 0);
    ClockTime_ptr_from_hour(&c, 26);
    IS_ERROR(hour_out_of_range);

    // from_hour_minute

    c = ClockTime::create(0, 0);
    IS(0, 0, 0, 0);
    c = ClockTime::create(0, 1);
    IS(0, 1, 0, 0);
    c = ClockTime::create(0, 59);
    IS(0, 59, 0, 0);
    c = ClockTime::create(0, 60);
    IS_ERROR(minute_out_of_range);
    c = ClockTime::create(0, -1);
    IS_ERROR(minute_out_of_range);

    c = ClockTime_from_hour_minute(14, 45);
    IS(14, 45, 0, 0);
    c = ClockTime_from_hour_minute(0, -2);
    IS_ERROR(minute_out_of_range);

    ClockTime_ptr_from_hour_minute(&c, 15, 56);
    IS(15, 56, 0, 0);
    ClockTime_ptr_from_hour_minute(&c, 0, -12);
    IS_ERROR(minute_out_of_range);

    // from_hour_minute_second

    c = ClockTime::create(0, 0, 0);
    IS(0, 0, 0, 0);
    c = ClockTime::create(0, 0, 1);
    IS(0, 0, 1, 0);
    c = ClockTime::create(0, 0, 59);
    IS(0, 0, 59, 0);
    c = ClockTime::create(0, 0, 60);    // leap second
    IS(0, 0, 60, 0);
    c = ClockTime::create(0, 0, 61);
    IS_ERROR(second_out_of_range);
    c = ClockTime::create(0, 0, -1);
    IS_ERROR(second_out_of_range);

    c = ClockTime_from_hour_minute_second(8, 9, 11);
    IS(8, 9, 11, 0);
    c = ClockTime_from_hour_minute_second(0, 0, -10);
    IS_ERROR(second_out_of_range);

    ClockTime_ptr_from_hour_minute_second(&c, 12, 13, 14);
    IS(12, 13, 14, 0);
    ClockTime_ptr_from_hour_minute_second(&c, 0, 0, -11);
    IS_ERROR(second_out_of_range);

    // from_hour_minute_second_nanosecond

    c = ClockTime::create(0, 0, 0, 0);
    IS(0, 0, 0, 0);
    c = ClockTime::create(0, 0, 0, 1);
    IS(0, 0, 0, 1);
    c = ClockTime::create(0, 0, 0, 999999999);
    IS(0, 0, 0, 999999999);
    c = ClockTime::create(0, 0, 0, 1000000000);
    IS_ERROR(nanosecond_out_of_range);
    c = ClockTime::create(0, 0, 0, -1);
    IS_ERROR(nanosecond_out_of_range);

    c = ClockTime_from_hour_minute_second_nanosecond(6, 7, 8, 9);
    IS(6, 7, 8, 9);
    c = ClockTime_from_hour_minute_second_nanosecond(0, 0, 0, -26);
    IS_ERROR(nanosecond_out_of_range);

    ClockTime_ptr_from_hour_minute_second_nanosecond(&c, 10, 11, 12, 13);
    IS(10, 11, 12, 13);
    ClockTime_ptr_from_hour_minute_second_nanosecond(&c, 0, 0, 0, -31);
    IS_ERROR(nanosecond_out_of_range);

    // ClockTime_create (macro - shortcut for C methods)

    c = ClockTime_create(3, 4, 5, 6);
    IS(3, 4, 5, 6);
    c = ClockTime_create(7, 8, 9);
    IS(7, 8, 9, 0);
    c = ClockTime_create(10, 11);
    IS(10, 11, 0, 0);
    c = ClockTime_create(12);
    IS(12, 0, 0, 0);

    ClockTime_ptr_create(&c, 13, 14, 15, 16);
    IS(13, 14, 15, 16);
    ClockTime_ptr_create(&c, 17, 18, 19);
    IS(17, 18, 19, 0);
    ClockTime_ptr_create(&c, 20, 21);
    IS(20, 21, 0, 0);
    ClockTime_ptr_create(&c, 22);
    IS(22, 0, 0, 0);

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
    IS_ERROR(second_out_of_range);
    c = ClockTime::create_with_decimal_seconds(1, 2, -1);
    IS_ERROR(second_out_of_range);

    c = ClockTime_create_with_decimal_seconds(5, 6, 48.9);
    IS(5, 6, 48, 900000000.0);
    c = ClockTime_create_with_decimal_seconds(7, 8, -1);
    IS_ERROR(second_out_of_range);

    ClockTime_ptr_create_with_decimal_seconds(&c, 9, 10, 11.9);
    IS(9, 10, 11, 900000000.0);
    ClockTime_ptr_create_with_decimal_seconds(&c, 11, 12, -13.0);
    IS_ERROR(second_out_of_range);

    // midnight, noon

    c = ClockTime::midnight();
    IS(0, 0, 0, 0);
    c = ClockTime::noon();
    IS(12, 0, 0, 0);

    c = ClockTime_midnight();
    IS(0, 0, 0, 0);
    c = ClockTime_noon();
    IS(12, 0, 0, 0);

    ClockTime_ptr_midnight(&c);
    IS(0, 0, 0, 0);
    ClockTime_ptr_noon(&c);
    IS(12, 0, 0, 0);
}

TEST_CASE("ClockTime accessors", "[clock-time]") {
    ClockTime c1 = ClockTime::create(0, 0, 0, 0);
    ClockTime c2 = ClockTime::create(3, 5, 8, 400);

    CHECK(c1.hour() == 0);
    CHECK(c2.hour() == 3);

    CHECK(c1.minute() == 0);
    CHECK(c2.minute() == 5);

    CHECK(c1.second() == 0);
    CHECK(c2.second() == 8);

    CHECK(c1.nanosecond() == 0);
    CHECK(c2.nanosecond() == 400);

    CHECK(c1.second_decimal() == 0.0);
    CHECK(c2.second_decimal() == 8.0000004);
}

TEST_CASE("ClockTime::time_since_midnight function", "[clock-time]") {
    ClockTime c;

    c = ClockTime::create(0, 0, 0, 0);
    CHECK(c.time_since_midnight() == TimeDelta::zero());

    c = ClockTime::create(1, 15, 30);
    CHECK(c.time_since_midnight() == TimeDelta::from_seconds(4530));

    c = ClockTime::create(0, 0, 45, 7000);
    CHECK(c.time_since_midnight() == TimeDelta::from_nanoseconds(45000007000));
}

TEST_CASE("ClockTime arithmetic operators", "[clock-time]") {
    TimeDelta d = TimeDelta::from_hours(2) + TimeDelta::from_minutes(4) +
        TimeDelta::from_seconds(6);
    ClockTime c;

    c = ClockTime::create(1, 3, 5, 0);
    c += d;
    IS(3, 7, 11, 0);

    c = ClockTime::create(10, 10, 10, 0);
    c -= d;
    IS(8, 6, 4, 0);

    c = ClockTime::create(10, 10, 10, 0);
    ClockTime c1 = c + d;
    ClockTime c1_reverse = d + c;
    ClockTime c2 = c - d;
    IS(10, 10, 10, 0);
    c = c1;
    IS(12, 14, 16, 0);
    c = c1_reverse;
    IS(12, 14, 16, 0);
    c = c2;
    IS(8, 6, 4, 0);

    // Testing nanoseconds spilling into seconds
    c = ClockTime::create(0, 0, 0, 999999998);
    TimeDelta d2 = TimeDelta::from_nanoseconds(5);
    c += d2;
    IS(0, 0, 1, 3);

    c = ClockTime::create(0, 0, 1, 2);
    c -= d2;
    IS(0, 0, 0, 999999997);

    // Testing wrap-around
    c = ClockTime::create(23, 0, 0, 0);
    d = TimeDelta::from_hours(1);
    c += d;
    IS(0, 0, 0, 0);

    c = ClockTime::create(1, 0, 0, 0);
    d = TimeDelta::from_hours(2);
    c -= d;
    IS(23, 0, 0, 0);
}

TEST_CASE("ClockTime comparison operators", "[clock-time]") {
    ClockTime c1 = ClockTime::create(0, 0, 0, 0),
              c2 = ClockTime::create(0, 0, 0, 1),
              c3 = ClockTime::create(12, 13, 14, 15),
              c4 = ClockTime::create(12, 13, 14, 15);

    CHECK(ClockTime::compare(c1, c1) == 0);
    CHECK(ClockTime::compare(c3, c4) == 0);
    CHECK(ClockTime::compare(c1, c2) < 0);
    CHECK(ClockTime::compare(c3, c2) > 0);

    CHECK(c1 == c1);
    CHECK(c3 == c4);
    CHECK(!(c1 == c3));
    CHECK(c1 != c3);
    CHECK(c1 != c2);

    CHECK(c1 < c2);
    CHECK(c1 < c3);
    CHECK(c2 < c3);
    CHECK(!(c3 < c4));
    CHECK(!(c3 < c2));

    CHECK(c1 <= c2);
    CHECK(c1 <= c2);
    CHECK(c1 <= c3);
    CHECK(c2 <= c3);
    CHECK(c3 <= c4);
    CHECK(c4 <= c3);
    CHECK(!(c2 <= c1));

    CHECK(c2 > c1);
    CHECK(c3 > c1);
    CHECK(c3 > c2);
    CHECK(!(c3 > c4));
    CHECK(!(c2 > c3));

    CHECK(c2 >= c1);
    CHECK(c3 >= c1);
    CHECK(c3 >= c2);
    CHECK(c4 >= c3);
    CHECK(c3 >= c4);
    CHECK(!(c1 >= c2));
}

