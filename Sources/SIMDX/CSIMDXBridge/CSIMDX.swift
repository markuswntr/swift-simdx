// Copyright 2022 Markus Winter
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

/// A protocol to address highly efficient and parallel processing optimized
/// `SIMD` register types.
///
/// Types conforming to this protocol are used to initialize a parallel
/// processing optimized `SIMD` storage based on the `Element` type within the
/// collection.
public protocol CSIMDX {

  typealias Index = CInt

  associatedtype Element

  var count: Int { get }

  subscript(position: Index) -> Element { get set }

  /// Initialize to a raw SIMD storage with all elements equal
  /// to `repeatingElement`.
  init(repeating repeatingElement: Element)

  /// Initialize to a raw SIMD storage with values equal to values in the
  /// array.
  ///
  /// - Precondition: The array must be of same length as the raw SIMD storage.
  /// - Parameter sequence: Values used, in order, for the storage initalization
  init(_ array: [Element])
}

// MARK: - Basic Properties
extension CSIMDX {
  @_transparent
  public var startIndex: Index { 0 }

  @_transparent
  public func index(before i: Index) -> Index {
    i - 1
  }

  @_transparent
  public func index(after i: Index) -> Index {
    i + 1
  }

  /// Initialize to a raw SIMD storage with values equal to values in the
  /// sequence.
  ///
  /// - Precondition: The sequence must be of same length as the storage.
  /// - Parameter sequence: Values used, in order, for the storage initalization
  init<Other: Sequence>(_ sequence: Other) where Other.Element == Self.Element {
    self.init(Array(sequence))
  }
}

// MARK: - Conformance to ExpressibleByIntegerLiteral
extension CSIMDX where Element: ExpressibleByIntegerLiteral {
  public typealias IntegerLiteralType = Element.IntegerLiteralType

  @_transparent
  public init(integerLiteral value: IntegerLiteralType) {
    self.init(repeating: Element(integerLiteral: value))
  }
}

// MARK: - 2-value register
/// A raw SIMD register type of exactly 2 values
public protocol CSIMDX2: CSIMDX {

    /// Initialize a raw SIMD register type to specified elements.
    init(_ element0: Element, _ element1: Element)
}

extension CSIMDX2 {
  @_transparent
  public var count: Int { 2 }

  @_transparent
  public var endIndex: Index { 2 }
}

// MARK: - 3-value register
/// A raw SIMD register type of exactly 3 values
public protocol CSIMDX3: CSIMDX {

  /// Initialize a raw SIMD register type to specified elements.
    init(_ element0: Element, _ element1: Element, _ element2: Element)
}

extension CSIMDX3 {
  @_transparent
  public var count: Int { 3 }

  @_transparent
  public var endIndex: Index { 3 }
}


// MARK: - 4-value register
/// A raw SIMD register type of exactly 4 values
public protocol CSIMDX4: CSIMDX {

  /// Initialize a raw SIMD register type to specified elements.
    init(_ element0: Element, _ element1: Element, _ element2: Element,
         _ element3: Element)
}

extension CSIMDX4 {
  @_transparent
  public var count: Int { 4 }

  @_transparent
  public var endIndex: Index { 4 }
}

// MARK: - 5-value register
/// A raw SIMD register type of exactly 5 values
public protocol CSIMDX5: CSIMDX {

  /// Initialize a raw SIMD register type to specified elements.
    init(_ element0: Element, _ element1: Element, _ element2: Element,
         _ element3: Element, _ element4: Element)
}

extension CSIMDX5 {
  @_transparent
  public var count: Int { 5 }

  @_transparent
  public var endIndex: Index { 5 }
}

// MARK: - 6-value register
/// A raw SIMD register type of exactly 6 values
public protocol CSIMDX6: CSIMDX {

  /// Initialize a raw SIMD register type to specified elements.
    init(_ element0: Element, _ element1: Element, _ element2: Element,
         _ element3: Element, _ element4: Element, _ element5: Element)
}

extension CSIMDX6 {
  @_transparent
  public var count: Int { 6 }

  @_transparent
  public var endIndex: Index { 6 }
}

// MARK: - 7-value register
/// A raw SIMD register type of exactly 7 values
public protocol CSIMDX7: CSIMDX {

  /// Initialize a raw SIMD register type to specified elements.
    init(_ element0: Element, _ element1: Element, _ element2: Element,
         _ element3: Element, _ element4: Element, _ element5: Element,
         _ element6: Element)
}

extension CSIMDX7 {
  @_transparent
  public var count: Int { 7 }

  @_transparent
  public var endIndex: Index { 7 }
}

// MARK: - 8-value register
/// A raw SIMD register type of exactly 8 values
public protocol CSIMDX8: CSIMDX {

  /// Initialize a raw SIMD register type to specified elements.
    init(_ element0: Element, _ element1: Element, _ element2: Element,
         _ element3: Element, _ element4: Element, _ element5: Element,
         _ element6: Element, _ element7: Element)
}

extension CSIMDX8 {
  @_transparent
  public var count: Int { 8 }

  @_transparent
  public var endIndex: Index { 8 }
}
