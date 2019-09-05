#pragma once

#include <emmintrin.h>

// MARK: - Floating Point

/// The 32-bit floating point type
#define Float32 float

/// The 64-bit floating point type
#define Float64 double

// MARK: Linear Storages

/// The 2 x 32-bit floating point storage
typedef __m128 CXFloat32x2; // Most significant 64 bits are unused (zero)

/// The 3 x 32-bit floating point storage
typedef __m128 CXFloat32x3; // Most significant 32 bits are unused (zero)

/// The 4 x 32-bit floating point storage
typedef __m128 CXFloat32x4;

/// The 2 x 64-bit floating point storage
typedef __m128d CXFloat64x2;

///// The 3 x 64-bit floating point storage
//typedef struct CXFloat64x3 { CXFloat64x2 val[2]; } CXFloat64x3; // Most significant 32 bits are unused (zero)
//
///// The 4 x 64-bit floating point storage
//typedef struct CXFloat64x4 { CXFloat64x2 val[2]; } CXFloat64x4;

// MARK: Matrix Storages

///// The 2 x 2 x 32-bit floating point storage
//typedef __m128 CXFloat32x2x2;
//
///// The 3 x 3 x 64-bit floating point storage
//typedef struct CXFloat32x3x3 { CXFloat32x4 val[3]; } CXFloat32x3x3; // Last coloumn is unused (zeros)
//
///// The 4 x 4 x 64-bit floating point storage
//typedef struct CXFloat32x4x4 { CXFloat32x4 val[4]; } CXFloat32x4x4;
//
/// The 2 x 2 x 64-bit floating point storage
//typedef struct CXFloat64x2x2 { CXFloat64x2 val[2]; } CXFloat64x2x2;
//
///// The 3 x 3 x 64-bit floating point storage
//typedef struct CXFloat64x3x3 { CXFloat64x4 val[3]; } CXFloat64x3x3; // Last coloumn is unused (zeros)
//
///// The 4 x 4 x 64-bit floating point storage
//typedef struct CXFloat64x4x4 { CXFloat64x4 val[4]; } CXFloat64x4x4;
