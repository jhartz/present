/*
 * Present - Date/Time Library
 *
 * Definitions of common integer types used throughout Present (without
 * including stdint.h)
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

/*
 * Rules: Must be compatible with C89 (anything that supports C99 won't be
 * using this implementation anyway).
 *    - Nothing from stdint.h
 *    - No "long long"
 */

#ifndef _PRESENT_TYPEDEFS_NO_STDINT_H_
#define _PRESENT_TYPEDEFS_NO_STDINT_H_

typedef signed char     present_int8;
typedef signed int      present_int16;
typedef signed long     present_int32;
typedef signed long     present_int64;

typedef unsigned char   present_uint8;
typedef unsigned int    present_uint16;
typedef unsigned long   present_uint32;
typedef unsigned long   present_uint64;

#endif /* _PRESENT_TYPEDEFS_NO_STDINT_H_ */

