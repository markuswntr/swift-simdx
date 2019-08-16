#pragma once

#include "CXFloat32x4.h"

// MARK: - Float32x2 register type -

/// 128bit floating point intrinsic. The first Float32 is stored in the lowest 32 bits, and so on.
/// Last two Float32's are unused and "zero-ed out".
typedef __m128 CXFloat32x2;

// MARK: Designated Initializers

/// Returns an 128bit intrinsic type initialized to the 2 given Float32 values, last two to zero.
/// @param value0 1st Float32 value
/// @param value1 2nd Float32 value
STATIC_ALWAYS_INLINE(CXFloat32x2)
CXFloat32x2Make(const Float32 value0, const Float32 value1)
{
    return CXFloat32x4Make(value0, value1, 0.f, 0.f);
}

/// Loads 2 floating point values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 floating point values
/// @return CXFloat32x2(pointer[0], pointer[1])
STATIC_ALWAYS_INLINE(CXFloat32x2)
CXFloat32x2Load(const float* pointer)
{
    CXFloat32x4 float32x4 = CXFloat32x4Load(pointer);
    ((Float32*)(&float32x4))[2] = 0.f; // zero-out the second last float32
    ((Float32*)(&float32x4))[3] = 0.f; // zero-out the last float32
    return (CXFloat32x2)float32x4;
}

/// Returns an 128bit intrinsic type initialized all 2 Float32 values to given value.
STATIC_ALWAYS_INLINE(CXFloat32x2)
CXFloat32x2MakeRepeatingElement(const Float32 value)
{
    return CXFloat32x2Make(value, value);
}

/// Returns an register type with all values initialized to zero (0.f).
STATIC_ALWAYS_INLINE(CXFloat32x2)
CXFloat32x2MakeZero(void)
{
    return CXFloat32x4MakeZero();
}

// MARK: Getter/Setter

/// Returns the element at `index` from the `float32x2` collection.
/// @param float32x2 The element collection to look up values
/// @param index The index of the value to return.
STATIC_ALWAYS_INLINE(Float32)
CXFloat32x2GetElement(const CXFloat32x2 float32x2, const Int32 index)
{
    return CXFloat32x4GetElement(float32x2, index);
}

/// Sets the element at `index` from `collection`.
/// @param collection The collection to look up values
/// @param index The index of the value to return.
STATIC_ALWAYS_INLINE(void)
CXFloat32x2SetElement(const CXFloat32x2* float32x2, const Int32 index, const Float32 value)
{
    return CXFloat32x4SetElement(float32x2, index, value);
}

// MARK: Comparison

/// Creates a two-part mask based on component-wise == compares of the input vectors
/// @param lhs 1st vector
/// @param rhs 2nd vector
STATIC_ALWAYS_INLINE(CXFloat32x2)
CXFloat32x2Equal(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return _mm_cmpeq_ps(lhs, rhs);
}

// MARK: Additive Arithmetics

/// Adds two float32x2 (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_ALWAYS_INLINE(CXFloat32x2)
CXFloat32x2Add(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return CXFloat32x4Add(lhs, rhs);
}

/// Subtracts a float32x2 from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_ALWAYS_INLINE(CXFloat32x2)
CXFloat32x2Subtract(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return CXFloat32x4Subtract(lhs, rhs);
}

/// Returns the negated value (element-wise).
/// @param float32x2 Source collection
STATIC_ALWAYS_INLINE(CXFloat32x2)
CXFloat32x2Negate(const CXFloat32x2 float32x2)
{
    return CXFloat32x4Negate(float32x2);
}

// MARK: Multiplicative Arithmetics

/// Multiplies two float32x2 (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_ALWAYS_INLINE(CXFloat32x2)
CXFloat32x2Multiply(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    return CXFloat32x4Multiply(lhs, rhs);
}
