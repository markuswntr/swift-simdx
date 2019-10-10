// Copyright 2019 Markus Winter
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#if defined(CX_NEON_128)
#include <arm_neon.h>
#elif defined(CX_X86_128)
#include <emmintrin.h>
#endif

// MARK: Numeric Types

/// The 32-bit floating point type
#define Float32 float
/// The 64-bit floating point type
#define Float64 double

// MARK: Linear Storages

/// The 2 x 32-bit floating point storage
#if defined(CX_NEON_128)
typedef float32x2_t __attribute((aligned(16))) CXFloat32x2;
#elif defined(CX_X86_128)
typedef __m128 CXFloat32x2; // Most significant 64 bits are unused (zero)
#elif defined(CX_EXT_VECTOR)
typedef Float32 CXFloat32x2 __attribute__((ext_vector_type(2)));
#else
typedef struct CXFloat32x2_t { Float32 val[2]; } CXFloat32x2;
#endif

/// The 3 x 32-bit floating point storage
#if defined(CX_NEON_128)
typedef float32x4_t __attribute((aligned(16))) CXFloat32x3; // Most significant 32 bits are unused (zero)
#elif defined(CX_X86_128)
typedef __m128 CXFloat32x3; // Most significant 32 bits are unused (zero)
#elif defined(CX_EXT_VECTOR)
typedef Float32 CXFloat32x3 __attribute__((ext_vector_type(3)));
#else
typedef struct CXFloat32x3_t { Float32 val[3]; } CXFloat32x3;
#endif

/// The 4 x 32-bit floating point storage
#if defined(CX_NEON_128)
typedef float32x4_t __attribute((aligned(16))) CXFloat32x4;
#elif defined(CX_X86_128)
typedef __m128 CXFloat32x4;
#elif defined(CX_EXT_VECTOR)
typedef Float32 CXFloat32x4 __attribute__((ext_vector_type(4)));
#else
typedef struct CXFloat32x4_t { Float32 val[4]; } CXFloat32x4;
#endif

/// The 2 x 64-bit floating point storage
#if defined(CX_NEON_128_WITH_AARCH64) // NOTE: float64x2_t requires aarch64
typedef float64x2_t __attribute((aligned(16))) CXFloat64x2;
#elif defined(CX_X86_128)
typedef __m128d CXFloat64x2;
#elif defined(CX_EXT_VECTOR)
typedef Float64 CXFloat64x2 __attribute__((ext_vector_type(2)));
#else
typedef struct CXFloat64x2_t { Float64 val[2]; } CXFloat64x2;
#endif
