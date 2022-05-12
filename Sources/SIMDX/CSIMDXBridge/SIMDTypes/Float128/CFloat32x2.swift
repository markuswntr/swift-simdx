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
extension CFloat32x2: CSIMDX, CSIMDX2 {
  public typealias Element = Float32
  public typealias Index = CInt
}

// MARK: - Additional Initializers
extension CFloat32x2: ExpressibleByIntegerLiteral {
  @_transparent
  public init(_ index0: Element, _ index1: Element) {
      self = CFloat32x2Make(index0, index1)
  }

  @_transparent
  public init(repeating repeatingElement: Element) {
      self = CFloat32x2MakeRepeatingElement(repeatingElement)
  }

  @_transparent
  public init(_ array: [Float32]) {
    precondition(array.count == 2, "Array must contain exactly 2 elements")
    var array = array
    self = CFloat32x2MakeLoad(&array)
  }
}

// MARK: - Conformance to MutableCollection
extension CFloat32x2 {
  public subscript(index: Index) -> Element {
    @_transparent set { CFloat32x2SetElement(&self, index, newValue) }
    @_transparent get { CFloat32x2GetElement(self, index) }
  }
}

// MARK: - Conformance to AdditiveArithmetic
extension CFloat32x2: AdditiveArithmetic {
  @_transparent
  public static var zero: Self {
    CFloat32x2MakeZero()
  }

  @_transparent
  public static func + (lhs: Self, rhs: Self) -> Self {
    CFloat32x2Add(lhs, rhs)
  }

  @_transparent
  public static func - (lhs: Self, rhs: Self) -> Self  {
    CFloat32x2Subtract(lhs, rhs)
  }
}

// MARK: - Conformance to Numeric
extension CFloat32x2: Numeric {
  public typealias Magnitude = Element.Magnitude

  @_transparent
  public var magnitude: Magnitude {
    #warning("TODO: this uses Swift.STDLIb.max")
    return CFloat32x2Absolute(self).max()
  }

  @_transparent
  public static func * (lhs: Self, rhs: Self) -> Self  {
    CFloat32x2Multiply(lhs, rhs)
  }

  @_transparent
  public init?<T>(exactly source: T) where T : BinaryInteger {
    guard let exactly = Element(exactly: source) else { return nil }
    self = CFloat32x2MakeRepeatingElement(exactly)
  }
}

// MARK: - Conformace to SignedNumeric
extension CFloat32x2: SignedNumeric {
  @_transparent
  public static prefix func - (operand: Self) -> Self  {
    CFloat32x2Negate(operand)
  }

  @_transparent
  public mutating func negate() {
    self = CFloat32x2Negate(self)
  }
}

// MARK: - Conformance to AlgebraicField
extension CFloat32x2: AlgebraicField {
  @_transparent
  public static func / (lhs: Self, rhs: Self) -> Self  {
    CFloat32x2Divide(lhs, rhs)
  }
}

// MARK: - Conformance to ElementaryFunctions
// TODO: These are not yet exposed to SIMDX
extension CFloat32x2/*: ElementaryFunctions*/ {
  @_transparent
  static func sqrt(_ x: Self) -> Self {
    CFloat32x2SquareRoot(x)
  }
}
