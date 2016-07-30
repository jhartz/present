/*
 * Present - Date/Time Library
 *
 * Internal data structure for storing time deltas
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present-utils/types.h"
#include "present-utils/utils.h"

#ifndef _PRESENT_TIME_DELTA_DATA_H_
#define _PRESENT_TIME_DELTA_DATA_H_

struct TimeDeltaData {
    int_fast64_t delta_seconds;
    int_fast64_t delta_nanoseconds;
};

#endif /* _PRESENT_TIME_DELTA_DATA_H_ */

