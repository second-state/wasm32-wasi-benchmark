# SPDX-License-Identifier: Apache-2.0

add_executable(nop
  ../src/nop.c
)

add_executable(cat-sync
  ../src/cat-sync.c
)
add_executable(fannkuch-redux-c
  ../src/fannkuch-redux.c
)

add_executable(nbody-c
  ../src/nbody.c
)
target_link_libraries(nbody-c PUBLIC m)

add_executable(nbody-cpp
  ../src/nbody.cpp
)
target_compile_options(nbody-cpp PUBLIC -fno-exceptions)

add_executable(mandelbrot-c
  ../src/mandelbrot.c
)

add_executable(mandelbrot-simd-c
  ../src/mandelbrot-simd.c
)

add_executable(binary-trees-c
  ../src/binary-trees.c
)

add_executable(fasta-c
  ../src/fasta.c
)

add_executable(f32
  ../spec/f32.c
)
target_link_libraries(f32 PUBLIC m)
add_executable(f64
  ../spec/f64.c
)
target_link_libraries(f64 PUBLIC m)
add_executable(i32
  ../spec/i32.c
)
add_executable(i64
  ../spec/i64.c
)

add_executable(clock
  ../spec/clock.c
)
target_link_libraries(clock PUBLIC rt)

add_executable(fd
  ../spec/fd.c
)
