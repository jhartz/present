/*
 * Present - Date/Time Library
 *
 * Definitions of common types used throughout Present
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present-config.h"

#ifndef _PRESENT_TYPES_H_
#define _PRESENT_TYPES_H_

/*
 * Typedefs for Present boolean type (present_bool)
 */

#ifdef __cplusplus
/* This is C++; we have nice things like "bool" */
typedef bool            present_bool;
#else
# ifdef PRESENT_USE_STDBOOL
/* At least C99 (so we have _Bool) */
typedef _Bool           present_bool;
# else
/* We ain't got nothing */
typedef unsigned char   present_bool;
# endif
#endif

/*
 * Include typedefs for Present int types
 */

#ifdef PRESENT_USE_STDINT
# include "present/utils/typedefs-stdint.h"
#else
# include "present/utils/typedefs-nostdint.h"
#endif

/*
 * Typedefs for common components of dates and times
 */

/* Timestamp */

typedef present_int64   int_timestamp;

/* Time (only used to describe parameters, not used for internal storage) */

typedef present_uint8   int_hour;
typedef present_uint8   int_minute;
typedef present_uint8   int_second;
typedef present_uint64  int_nanosecond;

/* Date */

typedef present_int32   int_year;
/* These values are at least 16-bit, and signed, to make calculations
   (when adding/subtracting deltas) easier */
typedef present_int16   int_month;
typedef present_int16   int_day;
typedef present_int16   int_day_of_year;
typedef present_int8    int_week_of_year;

typedef present_uint8   int_day_of_week;

/* NOTE: 0 is also a valid identifier for Sunday to be compatible with the
   `struct tm` definition, but the ISO8601 definition (using 7 for Sunday)
   is preferred. */
#define DAY_OF_WEEK_SUNDAY_COMPAT (0)
#define DAY_OF_WEEK_MONDAY      (1)
#define DAY_OF_WEEK_TUESDAY     (2)
#define DAY_OF_WEEK_WEDNESDAY   (3)
#define DAY_OF_WEEK_THURSDAY    (4)
#define DAY_OF_WEEK_FRIDAY      (5)
#define DAY_OF_WEEK_SATURDAY    (6)
#define DAY_OF_WEEK_SUNDAY      (7)

/* Time/Day Delta */

typedef present_int64   int_delta;

/* Month Delta */

typedef present_int32   int_month_delta;
typedef present_int32   int_year_delta;

#endif /* _PRESENT_TYPES_H_ */

