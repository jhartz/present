# Present

[![Build Status](https://travis-ci.org/jhartz/present.svg?branch=master)](https://travis-ci.org/jhartz/present)

**A date/time library for C and C++**

Present makes working with dates, times, and durations simple in both C and
C++.

Its functionality is broken down into 6 types. Each has a struct definition
that encapsulates its data. In C, these structs are passed around helper
methods that access and manipulate them, but, in C++, each struct is a
full-blown class.

## Basic Date/Time Types

### ClockTime

A `ClockTime` instance represents a time of day, including hours (0 to 24),
minutes, seconds, and nanoseconds if high precision is needed. No time zone
data is stored with the `ClockTime`.

- `08:00`
- `13:49:49`
- `00:00:00.001`

### Date

A `Date` instance represents a fixed date in time, with a year, month, and day.
It also does not include any time zone information.

- `January 4, 1970`
- `2012-08-01`

### Timestamp

A `Timestamp` instance is a combination of a `ClockTime` and a `Date`,
representing a fixed point in time (up to nanosecond precision).

- `January 1, 1970 00:00:00 UTC`
- `November 24, 2012 11:50 EST`
- `2008-08-09T23:29:59.456+04:00`

## Delta Types

These types are used to represent durations or differences between two points
in time.

### DayDelta

A `DayDelta` represents a duration measured in days or weeks.

- `0 days`
- `+5 days`
- `-18 days`
- `+12 weeks`

### MonthDelta

A `MonthDelta` represents a duration measured in months or years.

- `0 months`
- `+18 months`
- `-6 years`

### TimeDelta

A `TimeDelta` represents a duration measured anywhere from nanoseconds to weeks
(the idea being that seconds, minutes, hours, days, and weeks are all a fixed
amount of nanoseconds).

- `0 seconds`
- `+12 days`
- `-1 hours`
- `+36.35 seconds`
- `+5 minutes`
- `-4 weeks`

Note that `TimeDelta` is a superset of `DayDelta`, meaning that a `TimeDelta`
instance can represent anything that a `DayDelta` instance can. However, the
2 separate types exist because there are times when dealing with a duration in
days or weeks makes sense, but having more precision that that just gets messy
(for example, when dealing with `Date` instances that do not represent a
specific point in time and have no concept of time of day).

On the other hand, `MonthDelta` instances do not overlay with the other deltas
because months cannot be converted to a smaller unit (such as days) accurately.

## Interactions Between Types

One of Present's most powerful features is the simplicity of interactions
between various types. For example, applying deltas to clock times, dates, and
timestamps is quick and simple.

Examples of interactions:

- Adding a `TimeDelta` to a `ClockTime`
- Adding a `DayDelta` or `MonthDelta` to a `Date`
- Adding any type of delta to a `Timestamp`
- Using a `TimeDelta` as a time zone offset when creating a `Timestamp`

Additionally, the C++ classes support operator overloading, so all the code
involving these actions looks and feels intuitive.

## Requirements

Present uses some newer language features that are only available since C99,
including variadic macros and standard integer and boolean types. Therefore,
it is recommended that Present is compiled with a C99 (or C++11) compliant
compiler.

Present is meant to work across platforms. If there is an issue compiling it
with a C compiler supporting C99 or a C++ compiler supporting C++11, please
file an issue report.

## Building

Present consists of the following libraries:

- `libpresent`: includes the Present C++ classes and C methods
- `libpresentc`: includes only the Present C methods

The C++ classes are, for the most part, wrappers around the C methods. This
way, all the functionality is implemented at the lowest level (`C`) and thus
can be used in both C and C++ projects.

`libpresent` consists of all the source files in `src/`, including both the
`.c` and `.cpp` files (the `.c` files can be compiled with either a C or a C++
compiler without issue). The C++ classes in `libpresent` can be linked to from
C++ programs, and the C methods in `libpresent` can be linked to from both C
and C++ programs.

`libpresentc` consists of only the C source files in `src/`, and thus only
includes the C methods, not the C++ classes. This library can be used instead
of `libpresent` when a C++ compiler is not available or the C++ features are
not needed. It can be compiled by either a C or a C++ compiler.

Present comes with both a traditional `Makefile` and a `CMakeLists.txt` file
that can be used for compilation. However, using CMake is recommended as it
exposes more options and features.

## C++ Examples

```C++
// Either only include the types you need
#include "present/clock-time.h"
#include "present/date.h"
#include "present/day-delta.h"
#include "present/month-delta.h"
#include "present/time-delta.h"
#include "present/timestamp.h"

// Or include them all with this shortcut
#include "present.h"

// Create a ClockTime
ClockTime myClockTime(ClockTime::create(12, 59, 59));
// Add a TimeDelta of 1 second to make it 13:00:00
myClockTime += TimeDelta::fromSeconds(1);

// Create a MonthDelta from months and a MonthDelta from years
MonthDelta myMonthDelta(MonthDelta::from_months(4));
MonthDelta myYearDelta(MonthDelta::from_years(2));
// Some arithmetic modifications and comparisons supported by deltas
myMonthDelta < myYearDelta      // true
myMonthDelta * 6 == myYearDelta // true
myMonthDelta - myYearDelta == -MonthDelta::from_months(20)  // true

// Create some Dates
Date myDate1(Date::create(1969, 4, 19));
Date myDate2(myDate1 + myMonthDelta);
// Dates can be compared too
myDate2 > myDate1       // true

// Create a Timestamp based on the Date and ClockTime above, in UTC
Timestamp myTimestamp(Timestamp::create_utc(myDate, myClockTime));
// Now, get the ClockTime in Eastern Daylight Time (UTC-4:00)
myTimestamp.get_clock_time(TimeDelta::from_hours(-4))   // 09:00:00
```

## C Examples

All of the functionality above can be utilized from pure C as well.

```C
// Create a ClockTime
struct ClockTime myClockTime = ClockTime_create(12, 59, 59);
// Add a TimeDelta of 1 second to make it 13:00:00
const struct TimeDelta tempTimeDelta = TimeDelta_from_seconds(1);
ClockTime_add_time_delta(&myClockTime, &myTimeDelta);

// Create a MonthDelta from months and a MonthDelta from years
struct MonthDelta myMonthDelta = MonthDelta_from_months(4);
struct MonthDelta myYearDelta = MonthDelta_from_years(2);
// Some arithmetic modifications and comparisons supported by deltas
MonthDelta_less_than(&myMonthDelta, &myYearDelta)   // true
struct MonthDelta tempMonthDelta = myMonthDelta;
MonthDelta_multiply_by(&tempMonthDelta, 6);
MonthDelta_equal(&tempMonthDelta, &myYearDelta)     // true

// Create some Dates
struct Date myDate1 = Date_create(1969, 4, 19);
struct Date myDate2 = myDate1;
Date_add_month_delta(&myDate2, &myMonthDelta);
// Dates can be compared too
Date_greater_than(&myDate2, &myDate1)       // true

// Create a Timestamp based on the Date and ClockTime above, in UTC
struct Timestamp myTimestamp = Timestamp_create_utc(&myDate, &myClockTime);
// Now, get the ClockTime in Eastern Daylight Time (UTC-4:00)
const struct TimeDelta tempTimeDelta = TimeDelta_from_hours(-4);
Timestamp_get_clock_time(&myTimestamp, &tempTimeDelta)  // 09:00:00
```

