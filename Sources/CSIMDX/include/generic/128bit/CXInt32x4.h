#pragma once

#include <stdlib.h>
#include "CXInt32_t.h"

// MARK: Designated Initializers

/// Returns an intrinsic initialized to the 4 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Make(Int32 value0, Int32 value1, Int32 value2, Int32 value3)
{
    CXInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageInt32x4){ value0, value1, value2, value3 };
#else
    storage.elements = [value0, value1, value2, value3];
#endif
    return storage;
}

/// Loads 4 x Int32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 4 x Int32 values
/// @return CXInt32x4(pointer[0], pointer[1], pointer[2], pointer[3])
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeLoad(const Int32* pointer)
{
    CXInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageInt32x4){ pointer[0], pointer[1], pointer[2], pointer[3] };
#else
    storage.elements = (CEXStorageInt32x4)[ pointer[0], pointer[1], pointer[2], pointer[3] ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeRepeatingElement(const Int32 value)
{
    CXInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageInt32x4){ value, value, value, value };
#else
    storage.elements = (CEXStorageInt32x4)[ value, value, value, value ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4MakeZero(void)
{
    return CXInt32x4MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int32) CXInt32x4GetElement(const CXInt32x4 storage, const int index)
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
STATIC_INLINE_INTRINSIC(void) CXInt32x4SetElement(CXInt32x4* storage, const int index, const Int32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage).internalElements[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Negate(const CXInt32x4 storage)
{
    CXInt32x4 negStorage;
#if __has_extension(attribute_ext_vector_type)
    negStorage.internalElements = -(storage.internalElements);
#else
    negStorage.elements = (CXInt32x4)[
        -CXInt32x4GetElement(storage, 0),
        -CXInt32x4GetElement(storage, 1),
        -CXInt32x4GetElement(storage, 2),
        -CXInt32x4GetElement(storage, 3)
    ];
#endif
    return negStorage;
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXUInt32x4) CXInt32x4Absolute(const CXInt32x4 storage)
{
    CXUInt32x4 absStorage;
#if __has_extension(attribute_ext_vector_type)
    absStorage.internalElements = (CEXStorageUInt32x4){
        abs(CXInt32x4GetElement(storage, 0)),
        abs(CXInt32x4GetElement(storage, 1)),
        abs(CXInt32x4GetElement(storage, 2)),
        abs(CXInt32x4GetElement(storage, 3))
    };
#else
    absStorage.elements = (CXUInt32x4)[
        abs(CXInt32x4GetElement(storage, 0)),
        abs(CXInt32x4GetElement(storage, 1)),
        abs(CXInt32x4GetElement(storage, 2)),
        abs(CXInt32x4GetElement(storage, 3))
     ];
#endif
    return absStorage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Add(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    CXInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements + rhs.internalElements;
#else
    storage.elements = (CXInt32x4)[
         CXInt32x4GetElement(lhs, 0) + CXInt32x4GetElement(rhs, 0),
         CXInt32x4GetElement(lhs, 1) + CXInt32x4GetElement(rhs, 1),
         CXInt32x4GetElement(lhs, 2) + CXInt32x4GetElement(rhs, 2),
         CXInt32x4GetElement(lhs, 3) + CXInt32x4GetElement(rhs, 3)
     ];
#endif
    return storage;
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Subtract(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    CXInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements - rhs.internalElements;
#else
    storage.elements = (CXInt32x4)[
         CXInt32x4GetElement(lhs, 0) - CXInt32x4GetElement(rhs, 0),
         CXInt32x4GetElement(lhs, 1) - CXInt32x4GetElement(rhs, 1),
         CXInt32x4GetElement(lhs, 2) - CXInt32x4GetElement(rhs, 2),
         CXInt32x4GetElement(lhs, 3) - CXInt32x4GetElement(rhs, 3)
     ];
#endif
    return storage;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Multiply(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    CXInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements * rhs.internalElements;
#else
    storage.elements = (CXInt32x4)[
         CXInt32x4GetElement(lhs, 0) * CXInt32x4GetElement(rhs, 0),
         CXInt32x4GetElement(lhs, 1) * CXInt32x4GetElement(rhs, 1),
         CXInt32x4GetElement(lhs, 2) * CXInt32x4GetElement(rhs, 2),
         CXInt32x4GetElement(lhs, 3) * CXInt32x4GetElement(rhs, 3)
     ];
#endif
    return storage;
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x4) CXInt32x4Divide(const CXInt32x4 lhs, const CXInt32x4 rhs)
{
    CXInt32x4 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements / rhs.internalElements;
#else
    storage.elements = (CXInt32x4)[
         CXInt32x4GetElement(lhs, 0) / CXInt32x4GetElement(rhs, 0),
         CXInt32x4GetElement(lhs, 1) / CXInt32x4GetElement(rhs, 1),
         CXInt32x4GetElement(lhs, 2) / CXInt32x4GetElement(rhs, 2),
         CXInt32x4GetElement(lhs, 3) / CXInt32x4GetElement(rhs, 3)
     ];
#endif
    return storage;
}

