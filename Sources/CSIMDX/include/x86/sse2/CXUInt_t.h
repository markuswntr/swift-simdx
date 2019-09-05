#pragma once

#include <stdint.h>
#include <emmintrin.h>

// MARK: - Unsigned Integer

/// The 32-bit unsigned integer type
#define UInt32 uint32_t

/// The 64-bit unsigned integer type
#define UInt64 uint64_t

// MARK: Linear Storage

/// The 2 x 32-bit unsigned integer storage
typedef __m128i CXUInt32x2; // Most significant 2 x 32 bits are unused (zero)

/// The 3 x 32-bit unsigned integer storage
typedef __m128i CXUInt32x3; // Most significant 32 bits are unused (zero)

/// The 4 x 32-bit unsigned integer storage
typedef __m128i CXUInt32x4;

/// The 2 x 64-bit unsigned integer storage
typedef __m128i CXUInt64x2;

///// The 3 x 64-bit unsigned integer storage
//typedef struct CXUInt64x3 { CXUInt64x2 val[2]; } CXUInt64x3; // Most significant 32 bits are unused (zero)
//
///// The 4 x 64-bit unsigned integer storage
//typedef struct CXUInt64x4 { CXUInt64x2 val[2]; } CXUInt64x4;

// MARK: Matrix Storage

///// The 2 x 2 x 32-bit floating point storage
//typedef __m128i CXUInt32x2x2;
//
///// The 4 x 4 x 32-bit floating point storage
//typedef int32x4x4_t __attribute((aligned(16))) CXUInt32x4x4;
//
///// The 3 x 3 x 32-bit floating point storage
//typedef int32x4x3_t __attribute((aligned(16))) CXUInt32x3x3; // Last coloumn is unused (zeros)

/// The 2 x 2 x 64-bit unsigned integer storage
//typedef struct CXUInt64x2x2 { CXUInt64x2 val[2]; } CXUInt64x2x2;

///// The 3 x 3 x 64-bit unsigned integer storage
//typedef struct CXUInt64x3x3 { CXUInt64x4 val[3]; } CXUInt64x3x3; // Last coloumn is unused (zeros)
//
///// The 4 x 4 x 64-bit unsigned integer storage
//typedef struct CXUInt64x4x4 { CXUInt64x4 val[4]; } CXUInt64x4x4;
