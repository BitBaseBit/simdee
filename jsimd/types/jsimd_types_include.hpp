#ifndef JSIMD_TYPES_INCLUDE_HPP
#define JSIMD_TYPES_INCLUDE_HPP

#include "../config/jsimd_include.hpp"

#if defined(JSIMD_ENABLE_FALLBACK)
#include "jsimd_fallback.hpp"
#endif

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_SSE2_VERSION
#include "jsimd_sse_conversion.hpp"
#include "jsimd_sse_double.hpp"
#include "jsimd_sse_float.hpp"
#include "jsimd_sse_int8.hpp"
#include "jsimd_sse_int16.hpp"
#include "jsimd_sse_int32.hpp"
#include "jsimd_sse_int64.hpp"
#include "jsimd_sse_complex.hpp"
#endif

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_AVX_VERSION
#include "jsimd_avx_conversion.hpp"
#include "jsimd_avx_double.hpp"
#include "jsimd_avx_float.hpp"
#include "jsimd_avx_int8.hpp"
#include "jsimd_avx_int16.hpp"
#include "jsimd_avx_int32.hpp"
#include "jsimd_avx_int64.hpp"
#include "jsimd_avx_complex.hpp"
#endif

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_AVX512_VERSION
#include "jsimd_avx512_conversion.hpp"
#include "jsimd_avx512_bool.hpp"
#include "jsimd_avx512_double.hpp"
#include "jsimd_avx512_float.hpp"
#include "jsimd_avx512_int8.hpp"
#include "jsimd_avx512_int16.hpp"
#include "jsimd_avx512_int32.hpp"
#include "jsimd_avx512_int64.hpp"
#include "jsimd_avx512_complex.hpp"
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
	    #pragma message("Warning: No SIMD instructions set detected, please enable SIMD instructions or activate the fallback mode. (e.g. for x86 -march=native )")
        #else
	    #warning "No SIMD instructions set detected, please enable SIMD instructions or activate the fallback mode. (e.g. for x86 -march=native)"
	#endif
    #endif
#endif

#include "jsimd_utils.hpp"

#endif
