// Copyright 2019 Markus Winter
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

import Foundation
import CSIMDX

public struct Int64x2: RawStorage2, FixedWidthIntegerStorage, SignedIntegerStorage {

    // MARK: Collection Conformance

    public let startIndex: Int32 = 0

    public let endIndex: Int32 = 2

    // MARK: Raw Value Access

    public var rawValue: CXInt64x2

    @inlinable public subscript(index: Int32) -> Int64 {
        @inlinable set { CXInt64x2SetElement(&rawValue, index, newValue) }
        @inlinable get { CXInt64x2GetElement(rawValue, index) }
    }

    @inlinable public init(rawValue: CXInt64x2) {
        self.rawValue = rawValue
    }
}

// MARK: - Designated Initializer
extension Int64x2 {

    @inlinable public init(_ repeatingElement: Int64) {
        self.init(rawValue: CXInt64x2MakeRepeatingElement(repeatingElement))
    }

    @inlinable public init(_ index0: Int64, _ index1: Int64) {
        self.init(rawValue: CXInt64x2Make(index0, index1))
    }

    @inlinable public init(_ array: [Int64]) {
        var array = array
        self.init(rawValue: CXInt64x2MakeLoad(&array))
    }

    @inlinable public init<Other>(_ sequence: Other) where Other: Sequence, Other.Element == Int64 {
        self.init(Array(sequence))
    }
}

// MARK: - Comparison
extension Int64x2 {

    @inlinable public static func minimum(_ lhs: Int64x2, _ rhs: Int64x2) -> Int64x2 {
        .init(rawValue: CXInt64x2Minimum(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func maximum(_ lhs: Int64x2, _ rhs: Int64x2) -> Int64x2 {
        .init(rawValue: CXInt64x2Maximum(lhs.rawValue, rhs.rawValue))
    }
}

// MARK: - Bitwise
extension Int64x2 {

    @inlinable public  prefix static func ~ (operand: Int64x2) -> Int64x2 {
        return .init(rawValue: CXInt64x2BitwiseNot(operand.rawValue))
    }

    @inlinable public static func & (lhs: Int64x2, rhs: Int64x2) -> Int64x2 {
        return .init(rawValue: CXInt64x2BitwiseAnd(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func | (lhs: Int64x2, rhs: Int64x2) -> Int64x2 {
        return .init(rawValue: CXInt64x2BitwiseOr(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func ^ (lhs: Int64x2, rhs: Int64x2) -> Int64x2 {
        return .init(rawValue: CXInt64x2BitwiseExclusiveOr(lhs.rawValue, rhs.rawValue))
    }

    // MARK: Shifting

    @inlinable public static func >> <RHS>(lhs: Int64x2, rhs: RHS) -> Int64x2 where RHS: BinaryInteger {
        return .init(rawValue: CXInt64x2ShiftLeft(lhs.rawValue, numericCast(rhs)))
    }

    @inlinable public static func << <RHS>(lhs: Int64x2, rhs: RHS) -> Int64x2 where RHS: BinaryInteger {
        return .init(rawValue: CXInt64x2ShiftRight(lhs.rawValue, numericCast(rhs)))
    }
}

// MARK: - Arithmetics
extension Int64x2 {

    @inlinable public static var zero: Int64x2 { .init(rawValue: CXInt64x2MakeZero()) }

    @inlinable public var magnitude: UInt64x2 { .init(rawValue: CXInt64x2Absolute(rawValue)) }

    // MARK: Additive

    @inlinable public static func + (lhs: Int64x2, rhs: Int64x2) -> Int64x2 {
        .init(rawValue: CXInt64x2Add(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static func - (lhs: Int64x2, rhs: Int64x2) -> Int64x2  {
        .init(rawValue: CXInt64x2Subtract(lhs.rawValue, rhs.rawValue))
    }

    @inlinable public static prefix func - (operand: Int64x2) -> Int64x2  {
        .init(rawValue: CXInt64x2Negate(operand.rawValue))
    }

    @inlinable public mutating func negate() {
        rawValue = CXInt64x2Negate(rawValue)
    }

    // MARK: Multiplicative

    @inlinable public static func * (lhs: Int64x2, rhs: Int64x2) -> Int64x2  {
        .init(rawValue: CXInt64x2Multiply(lhs.rawValue, rhs.rawValue))
    }
}
