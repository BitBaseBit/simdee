/***************************************************************************
* Copyright (c) Johan Mabille, Sylvain Corlay, Wolf Vollprecht and         *
* Martin Renou                                                             *
* Copyright (c) QuantStack                                                 *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/
#include "jsimd/math/jsimd_rounding.hpp"
#include "jsimd/memory/jsimd_aligned_allocator.hpp"
#include "jsimd/types/jsimd_types_include.hpp"
#include "jsimd_rounding_test.hpp"

namespace jsimd
{
    template <class T, size_t N, size_t A>
    bool test_rounding(std::ostream& out, const std::string& name)
    {
        simd_rounding_tester<T, N, A> tester(name);
        return test_simd_rounding(out, tester);
    }
}

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_SSE2_VERSION
TEST(jsimd, sse_float_rounding)
{
    std::ofstream out("log/sse_float_rounding.log", std::ios_base::out);
    bool res = jsimd::test_rounding<float, 4, 16>(out, "sse float");
    EXPECT_TRUE(res);
}

TEST(jsimd, sse_double_rounding)
{
    std::ofstream out("log/sse_double_rounding.log", std::ios_base::out);
    bool res = jsimd::test_rounding<double, 2, 16>(out, "sse double");
    EXPECT_TRUE(res);
}
#endif

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_AVX_VERSION
TEST(jsimd, avx_float_rounding)
{
    std::ofstream out("log/avx_float_rounding.log", std::ios_base::out);
    bool res = jsimd::test_rounding<float, 8, 32>(out, "avx float");
    EXPECT_TRUE(res);
}

TEST(jsimd, avx_double_rounding)
{
    std::ofstream out("log/avx_double_rounding.log", std::ios_base::out);
    bool res = jsimd::test_rounding<double, 4, 32>(out, "avx double");
    EXPECT_TRUE(res);
}
#endif

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_AVX512_VERSION
TEST(jsimd, avx512_float_rounding)
{
    std::ofstream out("log/avx512_float_rounding.log", std::ios_base::out);
    bool res = jsimd::test_rounding<float, 16, 64>(out, "avx512 float");
    EXPECT_TRUE(res);
}

TEST(jsimd, avx512_double_rounding)
{
    std::ofstream out("log/avx512_double_rounding.log", std::ios_base::out);
    bool res = jsimd::test_rounding<double, 8, 64>(out, "avx512 double");
    EXPECT_TRUE(res);
}
#endif

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM7_NEON_VERSION
TEST(jsimd, neon_float_rounding)
{
    std::ofstream out("log/neon_float_rounding.log", std::ios_base::out);
    bool res = jsimd::test_rounding<float, 4, 16>(out, "neon float");
    EXPECT_TRUE(res);
}
#endif
#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
TEST(jsimd, neon_double_rounding)
{
    std::ofstream out("log/neon_double_rounding.log", std::ios_base::out);
    bool res = jsimd::test_rounding<double, 2, 32>(out, "neon double");
    EXPECT_TRUE(res);
}
#endif

#if defined(JSIMD_ENABLE_FALLBACK)
TEST(jsimd, fallback_float_rounding)
{
    std::ofstream out("log/fallback_float_rounding.log", std::ios_base::out);
    bool res = jsimd::test_rounding<float, 7, 32>(out, "fallback float");
    EXPECT_TRUE(res);
}

TEST(jsimd, fallback_double_rounding)
{
    std::ofstream out("log/fallback_double_rounding.log", std::ios_base::out);
    bool res = jsimd::test_rounding<double, 3, 32>(out, "fallback double");
    EXPECT_TRUE(res);
}
#endif
#endif // JSIMD_INSTR_SET_AVAILABLE
