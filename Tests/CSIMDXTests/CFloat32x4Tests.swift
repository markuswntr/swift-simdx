import XCTest
import CSIMDX

final class CFloat32x4Tests: XCTestCase {

    // MARK: Make

    func testMake() {
        let collection = CFloat32x4Make(1, 2, 3, 4)
        
        XCTAssertEqual(CFloat32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CFloat32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CFloat32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CFloat32x4GetElement(collection, 3), 4)
    }

    func testMakeLoad() {
        var array: [Float32] = [1, 2, 3, 4]
        let collection = CFloat32x4MakeLoad(&array)

        XCTAssertEqual(CFloat32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CFloat32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CFloat32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CFloat32x4GetElement(collection, 3), 4)
    }

    func testMakeRepeatingElement() {
        let collection = CFloat32x4MakeRepeatingElement(3)

        XCTAssertEqual(CFloat32x4GetElement(collection, 0), 3)
        XCTAssertEqual(CFloat32x4GetElement(collection, 1), 3)
        XCTAssertEqual(CFloat32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CFloat32x4GetElement(collection, 3), 3)
    }

    func testMakeZero() {
        let collection = CFloat32x4MakeZero()

        XCTAssertEqual(CFloat32x4GetElement(collection, 0), 0)
        XCTAssertEqual(CFloat32x4GetElement(collection, 1), 0)
        XCTAssertEqual(CFloat32x4GetElement(collection, 2), 0)
        XCTAssertEqual(CFloat32x4GetElement(collection, 3), 0)
    }

    // MARK: Access

    func testGetElement() {
        let collection = CFloat32x4Make(1, 2, 3, 4)
        
        XCTAssertEqual(CFloat32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CFloat32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CFloat32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CFloat32x4GetElement(collection, 3), 4)
    }
    
    func testSetElement() {
        var collection = CFloat32x4Make(1, 2, 3, 4)

        XCTAssertEqual(CFloat32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CFloat32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CFloat32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CFloat32x4GetElement(collection, 3), 4)

        CFloat32x4SetElement(&collection, 0, 5)
        CFloat32x4SetElement(&collection, 1, 6)
        CFloat32x4SetElement(&collection, 2, 7)
        CFloat32x4SetElement(&collection, 3, 8)

        XCTAssertEqual(CFloat32x4GetElement(collection, 0), 5)
        XCTAssertEqual(CFloat32x4GetElement(collection, 1), 6)
        XCTAssertEqual(CFloat32x4GetElement(collection, 2), 7)
        XCTAssertEqual(CFloat32x4GetElement(collection, 3), 8)
    }

    // MARK: Conversion

//    func testConvertFromInt32x4() {
//        let fromStorage = CXInt32x4Make(-2, 1, 0, -23)
//        let storage = CFloat32x4FromCXInt32x4(fromStorage)
//
//        XCTAssertEqual(CFloat32x4GetElement(storage, 0), -2.0)
//        XCTAssertEqual(CFloat32x4GetElement(storage, 1), 1.0)
//        XCTAssertEqual(CFloat32x4GetElement(storage, 2), 0.0)
//        XCTAssertEqual(CFloat32x4GetElement(storage, 3), -23.0)
//    }
//
//    func testConvertFromUInt32x4() {
//        let fromStorage = CXUInt32x4Make(2, 5, 3, 48)
//        let storage = CFloat32x4FromCXUInt32x4(fromStorage)
//
//        XCTAssertEqual(CFloat32x4GetElement(storage, 0), 2)
//        XCTAssertEqual(CFloat32x4GetElement(storage, 1), 5)
//        XCTAssertEqual(CFloat32x4GetElement(storage, 2), 3)
//        XCTAssertEqual(CFloat32x4GetElement(storage, 3), 48)
//    }

    // MARK: Comparison

    func testMinimum() {
        let lhs = CFloat32x4Make(34, 12, 0, 23.0)
        let rhs = CFloat32x4Make(-34, 24, -0, 23.1)
        let storage = CFloat32x4Minimum(lhs, rhs)

        XCTAssertEqual(CFloat32x4GetElement(storage, 0), -34)
        XCTAssertEqual(CFloat32x4GetElement(storage, 1), 12)
        XCTAssertEqual(CFloat32x4GetElement(storage, 2), 0)
        XCTAssertEqual(CFloat32x4GetElement(storage, 3), 23.0)
    }

    func testMaximum() {
        let lhs = CFloat32x4Make(34, 12, 0, 23.0)
        let rhs = CFloat32x4Make(-34, 24, -0, 23.1)
        let storage = CFloat32x4Maximum(lhs, rhs)

        XCTAssertEqual(CFloat32x4GetElement(storage, 0), 34)
        XCTAssertEqual(CFloat32x4GetElement(storage, 1), 24)
        XCTAssertEqual(CFloat32x4GetElement(storage, 2), 0)
        XCTAssertEqual(CFloat32x4GetElement(storage, 3), 23.1)
    }

    // MARK: Arithmetic

    func testAbsolute() {
        let normal = CFloat32x4Make(-1, 0, 3, -4)
        let absolute = CFloat32x4Absolute(normal)

        XCTAssertEqual(CFloat32x4GetElement(absolute, 0), 1)
        XCTAssertEqual(CFloat32x4GetElement(absolute, 1), 0)
        XCTAssertEqual(CFloat32x4GetElement(absolute, 2), 3)
        XCTAssertEqual(CFloat32x4GetElement(absolute, 3), 4)
    }

    func testNegate() {
        let normal = CFloat32x4Make(-1, 0, 3, -4)
        let negate = CFloat32x4Negate(normal)

        XCTAssertEqual(CFloat32x4GetElement(negate, 0), 1)
        XCTAssertEqual(CFloat32x4GetElement(negate, 1), 0)
        XCTAssertEqual(CFloat32x4GetElement(negate, 2), -3)
        XCTAssertEqual(CFloat32x4GetElement(negate, 3), 4)
    }

    func testAdd() {
        let lhs = CFloat32x4Make(1, 2, 3, 4)
        let rhs = CFloat32x4Make(4, 3, 2, 1)
        let sum = CFloat32x4Add(lhs, rhs)

        XCTAssertEqual(CFloat32x4GetElement(sum, 0), 5)
        XCTAssertEqual(CFloat32x4GetElement(sum, 1), 5)
        XCTAssertEqual(CFloat32x4GetElement(sum, 2), 5)
        XCTAssertEqual(CFloat32x4GetElement(sum, 3), 5)
    }

    func testSubtract() {
        let lhs = CFloat32x4Make(1, 2, 3, 4)
        let rhs = CFloat32x4Make(4, 3, 2, 1)
        let sum = CFloat32x4Subtract(lhs, rhs)

        XCTAssertEqual(CFloat32x4GetElement(sum, 0), -3)
        XCTAssertEqual(CFloat32x4GetElement(sum, 1), -1)
        XCTAssertEqual(CFloat32x4GetElement(sum, 2), 1)
        XCTAssertEqual(CFloat32x4GetElement(sum, 3), 3)

    }

    func testMultiply() {
        let lhs = CFloat32x4Make(1, -2, -3, 4)
        let rhs = CFloat32x4Make(4, -3, 2, -1)
        let product = CFloat32x4Multiply(lhs, rhs)

        XCTAssertEqual(CFloat32x4GetElement(product, 0), 4)
        XCTAssertEqual(CFloat32x4GetElement(product, 1), 6)
        XCTAssertEqual(CFloat32x4GetElement(product, 2), -6)
        XCTAssertEqual(CFloat32x4GetElement(product, 3), -4)
    }

    func testDivide() {
        let lhs = CFloat32x4Make(1, -6, -3, 4)
        let rhs = CFloat32x4Make(-4, -3, 3, 2)
        let product = CFloat32x4Divide(lhs, rhs)

        XCTAssertEqual(CFloat32x4GetElement(product, 0), -0.25)
        XCTAssertEqual(CFloat32x4GetElement(product, 1), 2)
        XCTAssertEqual(CFloat32x4GetElement(product, 2), -1)
        XCTAssertEqual(CFloat32x4GetElement(product, 3), 2)
    }

//    func testSquareRoot() {
//        let storage =  CFloat32x4SquareRoot(CFloat32x4Make(25, 144, 64, 256))
//
//        XCTAssertEqual(CFloat32x4GetElement(storage, 0), 5)
//        XCTAssertEqual(CFloat32x4GetElement(storage, 1), 12)
//        XCTAssertEqual(CFloat32x4GetElement(storage, 2), 8)
//        XCTAssertEqual(CFloat32x4GetElement(storage, 3), 16)
//    }
}
