# wasm-benchmark

wasm32-wasi benchmarks

all benchmarking C/C++ source are comming from [The Computer Langeuage Benchmarks Game](https://benchmarksgame-team.pages.debian.net/benchmarksgame/index.html).

# Requirement

* [Clang 9](https://clang.llvm.org/)
* [LLD 9](https://lld.llvm.org/)
* [emscripten](https://github.com/emscripten-core/emsdk)
* [nodejs v14.3.0](https://nodejs.org/en/)
* [docker v19.03.8](https://www.docker.com/)

# Recent Benchmark Results

Runs on Intel(R) Xeon(R) CPU E5-2673 v4 @ 2.30GHz, Linux 5.4.0-1010-azure

|                     | native |  ssvm  |  lucet |  WAVM  | node14 | docker |
| ------------------- | -----: | -----: | -----: | -----: | -----: | -----: |
| nop 0               |  0.001 |  0.004 |  0.002 |  0.054 |  0.055 |  0.818 |
| cat-sync 0          |  0.003 |  0.006 |  0.577 |  0.032 |  0.066 |  0.826 |
| nbody-c 50000000    |  3.310 |  3.716 |  4.616 |  3.750 |  3.393 |  4.110 |
| nbody-cpp 50000000  |  3.137 |  3.773 |  4.699 |  3.744 |  3.967 |  3.946 |
| fannkuch-redux-c 12 | 23.699 | 27.711 | 52.281 | 28.436 | 29.367 | 24.506 |
| mandelbrot-c 15000  |  9.400 | 11.850 | failed | 11.946 | 10.485 | 16.110 |
| binary-trees-c 21   | 15.691 | 12.917 | failed | 14.825 | 18.776 | 17.148 |
