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

#include <stdint.h>

#if CSIMDX_ARM_NEON
#include <arm_neon.h>
#elif CSIMDX_X86_SSE2
#include <emmintrin.h>
#endif

/// The 32-bit floating point type
#define Float32 float
/// The 64-bit floating point type
#define Float64 double

/// The 32-bit signed integer type
#define Int32 int32_t
/// The 64-bit signed integer type
#define Int64 int64_t

/// The 32-bit unsigned integer type
#define UInt32 uint32_t
/// The 64-bit unsigned integer type
#define UInt64 uint64_t


/// The 4 x 32-bit signed integer storage
#if CX_NEON_128
typedef int32x4_t __attribute((aligned(16))) CXInt32x4;
#elif CX_X86_128
typedef __m128i CXInt32x4;
#elif CX_EXT_VECTOR
typedef Int32 CXInt32x4 __attribute__((ext_vector_type(4)));
#else
typedef struct CXInt32x4_t { Int32 val[4]; } CXInt32x4;
#endif

/// The 2 x 64-bit signed integer storage
#if CX_NEON_128
typedef int64x2_t __attribute((aligned(16))) CXInt64x2;
#elif CX_X86_128
typedef __m128i CXInt64x2;
#elif CX_EXT_VECTOR
typedef Int64 CXInt64x2 __attribute__((ext_vector_type(2)));
#else
typedef struct CXInt64x2_t { Int64 val[2]; } CXInt64x2;
#endif








/// The 2 x 64-bit unsigned integer storage
#if CX_NEON_128
typedef uint64x2_t __attribute((aligned(16))) CXUInt64x2;
#elif CX_X86_128
typedef __m128i CXUInt64x2;
#elif CX_EXT_VECTOR
typedef UInt64 CXUInt64x2 __attribute__((ext_vector_type(2)));
#else
typedef struct CXUInt64x2_t { UInt64 val[2]; } CXUInt64x2;
#endif

#pragma mark - Conversion

///// Convert the elements of `operand`, load them in the new storage and return the result.
///// @returns `(CFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
//FORCE_INLINE(CFloat32x2) CFloat32x2FromCXInt32x2(CXInt32x2 operand)
//{
//  CFloat32x2 result;
//#if CSIMDX_ARM_NEON
//  result.rawValue = vcvt_f32_s32(operand.rawValue);
//#elif CSIMDX_X86_SSE2
//  result.rawValue = _mm_cvtepi32_ps(operand.rawValue);
//#endif
//  return result;
//}
//
///// Convert the elements of `operand`, load them in the new storage and return the result.
///// @returns `(CFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
//FORCE_INLINE(CFloat32x2) CFloat32x2FromCXUInt32x2(CXUInt32x2 operand)
//{
//#if CSIMDX_ARM_NEON
//  CFloat32x2 result;
//  result.rawValue = vcvt_f32_u32(operand.rawValue);
//  return result;
//#elif CSIMDX_X86_SSE2
//  return CFloat32x2FromCXInt32x2(operand.rawValue);
//#endif
//}
//
///// Convert the elements of `operand`, load them in the new storage and return the result.
///// @returns `(CFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
//FORCE_INLINE(CFloat32x2) CFloat32x2FromCXInt64x2(CXInt64x2 operand)
//{
//#if CSIMDX_ARM_NEON
//  #if CSIMDX_ARM_NEON_AARCH64
//    return CFloat32x2FromCXFloat64x2(vreinterpretq_f64_s64(operand.rawValue));
//  #else
//    return CFloat32x2Make((float)(operand.rawValue[0]), (float)(operand.rawValue[1]));
//  #endif
//#elif CSIMDX_X86_SSE2
//  //  Only works for inputs in the range: [-2^51, 2^51]
//  /// https://stackoverflow.com/questions/41144668/how-to-efficiently-perform-double-int64-conversions-with-sse-avx
//  CXInt64x2 temp = _mm_add_epi64(operand.rawValue, _mm_castpd_si128(_mm_set1_pd(0x0018000000000000)));
//  CXFloat64x2 converted = _mm_sub_pd(_mm_castsi128_pd(temp), _mm_set1_pd(0x0018000000000000));
//  return CFloat32x2FromCXFloat64x2(converted);
//#endif
//}
//
///// Convert the elements of `operand`, load them in the new storage and return the result.
///// @returns `(CFloat32x2){ (Float32)(operand[0]), (Float32)(operand[1]) }`
//FORCE_INLINE(CFloat32x2) CFloat32x2FromCXUInt64x2(CXUInt64x2 operand)
//{
//#if CSIMDX_ARM_NEON
//  #if CSIMDX_ARM_NEON_AARCH64
//    return CFloat32x2FromCXFloat64x2(vreinterpretq_f64_u64(operand.rawValue));
//  #else
//    return CFloat32x2Make((Float32)(operand.rawValue[0]), (Float32)(operand.rawValue[1]));
//  #endif
//#elif CSIMDX_X86_SSE2
//  return CFloat32x2FromCXInt64x2(operand.rawValue);
//#endif
//}

#pragma mark - Conversion

///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CFloat32x3){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]) }`
//FORCE_INLINE(CFloat32x3) CFloat32x3FromCXInt32x3(CXInt32x3 operand)
//{
//  CFloat32x3 result;
//#if CSIMDX_ARM_NEON
//    result.rawValue = vcvtq_f32_s32(operand);
//#elif CSIMDX_X86_SSE2
//    result.rawValue = _mm_cvtepi32_ps(operand);
//#endif
//  return result;
//}
//
///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CFloat32x3){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]) }`
//FORCE_INLINE(CFloat32x3) CFloat32x3FromCXUInt32x3(CXUInt32x3 operand)
//{
//  CFloat32x3 result;
//#if CSIMDX_ARM_NEON
//  result.rawValue = vcvtq_f32_u32(operand);
//#elif CSIMDX_X86_SSE2
//  result.rawValue = _mm_cvtepi32_ps(operand);
//#endif
//  return result;
//}

#pragma mark - Conversion

///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CFloat32x4){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]), ... }`
//FORCE_INLINE(CFloat32x4) CFloat32x4FromCXInt32x4(CXInt32x4 operand)
//{
//  CFloat32x4 result;
//#if CSIMDX_ARM_NEON
//return vcvtq_f32_s32(operand);
//#elif CSIMDX_X86_SSE2
//return _mm_cvtepi32_ps(operand);
//#endif
//  return result;
//}
//
///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CFloat32x4){ (Float32)(operand[0]), (Float32)(operand[1]), (Float32)(operand[2]), ... }`
//FORCE_INLINE(CFloat32x4) CFloat32x4FromCXUInt32x4(CXUInt32x4 operand)
//{
//  CFloat32x4 result;
//#if CSIMDX_ARM_NEON
//return vcvtq_f32_u32(operand);
//#elif CSIMDX_X86_SSE2
//return _mm_cvtepi32_ps(operand);
//#endif
//  return result;
//}

#pragma mark - Conversion

///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CFloat64x2){ (Float64)(operand[0]), (Float64)(operand[1]) }`
//FORCE_INLINE(CFloat64x2) CFloat64x2FromCXInt32x2(CInt32x2 operand)
//{
//#if CSIMDX_ARM_NEON_AARCH64
//    return CFloat64x2FromCFloat32x2(vreinterpret_f32_s32(operand));
//#elif CSIMDX_X86_SSE2
//    return _mm_cvtepi32_pd(operand);
//#elif CX_EXT_VECTOR
//    return __builtin_convertvector(operand, CFloat64x2);
//#else
//    return CFloat64x2Make( (Float64)(operand.val[0]), (Float64)(operand.val[1]) );
//#endif
//}
//
///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CFloat64x2){ (Float64)(operand[0]), (Float64)(operand[1]) }`
//FORCE_INLINE(CFloat64x2) CFloat64x2FromCXUInt32x2(CXUInt32x2 operand)
//{
//#if CSIMDX_ARM_NEON_AARCH64
//    return CFloat64x2FromCFloat32x2(vreinterpret_f32_u32(operand));
//#elif CSIMDX_X86_SSE2
//    return _mm_cvtepi32_pd(operand);
//#elif CX_EXT_VECTOR
//    return __builtin_convertvector(operand, CFloat64x2);
//#else
//    return CFloat64x2Make( (Float64)(operand.val[0]), (Float64)(operand.val[1]) );
//#endif
//}
//
///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CFloat64x2){ (Float64)(operand[0]), (Float64)(operand[1]) }`
//FORCE_INLINE(CFloat64x2) CFloat64x2FromCXInt64x2(CXInt64x2 operand)
//{
//#if CSIMDX_ARM_NEON_AARCH64
//    return vcvtq_f64_s64(operand);
//#elif CSIMDX_X86_SSE2
////    return _mm_castsi128_pd(operand);
//    return __builtin_convertvector(operand, CFloat64x2);
//#elif CX_EXT_VECTOR
//    return __builtin_convertvector(operand, CFloat64x2);
//#else
//    return CFloat64x2Make( (Float64)(operand.val[0]), (Float64)(operand.val[1]) );
//#endif
//}
//
///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CFloat64x2){ (Float64)(operand[0]), (Float64)(operand[1]) }`
//FORCE_INLINE(CFloat64x2) CFloat64x2FromCXUInt64x2(CXUInt64x2 operand)
//{
//#if CSIMDX_ARM_NEON_AARCH64
//    return vcvtq_f64_u64(operand);
//#elif CSIMDX_X86_SSE2
////    return _mm_castsi128_pd(operand);
//    return __builtin_convertvector(operand, CFloat64x2);
//#elif CX_EXT_VECTOR
//    return __builtin_convertvector(operand, CFloat64x2);
//#else
//    return CFloat64x2Make( (Float64)(operand.val[0]), (Float64)(operand.val[1]) );
//#endif
//}

#pragma mark - Conversion

///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CInt32x2){ (Int32)(operand[0]), (Int32)(operand[1]) }`
//FORCE_INLINE(CInt32x2) CInt32x2FromCFloat32x2(CFloat32x2 operand)
//{
//#if CX_NEON_128
//    return vcvt_s32_f32(operand);
//#elif CX_X86_128
//    return _mm_cvtps_epi32(operand);
//#elif CX_EXT_VECTOR
//    return CInt32x2Make( (Int32)nearbyintf(operand[0]), (Int32)nearbyintf(operand[1]) );
//#else
//    return CInt32x2Make( (Int32)nearbyintf(operand.val[0]), (Int32)nearbyintf(operand.val[1]) );
//#endif
//}
//
///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CInt32x2){ (Int32)(operand[0]), (Int32)(operand[1]) }`
//FORCE_INLINE(CInt32x2) CInt32x2FromCXUInt32x2(CXUInt32x2 operand)
//{
//#if CX_NEON_128
//    return vreinterpret_s32_u32(operand);
//#elif CX_X86_128
//    return operand;
//#elif CX_EXT_VECTOR
//    return __builtin_convertvector(operand, CInt32x2);
//#else
//    return CInt32x2Make( (Int32)(operand.val[0]), (Int32)(operand.val[1]) );
//#endif
//}
//
///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CInt32x2){ (Int32)(operand[0]), (Int32)(operand[1]) }`
//FORCE_INLINE(CInt32x2) CInt32x2FromCXFloat64x2(CXFloat64x2 operand)
//{
//#if CX_NEON_128_WITH_AARCH64
//    return vcvt_s32_f32(vcvt_f32_f64(operand));
//#elif CX_X86_128
//    return _mm_cvtpd_epi32(operand);
//#elif CX_EXT_VECTOR
//    return CInt32x2Make( (Int32)nearbyint(operand[0]), (Int32)nearbyint(operand[1]) );
//#else
//    return CInt32x2Make( (Int32)nearbyint(operand.val[0]), (Int32)nearbyint(operand.val[1]) );
//#endif
//}
//
///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CInt32x2){ (Int32)(operand[0]), (Int32)(operand[1]) }`
//FORCE_INLINE(CInt32x2) CInt32x2FromCXInt64x2(CXInt64x2 operand)
//{
//#if CX_NEON_128
//    return vmovn_s64(operand);
//#elif CX_X86_128
//    // There is no int64 to int32 conversion, so we are going int64 - (hacky way) -> float64 -> int32
//    // This is so stupid... Maybe move to an unpack solution later on.
//    //  Only works for inputs in the range: [-2^51, 2^51]
//    /// https://stackoverflow.com/questions/41144668/how-to-efficiently-perform-double-int64-conversions-with-sse-avx
//    CXInt64x2 temp = _mm_add_epi64(operand, _mm_castpd_si128(_mm_set1_pd(0x0018000000000000)));
//    CXFloat64x2 converted = _mm_sub_pd(_mm_castsi128_pd(temp), _mm_set1_pd(0x0018000000000000));
//    return CInt32x2FromCXFloat64x2(converted);
//#elif CX_EXT_VECTOR
//    return __builtin_convertvector(operand, CInt32x2);
//#else
//    return CInt32x2Make( (Int32)(operand.val[0]), (Int32)(operand.val[1]) );
//#endif
//}
//
///// Converts the elements of `operand`, load them in the new storage and returns the result.
///// @returns `(CInt32x2){ (Int32)(operand[0]), (Int32)(operand[1]) }`
//FORCE_INLINE(CInt32x2) CInt32x2FromCXUInt64x2(CXUInt64x2 operand)
//{
//#if CX_NEON_128
//    return vreinterpret_s32_u32(vmovn_u64(operand));
//#elif CX_X86_128
//    // There is no int64 to int32 conversion, so we are going uint64 - (hacky way) -> float64 -> int32
//    // This is so stupid... Maybe move to an unpack solution later on.
//    //  Only works for inputs in the range: [-2^51, 2^51]
//    /// https://stackoverflow.com/questions/41144668/how-to-efficiently-perform-double-int64-conversions-with-sse-avx
//    CXInt64x2 temp = _mm_or_si128(operand, _mm_castpd_si128(_mm_set1_pd(0x0010000000000000)));
//    CXFloat64x2 converted = _mm_sub_pd(_mm_castsi128_pd(temp), _mm_set1_pd(0x0010000000000000));
//    return CInt32x2FromCXFloat64x2(converted);
//#elif CX_EXT_VECTOR
//    return __builtin_convertvector(operand, CInt32x2);
//#else
//    return CInt32x2Make( (Int32)(operand.val[0]), (Int32)(operand.val[1]) );
//#endif
//}
