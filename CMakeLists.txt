# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.9)
project(WAsmBenchmark)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(native)
add_subdirectory(wasm)
add_subdirectory(emcc)
