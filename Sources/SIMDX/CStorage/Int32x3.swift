import Foundation
import CSIMDX

public struct Int32x3: RawStorage3, FixedWidthIntegerRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 3

    // MARK: Raw Value Access

    public var rawValue: CXInt32x3

    @inlinable public subscript(index: Int32) -> Int32 {
        @inlinable set { CXInt32x3SetElement(&rawValue, index, newValue) }
        @inlinable get { CXInt32x3GetElement(rawValue, index) }
    }

    @inlinable public init(rawValue: CXInt32x3) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Int32x3 {

    @inlinable public init(_ repeatingElement: Int32) {
        self.init(rawValue: CXInt32x3MakeRepeatingElement(repeatingElement))
    }

    @inlinable public init(_ index0: Int32, _ index1: Int32, _ index2: Int32) {
        self.init(rawValue: CXInt32x3Make(index0, index1, index2))
    }

    @inlinable public init(_ array: [Int32]) {
        var array = array
        self.init(rawValue: CXInt32x3MakeLoad(&array))
    }

    @inlinable public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Int32 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension Int32x3 {

    @inlinable public static var zero: Int32x3 { .init(rawValue: CXInt32x3MakeZero()) }

    @inlinable public var magnitude: Int32x3 { .init(rawValue: CXInt32x3Absolute(rawValue)) }

    // MARK: Additive

    @inlinable public static func + (lhs: Int32x3, rhs: Int32x3) -> Int32x3 {
        .init(rawValue: CXInt32x3Add(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func - (lhs: Int32x3, rhs: Int32x3) -> Int32x3  {
        .init(rawValue: CXInt32x3Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static prefix func - (operand: Int32x3) -> Int32x3  {
        .init(rawValue: CXInt32x3Negate(operand.rawValue))
    }

    @inlinable public mutating func negate() {
        rawValue = CXInt32x3Negate(rawValue)
    }

    // MARK: Multiplicative

    @inlinable public static func * (lhs: Int32x3, rhs: Int32x3) -> Int32x3  {
        .init(rawValue: CXInt32x3Multiply(lhs.rawValue, rhs.rawValue))
    }
}
