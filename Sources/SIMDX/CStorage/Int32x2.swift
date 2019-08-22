import Foundation
import CSIMDX

public struct Int64x2: RawStorage2, FixedWidthIntegerRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 2

    // MARK: Raw Value Access

    @inline(__always)
    public fileprivate(set) var rawValue: CXInt64x2

    @inline(__always)
    public subscript(index: Int32) -> Int64 {
        @inline(__always) set {
            CXInt64x2SetElement(&rawValue, index, newValue)
        }
        @inline(__always) get {
            CXInt64x2GetElement(rawValue, index)
        }
    }

    @inline(__always)
    public init(rawValue: CXInt64x2) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Int64x2 {

    @inline(__always)
    public init(_ repeatingElement: Int64) {
        self.init(rawValue: CXInt64x2MakeRepeatingElement(repeatingElement))
    }

    @inline(__always)
    public init(_ index0: Int64, _ index1: Int64) {
        self.init(rawValue: CXInt64x2Make(index0, index1))
    }

    @inline(__always)
    public init(_ array: [Int64]) {
        var array = array
        self.init(rawValue: CXInt64x2Load(&array))
    }

    @inline(__always)
    public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Int64 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension Int64x2 {

    @inline(__always)
    public static var zero: Int64x2 = .init(rawValue: CXInt64x2MakeZero())

    @inline(__always)
    public var magnitude: Int64x2 { .init(rawValue: CXInt64x2Absolute(rawValue)) }

    // MARK: Additive

    @inline(__always)
    public static func + (lhs: Int64x2, rhs: Int64x2) -> Int64x2 {
        return .init(rawValue: CXInt64x2Add(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static func - (lhs: Int64x2, rhs: Int64x2) -> Int64x2  {
        return .init(rawValue: CXInt64x2Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static prefix func - (operand: Int64x2) -> Int64x2  {
        return .init(rawValue: CXInt64x2Negate(operand.rawValue))
    }

    public mutating func negate() {
        rawValue = CXInt64x2Negate(rawValue)
    }

    // MARK: Multiplicative

    @inline(__always)
    public static func * (lhs: Int64x2, rhs: Int64x2) -> Int64x2  {
        return .init(rawValue: CXInt64x2Multiply(lhs.rawValue, rhs.rawValue))
    }
}
