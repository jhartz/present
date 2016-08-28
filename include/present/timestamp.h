/*
 * Present - Date/Time Library
 *
 * Definition of the Timestamp structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-timestamp-data.h"

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
 * Enum Definitions
 */

enum PresentTimestampError {
    Timestamp_ERROR_NONE = 0
    , Timestamp_INVALID_TIME_T
    , Timestamp_INVALID_STRUCT_TM
};

/*
 * C++ Class / C Struct Definition
 */

struct PRESENT_API Timestamp {
    enum PresentTimestampError error;
    struct PresentTimestampData data_;

#ifdef __cplusplus
    static Timestamp create(const time_t timestamp);

    static Timestamp create(
        const struct tm & tm,
        const TimeDelta & timeZoneOffset);
    static Timestamp create_utc(const struct tm & tm);
    static Timestamp create_local(const struct tm & tm);

    static Timestamp create(
        const Date & date,
        const ClockTime & clockTime,
        const TimeDelta & timeZoneOffset);
    static Timestamp create_utc(const Date & date, const ClockTime & clockTime);
    static Timestamp create_local(
        const Date & date,
        const ClockTime & clockTime);

    static Timestamp now();

    static Timestamp epoch();

    time_t get_time_t() const;

    struct tm get_struct_tm(const TimeDelta & timeZoneOffset) const;
    struct tm get_struct_tm_utc() const;
    struct tm get_struct_tm_local() const;

    Date get_date(const TimeDelta & timeZoneOffset) const;
    Date get_date_utc() const;
    Date get_date_local() const;

    ClockTime get_clock_time(const TimeDelta & timeZoneOffset) const;
    ClockTime get_clock_time_utc() const;
    ClockTime get_clock_time_local() const;

    TimeDelta get_difference(const Timestamp & other) const;
    TimeDelta get_absolute_difference(const Timestamp & other) const;

    Timestamp & operator+=(const TimeDelta &);
    Timestamp & operator+=(const DayDelta &);
    Timestamp & operator+=(const MonthDelta &);
    Timestamp & operator-=(const TimeDelta &);
    Timestamp & operator-=(const DayDelta &);
    Timestamp & operator-=(const MonthDelta &);

    friend const Timestamp operator+(const Timestamp &, const TimeDelta &);
    friend const Timestamp operator+(const Timestamp &, const DayDelta &);
    friend const Timestamp operator+(const Timestamp &, const MonthDelta &);
    friend const Timestamp operator-(const Timestamp &, const TimeDelta &);
    friend const Timestamp operator-(const Timestamp &, const DayDelta &);
    friend const Timestamp operator-(const Timestamp &, const MonthDelta &);

    friend bool operator==(const Timestamp &, const Timestamp &);
    friend bool operator!=(const Timestamp &, const Timestamp &);

    friend bool operator<(const Timestamp &, const Timestamp &);
    friend bool operator<=(const Timestamp &, const Timestamp &);
    friend bool operator>(const Timestamp &, const Timestamp &);
    friend bool operator>=(const Timestamp &, const Timestamp &);

    PRESENT_BOILERPLATE_CONSTRUCTORS(Timestamp)
#endif
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

PRESENT_API struct Timestamp
Timestamp_create_from_time_t(const time_t timestamp);


PRESENT_API struct Timestamp
Timestamp_create_from_struct_tm(
        const struct tm tm,
        const struct TimeDelta * const timeZoneOffset);

PRESENT_API struct Timestamp
Timestamp_create_from_struct_tm_utc(const struct tm tm);

PRESENT_API struct Timestamp
Timestamp_create_from_struct_tm_local(const struct tm tm);


PRESENT_API struct Timestamp
Timestamp_create(
        const struct Date * const date,
        const struct ClockTime * const clockTime,
        const struct TimeDelta * const timeZoneOffset);

PRESENT_API struct Timestamp
Timestamp_create_utc(
        const struct Date * const date,
        const struct ClockTime * const clockTime);

PRESENT_API struct Timestamp
Timestamp_create_local(
        const struct Date * const date,
        const struct ClockTime * const clockTime);


PRESENT_API struct Timestamp
Timestamp_now();

PRESENT_API struct Timestamp
Timestamp_epoch();


PRESENT_API time_t
Timestamp_get_time_t(const struct Timestamp * const self);


PRESENT_API struct tm
Timestamp_get_struct_tm(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset);

PRESENT_API struct tm
Timestamp_get_struct_tm_utc(const struct Timestamp * const self);

PRESENT_API struct tm
Timestamp_get_struct_tm_local(const struct Timestamp * const self);


PRESENT_API struct Date
Timestamp_get_date(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset);

PRESENT_API struct Date
Timestamp_get_date_utc(const struct Timestamp * const self);

PRESENT_API struct Date
Timestamp_get_date_local(const struct Timestamp * const self);


PRESENT_API struct ClockTime
Timestamp_get_clock_time(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset);

PRESENT_API struct ClockTime
Timestamp_get_clock_time_utc(const struct Timestamp * const self);

PRESENT_API struct ClockTime
Timestamp_get_clock_time_local(const struct Timestamp * const self);


PRESENT_API struct TimeDelta
Timestamp_get_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other);

PRESENT_API struct TimeDelta
Timestamp_get_absolute_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other);


PRESENT_API void
Timestamp_add_time_delta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta);

PRESENT_API void
Timestamp_add_day_delta(
        struct Timestamp * const self,
        const struct DayDelta * const delta);

PRESENT_API void
Timestamp_add_month_delta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta);

PRESENT_API void
Timestamp_subtract_time_delta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta);

PRESENT_API void
Timestamp_subtract_day_delta(
        struct Timestamp * const self,
        const struct DayDelta * const delta);

PRESENT_API void
Timestamp_subtract_month_delta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta);

PRESENT_API bool
Timestamp_equal(const struct Timestamp * const, const struct Timestamp * const);

PRESENT_API bool
Timestamp_less_than(
        const struct Timestamp * const,
        const struct Timestamp * const);

PRESENT_API bool
Timestamp_less_than_or_equal(
        const struct Timestamp * const,
        const struct Timestamp * const);

PRESENT_API bool
Timestamp_greater_than(
        const struct Timestamp * const,
        const struct Timestamp * const);

PRESENT_API bool
Timestamp_greater_than_or_equal(
        const struct Timestamp * const,
        const struct Timestamp * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_TIMESTAMP_H_ */

