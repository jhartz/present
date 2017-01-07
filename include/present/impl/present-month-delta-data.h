/*
 * Present - Date/Time Library
 *
 * Internal data structure for storing month deltas
 *
 * NOTE: This structure is not meant to be accessed directly, and may change
 * at any time.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"

#ifndef _PRESENT_MONTH_DELTA_DATA_H_
#define _PRESENT_MONTH_DELTA_DATA_H_

struct PresentMonthDeltaData {
    int_month_delta delta_months;
};

#endif /* _PRESENT_MONTH_DELTA_DATA_H_ */

