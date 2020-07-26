# wasm-benchmark

wasm32-wasi benchmarks

all benchmarking C/C++ source are comming from [The Computer Langeuage Benchmarks Game](https://benchmarksgame-team.pages.debian.net/benchmarksgame/index.html).

# Requirement

Use the `configure.sh` to install the following dependencies for this benchmark.
Or you can follow the installation intructions from these website to setup your working environment.

* [Clang 10](https://clang.llvm.org/)
* [LLD 10](https://lld.llvm.org/)
* [emscripten](https://github.com/emscripten-core/emsdk)
* [nodejs v14.3.0](https://nodejs.org/en/)
* [docker >v19.03.8](https://www.docker.com/)

# Recent Benchmark Results

Runs on Intel(R) Xeon(R) CPU E5-2673 v4 @ 2.30GHz, Linux 5.4.0-1010-azure

|                     | native |  ssvm  |  lucet |  WAVM  | node14 | docker |
| ------------------- | -----: | -----: | -----: | -----: | -----: | -----: |
| nop 0               |  0.001 |  0.005 |  0.002 |  0.024 |  0.059 |  0.724 |
| cat-sync 0          |  0.003 |  0.008 |  0.002 |  0.027 |  0.061 |  0.656 |
| nbody-c 50000000    |  3.282 |  3.772 |  4.650 |  3.708 |  3.334 |  3.919 |
| nbody-cpp 50000000  |  3.197 |  3.800 |  4.967 |  3.384 |  3.984 |  3.859 |
| fannkuch-redux-c 12 | 25.330 | 28.844 | 69.844 | 30.594 | 29.631 | 26.021 |
| mandelbrot-c 15000  |  9.341 | 12.946 | failed | 12.032 | 10.346 | 15.719 |
| binary-trees-c 21   | 16.434 | 12.088 | failed | 13.659 | 16.583 | 17.052 |
| fasta 25000000      |  1.650 |  2.466 | 10.998 |  2.158 |  4.283 | 26.731 |
