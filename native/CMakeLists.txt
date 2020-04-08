# SPDX-License-Identifier: Apache-2.0

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

add_executable(binary-trees-c
  ../src/binary-trees.c
)
