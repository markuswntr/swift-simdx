// swift-tools-version:5.1
import PackageDescription

let package = Package(
    name: "SIMDX",
    products: [
        .library(name: "SIMDX", targets: ["SIMDX"])
    ],
    targets: [
        .target(name: "CSIMDX"), // TODO: Add -mavx2 or -march=native and ?-mfpu=neon? to clang compile stage
        .target(name: "SIMDX", dependencies: ["CSIMDX"]),
        .testTarget(name: "CSIMDXTests", dependencies: ["CSIMDX"]),
        .testTarget(name: "SIMDXTests", dependencies: ["SIMDX"]),
    ]
)
