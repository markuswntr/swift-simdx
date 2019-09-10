#pragma once

#include <stdint.h>
#include <arm_neon.h>
#include "Attributes.h"

// MARK: - Numeric Types

/// The 32-bit floating point type
#define Float32 float

/// The 64-bit floating point type
#define Float64 double

/// The 32-bit signed integer type
#define Int32 int32_t

/// The 64-bit signed integer type
#define Int64 int64_t

/// The 32-bit unsigned integer type
#define UInt32 uint32_t

/// The 64-bit unsigned integer type
#define UInt64 uint64_t

// MARK: - Linear Storages

/// The 2 x 32-bit floating point storage
typedef float32x2_t __attribute((aligned(16))) CXFloat32x2;

/// The 3 x 32-bit floating point storage
typedef float32x4_t __attribute((aligned(16))) CXFloat32x3; // Most significant 32 bits are unused (zero)

/// The 4 x 32-bit floating point storage
typedef float32x4_t __attribute((aligned(16))) CXFloat32x4;

/// The 2 x 64-bit floating point storage
typedef float64x2_t __attribute((aligned(16))) CXFloat64x2;

/// The 2 x 32-bit signed integer storage
typedef int32x2_t __attribute((aligned(16))) CXInt32x2;

/// The 3 x 32-bit signed integer storage
typedef int32x4_t __attribute((aligned(16))) CXInt32x3; // Most significant 32 bits are unused (zero)

/// The 4 x 32-bit signed integer storage
typedef int32x4_t __attribute((aligned(16))) CXInt32x4;

/// The 2 x 64-bit signed integer storage
typedef int64x2_t __attribute((aligned(16))) CXInt64x2;

/// The 2 x 32-bit unsigned integer storage
typedef uint32x2_t __attribute((aligned(16))) CXUInt32x2;

/// The 3 x 32-bit unsigned integer storage
typedef uint32x4_t __attribute((aligned(16))) CXUInt32x3; // Most significant 32 bits are unused (zero)

/// The 4 x 32-bit unsigned integer storage
typedef uint32x4_t __attribute((aligned(16))) CXUInt32x4;

/// The 2 x 64-bit unsigned integer storage
typedef uint64x2_t __attribute((aligned(16))) CXUInt64x2;
