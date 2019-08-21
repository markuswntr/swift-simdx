#pragma once

#include "CXFloat64_t.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Make(Float64 value0, Float64 value1)
{
    return (CXFloat64x2){ value0, value1 };
}

/// Loads 2 x Float64 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Float64 values
/// @return CXFloat64x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Load(const void* pointer)
{
    return vld1q_f64((Float64*)pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2MakeRepeatingElement(const Float64 value)
{
    return vdupq_n_f64(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2MakeZero(void)
{
    return CXFloat64x2MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Float64) CXFloat64x2GetElement(const CXFloat64x2 storage, const int index)
{
    return storage[index]; // TODO: vgetq_lane_f64(storage, index)?
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXFloat64x2SetElement(CXFloat64x2* storage, const int index, const Float64 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Arithmetics

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Absolute(CXFloat64x2 storage)
{
    return vabsq_f64(storage);
}

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Negate(const CXFloat64x2 storage)
{
    return vnegq_f64(storage);
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Add(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return vaddq_f64(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Subtract(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return vsubq_f64(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Multiply(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return vmulq_f64(lhs, rhs);
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Divide(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return vdivq_f64(lhs, rhs);
}
