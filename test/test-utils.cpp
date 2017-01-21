/*
 * Present - Date/Time Library
 *
 * Implementations of utility functions for Present tests
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <stdlib.h>
#include <time.h>

#include "test-utils.hpp"

time_t get_local_time_zone_offset_for_date(
        int_year year, int_month month, int_day day) {
    struct tm tm = {};
    tm.tm_year = year;
    tm.tm_mon = month;
    tm.tm_mday = day;
    tm.tm_hour = 12;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;

    time_t in_local_time = mktime(&tm);
    if (in_local_time == -1) return -1;

    time_t in_utc;

#ifdef _WIN32
    in_utc = _mkgmtime(&tm);
#elif defined(__GNUC__)
    in_utc = timegm(&tm);
#elif defined(_POSIX_VERSION)
    char *tz = getenv("TZ");
    setenv("TZ", "", 1);
    tzset();

    in_utc = mktime(&tm);

    if (tz) {
        setenv("TZ", tz, 1);
    } else {
        unsetenv("TZ");
    }
    tzset();
#else
    return -1;
#endif

    if (in_utc == -1) return -1;

    return in_utc - in_local_time;
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

