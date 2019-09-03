import Foundation

// TODO: This type is not properly defined yet
public protocol FloatingPointRawStorage: SignedNumericRawStorage where Element: FloatingPoint {

    /// Returns the quotient of dividing the first value of the first storage by
    /// the first value of the second storage, rounded to a representable value.
    ///
    /// - Parameters:
    ///   - lhs: The values to divide.
    ///   - rhs: The values to divide `lhs` by.
    static func / (lhs: Self, rhs: Self) -> Self
}

extension FloatingPointRawStorage {

    /// Positive infinity.
    ///
    /// Infinity compares greater than all finite numbers and equal to other
    /// infinite values.
    ///
    ///     let x = Double.greatestFiniteMagnitude
    ///     let y = x * 2
    ///     // y == Double.infinity
    ///     // y > x
    @inlinable public static var infinity: Self { .init(.infinity) }

    /// The greatest finite number representable by this type.
    ///
    /// This value compares greater than or equal to all finite numbers, but less
    /// than `infinity`.
    ///
    /// This value corresponds to type-specific C macros such as `FLT_MAX` and
    /// `DBL_MAX`. The naming of those macros is slightly misleading, because
    /// `infinity` is greater than this value.
    @inlinable public static var greatestFiniteMagnitude: Self { .init(.greatestFiniteMagnitude) }

    /// The least positive normal number.
    ///
    /// This value compares less than or equal to all positive normal numbers.
    /// There may be smaller positive numbers, but they are *subnormal*, meaning
    /// that they are represented with less precision than normal numbers.
    ///
    /// This value corresponds to type-specific C macros such as `FLT_MIN` and
    /// `DBL_MIN`. The naming of those macros is slightly misleading, because
    /// subnormals, zeros, and negative numbers are smaller than this value.
    @inlinable public static var leastNormalMagnitude: Self { .init(.leastNormalMagnitude) }

    /// Divides the storage (element-wise) by given element.
    ///
    /// - Parameter storage: The storage to be divided by given element.
    /// - Parameter element: The element to use as divisor to each single other element in the storage.
    @inlinable static func / (storage: Self, element: Element) -> Self {
        return storage / .init(element)
    }
}

// TODO: This type is not properly defined yet
public protocol BinaryFloatingPointRawStorage: FloatingPointRawStorage where Element: BinaryFloatingPoint {

}
