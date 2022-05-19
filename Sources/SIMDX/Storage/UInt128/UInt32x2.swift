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

public struct UInt32x2: SIMDXStorage, SIMDX2Storage {
  public typealias RawValue = CUInt32x2
  public typealias Element = UInt32

  @_alwaysEmitIntoClient
  public var rawValue: RawValue

  @_alwaysEmitIntoClient
  public init(rawValue: RawValue) {
    self.rawValue = rawValue
  }
}

// MARK: - Additional Initializers
extension UInt32x2: ExpressibleByIntegerLiteral {
  @_transparent
  public init(_ index0: Element, _ index1: Element) {
    self.init(rawValue: CUInt32x2Make(index0, index1))
  }

  @_transparent
  public init(repeating repeatingElement: Element) {
    self.init(rawValue: CUInt32x2MakeRepeatingElement(repeatingElement))
  }

  @_transparent
  public init(_ array: [UInt32]) {
    precondition(array.count == 2, "Array must contain exactly 2 elements")
    var array = array
    self.init(rawValue: CUInt32x2MakeLoad(&array))
  }
}

// MARK: - Conformance to MutableCollection
extension UInt32x2 {
  public subscript(index: Index) -> Element {
    @_transparent set {
      precondition(indices.contains(index))
      CUInt32x2SetElement(&rawValue, index, newValue)
    }
    @_transparent get {
      precondition(indices.contains(index))
      return CUInt32x2GetElement(rawValue, index)
    }
  }
}

// MARK: - Conformance to Equatable
extension UInt32x2: Equatable {
  @_transparent
  public static func == (lhs: Self, rhs: Self) -> Bool {
    let cmp = CUInt32x2CompareElementWise(lhs.rawValue, rhs.rawValue)
    return lhs.indices.allSatisfy { CUInt32x2GetElement(cmp, $0) != .zero }
  }
}

// MARK: - Conformance to Hashable
extension UInt32x2: Hashable {
  public func hash(into hasher: inout Hasher) {
    hasher.combine(CUInt32x2GetElement(rawValue, 0))
    hasher.combine(CUInt32x2GetElement(rawValue, 1))
  }
}

// MARK: - Conformance to AdditiveArithmetic
extension UInt32x2: AdditiveArithmetic {
  @_transparent
  public static var zero: Self {
    self.init(rawValue: CUInt32x2MakeZero())
  }

  @_transparent
  public static func + (lhs: Self, rhs: Self) -> Self {
    self.init(rawValue: CUInt32x2Add(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func - (lhs: Self, rhs: Self) -> Self  {
    self.init(rawValue: CUInt32x2Subtract(lhs.rawValue, rhs.rawValue))
  }
}

// MARK: - Conformance to Numeric
extension UInt32x2: Numeric {
  public typealias Magnitude = Element.Magnitude

  @_alwaysEmitIntoClient
  public var magnitude: Magnitude {
    return indices.reduce(into: CUInt32x2GetElement(rawValue, 0)) {
      $0 = Swift.max($0, CUInt32x2GetElement(rawValue, $1))
    }
  }

  @_transparent
  public static func * (lhs: Self, rhs: Self) -> Self  {
    self.init(rawValue: CUInt32x2Multiply(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func *= (lhs: inout Self, rhs: Self) {
    lhs = lhs * rhs
  }

  @_transparent
  public init?<T>(exactly source: T) where T : BinaryInteger {
    guard let exactly = Element(exactly: source) else { return nil }
    self.init(rawValue: CUInt32x2MakeRepeatingElement(exactly))
  }
}

// MARK: - Bitwise
extension UInt32x2 {

  @_transparent
  public prefix static func ~ (operand: UInt32x2) -> UInt32x2 {
    self.init(rawValue: CUInt32x2BitwiseNot(operand.rawValue))
  }

  @_transparent
  public static func & (lhs: UInt32x2, rhs: UInt32x2) -> UInt32x2 {
    self.init(rawValue: CUInt32x2BitwiseAnd(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func | (lhs: UInt32x2, rhs: UInt32x2) -> UInt32x2 {
    self.init(rawValue: CUInt32x2BitwiseOr(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func ^ (lhs: UInt32x2, rhs: UInt32x2) -> UInt32x2 {
    self.init(rawValue: CUInt32x2BitwiseExclusiveOr(lhs.rawValue, rhs.rawValue))
  }

  // MARK: Shifting

  @_transparent
  public static func >> <RHS>(
    lhs: UInt32x2,
    rhs: RHS
  ) -> UInt32x2 where RHS: BinaryInteger {
    self.init(rawValue: CUInt32x2ShiftLeft(lhs.rawValue, numericCast(rhs)))
  }

  @_transparent
  public static func << <RHS>(
    lhs: UInt32x2,
    rhs: RHS
  ) -> UInt32x2 where RHS: BinaryInteger {
    self.init(rawValue: CUInt32x2ShiftRight(lhs.rawValue, numericCast(rhs)))
  }
}
