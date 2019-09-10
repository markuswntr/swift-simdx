#pragma once

#include <math.h>
#include "CXTypes_t.h"

/// Initializes a storage to given elements, from least-significant to most-significant bits.
/// @return `(CXFloat32x2){ element0, element1 }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Make(Float32 element0, Float32 element1)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x2){ element0, element1 };
#else
    return (CXFloat32x2){ .elements = [ element0, element1 ] };
#endif
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXFloat32x2){ pointer[0], pointer[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeLoad(const Float32* pointer)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x2){ pointer[0], pointer[1] };
#else
    return (CXFloat32x2){ .elements = [ pointer[0], pointer[1] ] };
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXFloat32x2){ value, value }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeRepeatingElement(const Float32 value)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x2)(value);
#else
    return (CXFloat32x2){ .elements = [ value, value ] };
#endif
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
/// @return `(CXFloat32x2){ 0.f, 0.f }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeZero(void)
{
    return CXFloat32x2MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x2GetElement(const CXFloat32x2 storage, const int index)
{
#if __has_extension(attribute_ext_vector_type)
    return storage[index];
#else
    return storage.elements[index];
#endif
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXFloat32x2SetElement(CXFloat32x2* storage, const int index, const Float32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage)[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2FromCXFloat64x2(CXFloat64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXFloat32x2);
#else
    return (CXFloat32x2){ .elements = [ (Float32)(operand.elements[0]), (Float32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2FromCXInt32x2(CXInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXFloat32x2);
#else
    return (CXFloat32x2){ .elements = [ (Float32)(operand.elements[0]), (Float32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2FromCXUInt32x2(CXUInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXFloat32x2);
#else
    return (CXFloat32x2){ .elements = [ (Float32)(operand.elements[0]), (Float32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2FromCXInt64x2(CXInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXFloat32x2);
#else
    return (CXFloat32x2){ .elements = [ (Float32)(operand.elements[0]), (Float32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2FromCXUInt64x2(CXUInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXFloat32x2);
#else
    return (CXFloat32x2){ .elements = [ (Float32)(operand.elements[0]), (Float32)(operand.elements[1]) ] };
#endif
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXFloat32x2){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Minimum(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    Float64 lhs0 = CXFloat32x2GetElement(lhs, 0), rhs0 = CXFloat32x2GetElement(rhs, 0);
    Float64 lhs1 = CXFloat32x2GetElement(lhs, 1), rhs1 = CXFloat32x2GetElement(rhs, 1);

#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x2){
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1
    };
#else
    return (CXFloat32x2){ .elements = [
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1
    ]};
#endif
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXFloat32x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Maximum(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    Float64 lhs0 = CXFloat32x2GetElement(lhs, 0), rhs0 = CXFloat32x2GetElement(rhs, 0);
    Float64 lhs1 = CXFloat32x2GetElement(lhs, 1), rhs1 = CXFloat32x2GetElement(rhs, 1);

#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x2){
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1
    };
#else
    return (CXFloat32x2){ .elements = [
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1
    ]};
#endif
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CXFloat32x2){ -(operand[0]), -(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Negate(const CXFloat32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return -(operand);
#else
    return (CXFloat32x2){ .elements = [
        -CXFloat32x2GetElement(operand, 0),
        -CXFloat32x2GetElement(operand, 1)
    ]};
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CXFloat32x2){ abs(operand[0]), abs(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Absolute(const CXFloat32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x2){
        fabsf(CXFloat32x2GetElement(operand, 0)),
        fabsf(CXFloat32x2GetElement(operand, 1))
    };
#else
    return (CXFloat32x2){ .elements = [
        fabsf(CXFloat32x2GetElement(operand, 0)),
        fabsf(CXFloat32x2GetElement(operand, 1))
    ]};
#endif
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXFloat32x2){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Add(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs + rhs;
#else
    return (CXFloat32x2){ .elements = [
         CXFloat32x2GetElement(lhs, 0) + CXFloat32x2GetElement(rhs, 0),
         CXFloat32x2GetElement(lhs, 1) + CXFloat32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXFloat32x2){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Subtract(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs - rhs;
#else
    return (CXFloat32x2){ .elements = [
         CXFloat32x2GetElement(lhs, 0) - CXFloat32x2GetElement(rhs, 0),
         CXFloat32x2GetElement(lhs, 1) - CXFloat32x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXFloat32x2){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Multiply(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs * rhs;
#else
    return (CXFloat32x2){ .elements = [
         CXFloat32x2GetElement(lhs, 0) * CXFloat32x2GetElement(rhs, 0),
         CXFloat32x2GetElement(lhs, 1) * CXFloat32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Divides two storages (element-wise).
/// @return `(CXFloat32x2){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Divide(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs / rhs;
#else
    return (CXFloat32x2){ .elements = [
         CXFloat32x2GetElement(lhs, 0) / CXFloat32x2GetElement(rhs, 0),
         CXFloat32x2GetElement(lhs, 1) / CXFloat32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Calculates the square root (element-wise).
/// @return `(CXFloat32x2){ sqrt(operand[0]), sqrt(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2SquareRoot(const CXFloat32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x2){
        sqrtf(CXFloat32x2GetElement(operand, 0)),
        sqrtf(CXFloat32x2GetElement(operand, 1))
    };
#else
    return (CXFloat32x2){ .elements = [
       sqrtf(CXFloat32x2GetElement(operand, 0)),
       sqrtf(CXFloat32x2GetElement(operand, 1))
    ]};
#endif
}
