#pragma once

#include <stdlib.h>
#include "CXUInt32_t.h"

// MARK: Designated Initializers

/// Returns an intrinsic initialized to the 4 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Make(UInt32 value0, UInt32 value1, UInt32 value2, UInt32 value3)
{
    CXUInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageUInt32x4){ value0, value1, value2, value3 };
#else
    storage.elements = [value0, value1, value2, value3];
#endif
    return storage;
}

/// Loads 4 x UInt32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 4 x UInt32 values
/// @return CXUInt32x4(pointer[0], pointer[1], pointer[2], pointer[3])
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4MakeLoad(const UInt32* pointer)
{
    CXUInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageUInt32x4){ pointer[0], pointer[1], pointer[2], pointer[3] };
#else
    storage.elements = (CEXStorageUInt32x4)[ pointer[0], pointer[1], pointer[2], pointer[3] ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4MakeRepeatingElement(const UInt32 value)
{
    CXUInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageUInt32x4){ value, value, value, value };
#else
    storage.elements = (CEXStorageUInt32x4)[ value, value, value, value ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4MakeZero(void)
{
    return CXUInt32x4MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(UInt32) CXUInt32x4GetElement(const CXUInt32x4 storage, const int index)
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
STATIC_INLINE_INTRINSIC(void) CXUInt32x4SetElement(CXUInt32x4* storage, const int index, const UInt32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage).internalElements[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Arithmetics

/// Returns the given storage unchanged. Allows for symmetry with signed values.
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Absolute(const CXUInt32x4 storage)
{
    return storage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Add(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    CXUInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements + rhs.internalElements;
#else
    storage.elements = (CXUInt32x4)[
         CXUInt32x4GetElement(lhs, 0) + CXUInt32x4GetElement(rhs, 0),
         CXUInt32x4GetElement(lhs, 1) + CXUInt32x4GetElement(rhs, 1),
         CXUInt32x4GetElement(lhs, 2) + CXUInt32x4GetElement(rhs, 2),
         CXUInt32x4GetElement(lhs, 3) + CXUInt32x4GetElement(rhs, 3)
     ];
#endif
    return storage;
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Subtract(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    CXUInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements - rhs.internalElements;
#else
    storage.elements = (CXUInt32x4)[
         CXUInt32x4GetElement(lhs, 0) - CXUInt32x4GetElement(rhs, 0),
         CXUInt32x4GetElement(lhs, 1) - CXUInt32x4GetElement(rhs, 1),
         CXUInt32x4GetElement(lhs, 2) - CXUInt32x4GetElement(rhs, 2),
         CXUInt32x4GetElement(lhs, 3) - CXUInt32x4GetElement(rhs, 3)
     ];
#endif
    return storage;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXUInt32x4Multiply(const CXUInt32x4 lhs, const CXUInt32x4 rhs)
{
    CXUInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements * rhs.internalElements;
#else
    storage.elements = (CXUInt32x4)[
         CXUInt32x4GetElement(lhs, 0) * CXUInt32x4GetElement(rhs, 0),
         CXUInt32x4GetElement(lhs, 1) * CXUInt32x4GetElement(rhs, 1),
         CXUInt32x4GetElement(lhs, 2) * CXUInt32x4GetElement(rhs, 2),
         CXUInt32x4GetElement(lhs, 3) * CXUInt32x4GetElement(rhs, 3)
     ];
#endif
    return storage;
}
