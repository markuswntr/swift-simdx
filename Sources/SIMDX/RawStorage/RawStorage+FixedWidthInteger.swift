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

/// An integer type that uses a fixed size for every instance.
public protocol FixedWidthIntegerStorage: BinaryIntegerStorage where Element: FixedWidthInteger {

    // TODO: Add overflowing operators if possible

    /// The maximum representable integer in `Element` on all lanes.
    ///
    /// For unsigned integer types, the maximum value is `(2 ** bitWidth) - 1`, where
    /// `**` is exponentiation. For signed integer types, this value is `(2 ** (bitWidth - 1)) - 1`.
    static var max: Self { get }

    /// The minimum representable integer in `Element` on all lanes.
    ///
    /// For unsigned integer types, the minimum value is always `0`. For signed integer
    /// types, this value is `-(2 ** (bitWidth - 1))`, where `**` is exponentiation.
    static var min: Self { get }

    /// Performs element-by-element comparison and returns the greater of each comparison in a new storage.
    static func maximum(_ lhs: Self, _ rhs: Self) -> Self

    /// Performs element-by-element comparison and returns the lesser of each comparison in a new storage.
    static func minimum(_ lhs: Self, _ rhs: Self) -> Self
}

extension FixedWidthIntegerStorage {

    /// The maximum representable integer in `Element` on all lanes.
    @inlinable public static var max: Self { .init(.max) }

    /// The minimum representable integer in `Element` on all lanes.
    @inlinable public static var min: Self { .init(.min) }
}
