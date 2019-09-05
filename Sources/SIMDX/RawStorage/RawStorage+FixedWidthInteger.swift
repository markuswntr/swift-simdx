import Foundation

/// An integer type that uses a fixed size for every instance.
public protocol FixedWidthIntegerRawStorage: BinaryIntegerRawStorage where Element: FixedWidthInteger {

    // TODO: Add overflowing operators if possible

    /// The maximum representable integer in `Element` on all lanes.
    ///
    /// For unsigned integer types, the maximum value is `(2 ** bitWidth) - 1`, where
    /// `**` is exponentiation. For signed integer types, this value is `(2 ** (bitWidth - 1)) - 1`.
    static var max: Self { get }

    /// The minimum representable integer in `Element` on all lanes.
    ///
    /// For unsigned integer types, the minimum value is always `0`. For signed integer
    /// types, this value is `-(2 ** (bitWidth - 1))`, where `**` is exponentiation.
    static var min: Self { get }
}

extension FixedWidthIntegerRawStorage {

    /// The maximum representable integer in `Element` on all lanes.
    @inlinable public static var max: Self { .init(.max) }

    /// The minimum representable integer in `Element` on all lanes.
    @inlinable public static var min: Self { .init(.min) }
}
