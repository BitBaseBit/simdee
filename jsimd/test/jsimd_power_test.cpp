#include <fstream>
#include <iostream>

#include "gtest/gtest.h"

#include "jsimd/config/jsimd_instruction_set.hpp"

#ifdef JSIMD_INSTR_SET_AVAILABLE

#include "jsimd/math/jsimd_power.hpp"
#include "jsimd/memory/jsimd_aligned_allocator.hpp"
#include "jsimd/types/jsimd_types_include.hpp"
#include "jsimd_power_test.hpp"

namespace jsimd
{
    template <class T, size_t N, size_t A>
    bool test_power(std::ostream& out, const std::string& name)
    {
        simd_power_tester<T, N, A> tester(name);
        return test_simd_power(out, tester);
    }
}

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_SSE2_VERSION
TEST(jsimd, sse_float_power)
{
    std::ofstream out("log/sse_float_power.log", std::ios_base::out);
    bool res = jsimd::test_power<float, 4, 16>(out, "sse float");
    EXPECT_TRUE(res);
}

TEST(jsimd, sse_double_power)
{
    std::ofstream out("log/sse_double_power.log", std::ios_base::out);
    bool res = jsimd::test_power<double, 2, 16>(out, "sse double");
    EXPECT_TRUE(res);
}
#endif

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_AVX_VERSION
TEST(jsimd, avx_float_power)
{
    std::ofstream out("log/avx_float_power.log", std::ios_base::out);
    bool res = jsimd::test_power<float, 8, 32>(out, "avx float");
    EXPECT_TRUE(res);
}

TEST(jsimd, avx_double_power)
{
    std::ofstream out("log/avx_double_power.log", std::ios_base::out);
    bool res = jsimd::test_power<double, 4, 32>(out, "avx double");
    EXPECT_TRUE(res);
}
#endif

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_AVX512_VERSION
TEST(jsimd, avx512_float_power)
{
    std::ofstream out("log/avx512_float_power.log", std::ios_base::out);
    bool res = jsimd::test_power<float, 16, 64>(out, "avx512 float");
    EXPECT_TRUE(res);
}

TEST(jsimd, avx512_double_power)
{
    std::ofstream out("log/avx512_double_power.log", std::ios_base::out);
    bool res = jsimd::test_power<double, 8, 64>(out, "avx512 double");
    EXPECT_TRUE(res);
}
#endif

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM7_NEON_VERSION
TEST(jsimd, neon_float_power)
{
    std::ofstream out("log/neon_float_power.log", std::ios_base::out);
    bool res = jsimd::test_power<float, 4, 16>(out, "neon float");
    EXPECT_TRUE(res);
}
#endif
#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
TEST(jsimd, neon_double_power)
{
    std::ofstream out("log/neon_double_power.log", std::ios_base::out);
    bool res = jsimd::test_power<double, 2, 32>(out, "neon double");
    EXPECT_TRUE(res);
}
#endif

#if defined(JSIMD_ENABLE_FALLBACK)
TEST(jsimd, fallback_float_power)
{
    std::ofstream out("log/fallback_float_power.log", std::ios_base::out);
    bool res = jsimd::test_power<float, 7, 32>(out, "fallback float");
    EXPECT_TRUE(res);
}

TEST(jsimd, fallback_double_power)
{
    std::ofstream out("log/fallback_double_power.log", std::ios_base::out);
    bool res = jsimd::test_power<double, 3, 32>(out, "fallback double");
    EXPECT_TRUE(res);
}
#endif
#endif // JSIMD_INSTR_SET_AVAILABLE
