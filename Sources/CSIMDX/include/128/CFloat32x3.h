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

#pragma mark - Type def

/// The 3 x 32-bit floating point storage
///
/// These type is wrapping the intrinsic to avoid conflicts with the standard
/// libraries implementation of these intrinsic.
typedef union CFloat32x3_t
{
#if CSIMDX_ARM_NEON
  float32x4_t rawValue; // Most significant 32 bits are unused (zero)
#elif CSIMDX_X86_SSE2
  __m128 rawValue;      // Most significant 32 bits are unused (zero)
#endif
} CFloat32x3;

#pragma mark - Functions

/// Initializes a storage to given elements. Least- to most-significant bits.
/// @return `(CFloat32x3){ element0, element1, element2 }`
FORCE_INLINE(CFloat32x3) CFloat32x3Make(float element0, float element1, float element2)
{
  CFloat32x3 result;
#if CSIMDX_ARM_NEON
  result.rawValue = (float32x4_t){ element0, element1, element2, 0.f  };
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_setr_ps(element0, element1, element2, 0.f);
#endif
  return result;
}

/// Loads 2 x Float32 values from unaligned memory.
/// @return `(CFloat32x3){ pointer[0], pointer[1], pointer[2] }`
FORCE_INLINE(CFloat32x3) CFloat32x3MakeLoad(const float* pointer)
{
  CFloat32x3 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vld1q_f32(pointer);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_loadu_ps(pointer);
  result.rawValue[3] = 0.f; // zero-out the last 32 bits
#endif
  return result;
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CFloat32x3){ value, value, value }`
FORCE_INLINE(CFloat32x3) CFloat32x3MakeRepeatingElement(const float value)
{
  CFloat32x3 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vdupq_n_f32(value);
  vsetq_lane_u32(0.f, result.rawValue, 3); // zero-out the last 32 bits
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_set1_ps(value);
  result.rawValue[3] = 0.f; // zero-out the last 32 bits
#endif
  return result;
}

/// Returns an intrinsic type with all elements initialized to zero (0.f).
/// @return `(CFloat32x3){ 0.f, 0.f }`
FORCE_INLINE(CFloat32x3) CFloat32x3MakeZero(void)
{
#if CSIMDX_ARM_NEON
  return CFloat32x3MakeRepeatingElement(0.f);
#elif CSIMDX_X86_SSE2
  CFloat32x3 result;
  result.rawValue = _mm_setzero_ps();
  return result;
#endif
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
FORCE_INLINE(float) CFloat32x3GetElement(const CFloat32x3 storage, const int index)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_SSE2
  return ((float*)&(storage.rawValue))[index];
#endif
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
FORCE_INLINE(void) CFloat32x3SetElement(CFloat32x3* storage, const int index, const float value)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_SSE2
  (storage->rawValue)[index] = value;
#endif
}

// MARK: - Conversion

///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CFloat32x3){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]) }`
//FORCE_INLINE(CFloat32x3) CFloat32x3FromCXInt32x3(CXInt32x3 operand)
//{
//  CFloat32x3 result;
//#if CSIMDX_ARM_NEON
//    result.rawValue = vcvtq_f32_s32(operand.rawValue);
//#elif CSIMDX_X86_SSE2
//    result.rawValue = _mm_cvtepi32_ps(operand.rawValue);
//#endif
//  return result;
//}
//
///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CFloat32x3){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]) }`
//FORCE_INLINE(CFloat32x3) CFloat32x3FromCXUInt32x3(CXUInt32x3 operand)
//{
//  CFloat32x3 result;
//#if CSIMDX_ARM_NEON
//  result.rawValue = vcvtq_f32_u32(operand.rawValue);
//#elif CSIMDX_X86_SSE2
//  result.rawValue = _mm_cvtepi32_ps(operand.rawValue);
//#endif
//  return result;
//}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CFloat32x3){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1], ... }`
FORCE_INLINE(CFloat32x3) CFloat32x3Minimum(const CFloat32x3 lhs, const CFloat32x3 rhs)
{
  CFloat32x3 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vminq_f32(lhs.rawValue, rhs.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_min_ps(lhs.rawValue, rhs.rawValue);
#endif
  return result;
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CFloat32x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
FORCE_INLINE(CFloat32x3) CFloat32x3Maximum(const CFloat32x3 lhs, const CFloat32x3 rhs)
{
  CFloat32x3 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vmaxq_f32(lhs.rawValue, rhs.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_max_ps(lhs.rawValue, rhs.rawValue);
#endif
  return result;
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CFloat32x3){ -(operand[0]), -(operand[1]), -(operand[2]) }`
FORCE_INLINE(CFloat32x3) CFloat32x3Negate(const CFloat32x3 operand)
{
  CFloat32x3 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vnegq_f32(operand.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_sub_ps(CFloat32x2MakeZero().rawValue, operand.rawValue);
#endif
  return result;
}

/// Returns the absolute storage (element-wise).
/// @return `(CFloat32x3){ abs(operand[0]), abs(operand[1]) }`
FORCE_INLINE(CFloat32x3) CFloat32x3Absolute(const CFloat32x3 operand)
{
  CFloat32x3 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vabsq_f32(operand.rawValue);
#elif CSIMDX_X86_SSE2
  uint32_t SIGN_BIT = (uint32_t)(~(1 << 31));
  union { __m128 operand; __m128i signs; } Signed;
  Signed.signs = _mm_setr_epi32(SIGN_BIT, SIGN_BIT, SIGN_BIT, SIGN_BIT);
  result.rawValue = _mm_and_ps(operand.rawValue, Signed.operand);
#endif
  return result;
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CFloat32x3){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
FORCE_INLINE(CFloat32x3) CFloat32x3Add(const CFloat32x3 lhs, const CFloat32x3 rhs)
{
  CFloat32x3 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vaddq_f32(lhs.rawValue, rhs.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_add_ps(lhs.rawValue, rhs.rawValue);
#endif
  return result;
}

/// Subtracts a storage from another (element-wise).
/// @return `(CFloat32x3){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
FORCE_INLINE(CFloat32x3) CFloat32x3Subtract(const CFloat32x3 lhs, const CFloat32x3 rhs)
{
  CFloat32x3 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vsubq_f32(lhs.rawValue, rhs.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_sub_ps(lhs.rawValue, rhs.rawValue);
#endif
  return result;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CFloat32x3){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
FORCE_INLINE(CFloat32x3) CFloat32x3Multiply(const CFloat32x3 lhs, const CFloat32x3 rhs)
{
  CFloat32x3 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vmulq_f32(lhs.rawValue, rhs.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_mul_ps(lhs.rawValue, rhs.rawValue);
#endif
  return result;
}

/// Divides two storages (element-wise).
/// @return `(CFloat32x3){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
FORCE_INLINE(CFloat32x3) CFloat32x3Divide(const CFloat32x3 lhs, CFloat32x3 rhs)
{
#if CSIMDX_ARM_NEON_WITH_AARCH
  // Prepare the unused bits of the rhs value,
  // to avoid a division by zero, but 1 instead
  vsetq_lane_f32(1.f, rhs.rawValue, 3);
  CFloat32x3 result;
  result.rawValue = vdivq_f32(lhs.rawValue, rhs.rawValue);
  return result;
#elif CSIMDX_X86_SSE2
  // Prepare the unused bits of the rhs value,
  // to avoid a division by zero, but 1 instead
  CFloat32x3SetElement(&rhs, 3, 1.f);
  CFloat32x3 result;
  result.rawValue = _mm_div_ps(lhs.rawValue, rhs.rawValue);
  return result;
#elif CSIMDX_ARM_NEON
    return CFloat32x3Make(
        CFloat32x3GetElement(lhs, 0) / CFloat32x3GetElement(rhs, 0),
        CFloat32x3GetElement(lhs, 1) / CFloat32x3GetElement(rhs, 1),
        CFloat32x3GetElement(lhs, 2) / CFloat32x3GetElement(rhs, 2)
    );
#endif
}

// #include <math>
///// Calculates the square root (element-wise).
///// @return `(CFloat32x3){ sqrt(operand[0]), sqrt(operand[1]) }`
//FORCE_INLINE(CFloat32x3) CFloat32x3SquareRoot(const CFloat32x3 operand)
//{
//#if CSIMDX_ARM_NEON_WITH_AARCH
//  CFloat32x3 result;
//  result.rawValue = vsqrtq_f32(operand.rawValue);
//  return result;
//#elif CSIMDX_X86_SSE2
//  CFloat32x3 result;
//  result.rawValue = _mm_sqrt_ps(operand.rawValue);
//  return result;
//#elif CSIMDX_ARM_NEON
//    return CFloat32x2Make(
//        sqrtf(CFloat32x2GetElement(operand, 0)),
//        sqrtf(CFloat32x2GetElement(operand, 1))
//    );
//#endif
//}
