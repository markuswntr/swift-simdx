import XCTest
import SIMDX

final class SIMDX3Tests: XCTestCase {

    func testExample() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct
        // results.
        let storage = SIMDX3<Float>(index0: 1, index1: 2, index2: 3)
        XCTAssertEqual(storage[.index0], 1)
        XCTAssertEqual(storage[.index1], 2)
        XCTAssertEqual(storage[.index2], 3)
    }

    static var allTests = [
        ("testExample", testExample),
    ]
}
