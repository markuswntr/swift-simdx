#pragma once

#include <stdlib.h>
#include "CXInt64_t.h"

// MARK: Designated Initializers

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Make(Int64 value0, Int64 value1)
{
    CXInt64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageInt64x2){ value0, value1 };
#else
    storage.elements = [value0, value1];
#endif
    return storage;
}

/// Loads 2 x Int64 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Int64 values
/// @return CXInt64x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeLoad(const Int64* pointer)
{
    CXInt64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageInt64x2){ pointer[0], pointer[1] };
#else
    storage.elements = (CEXStorageInt64x2)[ pointer[0], pointer[1] ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeRepeatingElement(const Int64 value)
{
    CXInt64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageInt64x2){ value, value };
#else
    storage.elements = (CEXStorageInt64x2)[ value, value ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2MakeZero(void)
{
    return CXInt64x2MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int64) CXInt64x2GetElement(const CXInt64x2 storage, const int index)
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
STATIC_INLINE_INTRINSIC(void) CXInt64x2SetElement(CXInt64x2* storage, const int index, const Int64 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage).internalElements[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Negate(const CXInt64x2 storage)
{
    CXInt64x2 negStorage;
#if __has_extension(attribute_ext_vector_type)
    negStorage.internalElements = -(storage.internalElements);
#else
    negStorage.elements = (CXInt64x2)[
        -CXInt64x2GetElement(storage, 0),
        -CXInt64x2GetElement(storage, 1)
    ];
#endif
    return negStorage;
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXUInt64x2) CXInt64x2Absolute(const CXInt64x2 storage)
{
    CXUInt64x2 absStorage;
#if __has_extension(attribute_ext_vector_type)
    absStorage.internalElements = (CEXStorageUInt64x2){
        labs(CXInt64x2GetElement(storage, 0)),
        labs(CXInt64x2GetElement(storage, 1))
    };
#else
    absStorage.elements = (CXUInt64x2)[
         labs(CXInt64x2GetElement(storage, 0)),
         labs(CXInt64x2GetElement(storage, 1))
     ];
#endif
    return absStorage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Add(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    CXInt64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements + rhs.internalElements;
#else
    storage.elements = (CXInt64x2)[
         CXInt64x2GetElement(lhs, 0) + CXInt64x2GetElement(rhs, 0),
         CXInt64x2GetElement(lhs, 1) + CXInt64x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Subtract(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    CXInt64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements - rhs.internalElements;
#else
    storage.elements = (CXInt64x2)[
         CXInt64x2GetElement(lhs, 0) - CXInt64x2GetElement(rhs, 0),
         CXInt64x2GetElement(lhs, 1) - CXInt64x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Multiply(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    CXInt64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements * rhs.internalElements;
#else
    storage.elements = (CXInt64x2)[
         CXInt64x2GetElement(lhs, 0) * CXInt64x2GetElement(rhs, 0),
         CXInt64x2GetElement(lhs, 1) * CXInt64x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt64x2) CXInt64x2Divide(const CXInt64x2 lhs, const CXInt64x2 rhs)
{
    CXInt64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements / rhs.internalElements;
#else
    storage.elements = (CXInt64x2)[
         CXInt64x2GetElement(lhs, 0) / CXInt64x2GetElement(rhs, 0),
         CXInt64x2GetElement(lhs, 1) / CXInt64x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

