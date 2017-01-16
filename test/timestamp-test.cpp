/*
 * Present - Date/Time Library
 *
 * Tests for the Timestamp C++ class and C-compatible methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "catch.hpp"

#include "present.h"

#include "utils/constants.h"
#include "utils/time-calls.h"

static const struct Timestamp EMPTY_TIMESTAMP = {};

/**
 * Shortcut macro to compare timestamp_seconds and additional_nanoseconds all
 * in one.
 * Expects that the Timestamp is "t".
 */
#define IS(test_timestamp_seconds, test_additional_nanoseconds) \
    REQUIRE_FALSE(t.has_error);                                 \
    CHECK(t.data_.timestamp_seconds == test_timestamp_seconds); \
    CHECK(t.data_.additional_nanoseconds == test_additional_nanoseconds);

/**
 * Shortcut macro to check if there's a certain error.
 * Expects that the Timestamp is "t".
 */
#define IS_ERROR(eRR_tYPE)      \
    CHECK(t.has_error);         \
    CHECK(t.errors.eRR_tYPE);

/**
 * Check that creating a Timestamp from a struct tm works correctly.
 */
#define TEST_CREATE_FROM_STRUCT_TM(yr, mon, mday, hr, min, sec, \
        tz_offset, expected_unix_timestamp)                     \
    do {                                                        \
        struct tm tm = {};                                      \
        tm.tm_year = yr - STRUCT_TM_YEAR_OFFSET;                \
        tm.tm_mon = mon - STRUCT_TM_MONTH_OFFSET;               \
        tm.tm_mday = mday;                                      \
        tm.tm_hour = hr;                                        \
        tm.tm_min = min;                                        \
        tm.tm_sec = sec;                                        \
        tm.tm_isdst = 0;                                        \
        REQUIRE(mktime(&tm) != -1);                             \
        {                                                       \
            Timestamp t = EMPTY_TIMESTAMP;                      \
            t = Timestamp::create(tm,                           \
                    TimeDelta::from_hours(tz_offset));          \
            REQUIRE_FALSE(t.has_error);                         \
            IS(expected_unix_timestamp, 0);                     \
            CHECK(t.get_clock_time_utc().minute() == min);      \
            CHECK(t.get_clock_time_utc().second() == sec);      \
            CHECK(t.get_clock_time_utc().nanosecond() == 0);    \
        }                                                       \
        {                                                       \
            Timestamp t = EMPTY_TIMESTAMP;                      \
            TimeDelta delta = TimeDelta::from_hours(tz_offset); \
            t = Timestamp_from_struct_tm(tm, &delta);           \
            REQUIRE_FALSE(t.has_error);                         \
            IS(expected_unix_timestamp, 0);                     \
            CHECK(t.get_clock_time_utc().minute() == min);      \
            CHECK(t.get_clock_time_utc().second() == sec);      \
            CHECK(t.get_clock_time_utc().nanosecond() == 0);    \
        }                                                       \
        {                                                       \
            Timestamp t = EMPTY_TIMESTAMP;                      \
            TimeDelta delta = TimeDelta::from_hours(tz_offset); \
            Timestamp_ptr_from_struct_tm(&t, tm, &delta);       \
            REQUIRE_FALSE(t.has_error);                         \
            IS(expected_unix_timestamp, 0);                     \
            CHECK(t.get_clock_time_utc().minute() == min);      \
            CHECK(t.get_clock_time_utc().second() == sec);      \
            CHECK(t.get_clock_time_utc().nanosecond() == 0);    \
        }                                                       \
    } while (0)

/**
 * Check that creating a Timestamp from a Date and a ClockTime works
 * correctly. This tests the C++ @p Timestamp::create function and the C
 * @p Timestamp_create and @p Timestamp_ptr_create functions.
 */
#define TEST_CREATE_FROM_DATE_TIME(yr, mon, mday, hr, min, sec,         \
        tz_offset, expected_unix_timestamp)                             \
    do {                                                                \
        const Date testDate = Date::create(yr, mon, mday);              \
        const ClockTime testTime = ClockTime::create(hr, min, sec);     \
        const TimeDelta testDelta = TimeDelta::from_hours(tz_offset);   \
        {                                                               \
            Timestamp t = EMPTY_TIMESTAMP;                              \
            t = Timestamp::create(testDate, testTime, testDelta);       \
            REQUIRE_FALSE(t.has_error);                                 \
            IS(expected_unix_timestamp, 0);                             \
            CHECK(t.get_clock_time_utc().minute() == min);              \
            CHECK(t.get_clock_time_utc().second() == sec);              \
            CHECK(t.get_clock_time_utc().nanosecond() == 0);            \
        }                                                               \
        {                                                               \
            Timestamp t = EMPTY_TIMESTAMP;                              \
            t = Timestamp_create(&testDate, &testTime, &testDelta);     \
            REQUIRE_FALSE(t.has_error);                                 \
            IS(expected_unix_timestamp, 0);                             \
            CHECK(t.get_clock_time_utc().minute() == min);              \
            CHECK(t.get_clock_time_utc().second() == sec);              \
            CHECK(t.get_clock_time_utc().nanosecond() == 0);            \
        }                                                               \
        {                                                               \
            Timestamp t = EMPTY_TIMESTAMP;                              \
            Timestamp_ptr_create(&t, &testDate, &testTime, &testDelta); \
            REQUIRE_FALSE(t.has_error);                                 \
            IS(expected_unix_timestamp, 0);                             \
            CHECK(t.get_clock_time_utc().minute() == min);              \
            CHECK(t.get_clock_time_utc().second() == sec);              \
            CHECK(t.get_clock_time_utc().nanosecond() == 0);            \
        }                                                               \
    } while (0)

/**
 * This test case tests all the overloads of the "create" method (which also
 * tests the C "Timestamp_create_..." functions).
 */
TEST_CASE("Timestamp creators", "[timestamp]") {
    Timestamp t;

    // create(time_t)
    // from_time_t

    t = Timestamp::create((time_t) 0);
    IS(0, 0);
    t = Timestamp::create((time_t) 1325376000);
    IS(1325376000, 0);

    t = Timestamp_from_time_t((time_t) 0);
    IS(0, 0);
    t = Timestamp_from_time_t((time_t) 918491000);
    IS(918491000, 0);

    Timestamp_ptr_from_time_t(&t, (time_t) 0);
    IS(0, 0);
    Timestamp_ptr_from_time_t(&t, (time_t) 1);
    IS(1, 0);

    // create(struct tm, TimeDelta)
    // create(Date, ClockTime, TimeDelta)
    // from_struct_tm

    TEST_CREATE_FROM_STRUCT_TM(
            1970, 1, 1,     // date
            0, 0, 0,        // time
            0,              // time zone offset
            0);             // expected UNIX timestamp
    TEST_CREATE_FROM_DATE_TIME(1970, 1, 1, 0, 0, 0,     0, 0);

    TEST_CREATE_FROM_STRUCT_TM(1969, 12, 31, 0, 0, 0,   0, -86400);
    TEST_CREATE_FROM_DATE_TIME(1969, 12, 31, 0, 0, 0,   0, -86400);

    TEST_CREATE_FROM_STRUCT_TM(1970, 1, 2, 0, 0, 0,     0, 86400);
    TEST_CREATE_FROM_DATE_TIME(1970, 1, 2, 0, 0, 0,     0, 86400);

    // All the same timestamp (197589599):
    // Apr. 5, 1976 21:59:59 UTC
    // Apr. 5, 1976 16:59:59 EST (UTC-05:00)
    // Apr. 6, 1976 00:59:59 MSK (UTC+03:00)
    TEST_CREATE_FROM_STRUCT_TM(1976, 4, 5, 21, 59, 59,  0,  197589599);
    TEST_CREATE_FROM_DATE_TIME(1976, 4, 5, 21, 59, 59,  0,  197589599);

    TEST_CREATE_FROM_STRUCT_TM(1976, 4, 5, 16, 59, 59,  -5, 197589599);
    TEST_CREATE_FROM_DATE_TIME(1976, 4, 5, 16, 59, 59,  -5, 197589599);

    TEST_CREATE_FROM_STRUCT_TM(1976, 4, 6, 0, 59, 59,   +3, 197589599);
    TEST_CREATE_FROM_DATE_TIME(1976, 4, 6, 0, 59, 59,   +3, 197589599);

    // create(Date, ClockTime) with bad Date / ClockTime
    Date bad_d = Date::create(0, 0, 0);
    REQUIRE(bad_d.has_error);
    Date good_d = Date::create(2000, 1, 1);
    REQUIRE_FALSE(good_d.has_error);

    ClockTime bad_ct = ClockTime::create(99, 99, 99);
    REQUIRE(bad_ct.has_error);
    ClockTime good_ct = ClockTime::noon();
    REQUIRE_FALSE(good_ct.has_error);

    t = Timestamp::create(bad_d, good_ct, TimeDelta::zero());
    IS_ERROR(invalid_date);
    t = Timestamp::create_utc(bad_d, good_ct);
    IS_ERROR(invalid_date);
    t = Timestamp::create_local(bad_d, good_ct);
    IS_ERROR(invalid_date);

    t = Timestamp::create(good_d, bad_ct, TimeDelta::zero());
    IS_ERROR(invalid_clock_time);
    t = Timestamp::create_utc(good_d, bad_ct);
    IS_ERROR(invalid_clock_time);
    t = Timestamp::create_local(good_d, bad_ct);
    IS_ERROR(invalid_clock_time);

    // now()
    // (change what present_now() returns to 1999-2-28 05:34:41.986 UTC)
    struct PresentNowStruct test_now = {
        (time_t) 920180081,
        (long)   986000000
    };
    present_set_test_time(test_now);

    t = EMPTY_TIMESTAMP;
    t = Timestamp::now();
    IS(920180081, 986000000);

    t = EMPTY_TIMESTAMP;
    t = Timestamp_now();
    IS(920180081, 986000000);

    t = EMPTY_TIMESTAMP;
    Timestamp_ptr_now(&t);
    IS(920180081, 986000000);

    present_reset_test_time();

    // epoch()
    t = EMPTY_TIMESTAMP;
    t = Timestamp::epoch();
    IS(0, 0);

    t = EMPTY_TIMESTAMP;
    t = Timestamp_epoch();
    IS(0, 0);

    t = EMPTY_TIMESTAMP;
    Timestamp_ptr_epoch(&t);
    IS(0, 0);
}

TEST_CASE("Timestamp accessors", "[timestamp]") {
    // All the same timestamp (197589599):
    // Apr. 5, 1976 21:59:59 UTC
    // Apr. 5, 1976 16:59:59 EST (UTC-05:00)
    // Apr. 6, 1976 00:59:59 MSK (UTC+03:00)

    Timestamp t = Timestamp::create((time_t) 197589599);
    REQUIRE_FALSE(t.has_error);

    // get_time_t
    CHECK(t.get_time_t() == 197589599);

    // get_struct_tm family
    struct tm tm_utc = t.get_struct_tm_utc();
    CHECK(tm_utc.tm_year == 1976 - STRUCT_TM_YEAR_OFFSET);
    CHECK(tm_utc.tm_mon == 4 - STRUCT_TM_MONTH_OFFSET);
    CHECK(tm_utc.tm_mday == 5);
    CHECK(tm_utc.tm_hour == 21);
    CHECK(tm_utc.tm_min == 59);
    CHECK(tm_utc.tm_sec == 59);

    struct tm tm_est = t.get_struct_tm(TimeDelta::from_hours(-5));
    CHECK(tm_est.tm_year == 1976 - STRUCT_TM_YEAR_OFFSET);
    CHECK(tm_est.tm_mon == 4 - STRUCT_TM_MONTH_OFFSET);
    CHECK(tm_est.tm_mday == 5);
    CHECK(tm_est.tm_hour == 16);
    CHECK(tm_est.tm_min == 59);
    CHECK(tm_est.tm_sec == 59);

    struct tm tm_msk = t.get_struct_tm(TimeDelta::from_hours(3));
    CHECK(tm_msk.tm_year == 1976 - STRUCT_TM_YEAR_OFFSET);
    CHECK(tm_msk.tm_mon == 4 - STRUCT_TM_MONTH_OFFSET);
    CHECK(tm_msk.tm_mday == 6);
    CHECK(tm_msk.tm_hour == 0);
    CHECK(tm_msk.tm_min == 59);
    CHECK(tm_msk.tm_sec == 59);

    // get_date family
    CHECK(t.get_date_utc() == Date::create(1976, 4, 5));
    CHECK(t.get_date(TimeDelta::zero()) == Date::create(1976, 4, 5));
    CHECK(t.get_date(TimeDelta::from_hours(-5)) == Date::create(1976, 4, 5));
    CHECK(t.get_date(TimeDelta::from_hours(3)) == Date::create(1976, 4, 6));

    // get_clock_time family
    CHECK(t.get_clock_time_utc() == ClockTime::create(21, 59, 59));
    CHECK(t.get_clock_time(TimeDelta::zero()) ==
            ClockTime::create(21, 59, 59));
    CHECK(t.get_clock_time(TimeDelta::from_hours(-5)) ==
            ClockTime::create(16, 59, 59));
    CHECK(t.get_clock_time(TimeDelta::from_hours(3)) ==
            ClockTime::create(0, 59, 59));

    // The best we can do for the "local" methods is try throwing something at
    // it and seeing that we get the same thing back
    t = Timestamp::create_local(Date::create(1959, 5, 17),
            ClockTime::create(14, 39, 45));
    REQUIRE_FALSE(t.has_error);

    struct tm tm_local = t.get_struct_tm_local();
    CHECK(tm_local.tm_year == 1959 - STRUCT_TM_YEAR_OFFSET);
    CHECK(tm_local.tm_mon == 5 - STRUCT_TM_MONTH_OFFSET);
    CHECK(tm_local.tm_mday == 17);
    CHECK(tm_local.tm_hour == 14);
    CHECK(tm_local.tm_min == 39);
    CHECK(tm_local.tm_sec == 45);

    CHECK(t.get_date_local() == Date::create(1959, 5, 17));
    CHECK(t.get_clock_time_local() == ClockTime::create(14, 39, 45));
}

TEST_CASE("Timestamp 'difference' functions", "[timestamp]") {
    const time_t base = 197589599;
    Timestamp t1 = Timestamp::create(base),
              t2 = Timestamp::create(base + 86400 + 3600);  // + 1 day, 1 hour
    REQUIRE_FALSE(t1.has_error);
    REQUIRE_FALSE(t2.has_error);

    TimeDelta exp_diff = TimeDelta::from_seconds(86400 + 3600);
    CHECK(t1.difference(t2) == -exp_diff);
    CHECK(t2.difference(t1) == exp_diff);
    CHECK(t1.absolute_difference(t2) == exp_diff);
    CHECK(t2.absolute_difference(t1) == exp_diff);
}

TEST_CASE("Timestamp arithmetic operators", "[timestamp]") {
    TimeDelta seconds_plus4 = TimeDelta::from_seconds(4),
              hours_minus4 = TimeDelta::from_hours(-4);

    Timestamp orig_t = Timestamp::create((time_t) 197589599),
              t;
    REQUIRE_FALSE(orig_t.has_error);

    t = orig_t;
    t += seconds_plus4;
    CHECK(t.get_time_t() == 197589599 + 4);

    t = orig_t;
    t -= seconds_plus4;
    CHECK(t.get_time_t() == 197589599 - 4);

    t = orig_t;
    t += hours_minus4;
    CHECK(t.get_time_t() == 197589599 + (3600 * -4));

    t = orig_t;
    t -= hours_minus4;
    CHECK(t.get_time_t() == 197589599 - (3600 * -4));
}

