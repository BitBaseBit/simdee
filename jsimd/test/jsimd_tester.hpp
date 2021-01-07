#ifndef JSIMD_TESTER_HPP
#define JSIMD_TESTER_HPP

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <string>
#include <vector>

#include "jsimd/memory/jsimd_aligned_allocator.hpp"

namespace jsimd
{

    template <class T, std::size_t N>
    class batch;

    template <class T, std::size_t N, std::size_t A>
    struct simd_tester
    {
        using vector_type = batch<T, N>;
        using value_type = T;
        using res_type = std::vector<value_type, aligned_allocator<value_type, A>>;
        static constexpr std::size_t size = N;
    };

    namespace detail
    {
        template <class V, class S>
        void load_vec(V& vec, const S& src)
        {
            vec.load_aligned(&src[0]);
        }

        template <class V, class R>
        void store_vec(V& vec, R& res)
        {
            vec.store_aligned(&res[0]);
        }

        template <class V, class S>
        void load_vec(V& vec, const S& src, size_t i)
        {
            vec.load_aligned(&src[i]);
        }

        template <class V, class R>
        void store_vec(V& vec, R& res, size_t i)
        {
            vec.store_aligned(&res[i]);
        }
    }
}

#endif
