#!/bin/bash

set -ev

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug -DCOMPILE_TESTS=ON -DCOMPILE_WITH_COVERAGE=ON ..

make
make test

if [ -z "$GITHUB_API_KEY" ]; then
    echo "ERROR: Missing GitHub API key"
else
    make present_coverage
    make doc
    mkdir web_push
    cd web_push
    git clone --depth 1 https://github.com/jhartz/present.git -b gh-pages
    cd present
    rm -rf coverage doc
    cp -R ../../coverage ../../doc .
    git add coverage doc
    git -c user.name=travis -c user.email=travis commit -m "Travis doc commit"
    # Make sure to make the output quiet, or else the API token will leak!
    git push -q https://jhartz:$GITHUB_API_KEY@github.com/jhartz/present gh-pages &2>/dev/null
    cd ..
fi

cd ..
