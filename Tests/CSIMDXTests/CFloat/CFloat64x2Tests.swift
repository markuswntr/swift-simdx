import XCTest
import CSIMDX

final class CFloat64x2Tests: XCTestCase {

  // MARK: Make

  func testMake() {
    let collection = CFloat64x2Make(1, 2)

    XCTAssertEqual(CFloat64x2GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat64x2GetElement(collection, 1), 2)
  }

  func testMakeLoad() {
    var array: [Float64] = [1, 2]
    let collection = CFloat64x2MakeLoad(&array)

    XCTAssertEqual(CFloat64x2GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat64x2GetElement(collection, 1), 2)
  }

  func testMakeRepeatingElement() {
    let collection = CFloat64x2MakeRepeatingElement(3)

    XCTAssertEqual(CFloat64x2GetElement(collection, 0), 3)
    XCTAssertEqual(CFloat64x2GetElement(collection, 1), 3)
  }

  func testMakeZero() {
    let collection = CFloat64x2MakeZero()

    XCTAssertEqual(CFloat64x2GetElement(collection, 0), 0)
    XCTAssertEqual(CFloat64x2GetElement(collection, 1), 0)
  }

  // MARK: Access

  func testGetElement() {
    let collection = CFloat64x2Make(1, 2)

    XCTAssertEqual(CFloat64x2GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat64x2GetElement(collection, 1), 2)
  }

  func testSetElement() {
    var collection = CFloat64x2Make(1, 2)

    XCTAssertEqual(CFloat64x2GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat64x2GetElement(collection, 1), 2)

    CFloat64x2SetElement(&collection, 0, 5)
    CFloat64x2SetElement(&collection, 1, 6)

    XCTAssertEqual(CFloat64x2GetElement(collection, 0), 5)
    XCTAssertEqual(CFloat64x2GetElement(collection, 1), 6)
  }

  // MARK: Comparison

  func testMinimum() {
    let lhs = CFloat64x2Make(34, 12)
    let rhs = CFloat64x2Make(-34, 24)
    let storage = CFloat64x2Minimum(lhs, rhs)

    XCTAssertEqual(CFloat64x2GetElement(storage, 0), -34)
    XCTAssertEqual(CFloat64x2GetElement(storage, 1), 12)
  }

  func testMaximum() {
    let lhs = CFloat64x2Make(34, 12)
    let rhs = CFloat64x2Make(-34, 24)
    let storage = CFloat64x2Maximum(lhs, rhs)

    XCTAssertEqual(CFloat64x2GetElement(storage, 0), 34)
    XCTAssertEqual(CFloat64x2GetElement(storage, 1), 24)
  }

  // MARK: Arithmetic

  func testMagnitude() {
    let normal = CFloat64x2Make(-1, 3)
    let absolute = CFloat64x2Magnitude(normal)

    XCTAssertEqual(CFloat64x2GetElement(absolute, 0), 1)
    XCTAssertEqual(CFloat64x2GetElement(absolute, 1), 3)
  }

  func testNegate() {
    let normal = CFloat64x2Make(-1, 3)
    let negate = CFloat64x2Negate(normal)

    XCTAssertEqual(CFloat64x2GetElement(negate, 0), 1)
    XCTAssertEqual(CFloat64x2GetElement(negate, 1), -3)
  }

  func testAdd() {
    let lhs = CFloat64x2Make(1, 2)
    let rhs = CFloat64x2Make(4, 3)
    let sum = CFloat64x2Add(lhs, rhs)

    XCTAssertEqual(CFloat64x2GetElement(sum, 0), 5)
    XCTAssertEqual(CFloat64x2GetElement(sum, 1), 5)
  }

  func testSubtract() {
    let lhs = CFloat64x2Make(1, 2)
    let rhs = CFloat64x2Make(4, 3)
    let sum = CFloat64x2Subtract(lhs, rhs)

    XCTAssertEqual(CFloat64x2GetElement(sum, 0), -3)
    XCTAssertEqual(CFloat64x2GetElement(sum, 1), -1)

  }

  func testMultiply() {
    let lhs = CFloat64x2Make(1, -2)
    let rhs = CFloat64x2Make(-4, -3)
    let product = CFloat64x2Multiply(lhs, rhs)

    XCTAssertEqual(CFloat64x2GetElement(product, 0), -4)
    XCTAssertEqual(CFloat64x2GetElement(product, 1), 6)
  }

  func testDivide() {
    let lhs = CFloat64x2Make(1, -6)
    let rhs = CFloat64x2Make(-4, -3)
    let product = CFloat64x2Divide(lhs, rhs)

    XCTAssertEqual(CFloat64x2GetElement(product, 0), -0.25)
    XCTAssertEqual(CFloat64x2GetElement(product, 1), 2)
  }

  func testSquareRoot() {
    let storage =  CFloat64x2SquareRoot(CFloat64x2Make(25, 144))

    XCTAssertEqual(CFloat64x2GetElement(storage, 0), 5)
    XCTAssertEqual(CFloat64x2GetElement(storage, 1), 12)
  }

  // MARK: Conversion

  func testConvertFromFloat32x2() {
    let fromStorage = CFloat32x2Make(2.11199999999999, 1.54321987654321)
    let storage = CFloat64x2FromCFloat32x2(fromStorage)

    let firstRange = 2.11199999999999 - Float64(Float32.ulpOfOne) ... 2.11199999999999 + Float64(Float32.ulpOfOne)
    let secondRange = 1.54321987654321 - Float64(Float32.ulpOfOne) ... 1.54321987654321 + Float64(Float32.ulpOfOne)
    XCTAssertTrue(firstRange.contains(CFloat64x2GetElement(storage, 0)))
    XCTAssertTrue(secondRange.contains(CFloat64x2GetElement(storage, 1)))
  }

//  func testConvertFromInt32x2() {
//    let fromStorage = CXInt32x2Make(-2, 1)
//    let storage = CFloat64x2FromCXInt32x2(fromStorage)
//
//    XCTAssertEqual(CFloat64x2GetElement(storage, 0), -2.00000000000000)
//    XCTAssertEqual(CFloat64x2GetElement(storage, 1), 1.00000000000000)
//  }
//
//  func testConvertFromUInt32x2() {
//    let fromStorage = CXUInt32x2Make(2, 5)
//    let storage = CFloat64x2FromCXUInt32x2(fromStorage)
//
//    XCTAssertEqual(CFloat64x2GetElement(storage, 0), 2)
//    XCTAssertEqual(CFloat64x2GetElement(storage, 1), 5)
//  }
//
//  func testConvertFromInt64x2() {
//    let fromStorage = CXInt64x2Make(-34, 12)
//    let storage = CFloat64x2FromCXInt64x2(fromStorage)
//
//    XCTAssertEqual(CFloat64x2GetElement(storage, 0), -34)
//    XCTAssertEqual(CFloat64x2GetElement(storage, 1), 12)
//  }
//
//  func testConvertFromUInt64x2() {
//    let fromStorage = CXUInt64x2Make(34, 12)
//    let storage = CFloat64x2FromCXUInt64x2(fromStorage)
//
//    XCTAssertEqual(CFloat64x2GetElement(storage, 0), 34)
//    XCTAssertEqual(CFloat64x2GetElement(storage, 1), 12)
//  }
}
