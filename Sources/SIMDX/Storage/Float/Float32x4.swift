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

public struct Float32x4: SIMDXStorage, SIMDX4Storage {
  public typealias RawValue = CFloat32x4
  public typealias Element = Float32

  @_alwaysEmitIntoClient
  public var rawValue: RawValue

  @_alwaysEmitIntoClient
  public init(rawValue: RawValue) {
    self.rawValue = rawValue
  }
}

// MARK: - Additional Initializers
extension Float32x4 {
  @_transparent
  public init(
    _ index0: Element,
    _ index1: Element,
    _ index2: Element,
    _ index3: Element
  ) {
    self.init(rawValue: CFloat32x4Make(index0, index1, index2, index3))
  }

  @_transparent
  public init(repeating repeatingElement: Element) {
    self.init(rawValue: CFloat32x4MakeRepeatingElement(repeatingElement))
  }

  @_transparent
  public init(_ array: [Float32]) {
    precondition(array.count == 4, "Array must contain exactly 4 elements")
    var array = array
    self.init(rawValue: CFloat32x4MakeLoad(&array))
  }
}

// MARK: - Conformance to MutableCollection
extension Float32x4 {
  public typealias Index = CInt
  public subscript(index: Index) -> Element {
    @_transparent set {
      precondition(indices.contains(index))
      CFloat32x4SetElement(&rawValue, index, newValue)
    }
    @_transparent get {
      precondition(indices.contains(index))
      return CFloat32x4GetElement(rawValue, index)
    }
  }
}

// MARK: - Conformance to Equatable
extension Float32x4: Equatable {
  @_transparent
  public static func == (lhs: Self, rhs: Self) -> Bool {
    lhs.indices.allSatisfy { lhs[$0] == rhs[$0] }
  }
}

// MARK: - Conformance to Hashable
extension Float32x4: Hashable {
  public func hash(into hasher: inout Hasher) {
    hasher.combine(CFloat32x4GetElement(rawValue, 0))
    hasher.combine(CFloat32x4GetElement(rawValue, 1))
    hasher.combine(CFloat32x4GetElement(rawValue, 2))
    hasher.combine(CFloat32x4GetElement(rawValue, 3))
  }
}

// MARK: - Conformance to AdditiveArithmetic
extension Float32x4: AdditiveArithmetic {
  @_transparent
  public static var zero: Self {
    self.init(rawValue: CFloat32x4MakeZero())
  }

  @_transparent
  public static func + (lhs: Self, rhs: Self) -> Self {
    self.init(rawValue: CFloat32x4Add(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func - (lhs: Self, rhs: Self) -> Self  {
    self.init(rawValue: CFloat32x4Subtract(lhs.rawValue, rhs.rawValue))
  }
}

// MARK: - Conformance to Numeric
extension Float32x4: Numeric {
  public typealias Magnitude = Element.Magnitude

  @_alwaysEmitIntoClient
  public var magnitude: Magnitude {
    indices.reduce(into: self[0]) { $0 = Swift.max($0, self[$1]) }
  }

  @_transparent
  public static func * (lhs: Self, rhs: Self) -> Self  {
    self.init(rawValue: CFloat32x4Multiply(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func *= (lhs: inout Self, rhs: Self) {
    lhs = lhs * rhs
  }

  @_transparent
  public init?<T>(exactly source: T) where T : BinaryInteger {
    guard let exactly = Element(exactly: source) else { return nil }
    self.init(rawValue: CFloat32x4MakeRepeatingElement(exactly))
  }
}

// MARK: - Conformace to SignedNumeric
extension Float32x4: SignedNumeric {
  @_transparent
  public static prefix func - (operand: Self) -> Self  {
    self.init(rawValue: CFloat32x4Negate(operand.rawValue))
  }

  @_transparent
  public mutating func negate() {
    rawValue = CFloat32x4Negate(rawValue)
  }
}

// MARK: - Conformance to AlgebraicField
extension Float32x4: AlgebraicField {
  @_transparent
  public static func / (lhs: Self, rhs: Self) -> Self  {
    self.init(rawValue: CFloat32x4Divide(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func /= (lhs: inout Self, rhs: Self) {
    lhs = lhs / rhs
  }
}

// MARK: - Conformance to ElementaryFunctions
// TODO: These are not yet exposed to SIMDX
extension Float32x4/*: ElementaryFunctions*/ {
  @_transparent
  static func sqrt(_ x: Self) -> Self {
    self.init(rawValue: CFloat32x4SquareRoot(x.rawValue))
  }
}
