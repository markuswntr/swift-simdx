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

// MARK: Common Interface

extension SIMDX {

    /// Allows read and write access to individual elements in the storage.
    @inlinable public subscript(index: Index) -> Element {
        @inlinable set { rawValue[index.rawValue] = newValue }
        @inlinable get { rawValue[index.rawValue] }
    }

    /// Initialize to a SIMDX collection with all elements to `value`.
    @inlinable public init(repeating value: Element) {
        self.init(rawValue: Storage.init(value))
    }

    /// Initialize to a SIMDX collection with elements taken from `other` sequence.
    /// - Precondition: `other` must have the exact same count as the SIMDX collection.
    @inlinable public init<Other>(other: Other) where Other: Sequence, Element == Other.Element {
        self.init(rawValue: Storage.init(other))
    }

    /// Creates an instance initialized with the given elements.
    @inlinable public init(arrayLiteral elements: Element...) {
        self.init(other: elements)
    }
}

// MARK: - Down the Numeric Road

extension SIMDX where Storage: EquatableStorage {

    /// Returns a Boolean value indicating whether the values of two storages are element-wise equal.
    @inlinable public static func == (lhs: Self, rhs: Self) -> Bool {
        return lhs.rawValue == rhs.rawValue
    }
}

// MARK: Additive Arithmetic

extension SIMDX where Storage: AdditiveArithmeticStorage {

    /// The zero value.
    @inlinable public static var zero: Self { return .init(rawValue: .zero) }

    /// Returns the given storage unchanged.
    ///
    /// You can use the unary plus operator (`+`) to provide symmetry in your
    /// code for positive storages when also using the unary minus operator.
    @inlinable prefix public static func + (operand: Self) -> Self { return operand }

    /// Adds two storages and produces their element-wise sums.
    /// - Parameter lhs: The left hand side operand.
    /// - Parameter rhs: The right hand side operand.
    @inlinable public static func + (lhs: Self, rhs: Self) -> Self {
        return .init(rawValue: lhs.rawValue + rhs.rawValue)
    }

    /// Adds two storages and stores their element-wise sums in the lhs variable.
    @inlinable public static func += (lhs: inout Self, rhs: Self) {
        lhs.rawValue += rhs.rawValue
    }

    /// Subtracts one storage from another and produces their element-wise differences.
    /// - Parameter lhs: A numeric storage.
    /// - Parameter rhs: The numeric storage to subtract from `lhs`.
    @inlinable public static func - (lhs: Self, rhs: Self) -> Self {
        return .init(rawValue: lhs.rawValue - rhs.rawValue)
    }

    /// Subtracts the second storage from the first and stores the element-wise differences in the lhs variable.
    @inlinable public static func -= (lhs: inout Self, rhs: Self) {
        lhs.rawValue -= rhs.rawValue
    }
}

// MARK: Numeric

extension SIMDX where Storage: NumericRawStorage {

    /// Multiplies two storages and produces their element-wise products.
    @inlinable public static func * (lhs: Self, rhs: Self) -> Self {
        return .init(rawValue: lhs.rawValue * rhs.rawValue)
    }

    /// Multiplies two storages element-wise and stores their products in the left-hand-side variable.
    @inlinable public static func *= (lhs: inout Self, rhs: Self) {
        lhs.rawValue *= rhs.rawValue
    }

    /// Multiplies the storage element-wise by given element, and returns their products.
    @inlinable public static func * (storage: Self, element: Element) -> Self {
        return .init(rawValue: storage.rawValue * element)
    }

    /// Replaces the storage with the products of current storage elements multiplied element-wise by given element.
    @inlinable public static func *= (storage: inout Self, element: Element) {
        storage.rawValue *= element
    }
}

// MARK: Signed Numeric

extension SIMDX where Storage: SignedNumericRawStorage {

    /// Returns the additive inverse of the specified storage.
    @inlinable prefix public static func - (operand: Self) -> Self {
       .init(rawValue: -(operand.rawValue))
    }

    /// Replaces this value with its additive inverse.
    @inlinable public mutating func negate() {
        self = -self
    }
}

extension SIMDX where Storage: BinaryIntegerRawStorage {

    /// A Boolean value indicating whether this storage contains signed integer types.
    @inlinable static var isSigned: Bool { return Storage.isSigned }
}

// MARK: Fixed Width Integer

extension SIMDX where Storage: FixedWidthIntegerRawStorage {

    /// The maximum representable integer in this type.
    ///
    /// For unsigned integer types, this value is `(2 ** bitWidth) - 1`, where
    /// `**` is exponentiation. For signed integer types, this value is `(2 ** (bitWidth - 1)) - 1`.
    @inlinable public static var max: Self { .init(rawValue: .max) }

    /// The minimum representable integer in this type.
    ///
    /// For unsigned integer types, this value is always `0`. For signed integer
    /// types, this value is `-(2 ** (bitWidth - 1))`, where `**` is exponentiation.
    @inlinable public static var min: Self { .init(rawValue: .min) }
}

// MARK: Floating Point

extension SIMDX where Storage: FloatingPointRawStorage {

    @inlinable public static func / (lhs: Self, rhs: Self) -> Self  {
        .init(rawValue: lhs.rawValue / rhs.rawValue)
    }

    @inlinable public static func /= (lhs: inout Self, rhs: Self) {
        lhs = .init(rawValue: lhs.rawValue / rhs.rawValue)
    }

    @inlinable public static func / (storage: Self, element: Element) -> Self  {
        .init(rawValue: storage.rawValue / element)
    }

    @inlinable public static func /= (lhs: inout Self, rhs: Element) {
        lhs = .init(rawValue: lhs.rawValue / rhs)
    }
}
