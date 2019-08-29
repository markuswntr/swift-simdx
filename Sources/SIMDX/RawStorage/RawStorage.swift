import Foundation

/// A protocol to address highly efficient and parallel processing optimized `SIMD` register types.
///
/// Types conforming to this protocol are used to initialize a parallel processing
/// optimized `SIMD` storage based on the `Element` type within the collection.
public protocol RawStorage: RandomAccessCollection, MutableCollection, RawRepresentable where Index == Int32 {

    /// Initialize to a SIMD storage with all elements equal to `repeatingElement`.
    init(_ repeatingElement: Element)

    /// Initialize to a raw SIMD storage with values equal to values in the sequence.
    ///
    /// - Precondition: The sequence must be of same length as the vector.
    /// - Parameter sequence: Values to use, in order, for the vector initalization
    init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Self.Element
}

// MARK: - Storage Length

/// SIMD storage with a length of exactly 2 values
public protocol RawStorage2: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element)
}

/// SIMD storage with a length of exactly 3 values
public protocol RawStorage3: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element)
}

/// SIMD storage with a length of exactly 4 values
public protocol RawStorage4: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element, _ index3: Element)
}
