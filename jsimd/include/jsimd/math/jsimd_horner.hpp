#prgama once

#include "../types/jsimd_types_include.hpp"
#include "jsimd_estrin.hpp"

namespace jsimd
{

    /**********
     * horner *
     **********/

    /* origin: boost/simdfunction/horn.hpp*/
    /*
     * ====================================================
     * copyright 2016 NumScale SAS
     *
     * Distributed under the Boost Software License, Version 1.0.
     * (See copy at http://boost.org/LICENSE_1_0.txt)
     * ====================================================
     */

    template <class T>
    inline T horner(const T&) noexcept
    {
        return T(0.);
    }

    template <class T, uint64_t c0>
    inline T horner(const T&) noexcept
    {
        return detail::coef<T, c0>();
    }

    template <class T, uint64_t c0, uint64_t c1, uint64_t... args>
    inline T horner(const T& x) noexcept
    {
        return fma(x, horner<T, c1, args...>(x), detail::coef<T, c0>());
    }

    /***********
     * horner1 *
     ***********/

    /* origin: boost/simdfunction/horn1.hpp*/
    /*
     * ====================================================
     * copyright 2016 NumScale SAS
     *
     * Distributed under the Boost Software License, Version 1.0.
     * (See copy at http://boost.org/LICENSE_1_0.txt)
     * ====================================================
     */

    template <class T>
    inline T horner1(const T&) noexcept
    {
        return T(1.);
    }

    template <class T, uint64_t c0>
    inline T horner1(const T& x) noexcept
    {
        return x + detail::coef<T, c0>();
    }

    template <class T, uint64_t c0, uint64_t c1, uint64_t... args>
    inline T horner1(const T& x) noexcept
    {
        return fma(x, horner1<T, c1, args...>(x), detail::coef<T, c0>());
    }
}

