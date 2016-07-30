/*
 * Present - Date/Time Library
 *
 * Internal data structure for storing timestamps
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"

#ifndef _PRESENT_TIMESTAMP_DATA_H_
#define _PRESENT_TIMESTAMP_DATA_H_

struct PresentTimestampData {
    time_t timestamp;
    int_nanosecond nanoseconds;
};

#endif /* _PRESENT_TIMESTAMP_DATA_H_ */

