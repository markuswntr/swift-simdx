// Copyright 2019 Markus Winter
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

import Foundation

/// A storage type with values that support multiplication.
public protocol NumericStorage: AdditiveArithmeticStorage where Element: Numeric {

    /// Creates a new instance from the given integer storage, if it can be represented exactly.
    ///
    /// If the value passed as `source` is not representable exactly, the result is `nil`.
    ///
    /// In the following example, the constant `x` is successfully created from a value of `[100, -2]`,
    /// while the attempt to initialize the constant `y` from `[1_000, -2]` fails because the `Int8` type
    /// can represent `127` at maximum:
    ///
    ///     let x = SIMDX2<Int8>(exactly: SIMDX<Int32>(index0: 100, index1: -2))
    ///     // x == SIMDX2<Int8>(100, -2)
    ///     let y = SIMDX2<Int8>(exactly: SIMDX<Int32>(index0: 1_000, index1: -2))
    ///     // y == nil
    ///
    /// - Parameter source: A storage to convert to this type.
    init?<Other>(exactly source: Other) where Other: NumericStorage, Other.Element: BinaryInteger

    /// A type that can represent the absolute value of any possible value of the conforming type.
    associatedtype Magnitude: NumericStorage where Magnitude.Element == Element.Magnitude

    /// The magnitude of this value.
    ///
    /// For any numeric value `x`, `x.magnitude` is the absolute value of `x`.
    ///
    ///     let x = SIMDX2<Int8>(100, -2)
    ///     // x.magnitude == SIMDX2<UInt8>(100, 2)
    ///
    /// The global `abs(_:)` function provides more familiar syntax when you need to find an absolute value.
    var magnitude: Magnitude { get }

    /// Multiplies two storages and produces their element-wise products.
    static func * (lhs: Self, rhs: Self) -> Self

    /// Multiplies two storages element-wise and stores their products in the left-hand-side variable.
    static func *= (lhs: inout Self, rhs: Self)

    /// Multiplies the storage element-wise by given element, and returns their products.
    static func * (storage: Self, element: Element) -> Self

    /// Replaces the storage with the products of current storage elements multiplied element-wise by given element.
    static func *= (storage: inout Self, element: Element)
}

extension NumericStorage {

    /// Creates a new instance from the given integer storage, if it can be represented exactly.
    @inlinable public init?<Other: NumericStorage>(exactly source: Other) where Other.Element: BinaryInteger {
        let convertedElements = source.compactMap(Element.init(exactly:))
        guard convertedElements.count == source.count else { return nil }
        self.init(convertedElements)
    }

    /// Multiplies two storages element-wise and stores their products in the left-hand-side variable.
    @inlinable public static func *= (lhs: inout Self, rhs: Self) {
        lhs = lhs * rhs
    }

    /// Multiplies the storage element-wise by given element, and return their products.
    @inlinable public static func * (storage: Self, element: Element) -> Self {
        return storage * .init(element)
    }

    /// Replaces the storage with the products of current storage elements multiplied element-wise by given element.
    @inlinable public static func *= (storage: inout Self, element: Element) {
        storage = storage * element
    }
}
