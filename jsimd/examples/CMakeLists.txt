cmake_minimum_required(VERSION 3.1)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    project(jsimd-examples)

    find_package(jsimd REQUIRED CONFIG)
    set(JSIMD_INCLUDE_DIR ${jsimd_INCLUDE_DIR})
endif ()

include_directories(${JSIMD_INCLUDE_DIR})

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting examples build type to Release")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
else()
    message(STATUS "Tests build type is ${CMAKE_BUILD_TYPE}")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native -std=c++14")
if(NOT CMAKE_CXX_COMPILER_ID MATCHES Clang) # We are using clang-cl
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
endif()

add_executable(mandelbrot mandelbrot.cpp ${JSIMD_HEADERS})

add_custom_target(xmandelbrot COMMAND mandelbrot DEPENDS mandelbrot)
