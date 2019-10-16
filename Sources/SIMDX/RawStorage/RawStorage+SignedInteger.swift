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

/// An integer type that can represent both positive and negative values.
public protocol SignedIntegerStorage: BinaryIntegerStorage, SignedNumericStorage where Element: SignedInteger {
}

extension SignedIntegerStorage {

    /// A Boolean value indicating whether this storage contains signed integer types.
    ///
    /// This property is always `true` for signed integer types.
    @inlinable public static var isSigned: Bool { return true }
}
