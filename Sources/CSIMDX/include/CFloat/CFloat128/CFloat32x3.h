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

/// The 3 x 32-bit floating point storage
#if CSIMDX_ARM_NEON
typedef float32x4_t CFloat32x3; // Most significant 32 bits are unused (zero)
#elif CSIMDX_X86_SSE2
typedef __m128 CFloat32x3;      // Most significant 32 bits are unused (zero)
#else
typedef struct CFloat32x3_t {
  Float32 rawValue[4];          // Most significant 32 bits are unused (zero)
} CFloat32x3;
#endif

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
FORCE_INLINE(Float32)
CFloat32x3GetElement(const CFloat32x3 storage, const int index)
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
CFloat32x3SetElement(CFloat32x3* storage, const int index, const Float32 value)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_SSE2
  (*storage)[index] = value;
#else
  (storage->rawValue)[index] = value;
#endif
}

#pragma mark - Initialisation

/// Initializes a storage to given elements. Least- to most-significant bits.
/// @return `(CFloat32x3){ element0, element1, element2 }`
FORCE_INLINE(CFloat32x3)
CFloat32x3Make(Float32 element0, Float32 element1, Float32 element2)
{
#if CSIMDX_X86_SSE2
  return _mm_setr_ps(element0, element1, element2, 0.f);
#else
  return (CFloat32x3){ element0, element1, element2, 0.f };
#endif
}

/// Loads 2 x Float32 values from unaligned memory.
/// @return `(CFloat32x3){ pointer[0], pointer[1], pointer[2] }`
FORCE_INLINE(CFloat32x3) CFloat32x3MakeLoad(const Float32* pointer)
{
#if CSIMDX_ARM_NEON
  CFloat32x3 result = vld1q_f32(pointer);
  CFloat32x3SetElement(&result, 3, 0.f);
  return result;
#elif CSIMDX_X86_SSE2
  CFloat32x3 result = _mm_loadu_ps(pointer);
  CFloat32x3SetElement(&result, 3, 0.f);
  return result;
#else
  return CFloat32x3Make(pointer[0], pointer[1], pointer[2]);
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CFloat32x3){ value, value, value }`
FORCE_INLINE(CFloat32x3) CFloat32x3MakeRepeatingElement(const Float32 value)
{
#if CSIMDX_ARM_NEON
  CFloat32x3 result = vdupq_n_f32(value);
  CFloat32x3SetElement(&result, 3, 0.f);
  return result;
#elif CSIMDX_X86_SSE2
  CFloat32x3 result = _mm_set1_ps(value);
  CFloat32x3SetElement(&result, 3, 0.f);
  return result;
#else
  return (CFloat32x3){ value, value, value, 0.0 };
#endif
}

/// Returns an intrinsic type with all elements initialized to zero (0.f).
/// @return `(CFloat32x3){ 0.f, 0.f, 0.f }`
FORCE_INLINE(CFloat32x3) CFloat32x3MakeZero(void)
{
#if CSIMDX_ARM_NEON
  return vdupq_n_f32(0.f);
#elif CSIMDX_X86_SSE2
  return _mm_setzero_ps();
#else
  return (CFloat32x3){ 0.0, 0.0, 0.0, 0.0 };
#endif
}

// MARK: - Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns
/// the lesser of each pair in the result.
/// @return
///   (CFloat32x3){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1],
///     ...
///   }
FORCE_INLINE(CFloat32x3)
CFloat32x3Minimum(const CFloat32x3 lhs, const CFloat32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vminq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_min_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x3GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x3GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x3GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x3GetElement(rhs, 1);
  Float32 lhs2 = CFloat32x3GetElement(lhs, 2);
  Float32 rhs2 = CFloat32x3GetElement(rhs, 2);
  return CFloat32x3Make(lhs0 < rhs0 ? lhs0 : rhs0,
                        lhs1 < rhs1 ? lhs1 : rhs1,
                        lhs2 < rhs2 ? lhs2 : rhs2);
#endif
}

/// Performs element-by-element comparison of both storages and returns
/// the greater of each pair in the result.
/// @return
///   (CFloat32x3){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1],
///     ...
///   }
FORCE_INLINE(CFloat32x3)
CFloat32x3Maximum(const CFloat32x3 lhs, const CFloat32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vmaxq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_max_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x3GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x3GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x3GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x3GetElement(rhs, 1);
  Float32 lhs2 = CFloat32x3GetElement(lhs, 2);
  Float32 rhs2 = CFloat32x3GetElement(rhs, 2);
  return CFloat32x3Make(lhs0 > rhs0 ? lhs0 : rhs0,
                        lhs1 > rhs1 ? lhs1 : rhs1,
                        lhs2 > rhs2 ? lhs2 : rhs2);
#endif
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CFloat32x3){ -(operand[0]), -(operand[1]), -(operand[2]) }`
FORCE_INLINE(CFloat32x3) CFloat32x3Negate(const CFloat32x3 operand)
{
#if CSIMDX_ARM_NEON
  return vnegq_f32(operand);
#elif CSIMDX_X86_SSE2
  return _mm_sub_ps(CFloat32x3MakeZero(), operand);
#else
  return CFloat32x3Make(-CFloat32x3GetElement(operand, 0),
                        -CFloat32x3GetElement(operand, 1),
                        -CFloat32x3GetElement(operand, 2));
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CFloat32x3){ abs(operand[0]), abs(operand[1]), abs(operand[2]) }`
FORCE_INLINE(CFloat32x3) CFloat32x3Absolute(const CFloat32x3 operand)
{
#if CSIMDX_ARM_NEON
  return vabsq_f32(operand);
#elif CSIMDX_X86_SSE2
  uint32_t SIGN_BIT = (uint32_t)(~(1 << 31));
  union { __m128 operand; __m128i signs; } Signed;
  Signed.signs = _mm_setr_epi32(SIGN_BIT, SIGN_BIT, SIGN_BIT, SIGN_BIT);
  return _mm_and_ps(operand, Signed.operand);
#else
  return CFloat32x3Make(__builtin_fabsf(CFloat32x3GetElement(operand, 0)),
                        __builtin_fabsf(CFloat32x3GetElement(operand, 1)),
                        __builtin_fabsf(CFloat32x3GetElement(operand, 2)));
#endif
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CFloat32x3){ lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2] }`
FORCE_INLINE(CFloat32x3)
CFloat32x3Add(const CFloat32x3 lhs, const CFloat32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vaddq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_add_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x3GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x3GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x3GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x3GetElement(rhs, 1);
  Float32 lhs2 = CFloat32x3GetElement(lhs, 2);
  Float32 rhs2 = CFloat32x3GetElement(rhs, 2);
  return CFloat32x3Make(lhs0 + rhs0, lhs1 + rhs1, lhs2 + rhs2);
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CFloat32x3){ lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2] }`
FORCE_INLINE(CFloat32x3)
CFloat32x3Subtract(const CFloat32x3 lhs, const CFloat32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vsubq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_sub_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x3GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x3GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x3GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x3GetElement(rhs, 1);
  Float32 lhs2 = CFloat32x3GetElement(lhs, 2);
  Float32 rhs2 = CFloat32x3GetElement(rhs, 2);
  return CFloat32x3Make(lhs0 - rhs0, lhs1 - rhs1, lhs2 - rhs2);
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CFloat32x3){ lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2] }`
FORCE_INLINE(CFloat32x3)
CFloat32x3Multiply(const CFloat32x3 lhs, const CFloat32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vmulq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_mul_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x3GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x3GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x3GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x3GetElement(rhs, 1);
  Float32 lhs2 = CFloat32x3GetElement(lhs, 2);
  Float32 rhs2 = CFloat32x3GetElement(rhs, 2);
  return CFloat32x3Make(lhs0 * rhs0, lhs1 * rhs1, lhs2 * rhs2);
#endif
}

/// Divides two storages (element-wise).
/// @return `(CFloat32x3){ lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2] }`
FORCE_INLINE(CFloat32x3) CFloat32x3Divide(const CFloat32x3 lhs, CFloat32x3 rhs)
{
#if CSIMDX_ARM_NEON_AARCH64
  // Prepare the unused bits of the rhs value,
  // to avoid a division by zero, but 1 instead
  CFloat32x3SetElement(&rhs, 3, 1.f);
  return vdivq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  // Prepare the unused bits of the rhs value,
  // to avoid a division by zero, but 1 instead
  CFloat32x3SetElement(&rhs, 3, 1.f);
  return _mm_div_ps(lhs, rhs);
#else
  Float32 lhs0 = CFloat32x3GetElement(lhs, 0);
  Float32 rhs0 = CFloat32x3GetElement(rhs, 0);
  Float32 lhs1 = CFloat32x3GetElement(lhs, 1);
  Float32 rhs1 = CFloat32x3GetElement(rhs, 1);
  Float32 lhs2 = CFloat32x3GetElement(lhs, 2);
  Float32 rhs2 = CFloat32x3GetElement(rhs, 2);
  return CFloat32x3Make(lhs0 / rhs0, lhs1 / rhs1, lhs2 / rhs2);
#endif
}

/// Calculates the square root (element-wise).
/// @return (CFloat32x3){ sqrt(operand[0]), sqrt(operand[1]), sqrt(operand[2]) }
FORCE_INLINE(CFloat32x3) CFloat32x3SquareRoot(const CFloat32x3 operand)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vsqrtq_f32(operand);
#elif CSIMDX_X86_SSE2
  return _mm_sqrt_ps(operand);
#else
  return CFloat32x3Make(__builtin_sqrtf(CFloat32x3GetElement(operand, 0)),
                        __builtin_sqrtf(CFloat32x3GetElement(operand, 1)),
                        __builtin_sqrtf(CFloat32x3GetElement(operand, 2)));
#endif
}

// MARK: - Conversion

///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CFloat32x3){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]) }`
//FORCE_INLINE(CFloat32x3) CFloat32x3FromCXInt32x3(CXInt32x3 operand)
//{
//  CFloat32x3 result;
//#if CSIMDX_ARM_NEON
//    result.rawValue = vcvtq_f32_s32(operand);
//#elif CSIMDX_X86_SSE2
//    result.rawValue = _mm_cvtepi32_ps(operand);
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
//  result.rawValue = vcvtq_f32_u32(operand);
//#elif CSIMDX_X86_SSE2
//  result.rawValue = _mm_cvtepi32_ps(operand);
//#endif
//  return result;
//}

#undef Float32
