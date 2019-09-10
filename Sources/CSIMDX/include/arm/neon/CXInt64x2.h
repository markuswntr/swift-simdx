#pragma once

#include "CXTypes_t.h"

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Make(Int64 value0, Int64 value1)
{
    return (CXInt64x2){ value0, value1 };
}

/// Loads 2 x Int64 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Int64 values
/// @return CXInt64x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeLoad(const Int64* pointer)
{
    return vld1q_s64(pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeRepeatingElement(const Int64 value)
{
    return vdupq_n_s64(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeZero(void)
{
    return CXInt64x2MakeRepeatingElement(0L);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int64) CXInt64x2GetElement(const CXInt64x2 storage, const int index)
{
    return storage[index];  // TODO: Function call instead?
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXInt64x2SetElement(CXInt64x2* storage, const int index, const Int64 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Negate(const CXInt64x2 storage)
{
    return vnegq_s64(storage);
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXInt64x2Absolute(const CXInt64x2 storage)
{
    return vreinterpretq_u64_s64(vabsq_s64(storage));
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Add(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return vaddq_s64(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Subtract(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return vsubq_s64(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Multiply(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    // TODO: NEON does not have a native multiply intrinsic for storages with 64 bit ints
    return lhs * rhs;
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseNot(const CXInt64x2 operand)
{
    // TODO: NEON does not have a native bitwise not operation for storages with 64 bit ints
    return ~operand;
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseAnd(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return vandq_s64(lhs, rhs);
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseAndNot(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return CXInt64x2BitwiseAnd(CXInt64x2BitwiseNot(lhs), rhs);
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseOr(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return vorrq_s64(lhs, rhs);
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseExclusiveOr(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return veorq_s64(lhs, rhs);
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2ShiftElementWiseLeft(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return vshlq_s64(lhs, rhs);
}

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2ShiftLeft(const CXInt64x2 lhs, const Int64 rhs)
{
    return CXInt64x2ShiftElementWiseLeft(lhs, CXInt64x2MakeRepeatingElement(rhs));
}

/// Right-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2ShiftElementWiseRight(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return CXInt64x2ShiftElementWiseLeft(lhs, CXInt64x2Negate(rhs));
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2ShiftRight(const CXInt64x2 lhs, const Int64 rhs)
{
    return CXInt64x2ShiftElementWiseRight(lhs, CXInt64x2MakeRepeatingElement(rhs));
}
