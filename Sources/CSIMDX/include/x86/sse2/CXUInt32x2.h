#pragma once

#include "CXTypes_t.h"
#include "CXInt32x2.h"

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Make(UInt32 value0, UInt32 value1)
{
    return CXInt32x2Make(value0, value1);
}

/// Loads 2 x UInt32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x UInt32 values
/// @return CXUInt32x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2MakeLoad(const UInt32* pointer)
{
    return CXInt32x2MakeLoad((const Int32*)pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2MakeRepeatingElement(const UInt32 value)
{
    return CXInt32x2MakeRepeatingElement(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2MakeZero(void)
{
    return CXInt32x2MakeZero();
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(UInt32) CXUInt32x2GetElement(const CXUInt32x2 storage, const int index)
{
    return CXInt32x2GetElement(storage, index);
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXUInt32x2SetElement(CXUInt32x2* storage, const int index, const UInt32 value)
{
    return CXInt32x2SetElement(storage, index, value);
}

// MARK: - Arithmetics

/// Returns the given storage unchanged. Allows for symmetry with signed values.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Absolute(const CXUInt32x2 storage)
{
    return storage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Add(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return CXInt32x2Add(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Subtract(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return CXInt32x2Subtract(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Multiply(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return CXInt32x2Multiply(lhs, rhs);
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseNot(const CXUInt32x2 operand)
{
    return CXInt32x2BitwiseNot(operand);
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseAnd(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return CXInt32x2BitwiseAnd(lhs, rhs);
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseAndNot(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return CXInt32x2BitwiseAndNot(lhs, rhs);
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseOr(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return CXInt32x2BitwiseOr(lhs, rhs);
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseExclusiveOr(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    return CXInt32x2BitwiseExclusiveOr(lhs, rhs);
}

// MARK: Shifting

/// Left-shifts each 64-bit value in the 128-bit integer storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2ShiftLeft(const CXUInt32x2 lhs, const UInt32 rhs)
{
    return CXInt32x2ShiftLeft(lhs, rhs);
}

/// Right-shifts each 64-bit value in the 128-bit integer storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2ShiftRight(const CXUInt32x2 lhs, const UInt32 rhs)
{
    return CXInt32x2ShiftRight(lhs, rhs);
}
