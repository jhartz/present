/*
 * Present - Date/Time Library
 *
 * Internal data structure for storing clock times
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"

#ifndef _PRESENT_CLOCK_TIME_DATA_H_
#define _PRESENT_CLOCK_TIME_DATA_H_

struct PresentClockTimeData {
    /* The number of seconds since midnight */
    int_delta seconds;
    /* Any additional nanoseconds after "seconds"
       (this will always be less than NANOSECONDS_IN_SECOND) */
    int_delta nanoseconds;
};

#endif /* _PRESENT_CLOCK_TIME_DATA_H_ */

