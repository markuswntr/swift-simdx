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
    /// - Precondition: The sequence must be of same length as the storage.
    /// - Parameter sequence: Values to use, in order, for the storage initalization
    init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Self.Element
}
