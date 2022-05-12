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

import CSIMDX
import RealModule

// MARK: Basic Contract
extension CFloat32x3: CSIMDX, CSIMDX3 {
  public typealias Element = Float32
  public typealias Index = CInt
}

// MARK: - Additional Initializers
extension CFloat32x3: ExpressibleByIntegerLiteral {
  @_transparent
  public init(_ index0: Element, _ index1: Element, _ index2: Element) {
      self = CFloat32x3Make(index0, index1, index2)
  }

  @_transparent
  public init(repeating repeatingElement: Element) {
      self = CFloat32x3MakeRepeatingElement(repeatingElement)
  }

  @_transparent
  public init(_ array: [Float32]) {
    precondition(array.count == 3, "Array must contain exactly 3 elements")
    var array = array
    self = CFloat32x3MakeLoad(&array)
  }
}

// MARK: - Conformance to MutableCollection
extension CFloat32x3 {
  public subscript(index: Index) -> Element {
    @_transparent set { CFloat32x3SetElement(&self, index, newValue) }
    @_transparent get { CFloat32x3GetElement(self, index) }
  }
}

// MARK: - Conformance to Equatable
extension CFloat32x3: Equatable {
  @_transparent
  public static func == (lhs: Self, rhs: Self) -> Bool {
    lhs.rawValue == rhs.rawValue
  }
}

// MARK: - Conformance to Hashable
extension CFloat32x3: Hashable {
  public func hash(into hasher: inout Hasher) {
    hasher.combine(rawValue)
  }
}

// MARK: - Conformance to AdditiveArithmetic
extension CFloat32x3: AdditiveArithmetic {
  @_transparent
  public static var zero: Self {
    CFloat32x3MakeZero()
  }

  @_transparent
  public static func + (lhs: Self, rhs: Self) -> Self {
    CFloat32x3Add(lhs, rhs)
  }

  @_transparent
  public static func - (lhs: Self, rhs: Self) -> Self  {
    CFloat32x3Subtract(lhs, rhs)
  }
}

// MARK: - Conformance to Numeric
extension CFloat32x3: Numeric {
  public typealias Magnitude = Element.Magnitude

  @_alwaysEmitIntoClient
  public var magnitude: Magnitude {
    indices.reduce(into: self[0]) { $0 = Swift.max($0, self[$1]) }
  }

  @_transparent
  public static func * (lhs: Self, rhs: Self) -> Self  {
    CFloat32x3Multiply(lhs, rhs)
  }

  @_transparent
  public static func *= (lhs: inout Self, rhs: Self) {
    lhs = lhs * rhs
  }

  @_transparent
  public init?<T>(exactly source: T) where T : BinaryInteger {
    guard let exactly = Element(exactly: source) else { return nil }
    self = CFloat32x3MakeRepeatingElement(exactly)
  }
}

// MARK: - Conformace to SignedNumeric
extension CFloat32x3: SignedNumeric {
  @_transparent
  public static prefix func - (operand: Self) -> Self  {
    CFloat32x3Negate(operand)
  }

  @_transparent
  public mutating func negate() {
    self = CFloat32x3Negate(self)
  }
}

// MARK: - Conformance to AlgebraicField
extension CFloat32x3: AlgebraicField {
  @_transparent
  public static func / (lhs: Self, rhs: Self) -> Self  {
    CFloat32x3Divide(lhs, rhs)
  }

  @_transparent
  public static func /= (lhs: inout CFloat32x3_t, rhs: CFloat32x3_t) {
    lhs = CFloat32x3Divide(lhs, rhs)
  }
}

//// MARK: - Conformance to ElementaryFunctions
//// TODO: These are not yet exposed to SIMDX
//extension CFloat32x3/*: ElementaryFunctions*/ {
//  @_transparent
//  static func sqrt(_ x: Self) -> Self {
//    CFloat32x3SquareRoot(x)
//  }
//}
