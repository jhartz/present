#!/bin/bash

set -e
DIR="$(dirname "${BASH_SOURCE[0]}")"
. "$DIR/travis-util.sh"

# Set up cmake to run tests (with coverage, if necessary)
CMAKE_ARGS=("-DCMAKE_BUILD_TYPE=Debug" "-DCOMPILE_TESTS=ON")
if [ "$PUBLISH_DOC" = "yup" ]; then
    CMAKE_ARGS=("${CMAKE_ARGS[@]}" "-DCOMPILE_WITH_COVERAGE=ON")
fi

# Run cmake
status "Running cmake..."
"$DIR/mkbuild.sh" "${CMAKE_ARGS[@]}"

