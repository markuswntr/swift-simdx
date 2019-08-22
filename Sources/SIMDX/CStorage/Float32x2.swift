import Foundation
import CSIMDX

public struct Float32x2: RawStorage2, FloatingPointRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 2

    // MARK: Raw Value Access

    public var rawValue: CXFloat32x2

    @inlinable public subscript(index: Int32) -> Float32 {
        @inlinable set { CXFloat32x2SetElement(&rawValue, index, newValue) }
        @inlinable get { CXFloat32x2GetElement(rawValue, index) }
    }

    @inlinable public init(rawValue: CXFloat32x2) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Float32x2 {

    @inlinable public init(_ repeatingElement: Float32) {
        self.init(rawValue: CXFloat32x2MakeRepeatingElement(repeatingElement))
    }

    @inlinable public init(_ index0: Float32, _ index1: Float32) {
        self.init(rawValue: CXFloat32x2Make(index0, index1))
    }

    @inlinable public init(_ array: [Float32]) {
        var array = array
        self.init(rawValue: CXFloat32x2Load(&array))
    }

    @inlinable public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Float32 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension Float32x2 {

    @inlinable public static var zero: Float32x2 { .init(rawValue: CXFloat32x2MakeZero()) }

    @inlinable public var magnitude: Float32x2 { .init(rawValue: CXFloat32x2Absolute(rawValue)) }

    // MARK: Additive

    @inlinable public static func + (lhs: Float32x2, rhs: Float32x2) -> Float32x2 {
        .init(rawValue: CXFloat32x2Add(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func - (lhs: Float32x2, rhs: Float32x2) -> Float32x2  {
        .init(rawValue: CXFloat32x2Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static prefix func - (operand: Float32x2) -> Float32x2  {
        .init(rawValue: CXFloat32x2Negate(operand.rawValue))
    }

    @inlinable public mutating func negate() {
        rawValue = CXFloat32x2Negate(rawValue)
    }

    // MARK: Multiplicative

    @inlinable public static func * (lhs: Float32x2, rhs: Float32x2) -> Float32x2  {
        .init(rawValue: CXFloat32x2Multiply(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func / (lhs: Float32x2, rhs: Float32x2) -> Float32x2  {
        .init(rawValue: CXFloat32x2Divide(lhs.rawValue, rhs.rawValue))
    }
}
