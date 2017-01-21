#!/bin/bash

set -e
DIR="$(dirname "${BASH_SOURCE[0]}")"
. "$DIR/travis-util.sh"

cd build

# Update online API documentation and code coverage report, if necessary
if [ "$PUBLISH_DOC" = "yup" ]; then
    status "Updating doc and coverage..."
    if [ -z "$GITHUB_API_KEY" ]; then
        echo "ERROR: Missing GitHub API key"
        exit 2
    else
        make present_coverage
        make doc
        mkdir -v web_push
        cd web_push
        git clone --depth 1 https://github.com/jhartz/present.git -b gh-pages
        cd present
        rm -rf coverage doc
        cp -R ../../coverage ../../doc .
        cp doc-index.html doc/index.html
        git add -A coverage doc
        git -c user.name=travis -c user.email=travis commit -m "Travis doc commit"

        status "Sending to gh-pages branch..."
        # Make sure to make the output quiet, or else the API token will leak!
        #git push -q https://jhartz:$GITHUB_API_KEY@github.com/jhartz/present gh-pages &2>/dev/null
        git push https://jhartz:$GITHUB_API_KEY@github.com/jhartz/present gh-pages 2>&1 | sed s/$GITHUB_API_KEY/[censored]/g 2>/dev/null
        cd ..
    fi
fi

