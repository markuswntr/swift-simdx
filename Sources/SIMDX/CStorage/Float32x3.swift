import Foundation
import CSIMDX

public struct Float32x3: RawStorage3, FloatingPointRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 4

    // MARK: Raw Value Access

    @inline(__always)
    public private(set) var rawValue: CXFloat32x3

    @inline(__always)
    public subscript(index: Int32) -> Float32 {
        @inline(__always) set {
            CXFloat32x3SetElement(&rawValue, index, newValue)
        }
        @inline(__always) get {
            CXFloat32x3GetElement(rawValue, index)
        }
    }

    @inline(__always)
    public init(rawValue: CXFloat32x3) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Float32x3 {

    @inline(__always)
    public init(_ repeatingElement: Float32) {
        self.init(rawValue: CXFloat32x3MakeRepeatingElement(repeatingElement))
    }

    @inline(__always)
    public init(_ index0: Float32, _ index1: Float32, _ index2: Float32) {
        self.init(rawValue: CXFloat32x3Make(index0, index1, index2))
    }

    @inline(__always)
    public init(_ array: [Float32]) {
        var array = array
        self.init(rawValue: CXFloat32x3Load(&array))
    }

    @inline(__always)
    public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Float32 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension Float32x3 {

    @inline(__always)
    public static var zero: Float32x3 = .init(rawValue: CXFloat32x3MakeZero())

    @inline(__always)
    public var magnitude: Float32x3 { .init(rawValue: CXFloat32x3Absolute(rawValue)) }

    // MARK: Additive

    @inline(__always)
    public static func + (lhs: Float32x3, rhs: Float32x3) -> Float32x3 {
        return .init(rawValue: CXFloat32x3Add(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static func - (lhs: Float32x3, rhs: Float32x3) -> Float32x3  {
        return .init(rawValue: CXFloat32x3Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static prefix func - (operand: Float32x3) -> Float32x3  {
        return .init(rawValue: CXFloat32x3Negate(operand.rawValue))
    }

    public mutating func negate() {
        rawValue = CXFloat32x3Negate(rawValue)
    }

    // MARK: Multiplicative

    @inline(__always)
    public static func * (lhs: Float32x3, rhs: Float32x3) -> Float32x3  {
        return .init(rawValue: CXFloat32x3Multiply(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static func / (lhs: Float32x3, rhs: Float32x3) -> Float32x3  {
        return .init(rawValue: CXFloat32x3Divide(lhs.rawValue, rhs.rawValue))
    }
}
