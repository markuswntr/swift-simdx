import Foundation

/// An integer type that can represent both positive and negative values.
public protocol SignedIntegerRawStorage: BinaryIntegerRawStorage, SignedNumericRawStorage where Element: SignedInteger {
}

extension SignedIntegerRawStorage {

    /// A Boolean value indicating whether this storage contains signed integer types.
    ///
    /// This property is always `true` for signed integer types.
    @inlinable public static var isSigned: Bool { return true }
}
