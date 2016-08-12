/*
 * Present - Date/Time Library
 *
 * Definitions of common types used throughout Present
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#ifndef __cplusplus
#include <stdbool.h>
#endif
#include <stdint.h>
#include <time.h>

#ifndef _PRESENT_TYPES_H_
#define _PRESENT_TYPES_H_

/*
 * Typedefs for common components of dates and times
 */

/* Time */

typedef uint_fast8_t    int_hour;
typedef uint_fast8_t    int_minute;
typedef uint_fast8_t    int_second;
typedef uint_fast64_t   int_nanosecond;

/* Date */

typedef int_fast32_t    int_year;
typedef uint_fast8_t    int_month;
/* The day is at least 16-bit to make calculations (when adding/subtracting
   deltas) easier */
typedef uint_fast16_t   int_day;

typedef uint_fast16_t   int_day_of_year;
typedef uint_fast8_t    int_week_of_year;
typedef uint_fast8_t    int_day_of_week;

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

typedef int_fast64_t    int_delta;

/* Month Delta */

typedef int_fast32_t    int_month_delta;
typedef int_fast16_t    int_year_delta;


#endif /* _PRESENT_TYPES_H_ */

