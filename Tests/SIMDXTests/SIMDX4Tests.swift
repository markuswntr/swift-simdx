import XCTest
@testable import SIMDX

final class SIMDXTests: XCTestCase {
    func testExample() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct
        // results.
        let storage = SIMDX4<Float>(index0: 1, index1: 2, index2: 3, index3: 4)
        XCTAssertEqual(storage[.index0], 1)
        XCTAssertEqual(storage[.index1], 2)
        XCTAssertEqual(storage[.index2], 3)
        XCTAssertEqual(storage[.index3], 4)
    }

    static var allTests = [
        ("testExample", testExample),
    ]
}
