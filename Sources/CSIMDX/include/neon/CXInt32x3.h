#pragma once

#include "CXInt32_t.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 3 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Make(Int32 value0, Int32 value1, Int32 value2)
{
    return (CXInt32x3){ value0, value1, value2, 0.f };
}

/// Loads 3 x Int32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 3 x Int32 values
/// @return CXInt32x3(pointer[0], pointer[1], pointer[2])
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeLoad(const Int32* pointer)
{
    CXInt32x3 storage = vld1q_s32(pointer);
    storage[3] = 0.f;
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeRepeatingElement(const Int32 value)
{
    return vdupq_n_s32(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeZero(void)
{
    return CXInt32x3MakeRepeatingElement(0);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int32) CXInt32x3GetElement(const CXInt32x3 storage, const int index)
{
    return storage[index];
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXInt32x3SetElement(CXInt32x3* storage, const int index, const Int32 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Arithmetics

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Absolute(const CXInt32x3 storage)
{
    return vabsq_s32(storage);
}

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Negate(const CXInt32x3 storage)
{
    return vnegq_s32(storage);
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Add(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return vaddq_s32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Subtract(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return vsubq_s32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Multiply(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return vmulq_s32(lhs, rhs);
}
