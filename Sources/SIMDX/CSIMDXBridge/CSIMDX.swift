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

/// A protocol to address highly efficient and for parallel processing optimized
/// `SIMD` register types.
///
/// Conforming types must be a SIMD register type. This protocol then adds an
/// interface to SIMDX on top of the existing SIMD functions. If possible all
/// the functions in the protocol should directly call the appropriate SIMD
/// intrinsic function and should not implement any additional logic - and avoid
/// unexpected performance characteristics.
public protocol CSIMDX: MutableCollection where Index == CInt {

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
