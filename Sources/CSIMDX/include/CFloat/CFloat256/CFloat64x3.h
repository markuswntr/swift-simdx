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

/// The 64-bit floating point element
#define Float64 double

/// The 3 x 64-bit floating point storage
///
/// NOTE: These are actually 4 x 64-bit floating-point storages,
/// with its most significant 64 bits unused (zero) for all types.
#if CSIMDX_X86_AVX
typedef __m256d CFloat64x3;
#else
typedef struct CFloat64x3_t {
  CFloat64x2 lo, hi;
} CFloat64x3;
#endif

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
FORCE_INLINE(Float64)
CFloat64x3GetElement(const CFloat64x3 storage, const int index)
{
#if CSIMDX_X86_AVX
  return storage[index];
#else
  union { CFloat64x3 storage; Float64 rawValue[4]; } Union;
  Union.storage = storage;
  return Union.rawValue[index];
#endif
}

/// Sets the element at `index` from `storage` to given value,
/// i.e. `(*storage)[index] = value;`
FORCE_INLINE(void)
CFloat64x3SetElement(CFloat64x3* storage, const int index, const Float64 value)
{
#if CSIMDX_X86_AVX
  (*storage)[index] = value;
#else
  union { CFloat64x3* storage; Float64* rawValue; } Union;
  Union.storage = storage;
  Union.rawValue[index] = value;
#endif
}

#pragma mark - Initialisation

/// Initializes a storage to given elements. Least- to most-significant bits.
/// @return `(CFloat64x3){ element0, element1, element2 }`
FORCE_INLINE(CFloat64x3)
CFloat64x3Make(Float64 element0, Float64 element1, Float64 element2)
{
#if CSIMDX_X86_AVX
  return _mm256_setr_pd(element0, element1, element2, 0.0);
#else
  CFloat64x3 result;
  result.lo = CFloat64x2Make(element0, element1);
  result.hi = CFloat64x2Make(element2, 0.0);
  return result;
#endif
}

/// Loads 2 x Float32 values from unaligned memory.
/// @return `(CFloat64x3){ pointer[0], pointer[1], pointer[2] }`
FORCE_INLINE(CFloat64x3)
CFloat64x3MakeLoad(Float64* pointer)
{
  CFloat64x3 result;
#if CSIMDX_X86_AVX
  result = _mm256_loadu_pd(pointer);
  CFloat64x3SetElement(&result, 3, 0.0);
#else
  result.lo = CFloat64x2MakeLoad(pointer);
  result.hi = CFloat64x2Make(pointer[2], 0.0);
#endif
  return result;
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CFloat64x3){ value, value, value }`
FORCE_INLINE(CFloat64x3) CFloat64x3MakeRepeatingElement(const Float64 value)
{
  CFloat64x3 result;
#if CSIMDX_X86_AVX
  result = _mm256_set1_pd(value);
  CFloat64x3SetElement(&result, 3, 0.0);
#else
  result.lo = CFloat64x2MakeRepeatingElement(value);
  result.hi = CFloat64x2Make(value, 0.0);
#endif
  return result;
}

/// Returns an intrinsic type with all elements initialized to zero (0.0).
/// @return `(CFloat64x3){ 0.0, 0.0 }`
FORCE_INLINE(CFloat64x3) CFloat64x3MakeZero(void)
{
#if CSIMDX_X86_AVX
  return _mm256_setzero_pd();
#else
  const CFloat64x2 zero = CFloat64x2MakeZero();
  CFloat64x3 result;
  result.lo = zero;
  result.hi = zero;
  return result;
#endif
}

// MARK: - Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns
/// the lesser of each pair in the result.
/// @return
///   (CFloat64x3){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1],
///     ...
///   }
FORCE_INLINE(CFloat64x3)
CFloat64x3Minimum(const CFloat64x3 lhs, const CFloat64x3 rhs)
{
#if CSIMDX_X86_AVX
  return _mm256_min_pd(lhs, rhs);
#else
  CFloat64x3 result;
  result.lo = CFloat64x2Minimum(lhs.lo, rhs.lo);
  result.hi = CFloat64x2Minimum(lhs.hi, rhs.hi);
  return result;
#endif
}

/// Performs element-by-element comparison of both storages and returns
/// the greater of each pair in the result.
/// @return
///   (CFloat64x3){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1],
///     ...
///   }
FORCE_INLINE(CFloat64x3)
CFloat64x3Maximum(const CFloat64x3 lhs, const CFloat64x3 rhs)
{
#if CSIMDX_X86_AVX
  return _mm256_max_pd(lhs, rhs);
#else
  CFloat64x3 result;
  result.lo = CFloat64x2Maximum(lhs.lo, rhs.lo);
  result.hi = CFloat64x2Maximum(lhs.hi, rhs.hi);
  return result;
#endif
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CFloat64x3){ -(operand[0]), -(operand[1]), -(operand[2]) }`
FORCE_INLINE(CFloat64x3) CFloat64x3Negate(const CFloat64x3 operand)
{
#if CSIMDX_X86_AVX
  return _mm256_sub_pd(CFloat64x3MakeZero(), operand);
#else
  CFloat64x3 result;
  result.lo = CFloat64x2Negate(operand.lo);
  // Flip only the lower of the high values. Do not flip sign on last lane.
  CFloat64x2SetElement(&result.hi, 0, -CFloat64x2GetElement(operand.hi, 0));
  return result;
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CFloat64x3){ abs(operand[0]), abs(operand[1]) }`
FORCE_INLINE(CFloat64x3) CFloat64x3Absolute(const CFloat64x3 operand)
{
#if CSIMDX_X86_AVX
  __m64 SIGN_BIT = _mm_cvtsi64_m64(~(1LL << 63));
  union { __m256d operand; __m256i signs; } Signed;
  Signed.signs = _mm256_setr_epi64x(SIGN_BIT, SIGN_BIT, SIGN_BIT, SIGN_BIT);
  return _mm256_and_pd(operand, Signed.operand);
#else
  CFloat64x3 result;
  result.lo = CFloat64x2Absolute(operand.lo);
  result.hi = CFloat64x2Absolute(operand.hi);
  return result;
#endif
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CFloat64x3){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
FORCE_INLINE(CFloat64x3)
CFloat64x3Add(const CFloat64x3 lhs, const CFloat64x3 rhs)
{
#if CSIMDX_X86_AVX
  return _mm256_add_pd(lhs, rhs);
#else
  CFloat64x3 result;
  result.lo = CFloat64x2Add(lhs.lo, rhs.lo);
  result.hi = CFloat64x2Add(lhs.hi, rhs.hi);
  return result;
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CFloat64x3){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
FORCE_INLINE(CFloat64x3)
CFloat64x3Subtract(const CFloat64x3 lhs, const CFloat64x3 rhs)
{
#if CSIMDX_X86_AVX
  return _mm256_sub_pd(lhs, rhs);
#else
  CFloat64x3 result;
  result.lo = CFloat64x2Subtract(lhs.lo, rhs.lo);
  result.hi = CFloat64x2Subtract(lhs.hi, rhs.hi);
  return result;
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CFloat64x3){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
FORCE_INLINE(CFloat64x3)
CFloat64x3Multiply(const CFloat64x3 lhs, const CFloat64x3 rhs)
{
#if CSIMDX_X86_AVX
  return _mm256_mul_pd(lhs, rhs);
#else
  CFloat64x3 result;
  result.lo = CFloat64x2Multiply(lhs.lo, rhs.lo);
  result.hi = CFloat64x2Multiply(lhs.hi, rhs.hi);
  return result;
#endif
}

/// Divides two storages (element-wise).
/// @return `(CFloat64x3){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
FORCE_INLINE(CFloat64x3) CFloat64x3Divide(const CFloat64x3 lhs, CFloat64x3 rhs)
{
#if CSIMDX_X86_AVX
  // Prepare the unused bits of the rhs value,
  // to avoid a division by zero, but 1 instead
  CFloat64x3SetElement(&rhs, 3, 1.0);
  return _mm256_div_pd(lhs, rhs);
#else
  CFloat64x3 result;
  result.lo = CFloat64x2Divide(lhs.lo, rhs.lo);
  result.hi = CFloat64x2Divide(lhs.hi, rhs.hi);
  return result;
#endif
}

/// Calculates the square root (element-wise).
/// @return (CFloat64x3){ sqrt(operand[0]), sqrt(operand[1]), sqrt(operand[2]) }
FORCE_INLINE(CFloat64x3) CFloat64x3SquareRoot(const CFloat64x3 operand)
{
#if CSIMDX_X86_AVX
  return _mm256_sqrt_pd(operand);
#else
  CFloat64x3 result;
  result.lo = CFloat64x2SquareRoot(operand.lo);
  result.hi = CFloat64x2SquareRoot(operand.hi);
  return result;
#endif
}

#undef Float64
