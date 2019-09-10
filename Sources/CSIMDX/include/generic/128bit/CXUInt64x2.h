#pragma once

#include <stdlib.h>
#include "CXTypes_t.h"

/// Initializes a storage to given elements, from least-significant to most-significant bits.
/// @return `(CXUInt64x2){ element0, element1 }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Make(UInt64 element0, UInt64 element1)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXUInt64x2){ element0, element1 };
#else
    return (CXUInt64x2){ .elements = [ element0, element1 ] };
#endif
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXUInt64x2){ pointer[0], pointer[1] }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2MakeLoad(const UInt64* pointer)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXUInt64x2){ pointer[0], pointer[1] };
#else
    return (CXUInt64x2){ .elements = [ pointer[0], pointer[1] ] };
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXUInt64x2){ value, value }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2MakeRepeatingElement(const UInt64 value)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXUInt64x2)(value);
#else
    return (CXUInt64x2){ .elements = [ value, value ] };
#endif
}

/// Returns an intrinsic type with all lanes initialized to zero (0).
/// @return `(CXUInt64x2){ 0, 0 }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2MakeZero(void)
{
    return CXUInt64x2MakeRepeatingElement(0L);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(UInt64) CXUInt64x2GetElement(const CXUInt64x2 storage, const int index)
{
#if __has_extension(attribute_ext_vector_type)
    return storage[index];
#else
    return storage.elements[index];
#endif
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXUInt64x2SetElement(CXUInt64x2* storage, const int index, const UInt64 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage)[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXUInt64x2){ (UInt64)(operand[0]), (UInt64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2FromCXFloat32x2(CXFloat32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXUInt64x2);
#else
    return (CXUInt64x2){ .elements = [ (UInt64)(operand.elements[0]), (UInt64)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXUInt64x2){ (UInt64)(operand[0]), (UInt64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2FromCXInt32x2(CXInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXUInt64x2);
#else
    return (CXUInt64x2){ .elements = [ (UInt64)(operand.elements[0]), (UInt64)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXUInt64x2){ (UInt64)(operand[0]), (UInt64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2FromCXUInt32x2(CXUInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXUInt64x2);
#else
    return (CXUInt64x2){ .elements = [ (UInt64)(operand.elements[0]), (UInt64)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXUInt64x2){ (UInt64)(operand[0]), (UInt64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2FromCXFloat64x2(CXFloat64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXUInt64x2);
#else
    return (CXUInt64x2){ .elements = [ (UInt64)(operand.elements[0]), (UInt64)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXUInt64x2){ (UInt64)(operand[0]), (UInt64)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2FromCXInt64x2(CXInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXUInt64x2);
#else
    return (CXUInt64x2){ .elements = [ (UInt64)(operand.elements[0]), (UInt64)(operand.elements[1]) ] };
#endif
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXUInt64x2){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1] }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Minimum(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    UInt64 lhs0 = CXUInt64x2GetElement(lhs, 0), rhs0 = CXUInt64x2GetElement(rhs, 0);
    UInt64 lhs1 = CXUInt64x2GetElement(lhs, 1), rhs1 = CXUInt64x2GetElement(rhs, 1);

#if __has_extension(attribute_ext_vector_type)
    return (CXUInt64x2){
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1
    };
#else
    return (CXUInt64x2){ .elements = [
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1
    ]};
#endif
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXUInt64x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Maximum(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
    UInt64 lhs0 = CXUInt64x2GetElement(lhs, 0), rhs0 = CXUInt64x2GetElement(rhs, 0);
    UInt64 lhs1 = CXUInt64x2GetElement(lhs, 1), rhs1 = CXUInt64x2GetElement(rhs, 1);

#if __has_extension(attribute_ext_vector_type)
    return (CXUInt64x2){
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1
    };
#else
    return (CXUInt64x2){ .elements = [
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1
    ]};
#endif
}

// MARK: - Arithmetics

/// Returns the absolute storage (element-wise).
/// @return `(CXUInt64x2){ abs(operand[0]), abs(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Absolute(const CXUInt64x2 operand)
{
    return operand;
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXUInt64x2){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Add(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs + rhs;
#else
    return (CXUInt64x2){ .elements = [
         CXUInt64x2GetElement(lhs, 0) + CXUInt64x2GetElement(rhs, 0),
         CXUInt64x2GetElement(lhs, 1) + CXUInt64x2GetElement(rhs, 1)
    ]};
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXUInt64x2){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Subtract(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs - rhs;
#else
    return (CXUInt64x2){ .elements = [
         CXUInt64x2GetElement(lhs, 0) - CXUInt64x2GetElement(rhs, 0),
         CXUInt64x2GetElement(lhs, 1) - CXUInt64x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXUInt64x2){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Multiply(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs * rhs;
#else
    return (CXUInt64x2){ .elements = [
         CXUInt64x2GetElement(lhs, 0) * CXUInt64x2GetElement(rhs, 0),
         CXUInt64x2GetElement(lhs, 1) * CXUInt64x2GetElement(rhs, 1)
    ]};
#endif
}

/// Divides two storages (element-wise).
/// @return `(CXUInt64x2){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2Divide(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs / rhs;
#else
    return (CXUInt64x2){ .elements = [
         CXUInt64x2GetElement(lhs, 0) / CXUInt64x2GetElement(rhs, 0),
         CXUInt64x2GetElement(lhs, 1) / CXUInt64x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseNot(const CXUInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return ~operand;
#else
    return (CXUInt64x2){ .elements = [
         ~CXUInt64x2GetElement(operand, 0),
         ~CXUInt64x2GetElement(operand, 1)
    ]};
#endif
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseAnd(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs & rhs;
#else
    return (CXUInt64x2){ .elements = [
         CXUInt64x2GetElement(lhs, 0) & CXUInt64x2GetElement(rhs, 0),
         CXUInt64x2GetElement(lhs, 1) & CXUInt64x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseAndNot(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return CXUInt64x2BitwiseNot(lhs) & rhs;
#else
    return (CXUInt64x2){ .elements = [
         CXUInt64x2BitwiseNot(CXUInt64x2GetElement(lhs, 0)) & CXUInt64x2GetElement(rhs, 0),
         CXUInt64x2BitwiseNot(CXUInt64x2GetElement(lhs, 1)) & CXUInt64x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseOr(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs | rhs;
#else
    return (CXUInt64x2){ .elements = [
         CXUInt64x2GetElement(lhs, 0) | CXUInt64x2GetElement(rhs, 0),
         CXUInt64x2GetElement(lhs, 1) | CXUInt64x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2BitwiseExclusiveOr(const CXUInt64x2 lhs, const CXUInt64x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs ^ rhs;
#else
    return (CXUInt64x2){ .elements = [
         CXUInt64x2GetElement(lhs, 0) ^ CXUInt64x2GetElement(rhs, 0),
         CXUInt64x2GetElement(lhs, 1) ^ CXUInt64x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2ShiftLeft(const CXUInt64x2 lhs, const UInt64 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs << rhs;
#else
    return (CXUInt64x2){ .elements = [
         CXUInt64x2GetElement(lhs, 0) << rhs,
         CXUInt64x2GetElement(lhs, 1) << rhs
    ]};
#endif
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXUInt64x2ShiftRight(const CXUInt64x2 lhs, const UInt64 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs >> rhs;
#else
    return (CXUInt64x2){ .elements = [
         CXUInt64x2GetElement(lhs, 0) >> rhs,
         CXUInt64x2GetElement(lhs, 1) >> rhs
    ]};
#endif
}
