#include <cstdio>
#include <iostream>
#include <string>

#include "pico_bench.hpp"

#define JSIMD_ENABLE_FALLBACK

#include <jsimd/jsimd.hpp>

// helper function to write the rendered image as PPM file
inline void writePPM(const std::string &fileName,
                     const int sizeX,
                     const int sizeY,
                     const int *pixel)
{
    FILE* file = fopen(fileName.c_str(), "wb");
    fprintf(file, "P6\n%i %i\n255\n", sizeX, sizeY);
    unsigned char* out = (unsigned char*)alloca(3 * sizeX);
    for (int y = 0; y < sizeY; y++)
    {
        const unsigned char* in =
            (const unsigned char*) &pixel[(sizeY - 1 - y) * sizeX];

        for (int x = 0; x < sizeX; x++)
        {
            out[3 * x + 0] = in[4 * x + 0];
            out[3 * x + 1] = in[4 * x + 1];
            out[3 * x + 2] = in[4 * x + 2];
        }

        fwrite(out, 3 * sizeX, sizeof(char), file);
    }
    fprintf(file, "\n");
    fclose(file);
}

namespace jsimd {

  template <std::size_t N>
  inline batch<int, N> mandel(const batch_bool<float, N> &_active,
                              const batch<float, N> &c_re,
                              const batch<float, N> &c_im,
                              int maxIters)
  {
      batch<float, N> z_re = c_re;
      batch<float, N> z_im = c_im;
      batch<int,   N> vi(0);

      for (int i = 0; i < maxIters; ++i)
      {
          auto active = _active & ((z_re * z_re + z_im * z_im) <= batch<float, N>(4.f));
          if (!jsimd::any(active))
          {
              break;
          }

          batch<float, N> new_re = z_re * z_re - z_im * z_im;
          batch<float, N> new_im = 2.f * z_re * z_im;

          z_re = c_re + new_re;
          z_im = c_im + new_im;

          vi = select(bool_cast(active), vi + 1, vi);
      }

      return vi;
  }

  template <std::size_t N>
  void mandelbrot(float x0,
                  float y0,
                  float x1,
                  float y1,
                  int width,
                  int height,
                  int maxIters,
                  int output[])
  {
      float dx = (x1 - x0) / width;
      float dy = (y1 - y0) / height;

      float arange[N];
      std::iota(&arange[0], &arange[N], 0.f);
      batch<float, N> programIndex(&arange[0], jsimd::aligned_mode());
      // std::iota(programIndex.begin(), programIndex.end(), 0.f);

      for (int j = 0; j < height; j++)
      {
          for (int i = 0; i < width; i += N)
          {
              batch<float, N> x(x0 + (i + programIndex) * dx);
              batch<float, N> y(y0 + j * dy);

              auto active = x < batch<float, N>(width);

              int base_index = (j * width + i);
              auto result    = mandel(active, x, y, maxIters);

              // implement masked store!
              // jsimd::store_aligned(result, output + base_index, active);
              batch<int, N> prev_data(output + base_index);
              select(bool_cast(active), result, prev_data)
                    .store_aligned(output + base_index);
          }
      }
  }

} // namespace jsimd

// omp version ////////////////////////////////////////////////////////////////

namespace omp {

#pragma omp declare simd
    template <typename T>
    inline int mandel(T c_re, T c_im, int count)
    {
        T z_re = c_re, z_im = c_im;
        int i;
        for (i = 0; i < count; ++i)
        {
            if (z_re * z_re + z_im * z_im > 4.f)
            {
                break;
            }

            T new_re = z_re * z_re - z_im * z_im;
            T new_im = 2.f * z_re * z_im;
            z_re     = c_re + new_re;
            z_im     = c_im + new_im;
        }

        return i;
    }

    void mandelbrot(float x0, float y0, float x1, float y1, int width,
                    int height, int maxIterations, int output[])
    {
        float dx = (x1 - x0) / width;
        float dy = (y1 - y0) / height;

        for (int j = 0; j < height; j++)
        {

#pragma omp simd
            for (int i = 0; i < width; ++i)
            {
                float x = x0 + i * dx;
                float y = y0 + j * dy;

                int index = (j * width + i);
                output[index] = mandel<float>(x, y, maxIterations);
            }
        }
    }

} // namespace omp

// scalar version /////////////////////////////////////////////////////////////

namespace scalar {

    inline int mandel(float c_re, float c_im, int count)
    {
        float z_re = c_re, z_im = c_im;
        int i;
        for (i = 0; i < count; ++i)
        {
            if (z_re * z_re + z_im * z_im > 4.f)
            {
                break;
            }

            float new_re = z_re * z_re - z_im * z_im;
            float new_im = 2.f * z_re * z_im;
            z_re         = c_re + new_re;
            z_im         = c_im + new_im;
        }

        return i;
    }

    void mandelbrot(float x0, float y0, float x1, float y1,
                    int width, int height, int maxIterations, int output[])
    {
        float dx = (x1 - x0) / width;
        float dy = (y1 - y0) / height;

        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; ++i)
            {
                float x = x0 + i * dx;
                float y = y0 + j * dy;

                int index     = (j * width + i);
                output[index] = mandel(x, y, maxIterations);
            }
        }
    }

}  // namespace scalar

int main()
{
    using namespace std::chrono;

    const unsigned int width  = 1024;
    const unsigned int height = 768;
    const float x0            = -2;
    const float x1            = 1;
    const float y0            = -1;
    const float y1            = 1;
    const int maxIters        = 256;

    alignas(64) std::array<int, width * height> buf;

    auto bencher = pico_bench::Benchmarker<milliseconds>{64, seconds{10}};

    std::cout << "starting benchmarks (results in 'ms')... " << '\n';

    // scalar run ///////////////////////////////////////////////////////////////

    std::fill(buf.begin(), buf.end(), 0);

    auto stats_scalar = bencher([&]() {
      scalar::mandelbrot(x0, y0, x1, y1, width, height, maxIters, buf.data());
    });

    const float scalar_min = stats_scalar.min().count();

    std::cout << '\n' << "scalar " << stats_scalar << '\n';

    writePPM("mandelbrot_scalar.ppm", width, height, buf.data());

    // omp run //////////////////////////////////////////////////////////////////

    std::fill(buf.begin(), buf.end(), 0);

    auto stats_omp = bencher([&]() {
      omp::mandelbrot(x0, y0, x1, y1, width, height, maxIters, buf.data());
    });

    const float omp_min = stats_omp.min().count();

    std::cout << '\n' << "omp " << stats_omp << '\n';

    writePPM("mandelbrot_omp.ppm", width, height, buf.data());

    // jsimd_1 run //////////////////////////////////////////////////////////////

    std::fill(buf.begin(), buf.end(), 0);

    auto stats_1 = bencher([&]() {
      jsimd::mandelbrot<1>(x0, y0, x1, y1, width, height, maxIters, buf.data());
    });

    const float jsimd1_min = stats_1.min().count();

    std::cout << '\n' << "jsimd_1 " << stats_1 << '\n';

    writePPM("mandelbrot_jsimd1.ppm", width, height, buf.data());

    // jsimd_4 run //////////////////////////////////////////////////////////////

    std::fill(buf.begin(), buf.end(), 0);

    auto stats_4 = bencher([&]() {
      jsimd::mandelbrot<4>(x0, y0, x1, y1, width, height, maxIters, buf.data());
    });

    const float jsimd4_min = stats_4.min().count();

    std::cout << '\n' << "jsimd_4 " << stats_4 << '\n';

    writePPM("mandelbrot_jsimd4.ppm", width, height, buf.data());

    // jsimd_8 run //////////////////////////////////////////////////////////////

    std::fill(buf.begin(), buf.end(), 0);

    auto stats_8 = bencher([&]() {
      jsimd::mandelbrot<8>(x0, y0, x1, y1, width, height, maxIters, buf.data());
    });

    const float jsimd8_min = stats_8.min().count();

    std::cout << '\n' << "jsimd_8 " << stats_8 << '\n';

    writePPM("mandelbrot_jsimd8.ppm", width, height, buf.data());

    // jsimd_16 run /////////////////////////////////////////////////////////////

    std::fill(buf.begin(), buf.end(), 0);

    auto stats_16 = bencher([&]() {
      jsimd::mandelbrot<16>(x0, y0, x1, y1, width, height, maxIters, buf.data());
    });

    const float jsimd16_min = stats_16.min().count();

    std::cout << '\n' << "jsimd_16 " << stats_16 << '\n';

    writePPM("mandelbrot_jsimd16.ppm", width, height, buf.data());

    // conclusions //////////////////////////////////////////////////////////////

    std::cout << '\n' << "Conclusions: " << '\n';

    // scalar //

    std::cout << '\n'
              << "--> scalar was " << omp_min / scalar_min
              << "x the speed of omp";

    std::cout << '\n'
              << "--> scalar was " << jsimd1_min / scalar_min
              << "x the speed of jsimd_1";

    std::cout << '\n'
              << "--> scalar was " << jsimd4_min / scalar_min
              << "x the speed of jsimd_4";

    std::cout << '\n'
              << "--> scalar was " << jsimd8_min / scalar_min
              << "x the speed of jsimd_8";

    std::cout << '\n'
              << "--> scalar was " << jsimd16_min / scalar_min
              << "x the speed of jsimd_16" << '\n';

    // omp //

    std::cout << '\n'
              << "--> omp was " << scalar_min / omp_min
              << "x the speed of scalar";

    std::cout << '\n'
              << "--> omp was " << jsimd1_min / omp_min
              << "x the speed of jsimd_1";

    std::cout << '\n'
              << "--> omp was " << jsimd4_min / omp_min
              << "x the speed of jsimd_4";

    std::cout << '\n'
              << "--> omp was " << jsimd8_min / omp_min
              << "x the speed of jsimd_8";

    std::cout << '\n'
              << "--> omp was " << jsimd16_min / omp_min
              << "x the speed of jsimd_16" << '\n';

    // jsimd1 //

    std::cout << '\n'
              << "--> jsimd1 was " << scalar_min / jsimd1_min
              << "x the speed of scalar";

    std::cout << '\n'
              << "--> jsimd1 was " << omp_min / jsimd1_min
              << "x the speed of omp";

    std::cout << '\n'
              << "--> jsimd1 was " << jsimd4_min / jsimd1_min
              << "x the speed of jsimd_4";

    std::cout << '\n'
              << "--> jsimd1 was " << jsimd8_min / jsimd1_min
              << "x the speed of jsimd_8";

    std::cout << '\n'
              << "--> jsimd1 was " << jsimd16_min / jsimd1_min
              << "x the speed of jsimd_16" << '\n';

    // jsimd4 //

    std::cout << '\n'
              << "--> jsimd4 was " << scalar_min / jsimd4_min
              << "x the speed of scalar";

    std::cout << '\n'
              << "--> jsimd4 was " << omp_min / jsimd4_min
              << "x the speed of omp";

    std::cout << '\n'
              << "--> jsimd4 was " << jsimd1_min / jsimd4_min
              << "x the speed of jsimd_1";

    std::cout << '\n'
              << "--> jsimd4 was " << jsimd8_min / jsimd4_min
              << "x the speed of jsimd_8";

    std::cout << '\n'
              << "--> jsimd4 was " << jsimd16_min / jsimd4_min
              << "x the speed of jsimd_16" << '\n';

    // jsimd8 //

    std::cout << '\n'
              << "--> jsimd8 was " << scalar_min / jsimd8_min
              << "x the speed of scalar";

    std::cout << '\n'
              << "--> jsimd8 was " << omp_min / jsimd8_min
              << "x the speed of omp";

    std::cout << '\n'
              << "--> jsimd8 was " << jsimd1_min / jsimd8_min
              << "x the speed of jsimd_1";

    std::cout << '\n'
              << "--> jsimd8 was " << jsimd4_min / jsimd8_min
              << "x the speed of jsimd_4";

    std::cout << '\n'
              << "--> jsimd8 was " << jsimd16_min / jsimd8_min
              << "x the speed of jsimd_16" << '\n';

    // jsimd16 //

    std::cout << '\n'
              << "--> jsimd16 was " << scalar_min / jsimd16_min
              << "x the speed of scalar";

    std::cout << '\n'
              << "--> jsimd16 was " << omp_min / jsimd16_min
              << "x the speed of omp";

    std::cout << '\n'
              << "--> jsimd16 was " << jsimd1_min / jsimd16_min
              << "x the speed of jsimd_1";

    std::cout << '\n'
              << "--> jsimd16 was " << jsimd4_min / jsimd16_min
              << "x the speed of jsimd_4";

    std::cout << '\n'
              << "--> jsimd16 was " << jsimd8_min / jsimd16_min
              << "x the speed of jsimd_8" << '\n';

    std::cout << '\n' << "wrote output images to 'mandelbrot_[type].ppm'" << '\n';

    return 0;
}
