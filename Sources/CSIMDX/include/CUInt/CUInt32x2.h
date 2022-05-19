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

/// The 2 x 32-bit unsigned integer storage
#if CSIMDX_ARM_NEON
typedef uint32x2_t CUInt32x2;
#elif CSIMDX_X86_MMX
typedef __m64 CUInt32x2;
#else
typedef struct CUInt32x2_t {
  UInt32 rawValue[2];
} CUInt32x2;
#endif

#pragma mark - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
FORCE_INLINE(UInt32)
CUInt32x2GetElement(const CUInt32x2 storage, const int index)
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
CUInt32x2SetElement(CUInt32x2* storage, const int index, const UInt32 value)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_MMX
  ((UInt32*)storage)[index] = value;
#else
  (storage->rawValue)[index] = value;
#endif
}

#pragma mark - Initialisation

/// Initializes a storage to given elements. Least- to most-significant bits.
/// @return `(CUInt32x2){ element0, element1 }`
FORCE_INLINE(CUInt32x2)
CUInt32x2Make(UInt32 element0, UInt32 element1)
{
#if CSIMDX_X86_MMX
  return _mm_setr_pi32(element0, element1);
#else
  return (CUInt32x2){ element0, element1 };
#endif
}

/// Loads 2 x UInt32 values from unaligned memory.
/// @return `(CUInt32x2){ pointer[0], pointer[1] }`
FORCE_INLINE(CUInt32x2)
CUInt32x2MakeLoad(const UInt32* pointer)
{
#if CSIMDX_ARM_NEON
  return vld1_u32(pointer);
#else
  return CUInt32x2Make(pointer[0], pointer[1]);
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CUInt32x2){ value, value }`
FORCE_INLINE(CUInt32x2)
CUInt32x2MakeRepeatingElement(const UInt32 value)
{
#if CSIMDX_ARM_NEON
  return vdup_n_u32(value);
#elif CSIMDX_X86_MMX
  return _mm_set1_pi32(value);
#else
  return CUInt32x2Make(value, value);
#endif
}

/// Returns an intrinsic type with all elements initialized to zero (0).
/// @return `(CUInt32x2){ 0, 0 }`
FORCE_INLINE(CUInt32x2) CUInt32x2MakeZero(void)
{
#if CSIMDX_ARM_NEON
  return vdup_n_u32(0);
#elif CSIMDX_X86_MMX
  return _mm_setzero_si64();
#else
  return CUInt32x2MakeRepeatingElement(0);
#endif
}

#pragma mark - Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns
/// the lesser of each pair in the result.
/// @return
///   (CUInt32x2){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1]
///   }
FORCE_INLINE(CUInt32x2)
CUInt32x2Minimum(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vmin_u32(lhs, rhs);
#elif CSIMDX_X86_SSE4_1
  // MMX has no `min` function for __m64, but SSE4 does for __m128i.
  // So promote both to __m128i, run `min`, and move back to __m64.
  return _mm_movepi64_pi64(_mm_min_epi32(_mm_movpi64_epi64(lhs),
                                         _mm_movpi64_epi64(rhs)));
#else
  UInt32 lhs0 = CUInt32x2GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x2GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x2GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x2GetElement(rhs, 1);
  return CUInt32x2Make(lhs0 < rhs0 ? lhs0 : rhs0,
                      lhs1 < rhs1 ? lhs1 : rhs1);
#endif
}

/// Performs element-by-element comparison of both storages and returns
/// the greater of each pair in the result.
/// @return
///   (CUInt32x2){
///     lhs[0] > rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] > rhs[1] ? lhs[1] : rhs[1]
///   }
FORCE_INLINE(CUInt32x2)
CUInt32x2Maximum(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vmax_u32(lhs, rhs);
#elif CSIMDX_X86_SSE4_1
  // MMX has no `max` function for __m64, but SSE4 does for __m128i.
  // So promote both to __m128i, run `max`, and move back to __m64.
  return _mm_movepi64_pi64(_mm_max_epi32(_mm_movpi64_epi64(lhs),
                                         _mm_movpi64_epi64(rhs)));
#else
  UInt32 lhs0 = CUInt32x2GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x2GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x2GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x2GetElement(rhs, 1);
  return CUInt32x2Make(lhs0 > rhs0 ? lhs0 : rhs0,
                      lhs1 > rhs1 ? lhs1 : rhs1);
#endif
}

#pragma mark - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CUInt32x2){ lhs[0] == rhs[0], lhs[1] == rhs[1] }`
FORCE_INLINE(CUInt32x2)
CUInt32x2CompareElementWise(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vceq_u32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_cmpeq_pi32(lhs, rhs);
#else
  UInt32 lhs0 = CUInt32x2GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x2GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x2GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x2GetElement(rhs, 1);
  return CUInt32x2Make(lhs0 == rhs0, lhs1 == rhs1);
#endif
}

#pragma mark Additive

/// Adds two storages (element-wise).
/// @return `(CUInt32x2){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
FORCE_INLINE(CUInt32x2)
CUInt32x2Add(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vadd_u32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_add_pi32(lhs, rhs);
#else
  UInt32 lhs0 = CUInt32x2GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x2GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x2GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x2GetElement(rhs, 1);
  return CUInt32x2Make(lhs0 + rhs0, lhs1 + rhs1);
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CUInt32x2){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
FORCE_INLINE(CUInt32x2)
CUInt32x2Subtract(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vsub_u32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_sub_pi32(lhs, rhs);
#else
  UInt32 lhs0 = CUInt32x2GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x2GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x2GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x2GetElement(rhs, 1);
  return CUInt32x2Make(lhs0 - rhs0, lhs1 - rhs1);
#endif
}

#pragma mark Multiplicative

/// Subtracts a storage from another (element-wise).
/// @return `(CUInt32x2){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
FORCE_INLINE(CUInt32x2)
CUInt32x2Multiply(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vmul_u32(lhs, rhs);
#else
  UInt32 lhs0 = CUInt32x2GetElement(lhs, 0);
  UInt32 rhs0 = CUInt32x2GetElement(rhs, 0);
  UInt32 lhs1 = CUInt32x2GetElement(lhs, 1);
  UInt32 rhs1 = CUInt32x2GetElement(rhs, 1);
  return CUInt32x2Make(lhs0 * rhs0, lhs1 * rhs1);
#endif
}

#pragma mark - Bitwise

/// Bitwise Not
FORCE_INLINE(CUInt32x2) CUInt32x2BitwiseNot(const CUInt32x2 operand)
{
#if CSIMDX_ARM_NEON
  return vmvn_u32(operand);
#elif CSIMDX_X86_MMX
  return _mm_xor_si64(operand, CUInt32x2MakeRepeatingElement(-1));
#else
  return CUInt32x2Make(~CUInt32x2GetElement(operand, 0),
                      ~CUInt32x2GetElement(operand, 1));
#endif
}

/// Bitwise And
FORCE_INLINE(CUInt32x2)
CUInt32x2BitwiseAnd(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vand_u32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_and_si64(rhs, lhs);
#else
  return CUInt32x2Make(CUInt32x2GetElement(lhs, 0) & CUInt32x2GetElement(rhs, 0),
                      CUInt32x2GetElement(lhs, 1) & CUInt32x2GetElement(rhs, 1));
#endif
}

/// Bitwise And Not
FORCE_INLINE(CUInt32x2)
CUInt32x2BitwiseAndNot(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_andnot_si64(lhs, rhs);
#else
  return CUInt32x2BitwiseAnd(CUInt32x2BitwiseNot(lhs), rhs);
#endif
}

/// Bitwise Or
FORCE_INLINE(CUInt32x2)
CUInt32x2BitwiseOr(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vorr_u32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_or_si64(lhs, rhs);
#else
  return CUInt32x2Make(CUInt32x2GetElement(lhs, 0) | CUInt32x2GetElement(rhs, 0),
                      CUInt32x2GetElement(lhs, 1) | CUInt32x2GetElement(rhs, 1));
#endif
}

/// Bitwise Exclusive Or
FORCE_INLINE(CUInt32x2)
CUInt32x2BitwiseExclusiveOr(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return veor_u32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_xor_si64(lhs, rhs);
#else
  return CUInt32x2Make(CUInt32x2GetElement(lhs, 0) ^ CUInt32x2GetElement(rhs, 0),
                      CUInt32x2GetElement(lhs, 1) ^ CUInt32x2GetElement(rhs, 1));
#endif
}

#pragma mark Shifting

/// Left-shifts each element in the storage operand (lhs) by the specified
/// number of bits in each lane of rhs.
FORCE_INLINE(CUInt32x2)
CUInt32x2ShiftLeftElementWise(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vshl_u32(lhs, rhs);
#else
  return CUInt32x2Make(CUInt32x2GetElement(lhs, 0) << CUInt32x2GetElement(rhs, 0),
                      CUInt32x2GetElement(lhs, 1) << CUInt32x2GetElement(rhs, 1));
#endif
}

/// Left-shifts each element in the storage operand (lhs) by the specified
/// number of bits of rhs.
FORCE_INLINE(CUInt32x2)
CUInt32x2ShiftLeft(const CUInt32x2 lhs, const UInt32 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_slli_pi32(lhs, rhs);
#else
  return CUInt32x2ShiftLeftElementWise(lhs, CUInt32x2MakeRepeatingElement(rhs));
#endif
}

/// Right-shifts each element in the storage operand (lhs) by the specified
/// number of bits in each lane of rhs.
FORCE_INLINE(CUInt32x2)
CUInt32x2ShiftRightElementWise(const CUInt32x2 lhs, const CUInt32x2 rhs)
{
  return CUInt32x2Make(CUInt32x2GetElement(lhs, 0) >> CUInt32x2GetElement(rhs, 0),
                       CUInt32x2GetElement(lhs, 1) >> CUInt32x2GetElement(rhs, 1));
}

/// Right-shifts each element in the storage operand (lhs) by the specified
/// number of bits of rhs.
FORCE_INLINE(CUInt32x2)
CUInt32x2ShiftRight(const CUInt32x2 lhs, const UInt32 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_srli_pi32(lhs, rhs);
#else
  return CUInt32x2ShiftRightElementWise(lhs, CUInt32x2MakeRepeatingElement(rhs));
#endif
}

#undef UInt32
