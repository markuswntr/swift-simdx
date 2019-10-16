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

/// A storage type with values that support addition and subtraction.
public protocol AdditiveArithmeticStorage: EquatableStorage where Element: AdditiveArithmetic {

    /// The zero value.
    static var zero: Self { get }

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
        operand
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
