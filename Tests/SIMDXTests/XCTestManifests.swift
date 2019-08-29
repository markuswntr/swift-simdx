import XCTest

#if !canImport(ObjectiveC)
public func allTests() -> [XCTestCaseEntry] {
    return [
        testCase(SIMDX2Tests.allTests),
        testCase(SIMDX3Tests.allTests),
        testCase(SIMDX4Tests.allTests)
    ]
}
#endif
