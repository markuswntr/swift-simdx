#pragma once

#include <arm_neon.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 32-bit signed integer type
#define Int32 int32_t

// MARK: - Vector Storage

/// The 4 x 32-bit signed integer storage
typedef int32x4_t __attribute((aligned(16))) CXInt32x4;

/// The 3 x 32-bit signed integer storage
typedef int32x4_t __attribute((aligned(16))) CXInt32x3; // Most significant 32 bits are unused (zero)

/// The 2 x 32-bit signed integer storage
typedef int32x2_t __attribute((aligned(16))) CXInt32x2;

// MARK: - Matrix Storage

/// The 4 x 4 x 32-bit floating point storage
typedef int32x4x4_t __attribute((aligned(16))) CXInt32x4x4;

/// The 3 x 3 x 32-bit floating point storage
typedef int32x4x3_t __attribute((aligned(16))) CXInt32x3x3; // Last coloumn is unused (zeros)

/// The 2 x 2 x 32-bit floating point storage
typedef int32x2x2_t __attribute((aligned(16))) CXInt32x2x2;
