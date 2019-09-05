import Foundation

/// A storage type that can be compared for value equality.
public protocol EquatableStorage: RawStorage where Element: Equatable {

    /// Returns a Boolean value indicating whether the values of two storages are element-wise equal.
    static func == (lhs: Self, rhs: Self) -> Bool
}

extension EquatableStorage {

    /// Returns a Boolean value indicating whether the values of two storages are element-wise equal.
    @inlinable public static func == (lhs: Self, rhs: Self) -> Bool {
        return zip(lhs, rhs).allSatisfy(==)
    }
}
