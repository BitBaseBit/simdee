#ifndef JSIMD_NUMERICAL_CONSTANT_HPP
#define JSIMD_NUMERICAL_CONSTANT_HPP

#include <limits>

#include "../types/jsimd_types_include.hpp"

namespace jsimd
{

#define JSIMD_DEFINE_CONSTANT(NAME, SINGLE, DOUBLE) \
    template <class T>                              \
    constexpr T NAME() noexcept                     \
    {                                               \
        return T(NAME<typename T::value_type>());   \
    }                                               \
    template <>                                     \
    constexpr float NAME<float>() noexcept          \
    {                                               \
        return SINGLE;                              \
    }                                               \
    template <>                                     \
    constexpr double NAME<double>() noexcept        \
    {                                               \
        return DOUBLE;                              \
    }

#define JSIMD_DEFINE_CONSTANT_HEX(NAME, SINGLE, DOUBLE) \
    template <class T>                                  \
    constexpr T NAME() noexcept                         \
    {                                                   \
        return T(NAME<typename T::value_type>());       \
    }                                                   \
    template <>                                         \
    constexpr float NAME<float>() noexcept              \
    {                                                   \
      return detail::caster32_t(uint32_t(SINGLE)).f;	\
    }                                                   \
    template <>                                         \
    constexpr double NAME<double>() noexcept            \
    {                                                   \
        return detail::caster64_t(uint64_t(DOUBLE)).f;  \
    }

    JSIMD_DEFINE_CONSTANT(infinity, (std::numeric_limits<float>::infinity()), (std::numeric_limits<double>::infinity()))
    JSIMD_DEFINE_CONSTANT(invlog_2, 1.442695040888963407359924681001892137426645954152986f, 1.442695040888963407359924681001892137426645954152986)
    JSIMD_DEFINE_CONSTANT_HEX(invlog_2hi, 0x3fb8b000, 0x3ff7154765200000)
    JSIMD_DEFINE_CONSTANT_HEX(invlog_2lo, 0xb9389ad4, 0x3de705fc2eefa200)
    JSIMD_DEFINE_CONSTANT(invlog10_2, 3.32192809488736234787031942949f, 3.32192809488736234787031942949)
    JSIMD_DEFINE_CONSTANT_HEX(invpi, 0x3ea2f983, 0x3fd45f306dc9c883)
    JSIMD_DEFINE_CONSTANT(log_2, 0.6931471805599453094172321214581765680755001343602553f, 0.6931471805599453094172321214581765680755001343602553)
    JSIMD_DEFINE_CONSTANT_HEX(log_2hi, 0x3f318000, 0x3fe62e42fee00000)
    JSIMD_DEFINE_CONSTANT_HEX(log_2lo, 0xb95e8083, 0x3dea39ef35793c76)
    JSIMD_DEFINE_CONSTANT_HEX(log10_2hi, 0x3e9a0000, 0x3fd3440000000000)
    JSIMD_DEFINE_CONSTANT_HEX(log10_2lo, 0x39826a14, 0x3ed3509f79fef312)
    JSIMD_DEFINE_CONSTANT_HEX(logeps, 0xc17f1402, 0xc04205966f2b4f12)
    JSIMD_DEFINE_CONSTANT_HEX(logpi, 0x3f928682, 0x3ff250d048e7a1bd)
    JSIMD_DEFINE_CONSTANT_HEX(logsqrt2pi, 0x3f6b3f8e, 0x3fed67f1c864beb5)
    JSIMD_DEFINE_CONSTANT(maxflint, 16777216.0f, 9007199254740992.0)
    JSIMD_DEFINE_CONSTANT(maxlog, 88.3762626647949f, 709.78271289338400)
    JSIMD_DEFINE_CONSTANT(maxlog2, 127.0f, 1023.)
    JSIMD_DEFINE_CONSTANT(maxlog10, 38.23080825805664f, 308.2547155599167)
    JSIMD_DEFINE_CONSTANT_HEX(mediumpi, 0x43490fdb, 0x412921fb54442d18)
    JSIMD_DEFINE_CONSTANT(minlog, -88.3762626647949f, -708.3964185322641)
    JSIMD_DEFINE_CONSTANT(minlog2, -127.0f, -1023.)
    JSIMD_DEFINE_CONSTANT(minlog10, -37.89999771118164f, -308.2547155599167)
    JSIMD_DEFINE_CONSTANT(minusinfinity, (-infinity<float>()), (-infinity<double>()))
    JSIMD_DEFINE_CONSTANT(minuszero, -0.0f, -0.0)
    JSIMD_DEFINE_CONSTANT_HEX(nan, 0xffffffff, 0xffffffffffffffff)
    JSIMD_DEFINE_CONSTANT_HEX(oneosqrteps, 0x453504f3, 0x4190000000000000)
    JSIMD_DEFINE_CONSTANT_HEX(oneotwoeps, 0x4a800000, 0x4320000000000000)
    JSIMD_DEFINE_CONSTANT_HEX(pi, 0x40490fdb, 0x400921fb54442d18)
    JSIMD_DEFINE_CONSTANT_HEX(pio_2lo, 0xb33bbd2e, 0x3c91a62633145c07)
    JSIMD_DEFINE_CONSTANT_HEX(pio_4lo, 0xb2bbbd2e, 0x3c81a62633145c07)
    JSIMD_DEFINE_CONSTANT_HEX(pio2, 0x3fc90fdb, 0x3ff921fb54442d18)
    JSIMD_DEFINE_CONSTANT_HEX(pio2_1, 0x3fc90f80, 0x3ff921fb54400000)
    JSIMD_DEFINE_CONSTANT_HEX(pio2_1t, 0x37354443, 0x3dd0b4611a626331)
    JSIMD_DEFINE_CONSTANT_HEX(pio2_2, 0x37354400, 0x3dd0b4611a600000)
    JSIMD_DEFINE_CONSTANT_HEX(pio2_2t, 0x2e85a308, 0x3ba3198a2e037073)
    JSIMD_DEFINE_CONSTANT_HEX(pio2_3, 0x2e85a300, 0x3ba3198a2e000000)
    JSIMD_DEFINE_CONSTANT_HEX(pio2_3t, 0x248d3132, 0x397b839a252049c1)
    JSIMD_DEFINE_CONSTANT_HEX(pio4, 0x3f490fdb, 0x3fe921fb54442d18)
    JSIMD_DEFINE_CONSTANT_HEX(signmask, 0x80000000, 0x8000000000000000)
    JSIMD_DEFINE_CONSTANT(smallestposval, 1.1754944e-38f, 2.225073858507201e-308)
    JSIMD_DEFINE_CONSTANT_HEX(sqrt_2pi, 0x40206c99, 0x40040d931ff62704)
    JSIMD_DEFINE_CONSTANT_HEX(sqrteps, 0x39b504f3, 0x3e50000000000000)
    JSIMD_DEFINE_CONSTANT_HEX(tanpio8, 0x3ed413cd, 0x3fda827999fcef31)
    JSIMD_DEFINE_CONSTANT_HEX(tan3pio8, 0x401a827a, 0x4003504f333f9de6)
    JSIMD_DEFINE_CONSTANT_HEX(twentypi, 0x427b53d1, 0x404f6a7a2955385e)
    JSIMD_DEFINE_CONSTANT_HEX(twoopi, 0x3f22f983, 0x3fe45f306dc9c883)
    JSIMD_DEFINE_CONSTANT(twotonmb, 8388608.0f, 4503599627370496.0)
    JSIMD_DEFINE_CONSTANT_HEX(twotonmbo3, 0x3ba14518, 0x3ed428a2f98d7286)

#undef JSIMD_DEFINE_CONSTANT
#undef JSIMD_DEFINE_CONSTANT_HEX

    template <class T>
    constexpr T allbits() noexcept;

    template <class T>
    constexpr as_integer_t<T> mask1frexp() noexcept;

    template <class T>
    constexpr as_integer_t<T> mask2frexp() noexcept;

    template <class T>
    constexpr as_integer_t<T> maxexponent() noexcept;

    template <class T>
    constexpr as_integer_t<T> maxexponentm1() noexcept;

    template <class T>
    constexpr int32_t nmb() noexcept;

    template <class T>
    constexpr T zero() noexcept;

    template <class T>
    constexpr T minvalue() noexcept;

    template <class T>
    constexpr T maxvalue() noexcept;

    /**************************
     * allbits implementation *
     **************************/

    namespace detail
    {
        template <class T, bool = std::is_integral<T>::value>
        struct allbits_impl
        {
            static constexpr T get_value() noexcept
            {
                return T(~0);
            }
        };

        template <class T>
        struct allbits_impl<T, false>
        {
            static constexpr T get_value() noexcept
            {
                return nan<T>();
            }
        };
    }

    template <class T>
    constexpr T allbits() noexcept
    {
        return T(detail::allbits_impl<typename T::value_type>::get_value());
    }

    /*****************************
     * mask1frexp implementation *
     *****************************/

    template <class T>
    constexpr as_integer_t<T> mask1frexp() noexcept
    {
        return as_integer_t<T>(mask1frexp<typename T::value_type>());
    }

    template <>
    constexpr int32_t mask1frexp<float>() noexcept
    {
        return 0x7f800000;
    }

    template <>
    constexpr int64_t mask1frexp<double>() noexcept
    {
        return 0x7ff0000000000000;
    }

    /*****************************
     * mask2frexp implementation *
     *****************************/

    template <class T>
    constexpr as_integer_t<T> mask2frexp() noexcept
    {
        return as_integer_t<T>(mask2frexp<typename T::value_type>());
    }

    template <>
    constexpr int32_t mask2frexp<float>() noexcept
    {
        return 0x3f000000;
    }

    template <>
    constexpr int64_t mask2frexp<double>() noexcept
    {
        return 0x3fe0000000000000;
    }

    /******************************
     * maxexponent implementation *
     ******************************/

    template <class T>
    constexpr as_integer_t<T> maxexponent() noexcept
    {
        return as_integer_t<T>(maxexponent<typename T::value_type>());
    }

    template <>
    constexpr int32_t maxexponent<float>() noexcept
    {
        return 127;
    }

    template <>
    constexpr int64_t maxexponent<double>() noexcept
    {
        return 1023;
    }

    /******************************
     * maxexponent implementation *
     ******************************/

    template <class T>
    constexpr as_integer_t<T> maxexponentm1() noexcept
    {
        return as_integer_t<T>(maxexponentm1<typename T::value_type>());
    }

    template <>
    constexpr int32_t maxexponentm1<float>() noexcept
    {
        return 126;
    }

    template <>
    constexpr int64_t maxexponentm1<double>() noexcept
    {
        return 1022;
    }

    /**********************
     * nmb implementation *
     **********************/

    template <class T>
    constexpr int32_t nmb() noexcept
    {
        return nmb<typename T::value_type>();
    }

    template <>
    constexpr int32_t nmb<float>() noexcept
    {
        return 23;
    }

    template <>
    constexpr int32_t nmb<double>() noexcept
    {
        return 52;
    }

    /***********************
     * zero implementation *
     ***********************/

    template <class T>
    constexpr T zero() noexcept
    {
        return T(typename T::value_type(0));
    }

    /***************************
     * minvalue implementation *
     ***************************/

    namespace detail
    {
        template <class T>
        struct minvalue_impl
        {
            static constexpr T get_value() noexcept
            {
                return std::numeric_limits<typename T::value_type>::min();
            }
        };

        template <>
        struct minvalue_impl<float>
        {
            static constexpr float get_value() noexcept
            {
                return detail::caster32_t(uint32_t(0xff7fffff)).f;
            }
        };

        template <>
        struct minvalue_impl<double>
        {
            static constexpr double get_value() noexcept
            {
                return detail::caster64_t(uint64_t(0xffefffffffffffff)).f;
            }
        };
    }

    template <class T>
    constexpr T minvalue() noexcept
    {
        return T(detail::minvalue_impl<typename T::value_type>::get_value());
    }

    /***************************
     * maxvalue implementation *
     ***************************/

    template <class T>
    constexpr T maxvalue() noexcept
    {
        return T(std::numeric_limits<typename T::value_type>::max());
    }
    
}

#endif
