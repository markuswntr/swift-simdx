import XCTest
import SIMDX

final class SIMDX2Tests: XCTestCase {

    func testExample() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct
        // results.
        let storage = SIMDX2<Float>(index0: 1, index1: 2)
        XCTAssertEqual(storage[.index0], 1)
        XCTAssertEqual(storage[.index1], 2)
    }

    static var allTests = [
        ("testExample", testExample),
    ]
}
