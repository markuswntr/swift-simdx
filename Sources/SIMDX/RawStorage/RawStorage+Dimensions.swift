import Foundation

// MARK: Dimensions

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

/// SIMD storage with a length of exactly 5 values
public protocol RawStorage5: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element, _ index3: Element,
         _ index4: Element)
}

/// SIMD storage with a length of exactly 6 values
public protocol RawStorage6: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element, _ index3: Element,
         _ index4: Element, _ index5: Element)
}

/// SIMD storage with a length of exactly 7 values
public protocol RawStorage7: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element, _ index3: Element,
         _ index4: Element, _ index5: Element, _ index6: Element)
}

/// SIMD storage with a length of exactly 8 values
public protocol RawStorage8: RawStorage {

    /// Initialize a raw SIMD storage to specified elements.
    init(_ index0: Element, _ index1: Element, _ index2: Element, _ index3: Element,
         _ index4: Element, _ index5: Element, _ index6: Element, _ index7: Element)
}

// MARK: Storables

/// Protocol of values that are representable in a `SIMDX2` storage
public protocol RawStorable2 where Storage2.Element == Self {
    associatedtype Storage2: RawStorage2
}

/// Protocol of values that are representable in a `SIMDX3` storage
public protocol RawStorable3 where Storage3.Element == Self {
    associatedtype Storage3: RawStorage3
}

/// Protocol of values that are representable in a `SIMDX4` storage
public protocol RawStorable4 where Storage4.Element == Self {
    associatedtype Storage4: RawStorage4
}

/// Protocol of values that are representable in a `SIMDX5` storage
public protocol RawStorable5 where Storage5.Element == Self {
    associatedtype Storage5: RawStorage5
}

/// Protocol of values that are representable in a `SIMDX6` storage
public protocol RawStorable6 where Storage6.Element == Self {
    associatedtype Storage6: RawStorage6
}

/// Protocol of values that are representable in a `SIMDX7` storage
public protocol RawStorable7 where Storage7.Element == Self {
    associatedtype Storage7: RawStorage7
}

/// Protocol of values that are representable in a `SIMDX8` storage
public protocol RawStorable8 where Storage8.Element == Self {
    associatedtype Storage8: RawStorage8
}
