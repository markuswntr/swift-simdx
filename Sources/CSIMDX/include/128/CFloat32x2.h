// Copyright 2022 Markus Winter
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

/// The 2 x 32-bit floating point storage
///
/// These type is wrapping the intrinsic to avoid conflicts with the standard
/// libraries implementation of these intrinsic.
typedef union CFloat32x2_t
{
#if CSIMDX_ARM_NEON
  float32x2_t rawValue;
#elif CSIMDX_X86_SSE2
  __m128 rawValue; // Most significant 64 bits are unused (zero)
#endif
} CFloat32x2;

#pragma mark - Functions

/// Initializes a storage to given elements. Least- to most-significant bits.
/// @return `(CFloat32x2){ element0, element1 }`
FORCE_INLINE(CFloat32x2) CFloat32x2Make(float element0, float element1)
{
  CFloat32x2 result;
#if CSIMDX_ARM_NEON
  result.rawValue = (float32x2_t){ element0, element1 };
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_setr_ps(element0, element1, 0.f, 0.f);
#endif
  return result;
}

/// Loads 2 x Float32 values from unaligned memory.
/// @return `(CFloat32x2){ pointer[0], pointer[1] }`
FORCE_INLINE(CFloat32x2) CFloat32x2MakeLoad(const float* pointer)
{
  CFloat32x2 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vld1_f32(pointer);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_loadu_ps(pointer);
  result.rawValue[2] = result.rawValue[3] = 0.f; // zero-out the last 64 bits
#endif
  return result;
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CFloat32x2){ value, value }`
FORCE_INLINE(CFloat32x2) CFloat32x2MakeRepeatingElement(const float value)
{
  CFloat32x2 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vdup_n_f32(value);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_set1_ps(value);
  result.rawValue[2] = result.rawValue[3] = 0.f; // zero-out the last 64 bits
#endif
  return result;
}

/// Returns an intrinsic type with all elements initialized to zero (0.f).
/// @return `(CFloat32x2){ 0.f, 0.f }`
FORCE_INLINE(CFloat32x2) CFloat32x2MakeZero(void)
{
#if CSIMDX_ARM_NEON
  return CFloat32x2MakeRepeatingElement(0.f);
#elif CSIMDX_X86_SSE2
  CFloat32x2 result;
  result.rawValue = _mm_setzero_ps();
  return result;
#endif
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
FORCE_INLINE(float) CFloat32x2GetElement(const CFloat32x2 storage, const int index)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_SSE2
  return ((float*)&(storage.rawValue))[index];
#endif
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
FORCE_INLINE(void) CFloat32x2SetElement(CFloat32x2* storage, const int index, const float value)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_SSE2
  (storage->rawValue)[index] = value;
#endif
}

// MARK: - Conversion

///// Convert the elements of `operand`, load them in the new storage and return the result.
///// @returns `(CFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
//FORCE_INLINE(CFloat32x2) CFloat32x2FromCXFloat64x2(CXFloat64x2 operand)
//{
//
//#if CSIMDX_ARM_NEON
//  #if CSIMDX_ARM_NEON_WITH_AARCH64
//    CFloat32x2 result;
//    result.rawValue = vcvt_f32_f64(operand.rawValue);
//    return result;
//  #else
//    return CFloat32x2Make((float)(operand.rawValue[0]),
//                          (float)(operand.rawValue[1]));
//  #endif
//#elif CSIMDX_X86_SSE2
//  CFloat32x2 result;
//  result.rawValue = _mm_cvtpd_ps(operand.rawValue);
//  return result;
//#endif
//}
//
///// Convert the elements of `operand`, load them in the new storage and return the result.
///// @returns `(CFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
//FORCE_INLINE(CFloat32x2) CFloat32x2FromCXInt32x2(CXInt32x2 operand)
//{
//  CFloat32x2 result;
//#if CSIMDX_ARM_NEON
//  result.rawValue = vcvt_f32_s32(operand.rawValue);
//#elif CSIMDX_X86_SSE2
//  result.rawValue = _mm_cvtepi32_ps(operand.rawValue);
//#endif
//  return result;
//}
//
///// Convert the elements of `operand`, load them in the new storage and return the result.
///// @returns `(CFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
//FORCE_INLINE(CFloat32x2) CFloat32x2FromCXUInt32x2(CXUInt32x2 operand)
//{
//#if CSIMDX_ARM_NEON
//  CFloat32x2 result;
//  result.rawValue = vcvt_f32_u32(operand.rawValue);
//  return result;
//#elif CSIMDX_X86_SSE2
//  return CFloat32x2FromCXInt32x2(operand.rawValue);
//#endif
//}
//
///// Convert the elements of `operand`, load them in the new storage and return the result.
///// @returns `(CFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
//FORCE_INLINE(CFloat32x2) CFloat32x2FromCXInt64x2(CXInt64x2 operand)
//{
//#if CSIMDX_ARM_NEON
//  #if CSIMDX_ARM_NEON_WITH_AARCH64
//    return CFloat32x2FromCXFloat64x2(vreinterpretq_f64_s64(operand.rawValue));
//  #else
//    return CFloat32x2Make((float)(operand.rawValue[0]), (float)(operand.rawValue[1]));
//  #endif
//#elif CSIMDX_X86_SSE2
//  //  Only works for inputs in the range: [-2^51, 2^51]
//  /// https://stackoverflow.com/questions/41144668/how-to-efficiently-perform-double-int64-conversions-with-sse-avx
//  CXInt64x2 temp = _mm_add_epi64(operand.rawValue, _mm_castpd_si128(_mm_set1_pd(0x0018000000000000)));
//  CXFloat64x2 converted = _mm_sub_pd(_mm_castsi128_pd(temp), _mm_set1_pd(0x0018000000000000));
//  return CFloat32x2FromCXFloat64x2(converted);
//#endif
//}
//
///// Convert the elements of `operand`, load them in the new storage and return the result.
///// @returns `(CFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
//FORCE_INLINE(CFloat32x2) CFloat32x2FromCXUInt64x2(CXUInt64x2 operand)
//{
//#if CSIMDX_ARM_NEON
//  #if CSIMDX_ARM_NEON_WITH_AARCH64
//    return CFloat32x2FromCXFloat64x2(vreinterpretq_f64_u64(operand.rawValue));
//  #else
//    return CFloat32x2Make((Float32)(operand.rawValue[0]), (Float32)(operand.rawValue[1]));
//  #endif
//#elif CSIMDX_X86_SSE2
//  return CFloat32x2FromCXInt64x2(operand.rawValue);
//#endif
//}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CFloat32x2){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1] }`
FORCE_INLINE(CFloat32x2) CFloat32x2Minimum(const CFloat32x2 lhs, const CFloat32x2 rhs)
{
  CFloat32x2 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vmin_f32(lhs.rawValue, rhs.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_min_ps(lhs.rawValue, rhs.rawValue);
#endif
  return result;
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CFloat32x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
FORCE_INLINE(CFloat32x2) CFloat32x2Maximum(const CFloat32x2 lhs, const CFloat32x2 rhs)
{
  CFloat32x2 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vmax_f32(lhs.rawValue, rhs.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_max_ps(lhs.rawValue, rhs.rawValue);
#endif
  return result;
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CFloat32x2){ -(operand[0]), -(operand[1]) }`
FORCE_INLINE(CFloat32x2) CFloat32x2Negate(const CFloat32x2 operand)
{
  CFloat32x2 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vneg_f32(operand.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_sub_ps(CFloat32x2MakeZero().rawValue, operand.rawValue);
#endif
  return result;
}

/// Returns the absolute storage (element-wise).
/// @return `(CFloat32x2){ abs(operand[0]), abs(operand[1]) }`
FORCE_INLINE(CFloat32x2) CFloat32x2Absolute(const CFloat32x2 operand)
{
  CFloat32x2 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vabs_f32(operand.rawValue);
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
/// @return `(CFloat32x2){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
FORCE_INLINE(CFloat32x2) CFloat32x2Add(const CFloat32x2 lhs, const CFloat32x2 rhs)
{
  CFloat32x2 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vadd_f32(lhs.rawValue, rhs.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_add_ps(lhs.rawValue, rhs.rawValue);
#endif
  return result;
}

/// Subtracts a storage from another (element-wise).
/// @return `(CFloat32x2){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
FORCE_INLINE(CFloat32x2) CFloat32x2Subtract(const CFloat32x2 lhs, const CFloat32x2 rhs)
{
  CFloat32x2 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vsub_f32(lhs.rawValue, rhs.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_sub_ps(lhs.rawValue, rhs.rawValue);
#endif
  return result;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CFloat32x2){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
FORCE_INLINE(CFloat32x2) CFloat32x2Multiply(const CFloat32x2 lhs, const CFloat32x2 rhs)
{
  CFloat32x2 result;
#if CSIMDX_ARM_NEON
  result.rawValue = vmul_f32(lhs.rawValue, rhs.rawValue);
#elif CSIMDX_X86_SSE2
  result.rawValue = _mm_mul_ps(lhs.rawValue, rhs.rawValue);
#endif
  return result;
}

/// Divides two storages (element-wise).
/// @return `(CFloat32x2){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
FORCE_INLINE(CFloat32x2) CFloat32x2Divide(const CFloat32x2 lhs, CFloat32x2 rhs)
{
#if CSIMDX_ARM_NEON_WITH_AARCH
  CFloat32x2 result;
  result.rawValue = vdiv_f32(lhs.rawValue, rhs.rawValue);
  return result;
#elif CSIMDX_X86_SSE2
  // Prepare the unused bits of the rhs value,
  // to avoid a division by zero, but 1 instead
  CFloat32x2SetElement(&rhs, 2, 1.f);
  CFloat32x2SetElement(&rhs, 3, 1.f);
  CFloat32x2 result;
  result.rawValue = _mm_div_ps(lhs.rawValue, rhs.rawValue);
  return result;
#elif CSIMDX_ARM_NEON
    return CFloat32x2Make(
        CFloat32x2GetElement(lhs, 0) / CFloat32x2GetElement(rhs, 0),
        CFloat32x2GetElement(lhs, 1) / CFloat32x2GetElement(rhs, 1)
    );
#endif
}

// #include <math>
///// Calculates the square root (element-wise).
///// @return `(CFloat32x2){ sqrt(operand[0]), sqrt(operand[1]) }`
//FORCE_INLINE(CFloat32x2) CFloat32x2SquareRoot(const CFloat32x2 operand)
//{
//#if CSIMDX_ARM_NEON_WITH_AARCH
//  CFloat32x2 result;
//  result.rawValue = vsqrt_f32(operand.rawValue);
//  return result;
//#elif CSIMDX_X86_SSE2
//  CFloat32x2 result;
//  result.rawValue = _mm_sqrt_ps(operand.rawValue);
//  return result;
//#elif CSIMDX_ARM_NEON
//    return CFloat32x2Make(
//        sqrtf(CFloat32x2GetElement(operand, 0)),
//        sqrtf(CFloat32x2GetElement(operand, 1))
//    );
//#endif
//}
