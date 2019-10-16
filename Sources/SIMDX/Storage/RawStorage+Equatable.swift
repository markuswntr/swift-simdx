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
