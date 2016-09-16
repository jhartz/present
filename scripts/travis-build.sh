#!/bin/bash

set -e
DIR="$(dirname "${BASH_SOURCE[0]}")"
. "$DIR/travis-util.sh"

# Make the build directory
mkdir -v build
cd build

# Set up cmake to run tests (with coverage, if necessary)
CMAKE_ARGS=("-DCMAKE_BUILD_TYPE=Debug" "-DCOMPILE_TESTS=ON")
if [ "$PUBLISH_DOC" = "yup" ]; then
    CMAKE_ARGS=("${CMAKE_ARGS[@]}" "-DCOMPILE_WITH_COVERAGE=ON")
fi

# Run cmake
status "Running cmake with args:" "${CMAKE_ARGS[@]}"
cmake "${CMAKE_ARGS[@]}" ..

# Compile present
status "Compiling..."
make

# Compile and run the tests
status "Running tests..."
make test

cd ..
