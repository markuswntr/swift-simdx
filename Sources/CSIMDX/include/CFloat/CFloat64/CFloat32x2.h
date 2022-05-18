// Copyright 2019-2022 Markus Winter
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

/// The 32-bit floating point element
#define Float32 float

/// The 2 x 32-bit floating point storage
#if CSIMDX_ARM_NEON
typedef float32x2_t CFloat32x2;
#elif CSIMDX_X86_SSE2
typedef __m128 CFloat32x2; // Most significant 64-bits are unused.
#else
typedef struct CFloat32x2_t {
  Float32 rawValue[2];
} CFloat32x2;
#endif

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
FORCE_INLINE(Float32)
CFloat32x2GetElement(const CFloat32x2 storage, const int index)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_SSE2
  return storage[index];
#else
  return storage.rawValue[index];
#endif
}

/// Sets the element at `index` from `storage` to given value,
/// i.e. `(*storage)[index] = value;`
FORCE_INLINE(void)
CFloat32x2SetElement(CFloat32x2* storage, const int index, const Float32 value)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_SSE2
  (*storage)[index] = value;
#else
  (storage->rawValue)[index] = value;
#endif
}

#pragma mark - Initialisation

/// Initializes a storage to given elements. Least- to most-significant bits.
/// @return `(CFloat32x2){ element0, element1 }`
FORCE_INLINE(CFloat32x2) CFloat32x2Make(Float32 element0, Float32 element1)
{
#if CSIMDX_X86_SSE2
  return _mm_setr_ps(element0, element1, 0.f, 0.f);
#else
  return (CFloat32x2){ element0, element1 };
#endif
}

/// Loads 2 x Float32 values from unaligned memory.
/// @return `(CFloat32x2){ pointer[0], pointer[1] }`
FORCE_INLINE(CFloat32x2) CFloat32x2MakeLoad(const Float32* pointer)
{
#if CSIMDX_ARM_NEON
  return vld1_f32(pointer);
#elif CSIMDX_X86_SSE2
  CFloat32x2 result = _mm_loadu_ps(pointer);
  CFloat32x2SetElement(&result, 2, 0.f); // The last 64 bits ...
  CFloat32x2SetElement(&result, 3, 0.f); // ... are unused, but zero.
  return result;
#else
  return (CFloat32x2){ pointer[0], pointer[1] };
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CFloat32x2){ value, value }`
FORCE_INLINE(CFloat32x2) CFloat32x2MakeRepeatingElement(const Float32 value)
{
#if CSIMDX_ARM_NEON
  return vdup_n_f32(value);
#elif CSIMDX_X86_SSE2
  CFloat32x2 result = _mm_set1_ps(value);
  CFloat32x2SetElement(&result, 2, 0.f); // The last 64 bits ...
  CFloat32x2SetElement(&result, 3, 0.f); // ... are unused, but zero.
  return result;
#else
  return (CFloat32x2){ value, value };
#endif
}

/// Returns an intrinsic type with all elements initialized to zero (0.f).
/// @return `(CFloat32x2){ 0.f, 0.f }`
FORCE_INLINE(CFloat32x2) CFloat32x2MakeZero(void)
{
#if CSIMDX_ARM_NEON
  return vdup_n_f32(0.f);
#elif CSIMDX_X86_SSE2
  return _mm_setzero_ps();
#else
  return (CFloat32x2){ 0.0, 0.0 };
#endif
}

// MARK: - Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns
/// the lesser of each pair in the result.
/// @return
///   (CFloat32x2){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1]
///   }
FORCE_INLINE(CFloat32x2)
CFloat32x2Minimum(const CFloat32x2 lhs, const CFloat32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vmin_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_min_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x2GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x2GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x2GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x2GetElement(rhs, 1);
  return CFloat32x2Make(lhs0 < rhs0 ? lhs0 : rhs0,
                        lhs1 < rhs1 ? lhs1 : rhs1);
#endif
}

/// Performs element-by-element comparison of both storages and returns
/// the greater of each pair in the result.
/// @return
///   (CFloat32x3){
///     lhs[0] > rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] > rhs[1] ? lhs[1] : rhs[1]
///   }
FORCE_INLINE(CFloat32x2)
CFloat32x2Maximum(const CFloat32x2 lhs, const CFloat32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vmax_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_max_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x2GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x2GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x2GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x2GetElement(rhs, 1);
  return CFloat32x2Make(lhs0 > rhs0 ? lhs0 : rhs0,
                        lhs1 > rhs1 ? lhs1 : rhs1);
#endif
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CFloat32x2){ -(operand[0]), -(operand[1]) }`
FORCE_INLINE(CFloat32x2) CFloat32x2Negate(const CFloat32x2 operand)
{
#if CSIMDX_ARM_NEON
  return vneg_f32(operand);
#elif CSIMDX_X86_SSE2
  return _mm_sub_ps(CFloat32x2MakeZero(), operand);
#else
  return CFloat32x2Make(-CFloat32x2GetElement(operand, 0),
                        -CFloat32x2GetElement(operand, 1));
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CFloat32x2){ abs(operand[0]), abs(operand[1]) }`
FORCE_INLINE(CFloat32x2) CFloat32x2Absolute(const CFloat32x2 operand)
{
#if CSIMDX_ARM_NEON
  return vabs_f32(operand);
#elif CSIMDX_X86_SSE2
  uint32_t SIGN_BIT = (uint32_t)(~(1 << 31));
  union { __m128 operand; __m128i signs; } Signed;
  Signed.signs = _mm_setr_epi32(SIGN_BIT, SIGN_BIT, SIGN_BIT, SIGN_BIT);
  return _mm_and_ps(operand, Signed.operand);
#else
  return CFloat32x2Make(__builtin_fabsf(CFloat32x2GetElement(operand, 0)),
                        __builtin_fabsf(CFloat32x2GetElement(operand, 1)));
#endif
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CFloat32x2){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
FORCE_INLINE(CFloat32x2)
CFloat32x2Add(const CFloat32x2 lhs, const CFloat32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vadd_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_add_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x2GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x2GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x2GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x2GetElement(rhs, 1);
  return CFloat32x2Make(lhs0 + rhs0, lhs1 + rhs1);
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CFloat32x2){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
FORCE_INLINE(CFloat32x2)
CFloat32x2Subtract(const CFloat32x2 lhs, const CFloat32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vsub_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_sub_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x2GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x2GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x2GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x2GetElement(rhs, 1);
  return CFloat32x2Make(lhs0 - rhs0, lhs1 - rhs1);
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CFloat32x2){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
FORCE_INLINE(CFloat32x2)
CFloat32x2Multiply(const CFloat32x2 lhs, const CFloat32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vmul_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_mul_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x2GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x2GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x2GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x2GetElement(rhs, 1);
  return CFloat32x2Make(lhs0 * rhs0, lhs1 * rhs1);
#endif
}

/// Divides two storages (element-wise).
/// @return `(CFloat32x2){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
FORCE_INLINE(CFloat32x2) CFloat32x2Divide(const CFloat32x2 lhs, CFloat32x2 rhs)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vdiv_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  // Prepare the unused bits of the rhs value,
  // to avoid a division by zero, but 1 instead
  CFloat32x2SetElement(&rhs, 2, 1.f);
  CFloat32x2SetElement(&rhs, 3, 1.f);
  return _mm_div_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x2GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x2GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x2GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x2GetElement(rhs, 1);
  return CFloat32x2Make(lhs0 / rhs0, lhs1 / rhs1);
#endif
}

/// Calculates the square root (element-wise).
/// @return `(CFloat32x2){ sqrt(operand[0]), sqrt(operand[1]) }`
FORCE_INLINE(CFloat32x2) CFloat32x2SquareRoot(const CFloat32x2 operand)
{
  CFloat32x2 result;
#if CSIMDX_ARM_NEON_AARCH64
  return vsqrt_f32(operand);
#elif CSIMDX_X86_SSE2
  return _mm_sqrt_ps(operand);
#else
  return CFloat32x2Make(__builtin_sqrtf(CFloat32x2GetElement(operand, 0)),
                        __builtin_sqrtf(CFloat32x2GetElement(operand, 1)));
#endif
  return result;
}

// MARK: - Conversion

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
//  #if CSIMDX_ARM_NEON_AARCH64
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
//  #if CSIMDX_ARM_NEON_AARCH64
//    return CFloat32x2FromCXFloat64x2(vreinterpretq_f64_u64(operand.rawValue));
//  #else
//    return CFloat32x2Make((Float32)(operand.rawValue[0]), (Float32)(operand.rawValue[1]));
//  #endif
//#elif CSIMDX_X86_SSE2
//  return CFloat32x2FromCXInt64x2(operand.rawValue);
//#endif
//}

#undef Float32
