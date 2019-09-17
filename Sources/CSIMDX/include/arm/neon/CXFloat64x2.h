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

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Make(Float64 value0, Float64 value1)
{
    return (CXFloat64x2){ value0, value1 };
}

/// Loads 2 x Float64 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Float64 values
/// @return CXFloat64x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2MakeLoad(const Float64* pointer)
{
    return vld1q_f64(pointer);
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

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat64x2){ (Float64)(operand[0]), (Float64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2FromCXFloat32x2(CXFloat32x2 operand)
{
    return vcvt_f64_f32(operand);
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat64x2){ (Float64)(operand[0]), (Float64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2FromCXInt32x2(CXInt32x2 operand)
{
    return CXFloat64x2FromCXFloat32x2(vreinterpret_f32_s32(operand));
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat64x2){ (Float64)(operand[0]), (Float64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2FromCXUInt32x2(CXUInt32x2 operand)
{
    return CXFloat64x2FromCXFloat32x2(vreinterpret_f32_u32(operand));
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat64x2){ (Float64)(operand[0]), (Float64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2FromCXInt64x2(CXInt64x2 operand)
{
    return vcvtq_f64_s64(operand);
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat64x2){ (Float64)(operand[0]), (Float64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2FromCXUInt64x2(CXUInt64x2 operand)
{
    return vcvtq_f64_u64(operand);
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXFloat64x2){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Minimum(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return vminq_f64(lhs, rhs);
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXFloat32x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Maximum(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return vmaxq_f64(lhs, rhs);
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Negate(const CXFloat64x2 storage)
{
    return vnegq_f64(storage);
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Absolute(const CXFloat64x2 storage)
{
    return vabsq_f64(storage);
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

/// Calculates the square root (element-wise).
/// @return `(CXFloat64x2){ sqrt(operand[0]), sqrt(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2SquareRoot(const CXFloat64x2 operand)
{
    return vsqrtq_f64(operand);
}
