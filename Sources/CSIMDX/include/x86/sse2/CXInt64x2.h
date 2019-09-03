#pragma once

#include "CXInt64_t.h"

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
