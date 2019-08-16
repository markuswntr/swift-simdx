import Foundation

/// A protocol to address highly efficient and parallel processing optimized `SIMD` register types.
///
/// Types conforming to this protocol are used to initialize a parallel processing
/// optimized `SIMD` storage based on the `Element` type within the collection.
public protocol RawStorage: RandomAccessCollection, MutableCollection, RawRepresentable, Equatable where Index == Int32 {

    /// Initialize to a SIMD storage with all elements equal to `repeatingElement`.
    init(_ repeatingElement: Element)

    /// Initialize to a raw SIMD storage with values equal to values in the sequence.
    ///
    /// - Precondition: The sequence must be of same length as the vector.
    /// - Parameter sequence: Values to use, in order, for the vector initalization
    init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Self.Element

    // MARK: Additive Arithmetics

    /// The zero value.
    ///
    /// Zero is the identity element for addition. For any value, `x + .zero == x` and `.zero + x == x`.
    static var zero: Self { get }

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
    static func + (lhs: Self, rhs: Self) -> Self

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
    static func - (lhs: Self, rhs: Self) -> Self

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
    prefix static func - (operant: Self) -> Self

    // MARK: Multiplicative Arithmetics

    static func * (lhs: Self, rhs: Self) -> Self
}

extension RawStorage {

    /// Returns the given number unchanged.
    ///
    /// You can use the unary plus operator (`+`) to provide symmetry in your
    /// code for positive numbers when also using the unary minus operator.
    ///
    ///     let x = -21
    ///     let y = +21
    ///     // x == -21
    ///     // y == 21
    ///
    /// - Returns: The given argument without any changes.
    @inline(__always)
    prefix public static func + (operant: Self) -> Self {
        return operant
    }
}

// MARK: - Fixed Length

/// SIMD storage with a length of exactly 2 values
public protocol RawStorage2: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element)
}

/// SIMD storage with a length of exactly 3 values
public protocol RawStorage3: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element)
}

/// SIMD storage with a length of exactly 4 values
public protocol RawStorage4: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element, _ index3: Element)
}
