# Present

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
other C++ programs, and the C methods in `libpresent` can be linked to from
both C and C++ programs.

`libpresentc` consists of only the C source files in `src/`, and thus only
includes the C methods, not the C++ classes. This library can be used instead
of `libpresent` when a C++ compiler is not available or the C++ features are
not needed. It can be compiled by either a C or a C++ compiler.

Present comes with both a traditional `Makefile` or a `CMakeLists.txt` file
that can be used for compilation. However, using CMake is recommended as it
exposes more options and features.

## Requirements

Present uses some newer language features that are only available since C99,
including variadic macros and standard integer and boolean types. Therefore,
it is recommended that Present is compiled with a C99 (or C++11) compliant
compiler.

Present is meant to work across platforms. If there is an issue compiling it
with a C compiler supporting C99 or a C++ compiler supporting C++11, please
file an issue report.

## C++ Examples

## C Examples

