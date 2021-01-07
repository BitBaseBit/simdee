#include <fstream>
#include <iostream>

#include "gtest/gtest.h"
#include "jsimd_api_test.hpp"

namespace jsimd
{
    template <size_t N, size_t A>
    bool test_api_load(std::ostream& out, const std::string& name)
    {
        simd_api_load_store_tester<N, A> tester(name);
        return test_simd_api_load(out, tester);
    }

    template <size_t N, size_t A>
    bool test_api_store(std::ostream& out, const std::string& name)
    {
        simd_api_load_store_tester<N, A> tester(name);
        return test_simd_api_store(out, tester);
    }

    template <class T, size_t N, size_t A>
    bool test_complex_api(std::ostream& out, const std::string& name)
    {
        simd_complex_ls_tester<T, N, A> tester(name);
        return test_simd_complex_api(out, tester);
    }
}

#if JSIMD_X86_INSTR_SET > JSIMD_VERSION_NUMBER_NOT_AVAILABLE
TEST(jsimd, complex_return_type)
{
    using cf_type = std::complex<float>;
    using cf_return_type = jsimd::simd_return_type<float, cf_type>;
    EXPECT_TRUE((std::is_same<cf_return_type, jsimd::batch<cf_type, JSIMD_BATCH_FLOAT_SIZE>>::value));

    using df_type = std::complex<double>;
    using df_return_type = jsimd::simd_return_type<double, df_type>;
    EXPECT_TRUE((std::is_same<df_return_type, jsimd::batch<df_type, JSIMD_BATCH_DOUBLE_SIZE>>::value));
}

#ifdef JSIMD_ENABLE_XTL_COMPLEX
TEST(jsimd, xtl_xcomplex_return_type)
{
    using cf_type = xtl::xcomplex<float>;
    using cf_return_type = jsimd::simd_return_type<float, cf_type>;
    EXPECT_TRUE((std::is_same<cf_return_type, jsimd::batch<cf_type, JSIMD_BATCH_FLOAT_SIZE>>::value));

#ifdef JSIMD_BATCH_DOUBLE_SIZE
    using df_type = xtl::xcomplex<double>;
    using df_return_type = jsimd::simd_return_type<double, df_type>;
    EXPECT_TRUE((std::is_same<df_return_type, jsimd::batch<df_type, JSIMD_BATCH_DOUBLE_SIZE>>::value));
#endif
}
#endif

TEST(jsimd, api_load)
{
    std::ofstream out("log/jsimd_api_load.log", std::ios_base::out);
    bool res = jsimd::test_api_load<JSIMD_BATCH_DOUBLE_SIZE, JSIMD_DEFAULT_ALIGNMENT>(out, "jsimd api load");
    EXPECT_TRUE(res);
}

TEST(jsimd, api_store)
{
    std::ofstream out("log/jsimd_api_store.log", std::ios_base::out);
    bool res = jsimd::test_api_store<JSIMD_BATCH_DOUBLE_SIZE, JSIMD_DEFAULT_ALIGNMENT>(out, "jsimd api store");
    EXPECT_TRUE(res);
}

TEST(jsimd, complex_float_api)
{
    std::ofstream out("log/jsimd_complex_float_api.log", std::ios_base::out);
    bool res = jsimd::test_complex_api<std::complex<float>, JSIMD_BATCH_FLOAT_SIZE, JSIMD_DEFAULT_ALIGNMENT>(out, "jsimd complex float api");
    EXPECT_TRUE(res);
}

TEST(jsimd, complex_double_api)
{
    std::ofstream out("log/jsimd_complex_double_api.log", std::ios_base::out);
    bool res = jsimd::test_complex_api<std::complex<double>, JSIMD_BATCH_DOUBLE_SIZE, JSIMD_DEFAULT_ALIGNMENT>(out, "jsimd complex double api");
    EXPECT_TRUE(res);
}

#ifdef JSIMD_BATCH_DOUBLE_SIZE
TEST(jsimd, api_set)
{
    std::ofstream out("log/jsimd_set_api.log", std::ios_base::out);
    bool res = jsimd::test_simd_api_set(out, "jsimd api set");
    EXPECT_TRUE(res);
}
#endif

#endif
