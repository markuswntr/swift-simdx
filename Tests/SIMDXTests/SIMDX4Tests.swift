//import XCTest
//import SIMDX
//
//final class SIMDX4Tests: XCTestCase {
//
//  func testMultiplyByElement() {
//    var float32Storage = SIMDX4<Float32>(3, 8, -32, 32.5)
//    float32Storage = float32Storage * 4 // Scale by 4
//    XCTAssertEqual(float32Storage[0], 12)
//    XCTAssertEqual(float32Storage[1], 32)
//    XCTAssertEqual(float32Storage[2], -128)
//    XCTAssertEqual(float32Storage[3], 130)
//
//    var float64Storage = SIMDX4<Float64>(3, 8, -32, 32.5)
//    float64Storage = float64Storage * 4 // Scale by 4
//    XCTAssertEqual(float64Storage[0], 12)
//    XCTAssertEqual(float64Storage[1], 32)
//    XCTAssertEqual(float64Storage[2], -128)
//    XCTAssertEqual(float64Storage[3], 130)
//  }
//
//  func testDivideByElement() {
//    var float32Storage = SIMDX4<Float32>(3, 8, -32, 32.5)
//    float32Storage = float32Storage / 2 // Scale by 0.5
//    XCTAssertEqual(float32Storage[0], 1.5)
//    XCTAssertEqual(float32Storage[1], 4.0)
//    XCTAssertEqual(float32Storage[2], -16.0)
//    XCTAssertEqual(float32Storage[3], 16.25)
//
//    var float64Storage = SIMDX4<Float64>(3, 8, -32, 32.5)
//    float64Storage = float64Storage / 2 // Scale by 0.5
//    XCTAssertEqual(float64Storage[0], 1.5)
//    XCTAssertEqual(float64Storage[1], 4.0)
//    XCTAssertEqual(float64Storage[2], -16.0)
//    XCTAssertEqual(float64Storage[3], 16.25)
//  }
//}
