#pragma once

#include "CXTypes_t.h"

/// Returns an intrinsic initialized to the 4 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Make(UInt32 value0, UInt32 value1, UInt32 value2, UInt32 value3)
{
    return (CXUInt32x4){ value0, value1, value2, value3 };
}

/// Loads 4 x UInt32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 4 x UInt32 values
/// @return CXUInt32x4(pointer[0], pointer[1], pointer[2], pointer[3])
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4MakeLoad(const UInt32* pointer)
{
    return vld1q_u32(pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4MakeRepeatingElement(const UInt32 value)
{
    return vdupq_n_u32(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4MakeZero(void)
{
    return CXUInt32x4MakeRepeatingElement(0);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(UInt32) CXUInt32x4GetElement(const CXUInt32x4 storage, const int index)
{
    return storage[index];
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXUInt32x4SetElement(CXUInt32x4* storage, const int index, const UInt32 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
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
    return vaddq_u32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Subtract(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return vsubq_u32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Multiply(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return vmulq_u32(lhs, rhs);
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4BitwiseNot(const CXUInt32x4 operand)
{
    return vmvnq_u32(operand);
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4BitwiseAnd(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return vandq_u32(lhs, rhs);
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4BitwiseAndNot(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return CXUInt32x4BitwiseAnd(CXUInt32x4BitwiseNot(lhs), rhs);
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4BitwiseOr(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return vorrq_u32(lhs, rhs);
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4BitwiseExclusiveOr(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return veorq_u32(lhs, rhs);
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4ShiftElementWiseLeft(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return vshlq_u32(lhs, rhs);
}

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4ShiftLeft(const CXUInt32x4 lhs, const UInt32 rhs)
{
    return CXUInt32x4ShiftElementWiseLeft(lhs, CXUInt32x4MakeRepeatingElement(rhs));
}

/// Right-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4ShiftElementWiseRight(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    return vreinterpretq_s32_u32(vshlq_s32(vreinterpretq_s32_u32(lhs), vnegq_s32(vreinterpretq_s32_u32(rhs))));
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4ShiftRight(const CXUInt32x4 lhs, const UInt32 rhs)
{
    return CXUInt32x4ShiftElementWiseRight(lhs, CXUInt32x4MakeRepeatingElement(rhs));
}
