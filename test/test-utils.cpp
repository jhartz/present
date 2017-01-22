/*
 * Present - Date/Time Library
 *
 * Implementations of utility functions for Present tests
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <assert.h>
#include <time.h>

#include "test-utils.hpp"

static const time_t JAN_1_1970_UNIX_TIMESTAMP = 0;
static const time_t JUL_1_1970_UNIX_TIMESTAMP = 15638400;

time_t get_local_time_zone_offset_for_january() {
    struct tm tm = {};
    tm.tm_year = 1970;
    tm.tm_mon = 1;
    tm.tm_mday = 1;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;

    time_t local_timestamp = mktime(&tm);
    assert(local_timestamp != -1);

    return JAN_1_1970_UNIX_TIMESTAMP - local_timestamp;
}

time_t get_local_time_zone_offset_for_july() {
    struct tm tm = {};
    tm.tm_year = 1970;
    tm.tm_mon = 7;
    tm.tm_mday = 1;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;

    time_t local_timestamp = mktime(&tm);
    assert(local_timestamp != -1);

    return JUL_1_1970_UNIX_TIMESTAMP - local_timestamp;
}

std::ostream & operator<<(std::ostream & os, ClockTime const & v) {
    os  << "ClockTime{" << v.hour() << ":" << v.minute() << ":"
        << v.second_decimal() << "}";

    return os;
}

std::ostream & operator<<(std::ostream & os, Date const & v) {
    os  << "Date{" << v.year() << "-" << v.month() << "-" << v.day() << "}";

    return os;
}

std::ostream & operator<<(std::ostream & os, DayDelta const & v) {
    os  << "DayDelta{" << v.days() << " days}";

    return os;
}

std::ostream & operator<<(std::ostream & os, MonthDelta const & v) {
    os  << "MonthDelta{" << v.months() << " months}";

    return os;
}

std::ostream & operator<<(std::ostream & os, TimeDelta const & v) {
    os << "TimeDelta{";
    if (v.weeks() > 1) {
        os  << v.weeks_decimal() << " weeks";
    } else if (v.days() > 1) {
        os  << v.days_decimal() << " days";
    } else if (v.hours() > 1) {
        os  << v.hours_decimal() << " hours";
    } else if (v.minutes() > 1) {
        os  << v.minutes_decimal() << " minutes";
    } else if (v.seconds() > 1) {
        os  << v.seconds_decimal() << " seconds";
    } else if (v.milliseconds() > 1) {
        os  << v.milliseconds_decimal() << " ms";
    } else if (v.microseconds() > 1) {
        os  << v.microseconds_decimal() << " us";
    } else {
        os  << v.nanoseconds() << " ns";
    }
    os << "}";

    return os;
}

std::ostream & operator<<(std::ostream & os, Timestamp const & v) {
    const Date &d = v.get_date_utc();
    const ClockTime &c = v.get_clock_time_utc();
    os  << "Timestamp{UTC="
        << d.year() << "-" << d.month() << "-" << d.day()
        << "_"
        << c.hour() << ":" << c.minute() << ":" << c.second_decimal()
        << "}";

    return os;
}

