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

/// A storage type that can contain both positive and negative values.
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
///
/// - Parameter value: A signed numeric raw storage.
/// - Returns: The absolute value of `storage`.
@inlinable public func abs<Storage>(_ storage: Storage) -> Storage.Magnitude where Storage: SignedNumericRawStorage {
    return storage.magnitude
}
