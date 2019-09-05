import Foundation


/// An integer storage type with a binary representation.
public protocol BinaryIntegerRawStorage: NumericRawStorage
where Element: BinaryInteger, Magnitude: BinaryIntegerRawStorage, Magnitude == Magnitude.Magnitude {

    /// A Boolean value indicating whether this storage contains signed integer types.
    static var isSigned: Bool { get }

    /// Creates a new instance from the given floating point storage, if it can be represented exactly.
    ///
    /// If the value passed as `source` is not representable exactly, the result is `nil`.
    ///
    /// In the following example, the constant `x` is successfully created from a value of `[6.0, -4.0]`,
    /// while the attempt to initialize the constant `y` from `[6.5, -4.0]` fails:
    ///
    ///     let x = SIMDX2<Int32>(exactly: SIMDX<Float32>(index0: 6.0, index1: -4.0))
    ///     // x == (6.0, -4.0)
    ///     let y = SIMDX2<Int32>(exactly: SIMDX<Float32>(index0: 6.5, index1: -4.0))
    ///     // y == nil
    ///
    /// - Parameter source: A floating-point storage to convert to this type.
    init?<Other>(exactly source: Other) where Other: NumericRawStorage, Other.Element: BinaryFloatingPoint

    /// Creates a new instance from the given floating point storage, rounding toward zero.
    /// If `source` is outside the bounds of this type after rounding toward zero, a runtime error may occur.
    ///
    /// - Parameter source: A floating-point storage to convert to an integer storage.
    init<Other>(_ source: Other) where Other: NumericRawStorage, Other.Element: BinaryFloatingPoint

    /// Creates a new instance from the given binary integer storage
    /// If the value passed as `source` is not representable in this type, a runtime error may occur.
    ///
    /// - Parameter source: An integer storage to convert. `source` must be representable in this type.
    init<Other>(_ source: Other) where Other: NumericRawStorage, Other.Element: BinaryInteger

    /// Creates an new instance from the bit patterns of the given storage by sign-extending or truncating to fit.
    ///
    /// - Parameter source: An integer storage to convert to this type.
    init<Other>(truncatingIfNeeded source: Other) where Other: NumericRawStorage, Other.Element: BinaryInteger

    /// Creates a new instance with the representable values that are closest to the given integer storages value.
    ///
    /// If values passed in `source` are greater than the maximum representable value in this type,
    /// the result is this type's `max` value. If values in `source` are less than the smallest
    /// representable value in this type, the result is the type's `min` value.
    ///
    /// - Parameter source: An integer to convert to this type.
    init<Other>(clamping source: Other) where Other: NumericRawStorage, Other.Element: BinaryInteger

    /// Returns the quotient of dividing the first storage by the second, element-wise.
    ///
    /// For integer types, any remainder of the division is discarded.
    ///
    ///     let x = 21 / 5
    ///     // x == 4
    ///
    /// - Parameters:
    ///   - lhs: The storage to divide element-wise.
    ///   - rhs: The storage to divide `lhs` by. `rhs` must not contain zero.
    static func / (lhs: Self, rhs: Self) -> Self

    /// Divides the first storage by the second and stores the quotient in the left-hand-side variable.
    ///
    /// For integer types, any remainder of the division is discarded.
    ///
    ///     var x = 21
    ///     x /= 5
    ///     // x == 4
    ///
    /// - Parameters:
    ///   - lhs: The storage to divide element-wise.
    ///   - rhs: The storage to divide `lhs` by. `rhs` must not contain zero.
    static func /= (lhs: inout Self, rhs: Self)

    /// Returns the quotient of element-wise dividing the first storage by `element`.
    ///
    /// For integer types, any remainder of the division is discarded.
    ///
    ///     let x = 21 / 5
    ///     // x == 4
    ///
    /// - Parameters:
    ///   - lhs: The storage to divide element-wise.
    ///   - rhs: The element to divide `lhs` element-wise by. `rhs` must not contain zero.
    static func / (lhs: Self, rhs: Element) -> Self

    /// Divides the first storage element-wise by `element` and stores the quotient in the left-hand-side variable.
    ///
    /// For integer types, any remainder of the division is discarded.
    ///
    ///     var x = 21
    ///     x /= 5
    ///     // x == 4
    ///
    /// - Parameters:
    ///   - lhs: The storage to divide element-wise.
    ///   - rhs: The element to divide `lhs` element-wise by. `rhs` must not contain zero.
    static func /= (lhs: inout Self, rhs: Element)

    /// Returns the remainders of dividing the first storage by the second.
    /// 
    /// - Parameters:
    ///   - lhs: The storage to divide.
    ///   - rhs: The storage to divide `lhs` by. `rhs` must not be zero.
    static func % (lhs: Self, rhs: Self) -> Self

    /// Divides the first storage by the second and stores the remainders in the left-hand-side variable.
    ///
    /// - Parameters:
    ///   - lhs: The storage to divide.
    ///   - rhs: The storage to divide `lhs` by. `rhs` must not be zero.
    static func %= (lhs: inout Self, rhs: Self)

    /// Returns the remainders of dividing the first storage element-wise by `element`.
    ///
    /// - Parameters:
    ///   - lhs: The storage to divide.
    ///   - rhs: The storage to divide `lhs` by. `rhs` must not be zero.
    static func % (lhs: Self, rhs: Element) -> Self

    /// Divides the first storage element-wise by `element` and stores the remainders in the left-hand-side variable.
    ///
    /// - Parameters:
    ///   - lhs: The storage to divide.
    ///   - rhs: The storage to divide `lhs` by. `rhs` must not be zero.
    static func %= (lhs: inout Self, rhs: Element)

    /// Returns the inverse of the bits set in the argument.
    prefix static func ~ (x: Self) -> Self

    /// Returns the result of performing a bitwise AND operation on the two given storages.
    ///
    /// - Parameters:
    ///   - lhs: An integer storage.
    ///   - rhs: Another integer storage.
    static func & (lhs: Self, rhs: Self) -> Self

    /// Stores the result of performing a bitwise AND operation on the two given storages in the lhs variable.
    ///
    /// - Parameters:
    ///   - lhs: An integer storage.
    ///   - rhs: Another integer storage.
    static func &= (lhs: inout Self, rhs: Self)

    /// Returns the result of performing a bitwise OR operation on the two given storages.
    ///
    /// - Parameters:
    ///   - lhs: An integer storage.
    ///   - rhs: Another integer storage.
    static func | (lhs: Self, rhs: Self) -> Self

    /// Stores the result of performing a bitwise OR operation on the two given values in the lhs variable.
    ///
    /// - Parameters:
    ///   - lhs: An integer storage.
    ///   - rhs: Another integer storage.
    static func |= (lhs: inout Self, rhs: Self)

    /// Returns the result of performing a bitwise XOR operation on the two given storages.
    ///
    /// - Parameters:
    ///   - lhs: An integer storage.
    ///   - rhs: Another integer storage.
    static func ^ (lhs: Self, rhs: Self) -> Self

    /// Stores the result of performing a bitwise XOR operation on the two given storages in the lhs variable.
    ///
    /// - Parameters:
    ///   - lhs: An integer storage.
    ///   - rhs: Another integer storage.
    static func ^= (lhs: inout Self, rhs: Self)

    /// Returns the result of shifting each element's binary representation the specified number of digits to the right.
    ///
    /// - Parameters:
    ///   - lhs: The storage to shift element-wise.
    ///   - rhs: The number of bits to shift each element in `lhs` to the right.
    static func >> <RHS>(lhs: Self, rhs: RHS) -> Self where RHS : BinaryInteger

    /// Stores the result of shifting each element's binary representation the specified
    /// number of digits to the right in the left-hand-side variable.
    ///
    /// - Parameters:
    ///   - lhs: The storage to shift element-wise.
    ///   - rhs: The number of bits to shift each element `lhs` to the right.
    static func >>= <RHS>(lhs: inout Self, rhs: RHS) where RHS : BinaryInteger

    /// Returns the result of shifting each element's binary representation the specified number of digits to the left.
    ///
    /// - Parameters:
    ///   - lhs: The storage to shift element-wise.
    ///   - rhs: The number of bits to shift each element in `lhs` to the left.
    static func << <RHS>(lhs: Self, rhs: RHS) -> Self where RHS : BinaryInteger

    /// Stores the result of shifting each element's binary representation the specified
    /// number of digits to the left in the left-hand-side variable.
    ///
    /// - Parameters:
    ///   - lhs: The storage to shift element-wise.
    ///   - rhs: The number of bits to shift each element `lhs` to the left.
    static func <<= <RHS>(lhs: inout Self, rhs: RHS) where RHS : BinaryInteger
}

extension BinaryIntegerRawStorage {

    /// Creates a new instance from the given floating point storage, if it can be represented exactly.
    @inlinable public init?<T>(exactly source: T) where T: NumericRawStorage, T.Element: BinaryFloatingPoint {
        let convertedElements = source.compactMap(Element.init(exactly:))
        guard convertedElements.count == source.count else { return nil }
        self.init(convertedElements)
    }

    /// Creates a new instance from the given floating point storage, rounding toward zero.
    @inlinable public init<Other>(_ source: Other) where Other: NumericRawStorage, Other.Element: BinaryFloatingPoint {
        self.init(source.map { Element.init($0) })
    }

    /// Creates a new instance from the given binary integer storage
    @inlinable public init<Other>(_ source: Other) where Other: NumericRawStorage, Other.Element: BinaryInteger {
        self.init(source.map { Element.init($0) })
   }

    /// Creates an new instance from the bit patterns of the given storage by sign-extending or truncating to fit.
    @inlinable public init<Other: NumericRawStorage>(truncatingIfNeeded source: Other) where Other.Element: BinaryInteger {
        self.init(source.map { Element.init(truncatingIfNeeded: $0) })
    }

    /// Creates a new instance with the representable values that are closest to the given integer storages value.
    @inlinable public init<Other>(clamping source: Other) where Other: NumericRawStorage, Other.Element: BinaryInteger {
        self.init(source.map { Element.init(clamping: $0) })
    }

    /// Divides the first storage by the second and stores the quotient in the left-hand-side variable.
    @inlinable public static func /= (lhs: inout Self, rhs: Self) {
        lhs = lhs / rhs
    }

    /// Returns the quotient of element-wise dividing the first storage by element.
    @inlinable public static func / (lhs: Self, rhs: Element) -> Self {
        return lhs / .init(rhs)
    }

    /// Divides the first storage element-wise by the element and stores the quotient in the left-hand-side variable.
    @inlinable public static func /= (lhs: inout Self, rhs: Element) {
        lhs = lhs / rhs
    }

    /// Divides the first storage by the second and stores the remainders in the left-hand-side variable.
    @inlinable public static func %= (lhs: inout Self, rhs: Self) {
        lhs = lhs % rhs
    }

    /// Returns the remainders of dividing the first storage element-wise by `element`.
    @inlinable public static func % (lhs: Self, rhs: Element) -> Self {
        return lhs % .init(rhs)
    }

    /// Divides the first storage element-wise by `element` and stores the remainders in the left-hand-side variable.
    @inlinable public static func %= (lhs: inout Self, rhs: Element) {
        lhs = lhs % rhs
    }

    /// Stores the result of performing a bitwise AND operation on the two given storages in the lhs variable.
    @inlinable public static func &= (lhs: inout Self, rhs: Self) {
        lhs = lhs & rhs
    }

    /// Stores the result of performing a bitwise OR operation on the two given values in the lhs variable.
    @inlinable public static func |= (lhs: inout Self, rhs: Self) {
        lhs = lhs | rhs
    }

    /// Stores the result of performing a bitwise XOR operation on the two given storages in the lhs variable.
    @inlinable public static func ^= (lhs: inout Self, rhs: Self) {
        lhs = lhs ^ rhs
    }

    /// Stores the result of shifting each element's binary representation the specified
    /// number of digits to the right in the left-hand-side variable.
    @inlinable public static func >>= <RHS>(lhs: inout Self, rhs: RHS) where RHS: BinaryInteger {
        lhs = lhs >> rhs
    }

    /// Stores the result of shifting each element's binary representation the specified
    /// number of digits to the left in the left-hand-side variable.
    @inlinable public static func <<= <RHS>(lhs: inout Self, rhs: RHS) where RHS: BinaryInteger {
        lhs = lhs << rhs
    }
}
