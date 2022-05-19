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

import CSIMDX
import RealModule

public struct Float64x3: SIMDXStorage, SIMDX3Storage {
  public typealias RawValue = CFloat64x3
  public typealias Element = Float64

  @_alwaysEmitIntoClient
  public var rawValue: RawValue

  @_alwaysEmitIntoClient
  public init(rawValue: RawValue) {
    self.rawValue = rawValue
  }
}

// MARK: - Additional Initializers
extension Float64x3: ExpressibleByIntegerLiteral {
  @_transparent
  public init(_ index0: Element, _ index1: Element, _ index2: Element) {
    self.init(rawValue: CFloat64x3Make(index0, index1, index2))
  }

  @_transparent
  public init(repeating repeatingElement: Element) {
    self.init(rawValue: CFloat64x3MakeRepeatingElement(repeatingElement))
  }

  @_transparent
  public init(_ array: [Float64]) {
    precondition(array.count == 3, "Array must contain exactly 3 elements")
    var array = array
    self.init(rawValue: CFloat64x3MakeLoad(&array))
  }
}

// MARK: - Conformance to MutableCollection
extension Float64x3 {
  public typealias Index = CInt

  public subscript(index: Index) -> Element {
    @_transparent set {
      precondition(indices.contains(index))
      CFloat64x3SetElement(&rawValue, index, newValue)
    }
    @_transparent get {
      precondition(indices.contains(index))
      return CFloat64x3GetElement(rawValue, index)
    }
  }
}

// MARK: - Conformance to Equatable
extension Float64x3: Equatable {
  @_transparent
  public static func == (lhs: Self, rhs: Self) -> Bool {
    lhs.indices.allSatisfy { lhs[$0] == rhs[$0] }
  }
}

// MARK: - Conformance to Hashable
extension Float64x3: Hashable {
  public func hash(into hasher: inout Hasher) {
    hasher.combine(CFloat64x3GetElement(rawValue, 0))
    hasher.combine(CFloat64x3GetElement(rawValue, 1))
    hasher.combine(CFloat64x3GetElement(rawValue, 2))
  }
}

// MARK: - Conformance to AdditiveArithmetic
extension Float64x3: AdditiveArithmetic {
  @_transparent
  public static var zero: Self {
    self.init(rawValue: CFloat64x3MakeZero())
  }

  @_transparent
  public static func + (lhs: Self, rhs: Self) -> Self {
    self.init(rawValue: CFloat64x3Add(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func - (lhs: Self, rhs: Self) -> Self  {
    self.init(rawValue: CFloat64x3Subtract(lhs.rawValue, rhs.rawValue))
  }
}

// MARK: - Conformance to Numeric
extension Float64x3: Numeric {
  public typealias Magnitude = Element.Magnitude

  @_alwaysEmitIntoClient
  public var magnitude: Magnitude {
    let rawValue = CFloat64x3Magnitude(rawValue)
    return indices.reduce(into: CFloat64x3GetElement(rawValue, 0)) {
      $0 = Swift.max($0, CFloat64x3GetElement(rawValue, $1))
    }
  }

  @_transparent
  public static func * (lhs: Self, rhs: Self) -> Self  {
    self.init(rawValue: CFloat64x3Multiply(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func *= (lhs: inout Self, rhs: Self) {
    lhs = lhs * rhs
  }

  @_transparent
  public init?<T>(exactly source: T) where T : BinaryInteger {
    guard let exactly = Element(exactly: source) else { return nil }
    self.init(rawValue: CFloat64x3MakeRepeatingElement(exactly))
  }
}

// MARK: - Conformace to SignedNumeric
extension Float64x3: SignedNumeric {
  @_transparent
  public static prefix func - (operand: Self) -> Self  {
    self.init(rawValue: CFloat64x3Negate(operand.rawValue))
  }

  @_transparent
  public mutating func negate() {
    rawValue = CFloat64x3Negate(rawValue)
  }
}

// MARK: - Conformance to AlgebraicField
extension Float64x3: AlgebraicField {
  @_transparent
  public static func / (lhs: Self, rhs: Self) -> Self  {
    self.init(rawValue: CFloat64x3Divide(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func /= (lhs: inout Self, rhs: Self) {
    lhs = lhs / rhs
  }
}

// MARK: - Conformance to ElementaryFunctions
// TODO: These are not yet exposed to SIMDX
extension Float64x3/*: ElementaryFunctions*/ {
  @_transparent
  static func sqrt(_ x: Self) -> Self {
    self.init(rawValue: CFloat64x3SquareRoot(x.rawValue))
  }
}
