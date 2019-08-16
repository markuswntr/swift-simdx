import XCTest
import CSIMDXTests
import SIMDXTests

var tests: [XCTestCaseEntry] = []
tests += CSIMDXTests.allTests()
tests += SIMDXTests.allTests()
XCTMain(tests)
