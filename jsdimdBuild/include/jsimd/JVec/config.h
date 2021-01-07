#pragma once

#ifndef JVEC_FORCED
    #if defined(__SSE__) || (_M_IX86_FP > 0) || (_M_X64 > 0)

        #define JVEC_SSE

    // __ARM_NEON is used instead of __ARM_NEON__ on armv8.
    #elif defined(__ARM_NEON__) || defined(__ARM_NEON)

        #define JVEC_NEON

    // Don't use gnu extension for arm, buggy with some gccs with armv6 and -Os,
    // Also doesn't seem perform as well
    #elif defined(__GNUC__) && !defined(__arm__)

        #define JVEC_GNU

    #else

        #define JVEC_SCALAR

    #endif
#endif



#ifdef JVEC_SCALAR
    #define JVEC_SIMD_TYPE "scalar"
#endif

#ifdef JVEC_SSE
    #define JVEC_SIMD_TYPE "sse"
#endif

#ifdef JVEC_NEON
    #define JVEC_SIMD_TYPE "neon"
    #define JVEC_HAVE_SIMD2F
#endif

#ifdef JVEC_GNU
    #define JVEC_SIMD_TYPE "gnu"
#endif



#if defined(JVEC_FORCED) && !defined(JVEC_SIMD_TYPE)
    #error JVEC_FORCED set but no simd-type found, try f.ex. JVEC_SCALAR
#endif


#define JVec_inline    static inline

#if defined(__GNUC__) 
  #if defined(__cplusplus)
    #define JVec_restrict  __restrict
  #endif
  #define simd4f_aligned16  __attribute__ ((aligned (16)))
#elif defined(_WIN32)
  #define JVec_restrict  
  #define simd4f_aligned16   __declspec(align(16))
#else
  #define JVec_restrict  restrict
  #define simd4f_aligned16   
#endif
// #define JVec_restrict

#ifdef __GNUC__
    #define JVec_pure __attribute__((pure))
#else
    #define JVec_pure
#endif

#ifdef _WIN32
  #if defined(min) || defined(max)
#pragma message ( "set NOMINMAX as preprocessor macro, undefining min/max " )
#undef min
#undef max
  #endif
#endif

#ifdef __cplusplus
    // Hack around msvc badness
    #define SIMD_PARAM(t, p) const t& p
#else
    #define SIMD_PARAM(t, p) t p
#endif
                    
#define JVEC_PI      3.14159265f
#define JVEC_HALFPI  1.57079633f


