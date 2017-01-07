cmake_minimum_required (VERSION 2.8)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/bilke-cmake-modules")
project (Present)

set (Present_VERSION_MAJOR 0)
set (Present_VERSION_MINOR 9)

option (COMPILE_REPL
    "Compile the Present REPL"
    ON
)

option (COMPILE_TESTS
    "Compile the Present unit tests"
    OFF
)

option (COMPILE_WITH_COVERAGE
    "Compile with support for code coverage tools"
    OFF
)

option (COMPILE_WITH_CXX_AS_CC
    "Use the C++ compiler to compile C files"
    OFF
)

option (PRESENT_USE_PTHREAD
    "Use the pthread library to ensure thread safety when calling time functions from the standard library"
    # (only works if Present is the only one calling the standard library functions directly)
    OFF
)

option (COMPILE_ANSI
    "Compile with the -ansi flag"
    OFF
)

###############################################################################
## Setup

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# Set up C/C++ standard
if (COMPILE_ANSI)
    set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -ansi")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi")
endif (COMPILE_ANSI)
#set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -std=c99")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Set up compiler warnings
include(EnableExtraCompilerWarnings)
globally_enable_extra_compiler_warnings()
if (CMAKE_COMPILER_IS_GNUCXX)
    # -Wtype-limits is annoying, and -Wno-parentheses blows up for each unit test
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wno-type-limits -Wno-parentheses")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-type-limits -Wno-parentheses")
endif (CMAKE_COMPILER_IS_GNUCXX)

# Set up coverage if necessary
if (COMPILE_WITH_COVERAGE)
    SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fprofile-arcs -ftest-coverage")
    include(CodeCoverage)
    setup_target_for_coverage(present_coverage present-test coverage)
endif (COMPILE_WITH_COVERAGE)

# Check if newer include files exist
include(CheckIncludeFile)
check_include_file (stdint.h PRESENT_USE_STDINT)
check_include_file (stdbool.h PRESENT_USE_STDBOOL)

# Configure a header file to pass some of the CMake settings to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/include/present-config.h.in"
    "${PROJECT_BINARY_DIR}/include/present-config.h"
)

# Add the binary tree to the search path for include files so that we will find
# present-config.h
include_directories ("${PROJECT_BINARY_DIR}/include")

# Add the header include files
include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("${PROJECT_SOURCE_DIR}/src")

# Install the header files (shared by both the C and C++ libraries)
install (
    FILES
        "${PROJECT_SOURCE_DIR}/include/present.h"
        "${PROJECT_BINARY_DIR}/include/present-config.h"
    DESTINATION include
)
install (
    DIRECTORY
        "${PROJECT_SOURCE_DIR}/include/present"
    DESTINATION include
)

###############################################################################
## libpresent (Present C library)

# If we're compiling C with a C++ compiler, set that
if (COMPILE_WITH_CXX_AS_CC)
    set_source_files_properties(
        src/utils/time-calls.c
        src/clock-time.c
        src/date.c
        src/day-delta.c
        src/month-delta.c
        src/time-delta.c
        src/timestamp.c

        PROPERTIES LANGUAGE CXX
    )
endif (COMPILE_WITH_CXX_AS_CC)

# Compile the C library
add_library (present SHARED
    src/utils/time-calls.c
    src/clock-time.c
    src/date.c
    src/day-delta.c
    src/month-delta.c
    src/time-delta.c
    src/timestamp.c
)

# Link librt if necessary
find_library (LIBRT_PATH rt)
if (LIBRT_PATH)
    target_link_libraries (present
        rt
    )
endif (LIBRT_PATH)

# Link pthread if necessary
if (PRESENT_USE_PTHREAD)
    target_link_libraries (present
        pthread
    )
endif (PRESENT_USE_PTHREAD)

# Install the C library
install (
    TARGETS present
    DESTINATION lib
)

###############################################################################
## REPL and unit tests

if (COMPILE_REPL)
    # Compile the REPL executable
    add_executable (present-repl
        src/repl.cpp
    )
    target_link_libraries (present-repl
        present
    )

    # Install the Present REPL
    install (
        TARGETS present-repl
        DESTINATION bin
    )
endif (COMPILE_REPL)

if (COMPILE_TESTS)
    # Compile the unit tests
    add_executable (present-test
        test/test.cpp

        test/clock-time-test.cpp
        test/date-test.cpp
        test/day-delta-test.cpp
        test/month-delta-test.cpp
        test/time-delta-test.cpp
        test/timestamp-test.cpp
    )
    target_link_libraries (present-test
        present
    )

    enable_testing()
    add_test(NAME present-test COMMAND present-test)
endif (COMPILE_TESTS)

###############################################################################
## Documentation generation (Doxygen)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    configure_file (
        "${PROJECT_SOURCE_DIR}/Doxyfile.in"
        "${PROJECT_BINARY_DIR}/Doxyfile"
        @ONLY
    )
    add_custom_target (doc
        ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif (DOXYGEN_FOUND)

###############################################################################
## Support for installing as a package

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
    "${PROJECT_SOURCE_DIR}/LICENSE"
)
set (CPACK_PACKAGE_VERSION_MAJOR "${Present_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Present_VERSION_MINOR}")
include (CPack)

