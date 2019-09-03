import Foundation
import CSIMDX

public struct Int32x4: RawStorage4, FixedWidthIntegerRawStorage, SignedIntegerRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 4

    // MARK: Raw Value Access

    public var rawValue: CXInt32x4

    @inlinable public subscript(index: Int32) -> Int32 {
        @inlinable set { CXInt32x4SetElement(&rawValue, index, newValue) }
        @inlinable get { CXInt32x4GetElement(rawValue, index) }
    }

    @inlinable public init(rawValue: CXInt32x4) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Int32x4 {

    @inlinable public init(_ repeatingElement: Int32) {
        self.init(rawValue: CXInt32x4MakeRepeatingElement(repeatingElement))
    }

    @inlinable public init(_ index0: Int32, _ index1: Int32, _ index2: Int32, _ index3: Int32) {
        self.init(rawValue: CXInt32x4Make(index0, index1, index2, index3))
    }

    @inlinable public init(_ array: [Int32]) {
        var array = array
        self.init(rawValue: CXInt32x4MakeLoad(&array))
    }

    @inlinable public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Int32 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension Int32x4 {

    @inlinable public static var zero: Int32x4 { .init(rawValue: CXInt32x4MakeZero()) }

    @inlinable public var magnitude: UInt32x4 { .init(rawValue: CXInt32x4Absolute(rawValue)) }

    // MARK: Additive

    @inlinable public static func + (lhs: Int32x4, rhs: Int32x4) -> Int32x4 {
        .init(rawValue: CXInt32x4Add(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func - (lhs: Int32x4, rhs: Int32x4) -> Int32x4  {
        .init(rawValue: CXInt32x4Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static prefix func - (operand: Int32x4) -> Int32x4  {
        .init(rawValue: CXInt32x4Negate(operand.rawValue))
    }

    @inlinable public mutating func negate() {
        rawValue = CXInt32x4Negate(rawValue)
    }

    // MARK: Multiplicative

    @inlinable public static func * (lhs: Int32x4, rhs: Int32x4) -> Int32x4  {
        .init(rawValue: CXInt32x4Multiply(lhs.rawValue, rhs.rawValue))
    }
}
