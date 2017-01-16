/*
 * Present - Date/Time Library
 *
 * Implementation utilities and macros
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

/*
 * IN REMEMBERANCE of the Variadic Macros that used to be here:
 * https://github.com/jhartz/present/blob/d060bb32f2be43299249bad8c7c44f428ff4bcc3/src/present-utils.h
 */

#include <string.h>

#ifndef _PRESENT_IMPL_UTILS_H_
#define _PRESENT_IMPL_UTILS_H_

/** Determine whether a given year is a leap year. */
#define IS_LEAP_YEAR(year)                      \
    ((year % 4 == 0 && year % 100 != 0) ||      \
     (year % 400 == 0))

/** Determine the number of days in a year. */
#define DAYS_IN_YEAR(year)                      \
    (IS_LEAP_YEAR(year) ? 366 : 365)


/** Clear (zero out) a pointer to a struct */
#define CLEAR(ptr)                              \
    memset((void *) (ptr), 0, sizeof(*(ptr)))


/**
 * Macros to create an instance of a struct, populated with either a
 * corresponding data object or an error, and return it.
 *
 * CONSTRUCTOR_HEAD: must be at the very top of the method
 * CONSTRUCTOR_RETURN: pass in the ...Data struct to return a struct wrapping
 * it
 * CONSTRUCTOR_ERROR_RETURN: pass in the name of an error from the struct's
 * corresponding error enum (not including "ClassName_ERROR_")
 */
#define CONSTRUCTOR_HEAD(_ClassName)                    \
    struct _ClassName internal_return_value;            \
    memset((void *)&internal_return_value, 0,           \
            sizeof(struct _ClassName));

#define CONSTRUCTOR_RETURN(_ClassName, _Data)           \
    internal_return_value.data_ = _Data;                \
    return internal_return_value;

#define CONSTRUCTOR_ERROR_RETURN(_ClassName, _Error)    \
    internal_return_value.error =                       \
        _ClassName ## _ERROR_ ## _Error;                \
    return internal_return_value;


/**
 * Compare 2 structs by the value of a data member.
 * _Else is returned if the 2 values are equal. If this is the last data
 * member being compared, _Else should be 0.
 */
#define STRUCT_COMPARE(_DataMember, _Else)                              \
    ((lhs->data_._DataMember < rhs->data_._DataMember) ? -1 :           \
        ((lhs->data_._DataMember > rhs->data_._DataMember) ? 1 :        \
         (_Else)))

/**
 * Define a comparison operator for a struct that uses the struct's "compare"
 * function to determine the result.
 * @param _StructName The name of the struct being compared.
 * @param _Operator The name, in words, of the operator (used for the
 * method name).
 * @param _Condition The condition of the "compare" result for which this
 * function should be true.
 */
#define STRUCT_DEFINE_COMPARISON_OPERATOR(                              \
        _StructName, _Operator, _Condition)                             \
    present_bool _StructName ## _ ## _Operator(                         \
            const struct _StructName * const lhs,                       \
            const struct _StructName * const rhs) {                     \
        return _StructName ## _compare(lhs, rhs) _Condition;            \
    }

/**
 * Shortcut for implementations of an equality function and the 4 standard
 * inequality operators.
 */
#define STRUCT_COMPARISON_OPERATORS(_StructName)                        \
    STRUCT_DEFINE_COMPARISON_OPERATOR(_StructName, equal, == 0)         \
    STRUCT_DEFINE_COMPARISON_OPERATOR(_StructName, less_than, < 0)      \
    STRUCT_DEFINE_COMPARISON_OPERATOR(_StructName,                      \
            less_than_or_equal, <= 0)                                   \
    STRUCT_DEFINE_COMPARISON_OPERATOR(_StructName, greater_than, > 0)   \
    STRUCT_DEFINE_COMPARISON_OPERATOR(_StructName,                      \
            greater_than_or_equal, >= 0)


#endif /* _PRESENT_IMPL_UTILS_H_ */

