/*
 * Present - Date/Time Library
 *
 * Internal data structure for storing clock times
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"

#ifndef _PRESENT_CLOCK_TIME_DATA_H_
#define _PRESENT_CLOCK_TIME_DATA_H_

struct PresentClockTimeData {
    int_hour hour;
    int_minute minute;
    int_second second;
    int_nanosecond nanosecond;
};

#endif /* _PRESENT_CLOCK_TIME_DATA_H_ */

