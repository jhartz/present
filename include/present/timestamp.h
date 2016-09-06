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
    , Timestamp_ERROR_INVALID_CLOCK_TIME
    , Timestamp_ERROR_INVALID_DATE
};

/*
 * C++ Class / C Struct Definition
 */

/**
 * Class or struct representing an exact point in time.
 *
 * This includes a full date and time, and is sensitive to time zones.
 */
struct PRESENT_API Timestamp {
    enum PresentTimestampError error;
    struct PresentTimestampData data_;

#ifdef __cplusplus
    /** @copydoc Timestamp_create_from_time_t */
    static Timestamp create(const time_t timestamp);

    /** @copydoc Timestamp_create_from_struct_tm */
    static Timestamp create(
        const struct tm & tm,
        const TimeDelta & timeZoneOffset);
    /** @copydoc Timestamp_create_from_struct_tm_utc */
    static Timestamp create_utc(const struct tm & tm);
    /** @copydoc Timestamp_create_from_struct_tm_local */
    static Timestamp create_local(const struct tm & tm);

    /** @copydoc Timestamp_create */
    static Timestamp create(
        const Date & date,
        const ClockTime & clockTime,
        const TimeDelta & timeZoneOffset);
    /** @copydoc Timestamp_create_utc */
    static Timestamp create_utc(const Date & date, const ClockTime & clockTime);
    /** @copydoc Timestamp_create_local */
    static Timestamp create_local(
        const Date & date,
        const ClockTime & clockTime);

    /** @copydoc Timestamp_now */
    static Timestamp now();

    /** @copydoc Timestamp_epoch */
    static Timestamp epoch();

    /** @copydoc Timestamp_get_time_t */
    time_t get_time_t() const;

    /** @copydoc Timestamp_get_struct_tm */
    struct tm get_struct_tm(const TimeDelta & timeZoneOffset) const;
    /** @copydoc Timestamp_get_struct_tm_utc */
    struct tm get_struct_tm_utc() const;
    /** @copydoc Timestamp_get_struct_tm_local */
    struct tm get_struct_tm_local() const;

    /** @copydoc Timestamp_get_date */
    Date get_date(const TimeDelta & timeZoneOffset) const;
    /** @copydoc Timestamp_get_date_utc */
    Date get_date_utc() const;
    /** @copydoc Timestamp_get_date_local */
    Date get_date_local() const;

    /** @copydoc Timestamp_get_clock_time */
    ClockTime get_clock_time(const TimeDelta & timeZoneOffset) const;
    /** @copydoc Timestamp_get_clock_time_utc */
    ClockTime get_clock_time_utc() const;
    /** @copydoc Timestamp_get_clock_time_local */
    ClockTime get_clock_time_local() const;

    /** @copydoc Timestamp_get_difference */
    TimeDelta get_difference(const Timestamp & other) const;
    /** @copydoc Timestamp_get_absolute_difference */
    TimeDelta get_absolute_difference(const Timestamp & other) const;

    /** @copydoc Timestamp_add_time_delta */
    Timestamp & operator+=(const TimeDelta &);
    /** @copydoc Timestamp_add_day_delta */
    Timestamp & operator+=(const DayDelta &);
    /** @copydoc Timestamp_add_month_delta */
    Timestamp & operator+=(const MonthDelta &);
    /** @copydoc Timestamp_subtract_time_delta */
    Timestamp & operator-=(const TimeDelta &);
    /** @copydoc Timestamp_subtract_day_delta */
    Timestamp & operator-=(const DayDelta &);
    /** @copydoc Timestamp_subtract_month_delta */
    Timestamp & operator-=(const MonthDelta &);

    friend const Timestamp operator+(const Timestamp &, const TimeDelta &);
    friend const Timestamp operator+(const Timestamp &, const DayDelta &);
    friend const Timestamp operator+(const Timestamp &, const MonthDelta &);
    friend const Timestamp operator-(const Timestamp &, const TimeDelta &);
    friend const Timestamp operator-(const Timestamp &, const DayDelta &);
    friend const Timestamp operator-(const Timestamp &, const MonthDelta &);

    /** @copydoc Timestamp_equal */
    friend bool operator==(const Timestamp &, const Timestamp &);
    friend bool operator!=(const Timestamp &, const Timestamp &);

    /** @copydoc Timestamp_less_than */
    friend bool operator<(const Timestamp &, const Timestamp &);
    /** @copydoc Timestamp_less_than_or_equal */
    friend bool operator<=(const Timestamp &, const Timestamp &);
    /** @copydoc Timestamp_greater_than */
    friend bool operator>(const Timestamp &, const Timestamp &);
    /** @copydoc Timestamp_greater_than_or_equal */
    friend bool operator>=(const Timestamp &, const Timestamp &);
#endif
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a new Timestamp based on a "time_t" value (from C's time library).
 *
 * @param timestamp The "time_t" value representing the timestamp.
 */
PRESENT_API struct Timestamp
Timestamp_create_from_time_t(const time_t timestamp);


/**
 * Create a new Timestamp based on a "struct tm" value (from C's time library)
 * in a certain time zone.
 *
 * @param tm The "struct tm" value representing the date and time.
 * @param timeZoneOffset The time zone offset (from UTC) used to interpret
 * @p tm.
 */
PRESENT_API struct Timestamp
Timestamp_create_from_struct_tm(
        const struct tm tm,
        const struct TimeDelta * const timeZoneOffset);

/**
 * Create a new Timestamp based on a "struct tm" value (from C's time library)
 * in Coordinated Universal Time.
 *
 * @param tm The "struct tm" value representing the date and time.
 */
PRESENT_API struct Timestamp
Timestamp_create_from_struct_tm_utc(const struct tm tm);

/**
 * Create a new Timestamp based on a "struct tm" value (from C's time library)
 * in the system's current local time zone.
 *
 * @param tm The "struct tm" value representing the date and time.
 */
PRESENT_API struct Timestamp
Timestamp_create_from_struct_tm_local(const struct tm tm);


/**
 * Create a new Timestamp based on a @ref Date and @ref ClockTime in a certain
 * time zone.
 *
 * @param date The @ref Date component of the Timestamp.
 * @param clockTime The @ref ClockTime component of the Timestamp.
 * @param timeZoneOffset The time zone offset (from UTC) used to interpret
 * @p date and @p clockTime.
 */
PRESENT_API struct Timestamp
Timestamp_create(
        const struct Date * const date,
        const struct ClockTime * const clockTime,
        const struct TimeDelta * const timeZoneOffset);

/**
 * Create a new Timestamp based on a @ref Date and @ref ClockTime in
 * Coordinated Universal Time.
 *
 * @param date The @ref Date component of the Timestamp.
 * @param clockTime The @ref ClockTime component of the Timestamp.
 */
PRESENT_API struct Timestamp
Timestamp_create_utc(
        const struct Date * const date,
        const struct ClockTime * const clockTime);

/**
 * Create a new Timestamp based on a @ref Date and @ref ClockTime in the
 * system's current local time zone.
 *
 * @param date The @ref Date component of the Timestamp.
 * @param clockTime The @ref ClockTime component of the Timestamp.
 */
PRESENT_API struct Timestamp
Timestamp_create_local(
        const struct Date * const date,
        const struct ClockTime * const clockTime);


/**
 * Create a new Timestamp representing the exact time right now.
 *
 * On most POSIX systems, this will return a Timestamp with up to nanosecond
 * precision (depending on the maximum precision of the machine). On other
 * systems, the Timestamp will only be to the nearest second.
 */
PRESENT_API struct Timestamp
Timestamp_now();

/**
 * Create a new Timestamp representing the UNIX epoch
 * (Jan. 1, 1970 00:00:00 UTC).
 */
PRESENT_API struct Timestamp
Timestamp_epoch();


/**
 * Convert a Timestamp to a "time_t" (from C's time library).
 */
PRESENT_API time_t
Timestamp_get_time_t(const struct Timestamp * const self);


/**
 * Convert a Timestamp to a "struct tm" (from C's time library) in a certain
 * time zone (represented by an offset from UTC).
 */
PRESENT_API struct tm
Timestamp_get_struct_tm(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset);

/**
 * Convert a Timestamp to a "struct tm" (from C's time library) in Coordinated
 * Universal Time.
 */
PRESENT_API struct tm
Timestamp_get_struct_tm_utc(const struct Timestamp * const self);

/**
 * Convert a Timestamp to a "struct tm" (from C's time library) in the system's
 * current local time zone.
 */
PRESENT_API struct tm
Timestamp_get_struct_tm_local(const struct Timestamp * const self);


/**
 * Get the @ref Date component of a Timestamp in a certain time zone
 * (represented by an offset from UTC).
 */
PRESENT_API struct Date
Timestamp_get_date(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset);

/**
 * Get the @ref Date component of a Timestamp in Coordinated Universal Time.
 */
PRESENT_API struct Date
Timestamp_get_date_utc(const struct Timestamp * const self);

/**
 * Get the @ref Date component of a Timestamp in the system's current local
 * time zone.
 */
PRESENT_API struct Date
Timestamp_get_date_local(const struct Timestamp * const self);


/**
 * Get the @ref ClockTime component of a Timestamp in a certain time zone
 * (represented by an offset from UTC).
 */
PRESENT_API struct ClockTime
Timestamp_get_clock_time(
        const struct Timestamp * const self,
        const struct TimeDelta * const timeZoneOffset);

/**
 * Get the @ref ClockTime component of a Timestamp in Coordinated Universal
 * Time.
 */
PRESENT_API struct ClockTime
Timestamp_get_clock_time_utc(const struct Timestamp * const self);

/**
 * Get the @ref ClockTime component of a Timestamp in the system's current
 * local time zone.
 */
PRESENT_API struct ClockTime
Timestamp_get_clock_time_local(const struct Timestamp * const self);


/**
 * Get the difference between two Timestamp instances as a @ref TimeDelta.
 */
PRESENT_API struct TimeDelta
Timestamp_get_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other);

/**
 * Get the absolute difference between two Timestamp instances as a
 * @ref TimeDelta.
 */
PRESENT_API struct TimeDelta
Timestamp_get_absolute_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other);


/**
 * Add a @ref TimeDelta to a Timestamp.
 */
PRESENT_API void
Timestamp_add_time_delta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta);

/**
 * Add a @ref DayDelta to a Timestamp.
 */
PRESENT_API void
Timestamp_add_day_delta(
        struct Timestamp * const self,
        const struct DayDelta * const delta);

/**
 * Add a @ref MonthDelta to a Timestamp.
 */
PRESENT_API void
Timestamp_add_month_delta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta);

/**
 * Subtract a @ref TimeDelta from a Timestamp.
 */
PRESENT_API void
Timestamp_subtract_time_delta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta);

/**
 * Subtract a @ref DayDelta from a Timestamp.
 */
PRESENT_API void
Timestamp_subtract_day_delta(
        struct Timestamp * const self,
        const struct DayDelta * const delta);

/**
 * Subtract a @ref MonthDelta from a Timestamp.
 */
PRESENT_API void
Timestamp_subtract_month_delta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta);

/**
 * Determine whether two Timestamp instances represent the exact same point in
 * time.
 */
PRESENT_API bool
Timestamp_equal(const struct Timestamp * const, const struct Timestamp * const);

/**
 * Determine whether a Timestamp occurs earlier than another Timestamp.
 */
PRESENT_API bool
Timestamp_less_than(
        const struct Timestamp * const,
        const struct Timestamp * const);

/**
 * Determine whether a Timestamp occurs earlier than or at the same time as
 * another Timestamp.
 */
PRESENT_API bool
Timestamp_less_than_or_equal(
        const struct Timestamp * const,
        const struct Timestamp * const);

/**
 * Determine whether a Timestamp occurs later than another Timestamp.
 */
PRESENT_API bool
Timestamp_greater_than(
        const struct Timestamp * const,
        const struct Timestamp * const);

/**
 * Determine whether a Timestamp occurs later than or at the same time as
 * another Timestamp.
 */
PRESENT_API bool
Timestamp_greater_than_or_equal(
        const struct Timestamp * const,
        const struct Timestamp * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_TIMESTAMP_H_ */

