#pragma once

#include "CXTypes_t.h"

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Make(UInt64 value0, UInt64 value1)
{
    return (CXUInt64x2){ value0, value1 };
}

/// Loads 2 x UInt64 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x UInt64 values
/// @return CXUInt64x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2MakeLoad(const UInt64* pointer)
{
    return vld1q_u64(pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2MakeRepeatingElement(const UInt64 value)
{
    return vdupq_n_u64(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2MakeZero(void)
{
    return CXUInt64x2MakeRepeatingElement(0L);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(UInt64) CXUInt64x2GetElement(const CXUInt64x2 storage, const int index)
{
    return storage[index];  // TODO: Function call instead?
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXUInt64x2SetElement(CXUInt64x2* storage, const int index, const UInt64 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Arithmetics

/// Returns the given storage unchanged. Allows for symmetry with signed values.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Absolute(const CXUInt64x2 storage)
{
    return storage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Add(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return vaddq_u64(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Subtract(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return vsubq_u64(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Multiply(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    // TODO: NEON does not have a native multiply intrinsic for storages with 64 bit ints
    return lhs * rhs;
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseNot(const CXUInt64x2 operand)
{
    // TODO: NEON does not have a native bitwise not operation for storages with 64 bit ints
    return ~operand;
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseAnd(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return vandq_u64(lhs, rhs);
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseAndNot(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return CXUInt64x2BitwiseAnd(CXUInt64x2BitwiseNot(lhs), rhs);
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseOr(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return vorrq_u64(lhs, rhs);
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseExclusiveOr(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return veorq_u64(lhs, rhs);
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2ShiftElementWiseLeft(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return vshlq_u64(lhs, rhs);
}

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2ShiftLeft(const CXUInt64x2 lhs, const UInt64 rhs)
{
    return CXUInt64x2ShiftElementWiseLeft(lhs, CXUInt64x2MakeRepeatingElement(rhs));
}

/// Right-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2ShiftElementWiseRight(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return vreinterpretq_s64_u64(vshlq_s64(vreinterpretq_s64_u64(lhs), vnegq_s64(vreinterpretq_s64_u64(rhs))));
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2ShiftRight(const CXUInt64x2 lhs, const UInt64 rhs)
{
    return CXUInt64x2ShiftElementWiseRight(lhs, CXUInt64x2MakeRepeatingElement(rhs));
}
