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

/// The 64-bit floating point element
#define Float64 double

/// The 2 x 64-bit floating point storage
#if CSIMDX_ARM_NEON_AARCH64
typedef float64x2_t CFloat64x2;
#elif CSIMDX_X86_SSE2
typedef __m128d CFloat64x2;
#else
typedef union CFloat64x2_t {
  Float64 rawValue[2];
} CFloat64x2;
#endif

#pragma mark - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
FORCE_INLINE(Float64)
CFloat64x2GetElement(const CFloat64x2 storage, const int index)
{
#if CSIMDX_ARM_NEON_AARCH64 || CSIMDX_X86_SSE2
  return ((Float64*)&(storage))[index];
#else
  return storage.rawValue[index];
#endif
}

/// Sets the element at `index` from `storage` to given value,
/// i.e. `(*storage)[index] = value;`
FORCE_INLINE(void)
CFloat64x2SetElement(CFloat64x2* storage, const int index, const Float64 value)
{
#if CSIMDX_ARM_NEON_AARCH64 || CSIMDX_X86_SSE2
  ((Float64*)storage)[index] = value;
#else
  (storage->rawValue)[index] = value;
#endif
}

#pragma mark - Initialisation

/// Initializes a storage to given elements. Least- to most-significant bits.
/// @return `(CFloat64x2){ element0, element1 }`
FORCE_INLINE(CFloat64x2) CFloat64x2Make(Float64 element0, Float64 element1)
{
#if CSIMDX_X86_SSE2
  return _mm_setr_pd(element0, element1);
#else
  return (CFloat64x2){ element0, element1 };
#endif
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CFloat64x2){ pointer[0], pointer[1] }`
FORCE_INLINE(CFloat64x2) CFloat64x2MakeLoad(const Float64* pointer)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vld1q_f64(pointer);
#elif CSIMDX_X86_SSE2
  return _mm_loadu_pd(pointer);
#else
  return (CFloat64x2){ pointer[0], pointer[1] };
#endif

}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CFloat64x2){ value, value }`
FORCE_INLINE(CFloat64x2) CFloat64x2MakeRepeatingElement(const Float64 value)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vdupq_n_f64(value);
#elif CSIMDX_X86_SSE2
  return _mm_set1_pd(value);
#else
  return (CFloat64x2){ value, value };
#endif
}

/// Returns an intrinsic type with all lanes initialized to zero (0.0).
/// @return `(CFloat64x2){ 0.0, 0.0 }`
FORCE_INLINE(CFloat64x2) CFloat64x2MakeZero(void)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vdupq_n_f64(0.0);
#elif CSIMDX_X86_SSE2
  return _mm_setzero_pd();
#else
  return (CFloat64x2){ 0.0, 0.0 };
#endif
}

#pragma mark Minimum & Maximum

/// Performs element-by-element comparison of both storages and
/// returns the lesser of each pair in the result.
/// @return
///   (CFloat64x2){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1]
///   }
FORCE_INLINE(CFloat64x2)
CFloat64x2Minimum(const CFloat64x2 lhs, const CFloat64x2 rhs)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vminq_f64(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_min_pd(lhs, rhs);
#else
  Float64 lhs0 = CFloat64x2GetElement(lhs, 0);
  Float64 rhs0 = CFloat64x2GetElement(rhs, 0);
  Float64 lhs1 = CFloat64x2GetElement(lhs, 1);
  Float64 rhs1 = CFloat64x2GetElement(rhs, 1);
  return CFloat64x2Make(lhs0 < rhs0 ? lhs0 : rhs0,
                        lhs1 < rhs1 ? lhs1 : rhs1);
#endif
}

/// Performs element-by-element comparison of both storages and
/// returns the greater of each pair in the result.
/// @return
///   (CXFloat64x3){
///     lhs[0] > rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] > rhs[1] ? lhs[1] : rhs[1],
///     ...
///   }
FORCE_INLINE(CFloat64x2)
CFloat64x2Maximum(const CFloat64x2 lhs, const CFloat64x2 rhs)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vmaxq_f64(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_max_pd(lhs, rhs);
#else
  Float64 lhs0 = CFloat64x2GetElement(lhs, 0);
  Float64 rhs0 = CFloat64x2GetElement(rhs, 0);
  Float64 lhs1 = CFloat64x2GetElement(lhs, 1);
  Float64 rhs1 = CFloat64x2GetElement(rhs, 1);
  return CFloat64x2Make(lhs0 > rhs0 ? lhs0 : rhs0,
                        lhs1 > rhs1 ? lhs1 : rhs1);
#endif
}

#pragma mark - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CFloat64x2){ -(operand[0]), -(operand[1]) }`
FORCE_INLINE(CFloat64x2)
CFloat64x2Negate(const CFloat64x2 operand)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vnegq_f64(operand);
#elif CSIMDX_X86_SSE2
  return _mm_sub_pd(CFloat64x2MakeZero(), operand);
#else
  return CFloat64x2Make(-CFloat64x2GetElement(operand, 0),
                        -CFloat64x2GetElement(operand, 1));
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CFloat64x2){ abs(operand[0]), abs(operand[1]) }`
FORCE_INLINE(CFloat64x2)
CFloat64x2Absolute(const CFloat64x2 operand)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vabsq_f64(operand);
#elif CSIMDX_X86_SSE2
  __m64 SIGN_BIT = _mm_cvtsi64_m64(~(1LL << 63));
  union { __m128d operand; __m128i signs; } Signed;
  Signed.signs = _mm_setr_epi64(SIGN_BIT, SIGN_BIT);
  return _mm_and_ps(operand, Signed.operand);
#else
  return CFloat64x2Make(__builtin_fabs(CFloat64x2GetElement(operand, 0)),
                        __builtin_fabs(CFloat64x2GetElement(operand, 1)));
#endif
}

#pragma mark Additive

/// Adds two storages (element-wise).
/// @return `(CFloat64x2){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
FORCE_INLINE(CFloat64x2)
CFloat64x2Add(const CFloat64x2 lhs, const CFloat64x2 rhs)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vaddq_f64(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_add_pd(lhs, rhs);
#else
  Float64 lhs0 = CFloat64x2GetElement(lhs, 0);
  Float64 rhs0 = CFloat64x2GetElement(rhs, 0);
  Float64 lhs1 = CFloat64x2GetElement(lhs, 1);
  Float64 rhs1 = CFloat64x2GetElement(rhs, 1);
  return CFloat64x2Make(lhs0 + rhs0, lhs1 + rhs1);
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CFloat64x2){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
FORCE_INLINE(CFloat64x2)
CFloat64x2Subtract(const CFloat64x2 lhs, const CFloat64x2 rhs)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vsubq_f64(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_sub_pd(lhs, rhs);
#else
  Float64 lhs0 = CFloat64x2GetElement(lhs, 0);
  Float64 rhs0 = CFloat64x2GetElement(rhs, 0);
  Float64 lhs1 = CFloat64x2GetElement(lhs, 1);
  Float64 rhs1 = CFloat64x2GetElement(rhs, 1);
  return CFloat64x2Make(lhs0 - rhs0, lhs1 - rhs1);
#endif
}

#pragma mark Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CFloat64x2){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
FORCE_INLINE(CFloat64x2)
CFloat64x2Multiply(const CFloat64x2 lhs, const CFloat64x2 rhs)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vmulq_f64(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_mul_pd(lhs, rhs);
#else
  Float64 lhs0 = CFloat64x2GetElement(lhs, 0);
  Float64 rhs0 = CFloat64x2GetElement(rhs, 0);
  Float64 lhs1 = CFloat64x2GetElement(lhs, 1);
  Float64 rhs1 = CFloat64x2GetElement(rhs, 1);
  return CFloat64x2Make(lhs0 * rhs0, lhs1 * rhs1);
#endif
}

/// Divides two storages (element-wise).
/// @return `(CFloat64x2){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
FORCE_INLINE(CFloat64x2)
CFloat64x2Divide(const CFloat64x2 lhs, const CFloat64x2 rhs)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vdivq_f64(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_div_pd(lhs, rhs);
#else
  Float64 lhs0 = CFloat64x2GetElement(lhs, 0);
  Float64 rhs0 = CFloat64x2GetElement(rhs, 0);
  Float64 lhs1 = CFloat64x2GetElement(lhs, 1);
  Float64 rhs1 = CFloat64x2GetElement(rhs, 1);
  return CFloat64x2Make(lhs0 / rhs0, lhs1 / rhs1);
#endif
}

/// Calculates the square root (element-wise).
/// @return `(CFloat64x2){ sqrt(operand[0]), sqrt(operand[1]) }`
FORCE_INLINE(CFloat64x2) CFloat64x2SquareRoot(const CFloat64x2 operand)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vsqrtq_f64(operand);
#elif CSIMDX_X86_SSE2
  return _mm_sqrt_pd(operand);
#else
  return CFloat64x2Make(__builtin_sqrt(CFloat64x2GetElement(operand, 0)),
                        __builtin_sqrt(CFloat64x2GetElement(operand, 1)));
#endif
}

#undef Float64
