#pragma once

// == References ================================================================================
//  - https://clang.llvm.org/doxygen/emmintrin_8h_source.html
//  - https://software.intel.com/sites/landingpage/IntrinsicsGuide/#text=_m128&techs=SSE2
//  - https://thinkingandcomputing.com/posts/using-avx-instructions-in-matrix-multiplication.html
// ==============================================================================================

/// The default function attributes for intrinsic wrapping functions
#define DEFAULT_FUNCTION_ATTRIBUTES  __attribute__((__always_inline__, __nodebug__, __min_vector_width__(128)))

/// Function pre-fix to make it static and to try force inlining it by the compiler. Takes the return value as input.
#define STATIC_INLINE_INTRINSIC(returnType) static __inline__ returnType DEFAULT_FUNCTION_ATTRIBUTES
