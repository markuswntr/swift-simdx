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

/// The 2 x 32-bit signed integer storage
#if CSIMDX_ARM_NEON
typedef int32x2_t CInt32x2;
#elif CSIMDX_X86_MMX
typedef __m64 CInt32x2;
#else
typedef struct CInt32x2_t {
  Int32 rawValue[2];
} CInt32x2;
#endif

#pragma mark - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
FORCE_INLINE(Int32)
CInt32x2GetElement(const CInt32x2 storage, const int index)
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
CInt32x2SetElement(CInt32x2* storage, const int index, const Int32 value)
{
#if CSIMDX_ARM_NEON || CSIMDX_X86_MMX
  ((Int32*)storage)[index] = value;
#else
  (storage->rawValue)[index] = value;
#endif
}

#pragma mark - Initialisation

/// Initializes a storage to given elements. Least- to most-significant bits.
/// @return `(CInt32x2){ element0, element1 }`
FORCE_INLINE(CInt32x2)
CInt32x2Make(Int32 element0, Int32 element1)
{
#if CSIMDX_X86_MMX
  return _mm_setr_pi32(element0, element1);
#else
  return (CInt32x2){ element0, element1 };
#endif
}

/// Loads 2 x Int32 values from unaligned memory.
/// @return `(CInt32x2){ pointer[0], pointer[1] }`
FORCE_INLINE(CInt32x2)
CInt32x2MakeLoad(const Int32* pointer)
{
#if CSIMDX_ARM_NEON
  return vld1_s32(pointer);
#else
  return CInt32x2Make(pointer[0], pointer[1]);
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CInt32x2){ value, value }`
FORCE_INLINE(CInt32x2)
CInt32x2MakeRepeatingElement(const Int32 value)
{
#if CSIMDX_ARM_NEON
  return vdup_n_s32(value);
#elif CSIMDX_X86_MMX
  return _mm_set1_pi32(value);
#else
  return CInt32x2Make(value, value);
#endif
}

/// Returns an intrinsic type with all elements initialized to zero (0).
/// @return `(CInt32x2){ 0, 0 }`
FORCE_INLINE(CInt32x2) CInt32x2MakeZero(void)
{
#if CSIMDX_ARM_NEON
  return vdup_n_s32(0);
#elif CSIMDX_X86_MMX
  return _mm_setzero_si64();
#else
  return CInt32x2MakeRepeatingElement(0);
#endif
}

#pragma mark - Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns
/// the lesser of each pair in the result.
/// @return
///   (CInt32x2){
///     lhs[0] < rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] < rhs[1] ? lhs[1] : rhs[1]
///   }
FORCE_INLINE(CInt32x2)
CInt32x2Minimum(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vmin_s32(lhs, rhs);
#elif CSIMDX_X86_SSE4_1
  // MMX has no `min` function for __m64, but SSE4 does for __m128i.
  // So promote both to __m128i, run `min`, and move back to __m64.
  return _mm_movepi64_pi64(_mm_min_epi32(_mm_movpi64_epi64(lhs),
                                         _mm_movpi64_epi64(rhs)));
#else
  Int32 lhs0 = CInt32x2GetElement(lhs, 0);
  Int32 rhs0 = CInt32x2GetElement(rhs, 0);
  Int32 lhs1 = CInt32x2GetElement(lhs, 1);
  Int32 rhs1 = CInt32x2GetElement(rhs, 1);
  return CInt32x2Make(lhs0 < rhs0 ? lhs0 : rhs0,
                      lhs1 < rhs1 ? lhs1 : rhs1);
#endif
}

/// Performs element-by-element comparison of both storages and returns
/// the greater of each pair in the result.
/// @return
///   (CInt32x2){
///     lhs[0] > rhs[0] ? lhs[0] : rhs[0],
///     lhs[1] > rhs[1] ? lhs[1] : rhs[1]
///   }
FORCE_INLINE(CInt32x2)
CInt32x2Maximum(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vmax_s32(lhs, rhs);
#elif CSIMDX_X86_SSE4_1
  // MMX has no `max` function for __m64, but SSE4 does for __m128i.
  // So promote both to __m128i, run `max`, and move back to __m64.
  return _mm_movepi64_pi64(_mm_max_epi32(_mm_movpi64_epi64(lhs),
                                         _mm_movpi64_epi64(rhs)));
#else
  Int32 lhs0 = CInt32x2GetElement(lhs, 0);
  Int32 rhs0 = CInt32x2GetElement(rhs, 0);
  Int32 lhs1 = CInt32x2GetElement(lhs, 1);
  Int32 rhs1 = CInt32x2GetElement(rhs, 1);
  return CInt32x2Make(lhs0 > rhs0 ? lhs0 : rhs0,
                      lhs1 > rhs1 ? lhs1 : rhs1);
#endif
}

#pragma mark - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CInt32x2){ lhs[0] == rhs[0], lhs[1] == rhs[1] }`
FORCE_INLINE(CInt32x2)
CInt32x2CompareElementWise(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vceq_s32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_cmpeq_pi32(lhs, rhs);
#else
  Int32 lhs0 = CInt32x2GetElement(lhs, 0);
  Int32 rhs0 = CInt32x2GetElement(rhs, 0);
  Int32 lhs1 = CInt32x2GetElement(lhs, 1);
  Int32 rhs1 = CInt32x2GetElement(rhs, 1);
  return CInt32x2Make(lhs0 == rhs0, lhs1 == rhs1);
#endif
}

/// Returns the negated storage (element-wise).
/// @return `(CInt32x2){ -(operand[0]), -(operand[1]) }`
FORCE_INLINE(CInt32x2) CInt32x2Negate(const CInt32x2 operand)
{
#if CSIMDX_ARM_NEON
  return vneg_s32(operand);
#elif CSIMDX_X86_MMX
  return _mm_sub_pi32(CInt32x2MakeZero(), operand);
#else
  return CInt32x2Make(-CInt32x2GetElement(operand, 0),
                      -CInt32x2GetElement(operand, 1));
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CUInt32x2){ abs(operand[0]), abs(operand[1]) }`
FORCE_INLINE(CUInt32x2) CInt32x2Magnitude(const CInt32x2 operand)
{
#if CSIMDX_ARM_NEON
  return vreinterpret_u32_s32(vabs_s32(operand));
#elif CSIMDX_X86_SSE3 // MMX has no `abs` function for __m64, but SSE3 does
  return _mm_abs_pi32(operand);
#else
  return CInt32x2Make(__builtin_abs(CInt32x2GetElement(operand, 0)),
                      __builtin_abs(CInt32x2GetElement(operand, 1)));
#endif
}

#pragma mark Additive

/// Adds two storages (element-wise).
/// @return `(CInt32x2){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
FORCE_INLINE(CInt32x2)
CInt32x2Add(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vadd_s32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_add_pi32(lhs, rhs);
#else
  Int32 lhs0 = CInt32x2GetElement(lhs, 0);
  Int32 rhs0 = CInt32x2GetElement(rhs, 0);
  Int32 lhs1 = CInt32x2GetElement(lhs, 1);
  Int32 rhs1 = CInt32x2GetElement(rhs, 1);
  return CInt32x2Make(lhs0 + rhs0, lhs1 + rhs1);
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CInt32x2){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
FORCE_INLINE(CInt32x2)
CInt32x2Subtract(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vsub_s32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_sub_pi32(lhs, rhs);
#else
  Int32 lhs0 = CInt32x2GetElement(lhs, 0);
  Int32 rhs0 = CInt32x2GetElement(rhs, 0);
  Int32 lhs1 = CInt32x2GetElement(lhs, 1);
  Int32 rhs1 = CInt32x2GetElement(rhs, 1);
  return CInt32x2Make(lhs0 - rhs0, lhs1 - rhs1);
#endif
}

#pragma mark Multiplicative

/// Subtracts a storage from another (element-wise).
/// @return `(CInt32x2){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
FORCE_INLINE(CInt32x2)
CInt32x2Multiply(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vmul_s32(lhs, rhs);
#else
  Int32 lhs0 = CInt32x2GetElement(lhs, 0);
  Int32 rhs0 = CInt32x2GetElement(rhs, 0);
  Int32 lhs1 = CInt32x2GetElement(lhs, 1);
  Int32 rhs1 = CInt32x2GetElement(rhs, 1);
  return CInt32x2Make(lhs0 * rhs0, lhs1 * rhs1);
#endif
}

#pragma mark - Bitwise

/// Bitwise Not
FORCE_INLINE(CInt32x2) CInt32x2BitwiseNot(const CInt32x2 operand)
{
#if CSIMDX_ARM_NEON
  return vmvn_s32(operand);
#elif CSIMDX_X86_MMX
  return _mm_xor_si64(operand, CInt32x2MakeRepeatingElement(-1));
#else
  return CInt32x2Make(~CInt32x2GetElement(operand, 0),
                      ~CInt32x2GetElement(operand, 1));
#endif
}

/// Bitwise And
FORCE_INLINE(CInt32x2)
CInt32x2BitwiseAnd(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vand_s32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_and_si64(rhs, lhs);
#else
  return CInt32x2Make(CInt32x2GetElement(lhs, 0) & CInt32x2GetElement(rhs, 0),
                      CInt32x2GetElement(lhs, 1) & CInt32x2GetElement(rhs, 1));
#endif
}

/// Bitwise And Not
FORCE_INLINE(CInt32x2)
CInt32x2BitwiseAndNot(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_andnot_si64(lhs, rhs);
#else
  return CInt32x2BitwiseAnd(CInt32x2BitwiseNot(lhs), rhs);
#endif
}

/// Bitwise Or
FORCE_INLINE(CInt32x2)
CInt32x2BitwiseOr(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vorr_s32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_or_si64(lhs, rhs);
#else
  return CInt32x2Make(CInt32x2GetElement(lhs, 0) | CInt32x2GetElement(rhs, 0),
                      CInt32x2GetElement(lhs, 1) | CInt32x2GetElement(rhs, 1));
#endif
}

/// Bitwise Exclusive Or
FORCE_INLINE(CInt32x2)
CInt32x2BitwiseExclusiveOr(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return veor_s32(lhs, rhs);
#elif CSIMDX_X86_MMX
  return _mm_xor_si64(lhs, rhs);
#else
  return CInt32x2Make(CInt32x2GetElement(lhs, 0) ^ CInt32x2GetElement(rhs, 0),
                      CInt32x2GetElement(lhs, 1) ^ CInt32x2GetElement(rhs, 1));
#endif
}

#pragma mark Shifting

/// Left-shifts each element in the storage operand (lhs) by the specified
/// number of bits in each lane of rhs.
FORCE_INLINE(CInt32x2)
CInt32x2ShiftLeftElementWise(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return vshl_s32(lhs, rhs);
#else
  return CInt32x2Make(CInt32x2GetElement(lhs, 0) << CInt32x2GetElement(rhs, 0),
                      CInt32x2GetElement(lhs, 1) << CInt32x2GetElement(rhs, 1));
#endif
}

/// Left-shifts each element in the storage operand (lhs) by the specified
/// number of bits of rhs.
FORCE_INLINE(CInt32x2)
CInt32x2ShiftLeft(const CInt32x2 lhs, const Int32 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_slli_pi32(lhs, rhs);
#else
  return CInt32x2ShiftLeftElementWise(lhs, CInt32x2MakeRepeatingElement(rhs));
#endif
}

/// Right-shifts each element in the storage operand (lhs) by the specified
/// number of bits in each lane of rhs.
FORCE_INLINE(CInt32x2)
CInt32x2ShiftRightElementWise(const CInt32x2 lhs, const CInt32x2 rhs)
{
#if CSIMDX_ARM_NEON
  return CInt32x2ShiftLeftElementWise(lhs, CInt32x2Negate(rhs));
#else
  return CInt32x2Make(CInt32x2GetElement(lhs, 0) >> CInt32x2GetElement(rhs, 0),
                      CInt32x2GetElement(lhs, 1) >> CInt32x2GetElement(rhs, 1));
#endif
}

/// Right-shifts each element in the storage operand (lhs) by the specified
/// number of bits of rhs.
FORCE_INLINE(CInt32x2)
CInt32x2ShiftRight(const CInt32x2 lhs, const Int32 rhs)
{
#if CSIMDX_X86_MMX
  return _mm_srli_pi32(lhs, rhs);
#else
  return CInt32x2ShiftRightElementWise(lhs, CInt32x2MakeRepeatingElement(rhs));
#endif
}

#undef Int32
