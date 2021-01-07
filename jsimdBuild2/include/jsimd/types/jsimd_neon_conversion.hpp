#prgama once

#include "jsimd_neon_bool.hpp"
#include "jsimd_neon_float.hpp"
#include "jsimd_neon_int8.hpp"
#include "jsimd_neon_int16.hpp"
#include "jsimd_neon_int32.hpp"
#include "jsimd_neon_int64.hpp"
#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
    #include "jsimd_neon_double.hpp"
#endif
#include "jsimd_neon_uint32.hpp"
#include "jsimd_neon_uint64.hpp"
#include "jsimd_neon_uint16.hpp"
#include "jsimd_neon_uint8.hpp"

namespace jsimd
{

    /************************
     * conversion functions *
     ************************/

    batch<int32_t, 4> to_int(const batch<float, 4>& x);
    batch<float, 4> to_float(const batch<int32_t, 4>& x);

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
    batch<int64_t, 2> to_int(const batch<double, 2>& x);
    batch<double, 2> to_float(const batch<int64_t, 2>& x);
#endif

    /**************************
     * boolean cast functions *
     **************************/

    batch_bool<int32_t, 4> bool_cast(const batch_bool<float, 4>& x);
    batch_bool<float, 4> bool_cast(const batch_bool<int32_t, 4>& x);

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
    batch_bool<int64_t, 2> bool_cast(const batch_bool<double, 2>& x);
    batch_bool<double, 2> bool_cast(const batch_bool<int64_t, 2>& x);
#endif

    /*******************************
     * bitwise_cast implementation *
     *******************************/

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
    JSIMD_DEFINE_BITWISE_CAST_FLOAT(double, 2)
#endif
    JSIMD_DEFINE_BITWISE_CAST_FLOAT(float, 4)
    JSIMD_DEFINE_BITWISE_CAST(int64_t, 2)
    JSIMD_DEFINE_BITWISE_CAST(uint64_t, 2)
    JSIMD_DEFINE_BITWISE_CAST(int32_t, 4)
    JSIMD_DEFINE_BITWISE_CAST(uint32_t, 4)
    JSIMD_DEFINE_BITWISE_CAST(int16_t, 8)
    JSIMD_DEFINE_BITWISE_CAST(uint16_t, 8)
    JSIMD_DEFINE_BITWISE_CAST(int8_t, 16)
    JSIMD_DEFINE_BITWISE_CAST(uint8_t, 16)
    
    /***************************************
     * conversion functions implementation *
     ***************************************/

    inline batch<int32_t, 4> to_int(const batch<float, 4>& x)
    {
        return vcvtq_s32_f32(x);
    }

    inline batch<float, 4> to_float(const batch<int32_t, 4>& x)
    {
        return vcvtq_f32_s32(x);
    }

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
    inline batch<int64_t, 2> to_int(const batch<double, 2>& x)
    {
        return vcvtq_s64_f64(x);
    }

    inline batch<double, 2> to_float(const batch<int64_t, 2>& x)
    {
        return vcvtq_f64_s64(x);
    }
#endif

    /*****************************************
     * batch cast functions implementation *
     *****************************************/

    JSIMD_BATCH_CAST_INTRINSIC(int8_t, uint8_t, 16, vreinterpretq_u8_s8);
    JSIMD_BATCH_CAST_INTRINSIC(uint8_t, int8_t, 16, vreinterpretq_s8_u8);
    JSIMD_BATCH_CAST_INTRINSIC(int16_t, uint16_t, 8, vreinterpretq_u16_s16);
    JSIMD_BATCH_CAST_INTRINSIC(uint16_t, int16_t, 8, vreinterpretq_s16_u16);
    JSIMD_BATCH_CAST_INTRINSIC(int32_t, uint32_t, 4, vreinterpretq_u32_s32);
    JSIMD_BATCH_CAST_INTRINSIC(int32_t, float, 4, vcvtq_f32_s32);
    JSIMD_BATCH_CAST_INTRINSIC(uint32_t, int32_t, 4, vreinterpretq_s32_u32);
    JSIMD_BATCH_CAST_INTRINSIC(uint32_t, float, 4, vcvtq_f32_u32);
    JSIMD_BATCH_CAST_INTRINSIC(float, int32_t, 4, vcvtq_s32_f32);
    JSIMD_BATCH_CAST_INTRINSIC(float, uint32_t, 4, vcvtq_u32_f32);
#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
    JSIMD_BATCH_CAST_INTRINSIC(int64_t, uint64_t, 2, vreinterpretq_u64_s64);
    JSIMD_BATCH_CAST_INTRINSIC(int64_t, double, 2, vcvtq_f64_s64);
    JSIMD_BATCH_CAST_INTRINSIC(uint64_t, int64_t, 2, vreinterpretq_s64_u64);
    JSIMD_BATCH_CAST_INTRINSIC(uint64_t, double, 2, vcvtq_f64_u64);
    JSIMD_BATCH_CAST_INTRINSIC(double, int64_t, 2, vcvtq_s64_f64);
    JSIMD_BATCH_CAST_INTRINSIC(double, uint64_t, 2, vcvtq_u64_f64);
#endif

    /**************************
     * boolean cast functions *
     **************************/

    inline batch_bool<int32_t, 4> bool_cast(const batch_bool<float, 4>& x)
    {
        return x;
    }

    inline batch_bool<float, 4> bool_cast(const batch_bool<int32_t, 4>& x)
    {
        return x;
    }

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
    inline batch_bool<int64_t, 2> bool_cast(const batch_bool<double, 2>& x)
    {
        return x;
    }

    inline batch_bool<double, 2> bool_cast(const batch_bool<int64_t, 2>& x)
    {
        return x;
    }
#endif

    /*****************************************
     * bitwise cast functions implementation *
     *****************************************/

    JSIMD_BITWISE_CAST_INTRINSIC(float, 4,
                                 int32_t, 4,
                                 vreinterpretq_s32_f32)

    JSIMD_BITWISE_CAST_INTRINSIC(float, 4,
                                 int64_t, 2,
                                 vreinterpretq_s64_f32)

    JSIMD_BITWISE_CAST_INTRINSIC(int32_t, 4,
                                 float, 4,
                                 vreinterpretq_f32_s32)

    JSIMD_BITWISE_CAST_INTRINSIC(int64_t, 2,
                                 float, 4,
                                 vreinterpretq_f32_s64)

#if JSIMD_ARM_INSTR_SET >= JSIMD_ARM8_64_NEON_VERSION
    JSIMD_BITWISE_CAST_INTRINSIC(double, 2,
                                 float, 4,
                                 vreinterpretq_f32_f64)

    JSIMD_BITWISE_CAST_INTRINSIC(double, 2,
                                 int32_t, 4,
                                 vreinterpretq_s32_f64)

    JSIMD_BITWISE_CAST_INTRINSIC(double, 2,
                                 int64_t, 2,
                                 vreinterpretq_s64_f64)

    JSIMD_BITWISE_CAST_INTRINSIC(int32_t, 4,
                                 double, 2,
                                 vreinterpretq_f64_s32)

    JSIMD_BITWISE_CAST_INTRINSIC(int64_t, 2,
                                 double, 2,
                                 vreinterpretq_f64_s64)

    JSIMD_BITWISE_CAST_INTRINSIC(float, 4,
                                 double, 2,
                                 vreinterpretq_f64_f32)
#endif

}

