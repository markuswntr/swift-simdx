#pragma once

#include "CXInt32x4.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Make(Int32 value0, Int32 value1)
{
    return CXInt32x4Make(value0, value1, 0, 0);
}

/// Loads 2 x Int32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Int32 values
/// @return CXInt32x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2MakeLoad(const Int32* pointer)
{
    return _mm_loadu_si64(pointer); // Loads only the first 64 bits using given pointer and zeros the rest.
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2MakeRepeatingElement(const Int32 value)
{
    return CXInt32x2Make(value, value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2MakeZero(void)
{
    return CXInt32x4MakeZero();
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int32) CXInt32x2GetElement(const CXInt32x2 storage, const int index)
{
    return CXInt32x4GetElement(storage, index);
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXInt32x2SetElement(CXInt32x2* storage, const int index, const Int32 value)
{
    CXInt32x4SetElement(storage, index, value);
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Negate(const CXInt32x2 storage)
{
    return CXInt32x4Negate(storage);
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Absolute(const CXInt32x2 storage)
{
    return CXInt32x4Absolute(storage);
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Add(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
    return CXInt32x4Add(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Subtract(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
    return CXInt32x4Subtract(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Multiply(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
    return CXInt32x4Multiply(lhs, rhs);
}
