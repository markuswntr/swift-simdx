#pragma once

#include "CXInt_t.h"
#include "CXUInt_t.h"
#include "CXFloat_t.h"
#include "Attributes.h"

// MARK: Designated Initializers

/// Returns an intrinsic initialized to the 4 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Make(Int32 value0, Int32 value1, Int32 value2, Int32 value3)
{
    return _mm_setr_epi32(value0, value1, value2, value3);
}

/// Loads 4 x Int32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 4 x Int32 values
/// @return CXInt32x4(pointer[0], pointer[1], pointer[2], pointer[3])
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeLoad(const Int32* pointer)
{
    return _mm_loadu_si128((const __m128i*)pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeRepeatingElement(const Int32 value)
{
    return _mm_set1_epi32(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeZero(void)
{
    return _mm_setzero_si128();
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int32) CXInt32x4GetElement(const CXInt32x4 storage, const int index)
{
    return ((Int32*)&(storage))[index];
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXInt32x4SetElement(CXInt32x4* storage, const int index, const Int32 value)
{
    ((Int32*)storage)[index] = value;
}

// MARK: - Conversion

/// Converts a vector of 4 x Float32 into a vector of 4 x Int32.
/// @param operand A 128-bit vector of 4 x Float32.
/// @returns A 128-bit integer vector of 4 x Int32 containing the converted values.
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4FromCXFloat32x4(CXFloat32x4 operand)
{
    return _mm_cvtps_epi32(operand);
}

/// Converts a vector of 4 x Float32 into a vector of 4 x Int32, truncating the result when it is inexact.
/// @param operand A 128-bit vector of 4 x Float32.
/// @returns A 128-bit vector of 4 x Int32 containing the converted values.
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4FromCXFloat32x4AllowTruncating(CXFloat32x4 operand)
{
    return _mm_cvttps_epi32(operand);
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Negate(const CXInt32x4 storage)
{
    return _mm_sub_epi32(CXInt32x4MakeZero(), storage);
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXInt32x4Absolute(const CXInt32x4 storage)
{
    #define CXInt32x4BitwiseExclusiveOr(operand) _mm_xor_si128(operand, CXInt32x4MakeRepeatingElement(0xFFFFFFFF))
    #define CXInt32x4CompareEqual(lhs, rhs) CXInt32x4BitwiseExclusiveOr(_mm_cmplt_epi32(lhs, rhs))
    CXInt32x4 comparison = CXInt32x4CompareEqual(storage, CXInt32x4MakeZero());
    CXInt32x4 negated = CXInt32x4Negate(storage);
    return _mm_xor_si128(negated, _mm_and_si128(comparison, _mm_xor_si128(storage, negated)));
    #undef CXInt32x4CompareEqual
    #undef CXInt32x4BitwiseExclusiveOr
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Add(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    return _mm_add_epi32(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Subtract(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    return _mm_sub_epi32(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Multiply(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    // SSE2 does not have a native multiply operation for 32bit ints
    __m128i temp0 = _mm_mul_epu32(lhs, rhs);
    __m128i temp1 = _mm_mul_epu32(_mm_srli_si128(lhs, 4), _mm_srli_si128(rhs, 4));
    return _mm_unpacklo_epi32(
        _mm_shuffle_epi32(temp0, _MM_SHUFFLE(0, 0, 2, 0)),
        _mm_shuffle_epi32(temp1, _MM_SHUFFLE(0, 0, 2, 0))
    );
}
