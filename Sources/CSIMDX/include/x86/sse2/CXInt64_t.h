#pragma once

#include <stdint.h>
#include <emmintrin.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 32-bit signed integer type
#define Int64 int64_t

// MARK: - Vector Storage

/// The 2 x 64-bit floating point storage
typedef __m128i CXInt64x2;

///// The 3 x 64-bit floating point storage
//typedef struct CXInt64x3 { CXInt64x2 val[2]; } CXInt64x3; // Most significant 32 bits are unused (zero)
//
///// The 4 x 64-bit floating point storage
//typedef struct CXInt64x4 { CXInt64x2 val[2]; } CXInt64x4;

// MARK: - Matrix Storage

/// The 2 x 2 x 64-bit floating point storage
//typedef struct CXInt64x2x2 { CXInt64x2 val[2]; } CXInt64x2x2;

///// The 3 x 3 x 64-bit floating point storage
//typedef struct CXInt64x3x3 { CXInt64x4 val[3]; } CXInt64x3x3; // Last coloumn is unused (zeros)
//
///// The 4 x 4 x 64-bit floating point storage
//typedef struct CXInt64x4x4 { CXInt64x4 val[4]; } CXInt64x4x4;
