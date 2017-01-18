/*
 * Present - Date/Time Library
 *
 * Header file that includes all structures and methods for:
 * ClockTime, Date, DayDelta, MonthDelta, TimeDelta, Timestamp
 *
 * If this is being read by a C compiler, it will just have the struct
 * definitions and C method declarations (no implementations). In this case,
 * you may include the individual header files in "present/" instead of this
 * file (but this approach is not recommended).
 *
 * If this is being read by a C++ compiler, it will also have the C++ inline
 * method implementations. In this case, you must include this file, NOT the
 * individual header files in "present/". (This is enforced at compile-time;
 * for more, see "present/internal/cpp-guard.h").
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#ifndef _PRESENT_H_
#define _PRESENT_H_


/*
 * Definitions of the C++ classes / C structs;
 * Declarations of the C functions
 */

/*
 * Disable clang warning about "incomplete type could be incompatible with C"
 * (we know this won't happen, since we declare all of our types as extern "C")
 */
#ifdef __cplusplus
# ifdef __clang__
#  ifndef __ICC
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
#  endif
# endif
#endif

#include "present/clock-time.h"
#include "present/date.h"
#include "present/day-delta.h"
#include "present/month-delta.h"
#include "present/time-delta.h"
#include "present/timestamp.h"

#ifdef __cplusplus
# ifdef __clang__
#  ifndef __ICC
#   pragma clang diagnostic pop
#  endif
# endif
#endif


#ifdef __cplusplus

/*
 * Implementations of the C++ methods (defined "inline")
 */

#include "present/impl/clock-time.hpp"
#include "present/impl/date.hpp"
#include "present/impl/day-delta.hpp"
#include "present/impl/month-delta.hpp"
#include "present/impl/time-delta.hpp"
#include "present/impl/timestamp.hpp"

#endif

#endif /* _PRESENT_H_ */

