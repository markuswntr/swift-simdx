#pragma once

#include <stdlib.h>
#include "CXInt32_t.h"
#include "CXUInt32_t.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Make(Int32 value0, Int32 value1)
{
    CXInt32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageInt32x2){ value0, value1 };
#else
    storage.elements = [value0, value1];
#endif
    return storage;
}

/// Loads 2 x Int32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Int32 values
/// @return CXInt32x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2MakeLoad(const Int32* pointer)
{
    CXInt32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageInt32x2){ pointer[0], pointer[1] };
#else
    storage.elements = (CEXStorageInt32x2)[ pointer[0], pointer[1] ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2MakeRepeatingElement(const Int32 value)
{
    CXInt32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageInt32x2){ value, value };
#else
    storage.elements = (CEXStorageInt32x2)[ value, value ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2MakeZero(void)
{
    return CXInt32x2MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int32) CXInt32x2GetElement(const CXInt32x2 storage, const int index)
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
STATIC_INLINE_INTRINSIC(void) CXInt32x2SetElement(CXInt32x2* storage, const int index, const Int32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage).internalElements[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Negate(const CXInt32x2 storage)
{
    CXInt32x2 negStorage;
#if __has_extension(attribute_ext_vector_type)
    negStorage.internalElements = -(storage.internalElements);
#else
    negStorage.elements = (CXInt32x2)[
        -CXInt32x2GetElement(storage, 0),
        -CXInt32x2GetElement(storage, 1)
    ];
#endif
    return negStorage;
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXUInt32x2) CXInt32x2Absolute(const CXInt32x2 storage)
{
    CXUInt32x2 absStorage;
#if __has_extension(attribute_ext_vector_type)
    absStorage.internalElements = (CEXStorageUInt32x2){
        abs(CXInt32x2GetElement(storage, 0)),
        abs(CXInt32x2GetElement(storage, 1))
    };
#else
    absStorage.elements = (CXUInt32x2)[
         abs(CXInt32x2GetElement(storage, 0)),
         abs(CXInt32x2GetElement(storage, 1))
     ];
#endif
    return absStorage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Add(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
    CXInt32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements + rhs.internalElements;
#else
    storage.elements = (CXInt32x2)[
         CXInt32x2GetElement(lhs, 0) + CXInt32x2GetElement(rhs, 0),
         CXInt32x2GetElement(lhs, 1) + CXInt32x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Subtract(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
    CXInt32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements - rhs.internalElements;
#else
    storage.elements = (CXInt32x2)[
         CXInt32x2GetElement(lhs, 0) - CXInt32x2GetElement(rhs, 0),
         CXInt32x2GetElement(lhs, 1) - CXInt32x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x2) CXInt32x2Multiply(const CXInt32x2 lhs, const CXInt32x2 rhs)
{
    CXInt32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements * rhs.internalElements;
#else
    storage.elements = (CXInt32x2)[
         CXInt32x2GetElement(lhs, 0) * CXInt32x2GetElement(rhs, 0),
         CXInt32x2GetElement(lhs, 1) * CXInt32x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}
