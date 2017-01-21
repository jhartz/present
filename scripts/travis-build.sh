#!/bin/bash

set -e
DIR="$(dirname "${BASH_SOURCE[0]}")"
. "$DIR/travis-util.sh"

cd build

status "Compiling Present..."
make

status "Running tests..."
bin/present-test

status "All good"

