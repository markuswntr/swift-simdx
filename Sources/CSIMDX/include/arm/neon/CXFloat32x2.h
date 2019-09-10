#pragma once

#include "CXTypes_t.h"

/// Initializes a storage to given elements, from least-significant to most-significant bits.
/// @return `(CXFloat32x2){ element0, element1 }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Make(Float32 element0, Float32 element1)
{
    return (CXFloat32x2){ element0, element1 };
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXFloat32x2){ pointer[0], pointer[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeLoad(const Float32* pointer)
{
    return vld1_f32(pointer);
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXFloat32x2){ value, value }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeRepeatingElement(const Float32 value)
{
    return vdup_n_f32(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
/// @return `(CXFloat32x2){ 0.f, 0.f }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeZero(void)
{
    return CXFloat32x2MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x2GetElement(const CXFloat32x2 storage, const int index)
{
    return storage[index];
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXFloat32x2SetElement(CXFloat32x2* storage, const int index, const Float32 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2FromCXFloat64x2(CXFloat64x2 operand)
{
    return vcvt_f32_f64(operand);
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2FromCXInt32x2(CXInt32x2 operand)
{
    return vcvt_f32_s32(operand);
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2FromCXUInt32x2(CXUInt32x2 operand)
{
    return vcvt_f32_u32(operand);
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2FromCXInt64x2(CXInt64x2 operand)
{
    return CXFloat32x2FromCXFloat64x2(vreinterpretq_f64_s64(operand));
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2FromCXUInt64x2(CXUInt64x2 operand)
{
    return CXFloat32x2FromCXFloat64x2(vreinterpretq_f64_u64(operand));
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXFloat32x2){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Minimum(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return vmin_f32(lhs, rhs);
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXFloat32x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Maximum(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return vmax_f32(lhs, rhs);
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CXFloat32x2){ -(operand[0]), -(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Negate(const CXFloat32x2 operand)
{
    return vneg_f32(operand);
}

/// Returns the absolute storage (element-wise).
/// @return `(CXFloat32x2){ abs(operand[0]), abs(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Absolute(const CXFloat32x2 operand)
{
    return vabs_f32(operand);
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXFloat32x2){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Add(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return vadd_f32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXFloat32x2){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Subtract(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return vsub_f32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXFloat32x2){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Multiply(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return vmul_f32(lhs, rhs);
}

/// Divides two storages (element-wise).
/// @return `(CXFloat32x2){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Divide(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return vdiv_f32(lhs, rhs);
}

/// Calculates the square root (element-wise).
/// @return `(CXFloat32x2){ sqrt(operand[0]), sqrt(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2SquareRoot(const CXFloat32x2 operand)
{
    return vsqrt_f32(operand);
}
