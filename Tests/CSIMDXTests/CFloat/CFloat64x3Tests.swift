import XCTest
import CSIMDX

final class CFloat64x3Tests: XCTestCase {
  
  // MARK: Make
  
  func testMake() {
    let collection = CFloat64x3Make(1, 2, 3)
    
    XCTAssertEqual(CFloat64x3GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat64x3GetElement(collection, 1), 2)
    XCTAssertEqual(CFloat64x3GetElement(collection, 2), 3)
  }
  
  func testMakeLoad() {
    var array: [Float64] = [1, 2, 3]
    let collection = CFloat64x3MakeLoad(&array)
    
    XCTAssertEqual(CFloat64x3GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat64x3GetElement(collection, 1), 2)
    XCTAssertEqual(CFloat64x3GetElement(collection, 2), 3)
  }
  
  func testMakeRepeatingElement() {
    let collection = CFloat64x3MakeRepeatingElement(3)
    
    XCTAssertEqual(CFloat64x3GetElement(collection, 0), 3)
    XCTAssertEqual(CFloat64x3GetElement(collection, 1), 3)
    XCTAssertEqual(CFloat64x3GetElement(collection, 2), 3)
  }
  
  func testMakeZero() {
    let collection = CFloat64x3MakeZero()
    
    XCTAssertEqual(CFloat64x3GetElement(collection, 0), 0)
    XCTAssertEqual(CFloat64x3GetElement(collection, 1), 0)
    XCTAssertEqual(CFloat64x3GetElement(collection, 2), 0)
  }
  
  // MARK: Access
  
  func testGetElement() {
    let collection = CFloat64x3Make(1, 2, 3)
    
    XCTAssertEqual(CFloat64x3GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat64x3GetElement(collection, 1), 2)
    XCTAssertEqual(CFloat64x3GetElement(collection, 2), 3)
  }
  
  func testSetElement() {
    var collection = CFloat64x3Make(1, 2, 3)
    
    XCTAssertEqual(CFloat64x3GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat64x3GetElement(collection, 1), 2)
    XCTAssertEqual(CFloat64x3GetElement(collection, 2), 3)
    
    CFloat64x3SetElement(&collection, 0, 5)
    CFloat64x3SetElement(&collection, 1, 6)
    CFloat64x3SetElement(&collection, 2, 7)
    
    XCTAssertEqual(CFloat64x3GetElement(collection, 0), 5)
    XCTAssertEqual(CFloat64x3GetElement(collection, 1), 6)
    XCTAssertEqual(CFloat64x3GetElement(collection, 2), 7)
  }
  
  // MARK: Comparison
  
  func testMinimum() {
    let lhs = CFloat64x3Make(34, 12, 0)
    let rhs = CFloat64x3Make(-34, 24, -0)
    let storage = CFloat64x3Minimum(lhs, rhs)
    
    XCTAssertEqual(CFloat64x3GetElement(storage, 0), -34)
    XCTAssertEqual(CFloat64x3GetElement(storage, 1), 12)
    XCTAssertEqual(CFloat64x3GetElement(storage, 2), 0)
  }
  
  func testMaximum() {
    let lhs = CFloat64x3Make(34, 12, 0)
    let rhs = CFloat64x3Make(-34, 24, -0)
    let storage = CFloat64x3Maximum(lhs, rhs)
    
    XCTAssertEqual(CFloat64x3GetElement(storage, 0), 34)
    XCTAssertEqual(CFloat64x3GetElement(storage, 1), 24)
    XCTAssertEqual(CFloat64x3GetElement(storage, 2), 0)
  }
  
  // MARK: Arithmetic
  
  func testMagnitude() {
    let normal = CFloat64x3Make(-1, 0, 3)
    let absolute = CFloat64x3Magnitude(normal)
    
    XCTAssertEqual(CFloat64x3GetElement(absolute, 0), 1)
    XCTAssertEqual(CFloat64x3GetElement(absolute, 1), 0)
    XCTAssertEqual(CFloat64x3GetElement(absolute, 2), 3)
  }
  
  func testNegate() {
    let normal = CFloat64x3Make(-1, 0, 3)
    let negate = CFloat64x3Negate(normal)
    
    XCTAssertEqual(CFloat64x3GetElement(negate, 0), 1)
    XCTAssertEqual(CFloat64x3GetElement(negate, 1), 0)
    XCTAssertEqual(CFloat64x3GetElement(negate, 2), -3)
  }
  
  func testAdd() {
    let lhs = CFloat64x3Make(1, 2, 3)
    let rhs = CFloat64x3Make(4, 3, 2)
    let sum = CFloat64x3Add(lhs, rhs)
    
    XCTAssertEqual(CFloat64x3GetElement(sum, 0), 5)
    XCTAssertEqual(CFloat64x3GetElement(sum, 1), 5)
    XCTAssertEqual(CFloat64x3GetElement(sum, 2), 5)
  }
  
  func testSubtract() {
    let lhs = CFloat64x3Make(1, 2, 3)
    let rhs = CFloat64x3Make(4, 3, 2)
    let sum = CFloat64x3Subtract(lhs, rhs)
    
    XCTAssertEqual(CFloat64x3GetElement(sum, 0), -3)
    XCTAssertEqual(CFloat64x3GetElement(sum, 1), -1)
    XCTAssertEqual(CFloat64x3GetElement(sum, 2), 1)
  }
  
  func testMultiply() {
    let lhs = CFloat64x3Make(1, -2, -3)
    let rhs = CFloat64x3Make(4, -3, 2)
    let product = CFloat64x3Multiply(lhs, rhs)
    
    XCTAssertEqual(CFloat64x3GetElement(product, 0), 4)
    XCTAssertEqual(CFloat64x3GetElement(product, 1), 6)
    XCTAssertEqual(CFloat64x3GetElement(product, 2), -6)
  }
  
  func testDivide() {
    let lhs = CFloat64x3Make(1, -6, -3)
    let rhs = CFloat64x3Make(-4, -3, 3)
    let product = CFloat64x3Divide(lhs, rhs)
    
    XCTAssertEqual(CFloat64x3GetElement(product, 0), -0.25)
    XCTAssertEqual(CFloat64x3GetElement(product, 1), 2)
    XCTAssertEqual(CFloat64x3GetElement(product, 2), -1)
  }
  
  func testSquareRoot() {
    let storage =  CFloat64x3SquareRoot(CFloat64x3Make(25, 144, 64))
    
    XCTAssertEqual(CFloat64x3GetElement(storage, 0), 5)
    XCTAssertEqual(CFloat64x3GetElement(storage, 1), 12)
    XCTAssertEqual(CFloat64x3GetElement(storage, 2), 8)
  }
}
