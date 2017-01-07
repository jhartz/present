/*
 * Present - Date/Time Library
 *
 * Internal data structure for storing timestamps
 *
 * NOTE: This structure is not meant to be accessed directly, and may change
 * at any time.
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"

#ifndef _PRESENT_TIMESTAMP_DATA_H_
#define _PRESENT_TIMESTAMP_DATA_H_

struct PresentTimestampData {
    /* UNIX timestamp (seconds since 01/01/1970 00:00 UTC) */
    int_timestamp timestamp_seconds;
    /* Supplement to timestamp */
    int_timestamp additional_nanoseconds;
};

#endif /* _PRESENT_TIMESTAMP_DATA_H_ */

