#!/bin/bash
# Run mkbuild.sh with some nice cmake config, then run mktest.sh

set -e
DIR="$(dirname "${BASH_SOURCE[0]}")"

"$DIR/mkbuild.sh" -DCMAKE_BUILD_TYPE=Debug -DCOMPILE_TESTS=ON

"$DIR/mktest.sh"

