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

/// The 32-bit signed integer element
#define Int32 int32_t

/// The 3 x 32-bit signed integer storage
#if CSIMDX_ARM_NEON
typedef int32x4_t CInt32x3; // Most significant 32 bits are unused (zero)
#elif CSIMDX_X86_SSE2
typedef __m128i CInt32x3;   // Most significant 32 bits are unused (zero)
#else
typedef struct CInt32x3_t {
  Int32 rawValue[4];        // Most significant 32 bits are unused (zero)
} CInt32x3;
#endif

#pragma mark - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
FORCE_INLINE(Int32)
CInt32x3GetElement(const CInt32x3 storage, const int index)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_MMX
  return ((Int32*)&(storage))[index];
#else
  return storage.rawValue[index];
#endif
}

/// Sets the element at `index` from `storage` to given value,
/// i.e. `(*storage)[index] = value;`
FORCE_INLINE(void)
CInt32x3SetElement(CInt32x3* storage, const int index, const Int32 value)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_MMX
  ((Int32*)storage)[index] = value;
#else
  (storage->rawValue)[index] = value;
#endif
}

#pragma mark - Initialisation

/// Initializes a storage to given elements. Least- to most-significant bits.
/// @return `(CInt32x3){ element0, element1 }`
FORCE_INLINE(CInt32x3)
CInt32x3Make(Int32 element0, Int32 element1, Int32 element2)
{
#if CSIMDX_X86_SSE2
  return _mm_setr_epi32(element0, element1, element2, 0);
#else
  return (CInt32x3){ element0, element1, element2, 0 };
#endif
}

/// Loads 3 x Int32 values from unaligned memory.
/// @return `(CInt32x3){ pointer[0], pointer[1] }`
FORCE_INLINE(CInt32x3)
CInt32x3MakeLoad(const Int32* pointer)
{
#if CSIMDX_ARM_NEON
  CInt32x3 result = vld1q_s32(pointer);
  CInt32x3SetElement(&result, 3, 0); // Set last element (unused) to 0
  return result;
#elif CSIMDX_X86_SSE2
  CInt32x3 result = _mm_loadu_si128((__m128i*)pointer);
  CInt32x3SetElement(&result, 3, 0); // Set last element (unused) to 0
  return result;
#else
  return CInt32x3Make(pointer[0], pointer[1], pointer[2]);
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CInt32x3){ value, value }`
FORCE_INLINE(CInt32x3)
CInt32x3MakeRepeatingElement(const Int32 value)
{
#if CSIMDX_ARM_NEON
  return vdupq_n_s32(value);
#elif CSIMDX_X86_SSE2
  return _mm_set1_epi32(value);
#else
  return CInt32x3Make(value, value);
#endif
}

/// Returns an intrinsic type with all elements initialized to zero (0).
/// @return `(CInt32x3){ 0, 0 }`
FORCE_INLINE(CInt32x3) CInt32x3MakeZero(void)
{
#if CSIMDX_ARM_NEON
  return vdupq_n_s32(0);
#elif CSIMDX_X86_SSE2
  return _mm_setzero_si128();
#else
  return CInt32x3MakeRepeatingElement(0);
#endif
}

#pragma mark - Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns
/// the lesser of each pair in the result.
/// @return
///   (CInt32x3){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1]
///   }
FORCE_INLINE(CInt32x3)
CInt32x3Minimum(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vminq_s32(lhs, rhs);
#elif CSIMDX_X86_SSE4_1 // SSE2 has no `min` function, but SSE4 does.
  return _mm_min_epi32(lhs, rhs);
#else
  Int32 lhs0 = CInt32x3GetElement(lhs, 0);
  Int32 rhs0 = CInt32x3GetElement(rhs, 0);
  Int32 lhs1 = CInt32x3GetElement(lhs, 1);
  Int32 rhs1 = CInt32x3GetElement(rhs, 1);
  Int32 lhs2 = CInt32x3GetElement(lhs, 2);
  Int32 rhs2 = CInt32x3GetElement(rhs, 2);
  return CInt32x3Make(lhs0 < rhs0 ? lhs0 : rhs0,
                      lhs1 < rhs1 ? lhs1 : rhs1,
                      lhs2 < rhs2 ? lhs2 : rhs2);
#endif
}

/// Performs element-by-element comparison of both storages and returns
/// the greater of each pair in the result.
/// @return
///   (CInt32x3){
///     lhs[0] > rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] > rhs[1] ? lhs[1] : rhs[1]
///   }
FORCE_INLINE(CInt32x3)
CInt32x3Maximum(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vmaxq_s32(lhs, rhs);
#elif CSIMDX_X86_SSE4_1 // SSE2 has no `min` function, but SSE4 does.
  return _mm_max_epi32(lhs, rhs);
#else
  Int32 lhs0 = CInt32x3GetElement(lhs, 0);
  Int32 rhs0 = CInt32x3GetElement(rhs, 0);
  Int32 lhs1 = CInt32x3GetElement(lhs, 1);
  Int32 rhs1 = CInt32x3GetElement(rhs, 1);
  Int32 lhs2 = CInt32x3GetElement(lhs, 2);
  Int32 rhs2 = CInt32x3GetElement(rhs, 2);
  return CInt32x3Make(lhs0 > rhs0 ? lhs0 : rhs0,
                      lhs1 > rhs1 ? lhs1 : rhs1,
                      lhs2 > rhs2 ? lhs2 : rhs2);
#endif
}

#pragma mark - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CInt32x3){ lhs[0] == rhs[0], lhs[1] == rhs[1] }`
FORCE_INLINE(CInt32x3)
CInt32x3CompareElementWise(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vceqq_s32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_cmpeq_epi32(lhs, rhs);
#else
  Int32 lhs0 = CInt32x3GetElement(lhs, 0);
  Int32 rhs0 = CInt32x3GetElement(rhs, 0);
  Int32 lhs1 = CInt32x3GetElement(lhs, 1);
  Int32 rhs1 = CInt32x3GetElement(rhs, 1);
  Int32 lhs2 = CInt32x3GetElement(lhs, 2);
  Int32 rhs2 = CInt32x3GetElement(rhs, 2);
  return CInt32x3Make(lhs0 == rhs0, lhs1 == rhs1, lhs2 == rhs2);
#endif
}

/// Returns the negated storage (element-wise).
/// @return `(CInt32x3){ -(operand[0]), -(operand[1]), -(operand[2]) }`
FORCE_INLINE(CInt32x3) CInt32x3Negate(const CInt32x3 operand)
{
#if CSIMDX_ARM_NEON
  return vnegq_s32(operand);
#elif CSIMDX_X86_SSE2
  return _mm_sub_epi32(CInt32x3MakeZero(), operand);
#else
  return CInt32x3Make(-CInt32x3GetElement(operand, 0),
                      -CInt32x3GetElement(operand, 1),
                      -CInt32x3GetElement(operand, 2));
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CUInt32x3){ abs(operand[0]), abs(operand[1]), abs(operand[2]) }`
FORCE_INLINE(CUInt32x3)
CInt32x3Magnitude(const CInt32x3 operand)
{
#if CSIMDX_ARM_NEON
  return vreinterpretq_u32_s32(vabsq_s32(operand));
#elif CSIMDX_X86_SSE3 // MMX has no `abs` function for __m64, but SSE3 does
  return _mm_abs_epi32(operand);
#else
  return CInt32x3Make(__builtin_abs(CInt32x3GetElement(operand, 0)),
                      __builtin_abs(CInt32x3GetElement(operand, 1)),
                      __builtin_abs(CInt32x3GetElement(operand, 2)));
#endif
}

#pragma mark Additive

/// Adds two storages (element-wise).
/// @return `(CInt32x3){ lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2] }`
FORCE_INLINE(CInt32x3)
CInt32x3Add(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vaddq_s32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_add_epi32(lhs, rhs);
#else
  Int32 lhs0 = CInt32x3GetElement(lhs, 0);
  Int32 rhs0 = CInt32x3GetElement(rhs, 0);
  Int32 lhs1 = CInt32x3GetElement(lhs, 1);
  Int32 rhs1 = CInt32x3GetElement(rhs, 1);
  Int32 lhs2 = CInt32x3GetElement(lhs, 2);
  Int32 rhs2 = CInt32x3GetElement(rhs, 2);
  return CInt32x3Make(lhs0 + rhs0, lhs1 + rhs1, lhs2 + rhs2);
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CInt32x3){ lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2] }`
FORCE_INLINE(CInt32x3)
CInt32x3Subtract(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vsubq_s32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_sub_epi32(lhs, rhs);
#else
  Int32 lhs0 = CInt32x3GetElement(lhs, 0);
  Int32 rhs0 = CInt32x3GetElement(rhs, 0);
  Int32 lhs1 = CInt32x3GetElement(lhs, 1);
  Int32 rhs1 = CInt32x3GetElement(rhs, 1);
  Int32 lhs2 = CInt32x3GetElement(lhs, 2);
  Int32 rhs2 = CInt32x3GetElement(rhs, 2);
  return CInt32x3Make(lhs0 - rhs0, lhs1 - rhs1, lhs2 - rhs2);
#endif
}

#pragma mark Multiplicative

/// Subtracts a storage from another (element-wise).
/// @return `(CInt32x3){ lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2] }`
FORCE_INLINE(CInt32x3)
CInt32x3Multiply(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vmulq_s32(lhs, rhs);
#else
  Int32 lhs0 = CInt32x3GetElement(lhs, 0);
  Int32 rhs0 = CInt32x3GetElement(rhs, 0);
  Int32 lhs1 = CInt32x3GetElement(lhs, 1);
  Int32 rhs1 = CInt32x3GetElement(rhs, 1);
  Int32 lhs2 = CInt32x3GetElement(lhs, 2);
  Int32 rhs2 = CInt32x3GetElement(rhs, 2);
  return CInt32x3Make(lhs0 * rhs0, lhs1 * rhs1, lhs2 * rhs2);
#endif
}

#pragma mark - Bitwise

/// Bitwise Not
FORCE_INLINE(CInt32x3) CInt32x3BitwiseNot(const CInt32x3 operand)
{
#if CSIMDX_ARM_NEON
  return vmvnq_s32(operand);
#elif CSIMDX_X86_SSE2
  return _mm_xor_si128(operand, CInt32x3MakeRepeatingElement(-1));
#else
  return CInt32x3Make(~CInt32x3GetElement(operand, 0),
                      ~CInt32x3GetElement(operand, 1),
                      ~CInt32x3GetElement(operand, 2));
#endif
}

/// Bitwise And
FORCE_INLINE(CInt32x3)
CInt32x3BitwiseAnd(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vandq_s32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_and_si128(rhs, lhs);
#else
  return CInt32x3Make(CInt32x3GetElement(lhs, 0) & CInt32x3GetElement(rhs, 0),
                      CInt32x3GetElement(lhs, 1) & CInt32x3GetElement(rhs, 1),
                      CInt32x3GetElement(lhs, 2) & CInt32x3GetElement(rhs, 2);
#endif
}

/// Bitwise And Not
FORCE_INLINE(CInt32x3)
CInt32x3BitwiseAndNot(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_andnot_si128(lhs, rhs);
#else
  return CInt32x3BitwiseAnd(CInt32x3BitwiseNot(lhs), rhs);
#endif
}

/// Bitwise Or
FORCE_INLINE(CInt32x3)
CInt32x3BitwiseOr(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vorrq_s32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_or_si128(lhs, rhs);
#else
  return CInt32x3Make(CInt32x3GetElement(lhs, 0) | CInt32x3GetElement(rhs, 0),
                      CInt32x3GetElement(lhs, 1) | CInt32x3GetElement(rhs, 1)
                      CInt32x3GetElement(lhs, 2) | CInt32x3GetElement(rhs, 2));
#endif
}

/// Bitwise Exclusive Or
FORCE_INLINE(CInt32x3)
CInt32x3BitwiseExclusiveOr(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return veorq_s32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_xor_si128(lhs, rhs);
#else
  return CInt32x3Make(CInt32x3GetElement(lhs, 0) ^ CInt32x3GetElement(rhs, 0),
                      CInt32x3GetElement(lhs, 1) ^ CInt32x3GetElement(rhs, 1),
                      CInt32x3GetElement(lhs, 2) ^ CInt32x3GetElement(rhs, 2));
#endif
}

#pragma mark Shifting

/// Left-shifts each element in the storage operand (lhs) by the specified
/// number of bits in each lane of rhs.
FORCE_INLINE(CInt32x3)
CInt32x3ShiftLeftElementWise(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vshlq_s32(lhs, rhs);
#else
  return CInt32x3Make(CInt32x3GetElement(lhs, 0) << CInt32x3GetElement(rhs, 0),
                      CInt32x3GetElement(lhs, 1) << CInt32x3GetElement(rhs, 1),
                      CInt32x3GetElement(lhs, 2) << CInt32x3GetElement(rhs, 2));
#endif
}

/// Left-shifts each element in the storage operand (lhs) by the specified
/// number of bits of rhs.
FORCE_INLINE(CInt32x3)
CInt32x3ShiftLeft(const CInt32x3 lhs, const Int32 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_slli_epi32(lhs, rhs);
#else
  return CInt32x3ShiftLeftElementWise(lhs, CInt32x3MakeRepeatingElement(rhs));
#endif
}

/// Right-shifts each element in the storage operand (lhs) by the specified
/// number of bits in each lane of rhs.
FORCE_INLINE(CInt32x3)
CInt32x3ShiftRightElementWise(const CInt32x3 lhs, const CInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return CInt32x3ShiftLeftElementWise(lhs, CInt32x3Negate(rhs));
#else
  return CInt32x3Make(CInt32x3GetElement(lhs, 0) >> CInt32x3GetElement(rhs, 0),
                      CInt32x3GetElement(lhs, 1) >> CInt32x3GetElement(rhs, 1),
                      CInt32x3GetElement(lhs, 2) >> CInt32x3GetElement(rhs, 2));
#endif
}

/// Right-shifts each element in the storage operand (lhs) by the specified
/// number of bits of rhs.
FORCE_INLINE(CInt32x3)
CInt32x3ShiftRight(const CInt32x3 lhs, const Int32 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_srli_epi32(lhs, rhs);
#else
  return CInt32x3ShiftRightElementWise(lhs, CInt32x3MakeRepeatingElement(rhs));
#endif
}

#undef Int32
