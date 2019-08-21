#pragma once

#include "Types.h"
#include "CXFloat32x4.h"

// MARK: Designated Initializers

/// Returns an 128bit intrinsic type initialized to the 3 given Float32 values, last one to zero.
/// @param value0 1st Float32 value
/// @param value1 2nd Float32 value
/// @param value2 3rd Float32 value
STATIC_INLINE_INTRINSIC(CXFloat32x3)
CXFloat32x3Make(const Float32 value0, const Float32 value1, const Float32 value2)
{
    return CXFloat32x4Make(value0, value1, value2, 0.f);
}

/// Loads 3 floating point values from unaligned memory.
/// @param pointer Unaligned memory pointer to 3 floating point values
/// @return CXFloat32x3(pointer[0], pointer[1], pointer[2])
STATIC_INLINE_INTRINSIC(CXFloat32x3)
CXFloat32x3Load(const float* pointer)
{
    CXFloat32x4 float32x4 = CXFloat32x4Load(pointer);
    float32x4[3] = 0.f; // zero-out the last float32
    return (CXFloat32x3)float32x4;
}

/// Returns an 128bit intrinsic type initialized all 3 Float32 values to given value.
STATIC_INLINE_INTRINSIC(CXFloat32x3)
CXFloat32x3MakeRepeatingElement(const Float32 value)
{
    return CXFloat32x3Make(value, value, value);
}

/// Returns an register type with all values initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat32x3)
CXFloat32x3MakeZero(void)
{
    return CXFloat32x4MakeZero();
}

// MARK: Getter/Setter

/// Returns the element at `index` from the `float32x3` collection.
/// @param float32x3 The element collection to look up values
/// @param index The index of the value to return.
STATIC_INLINE_INTRINSIC(Float32)
CXFloat32x3GetElement(const CXFloat32x3 float32x3, const Int32 index)
{
    return CXFloat32x4GetElement(float32x3, index);
}

/// Sets the element at `index` from `collection`.
/// @param collection The collection to look up values
/// @param index The index of the value to return.
STATIC_INLINE_INTRINSIC(void)
CXFloat32x3SetElement(const CXFloat32x3* float32x3, const Int32 index, const Float32 value)
{
    return CXFloat32x4SetElement(float32x3, index, value);
}

// MARK: Additive Arithmetics

/// Adds two float32x3 (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3)
CXFloat32x3Add(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return CXFloat32x4Add(lhs, rhs);
}

/// Subtracts a float32x3 from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3)
CXFloat32x3Subtract(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return CXFloat32x4Subtract(lhs, rhs);
}

/// Returns the negated value (element-wise).
/// @param float32x3 Source collection
STATIC_INLINE_INTRINSIC(CXFloat32x3)
CXFloat32x3Negate(const CXFloat32x3 float32x3)
{
    return CXFloat32x4Negate(float32x3);
}

// MARK: Multiplicative Arithmetics

/// Multiplies two float32x3 (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3)
CXFloat32x3Multiply(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    return CXFloat32x4Multiply(lhs, rhs);
}
