#pragma once

#include <math.h>
#include "CXFloat32_t.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 2 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Make(Float32 value0, Float32 value1)
{
    CXFloat32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = (ExtFloatStorage32x2){ value0, value1 };
#else
    storage.array = [value0, value1];
#endif
    return storage;
}

/// Loads 2 x Float32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 2 x Float32 values
/// @return CXFloat32x2(pointer[0], pointer[1])
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeLoad(const Float32* pointer)
{
    CXFloat32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = (ExtFloatStorage32x2){ pointer[0], pointer[1] };
#else
    storage.array = (ExtFloatStorage32x2)[ pointer[0], pointer[1] ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeRepeatingElement(const Float32 value)
{
    CXFloat32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = (ExtFloatStorage32x2){ value, value };
#else
    storage.array = (ExtFloatStorage32x2)[ value, value ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2MakeZero(void)
{
    return CXFloat32x2MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Float32) CXFloat32x2GetElement(const CXFloat32x2 storage, const int index)
{
#if __has_extension(attribute_ext_vector_type)
    return storage.extStorage[index];
#else
    return storage.array[index];
#endif
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXFloat32x2SetElement(CXFloat32x2* storage, const int index, const Float32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage).extStorage[index] = value;
#else
    (*storage).array[index] = value;
#endif
}

// MARK: - Arithmetics

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Absolute(const CXFloat32x2 storage)
{
    CXFloat32x2 absStorage;
#if __has_extension(attribute_ext_vector_type)
    absStorage.extStorage = (ExtFloatStorage32x2){
        fabs(CXFloat32x2GetElement(storage, 0)),
        fabs(CXFloat32x2GetElement(storage, 1))
    };
#else
    absStorage.array = (CXFloat32x2)[
         fabs(CXFloat32x2GetElement(storage, 0)),
         fabs(CXFloat32x2GetElement(storage, 1))
     ];
#endif
    return absStorage;
}

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Negate(const CXFloat32x2 storage)
{
    CXFloat32x2 negStorage;
#if __has_extension(attribute_ext_vector_type)
    negStorage.extStorage = -(storage.extStorage);
#else
    negStorage.array = (CXFloat32x2)[
        -CXFloat32x2GetElement(storage, 0),
        -CXFloat32x2GetElement(storage, 1)
    ];
#endif
    return negStorage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Add(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    CXFloat32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = lhs.extStorage + rhs.extStorage;
#else
    storage.array = (CXFloat32x2)[
         CXFloat32x2GetElement(lhs, 0) + CXFloat32x2GetElement(rhs, 0),
         CXFloat32x2GetElement(lhs, 1) + CXFloat32x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Subtract(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    CXFloat32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = lhs.extStorage - rhs.extStorage;
#else
    storage.array = (CXFloat32x2)[
         CXFloat32x2GetElement(lhs, 0) - CXFloat32x2GetElement(rhs, 0),
         CXFloat32x2GetElement(lhs, 1) - CXFloat32x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Multiply(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    CXFloat32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = lhs.extStorage * rhs.extStorage;
#else
    storage.array = (CXFloat32x2)[
         CXFloat32x2GetElement(lhs, 0) * CXFloat32x2GetElement(rhs, 0),
         CXFloat32x2GetElement(lhs, 1) * CXFloat32x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

/// Divides two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXFloat32x2) CXFloat32x2Divide(const CXFloat32x2 lhs, const CXFloat32x2 rhs)
{
    CXFloat32x2 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = lhs.extStorage / rhs.extStorage;
#else
    storage.array = (CXFloat32x2)[
         CXFloat32x2GetElement(lhs, 0) / CXFloat32x2GetElement(rhs, 0),
         CXFloat32x2GetElement(lhs, 1) / CXFloat32x2GetElement(rhs, 1)
     ];
#endif
    return storage;
}

