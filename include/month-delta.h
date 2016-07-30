/*
 * Present - Date/Time Library
 *
 * Definition of the MonthDelta structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present-utils/types.h"
#include "present-utils/utils.h"
#include "present-impl/month-delta-data.h"

#ifndef _PRESENT_MONTH_DELTA_H_
#define _PRESENT_MONTH_DELTA_H_

/*
 * Forward Declarations
 */


/*
 * C++ Class / C Struct Definition
 */

struct MonthDelta {
#ifdef __cplusplus

    MonthDelta(const MonthDelta &);
    MonthDelta & operator=(const MonthDelta &);

private:
    MonthDelta();
#endif

    struct MonthDeltaData my_data;
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_MONTH_DELTA_H_ */

