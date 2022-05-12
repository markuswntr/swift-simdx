// swift-tools-version:5.4
import PackageDescription

let package = Package(
    name: "SIMDX",
    products: [
        .library(name: "SIMDX", targets: ["SIMDX"]),
    ],
    dependencies: [
      .package(path: "../swift-numerics"),
    ],
    targets: [
        .target(name: "CSIMDX"), // TODO: Add -march=native, -mavx2, -mfpu=neon or equivalent to clang compile stage
        .target(name: "SIMDX", dependencies: [
          .product(name: "RealModule", package: "swift-numerics"),
          "CSIMDX",
        ]),
        .testTarget(name: "CSIMDXTests", dependencies: ["CSIMDX"]),
        .testTarget(name: "SIMDXTests", dependencies: ["SIMDX"]),
    ]
)
