import XCTest
import CSIMDX

final class CUInt32x3Tests: XCTestCase {
  // MARK: Access

  func testGetElement() {
    let collection = CUInt32x3Make(.min, .zero, .max)

    XCTAssertEqual(CUInt32x3GetElement(collection, 0), .min)
    XCTAssertEqual(CUInt32x3GetElement(collection, 1), .zero)
    XCTAssertEqual(CUInt32x3GetElement(collection, 2), .max)
  }

  func testSetElement() {
    var collection = CUInt32x3Make(.min, .zero, .max)

    XCTAssertEqual(CUInt32x3GetElement(collection, 0), .min)
    XCTAssertEqual(CUInt32x3GetElement(collection, 1), .zero)
    XCTAssertEqual(CUInt32x3GetElement(collection, 2), .max)

    CUInt32x3SetElement(&collection, 0, 5)
    CUInt32x3SetElement(&collection, 1, 6)
    CUInt32x3SetElement(&collection, 2, 7)

    XCTAssertEqual(CUInt32x3GetElement(collection, 0), 5)
    XCTAssertEqual(CUInt32x3GetElement(collection, 1), 6)
    XCTAssertEqual(CUInt32x3GetElement(collection, 2), 7)
  }

  // MARK: Make
  
  func testMake() {
    let collection = CUInt32x3Make(.min, .zero, .max)
    
    XCTAssertEqual(CUInt32x3GetElement(collection, 0), .min)
    XCTAssertEqual(CUInt32x3GetElement(collection, 1), .zero)
    XCTAssertEqual(CUInt32x3GetElement(collection, 2), .max)
  }
  
  func testMakeLoad() {
    var array: [UInt32] = [.min, .zero, .max]
    let collection = CUInt32x3MakeLoad(&array)
    
    XCTAssertEqual(CUInt32x3GetElement(collection, 0), .min)
    XCTAssertEqual(CUInt32x3GetElement(collection, 1), .zero)
    XCTAssertEqual(CUInt32x3GetElement(collection, 2), .max)
  }
  
  func testMakeRepeatingElement() {
    let collection = CUInt32x3MakeRepeatingElement(.max)
    
    XCTAssertEqual(CUInt32x3GetElement(collection, 0), .max)
    XCTAssertEqual(CUInt32x3GetElement(collection, 1), .max)
    XCTAssertEqual(CUInt32x3GetElement(collection, 2), .max)
  }
  
  func testMakeZero() {
    let collection = CUInt32x3MakeZero()
    
    XCTAssertEqual(CUInt32x3GetElement(collection, 0), 0)
    XCTAssertEqual(CUInt32x3GetElement(collection, 1), 0)
    XCTAssertEqual(CUInt32x3GetElement(collection, 2), 0)
  }
  
  // MARK: Comparison
  
  func testMinimum() {
    let lhs = CUInt32x3Make(34, 12, .max)
    let rhs = CUInt32x3Make(34, 24, .min)
    let storage = CUInt32x3Minimum(lhs, rhs)
    
    XCTAssertEqual(CUInt32x3GetElement(storage, 0), 34)
    XCTAssertEqual(CUInt32x3GetElement(storage, 1), 12)
    XCTAssertEqual(CUInt32x3GetElement(storage, 2), .min)
  }
  
  func testMaximum() {
    let lhs = CUInt32x3Make(34, 12, .max)
    let rhs = CUInt32x3Make(34, 24, .min)
    let storage = CUInt32x3Maximum(lhs, rhs)
    
    XCTAssertEqual(CUInt32x3GetElement(storage, 0), 34)
    XCTAssertEqual(CUInt32x3GetElement(storage, 1), 24)
    XCTAssertEqual(CUInt32x3GetElement(storage, 2), .max)
  }
  
  // MARK: Arithmetic
  
  func testAdd() {
    let lhs = CUInt32x3Make(1, 2, 3)
    let rhs = CUInt32x3Make(4, 3, 2)
    let sum = CUInt32x3Add(lhs, rhs)
    
    XCTAssertEqual(CUInt32x3GetElement(sum, 0), 5)
    XCTAssertEqual(CUInt32x3GetElement(sum, 1), 5)
    XCTAssertEqual(CUInt32x3GetElement(sum, 2), 5)
  }
  
  func testSubtract() {
    let lhs = CUInt32x3Make(4, 3, 5)
    let rhs = CUInt32x3Make(1, 1, 5)
    let sum = CUInt32x3Subtract(lhs, rhs)
    
    XCTAssertEqual(CUInt32x3GetElement(sum, 0), 3)
    XCTAssertEqual(CUInt32x3GetElement(sum, 1), 2)
    XCTAssertEqual(CUInt32x3GetElement(sum, 2), 0)
  }
  
  func testMultiply() {
    let lhs = CUInt32x3Make(1, 2, 3)
    let rhs = CUInt32x3Make(4, 3, 2)
    let product = CUInt32x3Multiply(lhs, rhs)
    
    XCTAssertEqual(CUInt32x3GetElement(product, 0), 4)
    XCTAssertEqual(CUInt32x3GetElement(product, 1), 6)
    XCTAssertEqual(CUInt32x3GetElement(product, 2), 6)
  }
  
  // MARK: Binary
  
  func testBitwiseNot() {
    let operand = CUInt32x3Make(0b0000_1111, 0b1111_0000, 0b0011_1100)
    let storage = CUInt32x3BitwiseNot(operand)
    XCTAssertEqual(CUInt32x3GetElement(storage, 0), ~(0b0000_1111))
    XCTAssertEqual(CUInt32x3GetElement(storage, 1), ~(0b1111_0000))
    XCTAssertEqual(CUInt32x3GetElement(storage, 2), ~(0b0011_1100))
  }
  
  func testBitwiseAnd() {
    let lhs = CUInt32x3Make(0b0000_1111, 0b1111_0000, 0b0011_1100)
    let rhs = CUInt32x3Make(0b1111_1111, 0b0000_0000, 0b1100_0011)
    let storage = CUInt32x3BitwiseAnd(lhs, rhs)
    XCTAssertEqual(CUInt32x3GetElement(storage, 0), 0b0000_1111 & 0b1111_1111)
    XCTAssertEqual(CUInt32x3GetElement(storage, 1), 0b1111_0000 & 0b0000_0000)
    XCTAssertEqual(CUInt32x3GetElement(storage, 2), 0b0011_1100 & 0b1100_0011)
  }
  
  func testBitwiseAndNot() {
    let lhs = CUInt32x3Make(0b0000_1111, 0b1111_0000, 0b0011_1100)
    let rhs = CUInt32x3Make(0b1111_1111, 0b0000_0000, 0b1100_0011)
    let storage = CUInt32x3BitwiseAndNot(lhs, rhs)
    XCTAssertEqual(CUInt32x3GetElement(storage, 0), (~0b0000_1111) & 0b1111_1111)
    XCTAssertEqual(CUInt32x3GetElement(storage, 1), (~0b1111_0000) & 0b0000_0000)
    XCTAssertEqual(CUInt32x3GetElement(storage, 2), (~0b0011_1100) & 0b1100_0011)
  }
  
  func testBitwiseOr() {
    let lhs = CUInt32x3Make(0b0000_1111, 0b1111_0000, 0b0011_1100)
    let rhs = CUInt32x3Make(0b1111_1111, 0b0000_0000, 0b1100_0011)
    let storage = CUInt32x3BitwiseOr(lhs, rhs)
    XCTAssertEqual(CUInt32x3GetElement(storage, 0), 0b0000_1111 | 0b1111_1111)
    XCTAssertEqual(CUInt32x3GetElement(storage, 1), 0b1111_0000 | 0b0000_0000)
    XCTAssertEqual(CUInt32x3GetElement(storage, 2), 0b0011_1100 | 0b1100_0011)
  }
  
  func testBitwiseExclusiveOr() {
    let lhs = CUInt32x3Make(0b0000_1111, 0b1111_0000, 0b0011_1100)
    let rhs = CUInt32x3Make(0b1111_1111, 0b0000_0000, 0b1100_0011)
    let storage = CUInt32x3BitwiseExclusiveOr(lhs, rhs)
    XCTAssertEqual(CUInt32x3GetElement(storage, 0), 0b0000_1111 ^ 0b1111_1111)
    XCTAssertEqual(CUInt32x3GetElement(storage, 1), 0b1111_0000 ^ 0b0000_0000)
    XCTAssertEqual(CUInt32x3GetElement(storage, 2), 0b0011_1100 ^ 0b1100_0011)
  }
  
  func testShiftLeft() {
    let lhs = CUInt32x3Make(0b1111_1111, 0b0000_1111, 0b0011_1100)
    let storage = CUInt32x3ShiftLeft(lhs, 2)
    XCTAssertEqual(CUInt32x3GetElement(storage, 0), 0b1111_1111 << 2)
    XCTAssertEqual(CUInt32x3GetElement(storage, 1), 0b0000_1111 << 2)
    XCTAssertEqual(CUInt32x3GetElement(storage, 2), 0b0011_1100 << 2)
  }
  
  func testShiftRight() {
    let lhs = CUInt32x3Make(0b1111_1111, 0b0000_1111, 0b0011_1100)
    let storage = CUInt32x3ShiftRight(lhs, 2)
    XCTAssertEqual(CUInt32x3GetElement(storage, 0), 0b1111_1111 >> 2)
    XCTAssertEqual(CUInt32x3GetElement(storage, 1), 0b0000_1111 >> 2)
    XCTAssertEqual(CUInt32x3GetElement(storage, 2), 0b0011_1100 >> 2)
  }
  
  //  // MARK: Conversion
  //
  //  func testConvertFromFloat32x3() {
  //      let fromStorage = CFloat32x3Make(2.49, 0.51, 1.5)
  //      let storage = CUInt32x3FromCFloat32x3(fromStorage)
  //
  //      XCTAssertEqual(CUInt32x3GetElement(storage, 0), 2)
  //      XCTAssertEqual(CUInt32x3GetElement(storage, 1), 1)
  //      XCTAssertEqual(CUInt32x3GetElement(storage, 2), 2)
  //  }
  //
  //  func testConvertFromInt32x3() {
  //      let fromStorage = CXInt32x3Make(2, 5, .max)
  //      let storage = CUInt32x3FromCXInt32x3(fromStorage)
  //
  //      XCTAssertEqual(CUInt32x3GetElement(storage, 0), 2)
  //      XCTAssertEqual(CUInt32x3GetElement(storage, 1), 5)
  //      XCTAssertEqual(CUInt32x3GetElement(storage, 2), UInt32(Int32.max))
  //  }
}
