#!/bin/bash

# Host Machine
HOST="" # Defaults to wherever the script is executed

# Cross compile/testing action
if [[ "$CROSS_COMPILE" == 1 ]]; then
	if [[ "$ARM_ARCH_DIR" == "aarch64-linux-gnu" ]]; then
		HOST="qemu-aarch64 -L /usr/aarch64-linux-gnu/";
	else
		HOST="qemu-arm -L /usr/arm-linux-gnueabi/";
	fi
fi

$HOST swift build -c debug;
$HOST swift test -c debug;
$HOST swift build -c release;
