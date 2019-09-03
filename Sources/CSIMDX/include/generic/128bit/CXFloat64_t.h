#pragma once
/// Reference: https://clang.llvm.org/docs/LanguageExtensions.html#langext-vectors

#include <stdint.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 64-bit floating point type
#define Float64 double

// MARK: - Vector Storage

/// Use built-in vectors when available
#if __has_extension(attribute_ext_vector_type)
typedef Float64 CEXStorageFloat64x2 __attribute__((ext_vector_type(2)));
typedef Float64 CEXStorageFloat64x3 __attribute__((ext_vector_type(3)));
typedef Float64 CEXStorageFloat64x4 __attribute__((ext_vector_type(4)));
#endif

/// The 2 x 64-bit floating point storage type
typedef union CXFloat64x2 {
    Float64 elements[2]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageFloat64x2 internalElements;
#endif
} CXFloat64x2;

/// The 3 x 64-bit floating point storage
typedef union CXFloat64x3 {
    Float64 elements[3]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageFloat64x3 internalElements;
#endif
} CXFloat64x3;

/// The 4 x 64-bit floating point storage
typedef union CXFloat64x4 {
    Float64 elements[4]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageFloat64x4 internalElements;
#endif
} CXFloat64x4;


