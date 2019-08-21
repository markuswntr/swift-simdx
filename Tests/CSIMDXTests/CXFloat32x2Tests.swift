import XCTest
@testable import CSIMDX

final class CXFloat32x2Tests: XCTestCase {

    func testMake() {
        let collection = CXFloat32x2Make(1, 2)

        XCTAssertEqual(CXFloat32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXFloat32x2GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testLoad() {
        var array: [Float32] = [1, 2]
        let collection = CXFloat32x2Load(&array)

        XCTAssertEqual(CXFloat32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXFloat32x2GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testMakeRepeatingValues() {
        let collection = CXFloat32x2MakeRepeatingElement(3)

        XCTAssertEqual(CXFloat32x2GetElement(collection, 0), 3)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 1), 3)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXFloat32x2GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testZero() {
        let collection = CXFloat32x2MakeZero()

        XCTAssertEqual(CXFloat32x2GetElement(collection, 0), 0)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 1), 0)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXFloat32x2GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testGetter() {
        let collection = CXFloat32x2Make(1, 2)

        XCTAssertEqual(CXFloat32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXFloat32x2GetElement(collection, 3), 0) // Make sure the unused value is zero
    }

    func testSetter() {
        var collection = CXFloat32x2Make(1, 2)

        XCTAssertEqual(CXFloat32x2GetElement(collection, 0), 1)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 1), 2)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 2), 0) // Make sure the unused value is zero
        XCTAssertEqual(CXFloat32x2GetElement(collection, 3), 0) // Make sure the unused value is zero

        CXFloat32x2SetElement(&collection, 0, 5)
        CXFloat32x2SetElement(&collection, 1, 6)

        XCTAssertEqual(CXFloat32x2GetElement(collection, 0), 5)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 1), 6)
        XCTAssertEqual(CXFloat32x2GetElement(collection, 2), 0) // Make sure the unused value remains zero
        XCTAssertEqual(CXFloat32x2GetElement(collection, 3), 0) // Make sure the unused value remains zero
    }

    func testAdd() {
        let lhs = CXFloat32x2Make(1, 2)
        let rhs = CXFloat32x2Make(4, 3)
        let sum = CXFloat32x2Add(lhs, rhs)

        XCTAssertEqual(CXFloat32x2GetElement(sum, 0), 5)
        XCTAssertEqual(CXFloat32x2GetElement(sum, 1), 5)
        XCTAssertEqual(CXFloat32x2GetElement(sum, 2), 0) // Make sure the unused value remains zero
        XCTAssertEqual(CXFloat32x2GetElement(sum, 3), 0) // Make sure the unused value remains zero
    }

    func testSubtract() {
        let lhs = CXFloat32x2Make(1, 2)
        let rhs = CXFloat32x2Make(4, 3)
        let sum = CXFloat32x2Subtract(lhs, rhs)

        XCTAssertEqual(CXFloat32x2GetElement(sum, 0), -3)
        XCTAssertEqual(CXFloat32x2GetElement(sum, 1), -1)
        XCTAssertEqual(CXFloat32x2GetElement(sum, 2), 0) // Make sure the unused value remains zero
        XCTAssertEqual(CXFloat32x2GetElement(sum, 3), 0) // Make sure the unused value remains zero

    }

    func testNegate() {
        let normal = CXFloat32x2Make(-1, 3)
        let negate = CXFloat32x2Negate(normal)

        XCTAssertEqual(CXFloat32x2GetElement(negate, 0), 1)
        XCTAssertEqual(CXFloat32x2GetElement(negate, 1), -3)
        XCTAssertEqual(CXFloat32x2GetElement(negate, 2), 0) // Make sure the unused value remains zero
        XCTAssertEqual(CXFloat32x2GetElement(negate, 3), 0) // Make sure the unused value remains zero
    }

    func testMultiply() {
        let lhs = CXFloat32x2Make(1, -2)
        let rhs = CXFloat32x2Make(-4, -3)
        let product = CXFloat32x2Multiply(lhs, rhs)

        XCTAssertEqual(CXFloat32x2GetElement(product, 0), -4)
        XCTAssertEqual(CXFloat32x2GetElement(product, 1), 6)
        XCTAssertEqual(CXFloat32x2GetElement(product, 2), 0) // Make sure the unused value remains zero
        XCTAssertEqual(CXFloat32x2GetElement(product, 3), 0) // Make sure the unused value remains zero
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
        ("testMultiply", testMultiply)
    ]
}
