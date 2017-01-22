/*
 * Present - Date/Time Library
 *
 * Header file that includes all structures and methods for:
 * ClockTime, Date, DayDelta, MonthDelta, TimeDelta, Timestamp
 *
 * If this is being read by a C compiler, it will just have the struct
 * definitions and C method declarations (no implementations). In this case,
 * you may include the individual header files in "present/" instead of this
 * file (but this approach is not recommended).
 *
 * If this is being read by a C++ compiler, it will also have the C++ inline
 * method implementations. In this case, you must include this file, NOT the
 * individual header files in "present/". (This is enforced at compile-time;
 * for more, see "present/internal/cpp-guard.h").
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#ifndef _PRESENT_H_
#define _PRESENT_H_


/*
 * Definitions of the C++ classes / C structs;
 * Declarations of the C functions
 */

/*
 * Disable clang warning about "incomplete type could be incompatible with C"
 * (we know this won't happen, since we declare all of our types as extern "C")
 */
#ifdef __cplusplus
# ifdef __clang__
#  ifndef __ICC
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
#  endif
# endif
#endif

#include "present/clock-time.h"
#include "present/date.h"
#include "present/day-delta.h"
#include "present/month-delta.h"
#include "present/time-delta.h"
#include "present/timestamp.h"

#ifdef __cplusplus
# ifdef __clang__
#  ifndef __ICC
#   pragma clang diagnostic pop
#  endif
# endif
#endif


/*
 * Shortcut macro for creating Present delta types
 */

#include "present/internal/delta-constructor-macros.h"

/**
 * Shortcut macro to create an instance of a Present delta type, based on a
 * numeric value and a unit.
 *
 * Possible units and their returned types:
 *
 * - *year*, *years*: @ref MonthDelta
 * - *month*, *months*: @ref MonthDelta
 *
 * - *week*, *weeks*: @ref DayDelta
 * - *day*, *days*: @ref DayDelta
 *
 * - *week_time*, *weeks_time*: @ref TimeDelta
 * - *day_time*, *days_time*: @ref TimeDelta
 *
 * - *hour*, *hours*, *hr*, *hrs*: @ref TimeDelta
 * - *minute*, *minutes*, *min*, *mins*: @ref TimeDelta
 * - *second*, *seconds*, *sec*, *secs*: @ref TimeDelta
 * - *millisecond*, *milliseconds*, *ms*: @ref TimeDelta
 * - *microsecond*, *microseconds*, *us*: @ref TimeDelta
 * - *nanosecond*, *nanoseconds*, *ns*: @ref TimeDelta
 *
 * Note that *day* and *week* return a @p DayDelta, not a @p TimeDelta. If you
 * need a @p TimeDelta instead in one of these situations, you need to use
 * *day_time* and *week_time*.
 *
 * Examples:
 *
 * ```
 * MonthDelta d = present_delta(6, months);
 * DayDelta   d = present_delta(-10, days);
 * TimeDelta  d = present_delta(4, weeks_time);
 * TimeDelta  d = present_delta(1, second);
 * ```
 */
#define present_delta(value, unit)  \
    present_delta_constructor_unit_ ## unit (value)


/*
 * Implementations of the C++ methods (defined "inline")
 */

#ifdef __cplusplus

#include "present/impl/clock-time.hpp"
#include "present/impl/date.hpp"
#include "present/impl/day-delta.hpp"
#include "present/impl/month-delta.hpp"
#include "present/impl/time-delta.hpp"
#include "present/impl/timestamp.hpp"

#endif

#endif /* _PRESENT_H_ */

