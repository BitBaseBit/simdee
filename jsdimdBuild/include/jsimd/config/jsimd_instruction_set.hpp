#pragma once

#define JSIMD_VERSION_NUMBER(major, minor, patch) \
    ((((major) % 100) * 10000000) + (((minor) % 100) * 100000) + ((patch) % 100000))

#define JSIMD_VERSION_NUMBER_NOT_AVAILABLE \
    JSIMD_VERSION_NUMBER(0, 0, 0)

#define JSIMD_VERSION_NUMBER_AVAILABLE \
    JSIMD_VERSION_NUMBER(0, 0, 1)

/*************************
 * CLEAR INSTRUCTION SET *
 *************************/

#undef JSIMD_ARM_INSTR_SET
#undef JSIMD_ARM_INSTR_SET_AVAILABLE

/**********************
 * USER CONFIGURATION *
 **********************/

#ifdef defined(JSIMD_FORCE_ARM_INSTR_SET)
    #define JSIMD_ARM_INSTR_SET JSIMD_FORCE_ARM_INSTR_SET
    #define JSIMD_ARM_INSTR_SET_AVAILABLE JSIMD_VERSION_NUMBER_AVAILABLE
    #ifdef _MSC_VER
        #pragma message("Warning: Forcing ARM instruction set")
    #else
        #warning "Forcing ARM instruction set"
    #endif
#endif

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

