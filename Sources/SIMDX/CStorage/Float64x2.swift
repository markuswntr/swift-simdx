import Foundation
import CSIMDX

public struct Float64x2: RawStorage2, FloatingPointRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 2

    // MARK: Raw Value Access

    @inline(__always)
    public fileprivate(set) var rawValue: CXFloat64x2

    @inline(__always)
    public subscript(index: Int32) -> Float64 {
        @inline(__always) set {
            CXFloat64x2SetElement(&rawValue, index, newValue)
        }
        @inline(__always) get {
            CXFloat64x2GetElement(rawValue, index)
        }
    }

    @inline(__always)
    public init(rawValue: CXFloat64x2) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Float64x2 {

    @inline(__always)
    public init(_ repeatingElement: Float64) {
        self.init(rawValue: CXFloat64x2MakeRepeatingElement(repeatingElement))
    }

    @inline(__always)
    public init(_ index0: Float64, _ index1: Float64) {
        self.init(rawValue: CXFloat64x2Make(index0, index1))
    }

    @inline(__always)
    public init(_ array: [Float64]) {
        var array = array
        self.init(rawValue: CXFloat64x2Load(&array))
    }

    @inline(__always)
    public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Float64 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension Float64x2 {

    @inline(__always)
    public static var zero: Float64x2 = .init(rawValue: CXFloat64x2MakeZero())

    @inline(__always)
    public var magnitude: Float64x2 { .init(rawValue: CXFloat64x2Absolute(rawValue)) }

    // MARK: Additive

    @inline(__always)
    public static func + (lhs: Float64x2, rhs: Float64x2) -> Float64x2 {
        return .init(rawValue: CXFloat64x2Add(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static func - (lhs: Float64x2, rhs: Float64x2) -> Float64x2  {
        return .init(rawValue: CXFloat64x2Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static prefix func - (operant: Float64x2) -> Float64x2  {
        return .init(rawValue: CXFloat64x2Negate(operant.rawValue))
    }

    public mutating func negate() {
        rawValue = CXFloat64x2Negate(rawValue)
    }

    // MARK: Multiplicative

    @inline(__always)
    public static func * (lhs: Float64x2, rhs: Float64x2) -> Float64x2  {
        return .init(rawValue: CXFloat64x2Multiply(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static func / (lhs: Float64x2, rhs: Float64x2) -> Float64x2  {
        return .init(rawValue: CXFloat64x2Divide(lhs.rawValue, rhs.rawValue))
    }
}
