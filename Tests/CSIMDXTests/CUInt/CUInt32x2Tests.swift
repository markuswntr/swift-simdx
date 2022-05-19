import XCTest
import CSIMDX

final class CUInt32x2Tests: XCTestCase {

  // MARK: Access

  func testGetElement() {
    let collection = CUInt32x2Make(1, 2)

    XCTAssertEqual(CUInt32x2GetElement(collection, 0), 1)
    XCTAssertEqual(CUInt32x2GetElement(collection, 1), 2)
  }

  func testSetElement() {
    var collection = CUInt32x2Make(1, 2)

    XCTAssertEqual(CUInt32x2GetElement(collection, 0), 1)
    XCTAssertEqual(CUInt32x2GetElement(collection, 1), 2)

    CUInt32x2SetElement(&collection, 0, 5)
    CUInt32x2SetElement(&collection, 1, 6)

    XCTAssertEqual(CUInt32x2GetElement(collection, 0), 5)
    XCTAssertEqual(CUInt32x2GetElement(collection, 1), 6)
  }

  // MARK: Make

  func testMake() {
    let collection = CUInt32x2Make(.min, .max)

    XCTAssertEqual(CUInt32x2GetElement(collection, 0), .min)
    XCTAssertEqual(CUInt32x2GetElement(collection, 1), .max)
  }

  func testMakeLoad() {
    var array: [UInt32] = [.min, .max]
    let collection = CUInt32x2MakeLoad(&array)

    XCTAssertEqual(CUInt32x2GetElement(collection, 0), .min)
    XCTAssertEqual(CUInt32x2GetElement(collection, 1), .max)
  }

  func testMakeRepeatingElement() {
    let collection = CUInt32x2MakeRepeatingElement(.max)

    XCTAssertEqual(CUInt32x2GetElement(collection, 0), .max)
    XCTAssertEqual(CUInt32x2GetElement(collection, 1), .max)
  }

  func testMakeZero() {
    let collection = CUInt32x2MakeZero()

    XCTAssertEqual(CUInt32x2GetElement(collection, 0), 0)
    XCTAssertEqual(CUInt32x2GetElement(collection, 1), 0)
  }

  // MARK: Comparison

  func testMinimum() {
    let lhs = CUInt32x2Make(34, 12)
    let rhs = CUInt32x2Make(34, 24)
    let storage = CUInt32x2Minimum(lhs, rhs)

    XCTAssertEqual(CUInt32x2GetElement(storage, 0), 34)
    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 12)
  }

  func testMaximum() {
    let lhs = CUInt32x2Make(34, 12)
    let rhs = CUInt32x2Make(34, 24)
    let storage = CUInt32x2Maximum(lhs, rhs)

    XCTAssertEqual(CUInt32x2GetElement(storage, 0), 34)
    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 24)
  }

  // MARK: Arithmetic

  func testAdd() {
    let lhs = CUInt32x2Make(1, 2)
    let rhs = CUInt32x2Make(4, 3)
    let sum = CUInt32x2Add(lhs, rhs)

    XCTAssertEqual(CUInt32x2GetElement(sum, 0), 5)
    XCTAssertEqual(CUInt32x2GetElement(sum, 1), 5)
  }

  func testSubtract() {
    let lhs = CUInt32x2Make(4, 3)
    let rhs = CUInt32x2Make(1, 2)
    let sum = CUInt32x2Subtract(lhs, rhs)

    XCTAssertEqual(CUInt32x2GetElement(sum, 0), 3)
    XCTAssertEqual(CUInt32x2GetElement(sum, 1), 1)

  }

  func testMultiply() {
    let lhs = CUInt32x2Make(1, 2)
    let rhs = CUInt32x2Make(4, 3)
    let product = CUInt32x2Multiply(lhs, rhs)

    XCTAssertEqual(CUInt32x2GetElement(product, 0), 4)
    XCTAssertEqual(CUInt32x2GetElement(product, 1), 6)
  }

  // MARK: Binary

  func testBitwiseNot() {
    let operand = CUInt32x2Make(0b0000_1111, 0b1111_0000)
    let storage = CUInt32x2BitwiseNot(operand)
    XCTAssertEqual(CUInt32x2GetElement(storage, 0), ~(0b0000_1111))
    XCTAssertEqual(CUInt32x2GetElement(storage, 1), ~(0b1111_0000))
  }

  func testBitwiseAnd() {
    let lhs = CUInt32x2Make(0b0000_1111, 0b1111_0000)
    let rhs = CUInt32x2Make(0b1111_1111, 0b0000_0000)
    let storage = CUInt32x2BitwiseAnd(lhs, rhs)
    XCTAssertEqual(CUInt32x2GetElement(storage, 0), 0b0000_1111 & 0b1111_1111)
    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 0b1111_0000 & 0b0000_0000)
  }

  func testBitwiseAndNot() {
    let lhs = CUInt32x2Make(0b0000_1111, 0b1111_0000)
    let rhs = CUInt32x2Make(0b1111_1111, 0b0000_0000)
    let storage = CUInt32x2BitwiseAndNot(lhs, rhs)
    XCTAssertEqual(CUInt32x2GetElement(storage, 0), (~0b0000_1111) & 0b1111_1111)
    XCTAssertEqual(CUInt32x2GetElement(storage, 1), (~0b1111_0000) & 0b0000_0000)
  }

  func testBitwiseOr() {
    let lhs = CUInt32x2Make(0b0000_1111, 0b1111_0000)
    let rhs = CUInt32x2Make(0b1111_1111, 0b0000_0000)
    let storage = CUInt32x2BitwiseOr(lhs, rhs)
    XCTAssertEqual(CUInt32x2GetElement(storage, 0), 0b0000_1111 | 0b1111_1111)
    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 0b1111_0000 | 0b0000_0000)
  }

  func testBitwiseExclusiveOr() {
    let lhs = CUInt32x2Make(0b0000_1111, 0b1111_0000)
    let rhs = CUInt32x2Make(0b1111_1111, 0b0000_0000)
    let storage = CUInt32x2BitwiseExclusiveOr(lhs, rhs)
    XCTAssertEqual(CUInt32x2GetElement(storage, 0), 0b0000_1111 ^ 0b1111_1111)
    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 0b1111_0000 ^ 0b0000_0000)
  }

  func testShiftLeft() {
    let lhs = CUInt32x2Make(0b1111_1111, 0b0000_1111)
    let storage = CUInt32x2ShiftLeft(lhs, 2)
    XCTAssertEqual(CUInt32x2GetElement(storage, 0), 0b1111_1111 << 2)
    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 0b0000_1111 << 2)
  }

  func testShiftRight() {
    let lhs = CUInt32x2Make(0b1111_1111, 0b0000_1111)
    let storage = CUInt32x2ShiftRight(lhs, 2)
    XCTAssertEqual(CUInt32x2GetElement(storage, 0), 0b1111_1111 >> 2)
    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 0b0000_1111 >> 2)
  }

//  // MARK: Conversion
//
//  func testConvertFromFloat32x2() {
//    let fromStorage = CFloat32x2Make(2.49, 0.51)
//    let storage = CUInt32x2FromCFloat32x2(fromStorage)
//
//    XCTAssertEqual(CUInt32x2GetElement(storage, 0), 2)
//    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 1)
//  }
//
//  func testConvertFromInt32x2() {
//    let fromStorage = CXInt32x2Make(2, 5)
//    let storage = CUInt32x2FromCXInt32x2(fromStorage)
//
//    XCTAssertEqual(CUInt32x2GetElement(storage, 0), 2)
//    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 5)
//  }
//
//  func testConvertFromFloat64x2() {
//    let fromStorage = CXFloat64x2Make(2.0000000, 1.9999999)
//    let storage = CUInt32x2FromCXFloat64x2(fromStorage)
//
//    XCTAssertEqual(CUInt32x2GetElement(storage, 0), 2)
//    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 2)
//  }
//
//  func testConvertFromInt64x2() {
//    let fromStorage = CXInt64x2Make(-34, 12)
//    let storage = CUInt32x2FromCXInt64x2(fromStorage)
//
//    XCTAssertEqual(CUInt32x2GetElement(storage, 0), UInt32.max - 34 + 1)
//    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 12)
//  }
//
//  func testConvertFromUInt64x2() {
//    let fromStorage = CXUInt64x2Make(34, 12)
//    let storage = CUInt32x2FromCXUInt64x2(fromStorage)
//
//    XCTAssertEqual(CUInt32x2GetElement(storage, 0), 34)
//    XCTAssertEqual(CUInt32x2GetElement(storage, 1), 12)
//  }
}
