#pragma once

#include "../config/jsimd_include.hpp"

#if defined(JSIMD_ENABLE_FALLBACK)
#include "jsimd_fallback.hpp"
#endif


#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM7_NEON_VERSION
#include "jsimd_neon_conversion.hpp"
#include "jsimd_neon_bool.hpp"
#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
    #include "jsimd_neon_double.hpp"
#endif
#include "jsimd_neon_float.hpp"
#include "jsimd_neon_int8.hpp"
#include "jsimd_neon_uint8.hpp"
#include "jsimd_neon_int16.hpp"
#include "jsimd_neon_uint16.hpp"
#include "jsimd_neon_int32.hpp"
#include "jsimd_neon_uint32.hpp"
#include "jsimd_neon_int64.hpp"
#include "jsimd_neon_uint64.hpp"
#include "jsimd_neon_complex.hpp"
#endif

#if !defined(JSIMD_INSTR_SET_AVAILABLE)
    #if defined(JSIMD_ENABLE_FALLBACK)
        #ifdef _MSC_VER
	    #pragma message("Warning: No SIMD instructions set detected, using fallback mode.")
        #else
	    #warning "No SIMD instructions set detected, using fallback mode."
        #endif
    #else
        #ifdef _MSC_VER
	    #pragma message("Warning: No SIMD instructions set detected, please enable SIMD instructions or activate the fallback mode. (e.g. for x86 -march=native or for ARM -mfpu=neon)")
        #else
	    #warning "No SIMD instructions set detected, please enable SIMD instructions or activate the fallback mode. (e.g. for x86 -march=native or for ARM -mfpu=neon)"
	#endif
    #endif
#endif

#include "jsimd_utils.hpp"

