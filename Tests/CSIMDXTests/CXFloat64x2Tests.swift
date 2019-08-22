import XCTest
@testable import CSIMDX

final class CXFloat64x2Tests: XCTestCase {

    func testMake() {
        let collection = CXFloat64x2Make(1, 2)

        XCTAssertEqual(CXFloat64x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat64x2GetElement(collection, 1), 2)
    }

    func testLoad() {
        var array: [Float64] = [1, 2]
        let collection = CXFloat64x2Load(&array)

        XCTAssertEqual(CXFloat64x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat64x2GetElement(collection, 1), 2)
    }

    func testMakeRepeatingValues() {
        let collection = CXFloat64x2MakeRepeatingElement(3)

        XCTAssertEqual(CXFloat64x2GetElement(collection, 0), 3)
        XCTAssertEqual(CXFloat64x2GetElement(collection, 1), 3)
    }

    func testGetter() {
        let collection = CXFloat64x2Make(1, 2)

        XCTAssertEqual(CXFloat64x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat64x2GetElement(collection, 1), 2)
    }

    func testSetter() {
        var collection = CXFloat64x2Make(1, 2)

        XCTAssertEqual(CXFloat64x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat64x2GetElement(collection, 1), 2)

        CXFloat64x2SetElement(&collection, 0, 5)
        CXFloat64x2SetElement(&collection, 1, 6)

        XCTAssertEqual(CXFloat64x2GetElement(collection, 0), 5)
        XCTAssertEqual(CXFloat64x2GetElement(collection, 1), 6)
    }

    func testZero() {
        let collection = CXFloat64x2MakeZero()

        XCTAssertEqual(CXFloat64x2GetElement(collection, 0), 0)
        XCTAssertEqual(CXFloat64x2GetElement(collection, 1), 0)
    }

    func testAbsolute() {
        let normal = CXFloat64x2Make(-1, 3)
        let absolute = CXFloat64x2Absolute(normal)

        XCTAssertEqual(CXFloat64x2GetElement(absolute, 0), 1)
        XCTAssertEqual(CXFloat64x2GetElement(absolute, 1), 3)
    }

    func testNegate() {
        let normal = CXFloat64x2Make(-1, 3)
        let negate = CXFloat64x2Negate(normal)

        XCTAssertEqual(CXFloat64x2GetElement(negate, 0), 1)
        XCTAssertEqual(CXFloat64x2GetElement(negate, 1), -3)
    }

    func testAdd() {
        let lhs = CXFloat64x2Make(1, 2)
        let rhs = CXFloat64x2Make(4, 3)
        let sum = CXFloat64x2Add(lhs, rhs)

        XCTAssertEqual(CXFloat64x2GetElement(sum, 0), 5)
        XCTAssertEqual(CXFloat64x2GetElement(sum, 1), 5)
    }

    func testSubtract() {
        let lhs = CXFloat64x2Make(1, 2)
        let rhs = CXFloat64x2Make(4, 3)
        let sum = CXFloat64x2Subtract(lhs, rhs)

        XCTAssertEqual(CXFloat64x2GetElement(sum, 0), -3)
        XCTAssertEqual(CXFloat64x2GetElement(sum, 1), -1)

    }

    func testMultiply() {
        let lhs = CXFloat64x2Make(1, -2)
        let rhs = CXFloat64x2Make(-4, -3)
        let product = CXFloat64x2Multiply(lhs, rhs)

        XCTAssertEqual(CXFloat64x2GetElement(product, 0), -4)
        XCTAssertEqual(CXFloat64x2GetElement(product, 1), 6)
    }

    func testDivide() {
        let lhs = CXFloat64x2Make(1, -6)
        let rhs = CXFloat64x2Make(-4, -3)
        let product = CXFloat64x2Divide(lhs, rhs)

        XCTAssertEqual(CXFloat64x2GetElement(product, 0), -0.25)
        XCTAssertEqual(CXFloat64x2GetElement(product, 1), 2)
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
