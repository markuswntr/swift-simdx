import XCTest
import SIMDX

final class SIMDX2Tests: XCTestCase {
  
  func testMultiplyByElement() {
    
    var float32Storage = SIMDX2<Float32>(3, 8)
    XCTAssertEqual(float32Storage[0], 3)
    XCTAssertEqual(float32Storage[1], 8)
    float32Storage = float32Storage * 4 // Scale by 4
    XCTAssertEqual(float32Storage[0], 12)
    XCTAssertEqual(float32Storage[1], 32)
    
    var float64Storage = SIMDX2<Float64>(3, 8)
    XCTAssertEqual(float64Storage[0], 3)
    XCTAssertEqual(float64Storage[1], 8)
    float64Storage = float64Storage * 4 // Scale by 4
    XCTAssertEqual(float64Storage[0], 12)
    XCTAssertEqual(float64Storage[1], 32)
  }
  
  func testDivideByElement() {
    
    var float32Storage = SIMDX2<Float32>(3, 8)
    XCTAssertEqual(float32Storage[0], 3)
    XCTAssertEqual(float32Storage[1], 8)
    float32Storage = float32Storage / 2 // Scale by 0.5
    XCTAssertEqual(float32Storage[0], 1.5)
    XCTAssertEqual(float32Storage[1], 4.0)
    
    var float64Storage = SIMDX2<Float64>(3, 8)
    XCTAssertEqual(float64Storage[0], 3)
    XCTAssertEqual(float64Storage[1], 8)
    float64Storage = float64Storage / 2 // Scale by 0.5
    XCTAssertEqual(float64Storage[0], 1.5)
    XCTAssertEqual(float64Storage[1], 4.0)
  }
}
