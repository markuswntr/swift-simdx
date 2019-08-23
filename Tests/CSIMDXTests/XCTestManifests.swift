import XCTest

#if !canImport(ObjectiveC)
public func allTests() -> [XCTestCaseEntry] {
    return [
        testCase(CXFloat32x2Tests.allTests),
        testCase(CXFloat32x3Tests.allTests),
        testCase(CXFloat32x4Tests.allTests),
        testCase(CXFloat64x2Tests.allTests),
        testCase(CXInt32x2Tests.allTests),
        testCase(CXInt32x3Tests.allTests),
        testCase(CXInt32x4Tests.allTests),
        testCase(CXInt64x2Tests.allTests)
    ]
}
#endif
