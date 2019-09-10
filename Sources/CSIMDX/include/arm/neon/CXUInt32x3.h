#pragma once

#include "CXTypes_t.h"
#include "CXUInt32x4.h"

/// Returns an intrinsic initialized to the 3 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Make(UInt32 value0, UInt32 value1, UInt32 value2)
{
    return (CXUInt32x3){ value0, value1, value2, 0 };
}

/// Loads 3 x UInt32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 3 x UInt32 values
/// @return CXUInt32x3(pointer[0], pointer[1], pointer[2])
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3MakeLoad(const UInt32* pointer)
{
    CXUInt32x3 storage = vld1q_u32(pointer);
    vsetq_lane_u32(0, storage, 3);
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3MakeRepeatingElement(const UInt32 value)
{
    CXUInt32x3 storage = vdupq_n_u32(value);
    vsetq_lane_u32(0, storage, 3);
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3MakeZero(void)
{
    return CXUInt32x3MakeRepeatingElement(0);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(UInt32) CXUInt32x3GetElement(const CXUInt32x3 storage, const int index)
{
    return storage[index];
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXUInt32x3SetElement(CXUInt32x3* storage, const int index, const UInt32 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Arithmetics

/// Returns the given storage unchanged. Allows for symmetry with signed values.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Absolute(const CXUInt32x3 storage)
{
    return storage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Add(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return vaddq_u32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Subtract(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return vsubq_u32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Multiply(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return vmulq_u32(lhs, rhs);
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3BitwiseNot(const CXUInt32x3 operand)
{
    CXUInt32x3 storage = CXUInt32x4BitwiseNot(operand);
    vsetq_lane_u32(0, storage, 3);
    return storage;
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3BitwiseAnd(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return CXUInt32x4BitwiseAnd(lhs, rhs);
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3BitwiseAndNot(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return CXUInt32x3BitwiseAnd(CXUInt32x3BitwiseNot(lhs), rhs);
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3BitwiseOr(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return CXUInt32x4BitwiseOr(lhs, rhs);
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3BitwiseExclusiveOr(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return CXUInt32x4BitwiseExclusiveOr(lhs, rhs);
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3ShiftElementWiseLeft(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return CXUInt32x4ShiftElementWiseLeft(lhs, rhs);
}

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3ShiftLeft(const CXUInt32x3 lhs, const UInt32 rhs)
{
    return CXUInt32x4ShiftLeft(lhs, rhs);
}

/// Right-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3ShiftElementWiseRight(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return CXUInt32x4ShiftElementWiseRight(lhs, rhs);
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3ShiftRight(const CXUInt32x3 lhs, const UInt32 rhs)
{
    return CXUInt32x4ShiftRight(lhs, rhs);
}
