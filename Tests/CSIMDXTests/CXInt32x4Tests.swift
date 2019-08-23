import XCTest
@testable import CSIMDX

final class CXInt32x4Tests: XCTestCase {

    func testMake() {
        let collection = CXInt32x4Make(1, 2, 3, 4)
        
        XCTAssertEqual(CXInt32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CXInt32x4GetElement(collection, 3), 4)
    }

    func testLoad() {
        var array: [Int32] = [1, 2, 3, 4]
        let collection = CXInt32x4MakeLoad(&array)

        XCTAssertEqual(CXInt32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CXInt32x4GetElement(collection, 3), 4)
    }

    func testMakeRepeatingValues() {
        let collection = CXInt32x4MakeRepeatingElement(3)

        XCTAssertEqual(CXInt32x4GetElement(collection, 0), 3)
        XCTAssertEqual(CXInt32x4GetElement(collection, 1), 3)
        XCTAssertEqual(CXInt32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CXInt32x4GetElement(collection, 3), 3)
    }

    func testGetter() {
        let collection = CXInt32x4Make(1, 2, 3, 4)
        
        XCTAssertEqual(CXInt32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CXInt32x4GetElement(collection, 3), 4)
    }
    
    func testSetter() {
        var collection = CXInt32x4Make(1, 2, 3, 4)

        XCTAssertEqual(CXInt32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CXInt32x4GetElement(collection, 3), 4)

        CXInt32x4SetElement(&collection, 0, 5)
        CXInt32x4SetElement(&collection, 1, 6)
        CXInt32x4SetElement(&collection, 2, 7)
        CXInt32x4SetElement(&collection, 3, 8)

        XCTAssertEqual(CXInt32x4GetElement(collection, 0), 5)
        XCTAssertEqual(CXInt32x4GetElement(collection, 1), 6)
        XCTAssertEqual(CXInt32x4GetElement(collection, 2), 7)
        XCTAssertEqual(CXInt32x4GetElement(collection, 3), 8)
    }

    func testZero() {
        let collection = CXInt32x4MakeZero()

        XCTAssertEqual(CXInt32x4GetElement(collection, 0), 0)
        XCTAssertEqual(CXInt32x4GetElement(collection, 1), 0)
        XCTAssertEqual(CXInt32x4GetElement(collection, 2), 0)
        XCTAssertEqual(CXInt32x4GetElement(collection, 3), 0)
    }

    func testAbsolute() {
        let normal = CXInt32x4Make(-1, 0, 3, -4)
        let absolute = CXInt32x4Absolute(normal)

        XCTAssertEqual(CXInt32x4GetElement(absolute, 0), 1)
        XCTAssertEqual(CXInt32x4GetElement(absolute, 1), 0)
        XCTAssertEqual(CXInt32x4GetElement(absolute, 2), 3)
        XCTAssertEqual(CXInt32x4GetElement(absolute, 3), 4)
    }

    func testNegate() {
        let normal = CXInt32x4Make(-1, 0, 3, -4)
        let negate = CXInt32x4Negate(normal)

        XCTAssertEqual(CXInt32x4GetElement(negate, 0), 1)
        XCTAssertEqual(CXInt32x4GetElement(negate, 1), 0)
        XCTAssertEqual(CXInt32x4GetElement(negate, 2), -3)
        XCTAssertEqual(CXInt32x4GetElement(negate, 3), 4)
    }

    func testAdd() {
        let lhs = CXInt32x4Make(1, 2, 3, 4)
        let rhs = CXInt32x4Make(4, 3, 2, 1)
        let sum = CXInt32x4Add(lhs, rhs)

        XCTAssertEqual(CXInt32x4GetElement(sum, 0), 5)
        XCTAssertEqual(CXInt32x4GetElement(sum, 1), 5)
        XCTAssertEqual(CXInt32x4GetElement(sum, 2), 5)
        XCTAssertEqual(CXInt32x4GetElement(sum, 3), 5)
    }

    func testSubtract() {
        let lhs = CXInt32x4Make(1, 2, 3, 4)
        let rhs = CXInt32x4Make(4, 3, 2, 1)
        let sum = CXInt32x4Subtract(lhs, rhs)

        XCTAssertEqual(CXInt32x4GetElement(sum, 0), -3)
        XCTAssertEqual(CXInt32x4GetElement(sum, 1), -1)
        XCTAssertEqual(CXInt32x4GetElement(sum, 2), 1)
        XCTAssertEqual(CXInt32x4GetElement(sum, 3), 3)

    }

    func testMultiply() {
        let lhs = CXInt32x4Make(1, -2, -3, 4)
        let rhs = CXInt32x4Make(4, -3, 2, -1)
        let product = CXInt32x4Multiply(lhs, rhs)

        XCTAssertEqual(CXInt32x4GetElement(product, 0), 4)
        XCTAssertEqual(CXInt32x4GetElement(product, 1), 6)
        XCTAssertEqual(CXInt32x4GetElement(product, 2), -6)
        XCTAssertEqual(CXInt32x4GetElement(product, 3), -4)
    }

    static var allTests = [
        ("testMake", testMake),
        ("testLoad", testLoad),
        ("testMakeRepeatingValues", testMakeRepeatingValues),
        ("testGetter", testGetter),
        ("testSetter", testSetter),
        ("testZero", testZero),
        ("testAbsolute", testAbsolute),
        ("testNegate", testNegate),
        ("testAdd", testAdd),
        ("testSubtract", testSubtract),
        ("testMultiply", testMultiply)
    ]
}
