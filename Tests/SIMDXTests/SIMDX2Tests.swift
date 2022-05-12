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

//        var float64Storage = SIMDX2<Float64>(index0: 3, index1: 8)
//        XCTAssertEqual(float64Storage[.index0], 3)
//        XCTAssertEqual(float64Storage[.index1], 8)
//        float64Storage = float64Storage * 4 // Scale by 4
//        XCTAssertEqual(float64Storage[.index0], 12)
//        XCTAssertEqual(float64Storage[.index1], 32)
//
//        var int32Storage = SIMDX2<Int32>(index0: 3, index1: 8)
//        XCTAssertEqual(int32Storage[.index0], 3)
//        XCTAssertEqual(int32Storage[.index1], 8)
//        int32Storage = int32Storage * 4 // Scale by 4
//        XCTAssertEqual(int32Storage[.index0], 12)
//        XCTAssertEqual(int32Storage[.index1], 32)
//
//        var int64Storage = SIMDX2<Int64>(index0: 3, index1: 8)
//        XCTAssertEqual(int64Storage[.index0], 3)
//        XCTAssertEqual(int64Storage[.index1], 8)
//        int64Storage = int64Storage * 4 // Scale by 4
//        XCTAssertEqual(int64Storage[.index0], 12)
//        XCTAssertEqual(int64Storage[.index1], 32)
    }

    func testDivideByElement() {

//        var float32Storage = SIMDX2<Float32>(3, 8)
//        XCTAssertEqual(float32Storage[0], 3)
//        XCTAssertEqual(float32Storage[1], 8)
//        float32Storage = float32Storage / 2 // Scale by 0.5
//        XCTAssertEqual(float32Storage[0], 1.5)
//        XCTAssertEqual(float32Storage[1], 4.0)

//        var float64Storage = SIMDX2<Float64>(index0: 3, index1: 8)
//        XCTAssertEqual(float64Storage[.index0], 3)
//        XCTAssertEqual(float64Storage[.index1], 8)
//        float64Storage = float64Storage / 2 // Scale by 0.5
//        XCTAssertEqual(float64Storage[.index0], 1.5)
//        XCTAssertEqual(float64Storage[.index1], 4.0)
    }

  func testPerf0() {
    measure {
      for _ in 0...10_000_000 {
        let _ = SIMD2<Float32>(x: 2, y: 3)
      }
    }
  }
  func testPerf1() {
    measure {
      for _ in 0...10_000_000 {
        let _ = SIMDX2<Float32>(2, 3)
      }
    }
  }
  func testPerf2() {
    measure {
      for _ in 0...10_000_000 {
        let _ = SIMD2<Float32>(x: 2, y: 3)
      }
    }
  }
  func testPerf3() {
    measure {
      for _ in 0...10_000_000 {
        let _ = SIMDX2<Float32>(2, 3)
      }
    }
  }
  func testPerf0p1() {
    measure {
      for _ in 0...10_000_000 {
        let _ = SIMD2<Float32>(x: 2, y: 3) + SIMD2<Float32>(x: 2, y: -3)
      }
    }
  }
  func testPerf1p1() {
    measure {
      for _ in 0...10_000_000 {
        let _ = SIMDX2<Float32>(2, 3) + SIMDX2<Float32>(2, -3)
      }
    }
  }
  func testPerf2p1() {
    measure {
      for _ in 0...10_000_000 {
        let _ = SIMD2<Float32>(x: 2, y: 3) + SIMD2<Float32>(x: 2, y: -3)
      }
    }
  }
  func testPerf3p1() {
    measure {
      for _ in 0...10_000_000 {
        let _ = SIMDX2<Float32>(2, 3) + SIMDX2<Float32>(2, -3)
      }
    }
  }
}
