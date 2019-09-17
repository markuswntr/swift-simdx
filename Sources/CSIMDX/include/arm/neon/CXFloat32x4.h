// Copyright 2019 Markus Winter
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "CXTypes_t.h"

/// Initializes a storage to given elements, from least-significant to most-significant bits.
/// @return `(CXFloat32x4){ element0, element1, element2, element3 }`
STATIC_INLINE_INTRINSIC(CXFloat32x4)
CXFloat32x4Make(Float32 element0, Float32 element1, Float32 element2, Float32 element3)
{
    return (CXFloat32x4){ element0, element1, element2, element3 };
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXFloat32x4){ pointer[0], pointer[1], pointer[2], pointer[3] }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeLoad(const Float32* pointer)
{
    return vld1q_f32(pointer);
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXFloat32x4){ value, value, value, value }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeRepeatingElement(const Float32 value)
{
    return vdupq_n_f32(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
/// @return `(CXFloat32x4){ 0.f, 0.f, 0.f, 0.f }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeZero(void)
{
    return CXFloat32x4MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x4GetElement(const CXFloat32x4 storage, const int index)
{
    return storage[index];
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXFloat32x4SetElement(CXFloat32x4* storage, const int index, const Float32 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x4){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]), ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4FromCXInt32x4(CXInt32x4 operand)
{
    return vcvtq_f32_s32(operand);
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x4){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]), ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4FromCXUInt32x4(CXUInt32x4 operand)
{
    return vcvtq_f32_u32(operand);
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXFloat32x4){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Minimum(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return vminq_f32(lhs, rhs);
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXFloat32x4){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Maximum(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return vmaxq_f32(lhs, rhs);
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CXFloat32x4){ -(operand[0]), -(operand[1]), -(operand[2]), -(operand[3]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Negate(const CXFloat32x4 operand)
{
    return vnegq_f32(operand);
}

/// Returns the absolute storage (element-wise).
/// @return `(CXFloat32x4){ abs(operand[0]), abs(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Absolute(const CXFloat32x4 operand)
{
    return vabsq_f32(operand);
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXFloat32x4){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Add(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return vaddq_f32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXFloat32x4){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Subtract(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return vsubq_f32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXFloat32x4){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Multiply(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return vmulq_f32(lhs, rhs);
}

/// Divides two storages (element-wise).
/// @return `(CXFloat32x4){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Divide(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return vdivq_f32(lhs, rhs);
}

/// Calculates the square root (element-wise).
/// @return `(CXFloat32x4){ sqrt(operand[0]), sqrt(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4SquareRoot(const CXFloat32x4 operand)
{
    return vsqrtq_f32(operand);
}
