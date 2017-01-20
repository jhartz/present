/*
 * Present - Date/Time Library
 *
 * Tests for the MonthDelta C++ class and C-compatible methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "catch.hpp"
#include "test-utils.hpp"

#include "present.h"

/**
 * Shortcut macro to compare the number of months.
 * Expects that the delta is called "d".
 */
#define IS(test_delta_months)                           \
    CHECK(d.data_.delta_months == test_delta_months);


/**
 * This test case tests all of the "from_" methods (which also tests the C
 * "MonthDelta_from_..." methods).
 */
TEST_CASE("MonthDelta creators", "[month-delta]") {
    MonthDelta d;

    SECTION("creating from a number of months") {
        d = MonthDelta::from_months(1);
        IS(1);
        d = MonthDelta::from_months(-1);
        IS(-1);
        d = MonthDelta::from_months(0);
        IS(0);
        d = MonthDelta::from_months(2147483647);
        IS(2147483647);
        d = MonthDelta::from_months(-2147483647);
        IS(-2147483647);

        d = MonthDelta_from_months(6);
        IS(6);

        MonthDelta_ptr_from_months(&d, -8);
        IS(-8);
    }

    SECTION("creating from a number of years") {
        d = MonthDelta::from_years(1);
        IS(12);
        d = MonthDelta::from_years(-2);
        IS(-24);
        d = MonthDelta::from_years(120);
        IS(1440);
        d = MonthDelta::from_years(-3600);
        IS(-43200);
        d = MonthDelta::from_years(0);
        IS(0);
        d = MonthDelta::from_years(32767);
        IS(393204);
        d = MonthDelta::from_years(-32767);
        IS(-393204);

        d = MonthDelta_from_years(5);
        IS(60);

        MonthDelta_ptr_from_years(&d, -8);
        IS(-96);
    }

    SECTION("creating with no months") {
        d = MonthDelta::zero();
        IS(0);

        d = MonthDelta_zero();
        IS(0);

        MonthDelta_ptr_zero(&d);
        IS(0);
    }
}

TEST_CASE("MonthDelta accessors", "[month-delta]") {
    MonthDelta d1 = MonthDelta::from_months(3),
               d2 = MonthDelta::from_months(100),
               d3 = MonthDelta::from_months(-10),
               d4 = MonthDelta::from_months(-20),
               d5 = MonthDelta::zero();

    CHECK(d1.months() == 3);
    CHECK(d2.months() == 100);
    CHECK(d3.months() == -10);
    CHECK(d4.months() == -20);
    CHECK(d5.months() == 0);

    CHECK(d1.years() == 0);
    CHECK(d2.years() == 8);
    CHECK(d3.years() == 0);
    CHECK(d4.years() == -1);
    CHECK(d5.years() == 0);

    CHECK(d1.years_decimal() == 0.25);
    CHECK(d2.years_decimal() == 8.333333333333334);
    CHECK(d3.years_decimal() == -0.8333333333333334);
    CHECK(d4.years_decimal() == -1.6666666666666667);
    CHECK(d5.years_decimal() == 0.0);
}

TEST_CASE("MonthDelta arithmetic operators", "[month-delta]") {
    MonthDelta d1 = MonthDelta::from_months(4),
               d2 = MonthDelta::from_months(-15),
               d3 = MonthDelta::zero();

    SECTION("is_negative()") {
        CHECK(!d1.is_negative());
        CHECK(d2.is_negative());
        CHECK(!d3.is_negative());
    }

    SECTION("negate()") {
        d1.negate();
        CHECK(d1.months() == -4);
        CHECK(d1.years() == 0);
        d1.negate();
        CHECK(d1.months() == 4);
        CHECK(d1.years() == 0);

        d2.negate();
        CHECK(d2.months() == 15);
        CHECK(d2.years() == 1);
        d2.negate();
        CHECK(d2.months() == -15);
        CHECK(d2.years() == -1);

        d3.negate();
        CHECK(d3.months() == 0);
        CHECK(d3.years() == 0);
        d3.negate();
        CHECK(d3.months() == 0);
        CHECK(d3.years() == 0);
    }

    SECTION("operator-") {
        MonthDelta d;

        d = -d1;
        IS(-4);
        d = -d2;
        IS(15);
        d = -d3;
        IS(0);
    }

    SECTION("operator++ / operator--") {
        MonthDelta d;

        d = MonthDelta::from_months(5);
        IS(5);
        CHECK((d++).months() == 5);
        IS(6);
        CHECK((++d).months() == 7);
        IS(7);
        CHECK((d--).months() == 7);
        IS(6);
        CHECK((--d).months() == 5);
        IS(5);
    }

    SECTION("scaling") {
        MonthDelta d;

        d = MonthDelta::from_months(5);
        IS(5);
        d *= 6;
        IS(30);
        d /= 10;
        IS(3);

        d = MonthDelta::from_months(-10);
        IS(-10);
        d *= 6;
        IS(-60);
        d /= 25;
        IS(-2);

        d = MonthDelta::from_months(9);
        IS(9);
        CHECK((d * 3).months() == 27);
        IS(9);
        CHECK((d * -5).months() == -45);
        IS(9);
        CHECK((d / 4).months() == 2);
        IS(9);
        CHECK((d / -3).months() == -3);
        IS(9);

        d = MonthDelta::from_months(-43);
        IS(-43);
        CHECK((d * 2).months() == -86);
        IS(-43);
        CHECK((d * -4).months() == 172);
        IS(-43);
        CHECK((d / 6).months() == -7);
        IS(-43);
        CHECK((d / -7).months() == 6);
        IS(-43);
    }

    SECTION("addition/subtraction") {
        MonthDelta d;

        d = MonthDelta::from_months(5);
        IS(5);
        d += MonthDelta::from_months(8);
        IS(13);
        d += MonthDelta::from_months(-4);
        IS(9);
        d -= MonthDelta::from_months(12);
        IS(-3);
        d -= MonthDelta::from_months(-5);
        IS(2);

        d = MonthDelta::from_months(-13);
        IS(-13);
        CHECK((d + MonthDelta::from_months(4)).months() == -9);
        IS(-13);
        CHECK((d + MonthDelta::from_months(-7)).months() == -20);
        IS(-13);
        CHECK((d - MonthDelta::from_months(8)).months() == -21);
        IS(-13);
        CHECK((d - MonthDelta::from_months(-34)).months() == 21);
        IS(-13);
    }
}

TEST_CASE("MonthDelta comparison operators", "[month-delta]") {
    MonthDelta d1 = MonthDelta::from_months(19),
               d2 = MonthDelta::from_months(21),
               d3 = MonthDelta::from_months(-13),
               d4 = MonthDelta::from_months(-13),
               d5 = MonthDelta::zero();

    CHECK(MonthDelta::compare(d1, d2) < 0);
    CHECK(MonthDelta::compare(d1, d3) > 0);
    CHECK(MonthDelta::compare(d1, d5) > 0);
    CHECK(MonthDelta::compare(d3, d4) == 0);
    CHECK(MonthDelta::compare(d4, d3) == 0);
    CHECK(MonthDelta::compare(d5, d5) == 0);

    CHECK(d3 == d4);
    CHECK(d4 == d3);
    CHECK(!(d1 == d2));
    CHECK(!(d1 == d5));
    CHECK(d1 != d2);
    CHECK(d5 != d1);

    CHECK(d1 < d2);
    CHECK(d3 < d1);
    CHECK(!(d5 < d4));
    CHECK(!(d3 < d4));

    CHECK(d1 <= d2);
    CHECK(d3 <= d2);
    CHECK(!(d5 <= d4));
    CHECK(d3 <= d4);

    CHECK(d1 > d3);
    CHECK(d2 > d1);
    CHECK(d5 > d3);
    CHECK(!(d3 > d4));
    CHECK(!(d3 > d2));
    CHECK(!(d1 > d2));

    CHECK(d1 >= d3);
    CHECK(d2 >= d1);
    CHECK(d5 >= d3);
    CHECK(d3 >= d4);
    CHECK(!(d5 >= d2));
}

