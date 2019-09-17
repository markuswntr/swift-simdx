#!/bin/bash
set -e; # Fail on first error

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then

    if [[ "$CROSS_COMPILE" == 1 ]]; then
        if [[ "$ARM_ARCH_DIR" == "aarch64-linux-gnu" ]]; then
            #HOST="qemu-aarch64 -L /usr/aarch64-linux-gnu/";
            echo "Cross compiling to aarch64"
        else
            #HOST="qemu-arm -L /usr/arm-linux-gnueabi/";
            echo "Cross compiling to arm"
        fi
    else # CROSS_COMPILE = false
        swift build -c release;
        swift test -c release;
    fi

elif # macOS

    if [[ "$CROSS_COMPILE" == 1 ]]; then
        sh ./ios-build.sh;
    else # CROSS_COMPILE = false
        swift build -c debug;
        swift test -c debug;
        swift build -c release;
    fi
fi
