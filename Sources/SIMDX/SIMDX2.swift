// Copyright 2019-2022 Markus Winter
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

import RealModule

/// A SIMD storage to 2 elements
public struct SIMDX2<Element>: SIMDX where Element: SIMDX2Element {
  public typealias RawValue = Element.Storage2
  public typealias Index = RawValue.Index

  public var rawValue: RawValue

  @_transparent
  public init(rawValue: RawValue) {
    self.rawValue = rawValue
  }
}

// MARK: - Additional Initializer
extension SIMDX2 {
  /// Initialize a raw SIMD storage to specified elements.
  @_transparent
  public init(_ element0: Element, _ element1: Element) {
    self.init(rawValue: RawValue(element0, element1))
  }
}

// MARK: - Conformance to (Mutable|RandomAccess)Collection
extension SIMDX2 {
  @_transparent
  public var startIndex: Index {
    rawValue.startIndex
  }

  @_transparent
  public var endIndex: Index {
    rawValue.endIndex
  }

  @_transparent
  public func index(before i: RawValue.Index) -> RawValue.Index {
    rawValue.index(before: i)
  }

  @_transparent
  public func index(after i: RawValue.Index) -> RawValue.Index {
    rawValue.index(after: i)
  }
}

// MARK: - Conformance to ExpressibleBy(Array|Integer)Literal
extension SIMDX2: ExpressibleByArrayLiteral {}
extension SIMDX2: ExpressibleByIntegerLiteral where RawValue: ExpressibleByIntegerLiteral {}

// MARK: - Conformance to Numerics Type
extension SIMDX2: Equatable where RawValue: Equatable {}
extension SIMDX2: AdditiveArithmetic where RawValue: AdditiveArithmetic {}
extension SIMDX2: Numeric where RawValue: Numeric {}

// NOTE:
// Implementation details of SignedNumeric and AlgebraicField can not be
// define in the SIMDX protocol for all its conforming types, as the standard
// library does provide default implementations for these operations as well.
extension SIMDX2: SignedNumeric where RawValue: SignedNumeric {
  @_transparent
  public static prefix func - (operand: Self) -> Self  {
    self.init(rawValue: -(operand.rawValue))
  }

  @_transparent
  public mutating func negate() {
    rawValue.negate()
  }
}

extension SIMDX2: AlgebraicField where RawValue: AlgebraicField {
  @_transparent
  public static func / (lhs: Self, rhs: Self) -> Self  {
    self.init(rawValue: lhs.rawValue / rhs.rawValue)
  }

  public static func /= (lhs: inout Self, rhs: Self) {
    lhs = lhs / rhs
  }
}
