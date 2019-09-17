// Copyright 2019 Markus Winter
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

/// The default function attributes for intrinsic wrapping functions
#define DEFAULT_FUNCTION_ATTRIBUTES  __attribute__((__always_inline__, __nodebug__))

/// Function pre-fix to make it static and to try force inlining it by the compiler. Takes the return value as input.
#define STATIC_INLINE_INTRINSIC(returnType) static __inline__ returnType DEFAULT_FUNCTION_ATTRIBUTES
