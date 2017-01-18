#!/bin/bash

set -e
DIR="$(dirname "${BASH_SOURCE[0]}")"
. "$DIR/travis-util.sh"

# Compile present and run tests
status "Compiling and running tests..."
"$DIR/mktest.sh"

