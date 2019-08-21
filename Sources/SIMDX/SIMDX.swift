import Foundation

//#error("A simd is a static collection of equally typed elements - commonly numerics")
//#error("A simd has most (if not any) properties and functions that a numeric (or down the protocol road) defines in its protocol")

/// A wrapper type to raw SIMD intrinsic instructions. TODO: More documentation.
public protocol SIMDX: RandomAccessCollection, MutableCollection, ExpressibleByArrayLiteral, RawRepresentable
where Element == Storage.Element, Index: RawRepresentable, Index.RawValue == Storage.Index {

    /// The raw SIMD storage type to use for instances of this type.
    associatedtype Storage: RawStorage

    /// The raw SIMD storage to operate on when calling this instance.
    var rawValue: Storage { get set }

    /// Initializes a new instance of `Self` backed by given storage.
    /// - Parameter rawValue: The value to use as storage for this instance.
    init(rawValue: Storage)
}

// MARK: Common Initializers
extension SIMDX {

    @inlinable public subscript(index: Index) -> Element {
        @inlinable set { rawValue[index.rawValue] = newValue }
        @inlinable get { rawValue[index.rawValue] }
    }

    /// Initialize to a SIMDX collection with all elements at `value`.
    @inlinable public init(repeating value: Element) {
        self.init(rawValue: Storage.init(value))
    }

    /// Initialize to a SIMDX collection with elements taken from `other` sequence.
    /// - Precondition: `other` must have the exact same count as the SIMDX collection.
    @inlinable public init<Other>(other: Other) where Other: Sequence, Element == Other.Element {
        self.init(rawValue: Storage.init(other))
    }

    // MARK: ExpressibleByArrayLiteral

    /// Creates an instance initialized with the given elements.
    @inlinable public init(arrayLiteral elements: Element...) {
        self.init(other: elements)
    }
}

// MARK: - Arithmetics

extension SIMDX where Storage: NumericRawStorage {

    @inlinable public static var zero: Self { .init(rawValue: .zero) }

    @inlinable public var magnitude: Self { .init(rawValue: rawValue.magnitude) }

    // MARK: Additive

    @inlinable prefix public static func + (operant: Self) -> Self { operant }

    @inlinable public static func + (lhs: Self, rhs: Self) -> Self {
        .init(rawValue: lhs.rawValue + rhs.rawValue)
    }

    @inlinable public static func += (lhs: inout Self, rhs: Self) {
        lhs = .init(rawValue: lhs.rawValue + rhs.rawValue)
    }

    @inlinable public static func - (lhs: Self, rhs: Self) -> Self {
        .init(rawValue: lhs.rawValue - rhs.rawValue)
    }

    @inlinable public static func -= (lhs: inout Self, rhs: Self) {
        lhs = .init(rawValue: lhs.rawValue - rhs.rawValue)
    }

    // MARK: Multiplicative

    @inlinable public static func * (lhs: Self, rhs: Self) -> Self  {
        .init(rawValue: lhs.rawValue * rhs.rawValue)
    }
}

extension SIMDX where Storage: SignedNumericRawStorage {

    @inlinable prefix public static func - (operant: Self) -> Self {
       return .init(rawValue: -(operant.rawValue))
    }
}

extension SIMDX where Storage: FloatingPointRawStorage {

    @inlinable public static func / (lhs: Self, rhs: Self) -> Self  {
        return .init(rawValue: lhs.rawValue / rhs.rawValue)
    }
}
