// Copyright 2019-2022 Markus Winter
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import RealModule

/// A wrapper type to raw SIMD intrinsic instructions. TODO: More documentation.
public protocol SIMDX: RawRepresentable, RandomAccessCollection, MutableCollection, ExpressibleByArrayLiteral
where RawValue: SIMDXStorage, RawValue.Element == Element, RawValue.Index == Index {
  // OVERRIDEN: All modifications (setter)
  var rawValue: RawValue { get set }

  // OVERRIDEN: Non-failable initializer
  init(rawValue: RawValue)
}

// MARK: - Conformance to Collection
extension SIMDX/*: MutableCollection*/ {
  @_transparent
  public var count: Int { rawValue.count }

  public subscript(position: Index) -> Element {
    @_transparent set { rawValue[position] = newValue }
    @_transparent get { rawValue[position] }
  }
}

// MARK: - Conformance to ExpressibleByArrayLiteral
extension SIMDX/*: ExpressibleByArrayLiteral*/ {
  @_transparent
  public init(arrayLiteral elements: Element...) {
    self.init(rawValue: RawValue(elements))
  }
}

// MARK: - Conformance to ExpressibleByIntegerLiteral
extension SIMDX/*: ExpressibleByIntegerLiteral*/ where RawValue: ExpressibleByIntegerLiteral {
  public typealias IntegerLiteralType = RawValue.IntegerLiteralType

  @_transparent
  public init(integerLiteral value: RawValue.IntegerLiteralType) {
    self.init(rawValue: RawValue(integerLiteral: value))
  }
}

// MARK: - Conformance to Equatable
extension SIMDX/*: Equatable*/ where RawValue: Equatable {
  /// Returns a Boolean value indicating whether the values of two storages are element-wise equal.
  @_transparent
  public static func == (lhs: Self, rhs: Self) -> Bool {
      lhs.rawValue == rhs.rawValue
  }
}

// MARK: - Conformance to AdditiveArithmetic
extension SIMDX/*: AdditiveArithmetic*/ where RawValue: AdditiveArithmetic {
  @_transparent
  public static var zero: Self {
    self.init(rawValue: .zero)
  }

  @_transparent
  public static func + (lhs: Self, rhs: Self) -> Self {
    self.init(rawValue: lhs.rawValue + rhs.rawValue)
  }

  @_transparent
  public static func - (lhs: Self, rhs: Self) -> Self {
    self.init(rawValue: lhs.rawValue - rhs.rawValue)
  }
}

// MARK: - Conformance to Numeric
extension SIMDX/*: Numeric*/ where RawValue: Numeric {
  @_transparent
  public init?<T>(exactly source: T) where T : BinaryInteger {
    guard let rawValue = RawValue(exactly: source) else { return nil }
    self.init(rawValue: rawValue)
  }

  @_transparent
  public var magnitude: RawValue.Magnitude {
    rawValue.magnitude
  }

  @_transparent
  public static func * (lhs: Self, rhs: Self) -> Self {
    self.init(rawValue: lhs.rawValue * rhs.rawValue)
  }

  @_transparent
  public static func *= (lhs: inout Self, rhs: Self) {
    lhs.rawValue *= rhs.rawValue
  }
}

//// MARK: Binary Integer
//
//extension SIMDX where Storage: BinaryIntegerStorage {
//
//    /// A Boolean value indicating whether this storage contains signed integer types.
//    @inlinable public static var isSigned: Bool { Storage.isSigned }
//
//    @inlinable public init?<Source>(
//        exactly value: Source
//    ) where Source: SIMDX, Source.Storage: NumericStorage, Source.Storage.Element: BinaryFloatingPoint {
//        guard let rawValue = Storage.init(exactly: value.rawValue) else { return nil }
//        self.init(rawValue: rawValue)
//    }
//
//    @inlinable public init<Source>(
//        _ value: Source
//    ) where Source: SIMDX, Source.Storage: NumericStorage, Source.Storage.Element: BinaryFloatingPoint {
//        self.init(rawValue: Storage.init(value.rawValue))
//    }
//
//    @inlinable public init<Source>(
//        _ value: Source
//    ) where Source: SIMDX, Source.Storage: NumericStorage, Source.Storage.Element: BinaryInteger {
//        self.init(rawValue: Storage.init(value.rawValue))
//    }
//
//    @inlinable public init<Source>(
//        truncatingIfNeeded value: Source
//    ) where Source: SIMDX, Source.Storage: NumericStorage, Source.Storage.Element: BinaryInteger {
//        self.init(rawValue: Storage.init(truncatingIfNeeded: value.rawValue))
//    }
//
//    @inlinable public init<Source>(
//        clamping value: Source
//    ) where Source: SIMDX, Source.Storage: NumericStorage, Source.Storage.Element: BinaryInteger {
//        self.init(rawValue: Storage.init(clamping: value.rawValue))
//    }
//
//    @inlinable public prefix static func ~ (operand: Self) -> Self {
//        .init(rawValue: ~(operand.rawValue))
//    }
//
//    @inlinable public static func & (lhs: Self, rhs: Self) -> Self {
//        .init(rawValue: lhs.rawValue & rhs.rawValue)
//    }
//
//    @inlinable public static func &= (lhs: inout Self, rhs: Self) {
//        lhs.rawValue &= rhs.rawValue
//    }
//
//    @inlinable public static func | (lhs: Self, rhs: Self) -> Self {
//        .init(rawValue: lhs.rawValue | rhs.rawValue)
//    }
//
//    @inlinable public static func |= (lhs: inout Self, rhs: Self) {
//        lhs.rawValue |= rhs.rawValue
//    }
//
//    @inlinable public static func ^ (lhs: Self, rhs: Self) -> Self {
//        .init(rawValue: lhs.rawValue ^ rhs.rawValue)
//    }
//
//    @inlinable public static func ^= (lhs: inout Self, rhs: Self) {
//        lhs.rawValue ^= rhs.rawValue
//    }
//
//    @inlinable public static func >> <RHS>(lhs: Self, rhs: RHS) -> Self where RHS : BinaryInteger {
//        .init(rawValue: lhs.rawValue >> rhs)
//    }
//
//    @inlinable public static func >>= <RHS>(lhs: inout Self, rhs: RHS) where RHS : BinaryInteger {
//        lhs.rawValue >>= rhs
//    }
//
//    @inlinable public static func << <RHS>(lhs: Self, rhs: RHS) -> Self where RHS : BinaryInteger {
//        .init(rawValue: lhs.rawValue << rhs)
//    }
//
//    @inlinable public static func <<= <RHS>(lhs: inout Self, rhs: RHS) where RHS : BinaryInteger {
//        lhs.rawValue <<= rhs
//    }
//}
//
//// MARK: Fixed Width Integer
//
//extension SIMDX where Storage: FixedWidthIntegerStorage {
//
//    /// The maximum representable integer in this type.
//    ///
//    /// For unsigned integer types, this value is `(2 ** bitWidth) - 1`, where
//    /// `**` is exponentiation. For signed integer types, this value is `(2 ** (bitWidth - 1)) - 1`.
//    @inlinable public static var max: Self { .init(rawValue: .max) }
//
//    /// The minimum representable integer in this type.
//    ///
//    /// For unsigned integer types, this value is always `0`. For signed integer
//    /// types, this value is `-(2 ** (bitWidth - 1))`, where `**` is exponentiation.
//    @inlinable public static var min: Self { .init(rawValue: .min) }
//}
//
//// MARK: Floating Point
//
//extension SIMDX where Storage: FloatingPointStorage {
//
//    @inlinable public init<Source>(
//        _ value: Source
//    ) where Source: SIMDX, Source.Storage: NumericStorage, Source.Storage.Element: BinaryInteger {
//        self.init(rawValue: Storage.init(value.rawValue))
//    }
//
//    @inlinable public init?<Source>(
//        exactly value: Source
//    ) where Source: SIMDX, Source.Storage: NumericStorage, Source.Storage.Element: BinaryInteger {
//        guard let rawValue = Storage.init(exactly: value.rawValue) else { return nil }
//        self.init(rawValue: rawValue)
//    }
//
//    @inlinable public static var infinity: Self {
//        .init(rawValue: .infinity)
//    }
//
//    @inlinable public static var greatestFiniteMagnitude: Self {
//        .init(rawValue: .greatestFiniteMagnitude)
//    }
//
//    @inlinable public static var pi: Self {
//        .init(rawValue: .pi)
//    }
//
//    @inlinable public static var ulpOfOne: Self {
//        .init(rawValue: .ulpOfOne)
//    }
//
//    @inlinable public static var leastNormalMagnitude: Self {
//        .init(rawValue: .leastNormalMagnitude)
//    }
//
//    @inlinable public static var leastNonzeroMagnitude: Self {
//        .init(rawValue: .leastNonzeroMagnitude)
//    }
//
//    @inlinable public static func / (lhs: Self, rhs: Self) -> Self  {
//        .init(rawValue: lhs.rawValue / rhs.rawValue)
//    }
//
//    @inlinable public static func /= (lhs: inout Self, rhs: Self) {
//        lhs.rawValue /= rhs.rawValue
//    }
//
//    @inlinable public static func / (storage: Self, element: Element) -> Self  {
//        .init(rawValue: storage.rawValue / element)
//    }
//
//    @inlinable public static func /= (lhs: inout Self, rhs: Element) {
//        lhs.rawValue /= rhs
//    }
//
//    @inlinable public func squareRoot() -> Self {
//        .init(rawValue: rawValue.squareRoot())
//    }
//
//    /// Replaces this storage with its square root, rounded to a representable value.
//    @inlinable public mutating func formSquareRoot() {
//        rawValue.formSquareRoot()
//    }
//
//    @inlinable public static func minimum(_ lhs: Self, _ rhs: Self) -> Self {
//        .init(rawValue: .minimum(lhs.rawValue, rhs.rawValue))
//    }
//
//    @inlinable public static func maximum(_ lhs: Self, _ rhs: Self) -> Self {
//        .init(rawValue: .maximum(lhs.rawValue, rhs.rawValue))
//    }
//}
//
//// MARK: Binary FloatingPoint
//
//extension SIMDX where Storage: BinaryFloatingPointStorage {
//
//    @inlinable public init<Source>(
//        _ value: Source
//    ) where Source: SIMDX, Source.Storage: NumericStorage, Source.Storage.Element: BinaryFloatingPoint {
//        self.init(rawValue: Storage.init(value.rawValue))
//    }
//
//    @inlinable public init?<Source>(
//        exactly value: Source
//    ) where Source: SIMDX, Source.Storage: NumericStorage, Source.Storage.Element: BinaryFloatingPoint {
//        guard let rawValue = Storage.init(exactly: value.rawValue) else { return nil }
//        self.init(rawValue: rawValue)
//    }
//}
