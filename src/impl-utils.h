/*
 * Present - Date/Time Library
 *
 * Implementation utilities and macros
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#ifndef _PRESENT_IMPL_UTILS_H_
#define _PRESENT_IMPL_UTILS_H_

#include <string.h>

/* Utility macros used to enable macro recursion */
#define EMPTY(...)
#define DEFER(...) __VA_ARGS__ EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__


/**
 * Macros to create an instance of a struct, populated with either a
 * corresponding data object or an error, and return it (for compatibility
 * with both C and C++).
 *
 * CONSTRUCTOR_HEAD: must be at the very top of the method
 * CONSTRUCTOR_RETURN: pass in the ...Data struct to return a struct wrapping
 * it
 * CONSTRUCTOR_ERROR_RETURN: pass in the name of an error from the struct's
 * corresponding error enum (not including "ClassName_ERROR_")
 */
#ifdef __cplusplus

#define CONSTRUCTOR_HEAD(_ClassName)
#define CONSTRUCTOR_RETURN(_ClassName, _Data)           \
    return _ClassName(_Data);
#define CONSTRUCTOR_ERROR_RETURN(_ClassName, _Error)    \
    return _ClassName(_ClassName ## _ERROR_ ## _Error);

#else

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

#endif


/*
 * Set of macros to support STRUCT_BINARY_OPERATOR (below)
 */

/**
 * Determine which macro to use depending on the number of data member names
 * remaining (either the recursive case or the base case).
 * Any more than 6 data members breaks this.
 * The last parameter ("dummy") is passed to make sure that
 * PRESET_OVERLOAD_MAX_6 has at least one variadic argument in there (to be
 * ISO C99 compliant).
 * @param _Symbol The symbol of the comparison operator.
 * @param ... The names of the data members to use for comparison.
 */
#define STRUCT_BINARY_OPERATOR_BODY(_Symbol, ...)                       \
    PRESENT_OVERLOAD_MAX_6(__VA_ARGS__,                                 \
        STRUCT_BINARY_OPERATOR_RECURSION,                               \
        STRUCT_BINARY_OPERATOR_RECURSION,                               \
        STRUCT_BINARY_OPERATOR_RECURSION,                               \
        STRUCT_BINARY_OPERATOR_RECURSION,                               \
        STRUCT_BINARY_OPERATOR_RECURSION,                               \
        STRUCT_BINARY_OPERATOR_BASE_CASE,                               \
        dummy)(_Symbol, __VA_ARGS__)

/* Wrapper for STRUCT_BINARY_OPERATOR_BODY to prevent it being painted blue */
#define STRUCT_BINARY_OPERATOR_BODY_ID() STRUCT_BINARY_OPERATOR_BODY

/**
 * Do the actual comparison between a certain data member in lhs and rhs.
 * @param _Symbol The symbol of the comparison operation.
 * @param _DataMember The name of the data member to use for comparison.
 */
#define STRUCT_BINARY_OPERATOR_BASE_CASE(_Symbol, _DataMember)          \
    return (lhs->data_._DataMember _Symbol rhs->data_._DataMember);

/**
 * If the current data member is the same in both instances of the struct,
 * move on to the next data member, otherwise returns the comparison of the
 * current data member (same comparison as used by the base case).
 * @param _Symbol The symbol of the comparison operation.
 * @param _DataMember The name of the data member to use for comparison.
 * @param ... The names of the rest of the data members.
 */
#define STRUCT_BINARY_OPERATOR_RECURSION(_Symbol, _DataMember, ...)     \
    if (lhs->data_._DataMember == rhs->data_._DataMember) {             \
        DEFER(STRUCT_BINARY_OPERATOR_BODY_ID)()(_Symbol, __VA_ARGS__)   \
    } else {                                                            \
        STRUCT_BINARY_OPERATOR_BASE_CASE(_Symbol, _DataMember)          \
    }

/**
 * Set up the comparison method, then start macro recursion with first call
 * to STRUCT_BINARY_OPERATOR_BODY.
 * @param _StructName The name of the struct being compared.
 * @param _Operator The name, in words, of the operator (used for the
 * method name).
 * @param _Symbol The symbol of the comparison operator.
 * @param ... The names of 1 to 6 data members to use for comparison (from
 * highest to lowest priority).
 */
#define STRUCT_BINARY_OPERATOR_INTERNAL(                                \
        _StructName, _Operator, _Symbol, ...)                           \
    bool _StructName ## _ ## _Operator(                                 \
            const struct _StructName * const lhs,                       \
            const struct _StructName * const rhs) {                     \
        assert(lhs != NULL);                                            \
        assert(rhs != NULL);                                            \
        STRUCT_BINARY_OPERATOR_BODY(_Symbol, __VA_ARGS__)               \
    }

/**
 * Define an operator for a struct that determines its output by comparing
 * one or more data members of the struct. The arguments are the same as
 * STRUCT_BINARY_OPERATOR_INTERNAL.
 * This macro wraps STRUCT_BINARY_OPERATOR_INTERNAL with 5 EXPANDs to
 * account for up to 6 data members (the last one is the base case, and
 * thus doesn't need an EXPAND).
 */
#define STRUCT_BINARY_OPERATOR(...)                                     \
    EXPAND(                                                             \
        EXPAND(                                                         \
            EXPAND(                                                     \
                EXPAND(                                                 \
                    EXPAND(                                             \
                        STRUCT_BINARY_OPERATOR_INTERNAL(__VA_ARGS__))))))

/**
 * Shortcut for implementations of the 4 standard inequality operators.
 */
#define STRUCT_INEQUALITY_OPERATORS(_StructName, ...)                   \
    STRUCT_BINARY_OPERATOR(_StructName, less_than, <,                   \
            __VA_ARGS__)                                                \
    STRUCT_BINARY_OPERATOR(_StructName, less_than_or_equal, <=,         \
            __VA_ARGS__)                                                \
    STRUCT_BINARY_OPERATOR(_StructName, greater_than, >,                \
            __VA_ARGS__)                                                \
    STRUCT_BINARY_OPERATOR(_StructName, greater_than_or_equal, >=,      \
            __VA_ARGS__)


#endif /* _PRESENT_IMPL_UTILS_H_ */

