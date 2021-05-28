#ifndef JSIMD_INCLUDE_HPP
#define JSIMD_INCLUDE_HPP

#include "jsimd_instruction_set.hpp"

// X86 intruction sets
#if JSIMD_X86_INSTR_SET >= JSIMD_X86_FMA3_VERSION // FMA3 and later
    #ifdef __GNUC__
        #include <x86intrin.h>         
                                       
    #else
        #include <immintrin.h>         
    #endif // __GNUC__
#elif JSIMD_X86_INSTR_SET == JSIMD_X86_AVX_VERSION
    #include <immintrin.h>             // AVX
#elif JSIMD_X86_INSTR_SET == JSIMD_X86_SSE4_2_VERSION
    #include <nmmintrin.h>             // SSE4.2
#elif JSIMD_X86_INSTR_SET == JSIMD_X86_SSE4_1_VERSION
    #include <smmintrin.h>             // SSE4.1
#elif JSIMD_X86_INSTR_SET == JSIMD_X86_SSSE3_VERSION
    #include <tmmintrin.h>             // SSSE3
#elif JSIMD_X86_INSTR_SET == JSIMD_X86_SSE3_VERSION
    #include <pmmintrin.h>             // SSE3
#elif JSIMD_X86_INSTR_SET == JSIMD_X86_SSE2_VERSION
    #include <emmintrin.h>             // SSE2
#elif JSIMD_X8_INSTR_SET == JSIMD_X86_SSE_VERSION
    #include <xmmintrin.h>             // SSE
#endif // JSIMD_X86_INSTR_SET

// AMD instruction sets
#if JSIMD_X86_AMD_INSTR_SET >= JSIMD_X86_AMD_FMA4_VERSION
    #ifdef _MSC_VER
        #include <intrin.h>
    #else
        #include <x86intrin.h>
        #if JSIMD_X86_AMD_INSTR_SET >= JSIMD_X86_AMD_XOP_VERSION
            #include <xopintrin.h>
        #else
            #include <fma4intrin.h>
        #endif
    #endif //  _MSC_VER
#elif JSIMD_X86_AMD_INSTR_SET == JSIMD_X86_AMD_SSE4A_VERSION
    #include <ammintrin.h>
#endif // JSIMD_X86_AMD_INSTR_SET


#endif
