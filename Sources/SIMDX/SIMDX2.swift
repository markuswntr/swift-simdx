import Foundation

// MARK: - Index

/// The `Index` type of a 2 value SIMD storage.
public struct Index2: RawRepresentable, Comparable {

    /// The index to the first element in the collection
    public static let index0: Index2 = .init(rawValue: 0)
    /// The index to the second element in the collection
    public static let index1: Index2 = .init(rawValue: 1)

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
    @inlinable public static func < (lhs: Index2, rhs: Index2) -> Bool {
        lhs.rawValue < rhs.rawValue
    }
}

// MARK: - Storage

/// A SIMD storage to 2 elements
public struct SIMDX2<Storable>: SIMDX where Storable: RawStorable2 {

    public typealias Storage = Storable.Storage2
    public typealias Element = Storable
    public typealias Index = Index2

    // MARK: RawValue Representable

    /// The raw storage
    public var rawValue: Storage

    /// Initializes a new instance to given raw value
    @inlinable public init(rawValue: Storage) {
        self.rawValue = rawValue
    }
}

// MARK: Storage Initializer
extension SIMDX2 {

    /// Initialize a raw SIMD storage to specified elements.
    @inlinable public init(index0: Storable, index1: Storable) {
        self.init(rawValue: .init(index0, index1))
    }
}

// MARK: Collection Conformance
extension SIMDX2 {

    /// The position of the first element in the collection.
    @inlinable public var startIndex: Index2 { .index0 }

    /// The collection's "past the end" position.
    /// That is, the position one greater than the last valid subscript argument.
    @inlinable public var endIndex: Index2 { .init(rawValue: 2) }

    /// Returns the position immediately before the given index.
    /// - Parameter index: A valid index of the collection. index must be greater than startIndex.
    @inlinable public func index(before index: Index2) -> Index2 {
        return Index(rawValue: index.rawValue - 1)
    }

    /// Returns the position immediately after the given index.
    /// - Parameter index: A valid index of the collection. index must be less than endIndex.
    @inlinable public func index(after index: Index2) -> Index2 {
        return Index(rawValue: index.rawValue + 1)
    }
}
