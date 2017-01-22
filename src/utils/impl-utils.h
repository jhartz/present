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
 * Compare 2 structs by the value of a data member.
 * __Else__ is returned if the 2 values are equal. If this is the last data
 * member being compared, __Else__ should be 0.
 */
#define STRUCT_COMPARE(__DataMember__, __Else__)                        \
    ((lhs->data_.__DataMember__ < rhs->data_.__DataMember__) ? -1 :     \
        ((lhs->data_.__DataMember__ > rhs->data_.__DataMember__) ? 1 :  \
         (__Else__)))

/**
 * Define a comparison operator for a struct that uses a comparison function
 * (returns <0, =0, or >0) to determine the result.
 *
 * @param __StructName__ The name of the struct being compared.
 * @param __OtherStructName__ The name of the struct being compared to.
 * @param __CompareFunc__ The name of the comparison function (not including
 *        the "Type_" prefix).
 * @param __Operator__ The name, in words, of the operator (used for the
 *        method name).
 * @param __Condition__ The condition of the "compare" result for which this
 *        function should be true.
 */
#define STRUCT_DEFINE_COMPARISON_OPERATOR(                      \
        __StructName__,__OtherStructName__, __CompareFunc__,    \
        __Operator__, __Condition__)                            \
    present_bool __StructName__ ## _ ## __Operator__(           \
            const struct __StructName__ * const lhs,            \
            const struct __OtherStructName__ * const rhs) {     \
        return __StructName__ ## _ ## __CompareFunc__           \
                (lhs, rhs) __Condition__;                       \
    }

/**
 * Shortcut for implementations of an equality function and the 4 standard
 * inequality operators.
 *
 * The implementations are based on the StructName_compare(lhs, rhs) function.
 */
#define STRUCT_COMPARISON_OPERATORS(__StructName__)                     \
    STRUCT_DEFINE_COMPARISON_OPERATOR(__StructName__, __StructName__,   \
            compare, equal, == 0)                                       \
    STRUCT_DEFINE_COMPARISON_OPERATOR(__StructName__, __StructName__,   \
            compare, less_than, < 0)                                    \
    STRUCT_DEFINE_COMPARISON_OPERATOR(__StructName__, __StructName__,   \
            compare, less_than_or_equal, <= 0)                          \
    STRUCT_DEFINE_COMPARISON_OPERATOR(__StructName__, __StructName__,   \
            compare, greater_than, > 0)                                 \
    STRUCT_DEFINE_COMPARISON_OPERATOR(__StructName__, __StructName__,   \
            compare, greater_than_or_equal, >= 0)

/**
 * Shortcut for implementations of an equality function and the 4 standard
 * inequality operators, with a struct of a different type.
 *
 * The implementations are based on the
 * StructName_compare_to_OtherStructName(lhs, rhs) function.
 */
#define STRUCT_COMPARISON_OPERATORS_WITH_OTHER_STRUCT(                      \
        __StructName__, __OtherStructName__)                                \
    STRUCT_DEFINE_COMPARISON_OPERATOR(__StructName__, __OtherStructName__,  \
            compare_to_ ## __OtherStructName__,                             \
            equal_ ## __OtherStructName__, == 0)                            \
    STRUCT_DEFINE_COMPARISON_OPERATOR(__StructName__, __OtherStructName__,  \
            compare_to_ ## __OtherStructName__,                             \
            less_than_ ## __OtherStructName__, < 0)                         \
    STRUCT_DEFINE_COMPARISON_OPERATOR(__StructName__, __OtherStructName__,  \
            compare_to_ ## __OtherStructName__,                             \
            less_than_or_equal_ ## __OtherStructName__, <= 0)               \
    STRUCT_DEFINE_COMPARISON_OPERATOR(__StructName__, __OtherStructName__,  \
            compare_to_ ## __OtherStructName__,                             \
            greater_than_ ## __OtherStructName__, > 0)                      \
    STRUCT_DEFINE_COMPARISON_OPERATOR(__StructName__, __OtherStructName__,  \
            compare_to_ ## __OtherStructName__,                             \
            greater_than_or_equal_ ## __OtherStructName__, >= 0)


#endif /* _PRESENT_IMPL_UTILS_H_ */

