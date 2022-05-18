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

public struct Int32x2: SIMDXStorage, SIMDX2Storage {
  public typealias RawValue = CInt32x2
  public typealias Element = Int32

  @_alwaysEmitIntoClient
  public var rawValue: RawValue

  @_alwaysEmitIntoClient
  public init(rawValue: RawValue) {
    self.rawValue = rawValue
  }
}

// MARK: - Additional Initializers
extension Int32x2: ExpressibleByIntegerLiteral {
  @_transparent
  public init(_ index0: Element, _ index1: Element) {
    self.init(rawValue: CInt32x2Make(index0, index1))
  }

  @_transparent
  public init(repeating repeatingElement: Element) {
    self.init(rawValue: CInt32x2MakeRepeatingElement(repeatingElement))
  }

  @_transparent
  public init(_ array: [Int32]) {
    precondition(array.count == 2, "Array must contain exactly 2 elements")
    var array = array
    self.init(rawValue: CInt32x2MakeLoad(&array))
  }
}

// MARK: - Conformance to MutableCollection
extension Int32x2 {
  public subscript(index: Index) -> Element {
    @_transparent set {
      precondition(indices.contains(index))
      CInt32x2SetElement(&rawValue, index, newValue)
    }
    @_transparent get {
      precondition(indices.contains(index))
      return CInt32x2GetElement(rawValue, index)
    }
  }
}

// MARK: - Conformance to Equatable
extension Int32x2: Equatable {
  @_transparent
  public static func == (lhs: Self, rhs: Self) -> Bool {
    #warning("TODO: Broadcast to other storages")
    let cmp = CInt32x2CompareElementWise(lhs.rawValue, rhs.rawValue)
    return lhs.indices.allSatisfy { CInt32x2GetElement(cmp, $0) != .zero }
  }
}

// MARK: - Conformance to Hashable
extension Int32x2: Hashable {
  public func hash(into hasher: inout Hasher) {
    hasher.combine(CInt32x2GetElement(rawValue, 0))
    hasher.combine(CInt32x2GetElement(rawValue, 1))
  }
}

// MARK: - Conformance to AdditiveArithmetic
extension Int32x2: AdditiveArithmetic {
  @_transparent
  public static var zero: Self {
    self.init(rawValue: CInt32x2MakeZero())
  }

  @_transparent
  public static func + (lhs: Self, rhs: Self) -> Self {
    self.init(rawValue: CInt32x2Add(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func - (lhs: Self, rhs: Self) -> Self  {
    self.init(rawValue: CInt32x2Subtract(lhs.rawValue, rhs.rawValue))
  }
}

// MARK: - Conformance to Numeric
extension Int32x2: Numeric {
  public typealias Magnitude = Element.Magnitude

  @_alwaysEmitIntoClient
  public var magnitude: Magnitude {
    UInt32(indices.reduce(into: self[0]) { $0 = Swift.max($0, self[$1]) })
  }

  @_transparent
  public static func * (lhs: Self, rhs: Self) -> Self  {
    self.init(rawValue: CInt32x2Multiply(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func *= (lhs: inout Self, rhs: Self) {
    lhs = lhs * rhs
  }

  @_transparent
  public init?<T>(exactly source: T) where T : BinaryInteger {
    guard let exactly = Element(exactly: source) else { return nil }
    self.init(rawValue: CInt32x2MakeRepeatingElement(exactly))
  }
}

// MARK: - Conformace to SignedNumeric
extension Int32x2: SignedNumeric {
  @_transparent
  public static prefix func - (operand: Self) -> Self  {
    self.init(rawValue: CInt32x2Negate(operand.rawValue))
  }

  @_transparent
  public mutating func negate() {
    rawValue = CInt32x2Negate(rawValue)
  }
}

// MARK: - Bitwise
extension Int32x2 {

  @_transparent
  public prefix static func ~ (operand: Int32x2) -> Int32x2 {
    self.init(rawValue: CInt32x2BitwiseNot(operand.rawValue))
  }

  @_transparent
  public static func & (lhs: Int32x2, rhs: Int32x2) -> Int32x2 {
    self.init(rawValue: CInt32x2BitwiseAnd(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func | (lhs: Int32x2, rhs: Int32x2) -> Int32x2 {
    self.init(rawValue: CInt32x2BitwiseOr(lhs.rawValue, rhs.rawValue))
  }

  @_transparent
  public static func ^ (lhs: Int32x2, rhs: Int32x2) -> Int32x2 {
    self.init(rawValue: CInt32x2BitwiseExclusiveOr(lhs.rawValue, rhs.rawValue))
  }

  // MARK: Shifting

  @_transparent
  public static func >> <RHS>(
    lhs: Int32x2,
    rhs: RHS
  ) -> Int32x2 where RHS: BinaryInteger {
    self.init(rawValue: CInt32x2ShiftLeft(lhs.rawValue, numericCast(rhs)))
  }

  @_transparent
  public static func << <RHS>(
    lhs: Int32x2,
    rhs: RHS
  ) -> Int32x2 where RHS: BinaryInteger {
    self.init(rawValue: CInt32x2ShiftRight(lhs.rawValue, numericCast(rhs)))
  }
}
