#pragma once

#include "jsimd_instruction_set.hpp"

/************************************************
 * Platform checks for aligned malloc functions *
 ************************************************/

#if ((defined __QNXNTO__) || (defined _GNU_SOURCE) || ((defined _XOPEN_SOURCE) && (_XOPEN_SOURCE >= 600))) \
 && (defined _POSIX_ADVISORY_INFO) && (_POSIX_ADVISORY_INFO > 0)
  #define JSIMD_HAS_POSIX_MEMALIGN 1
#else
  #define JSIMD_HAS_POSIX_MEMALIGN 0
#endif

/********************
 * Stack allocation *
 ********************/

#ifndef JSIMD_ALLOCA
    #if defined(__linux__)
        #define JSIMD_ALLOCA alloca
    #elif defined(_MSC_VER)
        #define JSIMD_ALLOCA _alloca
    #endif
#endif

/*********************
 * Default alignment *
 *********************/

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
    #define JSIMD_DEFAULT_ALIGNMENT 32
#elif JSIMD_ARM_INSTR_SET >= JSIMD_ARM7_NEON_VERSION
    #define JSIMD_DEFAULT_ALIGNMENT 16
#else
    // some versions of gcc do nos handle alignment set ot 0
    // see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=69089
    #if __GNUC__ < 7
        #define JSIMD_DEFAULT_ALIGNMENT 8
    #else
        #define JSIMD_DEFAULT_ALIGNMENT 0
    #endif
#endif

