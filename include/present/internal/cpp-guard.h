/*
 * Present - Date/Time Library
 *
 * Header file that creates an error when the Present header files are
 * included individually in C++
 *
 * When Present is used in C++, we maintain a rule that the only way to include
 * Present is to do:  #include "present.h"
 *
 * This is because we need to have all the Present struct definitions before
 * any of the C++ method implementations (so the C++ methods can return other
 * Present types properly). This is taken care of inside "present.h", which
 * includes all the struct definitions before any of the implementations.
 *
 * This does not apply when Present is being used in pure C code with a C
 * compiler since there are no inline C functions, so we do not display this
 * error in that case. (However, it is still recommended that people include
 * "present.h" instead of the individual header files in include/present/...)
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#ifdef __cplusplus
# ifndef _PRESENT_H_
#  error "When using Present in C++, include \"present.h\" instead of any individual header files."
# endif
#endif

