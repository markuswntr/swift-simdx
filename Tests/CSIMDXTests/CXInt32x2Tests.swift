import XCTest
@testable import CSIMDX

final class CXInt32x2Tests: XCTestCase {

    func testMake() {
        let collection = CXInt32x2Make(1, 2)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXInt32x2GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testLoad() {
        var array: [Int32] = [1, 2]
        let collection = CXInt32x2MakeLoad(&array)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXInt32x2GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testMakeRepeatingValues() {
        let collection = CXInt32x2MakeRepeatingElement(3)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 3)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 3)
        XCTAssertEqual(CXInt32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXInt32x2GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testGetter() {
        let collection = CXInt32x2Make(1, 2)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXInt32x2GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testSetter() {
        var collection = CXInt32x2Make(1, 2)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 2)
        XCTAssertEqual(CXInt32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXInt32x2GetElement(collection, 3), 0) // Make sure the unused value is zero

        CXInt32x2SetElement(&collection, 0, 5)
        CXInt32x2SetElement(&collection, 1, 6)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 5)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 6)
        XCTAssertEqual(CXInt32x2GetElement(collection, 2), 0) // Make sure the unused value remains zero
        XCTAssertEqual(CXInt32x2GetElement(collection, 3), 0) // Make sure the unused value remains zero
    }

    func testZero() {
        let collection = CXInt32x2MakeZero()

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 0)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 0)
        XCTAssertEqual(CXInt32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXInt32x2GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testAbsolute() {
        let normal = CXInt32x2Make(-1, 3)
        let absolute = CXInt32x2Absolute(normal)

        XCTAssertEqual(CXInt32x2GetElement(absolute, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(absolute, 1), 3)
        XCTAssertEqual(CXInt32x2GetElement(absolute, 2), 0) // Make sure the unused value remains zero
        XCTAssertEqual(CXInt32x2GetElement(absolute, 3), 0) // Make sure the unused value remains zero
    }

    func testNegate() {
        let normal = CXInt32x2Make(-1, 3)
        let negate = CXInt32x2Negate(normal)

        XCTAssertEqual(CXInt32x2GetElement(negate, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(negate, 1), -3)
        XCTAssertEqual(CXInt32x2GetElement(negate, 2), 0) // Make sure the unused value remains zero
        XCTAssertEqual(CXInt32x2GetElement(negate, 3), 0) // Make sure the unused value remains zero
    }

    func testAdd() {
        let lhs = CXInt32x2Make(1, 2)
        let rhs = CXInt32x2Make(4, 3)
        let sum = CXInt32x2Add(lhs, rhs)

        XCTAssertEqual(CXInt32x2GetElement(sum, 0), 5)
        XCTAssertEqual(CXInt32x2GetElement(sum, 1), 5)
        XCTAssertEqual(CXInt32x2GetElement(sum, 2), 0) // Make sure the unused value remains zero
        XCTAssertEqual(CXInt32x2GetElement(sum, 3), 0) // Make sure the unused value remains zero
    }

    func testSubtract() {
        let lhs = CXInt32x2Make(1, 2)
        let rhs = CXInt32x2Make(4, 3)
        let sum = CXInt32x2Subtract(lhs, rhs)

        XCTAssertEqual(CXInt32x2GetElement(sum, 0), -3)
        XCTAssertEqual(CXInt32x2GetElement(sum, 1), -1)
        XCTAssertEqual(CXInt32x2GetElement(sum, 2), 0) // Make sure the unused value remains zero
        XCTAssertEqual(CXInt32x2GetElement(sum, 3), 0) // Make sure the unused value remains zero

    }

    func testMultiply() {
        let lhs = CXInt32x2Make(1, -2)
        let rhs = CXInt32x2Make(-4, -3)
        let product = CXInt32x2Multiply(lhs, rhs)

        XCTAssertEqual(CXInt32x2GetElement(product, 0), -4)
        XCTAssertEqual(CXInt32x2GetElement(product, 1), 6)
        XCTAssertEqual(CXInt32x2GetElement(product, 2), 0) // Make sure the unused value remains zero
        XCTAssertEqual(CXInt32x2GetElement(product, 3), 0) // Make sure the unused value remains zero
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
