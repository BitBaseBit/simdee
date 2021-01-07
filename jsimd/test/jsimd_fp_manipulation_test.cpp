#include <fstream>
#include <iostream>

#include "gtest/gtest.h"

#include "jsimd/config/jsimd_instruction_set.hpp"

#ifdef JSIMD_INSTR_SET_AVAILABLE

#include "jsimd/math/jsimd_fp_manipulation.hpp"
#include "jsimd/memory/jsimd_aligned_allocator.hpp"
#include "jsimd/types/jsimd_types_include.hpp"
#include "jsimd_fp_manipulation_test.hpp"

namespace jsimd
{
    template <class T, size_t N, size_t A>
    bool test_fp_manipulation(std::ostream& out, const std::string& name)
    {
        simd_fpmanip_tester<T, N, A> tester(name);
        return test_simd_fp_manipulation(out, tester);
    }
}

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_SSE2_VERSION
TEST(jsimd, sse_float_fp_manipulation)
{
    std::ofstream out("log/sse_float_fp_manipulation.log", std::ios_base::out);
    bool res = jsimd::test_fp_manipulation<float, 4, 16>(out, "sse float");
    EXPECT_TRUE(res);
}

TEST(jsimd, sse_double_fp_manipulation)
{
    std::ofstream out("log/sse_double_fp_manipulation.log", std::ios_base::out);
    bool res = jsimd::test_fp_manipulation<double, 2, 16>(out, "sse double");
    EXPECT_TRUE(res);
}
#endif

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_AVX_VERSION
TEST(jsimd, avx_float_fp_manipulation)
{
    std::ofstream out("log/avx_float_fp_manipulation.log", std::ios_base::out);
    bool res = jsimd::test_fp_manipulation<float, 8, 32>(out, "avx float");
    EXPECT_TRUE(res);
}

TEST(jsimd, avx_double_fp_manipulation)
{
    std::ofstream out("log/avx_double_fp_manipulation.log", std::ios_base::out);
    bool res = jsimd::test_fp_manipulation<double, 4, 32>(out, "avx double");
    EXPECT_TRUE(res);
}
#endif

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_AVX512_VERSION
TEST(jsimd, avx512_float_fp_manipulation)
{
    std::ofstream out("log/avx512_float_fp_manipulation.log", std::ios_base::out);
    bool res = jsimd::test_fp_manipulation<float, 16, 64>(out, "avx512 float");
    EXPECT_TRUE(res);
}

TEST(jsimd, avx512_double_fp_manipulation)
{
    std::ofstream out("log/avx512_double_fp_manipulation.log", std::ios_base::out);
    bool res = jsimd::test_fp_manipulation<double, 8, 64>(out, "avx512 double");
    EXPECT_TRUE(res);
}
#endif

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM7_NEON_VERSION
TEST(jsimd, neon_float_fp_manipulation)
{
    std::ofstream out("log/neon_float_fp_manipulation.log", std::ios_base::out);
    bool res = jsimd::test_fp_manipulation<float, 4, 32>(out, "neon float");
    EXPECT_TRUE(res);
}
#endif
#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
TEST(jsimd, neon_double_fp_manipulation)
{
    std::ofstream out("log/neon_double_fp_manipulation.log", std::ios_base::out);
    bool res = jsimd::test_fp_manipulation<double, 2, 32>(out, "neon double");
    EXPECT_TRUE(res);
}
#endif

#if defined(JSIMD_ENABLE_FALLBACK)
TEST(jsimd, fallback_float_fp_manipulation)
{
    std::ofstream out("log/fallback_float_fp_manipulation.log", std::ios_base::out);
    bool res = jsimd::test_fp_manipulation<float, 7, 32>(out, "fallback float");
    EXPECT_TRUE(res);
}

TEST(jsimd, fallback_double_fp_manipulation)
{
    std::ofstream out("log/fallback_double_fp_manipulation.log", std::ios_base::out);
    bool res = jsimd::test_fp_manipulation<double, 3, 32>(out, "fallback double");
    EXPECT_TRUE(res);
}
#endif
#endif // JSIMD_INSTR_SET_AVAILABLE
