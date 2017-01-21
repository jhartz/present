/*
 * Present - Date/Time Library
 *
 * Definitions of utility functions for Present tests
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <sstream>

#include "present.h"

#ifndef _PRESENT_TEST_UTILS_H_
#define _PRESENT_TEST_UTILS_H_

time_t get_local_time_zone_offset_for_date(int_year, int_month, int_day);

std::ostream & operator<<(std::ostream &, ClockTime const &);

std::ostream & operator<<(std::ostream &, Date const &);

std::ostream & operator<<(std::ostream &, DayDelta const &);

std::ostream & operator<<(std::ostream &, MonthDelta const &);

std::ostream & operator<<(std::ostream &, TimeDelta const &);

std::ostream & operator<<(std::ostream &, Timestamp const &);

#endif /* _PRESENT_TEST_UTILS_H_ */

