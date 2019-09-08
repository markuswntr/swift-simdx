import Foundation

/// A radix-2 (binary) floating-point storage type.
public protocol BinaryFloatingPointRawStorage: FloatingPointRawStorage where Element: BinaryFloatingPoint {

    /// Creates a new instance from the given value, each element rounded to the closest possible representation.
    ///
    /// If two representable values are equally close, the result is the value
    /// with more trailing zeros in its significand bit pattern.
    ///
    /// - Parameter value: A floating-point value storage to be converted.
    init<Source>(_ value: Source) where Source: NumericRawStorage, Source.Element: BinaryFloatingPoint

    /// Creates a new instance from the given value, if it can be represented
    /// exactly.
    ///
    /// If the given floating-point value cannot be represented exactly, the
    /// result is `nil`. A value that is NaN ("not a number") cannot be
    /// represented exactly if its payload cannot be encoded exactly.
    ///
    /// - Parameter value: A floating-point value to be converted.
    init?<Source>(exactly value: Source) where Source: NumericRawStorage, Source.Element: BinaryFloatingPoint
}

extension BinaryFloatingPointRawStorage {

    /// Creates a new instance from the given value, rounded to the closest possible representation.
    @inlinable public init<Source>(
        _ source: Source
    ) where Source: NumericRawStorage, Source.Element: BinaryFloatingPoint {
        self.init(source.map(Element.init))
    }

    /// Creates a new instance from the given integer storage, if it can be represented exactly.
    @inlinable public init?<Source>(
        exactly source: Source
    ) where Source: NumericRawStorage, Source.Element: BinaryFloatingPoint {
        let convertedElements = source.compactMap(Element.init(exactly:))
        guard convertedElements.count == source.count else { return nil }
        self.init(convertedElements)
    }
}
