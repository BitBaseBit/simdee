#prgama once

#include <type_traits>

#include "jsimd_numerical_constant.hpp"

namespace jsimd
{

    template <class B>
    batch_type_t<B> bitofsign(const simd_base<B>& x);

    template <class B>
    batch_type_t<B> copysign(const simd_base<B>& x1, const simd_base<B>& x2);

    template <class B>
    batch_type_t<B> sign(const simd_base<B>& x);

    template <class B>
    batch_type_t<B> signnz(const simd_base<B>& x);

    /**************************
     * fp_sign implementation *
     **************************/

    template <class B>
    inline batch_type_t<B> bitofsign(const simd_base<B>& x)
    {
        return x() & minuszero<batch_type_t<B>>();
    }

    template <class B>
    inline batch_type_t<B> copysign(const simd_base<B>& x1, const simd_base<B>& x2)
    {
        return abs(x1) | bitofsign(x2);
    }

    /***********************
     * sign implementation *
     ***********************/

    namespace detail
    {
        /* origin: boost/simd/arch/common/simd/function/sign.hpp */
        /*
         * ====================================================
         * copyright 2016 NumScale SAS
         *
         * Distributed under the Boost Software License, Version 1.0.
         * (See copy at http://boost.org/LICENSE_1_0.txt)
         * ====================================================
         */

        template <class B, bool cond = std::is_integral<typename B::value_type>::value>
        struct sign_impl
        {
            static inline B compute(const B& a)
            {
                return select(a > zero<B>(), B(1), zero<B>()) - select(a < zero<B>(), B(1), zero<B>());
            }
        };

        template <class B>
        struct sign_impl<B, false>
        {
            static inline B compute(const B& a)
            {
                B r = select(a > B(0.), B(1.), B(0.)) - select(a < B(0.), B(1.), B(0.));
#ifdef JSIMD_NO_NANS
                return r;
#else
                return select(jsimd::isnan(a), nan<B>(), r);
#endif
            }
        };
    }

    template <class B>
    inline batch_type_t<B> sign(const simd_base<B>& x)
    {
        return detail::sign_impl<batch_type_t<B>>::compute(x());
    }

    /*************************
     * signnz implementation *
     *************************/

    namespace detail
    {
        /* origin: boost/simd/arch/common/simd/function/signnz.hpp */
        /*
         * ====================================================
         * copyright 2016 NumScale SAS
         *
         * Distributed under the Boost Software License, Version 1.0.
         * (See copy at http://boost.org/LICENSE_1_0.txt)
         * ====================================================
         */
        template <class B, bool cond = std::is_floating_point<typename B::value_type>::value>
        struct signnz_impl
        {
            static inline B compute(const B& x)
            {
                using value_type = typename B::value_type;
                return (x >> (sizeof(value_type) * 8 - 1)) | B(1.);
            }
        };

        template <class B>
        struct signnz_impl<B, true>
        {
            static inline B compute(const B& x)
            {
#ifndef JSIMD_NO_NANS
                return select(jsimd::isnan(x), nan<B>(), B(1.) | (signmask<B>() & x));
#else
                return B(1.) | (signmask<B>() & x);
#endif
            }
        };
    }

    template <class B>
    inline batch_type_t<B> signnz(const simd_base<B>& x)
    {
        return detail::signnz_impl<batch_type_t<B>>::compute(x());
    }
}

