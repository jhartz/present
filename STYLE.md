Present Style Guide
===================

- 80 character line limit
- Struct and class names are CamelCase
- Variable names and functions are underscore_separated (except when including
  the name of a struct or class)
- Comments in headers and C files must use `/* ... */` (C89 compatibility)
- Opening braces should be on the same line as the `if`/`for`/etc. statement
  (EXCEPT for functions; see below)

A function's implementation should have the following lines:

    1. Method return type (with "static", etc., if necessary)
    2. Method name and arguments (IF line is under 80 chars.)
    3. If arguments do not all fit on one line with method name, each should
       be on its own line (indented 2x).
    4. Opening brace of function
    5. Any static variables, followed by a single blank line
    6. Any variable declarations, followed by a single blank line
    7. Any asserts for function arguments, followed by a single blank line
    8. Function implementation
    9. Closing brace of function

