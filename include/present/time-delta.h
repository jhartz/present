/*
 * Present - Date/Time Library
 *
 * Definition of the TimeDelta structure and related methods
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include "present/utils/types.h"
#include "present/utils/utils.h"
#include "present/impl/present-time-delta-data.h"

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
    static TimeDelta from_nanoseconds(int_delta nanoseconds);

    static TimeDelta from_seconds(int_delta seconds);

    static TimeDelta from_minutes(int_delta minutes);

    static TimeDelta from_hours(int_delta hours);

    static TimeDelta from_days(int_delta days);

    static TimeDelta from_weeks(int_delta weeks);

    static TimeDelta zero();

    int_delta get_nanoseconds() const;

    int_delta get_seconds() const;

    double get_seconds_decimal() const;

    int_delta get_minutes() const;

    double get_minutes_decimal() const;

    int_delta get_hours() const;

    double get_hours_decimal() const;

    int_delta get_days() const;

    double get_days_decimal() const;

    int_delta get_weeks() const;

    double get_weeks_decimal() const;

    TimeDelta & operator*=(const int &);
    TimeDelta & operator*=(const double &);
    TimeDelta & operator/=(const int &);
    TimeDelta & operator/=(const double &);

    friend const TimeDelta operator*(const TimeDelta &, const int &);
    friend const TimeDelta operator*(const TimeDelta &, const double &);
    friend const TimeDelta operator/(const TimeDelta &, const int &);
    friend const TimeDelta operator/(const TimeDelta &, const double &);

    TimeDelta & operator+=(const TimeDelta &);
    TimeDelta & operator-=(const TimeDelta &);

    friend const TimeDelta operator+(const TimeDelta &, const TimeDelta &);
    friend const TimeDelta operator-(const TimeDelta &, const TimeDelta &);

    friend bool operator==(const TimeDelta &, const TimeDelta &);
    friend bool operator!=(const TimeDelta &, const TimeDelta &);

    friend bool operator<(const TimeDelta &, const TimeDelta &);
    friend bool operator<=(const TimeDelta &, const TimeDelta &);
    friend bool operator>(const TimeDelta &, const TimeDelta &);
    friend bool operator>=(const TimeDelta &, const TimeDelta &);

    TimeDelta(const TimeDelta &);
    TimeDelta & operator=(const TimeDelta &);

private:
    explicit TimeDelta(PresentTimeDeltaData &);
    TimeDelta();
#endif

    struct PresentTimeDeltaData my_data;
};

/*
 * C Method Definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

struct TimeDelta
TimeDelta_from_nanoseconds(int_delta nanoseconds);

struct TimeDelta
TimeDelta_from_seconds(int_delta seconds);

struct TimeDelta
TimeDelta_from_minutes(int_delta minutes);

struct TimeDelta
TimeDelta_from_hours(int_delta hours);

struct TimeDelta
TimeDelta_from_days(int_delta days);

struct TimeDelta
TimeDelta_from_weeks(int_delta weeks);

struct TimeDelta
TimeDelta_zero();

int_delta
TimeDelta_get_nanoseconds(const struct TimeDelta * const self);

int_delta
TimeDelta_get_seconds(const struct TimeDelta * const self);

double
TimeDelta_get_seconds_decimal(const struct TimeDelta * const self);

int_delta
TimeDelta_get_minutes(const struct TimeDelta * const self);

double
TimeDelta_get_minutes_decimal(const struct TimeDelta * const self);

int_delta
TimeDelta_get_hours(const struct TimeDelta * const self);

double
TimeDelta_get_hours_decimal(const struct TimeDelta * const self);

int_delta
TimeDelta_get_days(const struct TimeDelta * const self);

double
TimeDelta_get_days_decimal(const struct TimeDelta * const self);

int_delta
TimeDelta_get_weeks(const struct TimeDelta * const self);

double
TimeDelta_get_weeks_decimal(const struct TimeDelta * const self);

void TimeDelta_multiply_by(struct TimeDelta * const self, const int scaleFactor);

void TimeDelta_multiply_by_decimal(struct TimeDelta * const self, const double scaleFactor);

void TimeDelta_divide_by(struct TimeDelta * const self, const int scaleFactor);

void TimeDelta_divide_by_decimal(struct TimeDelta * const self, const double scaleFactor);

void TimeDelta_add_time_delta(struct TimeDelta * const self, const struct TimeDelta * const timeDeltaToAdd);

void TimeDelta_subtract_time_delta(struct TimeDelta * const self, const struct TimeDelta * const timeDeltaToSubtract);

bool TimeDelta_equal(const struct TimeDelta * const, const struct TimeDelta * const);

bool TimeDelta_less_than(const struct TimeDelta * const, const struct TimeDelta * const);

bool TimeDelta_less_than_or_equal(const struct TimeDelta * const, const struct TimeDelta * const);

bool TimeDelta_greater_than(const struct TimeDelta * const, const struct TimeDelta * const);

bool TimeDelta_greater_than_or_equal(const struct TimeDelta * const, const struct TimeDelta * const);

#ifdef __cplusplus
}
#endif

#endif /* _PRESENT_TIME_DELTA_H_ */

