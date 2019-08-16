// swift-tools-version:5.1
import PackageDescription

let package = Package(
    name: "SIMDX",
    products: [
        .library(name: "CSIMDX", targets: ["CSIMDX"]),
        .library(name: "SIMDX", targets: ["SIMDX"])
    ],
    dependencies: [],
    targets: [
        .target(name: "CSIMDX", dependencies: []), // TODO: Add -mavx2 and -mfpu=neon to clang compile stage
        .testTarget(name: "CSIMDXTests", dependencies: ["CSIMDX"]),
        .target(name: "SIMDX", dependencies: ["CSIMDX"]),
        .testTarget(name: "SIMDXTests", dependencies: ["SIMDX"]),
    ]
)
