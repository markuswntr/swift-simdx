import Foundation

/// A storage that can store both positive and negative values.
public protocol SignedNumericRawStorage: NumericRawStorage where Element: SignedNumeric {

    /// Returns the additive inverse of the specified storage.
    prefix static func - (operand: Self) -> Self

    /// Replaces this storage with its additive inverse element-wise.
    mutating func negate()
}

extension SignedNumericRawStorage {

    /// Replaces this value with its additive inverse.
    @inlinable public mutating func negate() {
        self = -self
    }
}

/// Returns the absolute values of the given storage.
/// The absolute values of `storage` must be representable in the same type.
///
/// - Parameter value: A signed numeric raw storage.
/// - Returns: The absolute value of `storage`.
@inlinable public func abs<Storage>(_ storage: Storage) -> Storage.Magnitude where Storage: SignedNumericRawStorage {
    return storage.magnitude
}
