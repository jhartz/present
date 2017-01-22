/*
 * Present - Date/Time Library
 *
 * Definitions of macros to construst Present delta types.
 *
 * These are not meant to be used directly; instead, they are used by the
 * "present_delta" macro (see present.h).
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#ifndef _PRESENT_DELTA_CONSTRUCTOR_MACROS_H_
#define _PRESENT_DELTA_CONSTRUCTOR_MACROS_H_

/* MonthDelta */

#define present_delta_constructor_unit_year(value)          \
    MonthDelta_from_years(value)
#define present_delta_constructor_unit_years(value)         \
    MonthDelta_from_years(value)

#define present_delta_constructor_unit_month(value)         \
    MonthDelta_from_months(value)
#define present_delta_constructor_unit_months(value)        \
    MonthDelta_from_months(value)

/* DayDelta */

#define present_delta_constructor_unit_week(value)          \
    DayDelta_from_weeks(value)
#define present_delta_constructor_unit_weeks(value)         \
    DayDelta_from_weeks(value)

#define present_delta_constructor_unit_day(value)           \
    DayDelta_from_days(value)
#define present_delta_constructor_unit_days(value)          \
    DayDelta_from_days(value)

/* TimeDelta */

#define present_delta_constructor_unit_week_time(value)     \
    TimeDelta_from_weeks(value)
#define present_delta_constructor_unit_weeks_time(value)    \
    TimeDelta_from_weeks(value)

#define present_delta_constructor_unit_day_time(value)      \
    TimeDelta_from_days(value)
#define present_delta_constructor_unit_days_time(value)     \
    TimeDelta_from_days(value)


#define present_delta_constructor_unit_hour(value)          \
    TimeDelta_from_hours(value)
#define present_delta_constructor_unit_hours(value)         \
    TimeDelta_from_hours(value)
#define present_delta_constructor_unit_hr(value)            \
    TimeDelta_from_hours(value)
#define present_delta_constructor_unit_hrs(value)           \
    TimeDelta_from_hours(value)

#define present_delta_constructor_unit_minute(value)        \
    TimeDelta_from_minutes(value)
#define present_delta_constructor_unit_minutes(value)       \
    TimeDelta_from_minutes(value)
#define present_delta_constructor_unit_min(value)           \
    TimeDelta_from_minutes(value)
#define present_delta_constructor_unit_mins(value)          \
    TimeDelta_from_minutes(value)

#define present_delta_constructor_unit_second(value)        \
    TimeDelta_from_seconds(value)
#define present_delta_constructor_unit_seconds(value)       \
    TimeDelta_from_seconds(value)
#define present_delta_constructor_unit_sec(value)           \
    TimeDelta_from_seconds(value)
#define present_delta_constructor_unit_secs(value)          \
    TimeDelta_from_seconds(value)

#define present_delta_constructor_unit_millisecond(value)   \
    TimeDelta_from_milliseconds(value)
#define present_delta_constructor_unit_milliseconds(value)  \
    TimeDelta_from_milliseconds(value)
#define present_delta_constructor_unit_ms(value)            \
    TimeDelta_from_milliseconds(value)

#define present_delta_constructor_unit_microsecond(value)   \
    TimeDelta_from_microseconds(value)
#define present_delta_constructor_unit_microseconds(value)  \
    TimeDelta_from_microseconds(value)
#define present_delta_constructor_unit_us(value)            \
    TimeDelta_from_microseconds(value)

#define present_delta_constructor_unit_nanosecond(value)    \
    TimeDelta_from_nanoseconds(value)
#define present_delta_constructor_unit_nanoseconds(value)   \
    TimeDelta_from_nanoseconds(value)
#define present_delta_constructor_unit_ns(value)            \
    TimeDelta_from_nanoseconds(value)

#endif /* _PRESENT_DELTA_CONSTRUCTOR_MACROS_H_ */

