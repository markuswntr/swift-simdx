#pragma once

// ==============================================================================
// References: https://clang.llvm.org/doxygen/immintrin_8h_source.html
// ==============================================================================

/// The default function attributes for intrinsic wrapping functions
#define DEFAULT_FUNCTION_ATTRIBUTES  __attribute__((__always_inline__, __nodebug__))

/// Function pre-fix to make it static and to try force inlining it by the compiler. Takes the return value as input.
#define STATIC_INLINE_INTRINSIC(returnType) static __inline__ returnType DEFAULT_FUNCTION_ATTRIBUTES
