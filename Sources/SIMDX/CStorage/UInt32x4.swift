import Foundation
import CSIMDX

public struct UInt32x4: RawStorage4, FixedWidthIntegerRawStorage, UnsignedIntegerRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 4

    // MARK: Raw Value Access

    public var rawValue: CXUInt32x4

    @inlinable public subscript(index: Int32) -> UInt32 {
        @inlinable set { CXUInt32x4SetElement(&rawValue, index, newValue) }
        @inlinable get { CXUInt32x4GetElement(rawValue, index) }
    }

    @inlinable public init(rawValue: CXUInt32x4) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension UInt32x4 {

    @inlinable public init(_ repeatingElement: UInt32) {
        self.init(rawValue: CXUInt32x4MakeRepeatingElement(repeatingElement))
    }

    @inlinable public init(_ index0: UInt32, _ index1: UInt32, _ index2: UInt32, _ index3: UInt32) {
        self.init(rawValue: CXUInt32x4Make(index0, index1, index2, index3))
    }

    @inlinable public init(_ array: [UInt32]) {
        var array = array
        self.init(rawValue: CXUInt32x4MakeLoad(&array))
    }

    @inlinable public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == UInt32 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension UInt32x4 {

    @inlinable public static var zero: UInt32x4 { .init(rawValue: CXUInt32x4MakeZero()) }

    @inlinable public var magnitude: UInt32x4 { .init(rawValue: CXUInt32x4Absolute(rawValue)) }

    // MARK: Additive

    @inlinable public static func + (lhs: UInt32x4, rhs: UInt32x4) -> UInt32x4 {
        .init(rawValue: CXUInt32x4Add(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func - (lhs: UInt32x4, rhs: UInt32x4) -> UInt32x4  {
        .init(rawValue: CXUInt32x4Subtract(lhs.rawValue, rhs.rawValue))
    }

    // MARK: Multiplicative

    @inlinable public static func * (lhs: UInt32x4, rhs: UInt32x4) -> UInt32x4  {
        .init(rawValue: CXUInt32x4Multiply(lhs.rawValue, rhs.rawValue))
    }
}
