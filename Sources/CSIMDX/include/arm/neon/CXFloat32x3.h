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
/// @return `(CXFloat32x3){ element0, element1, element2, element3 }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Make(Float32 element0, Float32 element1, Float32 element2)
{
    return (CXFloat32x3){ element0, element1, element2, 0.f };
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXFloat32x3){ pointer[0], pointer[1], pointer[2], pointer[3] }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeLoad(const Float32* pointer)
{
    CXFloat32x3 storage = vld1q_f32(pointer);
    vsetq_lane_u32(0.f, storage, 3);
    return storage;
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXFloat32x3){ value, value, value, value }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeRepeatingElement(const Float32 value)
{
    CXFloat32x3 storage = vdupq_n_f32(value);
    vsetq_lane_u32(0.f, storage, 3);
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
/// @return `(CXFloat32x3){ 0.f, 0.f, 0.f, 0.f }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeZero(void)
{
    return CXFloat32x3MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x3GetElement(const CXFloat32x3 storage, const int index)
{
    return storage[index];
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXFloat32x3SetElement(CXFloat32x3* storage, const int index, const Float32 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x3){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]), ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3FromCXInt32x4(CXInt32x4 operand)
{
    return vcvtq_f32_s32(operand);
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x3){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]), ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3FromCXUInt32x4(CXUInt32x4 operand)
{
    return vcvtq_f32_u32(operand);
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXFloat32x3){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Minimum(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return vminq_f32(lhs, rhs);
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXFloat32x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Maximum(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return vmaxq_f32(lhs, rhs);
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CXFloat32x3){ -(operand[0]), -(operand[1]), -(operand[2]), -(operand[3]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Negate(const CXFloat32x3 operand)
{
    return vnegq_f32(operand);
}

/// Returns the absolute storage (element-wise).
/// @return `(CXFloat32x3){ abs(operand[0]), abs(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Absolute(const CXFloat32x3 operand)
{
    return vabsq_f32(operand);
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXFloat32x3){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Add(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return vaddq_f32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXFloat32x3){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Subtract(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return vsubq_f32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXFloat32x3){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Multiply(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return vmulq_f32(lhs, rhs);
}

/// Divides two storages (element-wise).
/// @return `(CXFloat32x3){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Divide(const CXFloat32x3 lhs, CXFloat32x3 rhs)
{
    vsetq_lane_f32(1.f, rhs, 3);
    return vdivq_f32(lhs, rhs);
}

/// Calculates the square root (element-wise).
/// @return `(CXFloat32x3){ sqrt(operand[0]), sqrt(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3SquareRoot(const CXFloat32x3 operand)
{
    return vsqrtq_f32(operand);
}
