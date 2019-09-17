#!/bin/bash
set -e; # Fail on first error

# Prepare
set -o pipefail; # xcpretty
xcodebuild -version;
xcodebuild -showsdks;

# Generate xcodeproj for building/testing
swift package generate-xcodeproj;

# iOS Build & Test
xcodebuild -project SIMDX.xcodeproj -configuration Debug -scheme SIMDX-Package -destination "generic/platform=iOS" | xcpretty;
xcodebuild test -project SIMDX.xcodeproj -configuration Debug -scheme SIMDX-Package -destination "OS=13.0,name=iPhone XS Max" | xcpretty;

# tvOS Build & Test
xcodebuild -project SIMDX.xcodeproj -configuration Debug -scheme SIMDX-Package -destination "generic/platform=tvOS" | xcpretty;
xcodebuild test -project SIMDX.xcodeproj -configuration Debug -scheme SIMDX-Package -destination "OS=13.0,name=Apple TV 4K" | xcpretty;

# watchOS Build & Test
# xcodebuild -project SIMDX.xcodeproj -configuration Debug -scheme SIMDX-Package -destination "generic/platform=watchOS" | xcpretty; # Generic Device: No tests possible
# xcodebuild -project SIMDX.xcodeproj -configuration Debug -scheme SIMDX-Package -destination "OS=6.0,name=Apple Watch Series 5 - 44mm" | xcpretty; # Apple Watch: No tests possible