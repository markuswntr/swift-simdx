#pragma once

#include <math.h>
#include "CXFloat32_t.h"

// MARK: Designated Initializers

/// Returns an intrinsic initialized to the 3 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Make(Float32 value0, Float32 value1, Float32 value2)
{
    CXFloat32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageFloat32x3){ value0, value1, value2 };
#else
    storage.elements = [value0, value1, value2];
#endif
    return storage;
}

/// Loads 3 x Float32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 3 x Float32 values
/// @return CXFloat32x3(pointer[0], pointer[1], pointer[2])
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeLoad(const Float32* pointer)
{
    CXFloat32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageFloat32x3){ pointer[0], pointer[1], pointer[2] };
#else
    storage.elements = (CEXStorageFloat32x3)[ pointer[0], pointer[1], pointer[2] ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeRepeatingElement(const Float32 value)
{
    CXFloat32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageFloat32x3){ value, value, value };
#else
    storage.elements = (CEXStorageFloat32x3)[ value, value, value ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3MakeZero(void)
{
    return CXFloat32x3MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x3GetElement(const CXFloat32x3 storage, const int index)
{
#if __has_extension(attribute_ext_vector_type)
    return storage.internalElements[index];
#else
    return storage.elements[index];
#endif
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXFloat32x3SetElement(CXFloat32x3* storage, const int index, const Float32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage).internalElements[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Negate(const CXFloat32x3 storage)
{
    CXFloat32x3 negStorage;
#if __has_extension(attribute_ext_vector_type)
    negStorage.internalElements = -(storage.internalElements);
#else
    negStorage.elements = (CXFloat32x3)[
        -CXFloat32x3GetElement(storage, 0),
        -CXFloat32x3GetElement(storage, 1),
        -CXFloat32x3GetElement(storage, 2)
    ];
#endif
    return negStorage;
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Absolute(const CXFloat32x3 storage)
{
    CXFloat32x3 absStorage;
#if __has_extension(attribute_ext_vector_type)
    absStorage.internalElements = (CEXStorageFloat32x3){
        fabsf(CXFloat32x3GetElement(storage, 0)),
        fabsf(CXFloat32x3GetElement(storage, 1)),
        fabsf(CXFloat32x3GetElement(storage, 2))
    };
#else
    absStorage.elements = (CXFloat32x3)[
        fabsf(CXFloat32x3GetElement(storage, 0)),
        fabsf(CXFloat32x3GetElement(storage, 1)),
        fabsf(CXFloat32x3GetElement(storage, 2))
     ];
#endif
    return absStorage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Add(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    CXFloat32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements + rhs.internalElements;
#else
    storage.elements = (CXFloat32x3)[
         CXFloat32x3GetElement(lhs, 0) + CXFloat32x3GetElement(rhs, 0),
         CXFloat32x3GetElement(lhs, 1) + CXFloat32x3GetElement(rhs, 1),
         CXFloat32x3GetElement(lhs, 2) + CXFloat32x3GetElement(rhs, 2)
     ];
#endif
    return storage;
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Subtract(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    CXFloat32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements - rhs.internalElements;
#else
    storage.elements = (CXFloat32x3)[
         CXFloat32x3GetElement(lhs, 0) - CXFloat32x3GetElement(rhs, 0),
         CXFloat32x3GetElement(lhs, 1) - CXFloat32x3GetElement(rhs, 1),
         CXFloat32x3GetElement(lhs, 2) - CXFloat32x3GetElement(rhs, 2)
     ];
#endif
    return storage;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Multiply(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    CXFloat32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements * rhs.internalElements;
#else
    storage.elements = (CXFloat32x3)[
         CXFloat32x3GetElement(lhs, 0) * CXFloat32x3GetElement(rhs, 0),
         CXFloat32x3GetElement(lhs, 1) * CXFloat32x3GetElement(rhs, 1),
         CXFloat32x3GetElement(lhs, 2) * CXFloat32x3GetElement(rhs, 2)
     ];
#endif
    return storage;
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x3) CXFloat32x3Divide(const CXFloat32x3 lhs, const CXFloat32x3 rhs)
{
    CXFloat32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements / rhs.internalElements;
#else
    storage.elements = (CXFloat32x3)[
         CXFloat32x3GetElement(lhs, 0) / CXFloat32x3GetElement(rhs, 0),
         CXFloat32x3GetElement(lhs, 1) / CXFloat32x3GetElement(rhs, 1),
         CXFloat32x3GetElement(lhs, 2) / CXFloat32x3GetElement(rhs, 2)
     ];
#endif
    return storage;
}

