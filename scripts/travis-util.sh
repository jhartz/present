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
#export PUBLISH_DOC=
export PUBLISH_DOC=yup
if [ "$TRAVIS_PULL_REQUEST" = "false" ] && [ "$TRAVIS_BRANCH" = "master" ]; then
    export PUBLISH_DOC=yup
fi

# Build directory to use for documentation
export DOC_BUILD_DIR=builds/gcc
