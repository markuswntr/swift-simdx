#pragma once
/// Reference: https://developer.arm.com/architectures/instruction-sets/simd-isas/neon/intrinsics?search=float64

#include <stdint.h>
#include <arm_neon.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 64-bit floating point type
#define Float64 double

// MARK: - Vector Storage

/// The 2 x 64-bit floating point storage
typedef float64x2_t __attribute((aligned(16))) CXFloat64x2;

///// The 3 x 64-bit floating point storage
//typedef struct CXFloat64x3 { CXFloat64x2 val[2]; } CXFloat64x3; // Most significant 32 bits are unused (zero)
//
///// The 4 x 64-bit floating point storage
//typedef struct CXFloat64x4 { CXFloat64x2 val[2]; } CXFloat64x4;

// MARK: - Matrix Storage

/// The 2 x 2 x 64-bit floating point storage
typedef float64x2x2_t __attribute((aligned(16))) CXFloat64x2x2;

///// The 3 x 3 x 64-bit floating point storage
//typedef struct CXFloat64x3x3 { CXFloat64x4 val[3]; } CXFloat64x3x3; // Last coloumn is unused (zeros)
//
///// The 4 x 4 x 64-bit floating point storage
//typedef struct CXFloat64x4x4 { CXFloat64x4 val[4]; } CXFloat64x4x4;
