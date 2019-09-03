#pragma once
/// Reference: https://clang.llvm.org/docs/LanguageExtensions.html#langext-vectors

#include <stdint.h>
#include "Attributes.h"

// MARK: - Scalar

/// The 64-bit unsigned integer type
#define UInt64 uint64_t

// MARK: - Vector Storage

/// Use built-in vectors when available
#if __has_extension(attribute_ext_vector_type)
typedef UInt64 CEXStorageUInt64x2 __attribute__((ext_vector_type(2)));
typedef UInt64 CEXStorageUInt64x3 __attribute__((ext_vector_type(3)));
typedef UInt64 CEXStorageUInt64x4 __attribute__((ext_vector_type(4)));
#endif

/// The 2 x 64-bit unsigned integer storage type
typedef union CXUInt64x2 {
    UInt64 elements[2]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageUInt64x2 internalElements;
#endif
} CXUInt64x2;

/// The 3 x 64-bit unsigned integer storage
typedef union CXUInt64x3 {
    UInt64 elements[3]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageUInt64x3 internalElements;
#endif
} CXUInt64x3;

/// The 4 x 64-bit unsigned integer storage
typedef union CXUInt64x4 {
    UInt64 elements[4]; // Read-only if extended vector support
#if __has_extension(attribute_ext_vector_type)
    CEXStorageUInt64x4 internalElements;
#endif
} CXUInt64x4;


