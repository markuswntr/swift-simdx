#pragma once

#include "CXInt_t.h"
#include "CXUInt_t.h"
#include "CXFloat_t.h"
#include "Attributes.h"

// MARK: Designated Initializers

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Make(Int64 value0, Int64 value1)
{
    return _mm_setr_epi64(_mm_cvtsi64_m64(value0), _mm_cvtsi64_m64(value1));
}

/// Loads 2 x Int64 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Int64 values
/// @return CXInt64x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeLoad(const Int64* pointer)
{
    return _mm_loadu_si128((const __m128i*)pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeRepeatingElement(const Int64 value)
{
    return _mm_set1_epi64(_mm_cvtsi64_m64(value));
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeZero(void)
{
    return _mm_setzero_si128();
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int64) CXInt64x2GetElement(const CXInt64x2 storage, const int index)
{
    return storage[index];  // TODO: Function call instead?
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXInt64x2SetElement(CXInt64x2* storage, const int index, const Int64 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Conversion

/// Converts the 2 x Int32 elements of a CXInt32x2 into 2 x Int64 values, returned in a 128-bit storage.
/// @param storage A storage of 2 x Int32 elements.
/// @returns A storage of 2 x Int64 containing the converted values.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2FromCXInt32x2(CXInt32x2 operand)
{
    return (__m128i)__builtin_convertvector( // TODO: NO intel intrinsic?
        __builtin_shufflevector((__v4si)operand, (__v4si)operand, 0, 1), __v2di);
}

/// Converts the 2 x Float32 elements of a CXFloat32x2 into 2 x Int64 values, returned in a 128-bit storage.
/// @param storage A storage of 2 x Float32 elements.
/// @returns A storage of 2 x Int64 containing the converted values.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2FromCXFloat32x2(CXFloat32x2 operand)
{
    return (__m128i)__builtin_convertvector( // TODO: NO intel intrinsic?
        __builtin_shufflevector((__v4sf)operand, (__v4sf)operand, 0, 1), __v2di);
}

/// Converts the 2 x Float64 elements of a CXFloat64x2 into 2 x Int64 values, returned in a 128-bit storage.
/// @param storage A storage of 2 x Float64 elements.
/// @returns A storage of 2 x Int64 containing the converted values.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2FromCXFloat64x2(CXFloat64x2 operand)
{
    return _mm_castpd_si128(operand);
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Negate(const CXInt64x2 storage)
{
    return _mm_sub_epi64(CXInt64x2MakeZero(), storage);
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXInt64x2Absolute(const CXInt64x2 storage)
{
     // TODO: SSE2 does not have a native abs operation for storages with 64 bit ints
    return CXInt64x2Make(
        llabs(CXInt64x2GetElement(storage, 0)),
        llabs(CXInt64x2GetElement(storage, 1))
    );
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Add(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return _mm_add_epi64(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Subtract(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return _mm_sub_epi64(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Multiply(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    // TODO: SSE2 does not have a native multiply operation for storages with 64 bit ints
    return CXInt64x2Make(
        CXInt64x2GetElement(lhs, 0) * CXInt64x2GetElement(rhs, 0),
        CXInt64x2GetElement(lhs, 1) * CXInt64x2GetElement(rhs, 1)
    );
}

STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Divide(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    // TODO: SSE2 does not have a native integer division operation but find something better
    return CXInt64x2Make(
        CXInt64x2GetElement(lhs, 0) / CXInt64x2GetElement(rhs, 0),
        CXInt64x2GetElement(lhs, 1) / CXInt64x2GetElement(rhs, 1)
    );
}

STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Modulo(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    // TODO: SSE2 does not have a native integer division operation but find something better
    return CXInt64x2Make(
        CXInt64x2GetElement(lhs, 0) % CXInt64x2GetElement(rhs, 0),
        CXInt64x2GetElement(lhs, 1) % CXInt64x2GetElement(rhs, 1)
    );
}

// MARK: Logical

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseNot(const CXInt64x2 operand)
{
    return _mm_xor_si128(operand, _mm_set1_epi64(_mm_cvtsi64_m64(-1LL)));
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseAnd(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return _mm_and_si128(rhs, lhs);
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseAndNot(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return _mm_andnot_si128(lhs, rhs);
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseOr(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return _mm_or_si128(lhs, rhs);
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseExclusiveOr(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    return _mm_xor_si128(lhs, rhs);
}

// MARK: Shifting

/// Left-shifts each 64-bit value in the 128-bit integer storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2ShiftLeft(const CXInt64x2 lhs, const Int64 rhs)
{
    return _mm_sll_epi64(lhs, _mm_cvtsi64_si128(rhs));
}

/// Right-shifts each 64-bit value in the 128-bit integer storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2ShiftRight(const CXInt64x2 lhs, const Int64 rhs)
{
    // SSE2 does not have a right shift intrinsic
    __m128i bb, shi, slo, sra2;
    if (rhs <= 32) {
        bb = _mm_cvtsi32_si128(rhs);               // b
        shi = _mm_sra_epi32(lhs, bb);              // a >> b signed dwords
        slo = _mm_srl_epi64(lhs, bb);              // a >> b unsigned qwords
    } else {  // b > 32
        bb = _mm_cvtsi32_si128(rhs - 32);          // b - 32
        shi = _mm_srai_epi32(lhs, 31);             // sign of a
        sra2 = _mm_sra_epi32(lhs, bb);             // a >> (b-32) signed dwords
        slo = _mm_srli_epi64(sra2, 32);          // a >> (b-32) >> 32 (second shift unsigned qword)
    }
    __m128i mask = _mm_setr_epi32(0, -1, 0, -1); // mask for high part containing only sign
    return _mm_or_si128(_mm_and_si128(mask, shi), _mm_andnot_si128(mask, slo));
}
