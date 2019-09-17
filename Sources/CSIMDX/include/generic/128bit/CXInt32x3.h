// Copyright 2019 Markus Winter
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <stdlib.h>
#include "CXTypes_t.h"

/// Initializes a storage to given elements, from least-significant to most-significant bits.
/// @return `(CXInt32x3){ element0, element1, element2 }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Make(Int32 element0, Int32 element1, Int32 element2)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x3){ element0, element1, element2 };
#else
    return (CXInt32x3){ .elements = [ element0, element1, element2 ] };
#endif
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXInt32x3){ pointer[0], pointer[1], pointer[2] }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeLoad(const Int32* pointer)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x3){ pointer[0], pointer[1], pointer[2] };
#else
    return (CXInt32x3){ .elements = [ pointer[0], pointer[1], pointer[2] ] };
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXInt32x3){ value, value, value }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeRepeatingElement(const Int32 value)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x3)(value);
#else
    return (CXInt32x3){ .elements = [ value, value, value ] };
#endif
}

/// Returns an intrinsic type with all lanes initialized to zero (0).
/// @return `(CXInt32x3){ 0, 0, 0 }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeZero(void)
{
    return CXInt32x3MakeRepeatingElement(0);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(Int32) CXInt32x3GetElement(const CXInt32x3 storage, const int index)
{
#if __has_extension(attribute_ext_vector_type)
    return storage[index];
#else
    return storage.elements[index];
#endif
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXInt32x3SetElement(CXInt32x3* storage, const int index, const Int32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage)[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt32x3){ (Int32)(operand[0]), (Int32)(operand[1]), (Int32)(operand[2]) }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3FromCXFloat32x3(CXFloat32x3 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt32x3);
#else
    return (CXInt32x3){ .elements = [
        (Int32)(operand.elements[0]),
        (Int32)(operand.elements[1]),
        (Int32)(operand.elements[2])
    ]};
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXInt32x3){ (Int32)(operand[0]), (Int32)(operand[1]), (Int32)(operand[2]) }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3FromCXUInt32x3(CXUInt32x3 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXInt32x3);
#else
    return (CXInt32x3){ .elements = [
        (Int32)(operand.elements[0]),
        (Int32)(operand.elements[1]),
        (Int32)(operand.elements[2])
    ]};
#endif
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXInt32x3){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1] }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Minimum(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    Int64 lhs0 = CXInt32x3GetElement(lhs, 0), rhs0 = CXInt32x3GetElement(rhs, 0);
    Int64 lhs1 = CXInt32x3GetElement(lhs, 1), rhs1 = CXInt32x3GetElement(rhs, 1);
    Int64 lhs2 = CXInt32x3GetElement(lhs, 2), rhs2 = CXInt32x3GetElement(rhs, 2);

#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x3){
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1,
        lhs2 < rhs2 ? lhs2 : rhs2
    };
#else
    return (CXInt32x3){ .elements = [
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1,
        lhs2 < rhs2 ? lhs2 : rhs2
    ]};
#endif
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXInt32x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Maximum(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    Int64 lhs0 = CXInt32x3GetElement(lhs, 0), rhs0 = CXInt32x3GetElement(rhs, 0);
    Int64 lhs1 = CXInt32x3GetElement(lhs, 1), rhs1 = CXInt32x3GetElement(rhs, 1);
    Int64 lhs2 = CXInt32x3GetElement(lhs, 2), rhs2 = CXInt32x3GetElement(rhs, 2);

#if __has_extension(attribute_ext_vector_type)
    return (CXInt32x3){
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1,
        lhs2 > rhs2 ? lhs2 : rhs2
    };
#else
    return (CXInt32x3){ .elements = [
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1,
        lhs2 > rhs2 ? lhs2 : rhs2
    ]};
#endif
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CXInt32x3){ -(operand[0]), -(operand[1]), -(operand[2]) }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Negate(const CXInt32x3 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return -(operand);
#else
    return (CXInt32x3){ .elements = [
        -CXInt32x3GetElement(operand, 0),
        -CXInt32x3GetElement(operand, 1),
        -CXInt32x3GetElement(operand, 2)
    ]};
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CXUInt32x3){ abs(operand[0]), abs(operand[1]), abs(operand[2]) }`
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXInt32x3Absolute(const CXInt32x3 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXUInt32x3){
        abs(CXInt32x3GetElement(operand, 0)),
        abs(CXInt32x3GetElement(operand, 1)),
        abs(CXInt32x3GetElement(operand, 2))
    };
#else
    return (CXUInt32x3){ .elements = [
        abs(CXInt32x3GetElement(operand, 0)),
        abs(CXInt32x3GetElement(operand, 1)),
        abs(CXInt32x3GetElement(operand, 2))
    ]};
#endif
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXInt32x3){ lhs[0] + rhs[0], lhs[1] + rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Add(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs + rhs;
#else
    return (CXInt32x3){ .elements = [
         CXInt32x3GetElement(lhs, 0) + CXInt32x3GetElement(rhs, 0),
         CXInt32x3GetElement(lhs, 1) + CXInt32x3GetElement(rhs, 1),
         CXInt32x3GetElement(lhs, 2) + CXInt32x3GetElement(rhs, 2)
    ]};
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXInt32x3){ lhs[0] - rhs[0], lhs[1] - rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Subtract(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs - rhs;
#else
    return (CXInt32x3){ .elements = [
         CXInt32x3GetElement(lhs, 0) - CXInt32x3GetElement(rhs, 0),
         CXInt32x3GetElement(lhs, 1) - CXInt32x3GetElement(rhs, 1),
         CXInt32x3GetElement(lhs, 2) - CXInt32x3GetElement(rhs, 2)
    ]};
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXInt32x3){ lhs[0] * rhs[0], lhs[1] * rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Multiply(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs * rhs;
#else
    return (CXInt32x3){ .elements = [
         CXInt32x3GetElement(lhs, 0) * CXInt32x3GetElement(rhs, 0),
         CXInt32x3GetElement(lhs, 1) * CXInt32x3GetElement(rhs, 1),
         CXInt32x3GetElement(lhs, 2) * CXInt32x3GetElement(rhs, 2)
    ]};
#endif
}

/// Divides two storages (element-wise).
/// @return `(CXInt32x3){ lhs[0] / rhs[0], lhs[1] / rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Divide(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs / rhs;
#else
    return (CXInt32x3){ .elements = [
         CXInt32x3GetElement(lhs, 0) / CXInt32x3GetElement(rhs, 0),
         CXInt32x3GetElement(lhs, 1) / CXInt32x3GetElement(rhs, 1),
         CXInt32x3GetElement(lhs, 2) / CXInt32x3GetElement(rhs, 2)
    ]};
#endif
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3BitwiseNot(const CXInt32x3 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return ~operand;
#else
    return (CXInt32x3){ .elements = [
         ~CXInt32x3GetElement(operand, 0),
         ~CXInt32x3GetElement(operand, 1),
         ~CXInt32x3GetElement(operand, 2)
    ]};
#endif
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3BitwiseAnd(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs & rhs;
#else
    return (CXInt32x3){ .elements = [
         CXInt32x3GetElement(lhs, 0) & CXInt32x3GetElement(rhs, 0),
         CXInt32x3GetElement(lhs, 1) & CXInt32x3GetElement(rhs, 1),
         CXInt32x3GetElement(lhs, 2) & CXInt32x3GetElement(rhs, 2)
    ]};
#endif
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3BitwiseAndNot(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return CXInt32x3BitwiseNot(lhs) & rhs;
#else
    return (CXInt32x3){ .elements = [
         CXInt32x3BitwiseNot(CXInt32x3GetElement(lhs, 0)) & CXInt32x3GetElement(rhs, 0),
         CXInt32x3BitwiseNot(CXInt32x3GetElement(lhs, 1)) & CXInt32x3GetElement(rhs, 1),
         CXInt32x3BitwiseNot(CXInt32x3GetElement(lhs, 2)) & CXInt32x3GetElement(rhs, 2)
    ]};
#endif
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3BitwiseOr(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs | rhs;
#else
    return (CXInt32x3){ .elements = [
         CXInt32x3GetElement(lhs, 0) | CXInt32x3GetElement(rhs, 0),
         CXInt32x3GetElement(lhs, 1) | CXInt32x3GetElement(rhs, 1),
         CXInt32x3GetElement(lhs, 2) | CXInt32x3GetElement(rhs, 2)
    ]};
#endif
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3BitwiseExclusiveOr(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs ^ rhs;
#else
    return (CXInt32x3){ .elements = [
         CXInt32x3GetElement(lhs, 0) ^ CXInt32x3GetElement(rhs, 0),
         CXInt32x3GetElement(lhs, 1) ^ CXInt32x3GetElement(rhs, 1),
         CXInt32x3GetElement(lhs, 2) ^ CXInt32x3GetElement(rhs, 2)
    ]};
#endif
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3ShiftLeft(const CXInt32x3 lhs, const Int32 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs << rhs;
#else
    return (CXInt32x3){ .elements = [
         CXInt32x3GetElement(lhs, 0) << rhs,
         CXInt32x3GetElement(lhs, 1) << rhs,
         CXInt32x3GetElement(lhs, 2) << rhs
    ]};
#endif
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3ShiftRight(const CXInt32x3 lhs, const Int32 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs >> rhs;
#else
    return (CXInt32x3){ .elements = [
         CXInt32x3GetElement(lhs, 0) >> rhs,
         CXInt32x3GetElement(lhs, 1) >> rhs,
         CXInt32x3GetElement(lhs, 2) >> rhs
    ]};
#endif
}
