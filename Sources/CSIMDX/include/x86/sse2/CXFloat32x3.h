#pragma once

#include "CXFloat32x4.h"

// MARK: Designated Initializers

/// Returns an intrinsic initialized to the 3 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Make(Float32 value0, Float32 value1, Float32 value2)
{
    return CXFloat32x4Make(value0, value1, value2, 0.f);
}

/// Loads 3 x Float32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 3 x Float32 values
/// @return CXFloat32x3(pointer[0], pointer[1], pointer[2])
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeLoad(const Float32* pointer)
{
    CXFloat32x4 storage = CXFloat32x4MakeLoad(pointer);
    CXFloat32x4SetElement(&storage, 3, 0.f); // zero-out the last float32
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeRepeatingElement(const Float32 value)
{
    CXFloat32x4 storage = CXFloat32x4MakeRepeatingElement(value);
    CXFloat32x4SetElement(&storage, 3, 0.f); // zero-out the last float32
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeZero(void)
{
    return CXFloat32x4MakeZero();
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x3GetElement(const CXFloat32x3 storage, const int index)
{
    return CXFloat32x4GetElement(storage, index);
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXFloat32x3SetElement(CXFloat32x3* storage, const int index, const Float32 value)
{
    return CXFloat32x4SetElement(storage, index, value);
}

// MARK: - Conversion

/// Converts a vector of 3 x Int32 into a storage of 3 x Float32.
/// @param operand A 128-bit integer storage.
/// @returns A 128-bit storage of 3 x Float32 containing the converted values.
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3FromCXInt32x3(CXInt32x3 operand)
{
    return CXFloat32x4FromCXInt32x4(operand);
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Negate(const CXFloat32x3 storage)
{
    return CXFloat32x4Negate(storage);
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Absolute(const CXFloat32x3 storage)
{
    return CXFloat32x4Absolute(storage);
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Add(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return CXFloat32x4Add(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Subtract(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return CXFloat32x4Subtract(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Multiply(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return CXFloat32x4Multiply(lhs, rhs);
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Divide(const CXFloat32x3 lhs, CXFloat32x3 rhs)
{
    CXFloat32x3SetElement(&rhs, 3, 1.f); // Avoids division by zero, but 1.f instead
    return CXFloat32x4Divide(lhs, rhs);
}
