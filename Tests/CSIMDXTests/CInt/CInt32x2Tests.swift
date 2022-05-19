import XCTest
import CSIMDX

final class CInt32x2Tests: XCTestCase {

  // MARK: Make

  func testMake() {
    let collection = CInt32x2Make(1, 2)

    XCTAssertEqual(CInt32x2GetElement(collection, 0), 1)
    XCTAssertEqual(CInt32x2GetElement(collection, 1), 2)
  }

  func testMakeLoad() {
    var array: [Int32] = [1, 2]
    let collection = CInt32x2MakeLoad(&array)

    XCTAssertEqual(CInt32x2GetElement(collection, 0), 1)
    XCTAssertEqual(CInt32x2GetElement(collection, 1), 2)
  }

  func testMakeRepeatingElement() {
    let collection = CInt32x2MakeRepeatingElement(3)

    XCTAssertEqual(CInt32x2GetElement(collection, 0), 3)
    XCTAssertEqual(CInt32x2GetElement(collection, 1), 3)
  }

  func testMakeZero() {
    let collection = CInt32x2MakeZero()

    XCTAssertEqual(CInt32x2GetElement(collection, 0), 0)
    XCTAssertEqual(CInt32x2GetElement(collection, 1), 0)
  }

  // MARK: Access

  func testGetElement() {
    let collection = CInt32x2Make(1, 2)

    XCTAssertEqual(CInt32x2GetElement(collection, 0), 1)
    XCTAssertEqual(CInt32x2GetElement(collection, 1), 2)
  }

  func testSetElement() {
    var collection = CInt32x2Make(1, 2)

    XCTAssertEqual(CInt32x2GetElement(collection, 0), 1)
    XCTAssertEqual(CInt32x2GetElement(collection, 1), 2)

    CInt32x2SetElement(&collection, 0, 5)
    CInt32x2SetElement(&collection, 1, 6)

    XCTAssertEqual(CInt32x2GetElement(collection, 0), 5)
    XCTAssertEqual(CInt32x2GetElement(collection, 1), 6)
  }

  // MARK: Comparison

  func testMinimum() {
    let lhs = CInt32x2Make(34, 12)
    let rhs = CInt32x2Make(-34, 24)
    let storage = CInt32x2Minimum(lhs, rhs)

    XCTAssertEqual(CInt32x2GetElement(storage, 0), -34)
    XCTAssertEqual(CInt32x2GetElement(storage, 1), 12)
  }

  func testMaximum() {
    let lhs = CInt32x2Make(34, 12)
    let rhs = CInt32x2Make(-34, 24)
    let storage = CInt32x2Maximum(lhs, rhs)

    XCTAssertEqual(CInt32x2GetElement(storage, 0), 34)
    XCTAssertEqual(CInt32x2GetElement(storage, 1), 24)
  }

  // MARK: Arithmetic

  func testNegate() {
    let normal = CInt32x2Make(-1, 3)
    let negate = CInt32x2Negate(normal)

    XCTAssertEqual(CInt32x2GetElement(negate, 0), 1)
    XCTAssertEqual(CInt32x2GetElement(negate, 1), -3)
  }

  func testMagnitude() {
    let normal = CInt32x2Make(-1, 3)
    let absolute = CInt32x2Magnitude(normal)

    XCTAssertEqual(CUInt32x2GetElement(absolute, 0), 1)
    XCTAssertEqual(CUInt32x2GetElement(absolute, 1), 3)
  }

  func testAdd() {
    let lhs = CInt32x2Make(1, 2)
    let rhs = CInt32x2Make(4, 3)
    let sum = CInt32x2Add(lhs, rhs)

    XCTAssertEqual(CInt32x2GetElement(sum, 0), 5)
    XCTAssertEqual(CInt32x2GetElement(sum, 1), 5)
  }

  func testSubtract() {
    let lhs = CInt32x2Make(1, 2)
    let rhs = CInt32x2Make(4, 3)
    let sum = CInt32x2Subtract(lhs, rhs)

    XCTAssertEqual(CInt32x2GetElement(sum, 0), -3)
    XCTAssertEqual(CInt32x2GetElement(sum, 1), -1)

  }

  func testMultiply() {
    let lhs = CInt32x2Make(1, -2)
    let rhs = CInt32x2Make(-4, -3)
    let product = CInt32x2Multiply(lhs, rhs)

    XCTAssertEqual(CInt32x2GetElement(product, 0), -4)
    XCTAssertEqual(CInt32x2GetElement(product, 1), 6)
  }

  // MARK: Binary

  func testBitwiseNot() {
    let operand = CInt32x2Make(0b0000_1111, 0b1111_0000)
    let storage = CInt32x2BitwiseNot(operand)
    XCTAssertEqual(CInt32x2GetElement(storage, 0), ~(0b0000_1111))
    XCTAssertEqual(CInt32x2GetElement(storage, 1), ~(0b1111_0000))
  }

  func testBitwiseAnd() {
    let lhs = CInt32x2Make(0b0000_1111, 0b1111_0000)
    let rhs = CInt32x2Make(0b1111_1111, 0b0000_0000)
    let storage = CInt32x2BitwiseAnd(lhs, rhs)
    XCTAssertEqual(CInt32x2GetElement(storage, 0), 0b0000_1111 & 0b1111_1111)
    XCTAssertEqual(CInt32x2GetElement(storage, 1), 0b1111_0000 & 0b0000_0000)
  }

  func testBitwiseAndNot() {
    let lhs = CInt32x2Make(0b0000_1111, 0b1111_0000)
    let rhs = CInt32x2Make(0b1111_1111, 0b0000_0000)
    let storage = CInt32x2BitwiseAndNot(lhs, rhs)
    XCTAssertEqual(CInt32x2GetElement(storage, 0), (~0b0000_1111) & 0b1111_1111)
    XCTAssertEqual(CInt32x2GetElement(storage, 1), (~0b1111_0000) & 0b0000_0000)
  }

  func testBitwiseOr() {
    let lhs = CInt32x2Make(0b0000_1111, 0b1111_0000)
    let rhs = CInt32x2Make(0b1111_1111, 0b0000_0000)
    let storage = CInt32x2BitwiseOr(lhs, rhs)
    XCTAssertEqual(CInt32x2GetElement(storage, 0), 0b0000_1111 | 0b1111_1111)
    XCTAssertEqual(CInt32x2GetElement(storage, 1), 0b1111_0000 | 0b0000_0000)
  }

  func testBitwiseExclusiveOr() {
    let lhs = CInt32x2Make(0b0000_1111, 0b1111_0000)
    let rhs = CInt32x2Make(0b1111_1111, 0b0000_0000)
    let storage = CInt32x2BitwiseExclusiveOr(lhs, rhs)
    XCTAssertEqual(CInt32x2GetElement(storage, 0), 0b0000_1111 ^ 0b1111_1111)
    XCTAssertEqual(CInt32x2GetElement(storage, 1), 0b1111_0000 ^ 0b0000_0000)
  }

  func testShiftLeft() {
    let lhs = CInt32x2Make(0b1111_1111, 0b0000_1111)
    let storage = CInt32x2ShiftLeft(lhs, 2)
    XCTAssertEqual(CInt32x2GetElement(storage, 0), 0b1111_1111 << 2)
    XCTAssertEqual(CInt32x2GetElement(storage, 1), 0b0000_1111 << 2)
  }

  func testShiftLeftElementWise() {
    let lhs = CInt32x2Make(0b1111_1111, 0b0000_1111)
    let storage = CInt32x2ShiftLeftElementWise(lhs, CInt32x2Make(2, 4))
    XCTAssertEqual(CInt32x2GetElement(storage, 0), 0b1111_1111 << 2)
    XCTAssertEqual(CInt32x2GetElement(storage, 1), 0b0000_1111 << 4)
  }

  func testShiftRight() {
    let lhs = CInt32x2Make(0b1111_1111, 0b0000_1111)
    let storage = CInt32x2ShiftRight(lhs, 2)
    XCTAssertEqual(CInt32x2GetElement(storage, 0), 0b1111_1111 >> 2)
    XCTAssertEqual(CInt32x2GetElement(storage, 1), 0b0000_1111 >> 2)
  }

  func testShiftRightElementWise() {
    let lhs = CInt32x2Make(0b1111_1111, 0b0000_1111)
    let storage = CInt32x2ShiftRightElementWise(lhs, CInt32x2Make(2, 4))
    XCTAssertEqual(CInt32x2GetElement(storage, 0), 0b1111_1111 >> 2)
    XCTAssertEqual(CInt32x2GetElement(storage, 1), 0b0000_1111 >> 4)
  }
  //    // MARK: Conversion
  //
  //    func testConvertFromFloat32x2() {
  //        let fromStorage = CFloat32x2Make(2.49, 0.51)
  //        let storage = CInt32x2FromCFloat32x2(fromStorage)
  //
  //        XCTAssertEqual(CInt32x2GetElement(storage, 0), 2)
  //        XCTAssertEqual(CInt32x2GetElement(storage, 1), 1)
  //    }
  //
  //    func testConvertFromUInt32x2() {
  //        let fromStorage = CXUInt32x2Make(2, 5)
  //        let storage = CInt32x2FromCXUInt32x2(fromStorage)
  //
  //        XCTAssertEqual(CInt32x2GetElement(storage, 0), 2)
  //        XCTAssertEqual(CInt32x2GetElement(storage, 1), 5)
  //    }
  //
  //    func testConvertFromFloat64x2() {
  //        let fromStorage = CXFloat64x2Make(2.0000000, 1.9999999)
  //        let storage = CInt32x2FromCXFloat64x2(fromStorage)
  //
  //        XCTAssertEqual(CInt32x2GetElement(storage, 0), 2)
  //        XCTAssertEqual(CInt32x2GetElement(storage, 1), 2)
  //    }
  //
  //    func testConvertFromInt64x2() {
  //        let fromStorage = CXInt64x2Make(-34, 12)
  //        let storage = CInt32x2FromCXInt64x2(fromStorage)
  //
  //        XCTAssertEqual(CInt32x2GetElement(storage, 0), -34)
  //        XCTAssertEqual(CInt32x2GetElement(storage, 1), 12)
  //    }
  //
  //    func testConvertFromUInt64x2() {
  //        let fromStorage = CXUInt64x2Make(34, 12)
  //        let storage = CInt32x2FromCXUInt64x2(fromStorage)
  //
  //        XCTAssertEqual(CInt32x2GetElement(storage, 0), 34)
  //        XCTAssertEqual(CInt32x2GetElement(storage, 1), 12)
  //    }
}
