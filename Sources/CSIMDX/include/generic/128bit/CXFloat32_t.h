#pragma once
/// Reference: https://clang.llvm.org/docs/LanguageExtensions.html#langext-vectors

#include <stdint.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 32-bit floating point type
#define Float32 float

// MARK: - Vector Storage

/// Use built-in vectors when available
#if __has_extension(attribute_ext_vector_type)
typedef Float32 CEXStorageFloat32x2 __attribute__((ext_vector_type(2)));
typedef Float32 CEXStorageFloat32x3 __attribute__((ext_vector_type(3)));
typedef Float32 CEXStorageFloat32x4 __attribute__((ext_vector_type(4)));
#endif

/// The 2 x 32-bit floating point storage type
typedef union CXFloat32x2 {
    Float32 elements[2]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageFloat32x2 internalElements;
#endif
} CXFloat32x2;

/// The 3 x 32-bit floating point storage
typedef union CXFloat32x3 {
    Float32 elements[3]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageFloat32x3 internalElements;
#endif
} CXFloat32x3;

/// The 4 x 32-bit floating point storage
typedef union CXFloat32x4 {
    Float32 elements[4]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageFloat32x4 internalElements;
#endif
} CXFloat32x4;
