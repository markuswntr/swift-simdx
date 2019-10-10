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
#endif

// MARK: Numeric Types

/// The 32-bit signed integer type
#define Int32 int32_t
/// The 64-bit signed integer type
#define Int64 int64_t

// MARK: Linear Storages

/// The 2 x 32-bit signed integer storage
#if defined(CX_NEON_128)
typedef int32x2_t __attribute((aligned(16))) CXInt32x2;
#elif defined(CX_X86_128)
typedef __m128i CXInt32x2; // Most significant 2 x 32 bits are unused (zero)
#elif defined(CX_EXT_VECTOR)
typedef Int32 CXInt32x2 __attribute__((ext_vector_type(2)));
#else
typedef struct CXInt32x2_t { Int32 val[2]; } CXInt32x2;
#endif

/// The 3 x 32-bit signed integer storage
#if defined(CX_NEON_128)
typedef int32x4_t __attribute((aligned(16))) CXInt32x3; // Most significant 32 bits are unused (zero)
#elif defined(CX_X86_128)
typedef __m128i CXInt32x3; // Most significant 32 bits are unused (zero)
#elif defined(CX_EXT_VECTOR)
typedef Int32 CXInt32x3 __attribute__((ext_vector_type(3)));
#else
typedef struct CXInt32x3_t { Int32 val[3]; } CXInt32x3;
#endif

/// The 4 x 32-bit signed integer storage
#if defined(CX_NEON_128)
typedef int32x4_t __attribute((aligned(16))) CXInt32x4;
#elif defined(CX_X86_128)
typedef __m128i CXInt32x4;
#elif defined(CX_EXT_VECTOR)
typedef Int32 CXInt32x4 __attribute__((ext_vector_type(4)));
#else
typedef struct CXInt32x4_t { Int32 val[4]; } CXInt32x4;
#endif

/// The 2 x 64-bit signed integer storage
#if defined(CX_NEON_128)
typedef int64x2_t __attribute((aligned(16))) CXInt64x2;
#elif defined(CX_X86_128)
typedef __m128i CXInt64x2;
#elif defined(CX_EXT_VECTOR)
typedef Int64 CXInt64x2 __attribute__((ext_vector_type(2)));
#else
typedef struct CXInt64x2_t { Int64 val[2]; } CXInt64x2;
#endif
