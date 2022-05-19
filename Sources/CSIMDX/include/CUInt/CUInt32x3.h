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

/// The 32-bit unsigned integer element
#define UInt32 uint32_t

/// The 3 x 32-bit unsigned integer storage
#if CSIMDX_ARM_NEON
typedef uint32x4_t CUInt32x3;  // Most significant 32 bits are unused (zero)
#elif CSIMDX_X86_SSE2
typedef __m128i CUInt32x3;     // Most significant 32 bits are unused (zero)
#else
typedef struct CUInt32x3_t {
  UInt32 rawValue[4];          // Most significant 32 bits are unused (zero)
} CUInt32x3;
#endif

#pragma mark - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
FORCE_INLINE(UInt32)
CUInt32x3GetElement(const CUInt32x3 storage, const int index)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_MMX
  return ((UInt32*)&(storage))[index];
#else
  return storage.rawValue[index];
#endif
}

/// Sets the element at `index` from `storage` to given value,
/// i.e. `(*storage)[index] = value;`
FORCE_INLINE(void)
CUInt32x3SetElement(CUInt32x3* storage, const int index, const UInt32 value)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_MMX
  ((UInt32*)storage)[index] = value;
#else
  (storage->rawValue)[index] = value;
#endif
}

#pragma mark - Initialisation

/// Initializes a storage to given elements. Least- to most-significant bits.
/// @return `(CUInt32x3){ element0, element1 }`
FORCE_INLINE(CUInt32x3)
CUInt32x3Make(UInt32 element0, UInt32 element1, UInt32 element2)
{
#if CSIMDX_X86_SSE2
  return _mm_setr_epi32(element0, element1, element2, 0);
#else
  return (CUInt32x3){ element0, element1, element2, 0 };
#endif
}

/// Loads 3 x UInt32 values from unaligned memory.
/// @return `(CUInt32x3){ pointer[0], pointer[1] }`
FORCE_INLINE(CUInt32x3)
CUInt32x3MakeLoad(const UInt32* pointer)
{
#if CSIMDX_ARM_NEON
  CUInt32x3 result = vld1q_u32(pointer);
  CUInt32x3SetElement(&result, 3, 0); // Set last element (unused) to 0
  return result;
#elif CSIMDX_X86_SSE2
  // TODO: Check correctness
  CUInt32x3 result = _mm_loadu_si128((__m128i*)pointer);
  CUInt32x3SetElement(&result, 3, 0); // Set last element (unused) to 0
  return result;
#else
  return CUInt32x3Make(pointer[0], pointer[1], pointer[2]);
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CUInt32x3){ value, value }`
FORCE_INLINE(CUInt32x3)
CUInt32x3MakeRepeatingElement(const UInt32 value)
{
#if CSIMDX_ARM_NEON
  return vdupq_n_u32(value);
#elif CSIMDX_X86_SSE2
  return _mm_set1_epi32(value);
#else
  return CUInt32x3Make(value, value, value);
#endif
}

/// Returns an intrinsic type with all elements initialized to zero (0).
/// @return `(CUInt32x3){ 0, 0 }`
FORCE_INLINE(CUInt32x3) CUInt32x3MakeZero(void)
{
#if CSIMDX_ARM_NEON
  return vdupq_n_u32(0);
#elif CSIMDX_X86_SSE2
  return _mm_setzero_si128();
#else
  return CUInt32x3MakeRepeatingElement(0);
#endif
}

#pragma mark - Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns
/// the lesser of each pair in the result.
/// @return
///   (CUInt32x3){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1]
///   }
FORCE_INLINE(CUInt32x3)
CUInt32x3Minimum(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vminq_u32(lhs, rhs);
#elif CSIMDX_X86_SSE4_1 // SSE2 has no `min` function, but SSE4 does.
  return _mm_min_epu32(lhs, rhs);
#else
  UInt32 lhs0 = CUInt32x3GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x3GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x3GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x3GetElement(rhs, 1);
  UInt32 lhs2 = CUInt32x3GetElement(lhs, 2);
  UInt32 rhs2 = CUInt32x3GetElement(rhs, 2);
  return CUInt32x3Make(lhs0 < rhs0 ? lhs0 : rhs0,
                       lhs1 < rhs1 ? lhs1 : rhs1,
                       lhs2 < rhs2 ? lhs2 : rhs2);
#endif
}

/// Performs element-by-element comparison of both storages and returns
/// the greater of each pair in the result.
/// @return
///   (CUInt32x3){
///     lhs[0] > rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] > rhs[1] ? lhs[1] : rhs[1]
///   }
FORCE_INLINE(CUInt32x3)
CUInt32x3Maximum(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vmaxq_u32(lhs, rhs);
#elif CSIMDX_X86_SSE4_1 // SSE2 has no `min` function, but SSE4 does.
  return _mm_max_epu32(lhs, rhs);
#else
  UInt32 lhs0 = CUInt32x3GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x3GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x3GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x3GetElement(rhs, 1);
  UInt32 lhs2 = CUInt32x3GetElement(lhs, 2);
  UInt32 rhs2 = CUInt32x3GetElement(rhs, 2);
  return CUInt32x3Make(lhs0 > rhs0 ? lhs0 : rhs0,
                       lhs1 > rhs1 ? lhs1 : rhs1,
                       lhs2 > rhs2 ? lhs2 : rhs2);
#endif
}

#pragma mark - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CUInt32x3){ lhs[0] == rhs[0], lhs[1] == rhs[1] }`
FORCE_INLINE(CUInt32x3)
CUInt32x3CompareElementWise(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vceqq_u32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_cmpeq_epi32(lhs, rhs);
#else
  UInt32 lhs0 = CUInt32x3GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x3GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x3GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x3GetElement(rhs, 1);
  UInt32 lhs2 = CUInt32x3GetElement(lhs, 2);
  UInt32 rhs2 = CUInt32x3GetElement(rhs, 2);
  return CUInt32x3Make(lhs0 == rhs0, lhs1 == rhs1, lhs2 == rhs2);
#endif
}

#pragma mark Additive

/// Adds two storages (element-wise).
/// @return `(CUInt32x3){ lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2] }`
FORCE_INLINE(CUInt32x3)
CUInt32x3Add(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vaddq_u32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_add_epi32(lhs, rhs);
#else
  UInt32 lhs0 = CUInt32x3GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x3GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x3GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x3GetElement(rhs, 1);
  UInt32 lhs2 = CUInt32x3GetElement(lhs, 2);
  UInt32 rhs2 = CUInt32x3GetElement(rhs, 2);
  return CUInt32x3Make(lhs0 + rhs0, lhs1 + rhs1, lhs2 + rhs2);
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CUInt32x3){ lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2] }`
FORCE_INLINE(CUInt32x3)
CUInt32x3Subtract(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vsubq_u32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_sub_epi32(lhs, rhs);
#else
  UInt32 lhs0 = CUInt32x3GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x3GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x3GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x3GetElement(rhs, 1);
  UInt32 lhs2 = CUInt32x3GetElement(lhs, 2);
  UInt32 rhs2 = CUInt32x3GetElement(rhs, 2);
  return CUInt32x3Make(lhs0 - rhs0, lhs1 - rhs1, lhs2 - rhs2);
#endif
}

#pragma mark Multiplicative

/// Subtracts a storage from another (element-wise).
/// @return `(CUInt32x3){ lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2] }`
FORCE_INLINE(CUInt32x3)
CUInt32x3Multiply(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vmulq_u32(lhs, rhs);
#else
  UInt32 lhs0 = CUInt32x3GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x3GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x3GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x3GetElement(rhs, 1);
  UInt32 lhs2 = CUInt32x3GetElement(lhs, 2);
  UInt32 rhs2 = CUInt32x3GetElement(rhs, 2);
  return CUInt32x3Make(lhs0 * rhs0, lhs1 * rhs1, lhs2 * rhs2);
#endif
}

#pragma mark - Bitwise

/// Bitwise Not
FORCE_INLINE(CUInt32x3) CUInt32x3BitwiseNot(const CUInt32x3 operand)
{
#if CSIMDX_ARM_NEON
  return vmvnq_u32(operand);
#elif CSIMDX_X86_SSE2
  return _mm_xor_si128(operand, CUInt32x3MakeRepeatingElement(-1));
#else
  return CUInt32x3Make(~CUInt32x3GetElement(operand, 0),
                       ~CUInt32x3GetElement(operand, 1),
                       ~CUInt32x3GetElement(operand, 2));
#endif
}

/// Bitwise And
FORCE_INLINE(CUInt32x3)
CUInt32x3BitwiseAnd(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vandq_u32(lhs, rhs);
#elif CSIMDX_X86_SSE2
  return _mm_and_si128(rhs, lhs);
#else
  return CUInt32x3Make(CUInt32x3GetElement(lhs, 0) & CUInt32x3GetElement(rhs, 0),
                       CUInt32x3GetElement(lhs, 1) & CUInt32x3GetElement(rhs, 1),
                       CUInt32x3GetElement(lhs, 2) & CUInt32x3GetElement(rhs, 2);
#endif
}

/// Bitwise And Not
FORCE_INLINE(CUInt32x3)
CUInt32x3BitwiseAndNot(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_andnot_si128(lhs, rhs);
#else
  return CUInt32x3BitwiseAnd(CUInt32x3BitwiseNot(lhs), rhs);
#endif
}

/// Bitwise Or
FORCE_INLINE(CUInt32x3)
CUInt32x3BitwiseOr(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vorrq_u32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_or_si128(lhs, rhs);
#else
  return CUInt32x3Make(CUInt32x3GetElement(lhs, 0) | CUInt32x3GetElement(rhs, 0),
                       CUInt32x3GetElement(lhs, 1) | CUInt32x3GetElement(rhs, 1)
                       CUInt32x3GetElement(lhs, 2) | CUInt32x3GetElement(rhs, 2));
#endif
}

/// Bitwise Exclusive Or
FORCE_INLINE(CUInt32x3)
CUInt32x3BitwiseExclusiveOr(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return veorq_u32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_xor_si128(lhs, rhs);
#else
  return CUInt32x3Make(CUInt32x3GetElement(lhs, 0) ^ CUInt32x3GetElement(rhs, 0),
                       CUInt32x3GetElement(lhs, 1) ^ CUInt32x3GetElement(rhs, 1),
                       CUInt32x3GetElement(lhs, 2) ^ CUInt32x3GetElement(rhs, 2));
#endif
}

#pragma mark Shifting

/// Left-shifts each element in the storage operand (lhs) by the specified
/// number of bits in each lane of rhs.
FORCE_INLINE(CUInt32x3)
CUInt32x3ShiftLeftElementWise(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
#if CSIMDX_ARM_NEON
  return vshlq_u32(lhs, rhs);
#else
  return CUInt32x3Make(CUInt32x3GetElement(lhs, 0) << CUInt32x3GetElement(rhs, 0),
                       CUInt32x3GetElement(lhs, 1) << CUInt32x3GetElement(rhs, 1),
                       CUInt32x3GetElement(lhs, 2) << CUInt32x3GetElement(rhs, 2));
#endif
}

/// Left-shifts each element in the storage operand (lhs) by the specified
/// number of bits of rhs.
FORCE_INLINE(CUInt32x3)
CUInt32x3ShiftLeft(const CUInt32x3 lhs, const UInt32 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_slli_epi32(lhs, rhs);
#else
  return CUInt32x3ShiftLeftElementWise(lhs, CUInt32x3MakeRepeatingElement(rhs));
#endif
}

/// Right-shifts each element in the storage operand (lhs) by the specified
/// number of bits in each lane of rhs.
FORCE_INLINE(CUInt32x3)
CUInt32x3ShiftRightElementWise(const CUInt32x3 lhs, const CUInt32x3 rhs)
{
  return CUInt32x3Make(CUInt32x3GetElement(lhs, 0) >> CUInt32x3GetElement(rhs, 0),
                       CUInt32x3GetElement(lhs, 1) >> CUInt32x3GetElement(rhs, 1),
                       CUInt32x3GetElement(lhs, 2) >> CUInt32x3GetElement(rhs, 2));
}

/// Right-shifts each element in the storage operand (lhs) by the specified
/// number of bits of rhs.
FORCE_INLINE(CUInt32x3)
CUInt32x3ShiftRight(const CUInt32x3 lhs, const UInt32 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_srli_epi32(lhs, rhs);
#else
  return CUInt32x3ShiftRightElementWise(lhs, CUInt32x3MakeRepeatingElement(rhs));
#endif
}

#undef UInt32
