#pragma once

#include "CXInt64x2.h"

// MARK: Designated Initializers

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Make(UInt64 value0, UInt64 value1)
{
    return CXInt64x2Make(value0, value1);
}

/// Loads 2 x UInt64 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x UInt64 values
/// @return CXUInt64x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2MakeLoad(const UInt64* pointer)
{
    return CXInt64x2MakeLoad((const Int64*)pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2MakeRepeatingElement(const UInt64 value)
{
    return CXInt64x2MakeRepeatingElement(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2MakeZero(void)
{
    return CXInt64x2MakeZero();
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(UInt64) CXUInt64x2GetElement(const CXUInt64x2 storage, const int index)
{
    return CXInt64x2GetElement(storage, index);
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXUInt64x2SetElement(CXUInt64x2* storage, const int index, const UInt64 value)
{
    return CXInt64x2SetElement(storage, index, value);
}

// MARK: - Arithmetics

/// Returns the given storage unchanged. Allows for symmetry with signed values.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Absolute(const CXUInt64x2 storage)
{
    return storage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Add(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return CXInt64x2Add(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Subtract(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return CXInt64x2Subtract(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Multiply(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return CXInt64x2Multiply(lhs, rhs);
}

// MARK: Logical

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseNot(const CXUInt64x2 operand)
{
    return CXInt64x2BitwiseNot(operand);
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseAnd(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return CXInt64x2BitwiseAnd(lhs, rhs);
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseAndNot(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return CXInt64x2BitwiseAndNot(lhs, rhs);
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseOr(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return CXInt64x2BitwiseOr(lhs, rhs);
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseExclusiveOr(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    return CXInt64x2BitwiseExclusiveOr(lhs, rhs);
}

// MARK: Shifting

/// Left-shifts each 64-bit value in the 128-bit integer storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2ShiftLeft(const CXUInt64x2 lhs, const UInt64 rhs)
{
    return CXInt64x2ShiftLeft(lhs, rhs);
}

/// Right-shifts each 64-bit value in the 128-bit integer storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2ShiftRight(const CXUInt64x2 lhs, const UInt64 rhs)
{
    return CXInt64x2ShiftRight(lhs, rhs);
}

