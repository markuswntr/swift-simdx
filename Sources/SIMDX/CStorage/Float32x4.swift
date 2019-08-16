import Foundation
import CSIMDX

public struct Float32x4: RawStorage4 {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 4

    // MARK: Raw Value Access

    @inline(__always)
    public private(set) var rawValue: CXFloat32x4

    @inline(__always)
    public subscript(index: Int32) -> Float32 {
        @inline(__always) set {
            CXFloat32x4SetElement(&rawValue, index, newValue)
        }
        @inline(__always) get {
            CXFloat32x4GetElement(rawValue, index)
        }
    }

    @inline(__always)
    public init(rawValue: CXFloat32x4) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Float32x4 {

    @inline(__always)
    public init(_ repeatingElement: Float32) {
        self.init(rawValue: CXFloat32x4MakeRepeatingElement(repeatingElement))
    }

    @inline(__always)
    public init(_ index0: Float32, _ index1: Float32, _ index2: Float32, _ index3: Float32) {
        self.init(rawValue: CXFloat32x4Make(index0, index1, index2, index3))
    }

    @inline(__always)
    public init(_ array: [Float32]) {
        var array = array
        self.init(rawValue: CXFloat32x4Load(&array))
    }

    @inline(__always)
    public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Float32 {
        self.init(Array(sequence))
    }
}

// MARK: - Comparable
extension Float32x4 {

    @inline(__always)
    public func equalMask(to other: Float32x4) -> Float32x4 {
        return .init(rawValue: CXFloat32x4Equal(self.rawValue, other.rawValue))
    }

    @inline(__always)
    public static func == (lhs: Float32x4, rhs: Float32x4) -> Bool {
        let result: Float32x4 = lhs.equalMask(to: rhs) // TODO: Refactor
        return result[0] != 0.0 && result[1] != 0.0 && result[2] != 0.0 && result[3] != 0.0
    }
}

// MARK: - Arithmetics
extension Float32x4 {

    @inline(__always)
    public static var zero: Float32x4 = .init(rawValue: CXFloat32x4MakeZero())

    // MARK: Additive

    @inline(__always)
    public static func + (lhs: Float32x4, rhs: Float32x4) -> Float32x4 {
        return .init(rawValue: CXFloat32x4Add(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static func - (lhs: Float32x4, rhs: Float32x4) -> Float32x4  {
        return .init(rawValue: CXFloat32x4Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inline(__always)
    public static prefix func - (operant: Float32x4) -> Float32x4  {
        return .init(rawValue: CXFloat32x4Negate(operant.rawValue))
    }

    // MARK: Multiplicative

    @inline(__always)
    public static func * (lhs: Float32x4, rhs: Float32x4) -> Float32x4  {
        return .init(rawValue: CXFloat32x4Multiply(lhs.rawValue, rhs.rawValue))
    }
}
