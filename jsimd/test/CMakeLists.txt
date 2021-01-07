cmake_minimum_required(VERSION 3.1)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    project(jsimd-test)

    enable_testing()

    find_package(jsimd REQUIRED CONFIG)
    set(JSIMD_INCLUDE_DIR ${jsimd_INCLUDE_DIRS})
endif ()

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting tests build type to Release")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
else()
    message(STATUS "Tests build type is ${CMAKE_BUILD_TYPE}")
endif()

include(CheckCXXCompilerFlag)

string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)

################
# ARM SETTINGS #
################

OPTION(CROSS_COMPILE_ARM "cross compile for ARM targets" OFF)

# Note: to compile on ARM (or cross compile), you may need to add the following:
# -DTARGET_ARCH="armv8-a -mfpu=neon -mfloat-abi=softfp -target arm-linux-gnueabi"
set(TARGET_ARCH "native" CACHE STRING "Target architecture arguments")
set(ARM_ARCH_DIRECTORY "arm-linux-gnueabi" CACHE STRING "ARM arch header dir")
set(ARM_GCC_VER "4.7.3" CACHE STRING "ARM GCC header dir")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    if (CROSS_COMPILE_ARM)
        # We're cross-compiling with clang++ on Travis, this is all pretty specific and just for testing
        set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
        set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)
        set(CMAKE_THREAD_LIBS_INIT)

        include_directories(/usr/${ARM_ARCH_DIRECTORY}/include/c++/${ARM_GCC_VER}/${ARM_ARCH_DIRECTORY}/)
        include_directories(/usr/${ARM_ARCH_DIRECTORY}/include/c++/${ARM_GCC_VER}/)
        include_directories(/usr/${ARM_ARCH_DIRECTORY}/include/)
        if(NOT CMAKE_CXX_FLAGS MATCHES "-march")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=${TARGET_ARCH}")
        endif()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-parameter -Wextra -Wreorder -std=c++11")
    elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "^ppc64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fPIC -mcpu=${TARGET_ARCH} -mtune=${TARGET_ARCH} -Wunused-parameter -Wextra -Wreorder -std=c++11")
    elseif(NOT WIN32)
        if(NOT CMAKE_CXX_FLAGS MATCHES "-march")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=${TARGET_ARCH}")
        endif()
        CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CPP11_FLAG)
        if (ENABLE_XTL_COMPLEX)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fPIC -Wunused-parameter -Wextra -Wreorder -std=c++14")
        elseif (HAS_CPP11_FLAG)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fPIC -Wunused-parameter -Wextra -Wreorder -std=c++11")
        else()
            message(FATAL_ERROR "Unsupported compiler -- jsimd requires C++11 support!")
        endif()
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /MP /bigobj")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2")
    set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES Clang AND WIN32) # We are using clang-cl
    add_compile_options(/EHsc /bigobj)
    set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
endif()

if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
    if(DOWNLOAD_GTEST)
        # Download and unpack googletest at configure time
        configure_file(downloadGTest.cmake.in googletest-download/CMakeLists.txt)
    else()
        # Copy local source of googletest at configure time
        configure_file(copyGTest.cmake.in googletest-download/CMakeLists.txt)
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                     ${CMAKE_CURRENT_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL)

    set(GTEST_INCLUDE_DIRS "${gtest_SOURCE_DIR}/include")
    add_library(GTest::GTest INTERFACE IMPORTED)
    target_link_libraries(GTest::GTest INTERFACE gtest)
    add_library(GTest::Main INTERFACE IMPORTED)
    target_link_libraries(GTest::Main INTERFACE gtest_main)
else()
    find_package(GTest REQUIRED)
endif()

find_package(Threads)

include_directories(${GTEST_INCLUDE_DIRS})

set(JSIMD_TESTS
    main.cpp
    jsimd_api_test.hpp
    jsimd_api_test.cpp
    jsimd_algorithms.cpp
    jsimd_basic_test.hpp
    jsimd_basic_test.cpp
    jsimd_basic_math_test.hpp
    jsimd_basic_math_test.cpp
    jsimd_complex_basic_test.hpp
    jsimd_complex_tester.hpp
    jsimd_error_gamma_test.hpp
    jsimd_error_gamma_test.cpp
    jsimd_exponential_test.hpp
    jsimd_exponential_test.cpp
    jsimd_cexponential_test.hpp
    jsimd_cexponential_test.cpp
    jsimd_chyperbolic_test.hpp
    jsimd_chyperbolic_test.cpp
    jsimd_cpower_test.hpp
    jsimd_cpower_test.cpp
    jsimd_ctrigonometric_test.hpp
    jsimd_ctrigonometric_test.cpp
    jsimd_fp_manipulation_test.hpp
    jsimd_fp_manipulation_test.cpp
    jsimd_hyperbolic_test.hpp
    jsimd_hyperbolic_test.cpp
    jsimd_interface_test.cpp
    jsimd_memory_test.cpp
    jsimd_poly_evaluation_test.cpp
    jsimd_poly_evaluation_test.hpp
    jsimd_power_test.hpp
    jsimd_power_test.cpp
    jsimd_rounding_test.hpp
    jsimd_rounding_test.cpp
    jsimd_tester.hpp
    jsimd_test_utils.hpp
    jsimd_trigonometric_test.hpp
    jsimd_trigonometric_test.cpp
)

add_executable(test_jsimd ${JSIMD_TESTS} ${JSIMD_HEADERS})
target_link_libraries(test_jsimd xsimd GTest::GTest GTest::Main ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(test_jsimd PRIVATE ${JSIMD_INCLUDE_DIR})
add_test(NAME test_jsimd COMMAND test_xsimd)

if(DEFINED JSIMD_FORCE_X86_INSTR_SET)
    message("Forcing JSIMD_FORCE_X86_INSTR_SET to ${JSIMD_FORCE_X86_INSTR_SET}")
    target_compile_definitions(test_jsimd PRIVATE JSIMD_FORCE_X86_INSTR_SET=${JSIMD_FORCE_X86_INSTR_SET})
endif()

if(DEFINED JSIMD_FORCE_X86_AMD_INSTR_SET)
    message("Forcing JSIMD_FORCE_X86_AMD_INSTR_SET to ${JSIMD_FORCE_X86_AMD_INSTR_SET}")
    target_compile_definitions(test_jsimd PRIVATE JSIMD_FORCE_X86_AMD_INSTR_SET=${JSIMD_FORCE_X86_AMD_INSTR_SET})
endif()

if(DEFINED JSIMD_FORCE_PPC_INSTR_SET)
    message("Forcing JSIMD_FORCE_PPC_INSTR_SET to ${JSIMD_FORCE_PPC_INSTR_SET}")
    target_compile_definitions(test_jsimd PRIVATE JSIMD_FORCE_PPC_INSTR_SET=${JSIMD_FORCE_PPC_INSTR_SET})
endif()

if(DEFINED JSIMD_FORCE_ARM_INSTR_SET)
    message("Forcing JSIMD_FORCE_ARM_INSTR_SET to ${JSIMD_FORCE_ARM_INSTR_SET}")
    target_compile_definitions(test_jsimd PRIVATE JSIMD_FORCE_ARM_INSTR_SET=${JSIMD_FORCE_ARM_INSTR_SET})
endif()

if (CROSS_COMPILE_ARM)
    add_custom_target(xtest COMMAND qemu-arm -L /usr/arm-linux-gnueabi/ test_jsimd DEPENDS test_xsimd)
else()
    add_custom_target(xtest COMMAND test_jsimd DEPENDS test_xsimd)
endif()
