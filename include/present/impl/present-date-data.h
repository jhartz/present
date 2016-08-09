/*
 * Present - Date/Time Library
 *
 * Internal data structure for storing dates
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"

#ifndef _PRESENT_DATE_DATA_H_
#define _PRESENT_DATE_DATA_H_

struct PresentDateData {
    int_year year;
    int_month month;
    int_day day;
};

#endif /* _PRESENT_DATE_DATA_H_ */

