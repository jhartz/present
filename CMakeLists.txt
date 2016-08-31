cmake_minimum_required (VERSION 2.6)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/bilke-cmake-modules")
project (Present)

set (Present_VERSION_MAJOR 0)
set (Present_VERSION_MINOR 9)

option (COMPILE_PRESENTCPP
    "Compile the C++ Present library (libpresent) in addition to the C library (libpresentc) - required to use Present C++ classes, to compile the REPL, or to compile the unit tests"
    ON
)

option (COMPILE_REPL
    "Compile the Present REPL (requires libpresentcpp)"
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

option (USE_CXX_AS_CC
    "Use the C++ compiler to compile C files"
    OFF
)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# Set up compiler warnings
include(EnableExtraCompilerWarnings)
globally_enable_extra_compiler_warnings()

# Set up coverage if necessary
if (COMPILE_WITH_COVERAGE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    include(CodeCoverage)
    setup_target_for_coverage(present_coverage present-test coverage)
endif (COMPILE_WITH_COVERAGE)

# Configure a header file to pass some of the CMake settings to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/src/present-config.h.in"
    "${PROJECT_BINARY_DIR}/include/present-config.h"
)

# Add the binary tree to the search path for include files so that we will find
# PresentConfig.h
include_directories ("${PROJECT_BINARY_DIR}/include")

# Add the header include files
include_directories ("${PROJECT_SOURCE_DIR}/include")

# If we're compiling C with a C++ compiler, set that
if (USE_CXX_AS_CC)
    set_source_files_properties(
        src/clock-time.c
        src/date.c
        src/day-delta.c
        src/month-delta.c
        src/time-delta.c
        src/timestamp.c

        PROPERTIES LANGUAGE CXX
    )
endif (USE_CXX_AS_CC)

# Compile the C library
add_library (presentc SHARED
    src/clock-time.c
    src/date.c
    src/day-delta.c
    src/month-delta.c
    src/time-delta.c
    src/timestamp.c
)

# Install the C library
install (
    TARGETS presentc
    DESTINATION lib
)

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

# Alrighty, let's get compiling!
if (COMPILE_PRESENTCPP)
    # Compile the C++ library
    add_library (present SHARED
        src/clock-time.cpp
        src/date.cpp
        src/day-delta.cpp
        src/month-delta.cpp
        src/time-delta.cpp
        src/timestamp.cpp
    )
    target_link_libraries (present
        presentc
    )

    # Install the C++ library
    install (
        TARGETS present
        DESTINATION lib
    )

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
            #test/day-delta-test.cpp
            #test/month-delta-test.cpp
            #test/time-delta-test.cpp
            #test/timestamp-test.cpp
        )
        target_link_libraries (present-test
            present
        )

        enable_testing()
        add_test(NAME present-test COMMAND present-test)
    endif (COMPILE_TESTS)
endif (COMPILE_PRESENTCPP)

# Add documentation generation (Doxygen)
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

# Add support for installing as a package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
    "${PROJECT_SOURCE_DIR}/LICENSE"
)
set (CPACK_PACKAGE_VERSION_MAJOR "${Present_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Present_VERSION_MINOR}")
include (CPack)

