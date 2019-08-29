#pragma once
/// Reference: https://clang.llvm.org/docs/LanguageExtensions.html#langext-vectors

#include "Attributes.h"

// MARK: - Scalar

/// The 64-bit floating point type
#define Float64 double

// MARK: - Vector Storage

/// Use built-in vectors when available
#if __has_extension(attribute_ext_vector_type)
typedef Float64 ExtFloatStorage64x2 __attribute__((ext_vector_type(2)));
typedef Float64 ExtFloatStorage64x3 __attribute__((ext_vector_type(3)));
typedef Float64 ExtFloatStorage64x4 __attribute__((ext_vector_type(4)));
#endif

/// The 2 x 64-bit floating point storage type
typedef union CXFloat64x2 {
    Float64 array[2]; // Read-only of extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtFloatStorage64x2 extStorage;
#endif
} CXFloat64x2;

/// The 3 x 64-bit floating point storage
typedef union CXFloat64x3 {
    Float64 array[3]; // Read-only of extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtFloatStorage64x3 extStorage;
#endif
} CXFloat64x3;

/// The 4 x 64-bit floating point storage
typedef union CXFloat64x4 {
    Float64 array[4]; // Read-only of extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtFloatStorage64x4 extStorage;
#endif
} CXFloat64x4;


