/*
 * Present - Date/Time Library
 *
 * REPL program for testing and playing with Present types
 *
 * Licensed under the MIT License.
 * For details, see LICENSE.
 */

#include <iostream>

#include "present.h"

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    std::cout << "Hello, world!" << std::endl;
#ifdef PRESENT_USE_PTHREAD
    std::cout << "Using pthread" << std::endl;
#else
    std::cout << "No pthread" << std::endl;
#endif
}

