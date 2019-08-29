#pragma once
/// Reference: https://developer.arm.com/architectures/instruction-sets/simd-isas/neon/intrinsics?search=float32

#include <stdint.h>
#include <arm_neon.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 32-bit floating point type
#define Float32 float

// MARK: - Vector Storage

/// The 2 x 32-bit floating point storage
typedef float32x2_t __attribute((aligned(16))) CXFloat32x2;

/// The 3 x 32-bit floating point storage
typedef float32x4_t __attribute((aligned(16))) CXFloat32x3; // Most significant 32 bits are unused (zero)

/// The 4 x 32-bit floating point storage
typedef float32x4_t __attribute((aligned(16))) CXFloat32x4;

// MARK: - Matrix Storage

/// The 4 x 4 x 32-bit floating point storage
typedef float32x4x4_t __attribute((aligned(16))) CXFloat32x4x4;

/// The 3 x 3 x 32-bit floating point storage
typedef float32x4x3_t __attribute((aligned(16))) CXFloat32x3x3; // Last coloumn is unused (zeros)

/// The 2 x 2 x 32-bit floating point storage
typedef float32x2x2_t __attribute((aligned(16))) CXFloat32x2x2;

