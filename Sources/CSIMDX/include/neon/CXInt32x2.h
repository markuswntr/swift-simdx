#pragma once

#include "CXInt32_t.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Make(Int32 value0, Int32 value1)
{
    return (CXInt32x2){ value0, value1 };
}

/// Loads 2 x Int32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Int32 values
/// @return CXInt32x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Load(const void* pointer)
{
    return vld1_s32((Int32*)pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2MakeRepeatingElement(const Int32 value)
{
    return vdup_n_s32(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2MakeZero(void)
{
    return CXInt32x2MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int32) CXInt32x2GetElement(const CXInt32x2 storage, const int index)
{
    return storage[index];
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXInt32x2SetElement(CXInt32x2* storage, const int index, const Int32 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: -  Arithmetics

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Absolute(CXInt32x2 storage)
{
    return vabs_s32(storage);
}

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Negate(const CXInt32x2 storage)
{
    return vneg_s32(storage);
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Add(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
    return vadd_s32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Subtract(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
    return vsub_s32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Multiply(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
    return vmul_s32(lhs, rhs);
}
