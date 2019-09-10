#pragma once

#include "CXTypes_t.h"
#include "CXInt32x4.h"

/// Returns an intrinsic initialized to the 3 given values, from least- to most-significant bits.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Make(Int32 value0, Int32 value1, Int32 value2)
{
    return CXInt32x4Make(value0, value1, value2, 0);
}

/// Loads 3 x Int32 values from unaligned memory.
/// @param pointer Unaligned memory pointer to 3 x Int32 values
/// @return CXInt32x3(pointer[0], pointer[1], pointer[2])
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeLoad(const Int32* pointer)
{
    CXInt32x3 storage = CXInt32x4MakeLoad(pointer);
    vsetq_lane_s32(0, storage, 3);
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to `value`.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeRepeatingElement(const Int32 value)
{
    CXInt32x3 storage = CXInt32x4MakeRepeatingElement(value);
    vsetq_lane_s32(0, storage, 3);
    return storage;
}

/// Returns an intrinsic type with all lanes initialized to zero (0.f).
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3MakeZero(void)
{
    return CXInt32x3MakeRepeatingElement(0);
}

// MARK: - Getter/Setter

/// Returns the element at `index` of `storage` (`storage[index]`).
/// @param storage The storage to read values from
/// @param index The index of the value to return
STATIC_INLINE_INTRINSIC(Int32) CXInt32x3GetElement(const CXInt32x3 storage, const int index)
{
    return CXInt32x4GetElement(storage, index);
}

/// Sets the element at `index` from `storage` to given value.
/// @param storage The storage to look up values
/// @param index The index of the value to change.
/// @param value The value to set at storage[index].
STATIC_INLINE_INTRINSIC(void) CXInt32x3SetElement(CXInt32x3* storage, const int index, const Int32 value)
{
    CXInt32x4SetElement(storage, index, value);
}

// MARK: - Arithmetics

/// Returns the negated value (element-wise).
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Negate(const CXInt32x3 storage)
{
    return CXInt32x4Negate(storage);
}

/// Returns the absolute value (element-wise).
STATIC_INLINE_INTRINSIC(CXUInt32x3) CXInt32x3Absolute(const CXInt32x3 storage)
{
    return CXInt32x4Absolute(storage);
}

// MARK: Additive

/// Adds two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Add(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return CXInt32x4Add(lhs, rhs);
}

/// Subtracts a storage from another (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Subtract(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return CXInt32x4Subtract(lhs, rhs);
}

// MARK: Multiplicative

/// Multiplies two storages (element-wise) and returns the result.
/// @param lhs Left-hand side operator
/// @param rhs Right-hand side operator
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3Multiply(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return CXInt32x4Multiply(lhs, rhs);
}

// MARK: - Bitwise

/// Bitwise Not
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3BitwiseNot(const CXInt32x3 operand)
{
    CXInt32x4 storage = CXInt32x4BitwiseNot(operand);
    vsetq_lane_s32(0, storage, 3);
    return storage;
}

/// Bitwise And
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3BitwiseAnd(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return CXInt32x4BitwiseAnd(lhs, rhs);
}

/// Bitwise And Not
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3BitwiseAndNot(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return CXInt32x3BitwiseAndNot(CXInt32x3BitwiseNot(lhs), rhs);
}

/// Bitwise Or
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3BitwiseOr(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return CXInt32x4BitwiseOr(lhs, rhs);
}

/// Bitwise Exclusive Or
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3BitwiseExclusiveOr(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return CXInt32x4BitwiseExclusiveOr(lhs, rhs);
}

// MARK: Shifting

/// Left-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3ShiftElementWiseLeft(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return CXInt32x4ShiftElementWiseLeft(lhs, rhs);
}

/// Left-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3ShiftLeft(const CXInt32x3 lhs, const Int32 rhs)
{
    return CXInt32x4ShiftLeft(lhs, rhs);
}

/// Right-shifts each element in the storage operand by the specified number of bits in each lane of rhs.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3ShiftElementWiseRight(const CXInt32x3 lhs, const CXInt32x3 rhs)
{
    return CXInt32x4ShiftElementWiseRight(lhs, rhs);
}

/// Right-shifts each element in the storage operand by the specified number of bits.
STATIC_INLINE_INTRINSIC(CXInt32x3) CXInt32x3ShiftRight(const CXInt32x3 lhs, const Int32 rhs)
{
    return CXInt32x4ShiftRight(lhs, rhs);
}
