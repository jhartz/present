/*
 * Present - Date/Time Library
 *
 * Definition of the TimeDelta structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present-utils/types.h"
#include "present-utils/utils.h"
#include "present-impl/time-delta-data.h"

#ifndef _PRESENT_TIME_DELTA_H_
#define _PRESENT_TIME_DELTA_H_

/*
 * Forward Declarations
 */


/*
 * C++ Class / C Struct Definition
 */

struct TimeDelta {
#ifdef __cplusplus

    TimeDelta(const TimeDelta &);
    TimeDelta & operator=(const TimeDelta &);

private:
    TimeDelta();
#endif

    struct TimeDeltaData my_data;
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

#endif /* _PRESENT_TIME_DELTA_H_ */

