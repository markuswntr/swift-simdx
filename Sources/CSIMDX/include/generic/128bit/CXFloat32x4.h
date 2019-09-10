#pragma once

#include <math.h>
#include "CXTypes_t.h"

/// Initializes a storage to given elements, from least-significant to most-significant bits.
/// @return `(CXFloat32x4){ element0, element1, element2, element3 }`
STATIC_INLINE_INTRINSIC(CXFloat32x4)
CXFloat32x4Make(Float32 element0, Float32 element1, Float32 element2, Float32 element3)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x4){ element0, element1, element2, element3 };
#else
    return (CXFloat32x4){ .elements = [ element0, element1, element2, element3 ] };
#endif
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXFloat32x4){ pointer[0], pointer[1], pointer[2], pointer[3] }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeLoad(const Float32* pointer)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x4){ pointer[0], pointer[1], pointer[2], pointer[3] };
#else
    return (CXFloat32x4){ .elements = [ pointer[0], pointer[1], pointer[2], pointer[3] ] };
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXFloat32x4){ value, value, value, value }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeRepeatingElement(const Float32 value)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x4)(value);
#else
    return (CXFloat32x4){ .elements = [ value, value, value, value ] };
#endif
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
/// @return `(CXFloat32x4){ 0.f, 0.f, 0.f, 0.f }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeZero(void)
{
    return CXFloat32x4MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x4GetElement(const CXFloat32x4 storage, const int index)
{
#if __has_extension(attribute_ext_vector_type)
    return storage[index];
#else
    return storage.elements[index];
#endif
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXFloat32x4SetElement(CXFloat32x4* storage, const int index, const Float32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage)[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x4){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]), ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4FromCXInt32x4(CXInt32x4 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXFloat32x4);
#else
    return (CXFloat32x4){ .elements = [
        (Float32)(operand.elements[0]),
        (Float32)(operand.elements[1]),
        (Float32)(operand.elements[2]),
        (Float32)(operand.elements[3])
    ]};
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x4){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]), ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4FromCXUInt32x4(CXUInt32x4 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXFloat32x4);
#else
    return (CXFloat32x4){ .elements = [
        (Float32)(operand.elements[0]),
        (Float32)(operand.elements[1]),
        (Float32)(operand.elements[2]),
        (Float32)(operand.elements[3])
    ]};
#endif
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXFloat32x4){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Minimum(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    Float64 lhs0 = CXFloat32x4GetElement(lhs, 0), rhs0 = CXFloat32x4GetElement(rhs, 0);
    Float64 lhs1 = CXFloat32x4GetElement(lhs, 1), rhs1 = CXFloat32x4GetElement(rhs, 1);
    Float64 lhs2 = CXFloat32x4GetElement(lhs, 2), rhs2 = CXFloat32x4GetElement(rhs, 2);
    Float64 lhs3 = CXFloat32x4GetElement(lhs, 3), rhs3 = CXFloat32x4GetElement(rhs, 3);

#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x4){
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1,
        lhs2 < rhs2 ? lhs2 : rhs2,
        lhs3 < rhs3 ? lhs3 : rhs3
    };
#else
    return (CXFloat32x4){ .elements = [
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1,
        lhs2 < rhs2 ? lhs2 : rhs2,
        lhs3 < rhs3 ? lhs3 : rhs3
    ]};
#endif
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXFloat32x4){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Maximum(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    Float64 lhs0 = CXFloat32x4GetElement(lhs, 0), rhs0 = CXFloat32x4GetElement(rhs, 0);
    Float64 lhs1 = CXFloat32x4GetElement(lhs, 1), rhs1 = CXFloat32x4GetElement(rhs, 1);
    Float64 lhs2 = CXFloat32x4GetElement(lhs, 2), rhs2 = CXFloat32x4GetElement(rhs, 2);
    Float64 lhs3 = CXFloat32x4GetElement(lhs, 3), rhs3 = CXFloat32x4GetElement(rhs, 3);

#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x4){
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1,
        lhs2 > rhs2 ? lhs2 : rhs2,
        lhs3 > rhs3 ? lhs3 : rhs3
    };
#else
    return (CXFloat32x4){ .elements = [
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1,
        lhs2 > rhs2 ? lhs2 : rhs2,
        lhs3 > rhs3 ? lhs3 : rhs3
    ]};
#endif
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CXFloat32x4){ -(operand[0]), -(operand[1]), -(operand[2]), -(operand[3]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Negate(const CXFloat32x4 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return -(operand);
#else
    return (CXFloat32x4){ .elements = [
        -CXFloat32x4GetElement(operand, 0),
        -CXFloat32x4GetElement(operand, 1),
        -CXFloat32x4GetElement(operand, 2),
        -CXFloat32x4GetElement(operand, 3)
    ]};
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CXFloat32x4){ abs(operand[0]), abs(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Absolute(const CXFloat32x4 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x4){
        fabsf(CXFloat32x4GetElement(operand, 0)),
        fabsf(CXFloat32x4GetElement(operand, 1)),
        fabsf(CXFloat32x4GetElement(operand, 2)),
        fabsf(CXFloat32x4GetElement(operand, 3))
    };
#else
    return (CXFloat32x4){ .elements = [
        fabsf(CXFloat32x4GetElement(operand, 0)),
        fabsf(CXFloat32x4GetElement(operand, 1)),
        fabsf(CXFloat32x4GetElement(operand, 2)),
        fabsf(CXFloat32x4GetElement(operand, 3))
    ]};
#endif
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXFloat32x4){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Add(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs + rhs;
#else
    return (CXFloat32x4){ .elements = [
         CXFloat32x4GetElement(lhs, 0) + CXFloat32x4GetElement(rhs, 0),
         CXFloat32x4GetElement(lhs, 1) + CXFloat32x4GetElement(rhs, 1),
         CXFloat32x4GetElement(lhs, 2) + CXFloat32x4GetElement(rhs, 2),
         CXFloat32x4GetElement(lhs, 3) + CXFloat32x4GetElement(rhs, 3)
    ]};
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXFloat32x4){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Subtract(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs - rhs;
#else
    return (CXFloat32x4){ .elements = [
         CXFloat32x4GetElement(lhs, 0) - CXFloat32x4GetElement(rhs, 0),
         CXFloat32x4GetElement(lhs, 1) - CXFloat32x4GetElement(rhs, 1),
         CXFloat32x4GetElement(lhs, 2) - CXFloat32x4GetElement(rhs, 2),
         CXFloat32x4GetElement(lhs, 3) - CXFloat32x4GetElement(rhs, 3)
    ]};
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXFloat32x4){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Multiply(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs * rhs;
#else
    return (CXFloat32x4){ .elements = [
         CXFloat32x4GetElement(lhs, 0) * CXFloat32x4GetElement(rhs, 0),
         CXFloat32x4GetElement(lhs, 1) * CXFloat32x4GetElement(rhs, 1),
         CXFloat32x4GetElement(lhs, 2) * CXFloat32x4GetElement(rhs, 2),
         CXFloat32x4GetElement(lhs, 3) * CXFloat32x4GetElement(rhs, 3)
    ]};
#endif
}

/// Divides two storages (element-wise).
/// @return `(CXFloat32x4){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Divide(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs / rhs;
#else
    return (CXFloat32x4){ .elements = [
         CXFloat32x4GetElement(lhs, 0) / CXFloat32x4GetElement(rhs, 0),
         CXFloat32x4GetElement(lhs, 1) / CXFloat32x4GetElement(rhs, 1),
         CXFloat32x4GetElement(lhs, 2) / CXFloat32x4GetElement(rhs, 2),
         CXFloat32x4GetElement(lhs, 3) / CXFloat32x4GetElement(rhs, 3)
    ]};
#endif
}

/// Calculates the square root (element-wise).
/// @return `(CXFloat32x4){ sqrt(operand[0]), sqrt(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4SquareRoot(const CXFloat32x4 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x4){
        sqrtf(CXFloat32x4GetElement(operand, 0)),
        sqrtf(CXFloat32x4GetElement(operand, 1)),
        sqrtf(CXFloat32x4GetElement(operand, 2)),
        sqrtf(CXFloat32x4GetElement(operand, 3))
    };
#else
    return (CXFloat32x4){ .elements = [
       sqrtf(CXFloat32x4GetElement(operand, 0)),
       sqrtf(CXFloat32x4GetElement(operand, 1)),
       sqrtf(CXFloat32x4GetElement(operand, 2)),
       sqrtf(CXFloat32x4GetElement(operand, 3))
    ]};
#endif
}
