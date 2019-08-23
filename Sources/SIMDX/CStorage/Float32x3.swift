import Foundation
import CSIMDX

public struct Float32x3: RawStorage3, FloatingPointRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 4

    // MARK: Raw Value Access

    public var rawValue: CXFloat32x3

    @inlinable public subscript(index: Int32) -> Float32 {
        @inlinable set { CXFloat32x3SetElement(&rawValue, index, newValue) }
        @inlinable get { CXFloat32x3GetElement(rawValue, index) }
    }

    @inlinable public init(rawValue: CXFloat32x3) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Float32x3 {

    @inlinable public init(_ repeatingElement: Float32) {
        self.init(rawValue: CXFloat32x3MakeRepeatingElement(repeatingElement))
    }

    @inlinable public init(_ index0: Float32, _ index1: Float32, _ index2: Float32) {
        self.init(rawValue: CXFloat32x3Make(index0, index1, index2))
    }

    @inlinable public init(_ array: [Float32]) {
        var array = array
        self.init(rawValue: CXFloat32x3MakeLoad(&array))
    }

    @inlinable public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Float32 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension Float32x3 {

    @inlinable public static var zero: Float32x3 { .init(rawValue: CXFloat32x3MakeZero()) }

    @inlinable public var magnitude: Float32x3 { .init(rawValue: CXFloat32x3Absolute(rawValue)) }

    // MARK: Additive

    @inlinable public static func + (lhs: Float32x3, rhs: Float32x3) -> Float32x3 {
        .init(rawValue: CXFloat32x3Add(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func - (lhs: Float32x3, rhs: Float32x3) -> Float32x3  {
        .init(rawValue: CXFloat32x3Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static prefix func - (operand: Float32x3) -> Float32x3  {
        .init(rawValue: CXFloat32x3Negate(operand.rawValue))
    }

    @inlinable public mutating func negate() {
        rawValue = CXFloat32x3Negate(rawValue)
    }

    // MARK: Multiplicative

    @inlinable public static func * (lhs: Float32x3, rhs: Float32x3) -> Float32x3  {
        .init(rawValue: CXFloat32x3Multiply(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func / (lhs: Float32x3, rhs: Float32x3) -> Float32x3  {
        .init(rawValue: CXFloat32x3Divide(lhs.rawValue, rhs.rawValue))
    }
}
