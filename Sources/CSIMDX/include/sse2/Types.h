#pragma once

#include <emmintrin.h>
#include "../Common.h"

// MARK: 128 bit floating point

// The first Float32 is stored in the lowest (least significant) 32 bits, and so on.
typedef __m128 CXFloat32x2; // Most significant 2 x 32 bits are unused (zero)

// The first Float32 is stored in the lowest (least significant) 32 bits, and so on.
typedef __m128 CXFloat32x3; // Most significant 32 bits are unused (zero)

// The first Float32 is stored in the lowest (least significant) 32 bits, and so on.
typedef __m128 CXFloat32x4;

// The first Float64 is stored in the lowest (least significant) 64 bits, and so on.
typedef __m128d CXFloat64x2;

// MARK: 128 bit integer

// The first Int32 is stored in the lowest (least significant) 32 bits, and so on.
typedef __m128i CXInt32x2; // Most significant 2 x 32 bits are unused (zero)

// The first Int32 is stored in the lowest (least significant) 32 bits, and so on.
typedef __m128i CXInt32x3; // Most significant 32 bits are unused (zero)

// The first Int32 is stored in the lowest (least significant) 32 bits, and so on.
typedef __m128i CXInt32x4;

// The first Int64 is stored in the lowest (least significant) 64 bits, and so on.
typedef __m128i CXInt64x2;
