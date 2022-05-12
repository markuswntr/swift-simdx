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
// =============================================================================================
// #define CSIMDX_ARM_NEON
// #define CSIMDX_ARM_NEON_AARCH64

// == References ================================================================================
//  - https://clang.llvm.org/doxygen/emmintrin_8h_source.html
//  - https://software.intel.com/sites/landingpage/IntrinsicsGuide/#text=_m128&techs=SSE2
//  - https://thinkingandcomputing.com/posts/using-avx-instructions-in-matrix-multiplication.html
// ==============================================================================================
// #define CSIMDX_X86_SSE2

/// Find the relevant instruction set
#ifdef __ARM_NEON
  #define CSIMDX_ARM_NEON 1
  #include <arm_neon.h>
  /// Additionally, use the extend set of aarch64 if available
  #ifdef __aarch64__
    #define CSIMDX_ARM_NEON_AARCH64 1
  #endif
#elif __SSE2__
  #define CSIMDX_X86_SSE2 1
  #include <emmintrin.h>
#elif
  #error Unsupported Architecture
#endif

#if CSIMDX_ARM_NEON
  #define DEFAULT_FN_ATTRS __attribute__((__always_inline__, __nodebug__))
#elif CSIMDX_X86_SSE2
  #define DEFAULT_FN_ATTRS __attribute__((__always_inline__, __nodebug__, __min_vector_width__(128)))
#endif

/// Tries to force inline the function. Takes the return value as input.
#define FORCE_INLINE(returnType) static __inline__ returnType DEFAULT_FN_ATTRS

/// Include the 64 bit instructions
#include "128/CFloat32x2.h" // Actually 64 bit, but 128 bit is the minimum
//#include "CXInt32x2.h"  // Actually 64 bit, but 128 bit is the minimum
//#include "CXUInt32x2.h" // Actually 64 bit, but 128 bit is the minimum

/// Include the 128 bit instructions
#include "128/CFloat32x3.h" // The most significant 32 bits are not used
//#include "CXInt32x3.h"  // The most significant 32 bits are not used
//#include "CXUInt32x3.h" // The most significant 32 bits are not used

#include "128/CFloat32x4.h"
//#include "CXInt32x4.h"
//#include "CXUInt32x4.h"
//
//#include "CXFloat64x2.h"
//#include "CXInt64x2.h"
//#include "CXUInt64x2.h"
//
//
