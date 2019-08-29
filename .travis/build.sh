#!/bin/bash
set -e; # Fail on first error

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    export PATH="$HOME/.swiftenv/bin:$HOME/.swiftenv/shims:$PATH";
fi

swift build;
# swift build -c release;
swift test;