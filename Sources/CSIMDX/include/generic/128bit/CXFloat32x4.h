#pragma once

#include <math.h>
#include "CXFloat32_t.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 4 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Make(Float32 value0, Float32 value1, Float32 value2, Float32 value3)
{
    CXFloat32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageFloat32x4){ value0, value1, value2, value3 };
#else
    storage.elements = [value0, value1, value2, value3];
#endif
    return storage;
}

/// Loads 4 x Float32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 4 x Float32 values
/// @return CXFloat32x4(pointer[0], pointer[1], pointer[2], pointer[3])
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeLoad(const Float32* pointer)
{
    CXFloat32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageFloat32x4){ pointer[0], pointer[1], pointer[2], pointer[3] };
#else
    storage.elements = (CEXStorageFloat32x4)[ pointer[0], pointer[1], pointer[2], pointer[3] ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeRepeatingElement(const Float32 value)
{
    CXFloat32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageFloat32x4){ value, value, value, value };
#else
    storage.elements = (CEXStorageFloat32x4)[ value, value, value, value ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4MakeZero(void)
{
    return CXFloat32x4MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x4GetElement(const CXFloat32x4 storage, const int index)
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
STATIC_INLINE_INTRINSIC(void) CXFloat32x4SetElement(CXFloat32x4* storage, const int index, const Float32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage).internalElements[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Arithmetics

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Absolute(const CXFloat32x4 storage)
{
    CXFloat32x4 absStorage;
#if __has_extension(attribute_ext_vector_type)
    absStorage.internalElements = (CEXStorageFloat32x4){
        fabsf(CXFloat32x4GetElement(storage, 0)),
        fabsf(CXFloat32x4GetElement(storage, 1)),
        fabsf(CXFloat32x4GetElement(storage, 2)),
        fabsf(CXFloat32x4GetElement(storage, 3))
    };
#else
    absStorage.elements = (CXFloat32x4)[
        fabsf(CXFloat32x4GetElement(storage, 0)),
        fabsf(CXFloat32x4GetElement(storage, 1)),
        fabsf(CXFloat32x4GetElement(storage, 2)),
        fabsf(CXFloat32x4GetElement(storage, 3))
     ];
#endif
    return absStorage;
}

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Negate(const CXFloat32x4 storage)
{
    CXFloat32x4 negStorage;
#if __has_extension(attribute_ext_vector_type)
    negStorage.internalElements = -(storage.internalElements);
#else
    negStorage.elements = (CXFloat32x4)[
        -CXFloat32x4GetElement(storage, 0),
        -CXFloat32x4GetElement(storage, 1),
        -CXFloat32x4GetElement(storage, 2),
        -CXFloat32x4GetElement(storage, 3)
    ];
#endif
    return negStorage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Add(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    CXFloat32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements + rhs.internalElements;
#else
    storage.elements = (CXFloat32x4)[
         CXFloat32x4GetElement(lhs, 0) + CXFloat32x4GetElement(rhs, 0),
         CXFloat32x4GetElement(lhs, 1) + CXFloat32x4GetElement(rhs, 1),
         CXFloat32x4GetElement(lhs, 2) + CXFloat32x4GetElement(rhs, 2),
         CXFloat32x4GetElement(lhs, 3) + CXFloat32x4GetElement(rhs, 3)
     ];
#endif
    return storage;
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Subtract(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    CXFloat32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements - rhs.internalElements;
#else
    storage.elements = (CXFloat32x4)[
         CXFloat32x4GetElement(lhs, 0) - CXFloat32x4GetElement(rhs, 0),
         CXFloat32x4GetElement(lhs, 1) - CXFloat32x4GetElement(rhs, 1),
         CXFloat32x4GetElement(lhs, 2) - CXFloat32x4GetElement(rhs, 2),
         CXFloat32x4GetElement(lhs, 3) - CXFloat32x4GetElement(rhs, 3)
     ];
#endif
    return storage;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Multiply(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    CXFloat32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements * rhs.internalElements;
#else
    storage.elements = (CXFloat32x4)[
         CXFloat32x4GetElement(lhs, 0) * CXFloat32x4GetElement(rhs, 0),
         CXFloat32x4GetElement(lhs, 1) * CXFloat32x4GetElement(rhs, 1),
         CXFloat32x4GetElement(lhs, 2) * CXFloat32x4GetElement(rhs, 2),
         CXFloat32x4GetElement(lhs, 3) * CXFloat32x4GetElement(rhs, 3)
     ];
#endif
    return storage;
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x4) CXFloat32x4Divide(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
{
    CXFloat32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements / rhs.internalElements;
#else
    storage.elements = (CXFloat32x4)[
         CXFloat32x4GetElement(lhs, 0) / CXFloat32x4GetElement(rhs, 0),
         CXFloat32x4GetElement(lhs, 1) / CXFloat32x4GetElement(rhs, 1),
         CXFloat32x4GetElement(lhs, 2) / CXFloat32x4GetElement(rhs, 2),
         CXFloat32x4GetElement(lhs, 3) / CXFloat32x4GetElement(rhs, 3)
     ];
#endif
    return storage;
}

