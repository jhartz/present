/*
 * Present - Date/Time Library
 *
 * Internal data structure for storing time deltas
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"

#ifndef _PRESENT_TIME_DELTA_DATA_H_
#define _PRESENT_TIME_DELTA_DATA_H_

struct PresentTimeDeltaData {
    int_delta delta_seconds;
    /* delta_nanoseconds will always be less than NANOSECONDS_IN_SECOND */
    int_delta delta_nanoseconds;
};

#endif /* _PRESENT_TIME_DELTA_DATA_H_ */

