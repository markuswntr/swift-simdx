#pragma once
/// Reference: https://clang.llvm.org/docs/LanguageExtensions.html#langext-vectors

#include <stdint.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 32-bit signed integer type
#define Int32 int32_t

// MARK: - Vector Storage

/// Use built-in vectors when available
#if __has_extension(attribute_ext_vector_type)
typedef Int32 ExtIntStorage32x2 __attribute__((ext_vector_type(2)));
typedef Int32 ExtIntStorage32x3 __attribute__((ext_vector_type(3)));
typedef Int32 ExtIntStorage32x4 __attribute__((ext_vector_type(4)));
#endif

/// The 2 x 32-bit floating point storage type
typedef union CXInt32x2 {
    Int32 array[2]; // Read-only of extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtIntStorage32x2 extStorage;
#endif
} CXInt32x2;

/// The 3 x 32-bit floating point storage
typedef union CXInt32x3 {
    Int32 array[3]; // Read-only of extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtIntStorage32x3 extStorage;
#endif
} CXInt32x3;

/// The 4 x 32-bit floating point storage
typedef union CXInt32x4 {
    Int32 array[4]; // Read-only of extended vector support
#if __has_extension(attribute_ext_vector_type)
    ExtIntStorage32x4 extStorage;
#endif
} CXInt32x4;
