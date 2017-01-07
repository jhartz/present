/*
 * Present - Date/Time Library
 *
 * Internal data structure for storing day deltas
 *
 * NOTE: This structure is not meant to be accessed directly, and may change
 * at any time.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"

#ifndef _PRESENT_DAY_DELTA_DATA_H_
#define _PRESENT_DAY_DELTA_DATA_H_

struct PresentDayDeltaData {
    int_delta delta_days;
};

#endif /* _PRESENT_DAY_DELTA_DATA_H_ */

