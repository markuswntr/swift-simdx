import XCTest
import CSIMDX

final class CFloat32x3Tests: XCTestCase {
  
  // MARK: Make
  
  func testMake() {
    let collection = CFloat32x3Make(1, 2, 3)
    
    XCTAssertEqual(CFloat32x3GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat32x3GetElement(collection, 1), 2)
    XCTAssertEqual(CFloat32x3GetElement(collection, 2), 3)
  }
  
  func testMakeLoad() {
    var array: [Float32] = [1, 2, 3]
    let collection = CFloat32x3MakeLoad(&array)
    
    XCTAssertEqual(CFloat32x3GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat32x3GetElement(collection, 1), 2)
    XCTAssertEqual(CFloat32x3GetElement(collection, 2), 3)
  }
  
  func testMakeRepeatingElement() {
    let collection = CFloat32x3MakeRepeatingElement(3)
    
    XCTAssertEqual(CFloat32x3GetElement(collection, 0), 3)
    XCTAssertEqual(CFloat32x3GetElement(collection, 1), 3)
    XCTAssertEqual(CFloat32x3GetElement(collection, 2), 3)
  }
  
  func testMakeZero() {
    let collection = CFloat32x3MakeZero()
    
    XCTAssertEqual(CFloat32x3GetElement(collection, 0), 0)
    XCTAssertEqual(CFloat32x3GetElement(collection, 1), 0)
    XCTAssertEqual(CFloat32x3GetElement(collection, 2), 0)
  }
  
  // MARK: Access
  
  func testGetElement() {
    let collection = CFloat32x3Make(1, 2, 3)
    
    XCTAssertEqual(CFloat32x3GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat32x3GetElement(collection, 1), 2)
    XCTAssertEqual(CFloat32x3GetElement(collection, 2), 3)
  }
  
  func testSetElement() {
    var collection = CFloat32x3Make(1, 2, 3)
    
    XCTAssertEqual(CFloat32x3GetElement(collection, 0), 1)
    XCTAssertEqual(CFloat32x3GetElement(collection, 1), 2)
    XCTAssertEqual(CFloat32x3GetElement(collection, 2), 3)
    
    CFloat32x3SetElement(&collection, 0, 5)
    CFloat32x3SetElement(&collection, 1, 6)
    CFloat32x3SetElement(&collection, 2, 7)
    
    XCTAssertEqual(CFloat32x3GetElement(collection, 0), 5)
    XCTAssertEqual(CFloat32x3GetElement(collection, 1), 6)
    XCTAssertEqual(CFloat32x3GetElement(collection, 2), 7)
  }
  
  // MARK: Conversion
  
  //    func testConvertFromInt32x3() {
  //        let fromStorage = CXInt32x3Make(-2, 1, 0)
  //        let storage = CFloat32x3FromCXInt32x3(fromStorage)
  //
  //        XCTAssertEqual(CFloat32x3GetElement(storage, 0), -2.0)
  //        XCTAssertEqual(CFloat32x3GetElement(storage, 1), 1.0)
  //        XCTAssertEqual(CFloat32x3GetElement(storage, 2), 0.0)
  //    }
  //    
  //    func testConvertFromUInt32x3() {
  //        let fromStorage = CXUInt32x3Make(2, 5, 3)
  //        let storage = CFloat32x3FromCXUInt32x3(fromStorage)
  //
  //        XCTAssertEqual(CFloat32x3GetElement(storage, 0), 2)
  //        XCTAssertEqual(CFloat32x3GetElement(storage, 1), 5)
  //        XCTAssertEqual(CFloat32x3GetElement(storage, 2), 3)
  //    }
  
  // MARK: Comparison
  
  func testMinimum() {
    let lhs = CFloat32x3Make(34, 12, 0)
    let rhs = CFloat32x3Make(-34, 24, -0)
    let storage = CFloat32x3Minimum(lhs, rhs)
    
    XCTAssertEqual(CFloat32x3GetElement(storage, 0), -34)
    XCTAssertEqual(CFloat32x3GetElement(storage, 1), 12)
    XCTAssertEqual(CFloat32x3GetElement(storage, 2), 0)
  }
  
  func testMaximum() {
    let lhs = CFloat32x3Make(34, 12, 0)
    let rhs = CFloat32x3Make(-34, 24, -0)
    let storage = CFloat32x3Maximum(lhs, rhs)
    
    XCTAssertEqual(CFloat32x3GetElement(storage, 0), 34)
    XCTAssertEqual(CFloat32x3GetElement(storage, 1), 24)
    XCTAssertEqual(CFloat32x3GetElement(storage, 2), 0)
  }
  
  // MARK: Arithmetic
  
  func testAbsolute() {
    let normal = CFloat32x3Make(-1, 0, 3)
    let absolute = CFloat32x3Absolute(normal)
    
    XCTAssertEqual(CFloat32x3GetElement(absolute, 0), 1)
    XCTAssertEqual(CFloat32x3GetElement(absolute, 1), 0)
    XCTAssertEqual(CFloat32x3GetElement(absolute, 2), 3)
  }
  
  func testNegate() {
    let normal = CFloat32x3Make(-1, 0, 3)
    let negate = CFloat32x3Negate(normal)
    
    XCTAssertEqual(CFloat32x3GetElement(negate, 0), 1)
    XCTAssertEqual(CFloat32x3GetElement(negate, 1), 0)
    XCTAssertEqual(CFloat32x3GetElement(negate, 2), -3)
  }
  
  func testAdd() {
    let lhs = CFloat32x3Make(1, 2, 3)
    let rhs = CFloat32x3Make(4, 3, 2)
    let sum = CFloat32x3Add(lhs, rhs)
    
    XCTAssertEqual(CFloat32x3GetElement(sum, 0), 5)
    XCTAssertEqual(CFloat32x3GetElement(sum, 1), 5)
    XCTAssertEqual(CFloat32x3GetElement(sum, 2), 5)
  }
  
  func testSubtract() {
    let lhs = CFloat32x3Make(1, 2, 3)
    let rhs = CFloat32x3Make(4, 3, 2)
    let sum = CFloat32x3Subtract(lhs, rhs)
    
    XCTAssertEqual(CFloat32x3GetElement(sum, 0), -3)
    XCTAssertEqual(CFloat32x3GetElement(sum, 1), -1)
    XCTAssertEqual(CFloat32x3GetElement(sum, 2), 1)
  }
  
  func testMultiply() {
    let lhs = CFloat32x3Make(1, -2, -3)
    let rhs = CFloat32x3Make(4, -3, 2)
    let product = CFloat32x3Multiply(lhs, rhs)
    
    XCTAssertEqual(CFloat32x3GetElement(product, 0), 4)
    XCTAssertEqual(CFloat32x3GetElement(product, 1), 6)
    XCTAssertEqual(CFloat32x3GetElement(product, 2), -6)
  }
  
  func testDivide() {
    let lhs = CFloat32x3Make(1, -6, -3)
    let rhs = CFloat32x3Make(-4, -3, 3)
    let product = CFloat32x3Divide(lhs, rhs)
    
    XCTAssertEqual(CFloat32x3GetElement(product, 0), -0.25)
    XCTAssertEqual(CFloat32x3GetElement(product, 1), 2)
    XCTAssertEqual(CFloat32x3GetElement(product, 2), -1)
  }
  
  func testSquareRoot() {
    let storage =  CFloat32x3SquareRoot(CFloat32x3Make(25, 144, 64))
    
    XCTAssertEqual(CFloat32x3GetElement(storage, 0), 5)
    XCTAssertEqual(CFloat32x3GetElement(storage, 1), 12)
    XCTAssertEqual(CFloat32x3GetElement(storage, 2), 8)
  }
}
