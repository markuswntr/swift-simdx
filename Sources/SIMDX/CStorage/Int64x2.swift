import Foundation
import CSIMDX

public struct Int32x2: RawStorage2, FixedWidthIntegerRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 2

    // MARK: Raw Value Access

    @inline(__always)
    public fileprivate(set) var rawValue: CXInt32x2

    @inline(__always)
    public subscript(index: Int32) -> Int32 {
        @inline(__always) set {
            CXInt32x2SetElement(&rawValue, index, newValue)
        }
        @inline(__always) get {
            CXInt32x2GetElement(rawValue, index)
        }
    }

    @inline(__always)
    public init(rawValue: CXInt32x2) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Int32x2 {

    @inline(__always)
    public init(_ repeatingElement: Int32) {
        self.init(rawValue: CXInt32x2MakeRepeatingElement(repeatingElement))
    }

    @inline(__always)
    public init(_ index0: Int32, _ index1: Int32) {
        self.init(rawValue: CXInt32x2Make(index0, index1))
    }

    @inline(__always)
    public init(_ array: [Int32]) {
        var array = array
        self.init(rawValue: CXInt32x2Load(&array))
    }

    @inline(__always)
    public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Int32 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension Int32x2 {

    @inline(__always)
    public static var zero: Int32x2 = .init(rawValue: CXInt32x2MakeZero())

    @inline(__always)
    public var magnitude: Int32x2 { .init(rawValue: CXInt32x2Absolute(rawValue)) }

    // MARK: Additive

    @inline(__always)
    public static func + (lhs: Int32x2, rhs: Int32x2) -> Int32x2 {
        return .init(rawValue: CXInt32x2Add(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static func - (lhs: Int32x2, rhs: Int32x2) -> Int32x2  {
        return .init(rawValue: CXInt32x2Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static prefix func - (operand: Int32x2) -> Int32x2  {
        return .init(rawValue: CXInt32x2Negate(operand.rawValue))
    }

    public mutating func negate() {
        rawValue = CXInt32x2Negate(rawValue)
    }

    // MARK: Multiplicative

    @inline(__always)
    public static func * (lhs: Int32x2, rhs: Int32x2) -> Int32x2  {
        return .init(rawValue: CXInt32x2Multiply(lhs.rawValue, rhs.rawValue))
    }
}
