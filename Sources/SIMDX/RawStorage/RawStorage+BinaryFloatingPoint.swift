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

/// A radix-2 (binary) floating-point storage type.
public protocol BinaryFloatingPointStorage: FloatingPointStorage where Element: BinaryFloatingPoint {

    /// Creates a new instance from the given value, each element rounded to the closest possible representation.
    ///
    /// If two representable values are equally close, the result is the value
    /// with more trailing zeros in its significand bit pattern.
    ///
    /// - Parameter value: A floating-point value storage to be converted.
    init<Source>(_ value: Source) where Source: NumericStorage, Source.Element: BinaryFloatingPoint

    /// Creates a new instance from the given value, if it can be represented
    /// exactly.
    ///
    /// If the given floating-point value cannot be represented exactly, the
    /// result is `nil`. A value that is NaN ("not a number") cannot be
    /// represented exactly if its payload cannot be encoded exactly.
    ///
    /// - Parameter value: A floating-point value to be converted.
    init?<Source>(exactly value: Source) where Source: NumericStorage, Source.Element: BinaryFloatingPoint
}

extension BinaryFloatingPointStorage {

    /// Creates a new instance from the given value, rounded to the closest possible representation.
    @inlinable public init<Source>(
        _ source: Source
    ) where Source: NumericStorage, Source.Element: BinaryFloatingPoint {
        self.init(source.map(Element.init))
    }

    /// Creates a new instance from the given integer storage, if it can be represented exactly.
    @inlinable public init?<Source>(
        exactly source: Source
    ) where Source: NumericStorage, Source.Element: BinaryFloatingPoint {
        let convertedElements = source.compactMap(Element.init(exactly:))
        guard convertedElements.count == source.count else { return nil }
        self.init(convertedElements)
    }
}
