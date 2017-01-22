/*
 * Present - Date/Time Library
 *
 * Definition of the Timestamp structure and declarations of the corresponding
 * functions
 *
 * This file may be included individually ONLY if being used by a C compiler.
 * However, it is recommended (and required for C++ projects) to include
 * "present.h" rather than these individual header files.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <time.h>

#include "present/internal/cpp-guard.h"
#include "present/internal/header-utils.h"
#include "present/internal/types.h"

#include "present/internal/present-timestamp-data.h"

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

/**
 * Class or struct representing an exact point in time.
 *
 * This includes a full date and time, and is sensitive to time zones.
 */
struct PRESENT_API Timestamp {
    /**
     * This will be true if there were any errors when creating this Timestamp.
     *
     * @copydoc has_error_epilogue
     */
    present_bool has_error;

    /**
     * If there were any errors when creating this Timestamp, then one or more
     * of these fields will be set.
     *
     * @copydoc errors_epilogue
     */
    struct {
        unsigned int invalid_clock_time : 1,
                     invalid_date       : 1;
    } errors;

    /* Internal data representation */
    struct PresentTimestampData data_;

#ifdef __cplusplus
    /** @copydoc Timestamp_from_time_t */
    static Timestamp create(const time_t time);

    /** @copydoc Timestamp_from_struct_tm */
    static Timestamp create(
        const struct tm & tm,
        const TimeDelta & time_zone_offset);
    /** @copydoc Timestamp_from_struct_tm_utc */
    static Timestamp create_utc(const struct tm & tm);
    /** @copydoc Timestamp_from_struct_tm_local */
    static Timestamp create_local(const struct tm & tm);

    /** @copydoc Timestamp_create */
    static Timestamp create(
        const Date & date,
        const ClockTime & clock_time,
        const TimeDelta & time_zone_offset);
    /** @copydoc Timestamp_create_utc */
    static Timestamp create_utc(
            const Date & date,
            const ClockTime & clock_time);
    /** @copydoc Timestamp_create_local */
    static Timestamp create_local(
        const Date & date,
        const ClockTime & clock_time);

    /** @copydoc Timestamp_now */
    static Timestamp now();

    /** @copydoc Timestamp_epoch */
    static Timestamp epoch();

    /** @copydoc Timestamp_get_time_t */
    time_t get_time_t() const;

    /** @copydoc Timestamp_get_struct_tm */
    struct tm get_struct_tm(const TimeDelta & time_zone_offset) const;
    /** @copydoc Timestamp_get_struct_tm_utc */
    struct tm get_struct_tm_utc() const;
    /** @copydoc Timestamp_get_struct_tm_local */
    struct tm get_struct_tm_local() const;

    /** @copydoc Timestamp_get_date */
    Date get_date(const TimeDelta & time_zone_offset) const;
    /** @copydoc Timestamp_get_date_utc */
    Date get_date_utc() const;
    /** @copydoc Timestamp_get_date_local */
    Date get_date_local() const;

    /** @copydoc Timestamp_get_clock_time */
    ClockTime get_clock_time(const TimeDelta & time_zone_offset) const;
    /** @copydoc Timestamp_get_clock_time_utc */
    ClockTime get_clock_time_utc() const;
    /** @copydoc Timestamp_get_clock_time_local */
    ClockTime get_clock_time_local() const;

    /** @copydoc Timestamp_difference */
    TimeDelta difference(const Timestamp & other) const;
    /** @copydoc Timestamp_absolute_difference */
    TimeDelta absolute_difference(const Timestamp & other) const;

    /** @copydoc Timestamp_add_TimeDelta */
    Timestamp & operator+=(const TimeDelta & delta);
    /** @copydoc Timestamp_add_DayDelta */
    Timestamp & operator+=(const DayDelta & delta);
    /** @copydoc Timestamp_add_MonthDelta */
    Timestamp & operator+=(const MonthDelta & delta);
    /** @copydoc Timestamp_subtract_TimeDelta */
    Timestamp & operator-=(const TimeDelta & delta);
    /** @copydoc Timestamp_subtract_DayDelta */
    Timestamp & operator-=(const DayDelta & delta);
    /** @copydoc Timestamp_subtract_MonthDelta */
    Timestamp & operator-=(const MonthDelta & delta);

    /** @see Timestamp::operator+=(const TimeDelta & delta) */
    friend const Timestamp operator+(
            const Timestamp & lhs,
            const TimeDelta & rhs);
    /** @see Timestamp::operator+=(const TimeDelta & delta) */
    friend const Timestamp operator+(
            const TimeDelta & lhs,
            const Timestamp & rhs);

    /** @see Timestamp::operator+=(const DayDelta & delta) */
    friend const Timestamp operator+(
            const Timestamp & lhs,
            const DayDelta & rhs);
    /** @see Timestamp::operator+=(const DayDelta & delta) */
    friend const Timestamp operator+(
            const DayDelta & lhs,
            const Timestamp & rhs);

    /** @see Timestamp::operator+=(const MonthDelta & delta) */
    friend const Timestamp operator+(
            const Timestamp & lhs,
            const MonthDelta & rhs);
    /** @see Timestamp::operator+=(const MonthDelta & delta) */
    friend const Timestamp operator+(
            const MonthDelta & lhs,
            const Timestamp & rhs);

    /** @see Timestamp::operator-=(const TimeDelta & delta) */
    friend const Timestamp operator-(
            const Timestamp & lhs,
            const TimeDelta & rhs);

    /** @see Timestamp::operator-=(const DayDelta & delta) */
    friend const Timestamp operator-(
            const Timestamp & lhs,
            const DayDelta & rhs);

    /** @see Timestamp::operator-=(const MonthDelta & delta) */
    friend const Timestamp operator-(
            const Timestamp & lhs,
            const MonthDelta & rhs);

    /** @copydoc Timestamp_compare */
    static short compare(const Timestamp & lhs, const Timestamp & rhs);

    /** @copydoc Timestamp_equal */
    friend bool operator==(const Timestamp & lhs, const Timestamp & rhs);
    friend bool operator!=(const Timestamp & lhs, const Timestamp & rhs);

    /** @copydoc Timestamp_less_than */
    friend bool operator<(const Timestamp & lhs, const Timestamp & rhs);
    /** @copydoc Timestamp_less_than_or_equal */
    friend bool operator<=(const Timestamp & lhs, const Timestamp & rhs);
    /** @copydoc Timestamp_greater_than */
    friend bool operator>(const Timestamp & lhs, const Timestamp & rhs);
    /** @copydoc Timestamp_greater_than_or_equal */
    friend bool operator>=(const Timestamp & lhs, const Timestamp & rhs);
#endif
};

/*
 * C Method Declarations
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a new Timestamp based on a "time_t" value (from C's time library).
 *
 * @param time The "time_t" value representing the timestamp.
 */
PRESENT_API struct Timestamp
Timestamp_from_time_t(const time_t time);

/**
 * @copydoc Timestamp_from_time_t
 * @param[out] result A pointer to a struct Timestamp for the result.
 */
PRESENT_API void
Timestamp_ptr_from_time_t(
        struct Timestamp * const result,
        const time_t time);


/**
 * Create a new Timestamp based on a "struct tm" value (from C's time library)
 * in a certain time zone.
 *
 * @param tm The "struct tm" value representing the date and time.
 * @param time_zone_offset The time zone offset (from UTC) used to interpret
 * @p tm.
 */
PRESENT_API struct Timestamp
Timestamp_from_struct_tm(
        const struct tm tm,
        const struct TimeDelta * const time_zone_offset);

/**
 * @copydoc Timestamp_from_struct_tm
 * @param[out] result A pointer to a struct Timestamp for the result.
 */
PRESENT_API void
Timestamp_ptr_from_struct_tm(
        struct Timestamp * const result,
        const struct tm tm,
        const struct TimeDelta * const time_zone_offset);

/**
 * Create a new Timestamp based on a "struct tm" value (from C's time library)
 * in Coordinated Universal Time.
 *
 * @param tm The "struct tm" value representing the date and time.
 */
PRESENT_API struct Timestamp
Timestamp_from_struct_tm_utc(const struct tm tm);

/**
 * @copydoc Timestamp_from_struct_tm_utc
 * @param[out] result A pointer to a struct Timestamp for the result.
 */
PRESENT_API void
Timestamp_ptr_from_struct_tm_utc(
        struct Timestamp * const result,
        const struct tm tm);

/**
 * Create a new Timestamp based on a "struct tm" value (from C's time library)
 * in the system's current local time zone.
 *
 * @param tm The "struct tm" value representing the date and time.
 */
PRESENT_API struct Timestamp
Timestamp_from_struct_tm_local(const struct tm tm);

/**
 * @copydoc Timestamp_from_struct_tm_local
 * @param[out] result A pointer to a struct Timestamp for the result.
 */
PRESENT_API void
Timestamp_ptr_from_struct_tm_local(
        struct Timestamp * const result,
        const struct tm tm);


/**
 * Create a new Timestamp based on a @ref Date and @ref ClockTime in a certain
 * time zone.
 *
 * Future modifications to the original @ref Date and @ref ClockTime do NOT
 * affect the new Timestamp.
 *
 * If the @ref Date or @ref ClockTime is invalid, the Timestamp will have
 * @p has_error and @p errors set.
 *
 * @copydoc check_for_error_timestamp
 *
 * @param date The @ref Date component of the Timestamp.
 * @param clock_time The @ref ClockTime component of the Timestamp.
 * @param time_zone_offset The time zone offset (from UTC) used to interpret
 * @p date and @p clockTime.
 */
PRESENT_API struct Timestamp
Timestamp_create(
        const struct Date * const date,
        const struct ClockTime * const clock_time,
        const struct TimeDelta * const time_zone_offset);

/**
 * @copydoc Timestamp_create
 * @param[out] result A pointer to a struct Timestamp for the result.
 */
PRESENT_API void
Timestamp_ptr_create(
        struct Timestamp * const result,
        const struct Date * const date,
        const struct ClockTime * const clock_time,
        const struct TimeDelta * const time_zone_offset);

/**
 * Create a new Timestamp based on a @ref Date and @ref ClockTime in
 * Coordinated Universal Time.
 *
 * Future modifications to the original @ref Date and @ref ClockTime do NOT
 * affect the new Timestamp.
 *
 * If the @ref Date or @ref ClockTime is invalid, the Timestamp will have
 * @p has_error and @p errors set.
 *
 * @copydoc check_for_error_timestamp
 *
 * @param date The @ref Date component of the Timestamp.
 * @param clock_time The @ref ClockTime component of the Timestamp.
 */
PRESENT_API struct Timestamp
Timestamp_create_utc(
        const struct Date * const date,
        const struct ClockTime * const clock_time);

/**
 * @copydoc Timestamp_create_utc
 * @param[out] result A pointer to a struct Timestamp for the result.
 */
PRESENT_API void
Timestamp_ptr_create_utc(
        struct Timestamp * const result,
        const struct Date * const date,
        const struct ClockTime * const clock_time);

/**
 * Create a new Timestamp based on a @ref Date and @ref ClockTime in the
 * system's current local time zone.
 *
 * Future modifications to the original @ref Date and @ref ClockTime do NOT
 * affect the new Timestamp.
 *
 * If the @ref Date or @ref ClockTime is invalid, the Timestamp will have
 * @p has_error and @p errors set.
 *
 * @copydoc check_for_error_timestamp
 *
 * @param date The @ref Date component of the Timestamp.
 * @param clock_time The @ref ClockTime component of the Timestamp.
 */
PRESENT_API struct Timestamp
Timestamp_create_local(
        const struct Date * const date,
        const struct ClockTime * const clock_time);

/**
 * @copydoc Timestamp_create_local
 * @param[out] result A pointer to a struct Timestamp for the result.
 */
PRESENT_API void
Timestamp_ptr_create_local(
        struct Timestamp * const result,
        const struct Date * const date,
        const struct ClockTime * const clock_time);


/**
 * Create a new Timestamp representing the exact time right now.
 *
 * On most POSIX systems, this will return a Timestamp with up to nanosecond
 * precision (depending on the maximum precision of the machine). On other
 * systems, the Timestamp will only be to the nearest second.
 */
PRESENT_API struct Timestamp
Timestamp_now(void);

/**
 * @copydoc Timestamp_now
 * @param[out] result A pointer to a struct Timestamp for the result.
 */
PRESENT_API void
Timestamp_ptr_now(struct Timestamp * const result);

/**
 * Create a new Timestamp representing the UNIX epoch
 * (Jan. 1, 1970 00:00:00 UTC).
 */
PRESENT_API struct Timestamp
Timestamp_epoch(void);

/**
 * @copydoc Timestamp_epoch
 * @param[out] result A pointer to a struct Timestamp for the result.
 */
PRESENT_API void
Timestamp_ptr_epoch(struct Timestamp * const result);


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
        const struct TimeDelta * const time_zone_offset);

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
 *
 * Modifications to the returned @ref Date do NOT affect the existing
 * Timestamp.
 */
PRESENT_API struct Date
Timestamp_get_date(
        const struct Timestamp * const self,
        const struct TimeDelta * const time_zone_offset);

/**
 * Get the @ref Date component of a Timestamp in Coordinated Universal Time.
 *
 * Modifications to the returned @ref Date do NOT affect the existing
 * Timestamp.
 */
PRESENT_API struct Date
Timestamp_get_date_utc(const struct Timestamp * const self);

/**
 * Get the @ref Date component of a Timestamp in the system's current local
 * time zone.
 *
 * Modifications to the returned @ref Date do NOT affect the existing
 * Timestamp.
 */
PRESENT_API struct Date
Timestamp_get_date_local(const struct Timestamp * const self);


/**
 * Get the @ref ClockTime component of a Timestamp in a certain time zone
 * (represented by an offset from UTC).
 *
 * Modifications to the returned @ref ClockTime do NOT affect the existing
 * Timestamp.
 */
PRESENT_API struct ClockTime
Timestamp_get_clock_time(
        const struct Timestamp * const self,
        const struct TimeDelta * const time_zone_offset);

/**
 * Get the @ref ClockTime component of a Timestamp in Coordinated Universal
 * Time.
 *
 * Modifications to the returned @ref ClockTime do NOT affect the existing
 * Timestamp.
 */
PRESENT_API struct ClockTime
Timestamp_get_clock_time_utc(const struct Timestamp * const self);

/**
 * Get the @ref ClockTime component of a Timestamp in the system's current
 * local time zone.
 *
 * Modifications to the returned @ref ClockTime do NOT affect the existing
 * Timestamp.
 */
PRESENT_API struct ClockTime
Timestamp_get_clock_time_local(const struct Timestamp * const self);


/**
 * Get the difference between two Timestamp instances as a @ref TimeDelta.
 */
PRESENT_API struct TimeDelta
Timestamp_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other);

/**
 * Get the absolute difference between two Timestamp instances as a
 * @ref TimeDelta.
 */
PRESENT_API struct TimeDelta
Timestamp_absolute_difference(
        const struct Timestamp * const self,
        const struct Timestamp * const other);


/**
 * Add a @ref TimeDelta to a Timestamp.
 */
PRESENT_API void
Timestamp_add_TimeDelta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta);

/**
 * Add a @ref DayDelta to a Timestamp.
 */
PRESENT_API void
Timestamp_add_DayDelta(
        struct Timestamp * const self,
        const struct DayDelta * const delta);

/**
 * Add a @ref MonthDelta to a Timestamp.
 */
PRESENT_API void
Timestamp_add_MonthDelta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta);

/**
 * Subtract a @ref TimeDelta from a Timestamp.
 */
PRESENT_API void
Timestamp_subtract_TimeDelta(
        struct Timestamp * const self,
        const struct TimeDelta * const delta);

/**
 * Subtract a @ref DayDelta from a Timestamp.
 */
PRESENT_API void
Timestamp_subtract_DayDelta(
        struct Timestamp * const self,
        const struct DayDelta * const delta);

/**
 * Subtract a @ref MonthDelta from a Timestamp.
 */
PRESENT_API void
Timestamp_subtract_MonthDelta(
        struct Timestamp * const self,
        const struct MonthDelta * const delta);

/**
 * Compare two Timestamp instances.
 *
 * - If lhs < rhs, then a negative integer will be returned.
 * - If lhs == rhs, then 0 will be returned.
 * - If lhs > rhs, then a positive integer will be returned.
 */
PRESENT_API short
Timestamp_compare(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs);

/**
 * Determine whether two Timestamp instances represent the exact same point in
 * time (lhs == rhs).
 */
PRESENT_API present_bool
Timestamp_equal(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs);

/**
 * Determine whether a Timestamp occurs earlier than another Timestamp
 * (lhs < rhs).
 */
PRESENT_API present_bool
Timestamp_less_than(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs);

/**
 * Determine whether a Timestamp occurs earlier than or at the same time as
 * another Timestamp (lhs <= rhs).
 */
PRESENT_API present_bool
Timestamp_less_than_or_equal(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs);

/**
 * Determine whether a Timestamp occurs later than another Timestamp
 * (lhs > rhs).
 */
PRESENT_API present_bool
Timestamp_greater_than(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs);

/**
 * Determine whether a Timestamp occurs later than or at the same time as
 * another Timestamp (lhs >= rhs).
 */
PRESENT_API present_bool
Timestamp_greater_than_or_equal(
        const struct Timestamp * const lhs,
        const struct Timestamp * const rhs);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_TIMESTAMP_H_ */

