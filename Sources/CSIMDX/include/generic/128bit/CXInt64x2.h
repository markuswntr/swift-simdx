#pragma once

#include <stdlib.h>
#include "CXTypes_t.h"

/// Initializes a storage to given elements, from least-significant to most-significant bits.
/// @return `(CXInt64x2){ element0, element1 }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Make(Int64 element0, Int64 element1)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt64x2){ element0, element1 };
#else
    return (CXInt64x2){ .elements = [ element0, element1 ] };
#endif
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXInt64x2){ pointer[0], pointer[1] }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeLoad(const Int64* pointer)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt64x2){ pointer[0], pointer[1] };
#else
    return (CXInt64x2){ .elements = [ pointer[0], pointer[1] ] };
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXInt64x2){ value, value }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeRepeatingElement(const Int64 value)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt64x2)(value);
#else
    return (CXInt64x2){ .elements = [ value, value ] };
#endif
}

/// Returns an intrinsic type with all lanes initialized to zero (0).
/// @return `(CXInt64x2){ 0, 0 }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeZero(void)
{
    return CXInt64x2MakeRepeatingElement(0L);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(Int64) CXInt64x2GetElement(const CXInt64x2 storage, const int index)
{
#if __has_extension(attribute_ext_vector_type)
    return storage[index];
#else
    return storage.elements[index];
#endif
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXInt64x2SetElement(CXInt64x2* storage, const int index, const Int64 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage)[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt64x2){ (Int64)(operand[0]), (Int64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2FromCXFloat32x2(CXFloat32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt64x2);
#else
    return (CXInt64x2){ .elements = [ (Int64)(operand.elements[0]), (Int64)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt64x2){ (Int64)(operand[0]), (Int64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2FromCXInt32x2(CXInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt64x2);
#else
    return (CXInt64x2){ .elements = [ (Int64)(operand.elements[0]), (Int64)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt64x2){ (Int64)(operand[0]), (Int64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2FromCXUInt32x2(CXUInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt64x2);
#else
    return (CXInt64x2){ .elements = [ (Int64)(operand.elements[0]), (Int64)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt64x2){ (Int64)(operand[0]), (Int64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2FromCXFloat64x2(CXFloat64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt64x2);
#else
    return (CXInt64x2){ .elements = [ (Int64)(operand.elements[0]), (Int64)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt64x2){ (Int64)(operand[0]), (Int64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2FromCXUInt64x2(CXUInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt64x2);
#else
    return (CXInt64x2){ .elements = [ (Int64)(operand.elements[0]), (Int64)(operand.elements[1]) ] };
#endif
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXInt64x2){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1] }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Minimum(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    Int64 lhs0 = CXInt64x2GetElement(lhs, 0), rhs0 = CXInt64x2GetElement(rhs, 0);
    Int64 lhs1 = CXInt64x2GetElement(lhs, 1), rhs1 = CXInt64x2GetElement(rhs, 1);

#if __has_extension(attribute_ext_vector_type)
    return (CXInt64x2){
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1
    };
#else
    return (CXInt64x2){ .elements = [
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1
    ]};
#endif
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXInt64x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Maximum(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    Int64 lhs0 = CXInt64x2GetElement(lhs, 0), rhs0 = CXInt64x2GetElement(rhs, 0);
    Int64 lhs1 = CXInt64x2GetElement(lhs, 1), rhs1 = CXInt64x2GetElement(rhs, 1);

#if __has_extension(attribute_ext_vector_type)
    return (CXInt64x2){
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1
    };
#else
    return (CXInt64x2){ .elements = [
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1
    ]};
#endif
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CXInt64x2){ -(operand[0]), -(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Negate(const CXInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return -(operand);
#else
    return (CXInt64x2){ .elements = [
        -CXInt64x2GetElement(operand, 0),
        -CXInt64x2GetElement(operand, 1)
    ]};
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CXUInt64x2){ abs(operand[0]), abs(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXInt64x2Absolute(const CXInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXUInt64x2){
        llabs(CXInt64x2GetElement(operand, 0)),
        llabs(CXInt64x2GetElement(operand, 1))
    };
#else
    return (CXUInt64x2){ .elements = [
        llabs(CXInt64x2GetElement(operand, 0)),
        llabs(CXInt64x2GetElement(operand, 1))
    ]};
#endif
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXInt64x2){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Add(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs + rhs;
#else
    return (CXInt64x2){ .elements = [
         CXInt64x2GetElement(lhs, 0) + CXInt64x2GetElement(rhs, 0),
         CXInt64x2GetElement(lhs, 1) + CXInt64x2GetElement(rhs, 1)
    ]};
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXInt64x2){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Subtract(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs - rhs;
#else
    return (CXInt64x2){ .elements = [
         CXInt64x2GetElement(lhs, 0) - CXInt64x2GetElement(rhs, 0),
         CXInt64x2GetElement(lhs, 1) - CXInt64x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXInt64x2){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Multiply(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs * rhs;
#else
    return (CXInt64x2){ .elements = [
         CXInt64x2GetElement(lhs, 0) * CXInt64x2GetElement(rhs, 0),
         CXInt64x2GetElement(lhs, 1) * CXInt64x2GetElement(rhs, 1)
    ]};
#endif
}

/// Divides two storages (element-wise).
/// @return `(CXInt64x2){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Divide(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs / rhs;
#else
    return (CXInt64x2){ .elements = [
         CXInt64x2GetElement(lhs, 0) / CXInt64x2GetElement(rhs, 0),
         CXInt64x2GetElement(lhs, 1) / CXInt64x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseNot(const CXInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return ~operand;
#else
    return (CXInt64x2){ .elements = [
         ~CXInt64x2GetElement(operand, 0),
         ~CXInt64x2GetElement(operand, 1)
    ]};
#endif
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseAnd(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs & rhs;
#else
    return (CXInt64x2){ .elements = [
         CXInt64x2GetElement(lhs, 0) & CXInt64x2GetElement(rhs, 0),
         CXInt64x2GetElement(lhs, 1) & CXInt64x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseAndNot(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return CXInt64x2BitwiseNot(lhs) & rhs;
#else
    return (CXInt64x2){ .elements = [
         CXInt64x2BitwiseNot(CXInt64x2GetElement(lhs, 0)) & CXInt64x2GetElement(rhs, 0),
         CXInt64x2BitwiseNot(CXInt64x2GetElement(lhs, 1)) & CXInt64x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseOr(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs | rhs;
#else
    return (CXInt64x2){ .elements = [
         CXInt64x2GetElement(lhs, 0) | CXInt64x2GetElement(rhs, 0),
         CXInt64x2GetElement(lhs, 1) | CXInt64x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2BitwiseExclusiveOr(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs ^ rhs;
#else
    return (CXInt64x2){ .elements = [
         CXInt64x2GetElement(lhs, 0) ^ CXInt64x2GetElement(rhs, 0),
         CXInt64x2GetElement(lhs, 1) ^ CXInt64x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2ShiftLeft(const CXInt64x2 lhs, const Int64 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs << rhs;
#else
    return (CXInt64x2){ .elements = [
         CXInt64x2GetElement(lhs, 0) << rhs,
         CXInt64x2GetElement(lhs, 1) << rhs
    ]};
#endif
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2ShiftRight(const CXInt64x2 lhs, const Int64 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs >> rhs;
#else
    return (CXInt64x2){ .elements = [
         CXInt64x2GetElement(lhs, 0) >> rhs,
         CXInt64x2GetElement(lhs, 1) >> rhs
    ]};
#endif
}
