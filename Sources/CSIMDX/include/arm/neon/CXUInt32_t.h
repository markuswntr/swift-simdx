#pragma once

#include <stdint.h>
#include <arm_neon.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 32-bit unsigned integer type
#define UInt32 uint32_t

// MARK: - Vector Storage

/// The 4 x 32-bit unsigned integer storage
typedef uint32x4_t __attribute((aligned(16))) CXUInt32x4;

/// The 3 x 32-bit unsigned integer storage
typedef uint32x4_t __attribute((aligned(16))) CXUInt32x3; // Most significant 32 bits are unused (zero)

/// The 2 x 32-bit unsigned integer storage
typedef uint32x2_t __attribute((aligned(16))) CXUInt32x2;

// MARK: - Matrix Storage

/// The 4 x 4 x 32-bit unsigned integer storage
typedef uint32x4x4_t __attribute((aligned(16))) CXUInt32x4x4;

/// The 3 x 3 x 32-bit unsigned integer storage
typedef uint32x4x3_t __attribute((aligned(16))) CXUInt32x3x3; // Last coloumn is unused (zeros)

/// The 2 x 2 x 32-bit unsigned integer storage
typedef uint32x2x2_t __attribute((aligned(16))) CXUInt32x2x2;
