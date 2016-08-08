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
#define OVERLOAD_MAX_3(_1, _2, _3, NAME, ...) NAME
#define OVERLOAD_MAX_4(_1, _2, _3, _4, NAME, ...) NAME

#endif /* _PRESENT_UTILS_H_ */

