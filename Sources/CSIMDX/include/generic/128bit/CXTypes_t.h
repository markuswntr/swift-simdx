#pragma once

#include <stdint.h>
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

/// Use built-in vectors when available
#if __has_extension(attribute_ext_vector_type)

/// The 2 x 32-bit floating point storage type
typedef Float32 CXFloat32x2 __attribute__((ext_vector_type(2)));

/// The 3 x 32-bit floating point storage type
typedef Float32 CXFloat32x3 __attribute__((ext_vector_type(3)));

/// The 4 x 32-bit floating point storage type
typedef Float32 CXFloat32x4 __attribute__((ext_vector_type(4)));

/// The 2 x 64-bit floating point storage type
typedef Float64 CXFloat64x2 __attribute__((ext_vector_type(2)));

/// The 2 x 32-bit signed integer storage type
typedef Int32 CXInt32x2 __attribute__((ext_vector_type(2)));

/// The 3 x 32-bit signed integer storage type
typedef Int32 CXInt32x3 __attribute__((ext_vector_type(3)));

/// The 4 x 32-bit signed integer storage type
typedef Int32 CXInt32x4 __attribute__((ext_vector_type(4)));

/// The 2 x 64-bit signed integer storage type
typedef Int64 CXInt64x2 __attribute__((ext_vector_type(2)));

/// The 2 x 32-bit unsigned integer storage type
typedef UInt32 CXUInt32x2 __attribute__((ext_vector_type(2)));

/// The 3 x 32-bit unsigned integer storage type
typedef UInt32 CXUInt32x3 __attribute__((ext_vector_type(3)));

/// The 4 x 32-bit unsigned integer storage type
typedef UInt32 CXUInt32x4 __attribute__((ext_vector_type(4)));

/// The 2 x 64-bit unsigned integer storage type
typedef UInt64 CXUInt64x2 __attribute__((ext_vector_type(2)));

#else

/// The 2 x 32-bit floating point storage type
typedef struct CXFloat32x2_t { Float32 elements[2]; } CXFloat32x2;

/// The 3 x 32-bit floating point storage type
typedef struct CXFloat32x3_t { Float32 elements[3]; } CXFloat32x3;

/// The 4 x 32-bit floating point storage type
typedef struct CXFloat32x4_t { Float32 elements[4]; } CXFloat32x4;

/// The 2 x 64-bit floating point storage type
typedef struct CXFloat64x2_t { Float64 elements[2]; } CXFloat64x2;

/// The 2 x 32-bit signed integer storage type
typedef struct CXInt32x2_t { Int32 elements[2]; } CXInt32x2;

/// The 3 x 32-bit signed integer storage type
typedef struct CXInt32x3_t { Int32 elements[3]; } CXInt32x3;

/// The 4 x 32-bit signed integer storage type
typedef struct CXInt32x4_t { Int32 elements[4]; } CXInt32x4;

/// The 2 x 64-bit signed integer storage type
typedef struct CXInt64x2_t { Int64 elements[2]; } CXInt64x2;

/// The 2 x 32-bit unsigned integer storage type
typedef struct CXUInt32x2_t { UInt32 elements[2]; } CXUInt32x2;

/// The 3 x 32-bit unsigned integer storage type
typedef struct CXUInt32x3_t { UInt32 elements[3]; } CXUInt32x3;

/// The 4 x 32-bit unsigned integer storage type
typedef struct CXUInt32x4_t { UInt32 elements[4]; } CXUInt32x4;

/// The 2 x 64-bit unsigned integer storage type
typedef struct CXUInt64x2_t { UInt64 elements[2]; } CXUInt64x2;

#endif
