#pragma once
/// Reference: https://clang.llvm.org/docs/LanguageExtensions.html#langext-vectors

#include <stdint.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 32-bit signed integer type
#define Int64 int64_t

// MARK: - Vector Storage

/// Use built-in vectors when available
#if __has_extension(attribute_ext_vector_type)
typedef Int64 ExtIntStorage64x2 __attribute__((ext_vector_type(2)));
typedef Int64 ExtIntStorage64x3 __attribute__((ext_vector_type(3)));
typedef Int64 ExtIntStorage64x4 __attribute__((ext_vector_type(4)));
#endif

/// The 2 x 64-bit Inting point storage type
typedef union CXInt64x2 {
    Int64 elements[2]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtIntStorage64x2 internalElements;
#endif
} CXInt64x2;

/// The 3 x 64-bit Inting point storage
typedef union CXInt64x3 {
    Int64 elements[3]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtIntStorage64x3 internalElements;
#endif
} CXInt64x3;

/// The 4 x 64-bit Inting point storage
typedef union CXInt64x4 {
    Int64 elements[4]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtIntStorage64x4 internalElements;
#endif
} CXInt64x4;


