import XCTest
@testable import CSIMDX

final class CXFloat32x3Tests: XCTestCase {

    func testMake() {
        let collection = CXFloat32x3Make(1, 2, 3)

        XCTAssertEqual(CXFloat32x3GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 2), 3)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testLoad() {
        var array: [Float32] = [1, 2, 3]
        let collection = CXFloat32x3Load(&array)

        XCTAssertEqual(CXFloat32x3GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 2), 3)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testMakeRepeatingValues() {
        let collection = CXFloat32x3MakeRepeatingElement(3)

        XCTAssertEqual(CXFloat32x3GetElement(collection, 0), 3)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 1), 3)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 2), 3)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testZero() {
        let collection = CXFloat32x3MakeZero()

        XCTAssertEqual(CXFloat32x3GetElement(collection, 0), 0)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 1), 0)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 2), 0)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testGetter() {
        let collection = CXFloat32x3Make(1, 2, 3)

        XCTAssertEqual(CXFloat32x3GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 2), 3)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testSetter() {
        var collection = CXFloat32x3Make(1, 2, 3)

        XCTAssertEqual(CXFloat32x3GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 2), 3)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 3), 0) // Make sure the unused value is zero

        CXFloat32x3SetElement(&collection, 0, 5)
        CXFloat32x3SetElement(&collection, 1, 6)
        CXFloat32x3SetElement(&collection, 2, 7)

        XCTAssertEqual(CXFloat32x3GetElement(collection, 0), 5)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 1), 6)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 2), 7)
        XCTAssertEqual(CXFloat32x3GetElement(collection, 3), 0) // Make sure the unused value remains zero
    }

    func testAdd() {
        let lhs = CXFloat32x3Make(1, 2, 3)
        let rhs = CXFloat32x3Make(4, 3, 2)
        let sum = CXFloat32x3Add(lhs, rhs)

        XCTAssertEqual(CXFloat32x3GetElement(sum, 0), 5)
        XCTAssertEqual(CXFloat32x3GetElement(sum, 1), 5)
        XCTAssertEqual(CXFloat32x3GetElement(sum, 2), 5)
        XCTAssertEqual(CXFloat32x3GetElement(sum, 3), 0) // Make sure the unused value remains zero
    }

    func testSubtract() {
        let lhs = CXFloat32x3Make(1, 2, 3)
        let rhs = CXFloat32x3Make(4, 3, 2)
        let sum = CXFloat32x3Subtract(lhs, rhs)

        XCTAssertEqual(CXFloat32x3GetElement(sum, 0), -3)
        XCTAssertEqual(CXFloat32x3GetElement(sum, 1), -1)
        XCTAssertEqual(CXFloat32x3GetElement(sum, 2), 1)
        XCTAssertEqual(CXFloat32x3GetElement(sum, 3), 0) // Make sure the unused value remains zero

    }

    func testNegate() {
        let normal = CXFloat32x3Make(-1, 0, 3)
        let negate = CXFloat32x3Negate(normal)

        XCTAssertEqual(CXFloat32x3GetElement(negate, 0), 1)
        XCTAssertEqual(CXFloat32x3GetElement(negate, 1), 0)
        XCTAssertEqual(CXFloat32x3GetElement(negate, 2), -3)
        XCTAssertEqual(CXFloat32x3GetElement(negate, 3), 0) // Make sure the unused value remains zero
    }

    func testMultiply() {
        let lhs = CXFloat32x3Make(1, -2, -3)
        let rhs = CXFloat32x3Make(4, -3, 2)
        let product = CXFloat32x3Multiply(lhs, rhs)

        XCTAssertEqual(CXFloat32x3GetElement(product, 0), 4)
        XCTAssertEqual(CXFloat32x3GetElement(product, 1), 6)
        XCTAssertEqual(CXFloat32x3GetElement(product, 2), -6)
        XCTAssertEqual(CXFloat32x3GetElement(product, 3), 0) // Make sure the unused value remains zero
    }

    func testEqual() {
        let lhs = CXFloat32x3Make(1, -2, -3)
        let rhs = CXFloat32x3Make(1, 2, -3)
        let result = CXFloat32x3Equal(lhs, rhs)

        XCTAssertNotEqual(CXFloat32x3GetElement(result, 0), 0)
        XCTAssertEqual(CXFloat32x3GetElement(result, 1), 0)
        XCTAssertNotEqual(CXFloat32x3GetElement(result, 2), 0)
    }

    static var allTests = [
        ("testMake", testMake),
        ("testMakeRepeatingValues", testMakeRepeatingValues),
        ("testZero", testZero),
        ("testGetter", testGetter),
        ("testSetter", testSetter),
        ("testAdd", testAdd),
        ("testSubtract", testSubtract),
        ("testNegate", testNegate),
        ("testMultiply", testMultiply),
        ("testEqual", testEqual)
    ]
}
