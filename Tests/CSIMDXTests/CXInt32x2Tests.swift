import XCTest
import CSIMDX

final class CXInt32x2Tests: XCTestCase {

    func testMake() {
        let collection = CXInt32x2Make(1, 2)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 2)
    }

    func testLoad() {
        var array: [Int32] = [1, 2]
        let collection = CXInt32x2MakeLoad(&array)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 2)
    }

    func testMakeRepeatingValues() {
        let collection = CXInt32x2MakeRepeatingElement(3)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 3)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 3)
    }

    func testGetter() {
        let collection = CXInt32x2Make(1, 2)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 2)
    }

    func testSetter() {
        var collection = CXInt32x2Make(1, 2)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 2)

        CXInt32x2SetElement(&collection, 0, 5)
        CXInt32x2SetElement(&collection, 1, 6)

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 5)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 6)
    }

    func testZero() {
        let collection = CXInt32x2MakeZero()

        XCTAssertEqual(CXInt32x2GetElement(collection, 0), 0)
        XCTAssertEqual(CXInt32x2GetElement(collection, 1), 0)
    }

    func testAbsolute() {
        let normal = CXInt32x2Make(-1, 3)
        let absolute = CXInt32x2Absolute(normal)

        XCTAssertEqual(CXInt32x2GetElement(absolute, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(absolute, 1), 3)
    }

    func testNegate() {
        let normal = CXInt32x2Make(-1, 3)
        let negate = CXInt32x2Negate(normal)

        XCTAssertEqual(CXInt32x2GetElement(negate, 0), 1)
        XCTAssertEqual(CXInt32x2GetElement(negate, 1), -3)
    }

    func testAdd() {
        let lhs = CXInt32x2Make(1, 2)
        let rhs = CXInt32x2Make(4, 3)
        let sum = CXInt32x2Add(lhs, rhs)

        XCTAssertEqual(CXInt32x2GetElement(sum, 0), 5)
        XCTAssertEqual(CXInt32x2GetElement(sum, 1), 5)
    }

    func testSubtract() {
        let lhs = CXInt32x2Make(1, 2)
        let rhs = CXInt32x2Make(4, 3)
        let sum = CXInt32x2Subtract(lhs, rhs)

        XCTAssertEqual(CXInt32x2GetElement(sum, 0), -3)
        XCTAssertEqual(CXInt32x2GetElement(sum, 1), -1)

    }

    func testMultiply() {
        let lhs = CXInt32x2Make(1, -2)
        let rhs = CXInt32x2Make(-4, -3)
        let product = CXInt32x2Multiply(lhs, rhs)

        XCTAssertEqual(CXInt32x2GetElement(product, 0), -4)
        XCTAssertEqual(CXInt32x2GetElement(product, 1), 6)
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
