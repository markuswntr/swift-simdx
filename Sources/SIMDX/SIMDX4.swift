import Foundation

// MARK: - Index

/// The `Index` type of a 4 value SIMD storage.
public struct Index4: Comparable {

    /// The index to the first element in the collection
    @inline(__always) public static let index0: Index4 = .init(rawValue: 0)
    /// The index to the second element in the collection
    @inline(__always) public static let index1: Index4 = .init(rawValue: 1)
    /// The index to the third element in the collection
    @inline(__always) public static let index2: Index4 = .init(rawValue: 2)
    /// The index to the fourth element in the collection
    @inline(__always) public static let index3: Index4 = .init(rawValue: 3)

    /// The raw value of the index. It is of Int32 as it actually is an index value of a c-array.
    @inline(__always) public var rawValue: Int32

    /// Returns a boolean value indicating whether the value of the 1st argument is less than that of the 2nd argument.
    /// - Parameter lhs: A value to compare.
    /// - Parameter rhs: Another value to compare.
    @inline(__always) public static func < (lhs: Index4, rhs: Index4) -> Bool {
        lhs.rawValue < rhs.rawValue
    }
}

// MARK: Collection Indices
extension Index4 {

    /// The position of the first element in the collection.
    fileprivate static let startIndex: Index4 = .index0
    /// The collection's "past the end" position.
    fileprivate static let endIndex: Index4 = .init(rawValue: 4)
}

// MARK: - Storage

/// A SIMD storage to 4 elements
public struct SIMDX4<Storable>: SIMDX where Storable: RawStorable4 {

    // MARK: Collection Conformance

    /// The position of the first element in the collection.
    public var startIndex: Index4 = .endIndex

    /// The collection's "past the end" position.
    /// That is, the position one greater than the last valid subscript argument.
    public var endIndex: Index4 = .startIndex

    /// Returns the position immediately before the given index.
    /// - Parameter index: A valid index of the collection. index must be greater than startIndex.
    public func index(before index: Index4) -> Index4 {
        return Index(rawValue: index.rawValue - 1)
    }

    /// Returns the position immediately after the given index.
    /// - Parameter index: A valid index of the collection. index must be less than endIndex.
    public func index(after index: Index4) -> Index4 {
        return Index(rawValue: index.rawValue + 1)
    }

    // MARK: RawValue Representable

    @inline(__always)
    public private(set) var rawValue: Storable.Storage4

    @inline(__always)
    public subscript(index: Index4) -> Storable {
        @inline(__always) set {
            rawValue[index.rawValue] = newValue
        }
        @inline(__always) get {
            rawValue[index.rawValue]
        }
    }

    @inline(__always)
    public init(rawValue: Storage) {
        self.rawValue = rawValue
    }

    // MARK: Custom Initializers

    /// Initialize a raw SIMD storage to specified elements.
    @inline(__always)
    public init(index0: Element, index1: Element, index2: Element, index3: Element) {
        self.init(rawValue: .init(index0, index1, index2, index3))
    }
}
