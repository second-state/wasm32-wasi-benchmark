# wasm-benchmark

wasm32-wasi benchmarks

all benchmarking C/C++ source are comming from [The Computer Langeuage Benchmarks Game](https://benchmarksgame-team.pages.debian.net/benchmarksgame/index.html).

# Requirement

* [Clang 9](https://clang.llvm.org/)
* [LLD 9](https://lld.llvm.org/)
* [emscripten](https://github.com/emscripten-core/emsdk)

# Recent Benchmark Results

Runs on Intel(R) Xeon(R) CPU E5-2673 v4 @ 2.30GHz, Linux 5.3.0-1016-azure

|                     | native | ssvm    | lucet  | WAVM   | node13 |
| ------------------- | ------ | ------- | ------ | ------ | ------ |
| nbody-c 50000000    | 3.449  | 7.5524  | 19.552 | 6.791  | 9.877  |
| nbody-cpp 50000000  | 3.274  | 9.8285  | 23.117 | 12.555 | 16.432 |
| fannkuch-redux-c 12 | 25.052 | 78.8693 | 74.304 | 37.066 | 31.712 |
| mandelbrot-c 15000  | 9.969  | 16.7093 | 30.136 | 12.779 | 18.162 |
| binary-trees-c 18   | 1.575  | 3.2714  | 3.154  | 1.743  | 2.047  |
