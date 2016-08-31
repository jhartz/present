#!/bin/sh

set -e

if ! which gcovr >/dev/null 2>&1; then
    echo "gcovr not found"
    exit 1
fi

COVERAGE=1 make test
gcovr -r . --object-directory=build --html --html-details -o build/present-test-coverage.html
make clean-gcov

echo "**************************************"
echo "** Coverage information written to: **"
echo "** build/present-test-coverage.html **"
echo "**************************************"

