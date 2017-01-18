#!/bin/bash

set -e

CMAKE_ARGS=("-DCMAKE_BUILD_TYPE=Debug" "-DCOMPILE_TESTS=ON" "$@")

mk_build() {
    echo "*** Creating cmake build directory for $1"

    mkdir -pv "builds/$1"
    cd "builds/$1"

    local cc="$2"
    local cxx="$3"
    shift 3

    CC="$cc" CXX="$cxx" cmake "${CMAKE_ARGS[@]}" "$@" ../..

    echo ""
    echo ""

    cd ../..
}

mk_build_for_compiler() {
    local cc="$1"
    local cxx="$2"

    # If cmake is run with "-DCOMPILE_WITH_CXX_AS_CC", then CXX is used
    # instead of CC for compiling c source files.

    #           name            CC      CXX     Other cmake args
    mk_build    "$cc"           "$cc"   "$cxx"
    mk_build    "$cxx"          "$cc"   "$cxx"  -DCOMPILE_WITH_CXX_AS_CC=ON

    mk_build    "$cc"-pthread   "$cc"   "$cxx"  -DPRESENT_USE_PTHREAD=ON
    mk_build    "$cxx"-pthread  "$cc"   "$cxx"  -DPRESENT_USE_PTHREAD=ON -DCOMPILE_WITH_CXX_AS_CC=ON

    mk_build    "$cc"-ansi      "$cc"   "$cxx"  -DCOMPILE_ANSI=ON
    mk_build    "$cxx"-ansi     "$cc"   "$cxx"  -DCOMPILE_ANSI=ON -DCOMPILE_WITH_CXX_AS_CC=ON
}

#                       CC      CXX
mk_build_for_compiler   gcc     g++
mk_build_for_compiler   clang   clang++

