import Foundation

/// A storage type with values that support addition and subtraction.
public protocol AdditiveArithmeticStorage: EquatableStorage where Element: AdditiveArithmetic {

    /// The zero value.
    static var zero: Self { get }

    /// Returns the given storage unchanged.
    static prefix func + (operand: Self) -> Self

    /// Adds two storages and produces their element-wise sums.
    static func + (lhs: Self, rhs: Self) -> Self

    /// Adds two storages and stores their element-wise sums in the lhs variable.
    static func += (lhs: inout Self, rhs: Self)

    /// Subtracts one storage from another and produces their element-wise differences.
    static func - (lhs: Self, rhs: Self) -> Self

    /// Subtracts the second storage from the first and stores the element-wise differences in the lhs variable.
    static func -= (lhs: inout Self, rhs: Self)
}

extension AdditiveArithmeticStorage {

    /// Returns the given storage unchanged.
    @inlinable public static prefix func + (operand: Self) -> Self {
        return operand
    }

    /// Adds two storages and stores their element-wise sums in the left-hand-side.
    @inlinable public static func += (lhs: inout Self, rhs: Self) {
        lhs = lhs + rhs
    }

    /// Subtracts the second storage from the first and stores the element-wise differences in the left-hand-side.
    @inlinable public static func -= (lhs: inout Self, rhs: Self) {
        lhs = lhs - rhs
    }
}
