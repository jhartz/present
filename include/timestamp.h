/*
 * Present - Date/Time Library
 *
 * Definition of the Timestamp structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present-utils/types.h"
#include "present-utils/utils.h"
#include "present-impl/timestamp-data.h"

#ifndef _PRESENT_TIMESTAMP_H_
#define _PRESENT_TIMESTAMP_H_

/*
 * Forward Declarations
 */

struct ClockTime;
struct Date;
struct MonthDelta;
struct TimeDelta;

/*
 * C++ Class / C Struct Definition
 */

struct Timestamp {
#ifdef __cplusplus
    static Timestamp create(const time_t timestamp);

    static Timestamp create_utc(const struct tm & tm);
    static Timestamp create(const struct tm & tm, const TimeDelta & timeZoneOffset);
    static Timestamp create_local(const struct tm & tm);

    static Timestamp create_utc(const Date & date, const ClockTime & clockTime);
    static Timestamp create(const Date & date, const ClockTime & clockTime, const TimeDelta & timeZoneOffset);
    static Timestamp create_local(const Date & date, const ClockTime & clockTime);

    static Timestamp now();

    static Timestamp epoch();

    Date get_date_utc() const;
    Date get_date(const TimeDelta & timeZoneOffset);
    Date get_date_local() const;

    ClockTime get_clock_time_utc() const;
    ClockTime get_clock_time(const TimeDelta & timeZoneOffset) const;
    ClockTime get_clock_time_local() const;

    Timestamp & operator+=(const TimeDelta &);
    Timestamp & operator+=(const MonthDelta &);
    Timestamp & operator-=(const TimeDelta &);
    Timestamp & operator-=(const MonthDelta &);

    friend const Timestamp operator+(const Timestamp &, const TimeDelta &);
    friend const Timestamp operator+(const Timestamp &, const MonthDelta &);
    friend const Timestamp operator-(const Timestamp &, const TimeDelta &);
    friend const Timestamp operator-(const Timestamp &, const MonthDelta &);

    friend bool operator==(const Timestamp &, const Timestamp &);
    friend bool operator!=(const Timestamp &, const Timestamp &);

    friend bool operator<(const Timestamp &, const Timestamp &);
    friend bool operator<=(const Timestamp &, const Timestamp &);
    friend bool operator>(const Timestamp &, const Timestamp &);
    friend bool operator>=(const Timestamp &, const Timestamp &);

    Timestamp(const Timestamp &);
    Timestamp & operator=(const Timestamp &);

private:
    Timestamp();
#endif

    struct TimestampData my_data;
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_TIMESTAMP_H_ */

