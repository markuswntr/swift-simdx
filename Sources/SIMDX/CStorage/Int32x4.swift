import Foundation
import CSIMDX

public struct Int32x4: RawStorage4, FixedWidthIntegerRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 4

    // MARK: Raw Value Access

    @inline(__always)
    public private(set) var rawValue: CXInt32x4

    @inline(__always)
    public subscript(index: Int32) -> Int32 {
        @inline(__always) set {
            CXInt32x4SetElement(&rawValue, index, newValue)
        }
        @inline(__always) get {
            CXInt32x4GetElement(rawValue, index)
        }
    }

    @inline(__always)
    public init(rawValue: CXInt32x4) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Int32x4 {

    @inline(__always)
    public init(_ repeatingElement: Int32) {
        self.init(rawValue: CXInt32x4MakeRepeatingElement(repeatingElement))
    }

    @inline(__always)
    public init(_ index0: Int32, _ index1: Int32, _ index2: Int32, _ index3: Int32) {
        self.init(rawValue: CXInt32x4Make(index0, index1, index2, index3))
    }

    @inline(__always)
    public init(_ array: [Int32]) {
        var array = array
        self.init(rawValue: CXInt32x4Load(&array))
    }

    @inline(__always)
    public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Int32 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension Int32x4 {

    @inline(__always)
    public static var zero: Int32x4 = .init(rawValue: CXInt32x4MakeZero())

    @inline(__always)
    public var magnitude: Int32x4 { .init(rawValue: CXInt32x4Absolute(rawValue)) }

    // MARK: Additive

    @inline(__always)
    public static func + (lhs: Int32x4, rhs: Int32x4) -> Int32x4 {
        return .init(rawValue: CXInt32x4Add(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static func - (lhs: Int32x4, rhs: Int32x4) -> Int32x4  {
        return .init(rawValue: CXInt32x4Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static prefix func - (operant: Int32x4) -> Int32x4  {
        return .init(rawValue: CXInt32x4Negate(operant.rawValue))
    }

    public mutating func negate() {
        rawValue = CXInt32x4Negate(rawValue)
    }

    // MARK: Multiplicative

    @inline(__always)
    public static func * (lhs: Int32x4, rhs: Int32x4) -> Int32x4  {
        return .init(rawValue: CXInt32x4Multiply(lhs.rawValue, rhs.rawValue))
    }
}
