#pragma once

#include <stdlib.h>
#include "CXTypes_t.h"

/// Initializes a storage to given elements, from least-significant to most-significant bits.
/// @return `(CXInt32x4){ element0, element1, element2, element3 }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Make(Int32 element0, Int32 element1, Int32 element2, Int32 element3)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x4){ element0, element1, element2, element3 };
#else
    return (CXInt32x4){ .elements = [ element0, element1, element2, element2 ] };
#endif
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXInt32x4){ pointer[0], pointer[1], pointer[2], pointer[3] }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeLoad(const Int32* pointer)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x4){ pointer[0], pointer[1], pointer[2], pointer[3] };
#else
    return (CXInt32x4){ .elements = [ pointer[0], pointer[1], pointer[2], pointer[3] ] };
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXInt32x4){ value, value, value, value }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeRepeatingElement(const Int32 value)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x4)(value);
#else
    return (CXInt32x4){ .elements = [ value, value, value, value ] };
#endif
}

/// Returns an intrinsic type with all lanes initialized to zero (0).
/// @return `(CXInt32x4){ 0, 0, 0, 0 }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeZero(void)
{
    return CXInt32x4MakeRepeatingElement(0);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(Int32) CXInt32x4GetElement(const CXInt32x4 storage, const int index)
{
#if __has_extension(attribute_ext_vector_type)
    return storage[index];
#else
    return storage.elements[index];
#endif
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXInt32x4SetElement(CXInt32x4* storage, const int index, const Int32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage)[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt32x4){ (Int32)(operand[0]), (Int32)(operand[1]), (Int32)(operand[2]), (Int32)(operand[3]) }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4FromCXFloat32x4(CXFloat32x4 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt32x4);
#else
    return (CXInt32x4){ .elements = [
        (Int32)(operand.elements[0]),
        (Int32)(operand.elements[1]),
        (Int32)(operand.elements[2]),
        (Int32)(operand.elements[3])
    ]};
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt32x4){ (Int32)(operand[0]), (Int32)(operand[1]), (Int32)(operand[2]), (Int32)(operand[3]) }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4FromCXUInt32x4(CXUInt32x4 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt32x4);
#else
    return (CXInt32x4){ .elements = [
        (Int32)(operand.elements[0]),
        (Int32)(operand.elements[1]),
        (Int32)(operand.elements[2]),
        (Int32)(operand.elements[3])
    ]};
#endif
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXInt32x4){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Minimum(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    Int64 lhs0 = CXInt32x4GetElement(lhs, 0), rhs0 = CXInt32x4GetElement(rhs, 0);
    Int64 lhs1 = CXInt32x4GetElement(lhs, 1), rhs1 = CXInt32x4GetElement(rhs, 1);
    Int64 lhs2 = CXInt32x4GetElement(lhs, 2), rhs2 = CXInt32x4GetElement(rhs, 2);
    Int64 lhs3 = CXInt32x4GetElement(lhs, 3), rhs3 = CXInt32x4GetElement(rhs, 3);

#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x4){
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1,
        lhs2 < rhs2 ? lhs2 : rhs2,
        lhs3 < rhs3 ? lhs3 : rhs3
    };
#else
    return (CXInt32x4){ .elements = [
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1,
        lhs2 < rhs2 ? lhs2 : rhs2,
        lhs3 < rhs3 ? lhs3 : rhs3
    ]};
#endif
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXInt32x4){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Maximum(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    Int64 lhs0 = CXInt32x4GetElement(lhs, 0), rhs0 = CXInt32x4GetElement(rhs, 0);
    Int64 lhs1 = CXInt32x4GetElement(lhs, 1), rhs1 = CXInt32x4GetElement(rhs, 1);
    Int64 lhs2 = CXInt32x4GetElement(lhs, 2), rhs2 = CXInt32x4GetElement(rhs, 2);
    Int64 lhs3 = CXInt32x4GetElement(lhs, 3), rhs3 = CXInt32x4GetElement(rhs, 3);

#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x4){
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1,
        lhs2 > rhs2 ? lhs2 : rhs2,
        lhs3 > rhs3 ? lhs3 : rhs3
    };
#else
    return (CXInt32x4){ .elements = [
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1,
        lhs2 > rhs2 ? lhs2 : rhs2,
        lhs3 > rhs3 ? lhs3 : rhs3
    ]};
#endif
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CXInt32x4){ -(operand[0]), -(operand[1]), ... }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Negate(const CXInt32x4 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return -(operand);
#else
    return (CXInt32x4){ .elements = [
        -CXInt32x4GetElement(operand, 0),
        -CXInt32x4GetElement(operand, 1),
        -CXInt32x4GetElement(operand, 2),
        -CXInt32x4GetElement(operand, 3)
    ]};
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CXUInt32x4){ abs(operand[0]), abs(operand[1]), ... }`
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXInt32x4Absolute(const CXInt32x4 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXUInt32x4){
        abs(CXInt32x4GetElement(operand, 0)),
        abs(CXInt32x4GetElement(operand, 1)),
        abs(CXInt32x4GetElement(operand, 2)),
        abs(CXInt32x4GetElement(operand, 3))
    };
#else
    return (CXUInt32x4){ .elements = [
        abs(CXInt32x4GetElement(operand, 0)),
        abs(CXInt32x4GetElement(operand, 1)),
        abs(CXInt32x4GetElement(operand, 2)),
        abs(CXInt32x4GetElement(operand, 3))
    ]};
#endif
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXInt32x4){ lhs[0] + rhs[0], lhs[1] + rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Add(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs + rhs;
#else
    return (CXInt32x4){ .elements = [
         CXInt32x4GetElement(lhs, 0) + CXInt32x4GetElement(rhs, 0),
         CXInt32x4GetElement(lhs, 1) + CXInt32x4GetElement(rhs, 1),
         CXInt32x4GetElement(lhs, 2) + CXInt32x4GetElement(rhs, 2),
         CXInt32x4GetElement(lhs, 3) + CXInt32x4GetElement(rhs, 3)
    ]};
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXInt32x4){ lhs[0] - rhs[0], lhs[1] - rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Subtract(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs - rhs;
#else
    return (CXInt32x4){ .elements = [
         CXInt32x4GetElement(lhs, 0) - CXInt32x4GetElement(rhs, 0),
         CXInt32x4GetElement(lhs, 1) - CXInt32x4GetElement(rhs, 1),
         CXInt32x4GetElement(lhs, 2) - CXInt32x4GetElement(rhs, 2),
         CXInt32x4GetElement(lhs, 3) - CXInt32x4GetElement(rhs, 3)
    ]};
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXInt32x4){ lhs[0] * rhs[0], lhs[1] * rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Multiply(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs * rhs;
#else
    return (CXInt32x4){ .elements = [
         CXInt32x4GetElement(lhs, 0) * CXInt32x4GetElement(rhs, 0),
         CXInt32x4GetElement(lhs, 1) * CXInt32x4GetElement(rhs, 1),
         CXInt32x4GetElement(lhs, 2) * CXInt32x4GetElement(rhs, 2),
         CXInt32x4GetElement(lhs, 3) * CXInt32x4GetElement(rhs, 3)
    ]};
#endif
}

/// Divides two storages (element-wise).
/// @return `(CXInt32x4){ lhs[0] / rhs[0], lhs[1] / rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Divide(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs / rhs;
#else
    return (CXInt32x4){ .elements = [
         CXInt32x4GetElement(lhs, 0) / CXInt32x4GetElement(rhs, 0),
         CXInt32x4GetElement(lhs, 1) / CXInt32x4GetElement(rhs, 1),
         CXInt32x4GetElement(lhs, 2) / CXInt32x4GetElement(rhs, 2),
         CXInt32x4GetElement(lhs, 3) / CXInt32x4GetElement(rhs, 3)
    ]};
#endif
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4BitwiseNot(const CXInt32x4 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return ~operand;
#else
    return (CXInt32x4){ .elements = [
         ~CXInt32x4GetElement(operand, 0),
         ~CXInt32x4GetElement(operand, 1),
         ~CXInt32x4GetElement(operand, 2),
         ~CXInt32x4GetElement(operand, 3)
    ]};
#endif
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4BitwiseAnd(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs & rhs;
#else
    return (CXInt32x4){ .elements = [
         CXInt32x4GetElement(lhs, 0) & CXInt32x4GetElement(rhs, 0),
         CXInt32x4GetElement(lhs, 1) & CXInt32x4GetElement(rhs, 1),
         CXInt32x4GetElement(lhs, 2) & CXInt32x4GetElement(rhs, 2),
         CXInt32x4GetElement(lhs, 3) & CXInt32x4GetElement(rhs, 3)
    ]};
#endif
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4BitwiseAndNot(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return CXInt32x4BitwiseNot(lhs) & rhs;
#else
    return (CXInt32x4){ .elements = [
         CXInt32x4BitwiseNot(CXInt32x4GetElement(lhs, 0)) & CXInt32x4GetElement(rhs, 0),
         CXInt32x4BitwiseNot(CXInt32x4GetElement(lhs, 1)) & CXInt32x4GetElement(rhs, 1),
         CXInt32x4BitwiseNot(CXInt32x4GetElement(lhs, 2)) & CXInt32x4GetElement(rhs, 2),
         CXInt32x4BitwiseNot(CXInt32x4GetElement(lhs, 3)) & CXInt32x4GetElement(rhs, 3)
    ]};
#endif
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4BitwiseOr(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs | rhs;
#else
    return (CXInt32x4){ .elements = [
         CXInt32x4GetElement(lhs, 0) | CXInt32x4GetElement(rhs, 0),
         CXInt32x4GetElement(lhs, 1) | CXInt32x4GetElement(rhs, 1),
         CXInt32x4GetElement(lhs, 2) | CXInt32x4GetElement(rhs, 2),
         CXInt32x4GetElement(lhs, 3) | CXInt32x4GetElement(rhs, 3)
    ]};
#endif
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4BitwiseExclusiveOr(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs ^ rhs;
#else
    return (CXInt32x4){ .elements = [
         CXInt32x4GetElement(lhs, 0) ^ CXInt32x4GetElement(rhs, 0),
         CXInt32x4GetElement(lhs, 1) ^ CXInt32x4GetElement(rhs, 1),
         CXInt32x4GetElement(lhs, 2) ^ CXInt32x4GetElement(rhs, 2),
         CXInt32x4GetElement(lhs, 3) ^ CXInt32x4GetElement(rhs, 3)
    ]};
#endif
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4ShiftLeft(const CXInt32x4 lhs, const Int32 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs << rhs;
#else
    return (CXInt32x4){ .elements = [
         CXInt32x4GetElement(lhs, 0) << rhs,
         CXInt32x4GetElement(lhs, 1) << rhs,
         CXInt32x4GetElement(lhs, 2) << rhs,
         CXInt32x4GetElement(lhs, 3) << rhs
    ]};
#endif
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4ShiftRight(const CXInt32x4 lhs, const Int32 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs >> rhs;
#else
    return (CXInt32x4){ .elements = [
         CXInt32x4GetElement(lhs, 0) >> rhs,
         CXInt32x4GetElement(lhs, 1) >> rhs,
         CXInt32x4GetElement(lhs, 2) >> rhs,
         CXInt32x4GetElement(lhs, 3) >> rhs
    ]};
#endif
}
