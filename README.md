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
| nop 0               |  0.001 |  0.003 |  0.002 |  0.026 |  0.056 |  0.881 |
| cat-sync 0          |  0.003 |  0.006 |  0.002 |  0.028 |  0.060 |  0.806 |
| nbody-c 50000000    |  3.310 |  3.763 |  4.684 |  3.752 |  3.391 |  4.083 |
| nbody-cpp 50000000  |  3.221 |  3.817 |  4.957 |  3.762 |  4.020 |  4.029 |
| fannkuch-redux-c 12 | 25.442 | 32.807 | 56.817 | 29.518 | 30.084 | 26.118 |
| mandelbrot-c 15000  |  9.350 | 12.804 | failed | 11.901 | 10.470 | 15.574 |
| binary-trees-c 21   | 15.848 | 12.328 | failed | 13.676 | 17.421 | 17.552 |
