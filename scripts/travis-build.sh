#!/bin/bash

set -e

status() {
    echo ""
    echo "***"
    for arg; do
        echo "*** $arg"
    done
    echo "***"
    echo ""
}

# Only publish documentation/coverage if it's master (and not a pull request)
PUBLISH_DOC=
if [ "$TRAVIS_PULL_REQUEST" = "false" ] && [ "$TRAVIS_BRANCH" = "master" ]; then
    PUBLISH_DOC=yup
fi

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

# Update online API documentation and code coverage report, if necessary
if [ "$PUBLISH_DOC" = "yup" ]; then
    status "Updating doc and coverage..."
    if [ -z "$GITHUB_API_KEY" ]; then
        echo "ERROR: Missing GitHub API key"
        exit 2
    else
        make present_coverage
        make doc
        mkdir -v web_push
        cd web_push
        git clone --depth 1 https://github.com/jhartz/present.git -b gh-pages
        cd present
        rm -rf coverage doc
        cp -R ../../coverage ../../doc .
        git add coverage doc
        git -c user.name=travis -c user.email=travis commit -m "Travis doc commit"

        status "Sending to gh-pages branch..."
        # Make sure to make the output quiet, or else the API token will leak!
        git push -q https://jhartz:$GITHUB_API_KEY@github.com/jhartz/present gh-pages &2>/dev/null
        cd ..
    fi
fi

cd ..
