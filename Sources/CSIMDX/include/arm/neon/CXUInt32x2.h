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

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Make(UInt32 value0, UInt32 value1)
{
    return (CXUInt32x2){ value0, value1 };
}

/// Loads 2 x UInt32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x UInt32 values
/// @return CXUInt32x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2MakeLoad(const UInt32* pointer)
{
    return vld1_u32(pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2MakeRepeatingElement(const UInt32 value)
{
    return vdup_n_u32(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2MakeZero(void)
{
    return CXUInt32x2MakeRepeatingElement(0);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(UInt32) CXUInt32x2GetElement(const CXUInt32x2 storage, const int index)
{
    return storage[index];
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXUInt32x2SetElement(CXUInt32x2* storage, const int index, const UInt32 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: -  Arithmetics

/// Returns the given storage unchanged. Allows for symmetry with signed values.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Absolute(const CXUInt32x2 storage)
{
    return storage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Add(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return vadd_u32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Subtract(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return vsub_u32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Multiply(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return vmul_u32(lhs, rhs);
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseNot(const CXUInt32x2 operand)
{
    return vmvn_u32(operand);
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseAnd(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return vand_u32(lhs, rhs);
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseAndNot(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return CXUInt32x2BitwiseAnd(CXUInt32x2BitwiseNot(lhs), rhs);
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseOr(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return vorr_u32(lhs, rhs);
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseExclusiveOr(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return veor_u32(lhs, rhs);
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2ShiftElementWiseLeft(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return vshl_u32(lhs, rhs);
}

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2ShiftLeft(const CXUInt32x2 lhs, const UInt32 rhs)
{
    return CXUInt32x2ShiftElementWiseLeft(lhs, CXUInt32x2MakeRepeatingElement(rhs));
}

/// Right-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2ShiftElementWiseRight(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return vreinterpret_s32_u32(vshl_s32(vreinterpret_s32_u32(lhs), vneg_s32(vreinterpret_s32_u32(rhs))));
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2ShiftRight(const CXUInt32x2 lhs, const UInt32 rhs)
{
    return CXUInt32x2ShiftElementWiseRight(lhs, CXUInt32x2MakeRepeatingElement(rhs));
}
