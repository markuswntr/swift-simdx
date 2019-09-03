#pragma once

#include <stdlib.h>
#include "CXUInt32_t.h"

// MARK: Designated Initializers

/// Returns an intrinsic initialized to the 3 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Make(UInt32 value0, UInt32 value1, UInt32 value2)
{
    CXUInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageUInt32x3){ value0, value1, value2 };
#else
    storage.elements = [value0, value1, value2];
#endif
    return storage;
}

/// Loads 3 x UInt32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 3 x UInt32 values
/// @return CXUInt32x3(pointer[0], pointer[1], pointer[2])
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3MakeLoad(const UInt32* pointer)
{
    CXUInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageUInt32x3){ pointer[0], pointer[1], pointer[2] };
#else
    storage.elements = (CEXStorageUInt32x3)[ pointer[0], pointer[1], pointer[2] ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3MakeRepeatingElement(const UInt32 value)
{
    CXUInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageUInt32x3){ value, value, value };
#else
    storage.elements = (CEXStorageUInt32x3)[ value, value, value ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3MakeZero(void)
{
    return CXUInt32x3MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(UInt32) CXUInt32x3GetElement(const CXUInt32x3 storage, const int index)
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
STATIC_INLINE_INTRINSIC(void) CXUInt32x3SetElement(CXUInt32x3* storage, const int index, const UInt32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage).internalElements[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Arithmetics

/// Returns the given storage unchanged. Allows for symmetry with signed values.
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Absolute(const CXUInt32x3 storage)
{
    return storage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Add(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    CXUInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements + rhs.internalElements;
#else
    storage.elements = (CXUInt32x3)[
         CXUInt32x3GetElement(lhs, 0) + CXUInt32x3GetElement(rhs, 0),
         CXUInt32x3GetElement(lhs, 1) + CXUInt32x3GetElement(rhs, 1),
         CXUInt32x3GetElement(lhs, 2) + CXUInt32x3GetElement(rhs, 2)
     ];
#endif
    return storage;
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Subtract(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    CXUInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements - rhs.internalElements;
#else
    storage.elements = (CXUInt32x3)[
         CXUInt32x3GetElement(lhs, 0) - CXUInt32x3GetElement(rhs, 0),
         CXUInt32x3GetElement(lhs, 1) - CXUInt32x3GetElement(rhs, 1),
         CXUInt32x3GetElement(lhs, 2) - CXUInt32x3GetElement(rhs, 2)
     ];
#endif
    return storage;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXUInt32x3Multiply(const CXUInt32x3 lhs, const CXUInt32x3 rhs)
{
    CXUInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements * rhs.internalElements;
#else
    storage.elements = (CXUInt32x3)[
         CXUInt32x3GetElement(lhs, 0) * CXUInt32x3GetElement(rhs, 0),
         CXUInt32x3GetElement(lhs, 1) * CXUInt32x3GetElement(rhs, 1),
         CXUInt32x3GetElement(lhs, 2) * CXUInt32x3GetElement(rhs, 2)
     ];
#endif
    return storage;
}
