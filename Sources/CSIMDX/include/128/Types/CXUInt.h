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

#include <stdint.h>
#if defined(CX_NEON_128)
#include <arm_neon.h>
#elif defined(CX_X86_128)
#include <emmintrin.h>
#else
#include <stdlib.h>
#endif

// MARK: Numeric Types

/// The 32-bit unsigned integer type
#define UInt32 uint32_t
/// The 64-bit unsigned integer type
#define UInt64 uint64_t

// MARK: Linear Storages

/// The 2 x 32-bit unsigned integer storage
#if defined(CX_NEON_128)
typedef uint32x2_t __attribute((aligned(16))) CXUInt32x2;
#elif defined(CX_X86_128)
typedef __m128i CXUInt32x2; // Most significant 2 x 32 bits are unused (zero)
#elif defined(CX_EXT_VECTOR)
typedef UInt32 CXUInt32x2 __attribute__((ext_vector_type(2)));
#else
typedef struct CXUInt32x2_t { UInt32 val[2]; } CXUInt32x2;
#endif

/// The 3 x 32-bit unsigned integer storage
#if defined(CX_NEON_128)
typedef uint32x4_t __attribute((aligned(16))) CXUInt32x3; // Most significant 32 bits are unused (zero)
#elif defined(CX_X86_128)
typedef __m128i CXUInt32x3; // Most significant 32 bits are unused (zero)
#elif defined(CX_EXT_VECTOR)
typedef UInt32 CXUInt32x3 __attribute__((ext_vector_type(3)));
#else
typedef struct CXUInt32x3_t { UInt32 val[3]; } CXUInt32x3;
#endif

/// The 4 x 32-bit unsigned integer storage
#if defined(CX_NEON_128)
typedef uint32x4_t __attribute((aligned(16))) CXUInt32x4;
#elif defined(CX_X86_128)
typedef __m128i CXUInt32x4;
#elif defined(CX_EXT_VECTOR)
typedef UInt32 CXUInt32x4 __attribute__((ext_vector_type(4)));
#else
typedef struct CXUInt32x4_t { UInt32 val[4]; } CXUInt32x4;
#endif

/// The 2 x 64-bit unsigned integer storage
#if defined(CX_NEON_128)
typedef uint64x2_t __attribute((aligned(16))) CXUInt64x2;
#elif defined(CX_X86_128)
typedef __m128i CXUInt64x2;
#elif defined(CX_EXT_VECTOR)
typedef UInt64 CXUInt64x2 __attribute__((ext_vector_type(2)));
#else
typedef struct CXUInt64x2_t { UInt64 val[2]; } CXUInt64x2;
#endif
