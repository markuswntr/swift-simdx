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

/// The 4 x 32-bit floating point storage
#if CSIMDX_ARM_NEON
typedef float32x4_t CFloat32x4;
#elif CSIMDX_X86_SSE2
typedef __m128 CFloat32x4;
#else
typedef struct CFloat32x4_t {
  CFloat32x2 lo, hi;
} CFloat32x4;
#endif

#pragma mark - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
FORCE_INLINE(Float32)
CFloat32x4GetElement(const CFloat32x4 storage, const int index)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_AVX
  return ((Float32*)&(storage))[index];
#else
  union { CFloat32x4 storage; Float32 rawValue[4]; } Union;
  Union.storage = storage;
  return Union.rawValue[index];
#endif
}

/// Sets the element at `index` from `storage` to given value,
/// i.e. `(*storage)[index] = value;`
FORCE_INLINE(void)
CFloat32x4SetElement(CFloat32x4* storage, const int index, const Float32 value)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_AVX
  ((Float32*)storage)[index] = value;
#else
  union { CFloat32x4* storage; Float32* rawValue; } Union;
  Union.storage = storage;
  Union.rawValue[index] = value;
#endif
}

#pragma mark - Initialisation

/// Initializes a storage to given elements. Least- to most-significant bits.
/// @return `(CFloat32x4){ element0, element1, element2, element3 }`
FORCE_INLINE(CFloat32x4)
CFloat32x4Make(Float32 element0, Float32 element1,
               Float32 element2, Float32 element3)
{
#if CSIMDX_X86_SSE2
  return _mm_setr_ps(element0, element1, element2, element3);
#else
  return (CFloat32x4){ element0, element1, element2, element3 };
#endif
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CFloat32x4){ pointer[0], pointer[1], pointer[2], pointer[3] }`
FORCE_INLINE(CFloat32x4) CFloat32x4MakeLoad(const Float32* pointer)
{
#if CSIMDX_ARM_NEON
  return vld1q_f32(pointer);
#elif CSIMDX_X86_SSE2
  return _mm_loadu_ps(pointer);
#else
  return (CFloat32x4) {
    CFloat32x2MakeLoad(pointer),
    CFloat32x2MakeLoad(&pointer[2])
  };
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CFloat32x4){ value, value, value, value }`
FORCE_INLINE(CFloat32x4) CFloat32x4MakeRepeatingElement(const Float32 value)
{
#if CSIMDX_ARM_NEON
  return vdupq_n_f32(value);
#elif CSIMDX_X86_SSE2
  return _mm_set1_ps(value);
#else
  return (CFloat32x4) {
    CFloat32x2MakeRepeatingElement(value),
    CFloat32x2MakeRepeatingElement(value)
  };
#endif
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
/// @return `(CFloat32x4){ 0.f, 0.f, 0.f, 0.f }`
FORCE_INLINE(CFloat32x4) CFloat32x4MakeZero(void)
{
#if CSIMDX_ARM_NEON
  return vdupq_n_f32(0.f);
#elif CSIMDX_X86_SSE2
  return _mm_setzero_ps();
#else
  return (CFloat32x4) {
    CFloat32x2MakeRepeatingElement(0.f),
    CFloat32x2MakeRepeatingElement(0.f)
  };
#endif
}

#pragma mark Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns
/// the lesser of each pair in the result.
/// @return
///   (CFloat32x4){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1],
///     ...
///   }
FORCE_INLINE(CFloat32x4)
CFloat32x4Minimum(const CFloat32x4 lhs, const CFloat32x4 rhs)
{
#if CSIMDX_ARM_NEON
  return vminq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_min_ps(lhs, rhs);
#else
  return (CFloat32x4) {
    CFloat32x2Minimum(lhs.lo, rhs.lo),
    CFloat32x2Minimum(lhs.hi, rhs.hi)
  };
#endif
}

/// Performs element-by-element comparison of both storages and returns
/// the greater of each pair in the result.
/// @return
///   (CFloat32x4){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1],
///     ...
///   }
FORCE_INLINE(CFloat32x4)
CFloat32x4Maximum(const CFloat32x4 lhs, const CFloat32x4 rhs)
{
#if CSIMDX_ARM_NEON
  return vmaxq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_max_ps(lhs, rhs);
#else
  return (CFloat32x4) {
    CFloat32x2Maximum(lhs.lo, rhs.lo),
    CFloat32x2Maximum(lhs.hi, rhs.hi)
  };
#endif
}

#pragma mark - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CFloat32x4){ -(operand[0]), -(operand[1]), -(operand[2]), -(operand[3]) }`
FORCE_INLINE(CFloat32x4) CFloat32x4Negate(const CFloat32x4 operand)
{
#if CSIMDX_ARM_NEON
  return vnegq_f32(operand);
#elif CSIMDX_X86_SSE2
  return _mm_sub_ps(CFloat32x4MakeZero(), operand);
#else
  return (CFloat32x4) {
    CFloat32x2Negate(operand.lo),
    CFloat32x2Negate(operand.hi)
  };
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CFloat32x4){ abs(operand[0]), abs(operand[1]) }`
FORCE_INLINE(CFloat32x4) CFloat32x4Magnitude(const CFloat32x4 operand)
{
#if CSIMDX_ARM_NEON
  return vabsq_f32(operand);
#elif CSIMDX_X86_SSE2
  uint32_t SIGN_BIT = (uint32_t)(~(1 << 31));
  union { __m128 operand; __m128i signs; } Signed;
  Signed.signs = _mm_setr_epi32(SIGN_BIT, SIGN_BIT, SIGN_BIT, SIGN_BIT);
  return _mm_and_ps(operand, Signed.operand);
#else
  return (CFloat32x4) {
    CFloat32x2Magnitude(operand.lo),
    CFloat32x2Magnitude(operand.hi)
  };
#endif
}

#pragma mark Additive

/// Adds two storages (element-wise).
///   (CFloat32x4){
///     lhs[0] + rhs[0],
///     lhs[1] + rhs[1],
///     lhs[2] + rhs[2],
///     lhs[3] + rhs[3]
///   }
FORCE_INLINE(CFloat32x4)
CFloat32x4Add(const CFloat32x4 lhs, const CFloat32x4 rhs)
{
#if CSIMDX_ARM_NEON
  return vaddq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_add_ps(lhs, rhs);
#else
  return (CFloat32x4) {
    CFloat32x2Add(lhs.lo, rhs.lo),
    CFloat32x2Add(lhs.hi, rhs.hi)
  };
#endif
}

/// Subtracts a storage from another (element-wise).
///   (CFloat32x4){
///     lhs[0] - rhs[0],
///     lhs[1] - rhs[1],
///     lhs[2] - rhs[2],
///     lhs[3] - rhs[3]
///   }
FORCE_INLINE(CFloat32x4)
CFloat32x4Subtract(const CFloat32x4 lhs, const CFloat32x4 rhs)
{
#if CSIMDX_ARM_NEON
  return vsubq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_sub_ps(lhs, rhs);
#else
  return (CFloat32x4) {
    CFloat32x2Subtract(lhs.lo, rhs.lo),
    CFloat32x2Subtract(lhs.hi, rhs.hi)
  };
#endif
}

#pragma mark Multiplicative

/// Multiplies two storages (element-wise).
///   (CFloat32x4){
///     lhs[0] * rhs[0],
///     lhs[1] * rhs[1],
///     lhs[2] * rhs[2],
///     lhs[3] * rhs[3]
///   }
FORCE_INLINE(CFloat32x4)
CFloat32x4Multiply(const CFloat32x4 lhs, const CFloat32x4 rhs)
{
#if CSIMDX_ARM_NEON
  return vmulq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_mul_ps(lhs, rhs);
#else
  return (CFloat32x4) {
    CFloat32x2Multiply(lhs.lo, rhs.lo),
    CFloat32x2Multiply(lhs.hi, rhs.hi)
  };
#endif
}

/// Divides two storages (element-wise).
/// @return
///   (CFloat32x4){
///     lhs[0] / rhs[0],
///     lhs[1] / rhs[1],
///     lhs[2] / rhs[2],
///     lhs[3] / rhs[3]
///   }
FORCE_INLINE(CFloat32x4)
CFloat32x4Divide(const CFloat32x4 lhs, const CFloat32x4 rhs)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vdivq_f32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_div_ps(lhs, rhs);
#elif CSIMDX_ARM_NEON
  return CFloat32x4Make(
    CFloat32x4GetElement(lhs, 0) / CFloat32x4GetElement(rhs, 0),
    CFloat32x4GetElement(lhs, 1) / CFloat32x4GetElement(rhs, 1),
    CFloat32x4GetElement(lhs, 2) / CFloat32x4GetElement(rhs, 2),
    CFloat32x4GetElement(lhs, 3) / CFloat32x4GetElement(rhs, 3)
  );
#else
  return (CFloat32x4) {
    CFloat32x2Divide(lhs.lo, rhs.lo),
    CFloat32x2Divide(lhs.hi, rhs.hi)
  };
#endif
}

/// Calculates the square root (element-wise).
/// @return
///   (CFloat32x4){
///     sqrt(operand[0]),
///     sqrt(operand[1]),
///     sqrt(operand[2]),
///     sqrt(operand[3])
///   }
FORCE_INLINE(CFloat32x4) CFloat32x4SquareRoot(const CFloat32x4 operand)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vsqrtq_f32(operand);
#elif CSIMDX_X86_SSE2
  return _mm_sqrt_ps(operand);
#elif CSIMDX_ARM_NEON
  return CFloat32x4Make(
    __builtin_sqrtf(CFloat32x4GetElement(operand, 0)),
    __builtin_sqrtf(CFloat32x4GetElement(operand, 1)),
    __builtin_sqrtf(CFloat32x4GetElement(operand, 2)),
    __builtin_sqrtf(CFloat32x4GetElement(operand, 3))
  );
#else
  return (CFloat32x4) {
    CFloat32x2SquareRoot(operand.lo),
    CFloat32x2SquareRoot(operand.hi)
  };
#endif
}

#undef Float32
