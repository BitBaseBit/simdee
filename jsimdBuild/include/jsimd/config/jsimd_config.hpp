#ifndef JSIMD_CONFIG_HPP
#define JSIMD_CONFIG_HPP

#include "jsimd_align.hpp"

#define JSIMD_VERSION_MAJOR 1
#define JSIMD_VERSION_MINOR 0
#define JSIMD_VERSION_PATCH 0

#ifndef JSIMD_DEFAULT_ALLOCATOR
    #if JSIMD_X86_INSTR_SET_AVAILABLE
        #define JSIMD_DEFAULT_ALLOCATOR(T) jsimd::aligned_allocator<T, JSIMD_DEFAULT_ALIGNMENT>
    #else
        #define JSIMD_DEFAULT_ALLOCATOR(T) std::allocator<T>
    #endif
#endif

#ifndef JSIMD_STACK_ALLOCATION_LIMIT
    #define JSIMD_STACK_ALLOCATION_LIMIT 20000
#endif

#if defined(__LP64__) || defined(_WIN64)
    #define JSIMD_64_BIT_ABI
#else
    #define JSIMD_32_BIT_ABI
#endif

#endif
