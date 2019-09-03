#pragma once

#include <stdint.h>
#include <emmintrin.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 32-bit unsigned integer type
#define UInt64 uint64_t

// MARK: - Vector Storage

/// The 2 x 64-bit unsigned integer storage
typedef __m128i CXUInt64x2;

///// The 3 x 64-bit unsigned integer storage
//typedef struct CXUInt64x3 { CXUInt64x2 val[2]; } CXUInt64x3; // Most significant 32 bits are unused (zero)
//
///// The 4 x 64-bit unsigned integer storage
//typedef struct CXUInt64x4 { CXUInt64x2 val[2]; } CXUInt64x4;

// MARK: - Matrix Storage

/// The 2 x 2 x 64-bit unsigned integer storage
//typedef struct CXUInt64x2x2 { CXUInt64x2 val[2]; } CXUInt64x2x2;

///// The 3 x 3 x 64-bit unsigned integer storage
//typedef struct CXUInt64x3x3 { CXUInt64x4 val[3]; } CXUInt64x3x3; // Last coloumn is unused (zeros)
//
///// The 4 x 4 x 64-bit unsigned integer storage
//typedef struct CXUInt64x4x4 { CXUInt64x4 val[4]; } CXUInt64x4x4;
