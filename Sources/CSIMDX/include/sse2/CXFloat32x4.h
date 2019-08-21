#pragma once

#include "Types.h"

// MARK: Designated Initializers

/// Returns an 128bit intrinsic type initialized to the 4 given Float32 values.
/// @param value0 1st Float32 value
/// @param value1 2nd Float32 value
/// @param value2 3rd Float32 value
/// @param value3 4th Float32 value
STATIC_INLINE_INTRINSIC(CXFloat32x4)
CXFloat32x4Make(const Float32 value0, const Float32 value1, const Float32 value2, const Float32 value3)
{
    return _mm_setr_ps(value0, value1, value2, value3);
}

/// Loads 4 floating point values from unaligned memory.
/// @param pointer Unaligned memory pointer to 4 floating point values
/// @return CXFloat32x4(pointer[0], pointer[1], pointer[2], pointer[3])
STATIC_INLINE_INTRINSIC(CXFloat32x4)
CXFloat32x4Load(const float* pointer)
{
    return _mm_loadu_ps(pointer);
}

/// Returns an 128bit intrinsic type initialized all 4 Float32 values to given value.
STATIC_INLINE_INTRINSIC(CXFloat32x4)
CXFloat32x4MakeRepeatingElement(const Float32 value)
{
    return CXFloat32x4Make(value, value, value, value);
}

/// Returns an register type with all values initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat32x4)
CXFloat32x4MakeZero(void)
{
    return _mm_setzero_ps();
}

// MARK: Getter/Setter

/// Returns the element at `index` from the `float32x4` collection.
/// @param float32x4 The element collection to look up values
/// @param index The index of the value to return.
STATIC_INLINE_INTRINSIC(Float32)
CXFloat32x4GetElement(const CXFloat32x4 float32x4, const Int32 index)
{
    return (((Float32*)&(float32x4))[index]);
}

/// Sets the element at `index` from `collection`.
/// @param collection The collection to look up values
/// @param index The index of the value to return.
STATIC_INLINE_INTRINSIC(void)
CXFloat32x4SetElement(const CXFloat32x4* float32x4, const Int32 index, const Float32 value)
{
    ((Float32*)float32x4)[index] = value;
}

// MARK: Additive Arithmetics

/// Adds two float32x4 (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x4)
CXFloat32x4Add(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return _mm_add_ps(lhs, rhs);
}

/// Subtracts a float32x4 from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x4)
CXFloat32x4Subtract(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return _mm_sub_ps(lhs, rhs);
}

/// Returns the negated value (element-wise).
/// @param float32x4 Source collection
STATIC_INLINE_INTRINSIC(CXFloat32x4)
CXFloat32x4Negate(const CXFloat32x4 float32x4)
{
    return CXFloat32x4Subtract(CXFloat32x4MakeZero(), float32x4);
}

// MARK: Multiplicative Arithmetics

/// Multiplies two float32x4 (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x4)
CXFloat32x4Multiply(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    return _mm_mul_ps(lhs, rhs);
}
