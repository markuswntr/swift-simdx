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
#include <emmintrin.h>
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
typedef __m128 CXFloat32x2; // Most significant 64 bits are unused (zero)

/// The 3 x 32-bit floating point storage
typedef __m128 CXFloat32x3; // Most significant 32 bits are unused (zero)

/// The 4 x 32-bit floating point storage
typedef __m128 CXFloat32x4;

/// The 2 x 64-bit floating point storage
typedef __m128d CXFloat64x2;

/// The 2 x 32-bit signed integer storage
typedef __m128i CXInt32x2; // Most significant 2 x 32 bits are unused (zero)

/// The 3 x 32-bit signed integer storage
typedef __m128i CXInt32x3; // Most significant 32 bits are unused (zero)

/// The 4 x 32-bit signed integer storage
typedef __m128i CXInt32x4;

/// The 2 x 64-bit signed integer storage
typedef __m128i CXInt64x2;

/// The 2 x 32-bit unsigned integer storage
typedef __m128i CXUInt32x2; // Most significant 2 x 32 bits are unused (zero)

/// The 3 x 32-bit unsigned integer storage
typedef __m128i CXUInt32x3; // Most significant 32 bits are unused (zero)

/// The 4 x 32-bit unsigned integer storage
typedef __m128i CXUInt32x4;

/// The 2 x 64-bit unsigned integer storage
typedef __m128i CXUInt64x2;
