/*
 * Present - Date/Time Library
 *
 * Tests for the Timestamp C++ class and C-compatible methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "catch.hpp"
#include "test-utils.hpp"

#include "present.h"

#include "utils/constants.h"
#include "utils/time-utils.h"

// If we're using GCC, disable the annoying warning about missing initializers
#ifdef __GNUC__
# pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

static const struct Timestamp EMPTY_TIMESTAMP = {};

/** Absolute value for time_t's */
#define ABS(a, b) (((a) < (time_t) 0) ? -(a) : (a))

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
    // from_time_t(time_t)
    SECTION("creating from a time_t") {
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
    }

    // create(struct tm, TimeDelta)
    // create(Date, ClockTime, TimeDelta)
    // from_struct_tm(struct tm, TimeDelta)
    SECTION("creating from a struct tm, or from a Date/ClockTime/TimeDelta") {
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
    }

    SECTION("creating from a Date/ClockTime with a bad Date or ClockTime") {
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
    }

    SECTION("now()") {
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

        // (make sure it returns something different now)
        t = EMPTY_TIMESTAMP;
        t = Timestamp::now();
        REQUIRE_FALSE(t.has_error);
        CHECK(t.data_.timestamp_seconds != 920180081);
    }

    SECTION("epoch()") {
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
}

TEST_CASE("Timestamp creators edge case finder", "[timestamp]") {
    Timestamp t;

    for (int_year year = 2099; year >= 1500; year--) {
        t = Timestamp::create_utc(
                Date::create(year, 1, 1),
                ClockTime::midnight());
        CHECK(t.get_date_utc() == Date::create(year, 1, 1));

        t = Timestamp::create_utc(
                Date::create(year, 3, 1),
                ClockTime::midnight());
        CHECK(t.get_date_utc() == Date::create(year, 3, 1));
    }
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

    SECTION("get_struct_tm family") {
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
    }

    SECTION("get_date family") {
        CHECK(t.get_date_utc() == Date::create(1976, 4, 5));
        CHECK(t.get_date(TimeDelta::zero()) == Date::create(1976, 4, 5));
        CHECK(t.get_date(TimeDelta::from_hours(-5)) ==
                Date::create(1976, 4, 5));
        CHECK(t.get_date(TimeDelta::from_hours(3)) ==
                Date::create(1976, 4, 6));
    }

    SECTION("get_clock_time family") {
        CHECK(t.get_clock_time_utc() == ClockTime::create(21, 59, 59));
        CHECK(t.get_clock_time(TimeDelta::zero()) ==
                ClockTime::create(21, 59, 59));
        CHECK(t.get_clock_time(TimeDelta::from_hours(-5)) ==
                ClockTime::create(16, 59, 59));
        CHECK(t.get_clock_time(TimeDelta::from_hours(3)) ==
                ClockTime::create(0, 59, 59));
    }
}

TEST_CASE("Timestamp creators and accessors in local time", "[timestamp]") {
    SECTION("create in local time, access in local time (winter)") {
        Timestamp t = Timestamp::create_local(
                Date::create(1959, 1, 17),
                ClockTime::create(14, 39, 45));
        REQUIRE_FALSE(t.has_error);

        struct tm tm_local = t.get_struct_tm_local();
        CHECK(tm_local.tm_year == 1959 - STRUCT_TM_YEAR_OFFSET);
        CHECK(tm_local.tm_mon == 1 - STRUCT_TM_MONTH_OFFSET);
        CHECK(tm_local.tm_mday == 17);
        CHECK(tm_local.tm_hour == 14);
        CHECK(tm_local.tm_min == 39);
        CHECK(tm_local.tm_sec == 45);

        CHECK(t.get_date_local() == Date::create(1959, 1, 17));
        CHECK(t.get_clock_time_local() == ClockTime::create(14, 39, 45));
    }

    SECTION("create in local time, access in local time (summer)") {
        Timestamp t = Timestamp::create_local(
                Date::create(1959, 7, 17),
                ClockTime::create(14, 39, 45));
        REQUIRE_FALSE(t.has_error);

        struct tm tm_local = t.get_struct_tm_local();
        CHECK(tm_local.tm_year == 1959 - STRUCT_TM_YEAR_OFFSET);
        CHECK(tm_local.tm_mon == 7 - STRUCT_TM_MONTH_OFFSET);
        CHECK(tm_local.tm_mday == 17);
        CHECK(tm_local.tm_hour == 14);
        CHECK(tm_local.tm_min == 39);
        CHECK(tm_local.tm_sec == 45);

        CHECK(t.get_date_local() == Date::create(1959, 7, 17));
        CHECK(t.get_clock_time_local() == ClockTime::create(14, 39, 45));
    }

    // This test won't work if the absolute value of the time zone offset is
    // greater than 12 hours :(
    time_t time_zone_offset_winter = get_local_time_zone_offset_for_january();
    if (ABS(time_zone_offset_winter) < 12 * SECONDS_IN_HOUR) {
        TimeDelta time_zone_offset(
                TimeDelta::from_seconds(time_zone_offset_winter));

        SECTION("create in UTC, access in local time (winter)") {
            Timestamp t = Timestamp::create_utc(
                    Date::create(1987, 1, 4),
                    ClockTime::noon());
            REQUIRE_FALSE(t.has_error);

            CHECK(t.get_date_local() == Date::create(1987, 1, 4));
            CHECK(t.get_clock_time_local() - time_zone_offset
                    == ClockTime::noon());

            // Sanity check
            CHECK((t - time_zone_offset).get_date_local() ==
                    Date::create(1987, 1, 4));
            CHECK((t - time_zone_offset).get_clock_time_local() ==
                    ClockTime::noon());
        }

        SECTION("create in local time, access in UTC (winter)") {
            Timestamp t = Timestamp::create_local(
                    Date::create(1987, 1, 4),
                    ClockTime::noon());
            REQUIRE_FALSE(t.has_error);

            CHECK(t.get_date_utc() == Date::create(1987, 1, 4));
            CHECK(t.get_clock_time_utc() + time_zone_offset
                    == ClockTime::noon());

            // Sanity check
            CHECK((t + time_zone_offset).get_date_utc() ==
                    Date::create(1987, 1, 4));
            CHECK((t + time_zone_offset).get_clock_time_utc() ==
                    ClockTime::noon());
        }
    }

    // Now, do the same thing for summer
    time_t time_zone_offset_summer = get_local_time_zone_offset_for_july();
    if (ABS(time_zone_offset_summer) < 12 * SECONDS_IN_HOUR) {
        TimeDelta time_zone_offset(
                TimeDelta::from_seconds(time_zone_offset_summer));

        SECTION("create in UTC, access in local time (summer)") {
            Timestamp t = Timestamp::create_utc(
                    Date::create(1992, 7, 4),
                    ClockTime::noon());
            REQUIRE_FALSE(t.has_error);

            CHECK(t.get_date_local() == Date::create(1992, 7, 4));
            CHECK(t.get_clock_time_local() - time_zone_offset
                    == ClockTime::noon());

            // Sanity check
            CHECK((t - time_zone_offset).get_date_local() ==
                    Date::create(1992, 7, 4));
            CHECK((t - time_zone_offset).get_clock_time_local() ==
                    ClockTime::noon());
        }

        SECTION("create in local time, access in UTC (summer)") {
            Timestamp t = Timestamp::create_local(
                    Date::create(1992, 7, 4),
                    ClockTime::noon());
            REQUIRE_FALSE(t.has_error);

            CHECK(t.get_date_utc() == Date::create(1992, 7, 4));
            CHECK(t.get_clock_time_utc() + time_zone_offset
                    == ClockTime::noon());

            // Sanity check
            CHECK((t + time_zone_offset).get_date_utc() ==
                    Date::create(1992, 7, 4));
            CHECK((t + time_zone_offset).get_clock_time_utc() ==
                    ClockTime::noon());
        }
    }

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

TEST_CASE("Timestamp arithmetic operators with TimeDelta", "[timestamp]") {
    const time_t base_time = 197589599;
    TimeDelta seconds_plus4 = TimeDelta::from_seconds(4),
              hours_minus4 = TimeDelta::from_hours(-4);

    Timestamp orig_t = Timestamp::create(base_time),
              t;
    REQUIRE_FALSE(orig_t.has_error);

    t = orig_t;
    t += seconds_plus4;
    CHECK(t.get_time_t() == base_time + 4);

    t = orig_t;
    t -= seconds_plus4;
    CHECK(t.get_time_t() == base_time - 4);

    t = orig_t;
    t += hours_minus4;
    CHECK(t.get_time_t() == base_time + (3600 * -4));

    t = orig_t;
    t -= hours_minus4;
    CHECK(t.get_time_t() == base_time - (3600 * -4));

    // TODO: more...
}

TEST_CASE("Timestamp arithmetic operators with DayDelta", "[timestamp]") {
    DayDelta days_plus5 = DayDelta::from_days(5),
             weeks_minus2 = DayDelta::from_weeks(-2);

    Timestamp orig_t = Timestamp::create_utc(Date::create(1981, 4, 1),
            ClockTime::midnight());
    REQUIRE_FALSE(orig_t.has_error);
    Timestamp t;

    t = orig_t;
    t += days_plus5;
    CHECK(t.get_date_utc() == Date::create(1981, 4, 6));
    t += days_plus5;
    CHECK(t.get_date_utc() == Date::create(1981, 4, 11));

    t = orig_t;
    t -= days_plus5;
    CHECK(t.get_date_utc() == Date::create(1981, 3, 27));
    t -= days_plus5;
    CHECK(t.get_date_utc() == Date::create(1981, 3, 22));

    t = orig_t;
    t += weeks_minus2;
    CHECK(t.get_date_utc() == Date::create(1981, 3, 18));

    t = orig_t;
    t -= weeks_minus2;
    CHECK(t.get_date_utc() == Date::create(1981, 4, 15));
    t += weeks_minus2;
    CHECK(t.get_date_utc() == Date::create(1981, 4, 1));


    t = Timestamp::create_utc(Date::create(1995, 6, 23), ClockTime::midnight())
            + DayDelta::from_days(4);
    CHECK(t.get_date_utc() == Date::create(1995, 6, 27));

    t = Timestamp::create_utc(Date::create(1968, 2, 24), ClockTime::midnight())
            - DayDelta::from_days(16);
    CHECK(t.get_date_utc() == Date::create(1968, 2, 8));

    t = (Timestamp::create_utc(Date::create(2002, 1, 1), ClockTime::midnight())
            - DayDelta::from_days(3))
            + DayDelta::from_weeks(2);
    CHECK(t.get_date_utc() == Date::create(2002, 1, 12));

    t = DayDelta::from_days(8) + orig_t;
    CHECK(t.get_date_utc() == Date::create(1981, 4, 9));
}

TEST_CASE("Timestamp arithmetic operators with MonthDelta", "[timestamp]") {
    MonthDelta months_plus2 = MonthDelta::from_months(2),
               months_minus5 = MonthDelta::from_months(-5),
               years_plus4 = MonthDelta::from_years(4),
               years_minus16 = MonthDelta::from_years(-16);

    Timestamp orig_t = Timestamp::create_utc(Date::create(1982, 11, 13),
            ClockTime::midnight());
    Timestamp t;

    t = orig_t;
    t += months_plus2;
    CHECK(t.get_date_utc() == Date::create(1983, 1, 13));
    t += months_minus5;
    CHECK(t.get_date_utc() == Date::create(1982, 8, 13));

    t = orig_t;
    t -= months_plus2;
    CHECK(t.get_date_utc() == Date::create(1982, 9, 13));
    t -= months_minus5;
    CHECK(t.get_date_utc() == Date::create(1983, 2, 13));

    t = orig_t;
    t += years_plus4;
    CHECK(t.get_date_utc() == Date::create(1986, 11, 13));
    t += years_minus16;
    CHECK(t.get_date_utc() == Date::create(1970, 11, 13));

    t = orig_t;
    t -= years_plus4;
    CHECK(t.get_date_utc() == Date::create(1978, 11, 13));
    t -= years_minus16;
    CHECK(t.get_date_utc() == Date::create(1994, 11, 13));

    t = orig_t + MonthDelta::from_months(7);
    CHECK(t.get_date_utc() == Date::create(1983, 6, 13));

    t = orig_t - MonthDelta::from_months(3);
    CHECK(t.get_date_utc() == Date::create(1982, 8, 13));

    t = MonthDelta::from_years(4) + orig_t;
    CHECK(t.get_date_utc() == Date::create(1986, 11, 13));
}

TEST_CASE("Timestamp arithmetic operators edge cases", "[timestamp]") {
    DayDelta days_plus8 = DayDelta::from_days(8);
    MonthDelta months_plus5 = MonthDelta::from_months(5),
               months_minus11 = MonthDelta::from_months(-11);

    Timestamp orig_t = Timestamp::create_utc(
            Date::create(1934, 8, 16), ClockTime::create(23, 37, 48));
    Timestamp t;

    t = orig_t;
    t += days_plus8;
    CHECK(t.get_date_utc() == Date::create(1934, 8, 24));

    t = orig_t;
    t -= days_plus8;
    CHECK(t.get_date_utc() == Date::create(1934, 8, 8));

    t = orig_t;
    t += months_plus5;
    CHECK(t.get_date_utc() == Date::create(1935, 1, 16));

    t = orig_t;
    t -= months_plus5;
    CHECK(t.get_date_utc() == Date::create(1934, 3, 16));

    t = orig_t;
    t += months_minus11;
    CHECK(t.get_date_utc() == Date::create(1933, 9, 16));

    t = orig_t;
    t -= months_minus11;
    CHECK(t.get_date_utc() == Date::create(1935, 7, 16));
}

