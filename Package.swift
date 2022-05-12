// swift-tools-version:5.4
import PackageDescription

let package = Package(
  name: "SIMDX",
  products: [
  .library(name: "SIMDX", targets: ["SIMDX"]),
  ],
  dependencies: [
//    .package(url: "http://github.com/apple/swift-numerics", from: "1.0.0"),
    .package(path: "../swift-numerics")
  ],
  targets: [
    .target(name: "CSIMDX"),
    .target(name: "SIMDX", dependencies: [
      .product(name: "RealModule", package: "swift-numerics"),
      "CSIMDX",
    ]),
    .testTarget(name: "CSIMDXTests", dependencies: ["CSIMDX"]),
    .testTarget(name: "SIMDXTests", dependencies: ["SIMDX"]),
  ]
)
