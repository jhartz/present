/*
 * Present - Date/Time Library
 *
 * Utilities and macros for Present header files
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#ifndef _PRESENT_HEADER_UTILS_H_
#define _PRESENT_HEADER_UTILS_H_

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

#endif /* _PRESENT_HEADER_UTILS_H_ */

