import XCTest
import SIMDX

final class SIMDX3Tests: XCTestCase {

  func testMultiplyByElement() {
    var float32Storage = SIMDX3<Float32>(3, 8, -32)
    float32Storage = float32Storage * 4 // Scale by 4
    XCTAssertEqual(float32Storage[0], 12)
    XCTAssertEqual(float32Storage[1], 32)
    XCTAssertEqual(float32Storage[2], -128)

    var float64Storage = SIMDX3<Float64>(3, 8, -32)
    float64Storage = float64Storage * 4 // Scale by 4
    XCTAssertEqual(float64Storage[0], 12)
    XCTAssertEqual(float64Storage[1], 32)
    XCTAssertEqual(float64Storage[2], -128)
  }

  func testDivideByElement() {
    var float32Storage = SIMDX3<Float32>(3, 8, -32)
    float32Storage = float32Storage / 2 // Scale by 0.5
    XCTAssertEqual(float32Storage[0], 1.5)
    XCTAssertEqual(float32Storage[1], 4.0)
    XCTAssertEqual(float32Storage[2], -16.0)

    var float64Storage = SIMDX3<Float64>(3, 8, -32)
    float64Storage = float64Storage / 2 // Scale by 0.5
    XCTAssertEqual(float64Storage[0], 1.5)
    XCTAssertEqual(float64Storage[1], 4.0)
    XCTAssertEqual(float64Storage[2], -16.0)
  }
}
