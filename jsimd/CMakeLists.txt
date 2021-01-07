cmake_minimum_required(VERSION 3.1)
project(jsimd)

set(JSIMD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Versionning
# ===========

file(STRINGS "${JSIMD_INCLUDE_DIR}/jsimd/config/jsimd_config.hpp" jsimd_version_defines
     REGEX "#define JSIMD_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${jsimd_version_defines})
    if(ver MATCHES "#define JSIMD_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(JSIMD_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(${PROJECT_NAME}_VERSION
    ${JSIMD_VERSION_MAJOR}.${JSIMD_VERSION_MINOR}.${JSIMD_VERSION_PATCH})
message(STATUS "jsimd v${${PROJECT_NAME}_VERSION}")

# Build
# =====

set(JSIMD_HEADERS
    ${JSIMD_INCLUDE_DIR}/jsimd/jsimd.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/config/jsimd_align.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/config/jsimd_config.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/config/jsimd_include.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/config/jsimd_instruction_set.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_basic_math.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_error.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_exp_reduction.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_exponential.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_fp_manipulation.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_fp_sign.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_gamma.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_horner.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_hyperbolic.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_invtrigo.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_logarithm.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_math.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_math_complex.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_numerical_constant.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_power.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_rem_pio2.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_rounding.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_trigo_reduction.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/math/jsimd_trigonometric.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/memory/jsimd_aligned_allocator.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/memory/jsimd_aligned_stack_buffer.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/memory/jsimd_alignment.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx_complex.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx_conversion.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx_double.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx_float.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx_int8.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx_int32.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx_int64.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx_int_base.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx512_bool.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx512_complex.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx512_conversion.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx512_double.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx512_float.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx512_int8.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx512_int16.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx512_int32.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx512_int64.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_avx512_int_base.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_bool.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_complex.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_conversion.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_double.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_float.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_int8.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_int16.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_int32.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_int64.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_uint8.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_uint16.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_uint32.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_uint64.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_neon_utils.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_base.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_base_bool.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_complex_base.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_fallback.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_int_conversion.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_sse_complex.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_sse_conversion.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_sse_double.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_sse_float.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_sse_int8.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_sse_int32.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_sse_int64.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_sse_int_base.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_traits.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_types_include.hpp
    ${JSIMD_INCLUDE_DIR}/jsimd/types/jsimd_utils.hpp
)

add_library(jsimd INTERFACE)

target_include_directories(jsimd INTERFACE
    $<BUILD_INTERFACE:${JSIMD_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>)

target_compile_features(jsimd INTERFACE cxx_std_11)

OPTION(ENABLE_FALLBACK "build tests/benchmarks with fallback implementation" OFF)
OPTION(ENABLE_XTL_COMPLEX "enables support for xcomplex defined in xtl" OFF)
OPTION(BUILD_TESTS "jsimd test suite" OFF)
OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
    set(BUILD_TESTS ON)
endif()

if(ENABLE_FALLBACK)
    add_definitions(-DJSIMD_ENABLE_FALLBACK=1)
endif()

if(ENABLE_XTL_COMPLEX)
    add_definitions(-DJSIMD_ENABLE_XTL_COMPLEX=1)
    find_package(xtl 0.4.11 REQUIRED)
    target_link_libraries(jsimd INTERFACE xtl)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

OPTION(BUILD_BENCHMARK "jsimd benchmarks" OFF)
if(BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif()

OPTION(BUILD_EXAMPLES "jsimd examples" OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Installation
# ============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS jsimd
        EXPORT ${PROJECT_NAME}-targets)

# Makes the project importable from the build directory
export(EXPORT ${PROJECT_NAME}-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

install(DIRECTORY ${JSIMD_INCLUDE_DIR}/jsimd
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# GNUInstallDirs "DATADIR" wrong here; CMake search path wants "share".
set(JSIMD_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE STRING "install path for jsimdConfig.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${JSIMD_CMAKECONFIG_INSTALL_DIR})

# jsimd is header-only and does not depend on the architecture.
# Remove CMAKE_SIZEOF_VOID_P from xtensorConfigVersion.cmake so that an xtensorConfig.cmake
# generated for a 64 bit target can be used for 32 bit targets and vice versa.
set(_XTENSOR_CMAKE_SIZEOF_VOID_P ${CMAKE_SIZEOF_VOID_P})
unset(CMAKE_SIZEOF_VOID_P)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY SameMajorVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${JSIMD_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION ${JSIMD_CMAKECONFIG_INSTALL_DIR})

configure_file(${PROJECT_NAME}.pc.in
               "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
                @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig/")
