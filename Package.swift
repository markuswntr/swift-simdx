// swift-tools-version:5.6
import PackageDescription

let package = Package(
  name: "SIMDX",
  products: [
    .library(name: "SIMDX", targets: ["SIMDX"]),
  ],
  dependencies: [
    .package(url: "https://github.com/apple/swift-numerics", from: "1.0.0"),
  ],
  targets: [
    .target(name: "CSIMDX", cSettings: [
      .unsafeFlags(["-march=native"], .when(platforms: [.macOS])),
    ]),
    .target(name: "SIMDX", dependencies: [
      .product(name: "RealModule", package: "swift-numerics"),
      .byName(name: "CSIMDX"),
    ]),
    .testTarget(name: "CSIMDXTests", dependencies: ["CSIMDX"]),
    .testTarget(name: "SIMDXTests", dependencies: ["SIMDX"]),
  ]
)
