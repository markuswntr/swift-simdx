#pragma once
/// Reference: https://software.intel.com/sites/landingpage/IntrinsicsGuide/#text=_m128&techs=SSE2

#include <emmintrin.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 32-bit floating point type
#define Float32 float

// MARK: - Vector Storage

/// The 2 x 32-bit floating point storage
typedef __m128 CXFloat32x2; // Most significant 64 bits are unused (zero)

/// The 3 x 32-bit floating point storage
typedef __m128 CXFloat32x3; // Most significant 32 bits are unused (zero)

/// The 4 x 32-bit floating point storage
typedef __m128 CXFloat32x4;

// MARK: - Matrix Storage
/// https://thinkingandcomputing.com/posts/using-avx-instructions-in-matrix-multiplication.html

/// The 2 x 2 x 32-bit floating point storage
//typedef __m128 __attribute((aligned(32))) CXFloat32x2x2;

///// The 3 x 3 x 64-bit floating point storage
//typedef struct CXFloat32x3x3 { CXFloat32x4 val[3]; } CXFloat32x3x3; // Last coloumn is unused (zeros)
//
///// The 4 x 4 x 64-bit floating point storage
//typedef struct CXFloat32x4x4 { CXFloat32x4 val[4]; } CXFloat32x4x4;

