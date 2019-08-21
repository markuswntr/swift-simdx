#pragma once

// ==============================================================================
// Defines for supported Numeric c-types, to make them fit their Swift equivalent
// and to have their bit-width in the type name - it is an attempt to make things
// clearer when working with 128/256/... built-in intrinsics.
// ==============================================================================

/// The 32-bit integer scalar type
#define Int32 int
/// The 64-bit integer scalar type
#define Int64 long
/// The 32-bit unsigned integer scalar type
#define UInt32 unsigned int
/// The 64-bit unsigned integer scalar type
#define UInt64 unsigned long
/// The 32-bit floating scalar type
#define Float32 float
/// The 64-bit floating scalar type
#define Float64 double

// ==============================================================================
// References: https://clang.llvm.org/doxygen/immintrin_8h_source.html
// ==============================================================================

/// The default function attributes for intrinsic wrapping functions
#define DEFAULT_FUNCTION_ATTRIBUTES  __attribute__((__always_inline__, __nodebug__))

/// Function pre-fix to make it static and to try force inlining it by the compiler. Takes the return value as input.
#define STATIC_INLINE_INTRINSIC(returnType) static __inline__ returnType DEFAULT_FUNCTION_ATTRIBUTES

/// Reference: https://github.com/llvm-mirror/clang/blob/b165125115794a302175c79b63a1c964323cf6fb/test/Preprocessor/feature_tests.c
// !__has_builtin(__builtin_shufflevector) || \
// !__has_builtin(__builtin_convertvector) || \




