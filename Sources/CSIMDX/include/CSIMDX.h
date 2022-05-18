// Copyright 2022 Markus Winter
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

// == References ===============================================================================
//  - https://developer.arm.com/architectures/instruction-sets/simd-isas/neon/intrinsics
//  - http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0472k/chr1359125040547.html
//  - https://developer.arm.com/architectures/instruction-sets/intrinsics
//  - https://www.keil.com/support/man/docs/armclang_intro/armclang_intro_wap1490203634804.htm
// =============================================================================================
// #define CSIMDX_ARM_NEON
// #define CSIMDX_ARM_NEON_AARCH64

// == References ================================================================================
//  - https://clang.llvm.org/doxygen/emmintrin_8h_source.html
//  - https://software.intel.com/sites/landingpage/IntrinsicsGuide/#text=_m128&techs=SSE2
//  - https://thinkingandcomputing.com/posts/using-avx-instructions-in-matrix-multiplication.html
// ==============================================================================================
// #define CSIMDX_X86_SSE2
// #define CSIMDX_X86_AVX

/// Find the relevant instruction set
#ifdef __ARM_NEON
  #define CSIMDX_ARM_NEON 1
  #include <arm_neon.h>
  #ifdef __aarch64__
    /// Use the extend set of aarch64 if available
    #define CSIMDX_ARM_NEON_AARCH64 1
  #endif
  #ifdef __ARM_FEATURE_SVE
  #define CSIMDX_ARM_SVE 1
    #include <arm_sve.h>
  #endif
#elif __SSE2__
  #define CSIMDX_X86_SSE2 1
  #include <emmintrin.h>
  #ifdef __AVX__
    #define CSIMDX_X86_AVX 1
    #include <immintrin.h>
  #endif
#endif

/// Tries force inlining the function. Takes the return value as input.
#define FORCE_INLINE(returnType) static __inline__ __attribute__((always_inline)) returnType

#include "CFloat/CFloat.h"

#undef CSIMDX_ARM_NEON
#undef CSIMDX_ARM_NEON_AARCH64
#undef CSIMDX_ARM_SVE
#undef CSIMDX_X86_SSE2
#undef CSIMDX_X86_AVX
