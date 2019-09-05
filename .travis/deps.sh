#!/bin/bash

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    eval "$(curl -sL https://swiftenv.fuller.li/install.sh)";
    export PATH="$HOME/.swiftenv/bin:$HOME/.swiftenv/shims:$PATH";
fi