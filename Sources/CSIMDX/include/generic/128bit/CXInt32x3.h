#pragma once

#include <stdlib.h>
#include "CXInt32_t.h"

// MARK: - Designated Initializers

/// Returns an intrinsic initialized to the 3 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Make(Int32 value0, Int32 value1, Int32 value2)
{
    CXInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = (ExtIntStorage32x3){ value0, value1, value2 };
#else
    storage.array = [value0, value1, value2];
#endif
    return storage;
}

/// Loads 3 x Int32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 3 x Int32 values
/// @return CXInt32x3(pointer[0], pointer[1], pointer[2])
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeLoad(const Int32* pointer)
{
    CXInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = (ExtIntStorage32x3){ pointer[0], pointer[1], pointer[2] };
#else
    storage.array = (ExtIntStorage32x3)[ pointer[0], pointer[1], pointer[2] ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeRepeatingElement(const Int32 value)
{
    CXInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = (ExtIntStorage32x3){ value, value, value };
#else
    storage.array = (ExtIntStorage32x3)[ value, value, value ];
#endif
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeZero(void)
{
    return CXInt32x3MakeRepeatingElement(0.f);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int32) CXInt32x3GetElement(const CXInt32x3 storage, const int index)
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
STATIC_INLINE_INTRINSIC(void) CXInt32x3SetElement(CXInt32x3* storage, const int index, const Int32 value)
{
#if __has_extension(attribute_ext_vector_type)
    (*storage).extStorage[index] = value;
#else
    (*storage).array[index] = value;
#endif
}

// MARK: - Arithmetics

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Absolute(const CXInt32x3 storage)
{
    CXInt32x3 absStorage;
#if __has_extension(attribute_ext_vector_type)
    absStorage.extStorage = (ExtIntStorage32x3){
        abs(CXInt32x3GetElement(storage, 0)),
        abs(CXInt32x3GetElement(storage, 1)),
        abs(CXInt32x3GetElement(storage, 2))
    };
#else
    absStorage.array = (CXInt32x3)[
        abs(CXInt32x3GetElement(storage, 0)),
        abs(CXInt32x3GetElement(storage, 1)),
        abs(CXInt32x3GetElement(storage, 2))
     ];
#endif
    return absStorage;
}

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Negate(const CXInt32x3 storage)
{
    CXInt32x3 negStorage;
#if __has_extension(attribute_ext_vector_type)
    negStorage.extStorage = -(storage.extStorage);
#else
    negStorage.array = (CXInt32x3)[
        -CXInt32x3GetElement(storage, 0),
        -CXInt32x3GetElement(storage, 1),
        -CXInt32x3GetElement(storage, 2)
    ];
#endif
    return negStorage;
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Add(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    CXInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = lhs.extStorage + rhs.extStorage;
#else
    storage.array = (CXInt32x3)[
         CXInt32x3GetElement(lhs, 0) + CXInt32x3GetElement(rhs, 0),
         CXInt32x3GetElement(lhs, 1) + CXInt32x3GetElement(rhs, 1),
         CXInt32x3GetElement(lhs, 2) + CXInt32x3GetElement(rhs, 2)
     ];
#endif
    return storage;
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Subtract(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    CXInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = lhs.extStorage - rhs.extStorage;
#else
    storage.array = (CXInt32x3)[
         CXInt32x3GetElement(lhs, 0) - CXInt32x3GetElement(rhs, 0),
         CXInt32x3GetElement(lhs, 1) - CXInt32x3GetElement(rhs, 1),
         CXInt32x3GetElement(lhs, 2) - CXInt32x3GetElement(rhs, 2)
     ];
#endif
    return storage;
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Multiply(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    CXInt32x3 storage;
#if __has_extension(attribute_ext_vector_type)
    storage.extStorage = lhs.extStorage * rhs.extStorage;
#else
    storage.array = (CXInt32x3)[
         CXInt32x3GetElement(lhs, 0) * CXInt32x3GetElement(rhs, 0),
         CXInt32x3GetElement(lhs, 1) * CXInt32x3GetElement(rhs, 1),
         CXInt32x3GetElement(lhs, 2) * CXInt32x3GetElement(rhs, 2)
     ];
#endif
    return storage;
}
