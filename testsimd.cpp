#include <cstddef>
#include <vector>
#include "jsimd/include/jsimd/jsimd.hpp"

template <class C, class Tag>
void mean(const C& a, const C& b, C& res)
{
    using b_type = jsimd::simd_type<double>;
    std::size_t inc = b_type::size;
    std::size_t size = res.size();
    // size for which the vectorization is possible
    std::size_t vec_size = size - size % inc;
    for(std::size_t i = 0; i < vec_size; i += inc)
    {
        b_type avec = jsimd::load_simd(&a[i], Tag());
        b_type bvec = jsimd::load_simd(&b[i], Tag());
        b_type rvec = (avec + bvec) / 2;
        jsimd::store_simd(&res[i], rvec, Tag());
    }
    // Remaining part that cannot be vectorize
    for(std::size_t i = vec_size; i < size; ++i)
    {
        res[i] = (a[i] + b[i]) / 2;
    }
}
