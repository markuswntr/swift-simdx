#pragma once

#include "CXInt32x3.h"

// MARK: Designated Initializers

/// Returns an intrinsic initialized to the 3 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Make(UInt32 value0, UInt32 value1, UInt32 value2)
{
    return CXInt32x3Make(value0, value1, value2);
}

/// Loads 3 x UInt32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 3 x UInt32 values
/// @return CXUInt32x3(pointer[0], pointer[1], pointer[2])
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3MakeLoad(const UInt32* pointer)
{
    return CXInt32x3MakeLoad((const Int32*)pointer);
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3MakeRepeatingElement(const UInt32 value)
{
    return CXInt32x3MakeRepeatingElement(value);
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3MakeZero(void)
{
    return CXInt32x3MakeZero();
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(UInt32) CXUInt32x3GetElement(const CXUInt32x3 storage, const int index)
{
    return CXInt32x3GetElement(storage, index);
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXUInt32x3SetElement(CXUInt32x3* storage, const int index, const UInt32 value)
{
    return CXInt32x3SetElement(storage, index, value);
}

// MARK: - Arithmetics

/// Returns the given storage unchanged. Allows for symmetry with signed values.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Absolute(const CXUInt32x3 storage)
{
    return storage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Add(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return CXInt32x3Add(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Subtract(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return CXInt32x3Subtract(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Multiply(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    return CXInt32x3Multiply(lhs, rhs);
}
