import XCTest
@testable import CSIMDX

final class CXInt64x2Tests: XCTestCase {

    func testMake() {
        let collection = CXInt64x2Make(1, 2)

        XCTAssertEqual(CXInt64x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt64x2GetElement(collection, 1), 2)
    }

    func testLoad() {
        var array: [Int64] = [1, 2]
        let collection = CXInt64x2MakeLoad(&array)

        XCTAssertEqual(CXInt64x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt64x2GetElement(collection, 1), 2)
    }

    func testMakeRepeatingValues() {
        let collection = CXInt64x2MakeRepeatingElement(3)

        XCTAssertEqual(CXInt64x2GetElement(collection, 0), 3)
        XCTAssertEqual(CXInt64x2GetElement(collection, 1), 3)
    }

    func testGetter() {
        let collection = CXInt64x2Make(1, 2)

        XCTAssertEqual(CXInt64x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt64x2GetElement(collection, 1), 2)
    }

    func testSetter() {
        var collection = CXInt64x2Make(1, 2)

        XCTAssertEqual(CXInt64x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt64x2GetElement(collection, 1), 2)

        CXInt64x2SetElement(&collection, 0, 5)
        CXInt64x2SetElement(&collection, 1, 6)

        XCTAssertEqual(CXInt64x2GetElement(collection, 0), 5)
        XCTAssertEqual(CXInt64x2GetElement(collection, 1), 6)
    }

    func testZero() {
        let collection = CXInt64x2MakeZero()

        XCTAssertEqual(CXInt64x2GetElement(collection, 0), 0)
        XCTAssertEqual(CXInt64x2GetElement(collection, 1), 0)
    }

    func testAbsolute() {
        let normal = CXInt64x2Make(-1, 3)
        let absolute = CXInt64x2Absolute(normal)

        XCTAssertEqual(CXInt64x2GetElement(absolute, 0), 1)
        XCTAssertEqual(CXInt64x2GetElement(absolute, 1), 3)
    }

    func testNegate() {
        let normal = CXInt64x2Make(-1, 3)
        let negate = CXInt64x2Negate(normal)

        XCTAssertEqual(CXInt64x2GetElement(negate, 0), 1)
        XCTAssertEqual(CXInt64x2GetElement(negate, 1), -3)
    }

    func testAdd() {
        let lhs = CXInt64x2Make(1, 2)
        let rhs = CXInt64x2Make(4, 3)
        let sum = CXInt64x2Add(lhs, rhs)

        XCTAssertEqual(CXInt64x2GetElement(sum, 0), 5)
        XCTAssertEqual(CXInt64x2GetElement(sum, 1), 5)
    }

    func testSubtract() {
        let lhs = CXInt64x2Make(1, 2)
        let rhs = CXInt64x2Make(4, 3)
        let sum = CXInt64x2Subtract(lhs, rhs)

        XCTAssertEqual(CXInt64x2GetElement(sum, 0), -3)
        XCTAssertEqual(CXInt64x2GetElement(sum, 1), -1)

    }

    func testMultiply() {
        let lhs = CXInt64x2Make(1, -2)
        let rhs = CXInt64x2Make(-4, -3)
        let product = CXInt64x2Multiply(lhs, rhs)

        XCTAssertEqual(CXInt64x2GetElement(product, 0), -4)
        XCTAssertEqual(CXInt64x2GetElement(product, 1), 6)
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
