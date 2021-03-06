/*
 * Present - Date/Time Library
 *
 * Tests for the DayDelta C++ class and C-compatible methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "catch.hpp"
#include "test-utils.hpp"

#include "present.h"

/**
 * Shortcut macro to compare the number of days.
 * Expects that the delta is called "d".
 */
#define IS(test_delta_days)                         \
    CHECK(d.data_.delta_days == test_delta_days);


/**
 * This test case tests all of the "from_" methods (which also tests the C
 * "DayDelta_from_..." methods).
 */
TEST_CASE("DayDelta creators", "[day-delta]") {
    DayDelta d;

    SECTION("creating from a number of days") {
        d = DayDelta::from_days(1);
        IS(1);
        d = DayDelta::from_days(-1);
        IS(-1);
        d = DayDelta::from_days(0);
        IS(0);
        d = DayDelta::from_days(2147483647);
        IS(2147483647);
        d = DayDelta::from_days(-2147483647);
        IS(-2147483647);

        d = DayDelta_from_days(13);
        IS(13);

        DayDelta_ptr_from_days(&d, -11);
        IS(-11);
    }

    SECTION("creating from a number of weeks") {
        d = DayDelta::from_weeks(1);
        IS(7);
        d = DayDelta::from_weeks(5);
        IS(35);
        d = DayDelta::from_weeks(-1);
        IS(-7);
        d = DayDelta::from_weeks(-11);
        IS(-77);
        d = DayDelta::from_weeks(0);
        IS(0);
        d = DayDelta::from_weeks(306783378);
        IS(2147483646);
        d = DayDelta::from_weeks(-306783378);
        IS(-2147483646);

        d = DayDelta_from_weeks(7);
        IS(49);

        DayDelta_ptr_from_weeks(&d, -9);
        IS(-63);
    }

    SECTION("creating with 0 days") {
        d = DayDelta::zero();
        IS(0);

        d = DayDelta_zero();
        IS(0);

        DayDelta_ptr_zero(&d);
        IS(0);
    }
}

TEST_CASE("DayDelta accessors", "[day-delta]") {
    DayDelta d1 = DayDelta::from_days(5),
             d2 = DayDelta::from_days(7),
             d3 = DayDelta::from_days(-14),
             d4 = DayDelta::from_days(-20),
             d5 = DayDelta::zero();

    CHECK(d1.days() == 5);
    CHECK(d2.days() == 7);
    CHECK(d3.days() == -14);
    CHECK(d4.days() == -20);
    CHECK(d5.days() == 0);

    CHECK(d1.weeks() == 0);
    CHECK(d2.weeks() == 1);
    CHECK(d3.weeks() == -2);
    CHECK(d4.weeks() == -2);
    CHECK(d5.weeks() == 0);

    CHECK(d1.weeks_decimal() == 0.7142857142857143);
    CHECK(d2.weeks_decimal() == 1.0);
    CHECK(d3.weeks_decimal() == -2.0);
    CHECK(d4.weeks_decimal() == -2.857142857142857);
    CHECK(d5.weeks_decimal() == 0.0);

    CHECK(d1.to_TimeDelta() == TimeDelta::from_days(5));
    CHECK(d2.to_TimeDelta() == TimeDelta::from_days(7));
    CHECK(d3.to_TimeDelta() == TimeDelta::from_days(-14));
    CHECK(d4.to_TimeDelta() == TimeDelta::from_days(-20));
    CHECK(d5.to_TimeDelta() == TimeDelta::from_days(0));
}

TEST_CASE("DayDelta arithmetic operators", "[day-delta]") {
    DayDelta d1 = DayDelta::from_days(8),
             d2 = DayDelta::from_days(-21),
             d3 = DayDelta::zero();

    SECTION("is_negative()") {
        CHECK(!d1.is_negative());
        CHECK(d2.is_negative());
        CHECK(!d3.is_negative());
    }

    SECTION("negate()") {
        d1.negate();
        CHECK(d1.days() == -8);
        CHECK(d1.weeks() == -1);
        d1.negate();
        CHECK(d1.days() == 8);
        CHECK(d1.weeks() == 1);

        d2.negate();
        CHECK(d2.days() == 21);
        CHECK(d2.weeks() == 3);
        d2.negate();
        CHECK(d2.days() == -21);
        CHECK(d2.weeks() == -3);

        d3.negate();
        CHECK(!d3.is_negative());
        d3.negate();
        CHECK(!d3.is_negative());
    }

    SECTION("operator-") {
        DayDelta d;

        d = -d1;
        IS(-8);
        d = -d2;
        IS(21);
        d = -d3;
        IS(0);
    }

    SECTION("operator++ / operator--") {
        DayDelta d;

        d = DayDelta::from_days(5);
        IS(5);
        CHECK((d++).days() == 5);
        IS(6);
        CHECK((++d).days() == 7);
        IS(7);
        CHECK((d--).days() == 7);
        IS(6);
        CHECK((--d).days() == 5);
        IS(5);
    }

    SECTION("scaling") {
        DayDelta d;

        d = DayDelta::from_days(5);
        IS(5);
        d *= 6;
        IS(30);
        d /= 10;
        IS(3);

        d = DayDelta::from_days(-10);
        IS(-10);
        d *= 6;
        IS(-60);
        d /= 25;
        IS(-2);

        d = DayDelta::from_days(9);
        IS(9);
        CHECK((d * 3).days() == 27);
        IS(9);
        CHECK((d * -5).days() == -45);
        IS(9);
        CHECK((d / 4).days() == 2);
        IS(9);
        CHECK((d / -3).days() == -3);
        IS(9);

        d = DayDelta::from_days(-43);
        IS(-43);
        CHECK((d * 2).days() == -86);
        IS(-43);
        CHECK((d * -4).days() == 172);
        IS(-43);
        CHECK((d / 6).days() == -7);
        IS(-43);
        CHECK((d / -7).days() == 6);
        IS(-43);
    }

    SECTION("addition / subtraction") {
        DayDelta d;

        d = DayDelta::from_days(5);
        IS(5);
        d += DayDelta::from_days(8);
        IS(13);
        d += DayDelta::from_days(-4);
        IS(9);
        d -= DayDelta::from_days(12);
        IS(-3);
        d -= DayDelta::from_days(-5);
        IS(2);

        d = DayDelta::from_days(-13);
        IS(-13);
        CHECK((d + DayDelta::from_days(4)).days() == -9);
        IS(-13);
        CHECK((d + DayDelta::from_days(-7)).days() == -20);
        IS(-13);
        CHECK((d - DayDelta::from_days(8)).days() == -21);
        IS(-13);
        CHECK((d - DayDelta::from_days(-34)).days() == 21);
        IS(-13);
    }
}

TEST_CASE("DayDelta comparison operators", "[day-delta]") {
    DayDelta d1 = DayDelta::from_days(19),
             d2 = DayDelta::from_days(21),
             d3 = DayDelta::from_days(-13),
             d4 = DayDelta::from_days(-13),
             d5 = DayDelta::zero();

    TimeDelta td1 = TimeDelta::from_days(19),
              td2 = TimeDelta::from_days(21),
              td3 = TimeDelta::from_days(-13),
              td4 = TimeDelta::from_days(-13),
              td5 = TimeDelta::zero();

    CHECK(DayDelta::compare(d1, d2) < 0);
    CHECK(DayDelta::compare(d1, d3) > 0);
    CHECK(DayDelta::compare(d1, d5) > 0);
    CHECK(DayDelta::compare(d3, d4) == 0);
    CHECK(DayDelta::compare(d4, d3) == 0);
    CHECK(DayDelta::compare(d5, d5) == 0);

    CHECK(DayDelta::compare(d1, td2) < 0);
    CHECK(DayDelta::compare(d1, td3) > 0);
    CHECK(DayDelta::compare(d1, td5) > 0);
    CHECK(DayDelta::compare(d3, td4) == 0);
    CHECK(DayDelta::compare(d4, td3) == 0);
    CHECK(DayDelta::compare(d5, td5) == 0);

    CHECK(DayDelta::compare(td1, d2) < 0);
    CHECK(DayDelta::compare(td1, d3) > 0);
    CHECK(DayDelta::compare(td1, d5) > 0);
    CHECK(DayDelta::compare(td3, d4) == 0);
    CHECK(DayDelta::compare(td4, d3) == 0);
    CHECK(DayDelta::compare(td5, d5) == 0);

    CHECK(d3 == d4);        CHECK(d3 == td4);
    CHECK(d4 == d3);        CHECK(d4 == td3);
    CHECK(!(d1 == d2));     CHECK(!(d1 == td2));
    CHECK(!(d1 == d5));     CHECK(!(d1 == td5));
    CHECK(d1 != d2);        CHECK(d1 != td2);
    CHECK(d5 != d1);        CHECK(d5 != td1);

    CHECK(d1 < d2);         CHECK(d1 < td2);
    CHECK(d3 < d1);         CHECK(d3 < td1);
    CHECK(!(d5 < d4));      CHECK(!(d5 < td4));
    CHECK(!(d3 < d4));      CHECK(!(d3 < td4));

    CHECK(d1 <= d2);        CHECK(d1 <= td2);
    CHECK(d3 <= d2);        CHECK(d3 <= td2);
    CHECK(!(d5 <= d4));     CHECK(!(d5 <= td4));
    CHECK(d3 <= d4);        CHECK(d3 <= td4);

    CHECK(d1 > d3);         CHECK(d1 > td3);
    CHECK(d2 > d1);         CHECK(d2 > td1);
    CHECK(d5 > d3);         CHECK(d5 > td3);
    CHECK(!(d3 > d4));      CHECK(!(d3 > td4));
    CHECK(!(d3 > d2));      CHECK(!(d3 > td2));
    CHECK(!(d1 > d2));      CHECK(!(d1 > td2));

    CHECK(d1 >= d3);        CHECK(d1 >= td3);
    CHECK(d2 >= d1);        CHECK(d2 >= td1);
    CHECK(d5 >= d3);        CHECK(d5 >= td3);
    CHECK(d3 >= d4);        CHECK(d3 >= td4);
    CHECK(!(d5 >= d2));     CHECK(!(d5 >= td2));
}

