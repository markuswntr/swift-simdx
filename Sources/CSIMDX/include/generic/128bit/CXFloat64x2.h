#pragma once

#include <math.h>
#include "CXFloat64_t.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Make(Float64 value0, Float64 value1)
{
    CXFloat64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageFloat64x2){ value0, value1 };
#else
    storage.elements = [value0, value1];
#endif
    return storage;
}

/// Loads 2 x Float64 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Float64 values
/// @return CXFloat64x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2MakeLoad(const Float64* pointer)
{
    CXFloat64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageFloat64x2){ pointer[0], pointer[1] };
#else
    storage.elements = (CEXStorageFloat64x2)[ pointer[0], pointer[1] ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2MakeRepeatingElement(const Float64 value)
{
    CXFloat64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = (CEXStorageFloat64x2){ value, value };
#else
    storage.elements = (CEXStorageFloat64x2)[ value, value ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2MakeZero(void)
{
    return CXFloat64x2MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Float64) CXFloat64x2GetElement(const CXFloat64x2 storage, const int index)
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
STATIC_INLINE_INTRINSIC(void) CXFloat64x2SetElement(CXFloat64x2* storage, const int index, const Float64 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage).internalElements[index] = value;
#else
    (*storage).elements[index] = value;
#endif
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Negate(const CXFloat64x2 storage)
{
    CXFloat64x2 negStorage;
#if __has_extension(attribute_ext_vector_type)
    negStorage.internalElements = -(storage.internalElements);
#else
    negStorage.elements = (CXFloat64x2)[
        -CXFloat64x2GetElement(storage, 0),
        -CXFloat64x2GetElement(storage, 1)
    ];
#endif
    return negStorage;
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Absolute(const CXFloat64x2 storage)
{
    CXFloat64x2 absStorage;
#if __has_extension(attribute_ext_vector_type)
    absStorage.internalElements = (CEXStorageFloat64x2){
        fabs(CXFloat64x2GetElement(storage, 0)),
        fabs(CXFloat64x2GetElement(storage, 1))
    };
#else
    absStorage.elements = (CXFloat64x2)[
         fabs(CXFloat64x2GetElement(storage, 0)),
         fabs(CXFloat64x2GetElement(storage, 1))
     ];
#endif
    return absStorage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Add(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    CXFloat64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements + rhs.internalElements;
#else
    storage.elements = (CXFloat64x2)[
         CXFloat64x2GetElement(lhs, 0) + CXFloat64x2GetElement(rhs, 0),
         CXFloat64x2GetElement(lhs, 1) + CXFloat64x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Subtract(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    CXFloat64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements - rhs.internalElements;
#else
    storage.elements = (CXFloat64x2)[
         CXFloat64x2GetElement(lhs, 0) - CXFloat64x2GetElement(rhs, 0),
         CXFloat64x2GetElement(lhs, 1) - CXFloat64x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Multiply(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    CXFloat64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements * rhs.internalElements;
#else
    storage.elements = (CXFloat64x2)[
         CXFloat64x2GetElement(lhs, 0) * CXFloat64x2GetElement(rhs, 0),
         CXFloat64x2GetElement(lhs, 1) * CXFloat64x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat64x2) CXFloat64x2Divide(const CXFloat64x2 lhs, const CXFloat64x2 rhs)
{
    CXFloat64x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.internalElements = lhs.internalElements / rhs.internalElements;
#else
    storage.elements = (CXFloat64x2)[
         CXFloat64x2GetElement(lhs, 0) / CXFloat64x2GetElement(rhs, 0),
         CXFloat64x2GetElement(lhs, 1) / CXFloat64x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

