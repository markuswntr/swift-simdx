import Foundation

// MARK: - Index

/// The `Index` type of a 4 value SIMD storage.
public struct Index4: RawRepresentable, Comparable {

    /// The index to the first element in the collection
    public static let index0: Index4 = .init(rawValue: 0)
    /// The index to the second element in the collection
    public static let index1: Index4 = .init(rawValue: 1)
    /// The index to the third element in the collection
    public static let index2: Index4 = .init(rawValue: 2)
    /// The index to the fourth element in the collection
    public static let index3: Index4 = .init(rawValue: 3)

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
    @inlinable public static func < (lhs: Index4, rhs: Index4) -> Bool {
        lhs.rawValue < rhs.rawValue
    }
}

// MARK: - Storage

/// A SIMD storage to 4 elements
public struct SIMDX4<Storable>: SIMDX where Storable: RawStorable4 {

    public typealias Storage = Storable.Storage4
    public typealias Element = Storable
    public typealias Index = Index4

    /// The raw storage
    public var rawValue: Storage

    /// Initializes a new instance to given raw value
    @inlinable public init(rawValue: Storage) {
        self.rawValue = rawValue
    }
}

// MARK: Storage Initializer
extension SIMDX4 {

    /// Initialize a raw SIMD storage to specified elements.
    @inlinable public init(index0: Element, index1: Element, index2: Element, index3: Element) {
        self.init(rawValue: .init(index0, index1, index2, index3))
    }
}

// MARK: Collection Conformance
extension SIMDX4 {

    /// The position of the first element in the collection.
    public var startIndex: Index4 { .index0 }

    /// The collection's "past the end" position.
    /// That is, the position one greater than the last valid subscript argument.
    public var endIndex: Index4 { .init(rawValue: 4) }

    /// Returns the position immediately before the given index.
    /// - Parameter index: A valid index of the collection. index must be greater than startIndex.
    @inlinable public func index(before index: Index4) -> Index4 {
        return Index(rawValue: index.rawValue - 1)
    }

    /// Returns the position immediately after the given index.
    /// - Parameter index: A valid index of the collection. index must be less than endIndex.
    @inlinable public func index(after index: Index4) -> Index4 {
        return Index(rawValue: index.rawValue + 1)
    }
}

// MARK: Magnitude
extension SIMDX4 where Storage: NumericRawStorage, Storable.Magnitude: RawStorable4,
Storable.Magnitude.Storage4 == Storage.Magnitude {

    /// A type that can represent the absolute value of any possible value of the conforming type.
    public typealias Magnitude = SIMDX4<Storable.Magnitude>

    /// The magnitude of the values in the storage.
    @inlinable public var magnitude: SIMDX4<Storable.Magnitude> {
        return .init(rawValue: rawValue.magnitude)
    }
}
