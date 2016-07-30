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

struct Timestamp
Timestamp_create_from_time_t(const time_t timestamp);


struct Timestamp
Timestamp_create_from_struct_tm_utc(const struct tm tm);

struct Timestamp
Timestamp_create_from_struct_tm(const struct tm tm, const struct TimeDelta * const timeZoneOffset);

struct Timestamp
Timestamp_create_from_struct_tm_local(const struct tm tm);


struct Timestamp
Timestamp_create_utc(const struct Date * const date, const struct ClockTime * const clockTime);

struct Timestamp
Timestamp_create(const struct Date * const date, const struct ClockTime * const clockTime, const struct TimeDelta * const timeZoneOffset);

struct Timestamp
Timestamp_create_local(const struct Date * const date, const struct ClockTime * const clockTime);


struct Timestamp
Timestamp_now();

struct Timestamp
Timestamp_epoch();


struct Date
Timestamp_get_date_utc(const struct Timestamp * const self);

struct Date
Timestamp_get_date(const struct Timestamp * const self, const struct TimeDelta * const timeZoneOffset);

struct Date
Timestamp_get_date_local(const struct Timestamp * const self);


struct ClockTime
Timestamp_get_clock_time_utc(const struct Timestamp * const self);

struct ClockTime
Timestamp_get_clock_time(const struct Timestamp * const self, const struct TimeDelta * const timeZoneOffset);

struct ClockTime
Timestamp_get_clock_time_local(const struct Timestamp * const self);

void
Timestamp_add_time_delta(struct Timestamp * const self, const struct TimeDelta * const delta);

void
Timestamp_add_month_delta(struct Timestamp * const self, const struct MonthDelta * const delta);

void
Timestamp_subtract_time_delta(struct Timestamp * const self, const struct TimeDelta * const delta);

void
Timestamp_subtract_month_delta(struct Timestamp * const self, const struct TimeDelta * const delta);

bool
Timestamp_equal(const struct Timestamp * const, const struct Timestamp * const);

bool
Timestamp_less_than(const struct Timestamp * const, const struct Timestamp * const);

bool
Timestamp_less_than_or_equal(const struct Timestamp * const, const struct Timestamp * const);

bool
Timestamp_greater_than(const struct Timestamp * const, const struct Timestamp * const);

bool
Timestamp_greater_than_or_equal(const struct Timestamp * const, const struct Timestamp * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_TIMESTAMP_H_ */

