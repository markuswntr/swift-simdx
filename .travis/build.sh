#!/bin/bash
set -e; # Fail on first error

# Prepare OS before building
if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    export PATH="$HOME/.swiftenv/bin:$HOME/.swiftenv/shims:$PATH";
else # Debug configuration not building on linux
	swift build;
fi

# Cross compile/testing action
OPTIONAL_QEMU_HOST=""
if [[ "$CROSS_COMPILE" == 1 ]]; then
	if [[ "$ARM_ARCH_DIR" == "aarch64-linux-gnu" ]]; then
		OPTIONAL_QEMU_HOST="qemu-aarch64 -L /usr/aarch64-linux-gnu/";
	else
		OPTIONAL_QEMU_HOST="qemu-arm -L /usr/arm-linux-gnueabi/";
	fi
fi

$OPTIONAL_QEMU_HOST swift build -c release;
$OPTIONAL_QEMU_HOST swift test -c release;
