import Foundation
import CSIMDX

public struct Float32x2: RawStorage2, FloatingPointRawStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 2

    // MARK: Raw Value Access

    @inline(__always)
    public fileprivate(set) var rawValue: CXFloat32x2

    @inline(__always)
    public subscript(index: Int32) -> Float32 {
        @inline(__always) set {
            CXFloat32x2SetElement(&rawValue, index, newValue)
        }
        @inline(__always) get {
            CXFloat32x2GetElement(rawValue, index)
        }
    }

    @inline(__always)
    public init(rawValue: CXFloat32x2) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Float32x2 {

    @inline(__always)
    public init(_ repeatingElement: Float32) {
        self.init(rawValue: CXFloat32x2MakeRepeatingElement(repeatingElement))
    }

    @inline(__always)
    public init(_ index0: Float32, _ index1: Float32) {
        self.init(rawValue: CXFloat32x2Make(index0, index1))
    }

    @inline(__always)
    public init(_ array: [Float32]) {
        var array = array
        self.init(rawValue: CXFloat32x2Load(&array))
    }

    @inline(__always)
    public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Float32 {
        self.init(Array(sequence))
    }
}

// MARK: - Arithmetics
extension Float32x2 {

    @inline(__always)
    public static var zero: Float32x2 = .init(rawValue: CXFloat32x2MakeZero())

    @inline(__always)
    public var magnitude: Float32x2 { .init(rawValue: CXFloat32x2Absolute(rawValue)) }

    // MARK: Additive

    @inline(__always)
    public static func + (lhs: Float32x2, rhs: Float32x2) -> Float32x2 {
        return .init(rawValue: CXFloat32x2Add(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static func - (lhs: Float32x2, rhs: Float32x2) -> Float32x2  {
        return .init(rawValue: CXFloat32x2Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static prefix func - (operant: Float32x2) -> Float32x2  {
        return .init(rawValue: CXFloat32x2Negate(operant.rawValue))
    }

    public mutating func negate() {
        rawValue = CXFloat32x2Negate(rawValue)
    }

    // MARK: Multiplicative

    @inline(__always)
    public static func * (lhs: Float32x2, rhs: Float32x2) -> Float32x2  {
        return .init(rawValue: CXFloat32x2Multiply(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static func / (lhs: Float32x2, rhs: Float32x2) -> Float32x2  {
        return .init(rawValue: CXFloat32x2Divide(lhs.rawValue, rhs.rawValue))
    }
}
