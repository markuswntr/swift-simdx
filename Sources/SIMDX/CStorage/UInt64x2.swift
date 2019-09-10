import Foundation
import CSIMDX

public struct UInt64x2: RawStorage2, FixedWidthIntegerRawStorage, UnsignedIntegerRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 2

    // MARK: Raw Value Access

    public var rawValue: CXUInt64x2

    @inlinable public subscript(index: Int32) -> UInt64 {
        @inlinable set { CXUInt64x2SetElement(&rawValue, index, newValue) }
        @inlinable get { CXUInt64x2GetElement(rawValue, index) }
    }

    @inlinable public init(rawValue: CXUInt64x2) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension UInt64x2 {

    @inlinable public init(_ repeatingElement: UInt64) {
        self.init(rawValue: CXUInt64x2MakeRepeatingElement(repeatingElement))
    }

    @inlinable public init(_ index0: UInt64, _ index1: UInt64) {
        self.init(rawValue: CXUInt64x2Make(index0, index1))
    }

    @inlinable public init(_ array: [UInt64]) {
        var array = array
        self.init(rawValue: CXUInt64x2MakeLoad(&array))
    }

    @inlinable public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == UInt64 {
        self.init(Array(sequence))
    }
}

// MARK: - Bitwise
extension UInt64x2 {

    @inlinable public  prefix static func ~ (operand: UInt64x2) -> UInt64x2 {
        return .init(rawValue: CXUInt64x2BitwiseNot(operand.rawValue))
    }

    @inlinable public static func & (lhs: UInt64x2, rhs: UInt64x2) -> UInt64x2 {
        return .init(rawValue: CXUInt64x2BitwiseAnd(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func | (lhs: UInt64x2, rhs: UInt64x2) -> UInt64x2 {
        return .init(rawValue: CXUInt64x2BitwiseOr(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func ^ (lhs: UInt64x2, rhs: UInt64x2) -> UInt64x2 {
        return .init(rawValue: CXUInt64x2BitwiseExclusiveOr(lhs.rawValue, rhs.rawValue))
    }

    // MARK: Shifting

    @inlinable public static func >> <RHS>(lhs: UInt64x2, rhs: RHS) -> UInt64x2 where RHS: BinaryInteger {
        return .init(rawValue: CXUInt64x2ShiftLeft(lhs.rawValue, UInt64(rhs)))
    }

    @inlinable public static func << <RHS>(lhs: UInt64x2, rhs: RHS) -> UInt64x2 where RHS: BinaryInteger {
        return .init(rawValue: CXUInt64x2ShiftRight(lhs.rawValue, UInt64(rhs)))
    }
}

// MARK: - Arithmetics
extension UInt64x2 {

    @inlinable public static var zero: UInt64x2 { .init(rawValue: CXUInt64x2MakeZero()) }

    @inlinable public var magnitude: UInt64x2 { .init(rawValue: CXUInt64x2Absolute(rawValue)) }

    // MARK: Additive

    @inlinable public static func + (lhs: UInt64x2, rhs: UInt64x2) -> UInt64x2 {
        .init(rawValue: CXUInt64x2Add(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func - (lhs: UInt64x2, rhs: UInt64x2) -> UInt64x2  {
        .init(rawValue: CXUInt64x2Subtract(lhs.rawValue, rhs.rawValue))
    }

    // MARK: Multiplicative

    @inlinable public static func * (lhs: UInt64x2, rhs: UInt64x2) -> UInt64x2  {
        .init(rawValue: CXUInt64x2Multiply(lhs.rawValue, rhs.rawValue))
    }
}
