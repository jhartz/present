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

mkdir -v build
cd build

cmake_args=("-DCMAKE_BUILD_TYPE=Debug" "-DCOMPILE_TESTS=ON")
if [ "$TRAVIS_PULL_REQUEST" = "false" ]; then
    cmake_args=("${cmake_args[@]}" "-DCOMPILE_WITH_COVERAGE=ON")
fi

status "Running cmake with args:" "${cmake_args[@]}"
cmake "${cmake_args[@]}" ..

status "Compiling..."
make

status "Compiling and running tests..."
make test

if [ "$TRAVIS_PULL_REQUEST" = "false" ]; then
    status "Updating doc and coverage..."
    if [ -z "$GITHUB_API_KEY" ]; then
        echo "ERROR: Missing GitHub API key"
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
