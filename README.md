# SIMDX

_SIMDX_ provides a unified implementation for built-in vector and matrix intrinsics, such as **SSE/AVX on x86** and **NEON on ARM**, 
in C (see `CSIMDX` target) and exposes them to Swift as generic types (see `SIMDX` target) . Furthermore, _SIMDX_ provides a fast
and  portable implementations of SIMD intrinsics on **hardware which doesn't natively support** them, making _SIMDX_ independent
of the target hardware. Therefore it allows vector and matrix calculations on any (Swift supporting) hardware and automatically
routes([<sup>1</sup>](#1)) those through the fastest available instructions.

> **Note:** This is far from finished, and not guarantueed to perform faster. There have been no performance tests, no benchmarks, no nothing.

**TODO:**
- [ ] Comparison (Equal, Greater/LowerThan, ...)
- [ ] Documentation
- [ ] 256bit (Length) storages
- [ ] Casting different vector types
- [ ] Matrices
- [ ] Properly defining the numeric storages

/// Reference: https://github.com/llvm-mirror/clang/blob/b165125115794a302175c79b63a1c964323cf6fb/test/Preprocessor/feature_tests.c
// !__has_builtin(__builtin_shufflevector) || \
// !__has_builtin(__builtin_convertvector) || \

## References 

I started with almost zero knownledge of SIMD/Intrinsics or builtin clang functions and was DuckDuckGoing (is that a thing?) alot 
prior to started writting this lib. The following references contain some of the most useful instructions I could find across the internet.
I gathered them while writting this library, and I am pretty sure I will need them and re-visit them quite a lot so I leave them here.

### General Knownledge

- https://www.eduonix.com/courses/Software-Development/Learn-the-Basics-of-C-Programming-Language (:D **just kidding** - kind of)
- https://en.wikipedia.org/wiki/SIMD (_**not** kidding_)

### Built-in Vector Support in `clang`

- https://clang.llvm.org/docs/LanguageExtensions.html#langext-vectors
- https://clang.llvm.org/docs/LanguageExtensions.html#vectors-and-extended-vectors
- https://clang.llvm.org/docs/LanguageExtensions.html#builtin-shufflevector
- https://clang.llvm.org/docs/LanguageExtensions.html#langext-builtin-convertvector

### x86 Intrinsics

- https://software.intel.com/sites/landingpage/IntrinsicsGuide/
- https://en.wikipedia.org/wiki/Advanced_Vector_Extensions
- https://clang.llvm.org/doxygen/immintrin_8h.html
- https://clang.llvm.org/doxygen/immintrin_8h_source.html
- http://www.g-truc.net/post-0359.html

### Other Libraries

- https://github.com/QuantStack/xsimd
- https://github.com/nemequ/simde
- https://github.com/vectorclass/version2
- https://github.com/HandmadeMath/Handmade-Math

### NEON Intrinsics

- https://developer.arm.com/architectures/instruction-sets/simd-isas/neon/intrinsics

----
Footnotes: <a class="anchor" id="1">1</a>. It barely "routes" anything. All instructions are marked to be inline whenever possible.






#### Check available intrinsics

`clang -dM -E - < /dev/null | egrep "SSE|AVX" | sort`

Example output:
```
#define __SSE__ 1
#define __SSE2__ 1
#define __SSE2_MATH__ 1
#define __SSE3__ 1
#define __SSSE3__ 1
#define __SSE4_1__ 1
#define __SSE_MATH__ 1
```

> incl. AVX(2)

`clang -mavx2 -dM -E - < /dev/null | egrep "SSE|AVX" | sort`

Example output:
```
#define __AVX2__ 1
#define __AVX__ 1
#define __SSE2_MATH__ 1
#define __SSE2__ 1
#define __SSE3__ 1
#define __SSE4_1__ 1
#define __SSE4_2__ 1
#define __SSE_MATH__ 1
#define __SSE__ 1
#define __SSSE3__ 1
```



Was necessary but is currently unused as defined in the `modulemap`.
Kept for a while until I am pretty sure I will never ever need it again.
```
// MARK: - x86 Intrinsics -

/// This modules starts supporting SIMD instructions starting at AVX (immintrin) supporting processors.
/// This includes Intel processors starting 2008/Sandy Bridge and AMD processors starting 2011/Bulldozer.
///
/// AVX Reference: https://en.wikipedia.org/wiki/Advanced_Vector_Extensions
///
/// Header-File Reference: http://www.g-truc.net/post-0359.html
///
/// +----------------+------------------------------------------------------------------------------------------+
/// |     Header     |                                         Purpose                                          |
/// +----------------+------------------------------------------------------------------------------------------+
/// | x86intrin.h    | Everything, including non-vector x86 instructions like _rdtsc().                         |
/// | mmintrin.h     | MMX (Pentium MMX!)                                                                       |
/// | mm3dnow.h      | 3dnow! (K6-2) (deprecated)                                                               |
/// | xmmintrin.h    | SSE + MMX (Pentium 3, Athlon XP)                                                         |
/// | emmintrin.h    | SSE2 + SSE + MMX (Pentium 4, Athlon 64)                                                  |
/// | pmmintrin.h    | SSE3 + SSE2 + SSE + MMX (Pentium 4 Prescott, Athlon 64 San Diego)                        |
/// | tmmintrin.h    | SSSE3 + SSE3 + SSE2 + SSE + MMX (Core 2, Bulldozer)                                      |
/// | popcntintrin.h | POPCNT (Nehalem (Core i7), Phenom)                                                       |
/// | ammintrin.h    | SSE4A + SSE3 + SSE2 + SSE + MMX (AMD-only, starting with Phenom)                         |
/// | smmintrin.h    | SSE4_1 + SSSE3 + SSE3 + SSE2 + SSE + MMX (Penryn, Bulldozer)                             |
/// | nmmintrin.h    | SSE4_2 + SSE4_1 + SSSE3 + SSE3 + SSE2 + SSE + MMX (Nehalem (aka Core i7), Bulldozer)     |
/// | wmmintrin.h    | AES (Core i7 Westmere, Bulldozer)                                                        |
/// | immintrin.h    | AVX, AVX2, AVX512, all SSE+MMX (except SSE4A and XOP), popcnt, BMI/BMI2, FMA             |
/// +----------------+------------------------------------------------------------------------------------------+
#if __AVX__
#define CX_AVX_INSTRUCTIONS_AVAILABLE 1
#elif __AVX2__
#define CX_AVX_INSTRUCTIONS_AVAILABLE 1
#elif __AVX512__
#define CX_AVX_INSTRUCTIONS_AVAILABLE 1
#elif __AVX512F__
#define CX_AVX_INSTRUCTIONS_AVAILABLE 1
#endif
```
