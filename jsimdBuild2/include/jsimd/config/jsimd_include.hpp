#pragma once

#include "jsimd_instruction_set.hpp"

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM7_NEON_VERSION
    #include <arm_neon.h>
#endif

