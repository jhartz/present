/*
 * Present - Date/Time Library
 *
 * Definition of the ClockTime structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "types.h"
#include "util.h"
#include "impl/clock-time-data.h"

#ifndef _PRESENT_CLOCK_TIME_H_
#define _PRESENT_CLOCK_TIME_H_

/*
 * Forward Declarations
 */

struct MonthDelta;

/*
 * C++ Class / C Struct Definition
 */

struct ClockTime {
#ifdef __cplusplus
    static ClockTime create(int_hour hour, int_minute minute);

    static ClockTime create(int_hour hour, int_minute minute, int_second second);

    static ClockTime create(int_hour hour, int_minute minute, int_second second, int_nanosecond nanosecond);

    static ClockTime create(int_hour hour, int_minute minute, double second);

    static ClockTime midnight();

    static ClockTime noon();

    int_hour get_hour() const;

    int_minute get_minute() const;

    int_second get_second() const;

    int_nanosecond get_nanosecond() const;

    double get_second_decimal() const;

    ClockTime & operator+=(const TimeDelta &);
    ClockTime & operator-=(const TimeDelta &);

    friend const ClockTime operator+(const ClockTime &, const TimeDelta &);
    friend const ClockTime operator-(const ClockTime &, const TimeDelta &);

    friend bool operator==(const ClockTime &, const ClockTime &);
    friend bool operator!=(const ClockTime &, const ClockTime &);

    ClockTime(const ClockTime &);
    ClockTime & operator=(const ClockTime &);

private:
    ClockTime();
#endif

    struct ClockTimeData my_data;
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

#endif /* _PRESENT_CLOCK_TIME_H_ */

