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
/// @return `(CXUInt32x2){ element0, element1 }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Make(UInt32 element0, UInt32 element1)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXUInt32x2){ element0, element1 };
#else
    return (CXUInt32x2){ .elements = [ element0, element1 ] };
#endif
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXUInt32x2){ pointer[0], pointer[1] }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2MakeLoad(const UInt32* pointer)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXUInt32x2){ pointer[0], pointer[1] };
#else
    return (CXUInt32x2){ .elements = [ pointer[0], pointer[1] ] };
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXUInt32x2){ value, value }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2MakeRepeatingElement(const UInt32 value)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXUInt32x2)(value);
#else
    return (CXUInt32x2){ .elements = [ value, value ] };
#endif
}

/// Returns an intrinsic type with all lanes initialized to zero (0).
/// @return `(CXUInt32x2){ 0, 0 }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2MakeZero(void)
{
    return CXUInt32x2MakeRepeatingElement(0);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(UInt32) CXUInt32x2GetElement(const CXUInt32x2 storage, const int index)
{
#if __has_extension(attribute_ext_vector_type)
    return storage[index];
#else
    return storage.elements[index];
#endif
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXUInt32x2SetElement(CXUInt32x2* storage, const int index, const UInt32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage)[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXUInt32x2){ (UInt32)(operand[0]), (UInt32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2FromCXFloat32x2(CXFloat32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXUInt32x2);
#else
    return (CXUInt32x2){ .elements = [ (UInt32)(operand.elements[0]), (UInt32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXUInt32x2){ (UInt32)(operand[0]), (UInt32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2FromCXInt32x2(CXInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXUInt32x2);
#else
    return (CXUInt32x2){ .elements = [ (UInt32)(operand.elements[0]), (UInt32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXUInt32x2){ (UInt32)(operand[0]), (UInt32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2FromCXFloat64x2(CXFloat64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXUInt32x2);
#else
    return (CXUInt32x2){ .elements = [ (UInt32)(operand.elements[0]), (UInt32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXUInt32x2){ (UInt32)(operand[0]), (UInt32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2FromCXInt64x2(CXInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXUInt32x2);
#else
    return (CXUInt32x2){ .elements = [ (UInt32)(operand.elements[0]), (UInt32)(operand.elements[1]) ] };
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXUInt32x2){ (UInt32)(operand[0]), (UInt32)(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2FromCXUInt64x2(CXUInt64x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXUInt32x2);
#else
    return (CXUInt32x2){ .elements = [ (UInt32)(operand.elements[0]), (UInt32)(operand.elements[1]) ] };
#endif
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXUInt32x2){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1] }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Minimum(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    Int64 lhs0 = CXUInt32x2GetElement(lhs, 0), rhs0 = CXUInt32x2GetElement(rhs, 0);
    Int64 lhs1 = CXUInt32x2GetElement(lhs, 1), rhs1 = CXUInt32x2GetElement(rhs, 1);

#if __has_extension(attribute_ext_vector_type)
    return (CXUInt32x2){
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1
    };
#else
    return (CXUInt32x2){ .elements = [
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1
    ]};
#endif
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXUInt32x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Maximum(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
    Int64 lhs0 = CXUInt32x2GetElement(lhs, 0), rhs0 = CXUInt32x2GetElement(rhs, 0);
    Int64 lhs1 = CXUInt32x2GetElement(lhs, 1), rhs1 = CXUInt32x2GetElement(rhs, 1);

#if __has_extension(attribute_ext_vector_type)
    return (CXUInt32x2){
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1
    };
#else
    return (CXUInt32x2){ .elements = [
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1
    ]};
#endif
}

// MARK: - Arithmetics

/// Returns the absolute storage (element-wise).
/// @return `(CXUInt32x2){ abs(operand[0]), abs(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Absolute(const CXUInt32x2 operand)
{
    return operand;
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXUInt32x2){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Add(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs + rhs;
#else
    return (CXUInt32x2){ .elements = [
         CXUInt32x2GetElement(lhs, 0) + CXUInt32x2GetElement(rhs, 0),
         CXUInt32x2GetElement(lhs, 1) + CXUInt32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXUInt32x2){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Subtract(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs - rhs;
#else
    return (CXUInt32x2){ .elements = [
         CXUInt32x2GetElement(lhs, 0) - CXUInt32x2GetElement(rhs, 0),
         CXUInt32x2GetElement(lhs, 1) - CXUInt32x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXUInt32x2){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Multiply(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs * rhs;
#else
    return (CXUInt32x2){ .elements = [
         CXUInt32x2GetElement(lhs, 0) * CXUInt32x2GetElement(rhs, 0),
         CXUInt32x2GetElement(lhs, 1) * CXUInt32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Divides two storages (element-wise).
/// @return `(CXUInt32x2){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2Divide(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs / rhs;
#else
    return (CXUInt32x2){ .elements = [
         CXUInt32x2GetElement(lhs, 0) / CXUInt32x2GetElement(rhs, 0),
         CXUInt32x2GetElement(lhs, 1) / CXUInt32x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseNot(const CXUInt32x2 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return ~operand;
#else
    return (CXUInt32x2){ .elements = [
         ~CXUInt32x2GetElement(operand, 0),
         ~CXUInt32x2GetElement(operand, 1)
    ]};
#endif
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseAnd(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs & rhs;
#else
    return (CXUInt32x2){ .elements = [
         CXUInt32x2GetElement(lhs, 0) & CXUInt32x2GetElement(rhs, 0),
         CXUInt32x2GetElement(lhs, 1) & CXUInt32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseAndNot(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return CXUInt32x2BitwiseNot(lhs) & rhs;
#else
    return (CXUInt32x2){ .elements = [
         CXUInt32x2BitwiseNot(CXUInt32x2GetElement(lhs, 0)) & CXUInt32x2GetElement(rhs, 0),
         CXUInt32x2BitwiseNot(CXUInt32x2GetElement(lhs, 1)) & CXUInt32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseOr(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs | rhs;
#else
    return (CXUInt32x2){ .elements = [
         CXUInt32x2GetElement(lhs, 0) | CXUInt32x2GetElement(rhs, 0),
         CXUInt32x2GetElement(lhs, 1) | CXUInt32x2GetElement(rhs, 1)
    ]};
#endif
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2BitwiseExclusiveOr(const CXUInt32x2 lhs, const CXUInt32x2 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs ^ rhs;
#else
    return (CXUInt32x2){ .elements = [
         CXUInt32x2GetElement(lhs, 0) ^ CXUInt32x2GetElement(rhs, 0),
         CXUInt32x2GetElement(lhs, 1) ^ CXUInt32x2GetElement(rhs, 1)
    ]};
#endif
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2ShiftLeft(const CXUInt32x2 lhs, const UInt32 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs << rhs;
#else
    return (CXUInt32x2){ .elements = [
         CXUInt32x2GetElement(lhs, 0) << rhs,
         CXUInt32x2GetElement(lhs, 1) << rhs
    ]};
#endif
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXUInt32x2ShiftRight(const CXUInt32x2 lhs, const UInt32 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs >> rhs;
#else
    return (CXUInt32x2){ .elements = [
         CXUInt32x2GetElement(lhs, 0) >> rhs,
         CXUInt32x2GetElement(lhs, 1) >> rhs
    ]};
#endif
}
