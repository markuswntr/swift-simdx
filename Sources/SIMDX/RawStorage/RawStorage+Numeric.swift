import Foundation

// MARK: - Numeric Storage

/// A type with values that support addition, subtraction and multiplication.
public protocol NumericRawStorage: RawStorage where Element: Numeric {

    /// Creates a new instance from the given integer, if it can be represented
    /// exactly.
    ///
    /// If the value passed as `source` is not representable exactly, the result
    /// is `nil`. In the following example, the constant `x` is successfully
    /// created from a value of `100`, while the attempt to initialize the
    /// constant `y` from `1_000` fails because the `Int8` type can represent
    /// `127` at maximum:
    ///
    ///     let x = Int8(exactly: 100)
    ///     // x == Optional(100)
    ///     let y = Int8(exactly: 1_000)
    ///     // y == nil
    ///
    /// - Parameter source: A value to convert to this type.
//    init?<Other>(exactly source: Other) where Other: NumericRawStorage, Other.Element: BinaryInteger

    /// A type that can represent the absolute value of any possible value of the conforming type.
//    associatedtype Magnitude: Comparable, NumericRawStorage

    /// The magnitude of this value.
    ///
    /// For any numeric value `x`, `x.magnitude` is the absolute value of `x`.
    /// You can use the `magnitude` property in operations that are simpler to
    /// implement in terms of unsigned values, such as printing the value of an
    /// integer, which is just printing a '-' character in front of an absolute
    /// value.
    ///
    ///     let x = -200
    ///     // x.magnitude == 200
    ///
    /// The global `abs(_:)` function provides more familiar syntax when you need
    /// to find an absolute value. In addition, because `abs(_:)` always returns
    /// a value of the same type, even in a generic context, using the function
    /// instead of the `magnitude` property is encouraged.
    var magnitude: Self { get } // TODO: To strict. Must not necessarly be Self, but should be ok for now

    /// The zero value.
    ///
    /// Zero is the identity element for addition. For any value, `x + .zero == x` and `.zero + x == x`.
    static var zero: Self { get }

    // MARK: Additive Arithmetics

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

    // MARK: Multiplicative Arithmetics

    /// Multiplies two values and produces their product.
    ///
    /// The multiplication operator (`*`) calculates the product of its two
    /// arguments. For example:
    ///
    ///     2 * 3                   // 6
    ///     100 * 21                // 2100
    ///     -10 * 15                // -150
    ///     3.5 * 2.25              // 7.875
    ///
    /// You cannot use `*` with arguments of different types. To multiply values
    /// of different types, convert one of the values to the other value's type.
    ///
    ///     let x: Int8 = 21
    ///     let y: Int = 1000000
    ///     Int(x) * y              // 21000000
    ///
    /// - Parameters:
    ///   - lhs: The first value to multiply.
    ///   - rhs: The second value to multiply.
    static func * (lhs: Self, rhs: Self) -> Self
}

extension NumericRawStorage {

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
    @inlinable prefix public static func + (operand: Self) -> Self {
        return operand
    }
}

// MARK: - SignedNumeric Storage

/// A type that can store both positive and negative values.
///
/// The `SignedNumericRawStorage` protocol extends the operations defined by the
/// `NumericRawStorage` protocol to include a value's additive inverse.
public protocol SignedNumericRawStorage: NumericRawStorage where Element: SignedNumeric {

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
    /// - Returns: The additive inverse of this value.
    prefix static func - (operand: Self) -> Self

    /// Replaces this value with its additive inverse.
    ///
    /// The following example uses the `negate()` method to negate the value of
    /// an integer `x`:
    ///
    ///     var x = 21
    ///     x.negate()
    ///     // x == -21
    ///
    /// The resulting value must be representable within the value's type. In
    /// particular, negating a signed, fixed-width integer type's minimum
    /// results in a value that cannot be represented.
    ///
    ///     var y = Int8.min
    ///     y.negate()
    ///     // Overflow error
    mutating func negate()
}

extension SignedNumericRawStorage {

    @inlinable public mutating func negate() {
        self = -self
    }
}

/// Returns the absolute values of the given storage.
///
/// The absolute values of `storage` must be representable in the same type. In particular, the absolute
/// value of a storage with signed, fixed-width integer type's minimum cannot be represented.
///
///     let x = Int8.min
///     // x == -128
///     let y = abs(x)
///     // Overflow error
///
/// - Parameter value: A signed numeric raw storage.
/// - Returns: The absolute value of `storage`.
@inlinable public func abs<Storage>(_ storage: Storage) -> Storage where Storage: SignedNumericRawStorage {
    return storage.magnitude
}

// MARK: - FixedWidthInteger Storage

// TODO: This type is not properly defined yet
public protocol FixedWidthIntegerRawStorage: SignedNumericRawStorage where Element: FixedWidthInteger {

    /// The maximum representable integer in this type.
    ///
    /// For unsigned integer types, this value is `(2 ** bitWidth) - 1`, where
    /// `**` is exponentiation. For signed integer types, this value is
    /// `(2 ** (bitWidth - 1)) - 1`.
    static var max: Self { get }

    /// The minimum representable integer in this type.
    ///
    /// For unsigned integer types, this value is always `0`. For signed integer
    /// types, this value is `-(2 ** (bitWidth - 1))`, where `**` is
    /// exponentiation.
    static var min: Self { get }
}

extension FixedWidthIntegerRawStorage {

    @inlinable public static var max: Self { .init(.max) }

    @inlinable public static var min: Self { .init(.min) }
}

// MARK: - FloatingPoint Storage

// TODO: This type is not properly defined yet
public protocol FloatingPointRawStorage: SignedNumericRawStorage where Element: FloatingPoint {

    /// Positive infinity.
    ///
    /// Infinity compares greater than all finite numbers and equal to other
    /// infinite values.
    ///
    ///     let x = Double.greatestFiniteMagnitude
    ///     let y = x * 2
    ///     // y == Double.infinity
    ///     // y > x
    static var infinity: Self { get }

    /// The greatest finite number representable by this type.
    ///
    /// This value compares greater than or equal to all finite numbers, but less
    /// than `infinity`.
    ///
    /// This value corresponds to type-specific C macros such as `FLT_MAX` and
    /// `DBL_MAX`. The naming of those macros is slightly misleading, because
    /// `infinity` is greater than this value.
    static var greatestFiniteMagnitude: Self { get }

    /// The least positive normal number.
    ///
    /// This value compares less than or equal to all positive normal numbers.
    /// There may be smaller positive numbers, but they are *subnormal*, meaning
    /// that they are represented with less precision than normal numbers.
    ///
    /// This value corresponds to type-specific C macros such as `FLT_MIN` and
    /// `DBL_MIN`. The naming of those macros is slightly misleading, because
    /// subnormals, zeros, and negative numbers are smaller than this value.
    static var leastNormalMagnitude: Self { get }

    /// Returns the quotient of dividing the first value of the first storage by
    /// the first value of the second storage, rounded to a representable value.
    ///
    /// - Parameters:
    ///   - lhs: The values to divide.
    ///   - rhs: The values to divide `lhs` by.
    static func / (lhs: Self, rhs: Self) -> Self
}

extension FloatingPointRawStorage {

    @inlinable public static var infinity: Self { .init(.infinity) }

    @inlinable public static var greatestFiniteMagnitude: Self { .init(.greatestFiniteMagnitude) }

    @inlinable public static var leastNormalMagnitude: Self { .init(.leastNormalMagnitude) }
}
