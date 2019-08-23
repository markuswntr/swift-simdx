import XCTest
@testable import CSIMDX

final class CXInt32x3Tests: XCTestCase {

    func testMake() {
        let collection = CXInt32x3Make(1, 2, 3)

        XCTAssertEqual(CXInt32x3GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x3GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x3GetElement(collection, 2), 3)
        XCTAssertEqual(CXInt32x3GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testLoad() {
        var array: [Int32] = [1, 2, 3]
        let collection = CXInt32x3MakeLoad(&array)

        XCTAssertEqual(CXInt32x3GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x3GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x3GetElement(collection, 2), 3)
        XCTAssertEqual(CXInt32x3GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testMakeRepeatingValues() {
        let collection = CXInt32x3MakeRepeatingElement(3)

        XCTAssertEqual(CXInt32x3GetElement(collection, 0), 3)
        XCTAssertEqual(CXInt32x3GetElement(collection, 1), 3)
        XCTAssertEqual(CXInt32x3GetElement(collection, 2), 3)
        XCTAssertEqual(CXInt32x3GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testGetter() {
        let collection = CXInt32x3Make(1, 2, 3)

        XCTAssertEqual(CXInt32x3GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x3GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x3GetElement(collection, 2), 3)
        XCTAssertEqual(CXInt32x3GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testSetter() {
        var collection = CXInt32x3Make(1, 2, 3)

        XCTAssertEqual(CXInt32x3GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x3GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x3GetElement(collection, 2), 3)
        XCTAssertEqual(CXInt32x3GetElement(collection, 3), 0) // Make sure the unused value is zero

        CXInt32x3SetElement(&collection, 0, 5)
        CXInt32x3SetElement(&collection, 1, 6)
        CXInt32x3SetElement(&collection, 2, 7)

        XCTAssertEqual(CXInt32x3GetElement(collection, 0), 5)
        XCTAssertEqual(CXInt32x3GetElement(collection, 1), 6)
        XCTAssertEqual(CXInt32x3GetElement(collection, 2), 7)
        XCTAssertEqual(CXInt32x3GetElement(collection, 3), 0) // Make sure the unused value remains zero
    }

    func testZero() {
        let collection = CXInt32x3MakeZero()

        XCTAssertEqual(CXInt32x3GetElement(collection, 0), 0)
        XCTAssertEqual(CXInt32x3GetElement(collection, 1), 0)
        XCTAssertEqual(CXInt32x3GetElement(collection, 2), 0)
        XCTAssertEqual(CXInt32x3GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testAbsolute() {
        let normal = CXInt32x3Make(-1, 0, 3)
        let absolute = CXInt32x3Absolute(normal)

        XCTAssertEqual(CXInt32x3GetElement(absolute, 0), 1)
        XCTAssertEqual(CXInt32x3GetElement(absolute, 1), 0)
        XCTAssertEqual(CXInt32x3GetElement(absolute, 2), 3)
        XCTAssertEqual(CXInt32x3GetElement(absolute, 3), 0) // Make sure the unused value remains zero
    }

    func testNegate() {
        let normal = CXInt32x3Make(-1, 0, 3)
        let negate = CXInt32x3Negate(normal)

        XCTAssertEqual(CXInt32x3GetElement(negate, 0), 1)
        XCTAssertEqual(CXInt32x3GetElement(negate, 1), 0)
        XCTAssertEqual(CXInt32x3GetElement(negate, 2), -3)
        XCTAssertEqual(CXInt32x3GetElement(negate, 3), 0) // Make sure the unused value remains zero
    }

    func testAdd() {
        let lhs = CXInt32x3Make(1, 2, 3)
        let rhs = CXInt32x3Make(4, 3, 2)
        let sum = CXInt32x3Add(lhs, rhs)

        XCTAssertEqual(CXInt32x3GetElement(sum, 0), 5)
        XCTAssertEqual(CXInt32x3GetElement(sum, 1), 5)
        XCTAssertEqual(CXInt32x3GetElement(sum, 2), 5)
        XCTAssertEqual(CXInt32x3GetElement(sum, 3), 0) // Make sure the unused value remains zero
    }

    func testSubtract() {
        let lhs = CXInt32x3Make(1, 2, 3)
        let rhs = CXInt32x3Make(4, 3, 2)
        let sum = CXInt32x3Subtract(lhs, rhs)

        XCTAssertEqual(CXInt32x3GetElement(sum, 0), -3)
        XCTAssertEqual(CXInt32x3GetElement(sum, 1), -1)
        XCTAssertEqual(CXInt32x3GetElement(sum, 2), 1)
        XCTAssertEqual(CXInt32x3GetElement(sum, 3), 0) // Make sure the unused value remains zero
    }

    func testMultiply() {
        let lhs = CXInt32x3Make(1, -2, -3)
        let rhs = CXInt32x3Make(4, -3, 2)
        let product = CXInt32x3Multiply(lhs, rhs)

        XCTAssertEqual(CXInt32x3GetElement(product, 0), 4)
        XCTAssertEqual(CXInt32x3GetElement(product, 1), 6)
        XCTAssertEqual(CXInt32x3GetElement(product, 2), -6)
        XCTAssertEqual(CXInt32x3GetElement(product, 3), 0) // Make sure the unused value remains zero
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
