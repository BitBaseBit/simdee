#include "jsimd_benchmark.hpp"
#include <map>

void benchmark_operation()
{
    //std::size_t size = 9984;
    std::size_t size = 20000;
    jsimd::run_benchmark_2op(jsimd::add_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_2op(jsimd::sub_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_2op(jsimd::mul_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_2op(jsimd::div_fn(), std::cout, size, 1000);
}

void benchmark_exp_log()
{
    std::size_t size = 20000;
    jsimd::run_benchmark_1op(jsimd::exp_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::exp2_fn(), std::cout, size, 100);
    jsimd::run_benchmark_1op(jsimd::expm1_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::log_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::log2_fn(), std::cout, size, 100);
    jsimd::run_benchmark_1op(jsimd::log10_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::log1p_fn(), std::cout, size, 1000);
}

void benchmark_trigo()
{
    std::size_t size = 20000;
    jsimd::run_benchmark_1op(jsimd::sin_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::cos_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::tan_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::asin_fn(), std::cout, size, 1000, jsimd::init_method::arctrigo);
    jsimd::run_benchmark_1op(jsimd::acos_fn(), std::cout, size, 1000, jsimd::init_method::arctrigo);
    jsimd::run_benchmark_1op(jsimd::atan_fn(), std::cout, size, 1000, jsimd::init_method::arctrigo);
}

void benchmark_hyperbolic()
{
    std::size_t size = 20000;
    jsimd::run_benchmark_1op(jsimd::sinh_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::cosh_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::tanh_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::asinh_fn(), std::cout, size, 100);
    jsimd::run_benchmark_1op(jsimd::acosh_fn(), std::cout, size, 100);
    jsimd::run_benchmark_1op(jsimd::atanh_fn(), std::cout, size, 100);
}

void benchmark_power()
{
    std::size_t size = 20000;
    jsimd::run_benchmark_2op(jsimd::pow_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::sqrt_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::cbrt_fn(), std::cout, size, 100);
    jsimd::run_benchmark_2op(jsimd::hypot_fn(), std::cout, size, 1000);
}

void benchmark_rounding()
{
    std::size_t size = 20000;
    jsimd::run_benchmark_1op(jsimd::ceil_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::floor_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::trunc_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::round_fn(), std::cout, size, 100);
    jsimd::run_benchmark_1op(jsimd::nearbyint_fn(), std::cout, size, 100);
    jsimd::run_benchmark_1op(jsimd::rint_fn(), std::cout, size, 100);
}

#ifdef JSIMD_POLY_BENCHMARKS
void benchmark_poly_evaluation()
{
    std::size_t size = 20000;
    jsimd::run_benchmark_1op(jsimd::horner_5_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::estrin_5_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::horner_10_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::estrin_10_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::horner_12_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::estrin_12_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::horner_14_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::estrin_14_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::horner_16_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_1op(jsimd::estrin_16_fn(), std::cout, size, 1000);
}
#endif

void benchmark_basic_math()
{
    std::size_t size = 20000;
    jsimd::run_benchmark_2op(jsimd::fmod_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_2op(jsimd::remainder_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_2op(jsimd::fdim_fn(), std::cout, size, 1000);
    jsimd::run_benchmark_3op(jsimd::clip_fn(), std::cout, size, 1000);
#if 0
    jsimd::run_benchmark_1op_pred(jsimd::isfinite_fn(), std::cout, size, 100);
    jsimd::run_benchmark_1op_pred(jsimd::isinf_fn(), std::cout, size, 100);
    jsimd::run_benchmark_1op_pred(jsimd::is_flint_fn(), std::cout, size, 100);
    jsimd::run_benchmark_1op_pred(jsimd::is_odd_fn(), std::cout, size, 100);
    jsimd::run_benchmark_1op_pred(jsimd::is_even_fn(), std::cout, size, 100);
#endif
}

int main(int argc, char* argv[])
{
    const std::map<std::string, std::pair<std::string, void(*)()>> fn_map = {
        {"op", {"arithmetic", benchmark_operation}},
        {"exp", {"exponential and logarithm", benchmark_exp_log}},
        {"trigo", {"trigonometric", benchmark_trigo}},
        {"hyperbolic", {"hyperbolic", benchmark_hyperbolic}},
        {"power", {"power", benchmark_power}},
        {"basic_math", {"basic math", benchmark_basic_math}},
        {"rounding", {"rounding", benchmark_rounding}},
#ifdef JSIMD_POLY_BENCHMARKS
        {"utils", {"polynomial evaluation", benchmark_poly_evaluation}},
#endif
    };

    if (argc > 1)
    {
        if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")
        {
            std::cout << "Available options:" << std::endl;
            for(auto const& kv : fn_map)
            {
                std::cout << kv.first << ": run benchmark on " << kv.second.first << " functions" << std::endl;
            }
        }
        else
        {
            for (int i = 1; i < argc; ++i)
            {
                fn_map.at(argv[i]).second();
            }
        }
    }
    else
    {
        for(auto const& kv : fn_map)
        {
            kv.second.second();
        }
    }
    return 0;
}
