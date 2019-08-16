import Foundation

/// Protocol of scalar values that are representable in a `SIMDX2`
public protocol RawStorable2 where Storage2.Element == Self {
    associatedtype Storage2: RawStorage2
}

/// Protocol of scalar values that are representable in a `SIMDX3`
public protocol RawStorable3 where Storage3.Element == Self {
    associatedtype Storage3: RawStorage3
}

/// Protocol of scalar values that are representable in a `SIMDX4`
public protocol RawStorable4 where Storage4.Element == Self {
    associatedtype Storage4: RawStorage4
}
