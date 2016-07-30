/*
 * Present - Date/Time Library
 *
 * Definitions of common types used throughout Present
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#ifndef _PRESENT_TYPES_H_
#define _PRESENT_TYPES_H_

/*
 * Typedefs for common components of dates and times
 */

typedef uint_fast8_t    int_hour;
typedef uint_fast8_t    int_minute;
typedef uint_fast8_t    int_second;
typedef uint_fast64_t   int_nanosecond;

typedef int_fast32_t    int_year;
typedef uint_fast8_t    int_month;
typedef uint_fast8_t    int_day;

typedef uint_fast8_t    int_week_of_year;
typedef uint_fast8_t    int_day_of_week;

#define DAY_OF_WEEK_MONDAY      (1)
#define DAY_OF_WEEK_TUESDAY     (2)
#define DAY_OF_WEEK_WEDNESDAY   (3)
#define DAY_OF_WEEK_THURSDAY    (4)
#define DAY_OF_WEEK_FRIDAY      (5)
#define DAY_OF_WEEK_SATURDAY    (6)
#define DAY_OF_WEEK_SUNDAY      (7)

#ifdef __cplusplus
enum class DAY_OF_WEEK {
    MONDAY      = DAY_OF_WEEK_MONDAY,
    TUESDAY     = DAY_OF_WEEK_TUESDAY,
    WEDNESDAY   = DAY_OF_WEEK_WEDNESDAY,
    THURSDAY    = DAY_OF_WEEK_THURSDAY,
    FRIDAY      = DAY_OF_WEEK_FRIDAY,
    SATURDAY    = DAY_OF_WEEK_SATURDAY,
    SUNDAY      = DAY_OF_WEEK_SUNDAY
};
#endif


#endif /* _PRESENT_TYPES_H_ */

