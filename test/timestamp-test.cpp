/*
 * Present - Date/Time Library
 *
 * Tests for the Timestamp C++ class and C-compatible methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "catch.hpp"

#include "present/clock-time.h"
#include "present/date.h"
#include "present/day-delta.h"
#include "present/month-delta.h"
#include "present/time-delta.h"
#include "present-syscalls.h"

#include "present/timestamp.h"

/**
 * Shortcut macro to compare timestamp_seconds and additional_nanoseconds all
 * in one.
 * Expects that the Timestamp is "t".
 */
#define IS(test_timestamp_seconds, test_additional_nanoseconds) \
    REQUIRE(t.error == Timestamp_ERROR_NONE);                   \
    CHECK(t.data_.timestamp_seconds == test_timestamp_seconds); \
    CHECK(t.data_.additional_nanoseconds == test_additional_nanoseconds);

/**
 * Creates a Timestamp using 2 methods (struct tm, and Date/ClockTime), and
 * makes sure both are working well.
 */
#define TEST_CREATE(yr, mon, mday, hr, min, sec, tz_offset,     \
        expected_unix_timestamp)                                \
    do {                                                        \
        struct tm tm = {};                                      \
        tm.tm_year = yr - 1900;                                 \
        tm.tm_mon = mon - 1;                                    \
        tm.tm_mday = mday;                                      \
        tm.tm_hour = hr;                                        \
        tm.tm_min = min;                                        \
        tm.tm_sec = sec;                                        \
        tm.tm_isdst = 0;                                        \
        REQUIRE(mktime(&tm) != -1);                             \
        Timestamp t = Timestamp::create(tm,                     \
                TimeDelta::from_hours(tz_offset));              \
        IS(expected_unix_timestamp, 0);                         \
        CHECK(t.get_clock_time_utc().minute() == min);          \
        CHECK(t.get_clock_time_utc().second() == sec);          \
        CHECK(t.get_clock_time_utc().nanosecond() == 0);        \
                                                                \
        t = Timestamp::create(Date::create(yr, mon, mday),      \
                ClockTime::create(hr, min, sec),                \
                TimeDelta::from_hours(tz_offset));              \
        IS(expected_unix_timestamp, 0);                         \
        CHECK(t.get_clock_time_utc().minute() == min);          \
        CHECK(t.get_clock_time_utc().second() == sec);          \
        CHECK(t.get_clock_time_utc().nanosecond() == 0);        \
    } while (0)

/**
 * This test case tests all the overloads of the "create" method (which also
 * tests the C "Timestamp_create_..." functions).
 */
TEST_CASE("Timestamp creators", "[timestamp]") {
    Timestamp t;

    // create(time_t)

    t = Timestamp::create((time_t) 0);
    IS(0, 0);
    t = Timestamp::create((time_t) 1325376000);
    IS(1325376000, 0);

    // create(struct tm, TimeDelta)
    // create(Date, ClockTime, TimeDelta)

    TEST_CREATE(
            1970, 1, 1,     // date
            0, 0, 0,        // time
            0,              // time zone offset
            0);             // expected UNIX timestamp
    /*
    TEST_CREATE(
            1969, 12, 31,
            0, 0, 0,
            0,
            -86400);
    TEST_CREATE(
            1970, 1, 2,
            0, 0, 0,
            0,
            86400);

    // All the same timestamp (197589599):
    // Apr. 5, 1976 21:59:59 UTC
    // Apr. 5, 1976 16:59:59 EST (UTC-05:00)
    // Apr. 6, 1976 00:59:59 MSK (UTC+03:00)
    TEST_CREATE(
            1976, 4, 5,
            21, 59, 59,
            0,
            197589599);
    TEST_CREATE(
            1976, 4, 5,
            16, 59, 59,
            -5,
            197589599);
    TEST_CREATE(
            1976, 4, 6,
            0, 59, 59,
            3,
            197589599);
    */

    // now()
    // (change what present_now() returns to 1999-2-28 05:34:41.986 UTC)
    struct PresentNowStruct test_now = {
        (time_t) 920180081,
        (long)   986000000
    };
    present_set_test_time(test_now);

    t = Timestamp::now();
    IS(920180081, 986000000);

    present_reset_test_time();

    // epoch()
    t = Timestamp::epoch();
    IS(0, 0);
}

