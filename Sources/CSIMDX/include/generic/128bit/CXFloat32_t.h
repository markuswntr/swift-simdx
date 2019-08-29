#pragma once
/// Reference: https://clang.llvm.org/docs/LanguageExtensions.html#langext-vectors

#include "Attributes.h"

// MARK: - Scalar

/// The 32-bit floating point type
#define Float32 float

// MARK: - Vector Storage

/// Use built-in vectors when available
#if __has_extension(attribute_ext_vector_type)
typedef Float32 ExtFloatStorage32x2 __attribute__((ext_vector_type(2)));
typedef Float32 ExtFloatStorage32x3 __attribute__((ext_vector_type(3)));
typedef Float32 ExtFloatStorage32x4 __attribute__((ext_vector_type(4)));
#endif

/// The 2 x 32-bit floating point storage type
typedef union CXFloat32x2 {
    Float32 array[2]; // Read-only of extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtFloatStorage32x2 extStorage;
#endif
} CXFloat32x2;

/// The 3 x 32-bit floating point storage
typedef union CXFloat32x3 {
    Float32 array[3]; // Read-only of extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtFloatStorage32x3 extStorage;
#endif
} CXFloat32x3;

/// The 4 x 32-bit floating point storage
typedef union CXFloat32x4 {
    Float32 array[4]; // Read-only of extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtFloatStorage32x4 extStorage;
#endif
} CXFloat32x4;
