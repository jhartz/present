# Present

[![Build Status](https://travis-ci.org/jhartz/present.svg?branch=master)](https://travis-ci.org/jhartz/present)
[Code Coverage](https://jhartz.github.io/present/coverage/src/index.html) (work in progress)

**A small but sane date/time library for C and C++**

Present makes working with dates, times, and durations simple in both C and
C++.

For full documentation, see the [Present wiki](https://github.com/jhartz/present/wiki).

---

Present's functionality is broken down into 6 types. Each has a struct
definition that encapsulates its data. In C, these structs are passed around
helper methods that access and manipulate them, but, in C++, each struct is a
full-blown class with methods (although they remain "Plain Old Data", and thus
can be copied easily and shared with C programs).

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

A `Timestamp` instance is like combination of a `ClockTime` and a `Date`,
representing a fixed point in time (with up to nanosecond precision).

- `January 1, 1970 00:00:00 UTC`
- `November 24, 2012 11:50 EST`
- `2008-08-09T23:29:59.456+04:00`

Unlike just a mere pair of `ClockTime` and `Date`, though, a `Timestamp`
represents a specific *instance* in time. A single timestamp can be represented
in many possible ways (e.g. many different `ClockTime`+`Date` pairs can mean the
same timestamp) depending on time zone interpretations. For example, these are
the same timestamp: `Jan. 1, 2017 11:00 AM EST` and `Jan. 1, 2017 4:00 PM UTC`.

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
timestamps is simple and intuitive.

Examples of interactions:

- Adding a `TimeDelta` to a `ClockTime`
- Adding a `DayDelta` or `MonthDelta` to a `Date`
- Adding any type of delta to a `Timestamp`
- Using a `TimeDelta` as a time zone offset when creating a `Timestamp`

Additionally, in C++, these types support operator overloading, so interacting
with them looks and feels intuitive. For more, see the
[API documentation](https://github.com/jhartz/present/wiki/API-Documentation)
or the examples below.

No part of the Present implementation uses dynamic memory access, so it can be
used on systems that don't support `malloc` and friends, and you don't have to
worry about doing any special cleanup for Present types.

## C++ Examples

```C++
#include "present.h"
```

```C++
// Create a ClockTime
ClockTime myClockTime(ClockTime::create(12, 59, 59));

// Add a TimeDelta of 1 second to make it 13:00:00
myClockTime += TimeDelta::from_seconds(1);
```

```C++
// Create a MonthDelta from months and a MonthDelta from years
MonthDelta myMonthDelta(MonthDelta::from_months(4));
MonthDelta myYearDelta(MonthDelta::from_years(2));

// Some arithmetic modifications and comparisons supported by deltas
myMonthDelta < myYearDelta      // true
myMonthDelta * 6 == myYearDelta // true
myMonthDelta - myYearDelta == -MonthDelta::from_months(20)  // true

// The `present_delta` macro can be used to make creating deltas easier
myClockTime += present_delta(3, hours);
myClockTime += present_delta(-180, mins);
```

```C++
// Create some Dates
Date myDate(Date::create(1969, 4, 19));
Date myDate2(myDate + myMonthDelta);

// Dates can be compared too
myDate2 > myDate  // true
```

```C++
// Create a Timestamp based on the Date and ClockTime above, in UTC
Timestamp myTimestamp(Timestamp::create_utc(myDate, myClockTime));

// Add 4 years to the Timestamp
myTimestamp += present_delta(4, years);

// Now, get the Date and ClockTime in Eastern Daylight Time (UTC-4:00)
// (using the normal TimeDelta constructor, then the present_delta macro)
myTimestamp.get_date(TimeDelta::from_hours(-4))     // 1973-04-19
myTimestamp.get_clock_time(present_delta(-4, hrs))  // 09:00:00
```

## C Examples

All of the functionality above can be utilized from pure C as well.

```C
#include "present.h"
```

```C
// Create a ClockTime
struct ClockTime myClockTime = ClockTime_create(12, 59, 59);

// Add a TimeDelta of 1 second to make it 13:00:00
const struct TimeDelta tempTimeDelta = TimeDelta_from_seconds(1);
ClockTime_add_time_delta(&myClockTime, &tempTimeDelta);
```

```C
// Create a MonthDelta from months and a MonthDelta from years
struct MonthDelta myMonthDelta = MonthDelta_from_months(4);
struct MonthDelta myYearDelta = MonthDelta_from_years(2);

// Some arithmetic modifications and comparisons supported by deltas
MonthDelta_less_than(&myMonthDelta, &myYearDelta)  // true
struct MonthDelta tempMonthDelta = myMonthDelta;
MonthDelta_multiply_by(&tempMonthDelta, 6);
MonthDelta_equal(&tempMonthDelta, &myYearDelta)    // true

// The `present_delta` macro can be used to make creating deltas easier
struct TimeDelta tempTimeDelta1 = present_delta(3, hours),
                 tempTimeDelta2 = present_delta(-180, mins);
ClockTime_add_time_delta(&myClockTime, &tempTimeDelta1);
ClockTime_add_time_delta(&myClockTime, &tempTimeDelta2);
```

```C
// Create some Dates
struct Date myDate = Date_create(1969, 4, 19);
struct Date myDate2 = myDate;
Date_add_month_delta(&myDate2, &myMonthDelta);

// Dates can be compared too
Date_greater_than(&myDate2, &myDate)  // true
```

```C
// Create a Timestamp based on the Date and ClockTime above, in UTC
struct Timestamp myTimestamp = Timestamp_create_utc(&myDate, &myClockTime);

// Add 4 years to the Timestamp
struct MonthDelta tempMonthDeta = present_delta(4, years);
Timestamp_add_month_delta(&myTimestamp, &tempMonthDelta);

// Now, get the Date and ClockTime in Eastern Daylight Time (UTC-4:00)
// (using the normal TimeDelta constructor, then the present_delta macro)
const struct TimeDelta tempTimeDelta1 = TimeDelta_from_hours(-4),
                       tempTimeDelta2 = present_delta(-4, hrs);
tempTimeDelta1 == tempTimeDelta2  // true
Timestamp_get_date(&myTimestamp, &tempTimeDelta1)        // 1973-04-19
Timestamp_get_clock_time(&myTimestamp, &tempTimeDelta2)  // 09:00:00
```

