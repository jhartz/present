/*
 * Present - Date/Time Library
 *
 * Internal data structure for storing dates
 *
 * NOTE: This structure is not meant to be accessed directly, and may change
 * at any time.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"

#ifndef _PRESENT_DATE_DATA_H_
#define _PRESENT_DATE_DATA_H_

struct PresentDateData {
    int_year year;
    int_month month;
    int_day day;

    /* These are always calculated to match year/month/day */
    int_day_of_year day_of_year;
    int_day_of_week day_of_week;
};

#endif /* _PRESENT_DATE_DATA_H_ */

