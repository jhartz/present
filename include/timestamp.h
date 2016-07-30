/*
 * Present - Date/Time Library
 *
 * Definition of the Timestamp structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present-utils/types.h"
#include "present-utils/utils.h"
#include "present-impl/timestamp-data.h"

#ifndef _PRESENT_TIMESTAMP_H_
#define _PRESENT_TIMESTAMP_H_

/*
 * Forward Declarations
 */

struct Date;
struct ClockTime;
struct TimeDelta;
struct MonthDelta;

/*
 * C++ Class / C Struct Definition
 */

struct Timestamp {
#ifdef __cplusplus

    Timestamp(const Timestamp &);
    Timestamp & operator=(const Timestamp &);

private:
    Timestamp();
#endif

    struct TimestampData my_data;
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

#endif /* _PRESENT_TIMESTAMP_H_ */

