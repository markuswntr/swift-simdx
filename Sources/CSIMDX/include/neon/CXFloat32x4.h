#pragma once

#include "CXFloat32_t.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 4 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Make(Float32 value0, Float32 value1, Float32 value2, Float32 value3)
{
    return (CXFloat32x4){ value0, value1, value2, value3 };
}

/// Loads 4 x Float32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 4 x Float32 values
/// @return CXFloat32x4(pointer[0], pointer[1], pointer[2], pointer[3])
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeLoad(const Float32* pointer)
{
    return vld1q_f32(pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeRepeatingElement(const Float32 value)
{
    return vdupq_n_f32(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeZero(void)
{
    return CXFloat32x4MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x4GetElement(const CXFloat32x4 storage, const int index)
{
    return storage[index];
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXFloat32x4SetElement(CXFloat32x4* storage, const int index, const Float32 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Arithmetics

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Absolute(const CXFloat32x4 storage)
{
    return vabsq_f32(storage);
}

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Negate(const CXFloat32x4 storage)
{
    return vnegq_f32(storage);
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Add(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return vaddq_f32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Subtract(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return vsubq_f32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Multiply(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return vmulq_f32(lhs, rhs);
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Divide(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return vdivq_f32(lhs, rhs);
}
