/*
 * Present - Date/Time Library
 *
 * Utilities and macros
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#ifndef _PRESENT_UTILS_H_
#define _PRESENT_UTILS_H_

/*
 * Define class header macro if we're compiling on Windows
 */
#ifdef _WIN32
# ifdef PRESENT_EXPORTS
#  define PRESENT_API __declspec(dllexport)
# else
#  define PRESENT_API __declspec(dllimport)
# endif
#else
# define PRESENT_API
#endif

/*
 * Define macros used for definitions of overloaded functions in C API
 */
#define PRESENT_OVERLOAD_MAX_3(_1, _2, _3, NAME, ...) NAME
#define PRESENT_OVERLOAD_MAX_4(_1, _2, _3, _4, NAME, ...) NAME
#define PRESENT_OVERLOAD_MAX_6(_1, _2, _3, _4, _5, _6, NAME, ...) NAME

/*
 * Define macros used for boilerplate constructors for C++ classes
 */
#define PRESENT_BOILERPLATE_CONSTRUCTORS(_ClassName)                \
    _ClassName(const _ClassName & other)                            \
        : error(other.error), data_(other.data_) {}                 \
    _ClassName & operator=(const _ClassName & other) {              \
        this->error = other.error;                                  \
        this->data_ = other.data_;                                  \
        return *this;                                               \
    }                                                               \
    explicit _ClassName(Present ## _ClassName ## Data & data)       \
        : error(_ClassName ## _ERROR_NONE), data_(data) {}          \
    explicit _ClassName(Present ## _ClassName ## Error & error)     \
        : error(error) {}                                           \
    private:                                                        \
    _ClassName();

#endif /* _PRESENT_UTILS_H_ */

