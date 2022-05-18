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

#include "CFloat32x2.h"
#include "CFloat32x3.h"
#include "CFloat32x4.h"
#include "CFloat64x2.h"
#include "CFloat64x3.h"
#include "CFloat64x4.h"

#pragma mark - CFloat32x2 <-> CFloat64x2

/// Converts the double-precision floating-point elements of given `operand`
/// into single-precision floating-point values and returns them as the elements
/// of a new CFloat32x2 instance.
/// @returns `(CFloat32x2){ (float)(operand[0]), (float)(operand[1]) }`
FORCE_INLINE(CFloat32x2) CFloat32x2FromCFloat64x2(CFloat64x2 operand)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vcvt_f32_f64(operand);
#elif CSIMDX_X86_SSE2
  return _mm_cvtpd_ps(operand);
#else
  return CFloat32x2Make((double)CFloat64x2GetElement(operand, 0),
                        (double)CFloat64x2GetElement(operand, 1));
#endif
}

/// Converts the single-precision floating-point elements of given `operand`
/// into double-precision floating-point values and returns them as the elements
/// of a new CFloat64x2 instance.
/// @returns `(CFloat64x2){ (double)(operand[0]), (double)(operand[1]) }`
FORCE_INLINE(CFloat64x2) CFloat64x2FromCFloat32x2(CFloat32x2 operand)
{
#if CSIMDX_ARM_NEON_AARCH64
  return vcvt_f64_f32(operand);
#elif CSIMDX_X86_SSE2
  return _mm_cvtps_pd(operand);
#else
  return CFloat64x2Make((double)CFloat32x2GetElement(operand, 0),
                        (double)CFloat32x2GetElement(operand, 1));
#endif
}
