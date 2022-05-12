import XCTest
import CSIMDX

final class CFloat32x2Tests: XCTestCase {

    // MARK: Make

    func testMake() {
        let storage = CFloat32x2Make(1, 2)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 1)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 2)
    }

    func testMakeLoad() {
        var array: [Float32] = [1, 2]
        let storage = CFloat32x2MakeLoad(&array)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 1)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 2)
    }

    func testMakeRepeatingElement() {
        let storage = CFloat32x2MakeRepeatingElement(3)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 3)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 3)
    }

    func testMakeZero() {
        let storage = CFloat32x2MakeZero()

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 0)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 0)
    }

    // MARK: Access

    func testGetElement() {
        let storage = CFloat32x2Make(1, 2)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 1)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 2)
    }

    func testSetElement() {
        var storage = CFloat32x2Make(1, 2)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 1)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 2)

        CFloat32x2SetElement(&storage, 0, 5)
        CFloat32x2SetElement(&storage, 1, 6)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 5)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 6)
    }

    // MARK: Conversion

    func testConvertFromFloat64x2() {
        let fromStorage = CXFloat64x2Make(2.11199999999999, 1.54321987654321)
        let storage = CFloat32x2FromCXFloat64x2(fromStorage)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 2.11199999999999)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 1.54321987654321)
    }

    func testConvertFromInt32x2() {
        let fromStorage = CXInt32x2Make(-2, 1)
        let storage = CFloat32x2FromCXInt32x2(fromStorage)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), -2.00000000000000)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 1.00000000000000)
    }

    func testConvertFromUInt32x2() {
        let fromStorage = CXUInt32x2Make(2, 5)
        let storage = CFloat32x2FromCXUInt32x2(fromStorage)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 2)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 5)
    }

    func testConvertFromInt64x2() {
        let fromStorage = CXInt64x2Make(-34, 12)
        let storage = CFloat32x2FromCXInt64x2(fromStorage)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), -34)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 12)
    }

    func testConvertFromUInt64x2() {
        let fromStorage = CXUInt64x2Make(34, 12)
        let storage = CFloat32x2FromCXUInt64x2(fromStorage)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 34)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 12)
    }

    // MARK: Comparison

    func testMinimum() {
        let lhs = CFloat32x2Make(34, 12)
        let rhs = CFloat32x2Make(-34, 24)
        let storage = CFloat32x2Minimum(lhs, rhs)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), -34)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 12)
    }

    func testMaximum() {
        let lhs = CFloat32x2Make(34, 12)
        let rhs = CFloat32x2Make(-34, 24)
        let storage = CFloat32x2Maximum(lhs, rhs)

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 34)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 24)
    }

    // MARK: Arithmetic

    func testNegate() {
        let normal = CFloat32x2Make(-1, 3)
        let negate = CFloat32x2Negate(normal)

        XCTAssertEqual(CFloat32x2GetElement(negate, 0), 1)
        XCTAssertEqual(CFloat32x2GetElement(negate, 1), -3)
    }

    func testAbsolute() {
        let normal = CFloat32x2Make(-1, 3)
        let absolute = CFloat32x2Absolute(normal)

        XCTAssertEqual(CFloat32x2GetElement(absolute, 0), 1)
        XCTAssertEqual(CFloat32x2GetElement(absolute, 1), 3)
    }

    func testAdd() {
        let lhs = CFloat32x2Make(1, 2)
        let rhs = CFloat32x2Make(4, 3)
        let sum = CFloat32x2Add(lhs, rhs)

        XCTAssertEqual(CFloat32x2GetElement(sum, 0), 5)
        XCTAssertEqual(CFloat32x2GetElement(sum, 1), 5)
    }

    func testSubtract() {
        let lhs = CFloat32x2Make(1, 2)
        let rhs = CFloat32x2Make(4, 3)
        let sum = CFloat32x2Subtract(lhs, rhs)

        XCTAssertEqual(CFloat32x2GetElement(sum, 0), -3)
        XCTAssertEqual(CFloat32x2GetElement(sum, 1), -1)

    }

    func testMultiply() {
        let lhs = CFloat32x2Make(1, -2)
        let rhs = CFloat32x2Make(-4, -3)
        let product = CFloat32x2Multiply(lhs, rhs)

        XCTAssertEqual(CFloat32x2GetElement(product, 0), -4)
        XCTAssertEqual(CFloat32x2GetElement(product, 1), 6)
    }

    func testDivide() {
        let lhs = CFloat32x2Make(1, -6)
        let rhs = CFloat32x2Make(-4, -3)
        let product = CFloat32x2Divide(lhs, rhs)

        XCTAssertEqual(CFloat32x2GetElement(product, 0), -0.25)
        XCTAssertEqual(CFloat32x2GetElement(product, 1), 2)
    }

    func testSquareRoot() {
        let storage =  CFloat32x2SquareRoot(CFloat32x2Make(25, 144))

        XCTAssertEqual(CFloat32x2GetElement(storage, 0), 5)
        XCTAssertEqual(CFloat32x2GetElement(storage, 1), 12)
    }
}
