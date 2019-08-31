#pragma once

#include "CXFloat32x4.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Make(Float32 value0, Float32 value1)
{
    return CXFloat32x4Make(value0, value1, 0.f, 0.f);
}

/// Loads 2 x Float32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Float32 values
/// @return CXFloat32x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeLoad(const Float32* pointer)
{
    CXFloat32x4 storage = CXFloat32x4MakeLoad(pointer);
    CXFloat32x4SetElement(&storage, 2, 0.f); // zero-out the second last float32
    CXFloat32x4SetElement(&storage, 3, 0.f); // zero-out the last float32
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeRepeatingElement(const Float32 value)
{
    CXFloat32x4 storage = CXFloat32x4MakeRepeatingElement(value);
    CXFloat32x4SetElement(&storage, 2, 0.f); // zero-out the second last float32
    CXFloat32x4SetElement(&storage, 3, 0.f); // zero-out the last float32
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeZero(void)
{
    return CXFloat32x4MakeZero();
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x2GetElement(const CXFloat32x2 storage, const int index)
{
    return CXFloat32x4GetElement(storage, index);
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXFloat32x2SetElement(CXFloat32x2* storage, const int index, const Float32 value)
{
    CXFloat32x4SetElement(storage, index, value);
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Negate(const CXFloat32x2 storage)
{
    return CXFloat32x4Negate(storage);
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Absolute(const CXFloat32x2 storage)
{
    return CXFloat32x4Absolute(storage);
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Add(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return CXFloat32x4Add(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Subtract(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return CXFloat32x4Subtract(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Multiply(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return CXFloat32x4Multiply(lhs, rhs);
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Divide(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    CXFloat32x4SetElement(&rhs, 2, 1.f); // Prepare rhs value, to avoid a ...
    CXFloat32x4SetElement(&rhs, 3, 1.f); // ... division by zero, but 1 instead
    return CXFloat32x4Divide(lhs, rhs);
}
