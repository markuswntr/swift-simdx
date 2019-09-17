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

// MARK: - Index

/// The `Index` type of a 3 value SIMD storage.
public struct Index3: RawRepresentable, Comparable {

    /// The index to the first element in the collection
    public static let index0: Index3 = .init(rawValue: 0)
    /// The index to the second element in the collection
    public static let index1: Index3 = .init(rawValue: 1)
    /// The index to the third element in the collection
    public static let index2: Index3 = .init(rawValue: 2)

    /// The raw value of the index. It is of Int32 as it actually is an index value of a c-array.
    public var rawValue: Int32

    /// Initializes a new instance to given raw value.
    /// - Parameter rawValue: The raw value of the returning instance.
    @inlinable public init(rawValue: Int32) {
        self.rawValue = rawValue
    }

    /// Returns a boolean value indicating whether the value of the 1st argument is less than that of the 2nd argument.
    /// - Parameter lhs: A value to compare.
    /// - Parameter rhs: Another value to compare.
    @inlinable public static func < (lhs: Index3, rhs: Index3) -> Bool {
        lhs.rawValue < rhs.rawValue
    }
}

// MARK: - Storage

/// A SIMD storage to 3 elements
public struct SIMDX3<Storable>: SIMDX where Storable: RawStorable3 {

    public typealias Storage = Storable.Storage3
    public typealias Element = Storable
    public typealias Index = Index3

    /// The raw storage
    public var rawValue: Storage

    /// Initializes a new instance to given raw value
    @inlinable public init(rawValue: Storage) {
        self.rawValue = rawValue
    }
}

// MARK: Storage Initializer
extension SIMDX3 {

    /// Initialize a raw SIMD storage to specified elements.
    @inlinable public init(index0: Element, index1: Element, index2: Element) {
        self.init(rawValue: .init(index0, index1, index2))
    }
}

// MARK: Collection Conformance
extension SIMDX3 {

    /// The position of the first element in the collection.
    public var startIndex: Index3 { .index0 }

    /// The collection's "past the end" position.
    /// That is, the position one greater than the last valid subscript argument.
    public var endIndex: Index3 { .init(rawValue: 3) }

    /// Returns the position immediately before the given index.
    /// - Parameter index: A valid index of the collection. index must be greater than startIndex.
    @inlinable public func index(before index: Index3) -> Index3 {
        return Index(rawValue: index.rawValue - 1)
    }

    /// Returns the position immediately after the given index.
    /// - Parameter index: A valid index of the collection. index must be less than endIndex.
    @inlinable public func index(after index: Index3) -> Index3 {
        return Index(rawValue: index.rawValue + 1)
    }
}

// MARK: Magnitude
extension SIMDX3 where Storage: NumericRawStorage, Storable.Magnitude: RawStorable3,
Storable.Magnitude.Storage3 == Storage.Magnitude {

    /// A type that can represent the absolute value of any possible value of the conforming type.
    public typealias Magnitude = SIMDX3<Storable.Magnitude>

    /// The magnitude of the values in the storage.
    @inlinable public var magnitude: SIMDX3<Storable.Magnitude> {
        return .init(rawValue: rawValue.magnitude)
    }
}
