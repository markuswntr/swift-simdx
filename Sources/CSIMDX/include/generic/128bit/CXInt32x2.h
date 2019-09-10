#pragma once

#include <stdlib.h>
#include "CXTypes_t.h"

/// Initializes a storage to given elements, from least-significant to most-significant bits.
/// @return `(CXInt32x2){ element0, element1 }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Make(Int32 element0, Int32 element1)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x2){ element0, element1 };
#else
    return (CXInt32x2){ .elements = [ element0, element1 ] };
#endif
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXInt32x2){ pointer[0], pointer[1] }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2MakeLoad(const Int32* pointer)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x2){ pointer[0], pointer[1] };
#else
    return (CXInt32x2){ .elements = [ pointer[0], pointer[1] ] };
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXInt32x2){ value, value }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2MakeRepeatingElement(const Int32 value)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x2)(value);
#else
    return (CXInt32x2){ .elements = [ value, value ] };
#endif
}

/// Returns an intrinsic type with all lanes initialized to zero (0).
/// @return `(CXInt32x2){ 0, 0 }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2MakeZero(void)
{
    return CXInt32x2MakeRepeatingElement(0);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(Int32) CXInt32x2GetElement(const CXInt32x2 storage, const int index)
{
#if __has_extension(attribute_ext_vector_type)
    return storage[index];
#else
    return storage.elements[index];
#endif
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXInt32x2SetElement(CXInt32x2* storage, const int index, const Int32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage)[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt32x2){ (Int32)(operand[0]), (Int32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2FromCXFloat32x2(CXFloat32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt32x2);
#else
    return (CXInt32x2){ .elements = [ (Int32)(operand.elements[0]), (Int32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt32x2){ (Int32)(operand[0]), (Int32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2FromCXUInt32x2(CXUInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt32x2);
#else
    return (CXInt32x2){ .elements = [ (Int32)(operand.elements[0]), (Int32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt32x2){ (Int32)(operand[0]), (Int32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2FromCXFloat64x2(CXFloat64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt32x2);
#else
    return (CXInt32x2){ .elements = [ (Int32)(operand.elements[0]), (Int32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt32x2){ (Int32)(operand[0]), (Int32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2FromCXInt64x2(CXInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt32x2);
#else
    return (CXInt32x2){ .elements = [ (Int32)(operand.elements[0]), (Int32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt32x2){ (Int32)(operand[0]), (Int32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2FromCXUInt64x2(CXUInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt32x2);
#else
    return (CXInt32x2){ .elements = [ (Int32)(operand.elements[0]), (Int32)(operand.elements[1]) ] };
#endif
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXInt32x2){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1] }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Minimum(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
    Int64 lhs0 = CXInt32x2GetElement(lhs, 0), rhs0 = CXInt32x2GetElement(rhs, 0);
    Int64 lhs1 = CXInt32x2GetElement(lhs, 1), rhs1 = CXInt32x2GetElement(rhs, 1);

#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x2){
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1
    };
#else
    return (CXInt32x2){ .elements = [
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1
    ]};
#endif
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXInt32x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Maximum(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
    Int64 lhs0 = CXInt32x2GetElement(lhs, 0), rhs0 = CXInt32x2GetElement(rhs, 0);
    Int64 lhs1 = CXInt32x2GetElement(lhs, 1), rhs1 = CXInt32x2GetElement(rhs, 1);

#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x2){
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1
    };
#else
    return (CXInt32x2){ .elements = [
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1
    ]};
#endif
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CXInt32x2){ -(operand[0]), -(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Negate(const CXInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return -(operand);
#else
    return (CXInt32x2){ .elements = [
        -CXInt32x2GetElement(operand, 0),
        -CXInt32x2GetElement(operand, 1)
    ]};
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CXUInt32x2){ abs(operand[0]), abs(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXInt32x2Absolute(const CXInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXUInt32x2){
        abs(CXInt32x2GetElement(operand, 0)),
        abs(CXInt32x2GetElement(operand, 1))
    };
#else
    return (CXUInt32x2){ .elements = [
        abs(CXInt32x2GetElement(operand, 0)),
        abs(CXInt32x2GetElement(operand, 1))
    ]};
#endif
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXInt32x2){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Add(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs + rhs;
#else
    return (CXInt32x2){ .elements = [
         CXInt32x2GetElement(lhs, 0) + CXInt32x2GetElement(rhs, 0),
         CXInt32x2GetElement(lhs, 1) + CXInt32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXInt32x2){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Subtract(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs - rhs;
#else
    return (CXInt32x2){ .elements = [
         CXInt32x2GetElement(lhs, 0) - CXInt32x2GetElement(rhs, 0),
         CXInt32x2GetElement(lhs, 1) - CXInt32x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXInt32x2){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Multiply(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs * rhs;
#else
    return (CXInt32x2){ .elements = [
         CXInt32x2GetElement(lhs, 0) * CXInt32x2GetElement(rhs, 0),
         CXInt32x2GetElement(lhs, 1) * CXInt32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Divides two storages (element-wise).
/// @return `(CXInt32x2){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Divide(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs / rhs;
#else
    return (CXInt32x2){ .elements = [
         CXInt32x2GetElement(lhs, 0) / CXInt32x2GetElement(rhs, 0),
         CXInt32x2GetElement(lhs, 1) / CXInt32x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2BitwiseNot(const CXInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return ~operand;
#else
    return (CXInt32x2){ .elements = [
         ~CXInt32x2GetElement(operand, 0),
         ~CXInt32x2GetElement(operand, 1)
    ]};
#endif
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2BitwiseAnd(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs & rhs;
#else
    return (CXInt32x2){ .elements = [
         CXInt32x2GetElement(lhs, 0) & CXInt32x2GetElement(rhs, 0),
         CXInt32x2GetElement(lhs, 1) & CXInt32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2BitwiseAndNot(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return CXInt32x2BitwiseNot(lhs) & rhs;
#else
    return (CXInt32x2){ .elements = [
         CXInt32x2BitwiseNot(CXInt32x2GetElement(lhs, 0)) & CXInt32x2GetElement(rhs, 0),
         CXInt32x2BitwiseNot(CXInt32x2GetElement(lhs, 1)) & CXInt32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2BitwiseOr(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs | rhs;
#else
    return (CXInt32x2){ .elements = [
         CXInt32x2GetElement(lhs, 0) | CXInt32x2GetElement(rhs, 0),
         CXInt32x2GetElement(lhs, 1) | CXInt32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2BitwiseExclusiveOr(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs ^ rhs;
#else
    return (CXInt32x2){ .elements = [
         CXInt32x2GetElement(lhs, 0) ^ CXInt32x2GetElement(rhs, 0),
         CXInt32x2GetElement(lhs, 1) ^ CXInt32x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2ShiftLeft(const CXInt32x2 lhs, const Int32 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs << rhs;
#else
    return (CXInt32x2){ .elements = [
         CXInt32x2GetElement(lhs, 0) << rhs,
         CXInt32x2GetElement(lhs, 1) << rhs
    ]};
#endif
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2ShiftRight(const CXInt32x2 lhs, const Int32 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs >> rhs;
#else
    return (CXInt32x2){ .elements = [
         CXInt32x2GetElement(lhs, 0) >> rhs,
         CXInt32x2GetElement(lhs, 1) >> rhs
    ]};
#endif
}
