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

/// An integer storage type that can represent only nonnegative values.
public protocol UnsignedIntegerRawStorage: BinaryIntegerRawStorage where Element: UnsignedInteger {
}

extension UnsignedIntegerRawStorage {

    /// The magnitude of this value.
    ///
    /// Every unsigned integer storage is its own magnitude, so for any value `x`, `x == x.magnitude`.
    ///
    ///     let x = SIMDX2<UInt8>(100, 2)
    ///     // x.magnitude == SIMDX2<UInt8>(100, 2)
    ///
    /// The global `abs(_:)` function provides more familiar syntax when you need to find an absolute value.
    @inlinable public var magnitude: Self { return self }

    /// A Boolean value indicating whether this storage contains signed integer types.
    ///
    /// This property is always `false` for unsigned integer types.
    @inlinable public static var isSigned: Bool { return false }
}
