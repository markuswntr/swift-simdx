#pragma once
/// Reference: https://clang.llvm.org/docs/LanguageExtensions.html#langext-vectors

#include <stdint.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 32-bit unsigned integer type
#define UInt32 uint32_t

// MARK: - Vector Storage

/// Use built-in vectors when available
#if __has_extension(attribute_ext_vector_type)
typedef UInt32 CEXStorageUInt32x2 __attribute__((ext_vector_type(2)));
typedef UInt32 CEXStorageUInt32x3 __attribute__((ext_vector_type(3)));
typedef UInt32 CEXStorageUInt32x4 __attribute__((ext_vector_type(4)));
#endif

/// The 2 x 32-bit unsigned integer storage type
typedef union CXUInt32x2 {
    UInt32 elements[2]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageUInt32x2 internalElements;
#endif
} CXUInt32x2;

/// The 3 x 32-bit unsigned integer storage
typedef union CXUInt32x3 {
    UInt32 elements[3]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageUInt32x3 internalElements;
#endif
} CXUInt32x3;

/// The 4 x 32-bit unsigned integer storage
typedef union CXUInt32x4 {
    UInt32 elements[4]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageUInt32x4 internalElements;
#endif
} CXUInt32x4;
