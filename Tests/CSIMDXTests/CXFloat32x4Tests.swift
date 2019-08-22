import XCTest
@testable import CSIMDX

final class CXFloat32x4Tests: XCTestCase {

    func testMake() {
        let collection = CXFloat32x4Make(1, 2, 3, 4)
        
        XCTAssertEqual(CXFloat32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 3), 4)
    }

    func testLoad() {
        var array: [Float32] = [1, 2, 3, 4]
        let collection = CXFloat32x4Load(&array)

        XCTAssertEqual(CXFloat32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 3), 4)
    }

    func testMakeRepeatingValues() {
        let collection = CXFloat32x4MakeRepeatingElement(3)

        XCTAssertEqual(CXFloat32x4GetElement(collection, 0), 3)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 1), 3)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 3), 3)
    }

    func testGetter() {
        let collection = CXFloat32x4Make(1, 2, 3, 4)
        
        XCTAssertEqual(CXFloat32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 3), 4)
    }
    
    func testSetter() {
        var collection = CXFloat32x4Make(1, 2, 3, 4)

        XCTAssertEqual(CXFloat32x4GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 2), 3)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 3), 4)

        CXFloat32x4SetElement(&collection, 0, 5)
        CXFloat32x4SetElement(&collection, 1, 6)
        CXFloat32x4SetElement(&collection, 2, 7)
        CXFloat32x4SetElement(&collection, 3, 8)

        XCTAssertEqual(CXFloat32x4GetElement(collection, 0), 5)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 1), 6)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 2), 7)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 3), 8)
    }

    func testZero() {
        let collection = CXFloat32x4MakeZero()

        XCTAssertEqual(CXFloat32x4GetElement(collection, 0), 0)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 1), 0)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 2), 0)
        XCTAssertEqual(CXFloat32x4GetElement(collection, 3), 0)
    }

    func testAbsolute() {
        let normal = CXFloat32x4Make(-1, 0, 3, -4)
        let absolute = CXFloat32x4Absolute(normal)

        XCTAssertEqual(CXFloat32x4GetElement(absolute, 0), 1)
        XCTAssertEqual(CXFloat32x4GetElement(absolute, 1), 0)
        XCTAssertEqual(CXFloat32x4GetElement(absolute, 2), 3)
        XCTAssertEqual(CXFloat32x4GetElement(absolute, 3), 4)
    }

    func testNegate() {
        let normal = CXFloat32x4Make(-1, 0, 3, -4)
        let negate = CXFloat32x4Negate(normal)

        XCTAssertEqual(CXFloat32x4GetElement(negate, 0), 1)
        XCTAssertEqual(CXFloat32x4GetElement(negate, 1), 0)
        XCTAssertEqual(CXFloat32x4GetElement(negate, 2), -3)
        XCTAssertEqual(CXFloat32x4GetElement(negate, 3), 4)
    }

    func testAdd() {
        let lhs = CXFloat32x4Make(1, 2, 3, 4)
        let rhs = CXFloat32x4Make(4, 3, 2, 1)
        let sum = CXFloat32x4Add(lhs, rhs)

        XCTAssertEqual(CXFloat32x4GetElement(sum, 0), 5)
        XCTAssertEqual(CXFloat32x4GetElement(sum, 1), 5)
        XCTAssertEqual(CXFloat32x4GetElement(sum, 2), 5)
        XCTAssertEqual(CXFloat32x4GetElement(sum, 3), 5)
    }

    func testSubtract() {
        let lhs = CXFloat32x4Make(1, 2, 3, 4)
        let rhs = CXFloat32x4Make(4, 3, 2, 1)
        let sum = CXFloat32x4Subtract(lhs, rhs)

        XCTAssertEqual(CXFloat32x4GetElement(sum, 0), -3)
        XCTAssertEqual(CXFloat32x4GetElement(sum, 1), -1)
        XCTAssertEqual(CXFloat32x4GetElement(sum, 2), 1)
        XCTAssertEqual(CXFloat32x4GetElement(sum, 3), 3)

    }

    func testMultiply() {
        let lhs = CXFloat32x4Make(1, -2, -3, 4)
        let rhs = CXFloat32x4Make(4, -3, 2, -1)
        let product = CXFloat32x4Multiply(lhs, rhs)

        XCTAssertEqual(CXFloat32x4GetElement(product, 0), 4)
        XCTAssertEqual(CXFloat32x4GetElement(product, 1), 6)
        XCTAssertEqual(CXFloat32x4GetElement(product, 2), -6)
        XCTAssertEqual(CXFloat32x4GetElement(product, 3), -4)
    }

    func testDivide() {
        let lhs = CXFloat32x4Make(1, -6, -3, 4)
        let rhs = CXFloat32x4Make(-4, -3, 3, 2)
        let product = CXFloat32x4Divide(lhs, rhs)

        XCTAssertEqual(CXFloat32x4GetElement(product, 0), -0.25)
        XCTAssertEqual(CXFloat32x4GetElement(product, 1), 2)
        XCTAssertEqual(CXFloat32x4GetElement(product, 2), -1)
        XCTAssertEqual(CXFloat32x4GetElement(product, 3), 2)
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
        ("testMultiply", testMultiply),
        ("testDivide", testDivide)
    ]
}
