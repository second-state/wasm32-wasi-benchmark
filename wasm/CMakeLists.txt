# SPDX-License-Identifier: Apache-2.0

set(CMAKE_SYSTEM_PROCESSOR wasm32)
add_compile_options(
  --target=wasm32-wasi
  --sysroot=${CMAKE_CURRENT_SOURCE_DIR}/sysroot
  -fno-exceptions
  -fno-rounding-math
  )
add_link_options(
  --target=wasm32-wasi
  --sysroot=${CMAKE_CURRENT_SOURCE_DIR}/sysroot
  -fno-exceptions
  -resource-dir ${CMAKE_CURRENT_SOURCE_DIR}/sysroot
  -fuse-ld=/usr/bin/wasm-ld-9
  -Wl,--allow-undefined-file=${CMAKE_CURRENT_SOURCE_DIR}/sysroot/share/wasm32-wasi/undefined-symbols.txt
)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

add_executable(nop.wasm
  ../src/nop.c
)

add_executable(cat-sync.wasm
  ../src/cat-sync.c
)

add_executable(fannkuch-redux-c.wasm
  ../src/fannkuch-redux.c
)

add_executable(nbody-c.wasm
  ../src/nbody.c
)
target_link_libraries(nbody-c.wasm PUBLIC m)

add_executable(nbody-cpp.wasm
  ../src/nbody.cpp
)
target_compile_options(nbody-cpp.wasm PUBLIC -fno-exceptions)

add_executable(mandelbrot-c.wasm
  ../src/mandelbrot.c
)

add_executable(binary-trees-c.wasm
  ../src/binary-trees.c
)
