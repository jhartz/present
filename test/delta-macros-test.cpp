/*
 * Present - Date/Time Library
 *
 * Tests for the "present_delta" shortcut macro
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "catch.hpp"
#include "test-utils.hpp"

#include "present.h"

TEST_CASE("present_delta macro creating MonthDeltas",
          "[delta-macros] [month-delta]") {
    CHECK(present_delta(3, year) == MonthDelta::from_years(3));
    CHECK(present_delta(-4, year) == MonthDelta::from_years(-4));
    CHECK(present_delta(5, years) == MonthDelta::from_years(5));
    CHECK(present_delta(-6, years) == MonthDelta::from_years(-6));

    CHECK(present_delta(7, month) == MonthDelta::from_months(7));
    CHECK(present_delta(-8, month) == MonthDelta::from_months(-8));
    CHECK(present_delta(9, months) == MonthDelta::from_months(9));
    CHECK(present_delta(-10, months) == MonthDelta::from_months(-10));
}

TEST_CASE("present_delta macro creating DayDeltas",
          "[delta-macros] [day-delta]") {
    CHECK(present_delta(11, week) == DayDelta::from_weeks(11));
    CHECK(present_delta(-12, week) == DayDelta::from_weeks(-12));
    CHECK(present_delta(13, weeks) == DayDelta::from_weeks(13));
    CHECK(present_delta(-14, weeks) == DayDelta::from_weeks(-14));

    CHECK(present_delta(15, day) == DayDelta::from_days(15));
    CHECK(present_delta(-16, day) == DayDelta::from_days(-16));
    CHECK(present_delta(17, days) == DayDelta::from_days(17));
    CHECK(present_delta(-18, days) == DayDelta::from_days(-18));
}

TEST_CASE("present_delta macro creating TimeDeltas",
          "[delta-macros] [time-delta]") {
    CHECK(present_delta(19, week_time) == TimeDelta::from_weeks(19));
    CHECK(present_delta(-20, week_time) == TimeDelta::from_weeks(-20));
    CHECK(present_delta(21, weeks_time) == TimeDelta::from_weeks(21));
    CHECK(present_delta(-22, weeks_time) == TimeDelta::from_weeks(-22));

    CHECK(present_delta(23, day_time) == TimeDelta::from_days(23));
    CHECK(present_delta(-24, day_time) == TimeDelta::from_days(-24));
    CHECK(present_delta(25, days_time) == TimeDelta::from_days(25));
    CHECK(present_delta(-26, days_time) == TimeDelta::from_days(-26));

    CHECK(present_delta(27, hour) == TimeDelta::from_hours(27));
    CHECK(present_delta(28, hours) == TimeDelta::from_hours(28));
    CHECK(present_delta(29, hr) == TimeDelta::from_hours(29));
    CHECK(present_delta(30, hrs) == TimeDelta::from_hours(30));

    CHECK(present_delta(31, minute) == TimeDelta::from_minutes(31));
    CHECK(present_delta(32, minutes) == TimeDelta::from_minutes(32));
    CHECK(present_delta(33, min) == TimeDelta::from_minutes(33));
    CHECK(present_delta(34, mins) == TimeDelta::from_minutes(34));

    CHECK(present_delta(35, second) == TimeDelta::from_seconds(35));
    CHECK(present_delta(36, seconds) == TimeDelta::from_seconds(36));
    CHECK(present_delta(37, sec) == TimeDelta::from_seconds(37));
    CHECK(present_delta(38, secs) == TimeDelta::from_seconds(38));

    CHECK(present_delta(39, millisecond) == TimeDelta::from_milliseconds(39));
    CHECK(present_delta(40, milliseconds) == TimeDelta::from_milliseconds(40));
    CHECK(present_delta(41, ms) == TimeDelta::from_milliseconds(41));

    CHECK(present_delta(42, microsecond) == TimeDelta::from_microseconds(42));
    CHECK(present_delta(43, microseconds) == TimeDelta::from_microseconds(43));
    CHECK(present_delta(44, us) == TimeDelta::from_microseconds(44));

    CHECK(present_delta(45, nanosecond) == TimeDelta::from_nanoseconds(45));
    CHECK(present_delta(46, nanoseconds) == TimeDelta::from_nanoseconds(46));
    CHECK(present_delta(47, ns) == TimeDelta::from_nanoseconds(47));
}

