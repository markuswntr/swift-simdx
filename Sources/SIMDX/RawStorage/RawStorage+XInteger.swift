import Foundation

// MARK: - BinaryInteger Storage

// TODO: This type is not properly defined yet
public protocol BinaryIntegerRawStorage: NumericRawStorage where Element: BinaryInteger {

}

// MARK: - UnsignedInteger Storage

// TODO: This type is not properly defined yet
public protocol UnsignedIntegerRawStorage: BinaryIntegerRawStorage where Element: UnsignedInteger {

}

// MARK: - SignedInteger Storage

// TODO: This type is not properly defined yet
public protocol SignedIntegerRawStorage: BinaryIntegerRawStorage, SignedNumericRawStorage where Element: SignedInteger {

}

// MARK: - FixedWidthInteger Storage

// TODO: This type is not properly defined yet
public protocol FixedWidthIntegerRawStorage: BinaryIntegerRawStorage where Element: FixedWidthInteger {

    /// The maximum representable integer in `Element` on all lanes.
    ///
    /// For unsigned integer types, the maximum value is `(2 ** bitWidth) - 1`, where
    /// `**` is exponentiation. For signed integer types, this value is `(2 ** (bitWidth - 1)) - 1`.
    static var max: Self { get }

    /// The minimmum representable integer in `Element` on all lanes.
    ///
    /// For unsigned integer types, the minimum value is always `0`. For signed integer
    /// types, this value is `-(2 ** (bitWidth - 1))`, where `**` is exponentiation.
    static var min: Self { get }
}

extension FixedWidthIntegerRawStorage {

    /// The maximum representable integer in this type.
    @inlinable public static var max: Self { .init(.max) }

    /// The minimum representable integer in this type.
    @inlinable public static var min: Self { .init(.min) }
}
