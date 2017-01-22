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

/**
 * Get the number of seconds difference between the local time zone and UTC,
 * in January.
 *
 * This function is only intended for tests, not for actual use.
 */
time_t get_local_time_zone_offset_for_january();

/**
 * Get the number of seconds difference between the local time zone and UTC,
 * in July.
 *
 * This function is only intended for tests, not for actual use.
 */
time_t get_local_time_zone_offset_for_july();

std::ostream & operator<<(std::ostream &, ClockTime const &);

std::ostream & operator<<(std::ostream &, Date const &);

std::ostream & operator<<(std::ostream &, DayDelta const &);

std::ostream & operator<<(std::ostream &, MonthDelta const &);

std::ostream & operator<<(std::ostream &, TimeDelta const &);

std::ostream & operator<<(std::ostream &, Timestamp const &);

#endif /* _PRESENT_TEST_UTILS_H_ */

