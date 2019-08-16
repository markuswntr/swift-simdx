import Foundation

//#error("A simd is a static collection of equally typed elements - commonly numerics")
//#error("A simd has most (if not any) properties and functions that a numeric (or down the protocol road) defines in its protocol")

/// A wrapper type to raw SIMD intrinsic instructions. TODO: More documentation.
public protocol SIMDX: RandomAccessCollection, MutableCollection, ExpressibleByArrayLiteral, RawRepresentable
where Storage.Element == Element {

    /// The raw SIMD storage type to use for instances of this type.
    associatedtype Storage: RawStorage

    /// The raw SIMD storage to operate on when calling this instance.
    var rawValue: Storage { get }

    /// Initializes a new instance of `Self` backed by given storage.
    /// - Parameter rawValue: The value to use as storage for this instance.
    init(rawValue: Storage)
}

extension SIMDX {

    // MARK: Common Initializers

    /// Initialize to a SIMDX collection with all elements at `value`.
    @inline(__always)
    public init(repeating value: Element) {
        self.init(rawValue: Storage.init(value))
    }

    /// Initialize to a SIMDX collection with elements taken from `other` sequence.
    /// - Precondition: `other` must have the exact same count as the SIMDX collection.
    @inline(__always)
    public init<Other>(other: Other) where Other: Sequence, Element == Other.Element {
        self.init(rawValue: Storage.init(other))
    }

    // MARK: ExpressibleByArrayLiteral

    /// Creates an instance initialized with the given elements.
    @inline(__always)
    public init(arrayLiteral elements: Element...) {
        self.init(other: elements)
    }
}

// MARK: - Arithmetics
extension SIMDX {

    /// The zero value.
    ///
    /// Zero is the identity element for addition. For any value, `x + .zero == x` and `.zero + x == x`.
    @inline(__always)
    public static var zero: Self { .init(rawValue: Storage.zero) }

    // MARK: Additive

    /// Adds two values and produces their sum.
    ///
    /// The addition operator (`+`) calculates the sum of its two arguments. For
    /// example:
    ///
    ///     1 + 2                   // 3
    ///     -10 + 15                // 5
    ///     -15 + -5                // -20
    ///     21.5 + 3.25             // 24.75
    ///
    /// You cannot use `+` with arguments of different types. To add values of
    /// different types, convert one of the values to the other value's type.
    ///
    ///     let x: Int8 = 21
    ///     let y: Int = 1000000
    ///     Int(x) + y              // 1000021
    ///
    /// - Parameters:
    ///   - lhs: The first value to add.
    ///   - rhs: The second value to add.
    @inline(__always)
    public static func + (lhs: Self, rhs: Self) -> Self {
        return .init(rawValue: lhs.rawValue + rhs.rawValue)
    }

    /// Adds two values and stores the result in the left-hand-side variable.
    ///
    /// - Parameters:
    ///   - lhs: The first value to add.
    ///   - rhs: The second value to add.
    @inline(__always)
    public static func += (lhs: inout Self, rhs: Self) {
        lhs = .init(rawValue: lhs.rawValue + rhs.rawValue)
    }

    /// Subtracts one value from another and produces their difference.
    ///
    /// The subtraction operator (`-`) calculates the difference of its two
    /// arguments. For example:
    ///
    ///     8 - 3                   // 5
    ///     -10 - 5                 // -15
    ///     100 - -5                // 105
    ///     10.5 - 100.0            // -89.5
    ///
    /// You cannot use `-` with arguments of different types. To subtract values
    /// of different types, convert one of the values to the other value's type.
    ///
    ///     let x: UInt8 = 21
    ///     let y: UInt = 1000000
    ///     y - UInt(x)             // 999979
    ///
    /// - Parameters:
    ///   - lhs: A numeric value.
    ///   - rhs: The value to subtract from `lhs`.
    @inline(__always)
    public static func - (lhs: Self, rhs: Self) -> Self {
        return .init(rawValue: lhs.rawValue - rhs.rawValue)
    }

    /// Subtracts the second value from the first and stores the difference in the
    /// left-hand-side variable.
    ///
    /// - Parameters:
    ///   - lhs: A numeric value.
    ///   - rhs: The value to subtract from `lhs`.
    @inline(__always)
    public static func -= (lhs: inout Self, rhs: Self) {
        lhs = .init(rawValue: lhs.rawValue - rhs.rawValue)
    }

    /// Returns the additive inverse of the specified value.
    ///
    /// The negation operator (prefix `-`) returns the additive inverse of its
    /// argument.
    ///
    ///     let x = 21
    ///     let y = -x
    ///     // y == -21
    ///
    /// The resulting value must be representable in the same type as the
    /// argument. In particular, negating a signed, fixed-width integer type's
    /// minimum results in a value that cannot be represented.
    ///
    ///     let z = -Int8.min
    ///     // Overflow error
    ///
    /// - Returns: The additive inverse of the argument.
    @inline(__always)
    prefix public static func - (operant: Self) -> Self {
       return .init(rawValue: -(operant.rawValue))
    }

    // MARK: Multiplicative

    @inline(__always)
    public static func * (lhs: Self, rhs: Self) -> Self  {
        return .init(rawValue: lhs.rawValue * rhs.rawValue)
    }
}
