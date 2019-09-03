#pragma once

#include <stdint.h>
#include <arm_neon.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 64-bit unsigned integer type
#define UInt64 uint64_t

// MARK: - Vector Storage

/// The 2 x 64-bit unsigned integer storage
typedef uint64x2_t __attribute((aligned(16))) CXUInt64x2;

///// The 3 x 64-bit unsigned integer storage
//typedef struct CXInt64x3 { CXInt64x2 val[2]; } CXInt64x3; // Most significant 32 bits are unused (zero)
//
///// The 4 x 64-bit unsigned integer storage
//typedef struct CXInt64x4 { CXInt64x2 val[2]; } CXInt64x4;

// MARK: - Matrix Storage

/// The 2 x 2 x 64-bit unsigned integer storage
typedef uint64x2x2_t __attribute((aligned(16))) CXUInt64x2x2;

///// The 3 x 3 x 64-bit unsigned integer storage
//typedef struct CXInt64x3x3 { CXInt64x4 val[3]; } CXInt64x3x3; // Last coloumn is unused (zeros)
//
///// The 4 x 4 x 64-bit unsigned integer storage
//typedef struct CXInt64x4x4 { CXInt64x4 val[4]; } CXInt64x4x4;
