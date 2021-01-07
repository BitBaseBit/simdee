#ifndef JSIMD_INSTRUCTION_SET_HPP
#define JSIMD_INSTRUCTION_SET_HPP

#define JSIMD_VERSION_NUMBER(major, minor, patch) \
    ((((major) % 100) * 10000000) + (((minor) % 100) * 100000) + ((patch) % 100000))

#define JSIMD_VERSION_NUMBER_NOT_AVAILABLE \
    JSIMD_VERSION_NUMBER(0, 0, 0)

#define JSIMD_VERSION_NUMBER_AVAILABLE \
    JSIMD_VERSION_NUMBER(0, 0, 1)

/*************************
 * CLEAR INSTRUCTION SET *
 *************************/

#undef JSIMD_X86_INSTR_SET
#undef JSIMD_X86_INSTR_SET_AVAILABLE

#undef JSIMD_X86_AMD_INSTR_SET
#undef JSIMD_X86_AMD_INSTR_SET_AVAILABLE

#undef JSIMD_PPC_INSTR_SET
#undef JSIMD_PPC_INSTR_SET_AVAILABLE

#undef JSIMD_ARM_INSTR_SET
#undef JSIMD_ARM_INSTR_SET_AVAILABLE

/**********************
 * USER CONFIGURATION *
 **********************/

#ifdef JSIMD_FORCE_X86_INSTR_SET
    #define JSIMD_X86_INSTR_SET JSIMD_FORCE_X86_INSTR_SET
    #define JSIMD_X86_INSTR_SET_AVAILABLE JSIMD_VERSION_NUMBER_AVAILABLE
    #ifdef _MSC_VER
        #pragma message("Warning: Forcing X86 instruction set")
    #else
        #warning "Forcing X86 instruction set"
    #endif
#elif defined(JSIMD_FORCE_X86_AMD_INSTR_SET)
    #define JSIMD_X86_AMD_INSTR_SET JSIMD_FORCE_X86_AMD_INSTR_SET
    #define JSIMD_X86_AMD_INSTR_SET_AVAILABLE JSIMD_VERSION_NUMBER_AVAILABLE
    #ifdef _MSC_VER
        #pragma message("Warning: Forcing X86 AMD instruction set")
    #else
        #warning "Forcing X86 AMD instruction set"
    #endif
#elif defined(JSIMD_FORCE_PPC_INSTR_SET)
    #define JSIMD_PPC_INSTR_SET JSIMD_FORCE_PPC_INSTR_SET
    #define JSIMD_PPC_INSTR_SET_AVAILABLE JSIMD_VERSION_NUMBER_AVAILABLE
    #ifdef _MSC_VER
        #pragma message("Warning: Forcing PPC instruction set")
    #else
        #warning "Forcing PPC instruction set"
    #endif
#elif defined(JSIMD_FORCE_ARM_INSTR_SET)
    #define JSIMD_ARM_INSTR_SET JSIMD_FORCE_ARM_INSTR_SET
    #define JSIMD_ARM_INSTR_SET_AVAILABLE JSIMD_VERSION_NUMBER_AVAILABLE
    #ifdef _MSC_VER
        #pragma message("Warning: Forcing ARM instruction set")
    #else
        #warning "Forcing ARM instruction set"
    #endif
#endif

/***********************
 * X86 INSTRUCTION SET *
 ***********************/

#define JSIMD_X86_SSE_VERSION JSIMD_VERSION_NUMBER(1, 0, 0)
#define JSIMD_X86_SSE2_VERSION JSIMD_VERSION_NUMBER(2, 0, 0)
#define JSIMD_X86_SSE3_VERSION JSIMD_VERSION_NUMBER(3, 0, 0)
#define JSIMD_X86_SSSE3_VERSION JSIMD_VERSION_NUMBER(3, 1, 0)
#define JSIMD_X86_SSE4_1_VERSION JSIMD_VERSION_NUMBER(4, 1, 0)
#define JSIMD_X86_SSE4_2_VERSION JSIMD_VERSION_NUMBER(4, 2, 0)
#define JSIMD_X86_AVX_VERSION JSIMD_VERSION_NUMBER(5, 0, 0)
#define JSIMD_X86_FMA3_VERSION JSIMD_VERSION_NUMBER(5, 2, 0)
#define JSIMD_X86_AVX2_VERSION JSIMD_VERSION_NUMBER(5, 3, 0)
#define JSIMD_X86_AVX512_VERSION JSIMD_VERSION_NUMBER(6, 0, 0)
#define JSIMD_X86_MIC_VERSION JSIMD_VERSION_NUMBER(9, 0, 0)

#if !defined(JSIMD_X86_INSTR_SET) && defined(__MIC__)
    #define JSIMD_X86_INSTR_SET JSIMD_X86_MIC_VERSION
#endif

// AVX512 instructions are supported starting with gcc 6
// see https://www.gnu.org/software/gcc/gcc-6/changes.html
#if !defined(JSIMD_X86_INSTR_SET) && (defined(__AVX512__) || defined(__KNCNI__) || defined(__AVX512F__)\
    && (!defined(__GNUC__) || __GNUC__ >= 6))
    #define JSIMD_X86_INSTR_SET JSIMD_X86_AVX512_VERSION

    #if defined(__AVX512VL__)
        #define JSIMD_AVX512VL_AVAILABLE 1
    #endif

    #if defined(__AVX512DQ__)
        #define JSIMD_AVX512DQ_AVAILABLE 1
    #endif

    #if defined(__AVX512BW__)
        #define JSIMD_AVX512BW_AVAILABLE 1
    #endif

    #if __GNUC__ == 6
        #define JSIMD_AVX512_SHIFT_INTRINSICS_IMM_ONLY 1
    #endif
#endif

#if !defined(JSIMD_X86_INSTR_SET) && defined(__AVX2__)
    #define JSIMD_X86_INSTR_SET JSIMD_X86_AVX2_VERSION
#endif

#if !defined(JSIMD_X86_INSTR_SET) && defined(__FMA__)
    #define JSIMD_X86_INSTR_SET JSIMD_X86_FMA3_VERSION
#endif

#if !defined(JSIMD_X86_INSTR_SET) && defined(__AVX__)
    #define JSIMD_X86_INSTR_SET JSIMD_X86_AVX_VERSION
#endif

#if !defined(JSIMD_X86_INSTR_SET) && defined(__SSE4_2__)
    #define JSIMD_X86_INSTR_SET JSIMD_X86_SSE4_2_VERSION
#endif

#if !defined(JSIMD_X86_INSTR_SET) && defined(__SSE4_1__)
    #define JSIMD_X86_INSTR_SET JSIMD_X86_SSE4_1_VERSION
#endif

#if !defined(JSIMD_X86_INSTR_SET) && defined(__SSSE3__)
    #define JSIMD_X86_INSTR_SET JSIMD_X86_SSSE3_VERSION
#endif

#if !defined(JSIMD_X86_INSTR_SET) && defined(__SSE3__)
    #define JSIMD_X86_INSTR_SET JSIMD_X86_SSE3_VERSION
#endif

#if !defined(JSIMD_X86_INSTR_SET) && (defined(__SSE2__) || defined(__x86_64__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2))
    #define JSIMD_X86_INSTR_SET JSIMD_X86_SSE2_VERSION
#endif

#if !defined(JSIMD_X86_INSTR_SET) && (defined(__SSE__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1))
    #define JSIMD_X86_INSTR_SET JSIMD_X86_SSE_VERSION
#endif

#if !(defined JSIMD_X86_INSTR_SET)
    #define JSIMD_X86_INSTR_SET JSIMD_VERSION_NUMBER_NOT_AVAILABLE
#else
    #define JSIMD_X86_INSTR_SET_AVAILABLE JSIMD_VERSION_NUMBER_AVAILABLE
#endif

/***************************
 * X86_AMD INSTRUCTION SET *
 ***************************/

#define JSIMD_X86_AMD_SSE4A_VERSION JSIMD_VERSION_NUMBER(4, 0, 0)
#define JSIMD_X86_AMD_FMA4_VERSION JSIMD_VERSION_NUMBER(5, 1, 0)
#define JSIMD_X86_AMD_XOP_VERSION JSIMD_VERSION_NUMBER(5, 1, 1)

#if !defined(JSIMD_X86_AMD_INSTR_SET) && defined(__XOP__)
    #define JSIMD_X86_AMD_INSTR_SET JSIMD_X86_AMD_XOP_VERSION
#endif

#if !defined(JSIMD_X86_AMD_INSTR_SET) && defined(__FMA4__)
    #define JSIMD_X86_AMD_INSTR_SET JSIMD_X86_AMD_FMA4_VERSION
#endif

#if !defined(JSIMD_X86_AMD_INSTR_SET) && defined(__SSE4A__)
    #define JSIMD_X86_AMD_INSTR_SET JSIMD_X86_AMD_SSE4A_VERSION
#endif

#if !defined(JSIMD_X86_AMD_INSTR_SET)
    #define JSIMD_X86_AMD_INSTR_SET JSIMD_VERSION_NUMBER_NOT_AVAILABLE
#else
    // X86_AMD implies X86
    #if JSIMD_X86_INSTR_SET > JSIMD_X86_AMD_INSTR_SET
        #undef JSIMD_X86_AMD_INSTR_SET
        #define JSIMD_X86_AMD_INSTR_SET JSIMD_X86_INSTR_SET
    #endif
    #define JSIMD_X86_AMD_INSTR_SET_AVAILABLE JSIMD_VERSION_NUMBER_AVAILABLE
#endif

/***********************
 * PPC INSTRUCTION SET *
 ***********************/

// We haven't implemented any support for PPC, so we should
// not enable detection for this instructoin set
/*#define JSIMD_PPC_VMX_VERSION JSIMD_VERSION_NUMBER(1, 0, 0)
#define JSIMD_PPC_VSX_VERSION JSIMD_VERSION_NUMBER(1, 1, 0)
#define JSIMD_PPC_QPX_VERSION JSIMD_VERSION_NUMBER(2, 0, 0)

#if !defined(JSIMD_PPC_INSTR_SET) && defined(__VECTOR4DOUBLE__)
    #define JSIMD_PPC_INSTR_SET JSIMD_PPC_QPX_VERSION
#endif

#if !defined(JSIMD_PPC_INSTR_SET) && defined(__VSX__)
    #define JSIMD_PPC_INSTR_SET JSIMD_PPC_VSX_VERSION
#endif

#if !defined(JSIMD_PPC_INSTR_SET) && (defined(__ALTIVEC__) || defined(__VEC__))
    #define JSIMD_PPC_INSTR_SET JSIMD_PPC_VMX_VERSION
#endif

#if !defined(JSIMD_PPC_INSTR_SET)
    #define JSIMD_PPC_INSTR_SET JSIMD_VERSION_NUMBER_NOT_AVAILABLE
#else
    #define JSIMD_PPC_INSTR_SET_AVAILABLE JSIMD_VERSION_NUMBER_AVAILABLE
#endif*/

/***********************
 * ARM INSTRUCTION SET *
 ***********************/

#define JSIMD_ARM7_NEON_VERSION JSIMD_VERSION_NUMBER(1, 0, 0)
#define JSIMD_ARM8_32_NEON_VERSION JSIMD_VERSION_NUMBER(1, 0, 0)
#define JSIMD_ARM8_64_NEON_VERSION JSIMD_VERSION_NUMBER(1, 0, 0)

// TODO __ARM_FEATURE_FMA
#if !defined(JSIMD_ARM_INSTR_SET) && (defined(__ARM_NEON))
    #if __ARM_ARCH >= 8
        #if defined(__aarch64__)
            #define JSIMD_ARM_INSTR_SET JSIMD_ARM8_64_NEON_VERSION
        #else
            #define JSIMD_ARM_INSTR_SET JSIMD_ARM8_32_NEON_VERSION
        #endif
    #elif __ARM_ARCH >= 7
        #define JSIMD_ARM_INSTR_SET JSIMD_ARM7_NEON_VERSION
    #elif defined(JSIMD_ENABLE_FALLBACK)
        #warning "NEON instruction set not supported, using fallback mode."
    #else
        static_assert(false, "NEON instruction set not supported.");
    #endif
#endif

#if !defined(JSIMD_ARM_INSTR_SET)
    #define JSIMD_ARM_INSTR_SET JSIMD_VERSION_NUMBER_NOT_AVAILABLE
#else
    #define JSIMD_ARM_INSTR_SET_AVAILABLE JSIMD_VERSION_NUMBER_AVAILABLE
#endif

/***************************
 * GENERIC INSTRUCTION SET *
 ***************************/

#undef JSIMD_INSTR_SET
#undef JSIMD_INSTR_SET_AVAILABLE

#if defined(JSIMD_X86_AMD_AVAILABLE)
    #if JSIMD_X86_INSTR_SET > JSIMD_X86_AMD_INSTR_SET
        #define JSIMD_INSTR_SET JSIMD_X86_INSTR_SET
    #else
        #define JSIMD_INSTR_SET JSIMD_X86_AMD_INSTR_SET
    #endif
#endif

#if !defined(JSIMD_INSTR_SET) && defined(JSIMD_X86_INSTR_SET_AVAILABLE)
    #define JSIMD_INSTR_SET JSIMD_X86_INSTR_SET
#endif

#if !defined(JSIMD_INSTR_SET) && defined(JSIMD_PPC_INSTR_SET_AVAILABLE)
    #define JSIMD_INSTR_SET JSIMD_PPC_INSTR_SET
#endif

#if !defined(JSIMD_INSTR_SET) && defined(JSIMD_ARM_INSTR_SET_AVAILABLE)
    #define JSIMD_INSTR_SET JSIMD_ARM_INSTR_SET
#endif

#if !defined(JSIMD_INSTR_SET)
    #define JSIMD_INSTR_SET JSIMD_VERSION_NUMBER_NOT_AVAILABLE
#elif JSIMD_INSTR_SET != JSIMD_VERSION_NUMBER_NOT_AVAILABLE
    #define JSIMD_INSTR_SET_AVAILABLE JSIMD_VERSION_NUMBER_AVAILABLE
#endif

#endif
