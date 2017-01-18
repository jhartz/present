#!/bin/bash

set -e

successes="Successful:"
fails="FAILED:    "
had_fail=0

mk_test() {
    echo "*** Compiling and running tests for $1"

    cd "builds/$1"

    if make >/dev/null && bin/present-test; then
        successes="$successes $1"
        echo "[ ok ] $1"
    else
        fails="$fails $1"
        echo "[FAIL] $1"
        had_fail=1
    fi

    echo ""
    echo ""

    cd ../..
}

mk_test_for_compiler() {
    local cc="$1"
    local cxx="$2"

    #       name (from mkbuild.sh)

    mk_test "$cc"
    mk_test "$cxx"

    mk_test "$cc"-pthread
    mk_test "$cxx"-pthread

    mk_test "$cc"-ansi
    mk_test "$cxx"-ansi
}

#                       CC      CXX
mk_test_for_compiler    gcc     g++
mk_test_for_compiler    clang   clang++



echo "
===============================================================================
===============================================================================
===============================================================================
"

echo "$successes"
echo "$fails"

if [ "$had_fail" -eq 1 ]; then
    exit 1
fi

