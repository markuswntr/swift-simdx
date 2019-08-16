//#pragma once
//
//#include <immintrin.h>
//#include "Common.h"
//
//// MARK: - Int32x4 register type -
//
///// 128bit integer intrinsic. The first Int32 is stored in the lowest 32 bits, and so on.
//typedef __m128i CXInt32x4;
//
//// MARK: Designated Initializers
//
///// Returns an 128bit intrinsic type initialized to the 4 given Int32 values.
///// @param value0 1st integer component
///// @param value1 2nd integer component
///// @param value2 3rd integer component
///// @param value3 4th integer component
//static __attribute__((always_inline))
//CXInt32x4 CXInt32x4Make(Int32 value0, Int32 value1, Int32 value2, Int32 value3)
//{
//	return _mm_setr_epi32(value0, value1, value2, value3);
//}
//
//struct Test {
//    
//};
//
//#pragma once
//
//#include "Common.h"
//#include <immintrin.h>
//
//// MARK: - Float32x4 register type -
//
///// 128bit floating point intrinsic. The first Float32 is stored in the lowest 32 bits, and so on.
//typedef __m128 CXFloat32x4;
//
//// MARK: Designated Initializers
//
///// Returns an 128bit intrinsic type initialized to the 4 given Float32 values.
///// @param value0 1st Float32 value
///// @param value1 2nd Float32 value
///// @param value2 3rd Float32 value
///// @param value3 4th Float32 value
//static __inline__ CXFloat32x4 __attribute__((__always_inline__))
//CXFloat32x4Make(const Float32 value0, const Float32 value1, const Float32 value2, const Float32 value3)
//{
//    return _mm_setr_ps(value0, value1, value2, value3);
//}
//
///// Loads 4 floating point values from unaligned memory.
///// @param pointer Unaligned memory pointer to 4 floating point values
///// @return CXFloat32x4(pointer[0], pointer[1], pointer[2], pointer[3])
//static __attribute__((always_inline))
//CXFloat32x4 CXFloat32x4Load(const float* pointer)
//{
//    return _mm_loadu_ps(pointer);
//}
//
///// Returns an 128bit intrinsic type initialized all 4 Float32 values to given value.
///// @param value0 1st float component
///// @param value1 2nd float component
///// @param value2 3rd float component
///// @param value3 4th float component
//static __attribute__((always_inline))
//CXFloat32x4 CXFloat32x4MakeRepeatingElement(const Float32 value)
//{
//    return CXFloat32x4Make(value, value, value, value);
//}
//
///// Returns an register type with all values initialized to zero (0.f).
//static __attribute__((always_inline))
//CXFloat32x4 CXFloat32x4MakeZero(void)
//{
//    return _mm_setzero_ps();
//}
//
///// Returns an register type with all values initialized to one (1.f).
//static __attribute__((always_inline))
//CXFloat32x4 CXFloat32x4MakeOne(void)
//{
//    return CXFloat32x4MakeRepeatingElement(1.f);
//}
//
//// MARK: Getter/Setter
//
///// Returns the element at `index` from the `float32x4` collection.
///// @param float32x4 The element collection to look up values
///// @param index The index of the value to return.
//static __attribute__((always_inline))
//Float32 CXFloat32x4GetElement(const CXFloat32x4 float32x4, const Int32 index)
//{
//    return (((Float32*)&(float32x4))[index]);
//}
//
///// Sets the element at `index` from `collection`.
///// @param collection The collection to look up values
///// @param index The index of the value to return.
//static __attribute__((always_inline))
//void CXFloat32x4SetElement(const CXFloat32x4* float32x4, const Int32 index, const Float32 value)
//{
//    ((Float32*)float32x4)[index] = value;
//}
//
//// MARK: Additive Arithmetics
//
///// Adds two float32x4 (element-wise) and returns the result.
///// @param lhs Left-hand side operator
///// @param rhs Right-hand side operator
//static __attribute__((always_inline))
//CXFloat32x4 CXFloat32x4Add(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
//{
//    return _mm_add_ps(lhs, rhs);
//}
//
///// Subtracts a float32x4 from another (element-wise) and returns the result.
///// @param lhs Left-hand side operator
///// @param rhs Right-hand side operator
//static __attribute__((always_inline))
//CXFloat32x4 CXFloat32x4Subtract(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
//{
//    return _mm_sub_ps(lhs, rhs);
//}
//
///// Returns the negated value (element-wise).
///// @param float32x4 Source collection
//static __attribute__((always_inline))
//CXFloat32x4 CXFloat32x4Negate(const CXFloat32x4 float32x4)
//{
//    return CXFloat32x4Subtract(CXFloat32x4MakeZero(), float32x4);
//}
//
//// MARK: Multiplicative Arithmetics
//
///// Multiplies two float32x4 (element-wise) and returns the result.
///// @param lhs Left-hand side operator
///// @param rhs Right-hand side operator
//static __attribute__((always_inline))
//CXFloat32x4 CXFloat32x4Multiply(const CXFloat32x4 lhs, const CXFloat32x4 rhs)
//{
//    return _mm_mul_ps(lhs, rhs);
//}
//
