import XCTest
import CSIMDX

final class CInt32x3Tests: XCTestCase {

  // MARK: Make

  func testMake() {
    let collection = CInt32x3Make(1, 2, 3)

    XCTAssertEqual(CInt32x3GetElement(collection, 0), 1)
    XCTAssertEqual(CInt32x3GetElement(collection, 1), 2)
    XCTAssertEqual(CInt32x3GetElement(collection, 2), 3)
  }

  func testMakeLoad() {
    var array: [Int32] = [1, -2, 3]
    let collection = CInt32x3MakeLoad(&array)

    XCTAssertEqual(CInt32x3GetElement(collection, 0),  1)
    XCTAssertEqual(CInt32x3GetElement(collection, 1), -2)
    XCTAssertEqual(CInt32x3GetElement(collection, 2),  3)
  }

  func testMakeRepeatingElement() {
    let collection = CInt32x3MakeRepeatingElement(3)

    XCTAssertEqual(CInt32x3GetElement(collection, 0), 3)
    XCTAssertEqual(CInt32x3GetElement(collection, 1), 3)
    XCTAssertEqual(CInt32x3GetElement(collection, 2), 3)
  }

  func testMakeZero() {
    let collection = CInt32x3MakeZero()

    XCTAssertEqual(CInt32x3GetElement(collection, 0), 0)
    XCTAssertEqual(CInt32x3GetElement(collection, 1), 0)
    XCTAssertEqual(CInt32x3GetElement(collection, 2), 0)
  }

  // MARK: Access

  func testGetElement() {
    let collection = CInt32x3Make(1, 2, 3)

    XCTAssertEqual(CInt32x3GetElement(collection, 0), 1)
    XCTAssertEqual(CInt32x3GetElement(collection, 1), 2)
    XCTAssertEqual(CInt32x3GetElement(collection, 2), 3)
  }

  func testSetElement() {
    var collection = CInt32x3Make(1, 2, 3)

    XCTAssertEqual(CInt32x3GetElement(collection, 0), 1)
    XCTAssertEqual(CInt32x3GetElement(collection, 1), 2)
    XCTAssertEqual(CInt32x3GetElement(collection, 2), 3)

    CInt32x3SetElement(&collection, 0, 5)
    CInt32x3SetElement(&collection, 1, 6)
    CInt32x3SetElement(&collection, 2, 7)

    XCTAssertEqual(CInt32x3GetElement(collection, 0), 5)
    XCTAssertEqual(CInt32x3GetElement(collection, 1), 6)
    XCTAssertEqual(CInt32x3GetElement(collection, 2), 7)
  }

  // MARK: Comparison

  func testMinimum() {
    let lhs = CInt32x3Make(34, 12, .max)
    let rhs = CInt32x3Make(-34, 24, .min)
    let storage = CInt32x3Minimum(lhs, rhs)

    XCTAssertEqual(CInt32x3GetElement(storage, 0), -34)
    XCTAssertEqual(CInt32x3GetElement(storage, 1), 12)
    XCTAssertEqual(CInt32x3GetElement(storage, 2), .min)
  }

  func testMaximum() {
    let lhs = CInt32x3Make(34, 12, .max)
    let rhs = CInt32x3Make(-34, 24, .min)
    let storage = CInt32x3Maximum(lhs, rhs)

    XCTAssertEqual(CInt32x3GetElement(storage, 0), 34)
    XCTAssertEqual(CInt32x3GetElement(storage, 1), 24)
    XCTAssertEqual(CInt32x3GetElement(storage, 2), .max)
  }

  // MARK: Arithmetic

  func testMagnitude() {
    let normal = CInt32x3Make(-1, 0, 3)
    let absolute = CInt32x3Magnitude(normal)

    XCTAssertEqual(CUInt32x3GetElement(absolute, 0), 1)
    XCTAssertEqual(CUInt32x3GetElement(absolute, 1), 0)
    XCTAssertEqual(CUInt32x3GetElement(absolute, 2), 3)
  }

  func testNegate() {
    let normal = CInt32x3Make(-1, 0, 3)
    let negate = CInt32x3Negate(normal)

    XCTAssertEqual(CInt32x3GetElement(negate, 0), 1)
    XCTAssertEqual(CInt32x3GetElement(negate, 1), 0)
    XCTAssertEqual(CInt32x3GetElement(negate, 2), -3)
  }

  func testAdd() {
    let lhs = CInt32x3Make(1, 2, 3)
    let rhs = CInt32x3Make(4, 3, 2)
    let sum = CInt32x3Add(lhs, rhs)

    XCTAssertEqual(CInt32x3GetElement(sum, 0), 5)
    XCTAssertEqual(CInt32x3GetElement(sum, 1), 5)
    XCTAssertEqual(CInt32x3GetElement(sum, 2), 5)
  }

  func testSubtract() {
    let lhs = CInt32x3Make(1, 2, 3)
    let rhs = CInt32x3Make(4, 3, 2)
    let sum = CInt32x3Subtract(lhs, rhs)

    XCTAssertEqual(CInt32x3GetElement(sum, 0), -3)
    XCTAssertEqual(CInt32x3GetElement(sum, 1), -1)
    XCTAssertEqual(CInt32x3GetElement(sum, 2), 1)
  }

  func testMultiply() {
    let lhs = CInt32x3Make(1, -2, -3)
    let rhs = CInt32x3Make(4, -3, 2)
    let product = CInt32x3Multiply(lhs, rhs)

    XCTAssertEqual(CInt32x3GetElement(product, 0), 4)
    XCTAssertEqual(CInt32x3GetElement(product, 1), 6)
    XCTAssertEqual(CInt32x3GetElement(product, 2), -6)
  }

  // MARK: Binary

  func testBitwiseNot() {
    let operand = CInt32x3Make(0b0000_1111, 0b1111_0000, 0b0011_1100)
    let storage = CInt32x3BitwiseNot(operand)
    XCTAssertEqual(CInt32x3GetElement(storage, 0), ~(0b0000_1111))
    XCTAssertEqual(CInt32x3GetElement(storage, 1), ~(0b1111_0000))
    XCTAssertEqual(CInt32x3GetElement(storage, 2), ~(0b0011_1100))
  }

  func testBitwiseAnd() {
    let lhs = CInt32x3Make(0b0000_1111, 0b1111_0000, 0b0011_1100)
    let rhs = CInt32x3Make(0b1111_1111, 0b0000_0000, 0b1100_0011)
    let storage = CInt32x3BitwiseAnd(lhs, rhs)
    XCTAssertEqual(CInt32x3GetElement(storage, 0), 0b0000_1111 & 0b1111_1111)
    XCTAssertEqual(CInt32x3GetElement(storage, 1), 0b1111_0000 & 0b0000_0000)
    XCTAssertEqual(CInt32x3GetElement(storage, 2), 0b0011_1100 & 0b1100_0011)
  }

  func testBitwiseAndNot() {
    let lhs = CInt32x3Make(0b0000_1111, 0b1111_0000, 0b0011_1100)
    let rhs = CInt32x3Make(0b1111_1111, 0b0000_0000, 0b1100_0011)
    let storage = CInt32x3BitwiseAndNot(lhs, rhs)
    XCTAssertEqual(CInt32x3GetElement(storage, 0), (~0b0000_1111) & 0b1111_1111)
    XCTAssertEqual(CInt32x3GetElement(storage, 1), (~0b1111_0000) & 0b0000_0000)
    XCTAssertEqual(CInt32x3GetElement(storage, 2), (~0b0011_1100) & 0b1100_0011)
  }

  func testBitwiseOr() {
    let lhs = CInt32x3Make(0b0000_1111, 0b1111_0000, 0b0011_1100)
    let rhs = CInt32x3Make(0b1111_1111, 0b0000_0000, 0b1100_0011)
    let storage = CInt32x3BitwiseOr(lhs, rhs)
    XCTAssertEqual(CInt32x3GetElement(storage, 0), 0b0000_1111 | 0b1111_1111)
    XCTAssertEqual(CInt32x3GetElement(storage, 1), 0b1111_0000 | 0b0000_0000)
    XCTAssertEqual(CInt32x3GetElement(storage, 2), 0b0011_1100 | 0b1100_0011)
  }

  func testBitwiseExclusiveOr() {
    let lhs = CInt32x3Make(0b0000_1111, 0b1111_0000, 0b0011_1100)
    let rhs = CInt32x3Make(0b1111_1111, 0b0000_0000, 0b1100_0011)
    let storage = CInt32x3BitwiseExclusiveOr(lhs, rhs)
    XCTAssertEqual(CInt32x3GetElement(storage, 0), 0b0000_1111 ^ 0b1111_1111)
    XCTAssertEqual(CInt32x3GetElement(storage, 1), 0b1111_0000 ^ 0b0000_0000)
    XCTAssertEqual(CInt32x3GetElement(storage, 2), 0b0011_1100 ^ 0b1100_0011)
  }

  func testShiftLeft() {
    let lhs = CInt32x3Make(0b1111_1111, 0b0000_1111, 0b0011_1100)
    let storage = CInt32x3ShiftLeft(lhs, 2)
    XCTAssertEqual(CInt32x3GetElement(storage, 0), 0b1111_1111 << 2)
    XCTAssertEqual(CInt32x3GetElement(storage, 1), 0b0000_1111 << 2)
    XCTAssertEqual(CInt32x3GetElement(storage, 2), 0b0011_1100 << 2)
  }

  func testShiftRight() {
    let lhs = CInt32x3Make(0b1111_1111, 0b0000_1111, 0b0011_1100)
    let storage = CInt32x3ShiftRight(lhs, 2)
    XCTAssertEqual(CInt32x3GetElement(storage, 0), 0b1111_1111 >> 2)
    XCTAssertEqual(CInt32x3GetElement(storage, 1), 0b0000_1111 >> 2)
    XCTAssertEqual(CInt32x3GetElement(storage, 2), 0b0011_1100 >> 2)
  }

//  // MARK: Conversion
//
//  func testConvertFromFloat32x3() {
//    let fromStorage = CFloat32x3Make(2.49, 0.51, 1.5)
//    let storage = CInt32x3FromCFloat32x3(fromStorage)
//
//    XCTAssertEqual(CInt32x3GetElement(storage, 0), 2)
//    XCTAssertEqual(CInt32x3GetElement(storage, 1), 1)
//    XCTAssertEqual(CInt32x3GetElement(storage, 2), 2)
//  }
//
//  func testConvertFromUInt32x3() {
//    let fromStorage = CXUInt32x3Make(2, 5, .max)
//    let storage = CInt32x3FromCXUInt32x3(fromStorage)
//
//    XCTAssertEqual(CInt32x3GetElement(storage, 0), 2)
//    XCTAssertEqual(CInt32x3GetElement(storage, 1), 5)
//    XCTAssertEqual(CInt32x3GetElement(storage, 2), -1)
//  }
}
