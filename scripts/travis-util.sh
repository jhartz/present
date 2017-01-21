status() {
    echo ""
    echo "==="
    for arg; do
        echo "=== $arg"
    done
    echo "==="
    echo ""
}

# cmake args that we might find in the environment (from the Travis matrix)
CMAKE_ARG_NAMES=(CMAKE_BUILD_TYPE COMPILE_TESTS COMPILE_WITH_CXX_AS_CC PRESENT_USE_PTHREAD COMPILE_ANSI)

# Only publish documentation/coverage if ...
# - it's not a pull request
# - the branch is master
# - we're compiling in the most normal way possible in the Travis matrix
# - the compiler is gcc
export PUBLISH_DOC=
if  [ "$TRAVIS_PULL_REQUEST" = "false" ] &&
    [ "$TRAVIS_BRANCH" = "master" ] &&
    [ "$TRY_PUBLISH_DOC" = "yup" ] &&
    [ "$CC" = "gcc" ]
then
    export PUBLISH_DOC=yup
fi

