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

#pragma once

#include "CXTypes_t.h"
#include "CXInt32x4.h"

/// Returns an intrinsic initialized to the 4 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Make(UInt32 value0, UInt32 value1, UInt32 value2, UInt32 value3)
{
    return CXInt32x4Make(value0, value1, value2, value3);
}

/// Loads 4 x UInt32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 4 x UInt32 values
/// @return CXUInt32x4(pointer[0], pointer[1], pointer[2], pointer[3])
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4MakeLoad(const UInt32* pointer)
{
    return CXInt32x4MakeLoad((const Int32*)pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4MakeRepeatingElement(const UInt32 value)
{
    return CXInt32x4MakeRepeatingElement(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4MakeZero(void)
{
    return CXInt32x4MakeZero();
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(UInt32) CXUInt32x4GetElement(const CXUInt32x4 storage, const int index)
{
    return CXInt32x4GetElement(storage, index);
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXUInt32x4SetElement(CXUInt32x4* storage, const int index, const UInt32 value)
{
    return CXInt32x4SetElement(storage, index, value);
}

// MARK: - Arithmetics

/// Returns the given storage unchanged. Allows for symmetry with signed values.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Absolute(const CXUInt32x4 storage)
{
    return storage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Add(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return CXInt32x4Add(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Subtract(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return CXInt32x4Subtract(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Multiply(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return CXInt32x4Multiply(lhs, rhs);
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4BitwiseNot(const CXUInt32x4 operand)
{
    return CXInt32x4BitwiseNot(operand);
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4BitwiseAnd(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return CXInt32x4BitwiseAnd(lhs, rhs);
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4BitwiseAndNot(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return CXInt32x4BitwiseAndNot(lhs, rhs);
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4BitwiseOr(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return CXInt32x4BitwiseOr(lhs, rhs);
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4BitwiseExclusiveOr(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return CXInt32x4BitwiseExclusiveOr(lhs, rhs);
}

// MARK: Shifting

/// Left-shifts each 64-bit value in the 128-bit integer storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4ShiftLeft(const CXUInt32x4 lhs, const UInt32 rhs)
{
    return CXInt32x4ShiftLeft(lhs, rhs);
}

/// Right-shifts each 64-bit value in the 128-bit integer storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4ShiftRight(const CXUInt32x4 lhs, const UInt32 rhs)
{
    return CXInt32x4ShiftRight(lhs, rhs);
}
