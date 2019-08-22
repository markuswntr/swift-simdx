#pragma once

#include "CXFloat64_t.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Make(Float64 value0, Float64 value1)
{
    return _mm_setr_pd(value0, value1);
}

/// Loads 2 x Float64 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Float64 values
/// @return CXFloat64x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Load(const Float64* pointer)
{
    return _mm_loadu_pd(pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2MakeRepeatingElement(const Float64 value)
{
    return _mm_set1_pd(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2MakeZero(void)
{
    return _mm_setzero_pd();
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Float64) CXFloat64x2GetElement(const CXFloat64x2 storage, const int index)
{
    return storage[index]; // TODO: Function call instead?
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXFloat64x2SetElement(CXFloat64x2* storage, const int index, const Float64 value)
{
    (*storage)[index] = value; // TODO: Function call instead?
}

// MARK: - Arithmetics

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Absolute(const CXFloat64x2 storage)
{
    __m64 SIGN_BIT = _mm_cvtsi64_m64(~(1LL << 63));
    union { CXFloat64x2 storage; __m128i integers; } Signed;
    Signed.integers = _mm_setr_epi64(SIGN_BIT, SIGN_BIT);
    return _mm_and_ps(storage, Signed.storage);
}

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Negate(const CXFloat64x2 storage)
{
    return _mm_sub_pd(CXFloat64x2MakeZero(), storage);
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Add(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_add_pd(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Subtract(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_sub_pd(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Multiply(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_mul_pd(lhs, rhs);
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Divide(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_div_pd(lhs, rhs);
}
