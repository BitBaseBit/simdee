#ifndef JSIMD_SSE_CONVERSION_HPP
#define JSIMD_SSE_CONVERSION_HPP

#include "jsimd_sse_double.hpp"
#include "jsimd_sse_float.hpp"
#include "jsimd_sse_int8.hpp"
#include "jsimd_sse_int16.hpp"
#include "jsimd_sse_int32.hpp"
#include "jsimd_sse_int64.hpp"

namespace jsimd
{

    /************************
     * conversion functions *
     ************************/

    batch<int32_t, 4> to_int(const batch<float, 4>& x);
    batch<int64_t, 2> to_int(const batch<double, 2>& x);

    batch<float, 4> to_float(const batch<int32_t, 4>& x);
    batch<double, 2> to_float(const batch<int64_t, 2>& x);

    /**************************
     * boolean cast functions *
     **************************/

    batch_bool<int32_t, 4> bool_cast(const batch_bool<float, 4>& x);
    batch_bool<int64_t, 2> bool_cast(const batch_bool<double, 2>& x);
    batch_bool<float, 4> bool_cast(const batch_bool<int32_t, 4>& x);
    batch_bool<double, 2> bool_cast(const batch_bool<int64_t, 2>& x);

    /***************************************
     * conversion functions implementation *
     ***************************************/

    inline batch<int32_t, 4> to_int(const batch<float, 4>& x)
    {
        return _mm_cvttps_epi32(x);
    }

    inline batch<int64_t, 2> to_int(const batch<double, 2>& x)
    {
#if defined(JSIMD_AVX512VL_AVAILABLE) & defined(JSIMD_AVX512DQ_AVAILABLE)
        return _mm_cvttpd_epi64(x);
#else
        return batch<int64_t, 2>(static_cast<int64_t>(x[0]), static_cast<int64_t>(x[1]));
#endif
    }

    inline batch<float, 4> to_float(const batch<int32_t, 4>& x)
    {
        return _mm_cvtepi32_ps(x);
    }

    inline batch<double, 2> to_float(const batch<int64_t, 2>& x)
    {
#if defined(JSIMD_AVX512VL_AVAILABLE) & defined(JSIMD_AVX512DQ_AVAILABLE)
        return _mm_cvtepi64_pd(x);
#else
        return batch<double, 2>(static_cast<double>(x[0]), static_cast<double>(x[1]));
#endif
    }

    /*****************************************
     * batch cast functions implementation *
     *****************************************/

    JSIMD_BATCH_CAST_IMPLICIT(int8_t, uint8_t, 16)
    JSIMD_BATCH_CAST_IMPLICIT(uint8_t, int8_t, 16)
    JSIMD_BATCH_CAST_IMPLICIT(int16_t, uint16_t, 8)
    JSIMD_BATCH_CAST_IMPLICIT(uint16_t, int16_t, 8)
    JSIMD_BATCH_CAST_IMPLICIT(int32_t, uint32_t, 4)
    JSIMD_BATCH_CAST_INTRINSIC(int32_t, float, 4, _mm_cvtepi32_ps)
    JSIMD_BATCH_CAST_IMPLICIT(uint32_t, int32_t, 4)
    JSIMD_BATCH_CAST_IMPLICIT(int64_t, uint64_t, 2)
    JSIMD_BATCH_CAST_IMPLICIT(uint64_t, int64_t, 2)
    JSIMD_BATCH_CAST_INTRINSIC(float, int32_t, 4, _mm_cvttps_epi32)
#if defined(JSIMD_AVX512VL_AVAILABLE)
    JSIMD_BATCH_CAST_INTRINSIC(uint32_t, float, 4, _mm_cvtepu32_ps)
    JSIMD_BATCH_CAST_INTRINSIC(float, uint32_t, 4, _mm_cvttps_epu32)
#if defined(JSIMD_AVX512DQ_AVAILABLE)
    JSIMD_BATCH_CAST_INTRINSIC(int64_t, double, 2, _mm_cvtepi64_pd)
    JSIMD_BATCH_CAST_INTRINSIC(uint64_t, double, 2, _mm_cvtepu64_pd)
    JSIMD_BATCH_CAST_INTRINSIC(double, int64_t, 2, _mm_cvttpd_epi64)
    JSIMD_BATCH_CAST_INTRINSIC(double, uint64_t, 2, _mm_cvttpd_epu64)
#endif
#endif

    /**************************
     * boolean cast functions *
     **************************/

    inline batch_bool<int32_t, 4> bool_cast(const batch_bool<float, 4>& x)
    {
        return _mm_castps_si128(x);
    }

    inline batch_bool<int64_t, 2> bool_cast(const batch_bool<double, 2>& x)
    {
        return _mm_castpd_si128(x);
    }

    inline batch_bool<float, 4> bool_cast(const batch_bool<int32_t, 4>& x)
    {
        return _mm_castsi128_ps(x);
    }

    inline batch_bool<double, 2> bool_cast(const batch_bool<int64_t, 2>& x)
    {
        return _mm_castsi128_pd(x);
    }

    /*****************************************
     * bitwise cast functions implementation *
     *****************************************/

    JSIMD_BITWISE_CAST_INTRINSIC(float, 4,
                                 double, 2,
                                 _mm_castps_pd)

    JSIMD_BITWISE_CAST_INTRINSIC(float, 4,
                                 int32_t, 4,
                                 _mm_castps_si128)

    JSIMD_BITWISE_CAST_INTRINSIC(float, 4,
                                 int64_t, 2,
                                 _mm_castps_si128)

    JSIMD_BITWISE_CAST_INTRINSIC(double, 2,
                                 float, 4,
                                 _mm_castpd_ps)

    JSIMD_BITWISE_CAST_INTRINSIC(double, 2,
                                 int32_t, 4,
                                 _mm_castpd_si128)

    JSIMD_BITWISE_CAST_INTRINSIC(double, 2,
                                 int64_t, 2,
                                 _mm_castpd_si128)

    JSIMD_BITWISE_CAST_INTRINSIC(int32_t, 4,
                                 float, 4,
                                 _mm_castsi128_ps)

    JSIMD_BITWISE_CAST_INTRINSIC(int32_t, 4,
                                 double, 2,
                                 _mm_castsi128_pd)

    JSIMD_BITWISE_CAST_INTRINSIC(int64_t, 2,
                                 float, 4,
                                 _mm_castsi128_ps)

    JSIMD_BITWISE_CAST_INTRINSIC(int64_t, 2,
                                 double, 2,
                                 _mm_castsi128_pd)
}

#endif
