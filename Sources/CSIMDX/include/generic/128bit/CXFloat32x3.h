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

#include <math.h>
#include "CXTypes_t.h"

/// Initializes a storage to given elements, from least-significant to most-significant bits.
/// @return `(CXFloat32x3){ element0, element1, element2 }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Make(Float32 element0, Float32 element1, Float32 element2)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x3){ element0, element1, element2 };
#else
    return (CXFloat32x3){ .elements = [ element0, element1, element2 ] };
#endif
}

/// Loads elements from an unaligned memory pointer.
/// @return `(CXFloat32x3){ pointer[0], pointer[1], pointer[2] }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeLoad(const Float32* pointer)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x3){ pointer[0], pointer[1], pointer[2] };
#else
    return (CXFloat32x3){ .elements = [ pointer[0], pointer[1], pointer[2] ] };
#endif
}

/// Returns an intrinsic type with all elements initialized to `value`.
/// @return `(CXFloat32x3){ value, value, value }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeRepeatingElement(const Float32 value)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x3)(value);
#else
    return (CXFloat32x3){ .elements = [ value, value, value ] };
#endif
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
/// @return `(CXFloat32x3){ 0.f, 0.f, 0.f }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeZero(void)
{
    return CXFloat32x3MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @return `storage[index]`
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x3GetElement(const CXFloat32x3 storage, const int index)
{
#if __has_extension(attribute_ext_vector_type)
    return storage[index];
#else
    return storage.elements[index];
#endif
}

/// Sets the element at `index` from `storage` to given value, i.e. `(*storage)[index] = value;`
STATIC_INLINE_INTRINSIC(void) CXFloat32x3SetElement(CXFloat32x3* storage, const int index, const Float32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage)[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Conversion

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x3){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3FromCXInt32x3(CXInt32x3 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXFloat32x3);
#else
    return (CXFloat32x3){ .elements = [
        (Float32)(operand.elements[0]),
        (Float32)(operand.elements[1]),
        (Float32)(operand.elements[2])
    ]};
#endif
}

/// Converts the elements of `operand`, load them in the new storage and returns the result.
/// @returns `(CXFloat32x3){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3FromCXUInt32x3(CXUInt32x3 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return __builtin_convertvector(operand, CXFloat32x3);
#else
    return (CXFloat32x3){ .elements = [
        (Float32)(operand.elements[0]),
        (Float32)(operand.elements[1]),
        (Float32)(operand.elements[2])
    ]};
#endif
}

// MARK: Minimum & Maximum

/// Performs element-by-element comparison of both storages and returns the lesser of each pair in the result.
/// @return `(CXFloat32x3){ lhs[0] < rhs[0] ? lhs[0] : rhs[0], lhs[1] < rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Minimum(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    Float64 lhs0 = CXFloat32x3GetElement(lhs, 0), rhs0 = CXFloat32x3GetElement(rhs, 0);
    Float64 lhs1 = CXFloat32x3GetElement(lhs, 1), rhs1 = CXFloat32x3GetElement(rhs, 1);
    Float64 lhs2 = CXFloat32x3GetElement(lhs, 2), rhs2 = CXFloat32x3GetElement(rhs, 2);

#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x3){
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1,
        lhs2 < rhs2 ? lhs2 : rhs2
    };
#else
    return (CXFloat32x3){ .elements = [
        lhs0 < rhs0 ? lhs0 : rhs0,
        lhs1 < rhs1 ? lhs1 : rhs1,
        lhs2 < rhs2 ? lhs2 : rhs2
    ]};
#endif
}

/// Performs element-by-element comparison of both storages and returns the greater of each pair in the result.
/// @return `(CXFloat32x3){ lhs[0] > rhs[0] ? lhs[0] : rhs[0], lhs[1] > rhs[1] ? lhs[1] : rhs[1], ... }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Maximum(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    Float64 lhs0 = CXFloat32x3GetElement(lhs, 0), rhs0 = CXFloat32x3GetElement(rhs, 0);
    Float64 lhs1 = CXFloat32x3GetElement(lhs, 1), rhs1 = CXFloat32x3GetElement(rhs, 1);
    Float64 lhs2 = CXFloat32x3GetElement(lhs, 2), rhs2 = CXFloat32x3GetElement(rhs, 2);

#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x3){
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1,
        lhs2 > rhs2 ? lhs2 : rhs2
    };
#else
    return (CXFloat32x3){ .elements = [
        lhs0 > rhs0 ? lhs0 : rhs0,
        lhs1 > rhs1 ? lhs1 : rhs1,
        lhs2 > rhs2 ? lhs2 : rhs2
    ]};
#endif
}

// MARK: - Arithmetics

/// Returns the negated storage (element-wise).
/// @return `(CXFloat32x3){ -(operand[0]), -(operand[1]), -(operand[2]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Negate(const CXFloat32x3 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return -(operand);
#else
    return (CXFloat32x3){ .elements = [
        -CXFloat32x3GetElement(operand, 0),
        -CXFloat32x3GetElement(operand, 1),
        -CXFloat32x3GetElement(operand, 2)
    ]};
#endif
}

/// Returns the absolute storage (element-wise).
/// @return `(CXFloat32x3){ abs(operand[0]), abs(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Absolute(const CXFloat32x3 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x3){
        fabsf(CXFloat32x3GetElement(operand, 0)),
        fabsf(CXFloat32x3GetElement(operand, 1)),
        fabsf(CXFloat32x3GetElement(operand, 2))
    };
#else
    return (CXFloat32x3){ .elements = [
        fabsf(CXFloat32x3GetElement(operand, 0)),
        fabsf(CXFloat32x3GetElement(operand, 1)),
        fabsf(CXFloat32x3GetElement(operand, 2))
    ]};
#endif
}

// MARK: Additive

/// Adds two storages (element-wise).
/// @return `(CXFloat32x3){ lhs[0] + rhs[0], lhs[1] + rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Add(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs + rhs;
#else
    return (CXFloat32x3){ .elements = [
         CXFloat32x3GetElement(lhs, 0) + CXFloat32x3GetElement(rhs, 0),
         CXFloat32x3GetElement(lhs, 1) + CXFloat32x3GetElement(rhs, 1),
         CXFloat32x3GetElement(lhs, 2) + CXFloat32x3GetElement(rhs, 2)
    ]};
#endif
}

/// Subtracts a storage from another (element-wise).
/// @return `(CXFloat32x3){ lhs[0] - rhs[0], lhs[1] - rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Subtract(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs - rhs;
#else
    return (CXFloat32x3){ .elements = [
         CXFloat32x3GetElement(lhs, 0) - CXFloat32x3GetElement(rhs, 0),
         CXFloat32x3GetElement(lhs, 1) - CXFloat32x3GetElement(rhs, 1),
         CXFloat32x3GetElement(lhs, 2) - CXFloat32x3GetElement(rhs, 2)
    ]};
#endif
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise).
/// @return `(CXFloat32x3){ lhs[0] * rhs[0], lhs[1] * rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Multiply(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs * rhs;
#else
    return (CXFloat32x3){ .elements = [
         CXFloat32x3GetElement(lhs, 0) * CXFloat32x3GetElement(rhs, 0),
         CXFloat32x3GetElement(lhs, 1) * CXFloat32x3GetElement(rhs, 1),
         CXFloat32x3GetElement(lhs, 2) * CXFloat32x3GetElement(rhs, 2)
    ]};
#endif
}

/// Divides two storages (element-wise).
/// @return `(CXFloat32x3){ lhs[0] / rhs[0], lhs[1] / rhs[1] }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Divide(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
#if __has_extension(attribute_ext_vector_type)
    return lhs / rhs;
#else
    return (CXFloat32x3){ .elements = [
         CXFloat32x3GetElement(lhs, 0) / CXFloat32x3GetElement(rhs, 0),
         CXFloat32x3GetElement(lhs, 1) / CXFloat32x3GetElement(rhs, 1),
         CXFloat32x3GetElement(lhs, 2) / CXFloat32x3GetElement(rhs, 2)
    ]};
#endif
}

/// Calculates the square root (element-wise).
/// @return `(CXFloat32x3){ sqrt(operand[0]), sqrt(operand[1]) }`
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3SquareRoot(const CXFloat32x3 operand)
{
#if __has_extension(attribute_ext_vector_type)
    return (CXFloat32x3){
        sqrtf(CXFloat32x3GetElement(operand, 0)),
        sqrtf(CXFloat32x3GetElement(operand, 1)),
        sqrtf(CXFloat32x3GetElement(operand, 2))
    };
#else
    return (CXFloat32x3){ .elements = [
       sqrtf(CXFloat32x3GetElement(operand, 0)),
       sqrtf(CXFloat32x3GetElement(operand, 1)),
       sqrtf(CXFloat32x3GetElement(operand, 2))
    ]};
#endif
}
