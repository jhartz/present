Present Style Guide
===================

- 80 character line limit
- Indentation is 4 spaces (no tabs)
- Struct and class names are CamelCase
- Variable names and functions are `underscore_separated`, except when
  including the name of a struct or class in the context of a conversion
  (usually preceded by "to", such as `to_TimeDelta`)
- Comments in headers and C files must use `/* ... */` (C89 compatibility)
- Opening braces should be on the same line as the `if`/`for`/etc. statement
  (EXCEPT for functions; see below)

## Function Implementations

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

## Macros

Macros in Present fall into 4 categories:

1.  *Constants*

2.  *Function-like macros that result in a single expression (like a function
    without a return value)*

    These should be callable just like normal functions, and they should
    compute a value without any side effects.

3.  *Function-like macros that result in multiple statements (like a one-line
    function that returns a value)*

    These should be callable like normal "void" functions, and should require
    a semicolon on the end of the statement. For example:

    - Good: `CHECK_DATA(d);`
    - Bad: `CHECK_DATA(d)`

    Additionally, function-like macros should work fine in situations such as:

    ```c
    if (condition) CHECK_DATA(d);
    ```

    To accomplish both these goals, the recommended style is:

    ```c
    #define CHECK_DATA(data)    \
        do {                    \
            ...                 \
        } while (0)
    ```

4.  *Function-like macros that result in function definitions*

    Unlike in the previous case, these should not require a semicolon, as they
    are not called inside other functions.

    Also, since these macros are usually more complex, their arguments should
    stand out; for example, using `__UnderscoresAndCamelCase__` for macro
    arguments is one method to differentiate them from everything else going on
    in the macro.

    Example:

    ```c
    #define EQUALITY_OPERATORS(__StructName__, __DataMember__)              \
        int is_equal(struct __StructName__ *a, struct __StructName__ *b)    \
        {                                                                   \
            return a->(__DataMember__) == b->(__DataMember__);              \
        }                                                                   \
        int is_unequal(struct __StructName__ *a, struct __StructName__ *b)  \
        {                                                                   \
            return a->(__DataMember__) != b->(__DataMember__);              \
        }
    ```

Because preprocessor macros are fickle creatures, these are only guidelines,
and each situation may require special treatment.

