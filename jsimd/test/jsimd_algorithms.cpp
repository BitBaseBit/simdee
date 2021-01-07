#include <fstream>
#include <iostream>
#include <numeric>

#include "jsimd/jsimd.hpp"

#include "gtest/gtest.h"

struct binary_functor
{
    template <class T>
    T operator()(const T& a, const T& b) const
    {
        return a + b;
    }
};

struct unary_functor
{
    template <class T>
    T operator()(const T& a) const
    {
        return -a;
    }
};

#ifdef JSIMD_DEFAULT_ALIGNMENT
template <class T>
using test_allocator_type = jsimd::aligned_allocator<T, JSIMD_DEFAULT_ALIGNMENT>;
#else
template <class T>
using test_allocator_type = std::allocator<T>;
#endif

TEST(jsimd, binary_transform)
{
    std::vector<double> expected(93);

    std::vector<double> a(93, 123), b(93, 123), c(93);
    std::vector<double, test_allocator_type<double>> aa(93, 123), ba(93, 123), ca(93);

    std::transform(a.begin(), a.end(), b.begin(), expected.begin(),
                    binary_functor{});

    jsimd::transform(a.begin(), a.end(), b.begin(), c.begin(),
                     binary_functor{});
    EXPECT_TRUE(std::equal(expected.begin(), expected.end(), c.begin()) && expected.size() == c.size());
    std::fill(c.begin(), c.end(), -1); // erase

    jsimd::transform(aa.begin(), aa.end(), ba.begin(), c.begin(),
                     binary_functor{});
    EXPECT_TRUE(std::equal(expected.begin(), expected.end(), c.begin()) && expected.size() == c.size());
    std::fill(c.begin(), c.end(), -1); // erase

    jsimd::transform(aa.begin(), aa.end(), b.begin(), c.begin(),
                     binary_functor{});
    EXPECT_TRUE(std::equal(expected.begin(), expected.end(), c.begin()) && expected.size() == c.size());
    std::fill(c.begin(), c.end(), -1); // erase

    jsimd::transform(a.begin(), a.end(), ba.begin(), c.begin(),
                     binary_functor{});
    EXPECT_TRUE(std::equal(expected.begin(), expected.end(), c.begin()) && expected.size() == c.size());
    std::fill(c.begin(), c.end(), -1); // erase

    jsimd::transform(aa.begin(), aa.end(), ba.begin(), ca.begin(),
                     binary_functor{});
    EXPECT_TRUE(std::equal(expected.begin(), expected.end(), ca.begin()) && expected.size() == ca.size());
    std::fill(ca.begin(), ca.end(), -1); // erase

    jsimd::transform(aa.begin(), aa.end(), b.begin(), ca.begin(),
                     binary_functor{});
    EXPECT_TRUE(std::equal(expected.begin(), expected.end(), ca.begin()) && expected.size() == ca.size());
    std::fill(ca.begin(), ca.end(), -1); // erase

    jsimd::transform(a.begin(), a.end(), ba.begin(), ca.begin(),
                     binary_functor{});
    EXPECT_TRUE(std::equal(expected.begin(), expected.end(), ca.begin()) && expected.size() == ca.size());
    std::fill(ca.begin(), ca.end(), -1); // erase
}


TEST(jsimd, unary_transform)
{
    std::vector<double> expected(93);
    std::vector<double> a(93, 123), c(93);
    std::vector<double, test_allocator_type<double>> aa(93, 123), ca(93);

    std::transform(a.begin(), a.end(), expected.begin(),
                   unary_functor{});

    jsimd::transform(a.begin(), a.end(), c.begin(),
                     unary_functor{});
    EXPECT_TRUE(std::equal(expected.begin(), expected.end(), c.begin()) && expected.size() == c.size());
    std::fill(c.begin(), c.end(), -1); // erase

    jsimd::transform(aa.begin(), aa.end(), c.begin(),
                     unary_functor{});
    EXPECT_TRUE(std::equal(expected.begin(), expected.end(), c.begin()) && expected.size() == c.size());
    std::fill(c.begin(), c.end(), -1); // erase

    jsimd::transform(a.begin(), a.end(), ca.begin(),
                     unary_functor{});
    EXPECT_TRUE(std::equal(expected.begin(), expected.end(), ca.begin()) && expected.size() == ca.size());
    std::fill(ca.begin(), ca.end(), -1); // erase

    jsimd::transform(aa.begin(), aa.end(), ca.begin(),
                     unary_functor{});
    EXPECT_TRUE(std::equal(expected.begin(), expected.end(), ca.begin()) && expected.size() == ca.size());
    std::fill(ca.begin(), ca.end(), -1); // erase
}

class jsimd_reduce : public ::testing::Test
{
public:
    using aligned_vec_t = std::vector<double, test_allocator_type<double>>;

    static constexpr std::size_t num_elements = 4 * jsimd::simd_traits<double>::size;
    static constexpr std::size_t small_num = jsimd::simd_traits<double>::size - 1;

    aligned_vec_t vec = aligned_vec_t(num_elements, 123.);
    aligned_vec_t small_vec = aligned_vec_t(small_num, 42.); 
    double        init = 1337.;

    struct multiply
    {
        template <class T>
        T operator()(const T& a, const T& b) const
        {
            return a * b;
        }
    };
};

TEST_F(jsimd_reduce, unaligned_begin_unaligned_end)
{
    auto const begin = std::next(vec.begin());
    auto const end = std::prev(vec.end());

    EXPECT_EQ(std::accumulate(begin, end, init), jsimd::reduce(begin, end, init));

    if(small_vec.size() > 1)
    {
        auto const sbegin = std::next(small_vec.begin());
        auto const send = std::prev(small_vec.end());

        EXPECT_EQ(std::accumulate(sbegin, send, init), jsimd::reduce(sbegin, send, init));
    }
}

TEST_F(jsimd_reduce, unaligned_begin_aligned_end)
{
    auto const begin = std::next(vec.begin());
    auto const end = vec.end();

    EXPECT_EQ(std::accumulate(begin, end, init), jsimd::reduce(begin, end, init));

    if(small_vec.size() > 1)
    {
        auto const sbegin = std::next(small_vec.begin());
        auto const send = small_vec.end();

        EXPECT_EQ(std::accumulate(sbegin, send, init), jsimd::reduce(sbegin, send, init));
    }
}

TEST_F(jsimd_reduce, aligned_begin_unaligned_end)
{
    auto const begin = vec.begin();
    auto const end = std::prev(vec.end());

    EXPECT_EQ(std::accumulate(begin, end, init), jsimd::reduce(begin, end, init));

    if(small_vec.size() > 1)
    {
        auto const sbegin = small_vec.begin();
        auto const send = std::prev(small_vec.end());

        EXPECT_EQ(std::accumulate(sbegin, send, init), jsimd::reduce(sbegin, send, init));
    }
}

TEST_F(jsimd_reduce, aligned_begin_aligned_end)
{
    auto const begin = vec.begin();
    auto const end = vec.end();

    EXPECT_EQ(std::accumulate(begin, end, init), jsimd::reduce(begin, end, init));

    if(small_vec.size() > 1)
    {
        auto const sbegin = small_vec.begin();
        auto const send = small_vec.end();

        EXPECT_EQ(std::accumulate(sbegin, send, init), jsimd::reduce(sbegin, send, init));
    }
}

TEST_F(jsimd_reduce, using_custom_binary_function)
{
    auto const begin = vec.begin();
    auto const end = vec.end();

    EXPECT_DOUBLE_EQ(std::accumulate(begin, end, init, multiply{}), jsimd::reduce(begin, end, init, multiply{}));

    if(small_vec.size() > 1)
    {
        auto const sbegin = small_vec.begin();
        auto const send = small_vec.end();

        EXPECT_DOUBLE_EQ(std::accumulate(sbegin, send, init, multiply{}), jsimd::reduce(sbegin, send, init, multiply{}));
    }
}

#if JSIMD_X86_INSTR_SET > JSIMD_VERSION_NUMBER_NOT_AVAILABLE || JSIMD_ARM_INSTR_SET > JSIMD_VERSION_NUMBER_NOT_AVAILABLE
TEST(jsimd, iterator)
{
    std::vector<float, test_allocator_type<float>> a(10 * 16, 0.2), b(1000, 2.), c(1000, 3.);

    std::iota(a.begin(), a.end(), 0.f);
    std::vector<float> a_cpy(a.begin(), a.end());

    using batch_type = typename jsimd::simd_traits<float>::type;
    auto begin = jsimd::aligned_iterator<batch_type>(&a[0]);
    auto end = jsimd::aligned_iterator<batch_type>(&a[0] + a.size());
 
    for (; begin != end; ++begin)
    {
        *begin = *begin / 2.f;
    }

    for (auto& el : a_cpy)
    {
        el /= 2.f;
    }

    EXPECT_TRUE(a.size() == a_cpy.size() && std::equal(a.begin(), a.end(), a_cpy.begin()));

    begin = jsimd::aligned_iterator<batch_type>(&a[0]);
    *begin = sin(*begin);

    for (std::size_t i = 0; i < batch_type::size; ++i)
    {
        EXPECT_NEAR(a[i], sinf(a_cpy[i]), 1e-6);
    }

#ifdef JSIMD_BATCH_DOUBLE_SIZE
    std::vector<std::complex<double>, test_allocator_type<std::complex<double>>> ca(10 * 16, std::complex<double>(0.2));
    using cbatch_type = typename jsimd::simd_traits<std::complex<double>>::type;
    auto cbegin = jsimd::aligned_iterator<cbatch_type>(&ca[0]);
    auto cend = jsimd::aligned_iterator<cbatch_type>(&ca[0] + a.size());

    for (; cbegin != cend; ++cbegin)
    {
        *cbegin = (*cbegin + std::complex<double>(0, .3)) / 2.;
    }

    cbegin = jsimd::aligned_iterator<cbatch_type>(&ca[0]);
    *cbegin = sin(*cbegin);
    *cbegin = sqrt(*cbegin);
    auto real_part = abs(*(cbegin));
#endif

}
#endif
