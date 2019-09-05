import Foundation
import CSIMDX

public struct UInt32x2: RawStorage2, FixedWidthIntegerRawStorage, UnsignedIntegerRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 2

    // MARK: Raw Value Access

    public var rawValue: CXUInt32x2

    @inlinable public subscript(index: Int32) -> UInt32 {
        @inlinable set { CXUInt32x2SetElement(&rawValue, index, newValue) }
        @inlinable get { CXUInt32x2GetElement(rawValue, index) }
    }

    @inlinable public init(rawValue: CXUInt32x2) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension UInt32x2 {

    @inlinable public init(_ repeatingElement: UInt32) {
        self.init(rawValue: CXUInt32x2MakeRepeatingElement(repeatingElement))
    }

    @inlinable public init(_ index0: UInt32, _ index1: UInt32) {
        self.init(rawValue: CXUInt32x2Make(index0, index1))
    }

    @inlinable public init(_ array: [UInt32]) {
        var array = array
        self.init(rawValue: CXUInt32x2MakeLoad(&array))
    }

    @inlinable public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == UInt32 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension UInt32x2 {

    @inlinable public static var zero: UInt32x2 { .init(rawValue: CXUInt32x2MakeZero()) }

    @inlinable public var magnitude: UInt32x2 { .init(rawValue: CXUInt32x2Absolute(rawValue)) }

    // MARK: Additive

    @inlinable public static func + (lhs: UInt32x2, rhs: UInt32x2) -> UInt32x2 {
        .init(rawValue: CXUInt32x2Add(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func - (lhs: UInt32x2, rhs: UInt32x2) -> UInt32x2  {
        .init(rawValue: CXUInt32x2Subtract(lhs.rawValue, rhs.rawValue))
    }

    // MARK: Multiplicative

    @inlinable public static func * (lhs: UInt32x2, rhs: UInt32x2) -> UInt32x2  {
        .init(rawValue: CXUInt32x2Multiply(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func / (lhs: UInt32x2, rhs: UInt32x2) -> UInt32x2 {
        return .init(rawValue: CXUInt32x2Divide(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func % (lhs: UInt32x2, rhs: UInt32x2) -> UInt32x2 {
        return .init(rawValue: CXUInt32x2Modulo(lhs.rawValue, rhs.rawValue))
    }

    // MARK: Logical

    @inlinable public  prefix static func ~ (operand: UInt32x2) -> UInt32x2 {
        return .init(rawValue: CXUInt32x2BitwiseNot(operand.rawValue))
    }

    @inlinable public static func & (lhs: UInt32x2, rhs: UInt32x2) -> UInt32x2 {
        return .init(rawValue: CXUInt32x2BitwiseAnd(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func | (lhs: UInt32x2, rhs: UInt32x2) -> UInt32x2 {
        return .init(rawValue: CXUInt32x2BitwiseOr(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func ^ (lhs: UInt32x2, rhs: UInt32x2) -> UInt32x2 {
        return .init(rawValue: CXUInt32x2BitwiseExclusiveOr(lhs.rawValue, rhs.rawValue))
    }

    // MARK: Shifting

    @inlinable public static func >> <RHS>(lhs: UInt32x2, rhs: RHS) -> UInt32x2 where RHS: BinaryInteger {
        return .init(rawValue: CXUInt32x2ShiftLeft(lhs.rawValue, UInt32(rhs)))
    }

    @inlinable public static func << <RHS>(lhs: UInt32x2, rhs: RHS) -> UInt32x2 where RHS: BinaryInteger {
        return .init(rawValue: CXUInt32x2ShiftRight(lhs.rawValue, UInt32(rhs)))
    }
}
