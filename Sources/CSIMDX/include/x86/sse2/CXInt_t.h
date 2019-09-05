#pragma once

#include <stdint.h>
#include <emmintrin.h>

// MARK: - Signed Integer

/// The 32-bit signed integer type
#define Int32 int32_t

/// The 64-bit signed integer type
#define Int64 int64_t

// MARK: Linear Storages

/// The 2 x 32-bit signed integer storage
typedef __m128i CXInt32x2; // Most significant 2 x 32 bits are unused (zero)

/// The 3 x 32-bit signed integer storage
typedef __m128i CXInt32x3; // Most significant 32 bits are unused (zero)

/// The 4 x 32-bit signed integer storage
typedef __m128i CXInt32x4;

/// The 2 x 64-bit signed integer storage
typedef __m128i CXInt64x2;

///// The 3 x 64-bit signed integer storage
//typedef struct CXInt64x3 { CXInt64x2 val[2]; } CXInt64x3; // Most significant 32 bits are unused (zero)
//
///// The 4 x 64-bit signed integer storage
//typedef struct CXInt64x4 { CXInt64x2 val[2]; } CXInt64x4;

// MARK: Matrix Storages

///// The 2 x 2 x 32-bit floating point storage
//typedef __m128i CXInt32x2x2;
//
///// The 4 x 4 x 32-bit floating point storage
//typedef int32x4x4_t __attribute((aligned(16))) CXInt32x4x4;
//
///// The 3 x 3 x 32-bit floating point storage
//typedef int32x4x3_t __attribute((aligned(16))) CXInt32x3x3; // Last coloumn is unused (zeros)
//
/// The 2 x 2 x 64-bit signed integer storage
//typedef struct CXInt64x2x2 { CXInt64x2 val[2]; } CXInt64x2x2;
//
///// The 3 x 3 x 64-bit signed integer storage
//typedef struct CXInt64x3x3 { CXInt64x4 val[3]; } CXInt64x3x3; // Last coloumn is unused (zeros)
//
///// The 4 x 4 x 64-bit signed integer storage
//typedef struct CXInt64x4x4 { CXInt64x4 val[4]; } CXInt64x4x4;
