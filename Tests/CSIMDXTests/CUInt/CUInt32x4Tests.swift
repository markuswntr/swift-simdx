import XCTest
import CSIMDX

final class CUInt32x4Tests: XCTestCase {

  // MARK: Make

  func testMake() {
    let collection = CUInt32x4Make(1, 2, 3, 4)

    XCTAssertEqual(CUInt32x4GetElement(collection, 0), 1)
    XCTAssertEqual(CUInt32x4GetElement(collection, 1), 2)
    XCTAssertEqual(CUInt32x4GetElement(collection, 2), 3)
    XCTAssertEqual(CUInt32x4GetElement(collection, 3), 4)
  }

  func testMakeLoad() {
    var array: [UInt32] = [1, 2, 3, 4]
    let collection = CUInt32x4MakeLoad(&array)

    XCTAssertEqual(CUInt32x4GetElement(collection, 0), 1)
    XCTAssertEqual(CUInt32x4GetElement(collection, 1), 2)
    XCTAssertEqual(CUInt32x4GetElement(collection, 2), 3)
    XCTAssertEqual(CUInt32x4GetElement(collection, 3), 4)
  }

  func testMakeRepeatingElement() {
    let collection = CUInt32x4MakeRepeatingElement(3)

    XCTAssertEqual(CUInt32x4GetElement(collection, 0), 3)
    XCTAssertEqual(CUInt32x4GetElement(collection, 1), 3)
    XCTAssertEqual(CUInt32x4GetElement(collection, 2), 3)
    XCTAssertEqual(CUInt32x4GetElement(collection, 3), 3)
  }

  func testMakeZero() {
    let collection = CUInt32x4MakeZero()

    XCTAssertEqual(CUInt32x4GetElement(collection, 0), 0)
    XCTAssertEqual(CUInt32x4GetElement(collection, 1), 0)
    XCTAssertEqual(CUInt32x4GetElement(collection, 2), 0)
    XCTAssertEqual(CUInt32x4GetElement(collection, 3), 0)
  }

  // MARK: Access

  func testGetElement() {
    let collection = CUInt32x4Make(1, 2, 3, 4)

    XCTAssertEqual(CUInt32x4GetElement(collection, 0), 1)
    XCTAssertEqual(CUInt32x4GetElement(collection, 1), 2)
    XCTAssertEqual(CUInt32x4GetElement(collection, 2), 3)
    XCTAssertEqual(CUInt32x4GetElement(collection, 3), 4)
  }

  func testSetElement() {
    var collection = CUInt32x4Make(1, 2, 3, 4)

    XCTAssertEqual(CUInt32x4GetElement(collection, 0), 1)
    XCTAssertEqual(CUInt32x4GetElement(collection, 1), 2)
    XCTAssertEqual(CUInt32x4GetElement(collection, 2), 3)
    XCTAssertEqual(CUInt32x4GetElement(collection, 3), 4)

    CUInt32x4SetElement(&collection, 0, 5)
    CUInt32x4SetElement(&collection, 1, 6)
    CUInt32x4SetElement(&collection, 2, 7)
    CUInt32x4SetElement(&collection, 3, 8)

    XCTAssertEqual(CUInt32x4GetElement(collection, 0), 5)
    XCTAssertEqual(CUInt32x4GetElement(collection, 1), 6)
    XCTAssertEqual(CUInt32x4GetElement(collection, 2), 7)
    XCTAssertEqual(CUInt32x4GetElement(collection, 3), 8)
  }

  // MARK: Comparison

  func testMinimum() {
    let lhs = CUInt32x4Make(34, 12, .max, .min)
    let rhs = CUInt32x4Make(34, 24, .min, .max)
    let storage = CUInt32x4Minimum(lhs, rhs)

    XCTAssertEqual(CUInt32x4GetElement(storage, 0), 34)
    XCTAssertEqual(CUInt32x4GetElement(storage, 1), 12)
    XCTAssertEqual(CUInt32x4GetElement(storage, 2), .min)
    XCTAssertEqual(CUInt32x4GetElement(storage, 3), .min)
  }

  func testMaximum() {
    let lhs = CUInt32x4Make(34, 12, .max, .min)
    let rhs = CUInt32x4Make(34, 24, .min, .max)
    let storage = CUInt32x4Maximum(lhs, rhs)

    XCTAssertEqual(CUInt32x4GetElement(storage, 0), 34)
    XCTAssertEqual(CUInt32x4GetElement(storage, 1), 24)
    XCTAssertEqual(CUInt32x4GetElement(storage, 2), .max)
    XCTAssertEqual(CUInt32x4GetElement(storage, 3), .max)
  }

  // MARK: Arithmetic

  func testAdd() {
    let lhs = CUInt32x4Make(1, 2, 3, 4)
    let rhs = CUInt32x4Make(4, 3, 2, 1)
    let sum = CUInt32x4Add(lhs, rhs)

    XCTAssertEqual(CUInt32x4GetElement(sum, 0), 5)
    XCTAssertEqual(CUInt32x4GetElement(sum, 1), 5)
    XCTAssertEqual(CUInt32x4GetElement(sum, 2), 5)
    XCTAssertEqual(CUInt32x4GetElement(sum, 3), 5)
  }

  func testSubtract() {
    let lhs = CUInt32x4Make(4, 3, 5, 4)
    let rhs = CUInt32x4Make(1, 2, 5, 1)
    let sum = CUInt32x4Subtract(lhs, rhs)

    XCTAssertEqual(CUInt32x4GetElement(sum, 0), 3)
    XCTAssertEqual(CUInt32x4GetElement(sum, 1), 1)
    XCTAssertEqual(CUInt32x4GetElement(sum, 2), 0)
    XCTAssertEqual(CUInt32x4GetElement(sum, 3), 3)

  }

  func testMultiply() {
    let lhs = CUInt32x4Make(1, 2, 3, 4)
    let rhs = CUInt32x4Make(4, 3, 2, 1)
    let product = CUInt32x4Multiply(lhs, rhs)

    XCTAssertEqual(CUInt32x4GetElement(product, 0), 4)
    XCTAssertEqual(CUInt32x4GetElement(product, 1), 6)
    XCTAssertEqual(CUInt32x4GetElement(product, 2), 6)
    XCTAssertEqual(CUInt32x4GetElement(product, 3), 4)
  }

  // MARK: Binary

  func testBitwiseNot() {
    let operand = CUInt32x4Make(0b0000_1111, 0b1111_0000, 0b0011_1100, 0b1100_0011)
    let storage = CUInt32x4BitwiseNot(operand)
    XCTAssertEqual(CUInt32x4GetElement(storage, 0), ~(0b0000_1111))
    XCTAssertEqual(CUInt32x4GetElement(storage, 1), ~(0b1111_0000))
    XCTAssertEqual(CUInt32x4GetElement(storage, 2), ~(0b0011_1100))
    XCTAssertEqual(CUInt32x4GetElement(storage, 3), ~(0b1100_0011))
  }

  func testBitwiseAnd() {
    let lhs = CUInt32x4Make(0b0000_1111, 0b1111_0000, 0b0011_1100, 0b0101_0101)
    let rhs = CUInt32x4Make(0b1111_1111, 0b0000_0000, 0b1100_0011, 0b1010_1010)
    let storage = CUInt32x4BitwiseAnd(lhs, rhs)
    XCTAssertEqual(CUInt32x4GetElement(storage, 0), 0b0000_1111 & 0b1111_1111)
    XCTAssertEqual(CUInt32x4GetElement(storage, 1), 0b1111_0000 & 0b0000_0000)
    XCTAssertEqual(CUInt32x4GetElement(storage, 2), 0b0011_1100 & 0b1100_0011)
    XCTAssertEqual(CUInt32x4GetElement(storage, 3), 0b0101_0101 & 0b1010_1010)
  }

  func testBitwiseAndNot() {
    let lhs = CUInt32x4Make(0b0000_1111, 0b1111_0000, 0b0011_1100, 0b0101_0101)
    let rhs = CUInt32x4Make(0b1111_1111, 0b0000_0000, 0b1100_0011, 0b1010_1010)
    let storage = CUInt32x4BitwiseAndNot(lhs, rhs)
    XCTAssertEqual(CUInt32x4GetElement(storage, 0), (~0b0000_1111) & 0b1111_1111)
    XCTAssertEqual(CUInt32x4GetElement(storage, 1), (~0b1111_0000) & 0b0000_0000)
    XCTAssertEqual(CUInt32x4GetElement(storage, 2), (~0b0011_1100) & 0b1100_0011)
    XCTAssertEqual(CUInt32x4GetElement(storage, 3), (~0b0101_0101) & 0b1010_1010)
  }

  func testBitwiseOr() {
    let lhs = CUInt32x4Make(0b0000_1111, 0b1111_0000, 0b0011_1100, 0b0101_0101)
    let rhs = CUInt32x4Make(0b1111_1111, 0b0000_0000, 0b1100_0011, 0b1010_1010)
    let storage = CUInt32x4BitwiseOr(lhs, rhs)
    XCTAssertEqual(CUInt32x4GetElement(storage, 0), 0b0000_1111 | 0b1111_1111)
    XCTAssertEqual(CUInt32x4GetElement(storage, 1), 0b1111_0000 | 0b0000_0000)
    XCTAssertEqual(CUInt32x4GetElement(storage, 2), 0b0011_1100 | 0b1100_0011)
    XCTAssertEqual(CUInt32x4GetElement(storage, 3), 0b0101_0101 | 0b1010_1010)
  }

  func testBitwiseExclusiveOr() {
    let lhs = CUInt32x4Make(0b0000_1111, 0b1111_0000, 0b0011_1100, 0b0101_0101)
    let rhs = CUInt32x4Make(0b1111_1111, 0b0000_0000, 0b1100_0011, 0b1010_1010)
    let storage = CUInt32x4BitwiseExclusiveOr(lhs, rhs)
    XCTAssertEqual(CUInt32x4GetElement(storage, 0), 0b0000_1111 ^ 0b1111_1111)
    XCTAssertEqual(CUInt32x4GetElement(storage, 1), 0b1111_0000 ^ 0b0000_0000)
    XCTAssertEqual(CUInt32x4GetElement(storage, 2), 0b0011_1100 ^ 0b1100_0011)
    XCTAssertEqual(CUInt32x4GetElement(storage, 3), 0b0101_0101 ^ 0b1010_1010)
  }

  func testShiftLeft() {
    let lhs = CUInt32x4Make(0b1111_1111, 0b0000_1111, 0b0011_1100, 0b1010_1010)
    let storage = CUInt32x4ShiftLeft(lhs, 2)
    XCTAssertEqual(CUInt32x4GetElement(storage, 0), 0b1111_1111 << 2)
    XCTAssertEqual(CUInt32x4GetElement(storage, 1), 0b0000_1111 << 2)
    XCTAssertEqual(CUInt32x4GetElement(storage, 2), 0b0011_1100 << 2)
    XCTAssertEqual(CUInt32x4GetElement(storage, 3), 0b1010_1010 << 2)
  }

  func testShiftRight() {
    let lhs = CUInt32x4Make(0b1111_1111, 0b0000_1111, 0b0011_1100, 0b1010_1010)
    let storage = CUInt32x4ShiftRight(lhs, 2)
    XCTAssertEqual(CUInt32x4GetElement(storage, 0), 0b1111_1111 >> 2)
    XCTAssertEqual(CUInt32x4GetElement(storage, 1), 0b0000_1111 >> 2)
    XCTAssertEqual(CUInt32x4GetElement(storage, 2), 0b0011_1100 >> 2)
    XCTAssertEqual(CUInt32x4GetElement(storage, 3), 0b1010_1010 >> 2)
  }

//  // MARK: Conversion
//
//  func testConvertFromFloat32x4() {
//    let fromStorage = CXFloat32x4Make(2.49, 0.51, 1.5, .pi)
//    let storage = CUInt32x4FromCXFloat32x4(fromStorage)
//
//    XCTAssertEqual(CUInt32x4GetElement(storage, 0), 2)
//    XCTAssertEqual(CUInt32x4GetElement(storage, 1), 1)
//    XCTAssertEqual(CUInt32x4GetElement(storage, 2), 2)
//    XCTAssertEqual(CUInt32x4GetElement(storage, 3), 3) // ;)
//  }
//
//  func testConvertFromInt32x4() {
//    let fromStorage = CXInt32x4Make(2, 5, .max, .min)
//    let storage = CUInt32x4FromCXInt32x4(fromStorage)
//
//    XCTAssertEqual(CUInt32x4GetElement(storage, 0), 2)
//    XCTAssertEqual(CUInt32x4GetElement(storage, 1), 5)
//    XCTAssertEqual(CUInt32x4GetElement(storage, 2), UInt32(Int32.max))
//    XCTAssertEqual(CUInt32x4GetElement(storage, 3), UInt32(Int32.max) + 1) // Overflow
//  }
}
