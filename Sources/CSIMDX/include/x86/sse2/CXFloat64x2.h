#pragma once

#include "CXTypes_t.h"

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Make(Float64 value0, Float64 value1)
{
    return _mm_setr_pd(value0, value1);
}

/// Loads 2 x Float64 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Float64 values
/// @return CXFloat64x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2MakeLoad(const Float64* pointer)
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

// MARK: Getter/Setter

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

// MARK: - Conversion

/// Converts the 2 x Float32 elements of a CXFloat32x2 into 2 x Float64 values, returned in a 128-bit storage.
/// @param storage A 128-bit storage of two single-precision floating-point elements.
/// @returns A 128-bit vector of 2 x Float64 containing the converted values.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2FromCXFloat32x2(CXFloat32x2 operand)
{
    return _mm_cvtps_pd(operand);
}

/// Converts the 2 x Int32 elements of a CXInt32x2 into 2 x Float64 values, returned in a 128-bit storage.
/// @param storage A 128-bit storage of 2 x Int32 elements.
/// @returns A 128-bit vector of 2 x Float64 containing the converted values.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2FromCXInt32x2(CXInt32x2 operand)
{
    return _mm_cvtepi32_pd(operand);
}

/// Converts the 2 x Int64 elements of a CXInt64x2 into 2 x Float64 values, returned in a 128-bit storage.
/// @param storage A 128-bit storage of 2 x Int64 elements.
/// @returns A 128-bit vector of 2 x Float64 containing the converted values.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2FromCXInt64x2(CXInt64x2 operand)
{
    return _mm_castsi128_pd(operand);
}

// MARK: - Comparison

/// Compares each of the corresponding double-precision values of the 128-bit storages of 2 x Float64 for equality.
///
/// Each comparison yields 0x0 for false, 0xFFFFFFFFFFFFFFFF for true.
///
/// @param lhs A 128-bit storage of 2 x Float64.
/// @param rhs A 128-bit storage of 2 x Float64.
/// @returns A 128-bit storage containing the comparison results.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2CompareEqual(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_cmpeq_pd(lhs, rhs);
}

/// Compares each of the corresponding double-precision values of the 128-bit storages of 2 x Float64 to determine
/// if the values in the first operand are unequal to those in the second operand.
///
/// Each comparison yields 0x0 for false, 0xFFFFFFFFFFFFFFFF for true.
///
/// @param lhs A 128-bit storage of 2 x Float64.
/// @param rhs A 128-bit storage of 2 x Float64.
/// @returns A 128-bit storage containing the comparison results.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2CompareNotEqual(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_cmpneq_pd(lhs, rhs);
}

/// Compares each of the corresponding double-precision values of the 128-bit storages of 2 x Float64
/// to determine if the values in the first operand are less than those in the second operand.
///
/// Each comparison yields 0x0 for false, 0xFFFFFFFFFFFFFFFF for true.
///
/// @param lhs A 128-bit storage of 2 x Float64.
/// @param rhs A 128-bit storage of 2 x Float64.
/// @returns A 128-bit storage containing the comparison results.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2CompareLessThan(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_cmplt_pd(lhs, rhs);
}

/// Compares each of the corresponding double-precision values of the 128-bit storages of 2 x Float64 to
/// determine if the values in the first operand are less than or equal to those in the second operand.
///
/// Each comparison yields 0x0 for false, 0xFFFFFFFFFFFFFFFF for true.
///
/// @param lhs A 128-bit storage of 2 x Float64.
/// @param rhs A 128-bit storage of 2 x Float64.
/// @returns A 128-bit storage containing the comparison results.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2CompareLessThanOrEqual(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_cmple_pd(lhs, rhs);
}

/// Compares each of the corresponding double-precision values of the 128-bit storages of 2 x Float64
/// to determine if the values in the first operand are greater than those in the second operand.
///
/// Each comparison yields 0x0 for false, 0xFFFFFFFFFFFFFFFF for true.
///
/// @param lhs A 128-bit storage of 2 x Float64.
/// @param rhs A 128-bit storage of 2 x Float64.
/// @returns A 128-bit storage containing the comparison results.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2CompareGreaterThan(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_cmpgt_pd(lhs, rhs);
}

/// Compares each of the corresponding double-precision values of the 128-bit storages of 2 x Float64 to
/// determine if the values in the first operand are greater than or equal to those in the second operand.
///
/// Each comparison yields 0x0 for false, 0xFFFFFFFFFFFFFFFF for true.
///
/// @param lhs A 128-bit storage of 2 x Float64.
/// @param rhs A 128-bit storage of 2 x Float64.
/// @returns A 128-bit storage containing the comparison results.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2CompareGreaterThanOrEqual(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_cmpge_pd(lhs, rhs);
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of the two 128-bit storages of 2 x Float64.
/// Returns the storage containing the lesser of each pair of values.
/// @param lhs A 128-bit storage of 2 x Float64 containing one of the operands.
/// @param rhs A 128-bit storage of 2 x Float64 containing one of the operands.
/// @return A 128-bit storage of 2 x Float64 containing the minimum values between both operands.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Minimum(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_min_pd(lhs, rhs);
}

/// Performs element-by-element comparison of the two 128-bit storages of 2 x Float64.
/// Returns the storage containing the greatre of each pair of values.
/// @param lhs A 128-bit storage of 2 x Float64 containing one of the operands.
/// @param rhs A 128-bit storage of 2 x Float64 containing one of the operands.
/// @return A 128-bit storage of 2 x Float64 containing the minimum values between both operands.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Maximum(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_max_pd(lhs, rhs);
}

// MARK: Bitwise

/// Performs a bitwise AND of two 128-bit storages of 2 x Float64.
/// @param lhs A 128-bit storage of 2 x Float64 containing one of the source operands.
/// @param rhs A 128-bit storage of 2 x Float64 containing one of the source operands.
/// @returns A 128-bit storage of 2 x Float64 containing the bitwise AND of the values between both operands.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2BitwiseAnd(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_and_pd(lhs, rhs);
}

/// Performs a bitwise AND of two 128-bit storages of 2 x Float64, using the one's
/// complement of the values contained in the first source operand.
/// @param lhs A 128-bit storage of 2 x Float64 containing the left source operand.
///            The one's complement of this value is used in the bitwise AND.
/// @param rhs A 128-bit storage of 2 x Float64 containing the right source operand.
/// @returns A 128-bit storage of 2 x Float64 containing the bitwise AND of the values in the second operand
///          and the one's complement of the first operand.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2BitwiseAndNot(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_andnot_pd(lhs, rhs);
}

/// Performs a bitwise OR of two 128-bit storages of 2 x Float64.
/// @param lhs A 128-bit storage of 2 x Float64 containing one of the source operands.
/// @param rhs A 128-bit storage of 2 x Float64 containing one of the source operands.
/// @returns A 128-bit storage of 2 x Float64 containing the bitwise OR of the values between both operands.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2BitwiseOr(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_or_pd(lhs, rhs);
}

/// Performs a bitwise XOR of two 128-bit storages of 2 x Float64.
/// @param lhs A 128-bit storage of 2 x Float64 containing one of the source operands.
/// @param rhs A 128-bit storage of 2 x Float64 containing one of the source operands.
/// @returns A 128-bit storage of 2 x Float64 containing the bitwise XOR of the values between both operands.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2BitwiseExclusiveOr(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    return _mm_xor_pd(lhs, rhs);
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Negate(const CXFloat64x2 storage)
{
    return _mm_sub_pd(CXFloat64x2MakeZero(), storage);
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Absolute(const CXFloat64x2 storage)
{
    __m64 SIGN_BIT = _mm_cvtsi64_m64(~(1LL << 63));
    union { CXFloat64x2 storage; __m128i signs; } Signed;
    Signed.signs = _mm_setr_epi64(SIGN_BIT, SIGN_BIT);
    return _mm_and_ps(storage, Signed.storage);
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

/// Calculates the square root of each value stored in `operand` and returns the results.
///
/// @param operant The storage of which to calculate square root values.
/// @return [ sqrt(operand[0]), sqrt(operand[1] ]
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2SquareRoot(const CXFloat64x2 operand)
{
    return _mm_sqrt_pd(operand);
}
