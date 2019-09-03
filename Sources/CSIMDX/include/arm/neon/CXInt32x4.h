#pragma once

#include "CXInt32_t.h"

// MARK: Designated Initializers

/// Returns an intrinsic initialized to the 4 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Make(Int32 value0, Int32 value1, Int32 value2, Int32 value3)
{
    return (CXInt32x4){ value0, value1, value2, value3 };
}

/// Loads 4 x Int32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 4 x Int32 values
/// @return CXInt32x4(pointer[0], pointer[1], pointer[2], pointer[3])
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeLoad(const Int32* pointer)
{
    return vld1q_s32(pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeRepeatingElement(const Int32 value)
{
    return vdupq_n_s32(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeZero(void)
{
    return CXInt32x4MakeRepeatingElement(0);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int32) CXInt32x4GetElement(const CXInt32x4 storage, const int index)
{
    return storage[index];
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXInt32x4SetElement(CXInt32x4* storage, const int index, const Int32 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Negate(const CXInt32x4 storage)
{
    return vnegq_s32(storage);
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Absolute(const CXInt32x4 storage)
{
    return vabsq_s32(storage);
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Add(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    return vaddq_s32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Subtract(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    return vsubq_s32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Multiply(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    return vmulq_s32(lhs, rhs);
}
