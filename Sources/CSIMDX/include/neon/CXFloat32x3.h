#pragma once

#include "CXFloat32_t.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 3 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Make(Float32 value0, Float32 value1, Float32 value2)
{
    return (CXFloat32x4){ value0, value1, value2, 0.f };
}

/// Loads 3 x Float32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 3 x Float32 values
/// @return CXFloat32x3(pointer[0], pointer[1], pointer[2])
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Load(const void* pointer)
{
    CXFloat32x3 storage = vld1q_f32((Float32*)pointer);
    storage[3] = 0.f;
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeRepeatingElement(const Float32 value)
{
    return vdupq_n_f32(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeZero(void)
{
    return CXFloat32x3MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x3GetElement(const CXFloat32x3 storage, const int index)
{
    return storage[index];
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXFloat32x3SetElement(CXFloat32x3* storage, const int index, const Float32 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Arithmetics

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Absolute(CXFloat32x3 storage)
{
    return vabsq_f32(storage);
}

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Negate(const CXFloat32x3 storage)
{
    return vnegq_f32(storage);
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Add(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return vaddq_f32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Subtract(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return vsubq_f32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Multiply(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return vmulq_f32(lhs, rhs);
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Divide(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return vdivq_f32(lhs, rhs);
}
