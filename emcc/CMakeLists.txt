# SPDX-License-Identifier: Apache-2.0

function(add_emcc_executable name)
  foreach(l ${ARGN})
    get_filename_component(fp ${l} REALPATH)
    list(APPEND listed ${fp})
  endforeach()

  add_custom_target(emcc-${name} ALL
    emcc -g -Oz --llvm-lto 1 -s STANDALONE_WASM -s INITIAL_MEMORY=32MB -s MAXIMUM_MEMORY=-1 ${listed} -o ${name}
    BYPRODUCTS ${name}
    DEPENDS ${listed}
  )
endfunction()

add_emcc_executable(nop.wasm
  ../src/nop.c
)

add_emcc_executable(cat-sync.wasm
  ../src/cat-sync.c
)

add_emcc_executable(fannkuch-redux-c.wasm
  ../src/fannkuch-redux.c
)

add_emcc_executable(nbody-c.wasm
  ../src/nbody.c
)

add_emcc_executable(nbody-cpp.wasm
  ../src/nbody.cpp
)

add_emcc_executable(mandelbrot-c.wasm
  ../src/mandelbrot.c
)

add_emcc_executable(binary-trees-c.wasm
  ../src/binary-trees.c
)

add_emcc_executable(f32.wasm
  ../spec/f32.c
)

add_emcc_executable(f64.wasm
  ../spec/f64.c
)

add_emcc_executable(i32.wasm
  ../spec/i32.c
)

add_emcc_executable(i64.wasm
  ../spec/i64.c
)
