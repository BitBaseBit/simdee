#include <fstream>
#include <iostream>

#include "gtest/gtest.h"

#include "jsimd/math/jsimd_math_complex.hpp"
#include "jsimd/memory/jsimd_aligned_allocator.hpp"
#include "jsimd/types/jsimd_types_include.hpp"
#include "jsimd_cexponential_test.hpp"

namespace jsimd
{
    template <class T, size_t N, size_t A>
    bool test_cexponential(std::ostream& out, const std::string& name)
    {
        simd_cexponential_tester<T, N, A> tester(name);
        return test_simd_cexponential(out, tester);
    }
}

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_SSE2_VERSION
TEST(jsimd, sse_complex_float_exponential)
{
    std::ofstream out("log/sse_complex_float_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<std::complex<float>, 4, 16>(out, "sse complex float");
    EXPECT_TRUE(res);
}

TEST(jsimd, sse_complex_double_exponential)
{
    std::ofstream out("log/sse_complex_double_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<std::complex<double>, 2, 16>(out, "sse complex double");
    EXPECT_TRUE(res);
}

#if JSIMD_ENABLE_XTL_COMPLEX
TEST(jsimd, sse_xtl_xcomplex_float_exponential)
{
    std::ofstream out("log/sse_xtl_xcomplex_float_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<xtl::xcomplex<float>, 4, 16>(out, "sse xtl xcomplex float");
    EXPECT_TRUE(res);
}

TEST(jsimd, sse_xtl_xcomplex_double_exponential)
{
    std::ofstream out("log/sse_xtl_xcomplex_double_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<xtl::xcomplex<double>, 2, 16>(out, "sse xtl xcomplex double");
    EXPECT_TRUE(res);
}
#endif

#endif

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_AVX_VERSION
TEST(jsimd, avx_complex_float_exponential)
{
    std::ofstream out("log/avx_complex_float_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<std::complex<float>, 8, 32>(out, "avx complex float");
    EXPECT_TRUE(res);
}

TEST(jsimd, avx_complex_double_exponential)
{
    std::ofstream out("log/avx_complex_double_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<std::complex<double>, 4, 32>(out, "avx complex double");
    EXPECT_TRUE(res);
}

#if JSIMD_ENABLE_XTL_COMPLEX
TEST(jsimd, avx_xtl_xcomplex_float_exponential)
{
    std::ofstream out("log/avx_xtl_xcomplex_float_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<xtl::xcomplex<float>, 8, 32>(out, "avx xtl xcomplex float");
    EXPECT_TRUE(res);
}

TEST(jsimd, avx_xtl_xcomplex_double_exponential)
{
    std::ofstream out("log/avx_xtl_xcomplex_double_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<xtl::xcomplex<double>, 4, 32>(out, "avx xtl xcomplex double");
    EXPECT_TRUE(res);
}
#endif

#endif

#if JSIMD_X86_INSTR_SET >= JSIMD_X86_AVX512_VERSION
TEST(jsimd, avx512_complex_float_exponential)
{
    std::ofstream out("log/avx512_complex_float_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<std::complex<float>, 16, 64>(out, "avx512 complex float");
    EXPECT_TRUE(res);
}

TEST(jsimd, avx512_complex_double_exponential)
{
    std::ofstream out("log/avx512_complex_double_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<std::complex<double>, 8, 64>(out, "avx512 complex double");
    EXPECT_TRUE(res);
}

#if JSIMD_ENABLE_XTL_COMPLEX
TEST(jsimd, avx512_xtl_xcomplex_float_exponential)
{
    std::ofstream out("log/avx512_xtl_xcomplex_float_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<xtl::xcomplex<float>, 16, 64>(out, "avx512 xtl xcomplex float");
    EXPECT_TRUE(res);
}

TEST(jsimd, avx512_xtl_xcomplex_double_exponential)
{
    std::ofstream out("log/avx512_xtl_xcomplex_double_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<xtl::xcomplex<double>, 8, 64>(out, "avx512 xtl xcomplex double");
    EXPECT_TRUE(res);
}
#endif

#endif

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM7_NEON_VERSION
TEST(jsimd, neon_complex_float_exponential)
{
    std::ofstream out("log/neon_complex_float_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<std::complex<float>, 4, 16>(out, "neon complex float");
    EXPECT_TRUE(res);
}
#if JSIMD_ENABLE_XTL_COMPLEX
TEST(jsimd, neon_xtl_xcomplex_float_exponential)
{
    std::ofstream out("log/neon_xtl_xcomplex_float_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<xtl::xcomplex<float>, 4, 16>(out, "neon xtl xcomplex float");
    EXPECT_TRUE(res);
}
#endif
#endif
#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
TEST(jsimd, neon_complex_double_exponential)
{
    std::ofstream out("log/neon_complex_double_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<std::complex<double>, 2, 32>(out, "neon complex double");
    EXPECT_TRUE(res);
}
#if JSIMD_ENABLE_XTL_COMPLEX
TEST(jsimd, neon_xtl_xcomplex_double_exponential)
{
    std::ofstream out("log/neon_xtl_xcomplex_double_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<xtl::xcomplex<double>, 2, 32>(out, "neon xtl xcomplex double");
    EXPECT_TRUE(res);
}
#endif
#endif

#if defined(JSIMD_ENABLE_FALLBACK)
TEST(jsimd, fallback_complex_float_exponential)
{
    std::ofstream out("log/fallback_complex_float_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<std::complex<float>, 7, 32>(out, "fallback complex float");
    EXPECT_TRUE(res);
}

TEST(jsimd, fallback_complex_double_exponential)
{
    std::ofstream out("log/fallback_complex_double_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<std::complex<double>, 3, 32>(out, "fallback complex double");
    EXPECT_TRUE(res);
}

#if JSIMD_ENABLE_XTL_COMPLEX
TEST(jsimd, fallback_xtl_xcomplex_float_exponential)
{
    std::ofstream out("log/fallback_xtl_xcomplex_float_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<xtl::xcomplex<float>, 7, 32>(out, "fallback xtl xcomplex float");
    EXPECT_TRUE(res);
}

TEST(jsimd, fallback_xtl_xcomplex_double_exponential)
{
    std::ofstream out("log/fallback_xtl_xcomplex_double_exponential.log", std::ios_base::out);
    bool res = jsimd::test_cexponential<xtl::xcomplex<double>, 3, 32>(out, "fallback xtl xcomplex double");
    EXPECT_TRUE(res);
}
#endif

#endif
