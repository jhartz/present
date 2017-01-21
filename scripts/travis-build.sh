#!/bin/bash

set -e
DIR="$(dirname "${BASH_SOURCE[0]}")"
. "$DIR/travis-util.sh"

# Set up the proper cmake args from the Travis matrix's environment
CMAKE_ARGS=()
for arg_name in "${CMAKE_ARG_NAMES[@]}"; do
    CMAKE_ARGS=("${CMAKE_ARGS[@]}" "-D${arg_name}=${!arg_name}")
done

# Set up cmake to run tests with coverage, if necessary
if [ "$PUBLISH_DOC" = "yup" ]; then
    CMAKE_ARGS=("${CMAKE_ARGS[@]}" "-DCOMPILE_WITH_COVERAGE=ON")
fi

# Make the cmake build directory
mkdir -p build
cd build

# Run cmake
status "Running cmake (CC=$CC CXX=$CXX) with args:" "${CMAKE_ARGS[@]}"
cmake "${CMAKE_ARGS[@]}" ..

# Compile Present and run tests
status "Compiling Present..."
make
status "Running tests..."
bin/present-test

status "All good"

