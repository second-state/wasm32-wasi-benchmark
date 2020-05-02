# wasm-benchmark

wasm32-wasi benchmarks

all benchmarking C/C++ source are comming from [The Computer Langeuage Benchmarks Game](https://benchmarksgame-team.pages.debian.net/benchmarksgame/index.html).

# Requirement

* [Clang 9](https://clang.llvm.org/)
* [LLD 9](https://lld.llvm.org/)
* [emscripten](https://github.com/emscripten-core/emsdk)

# Recent Benchmark Results

Runs on Intel(R) Xeon(R) CPU E5-2673 v4 @ 2.30GHz, Linux 5.3.0-1016-azure

|                     | native | ssvm   | lucet  | WAVM   | node13 |
| ------------------- | ------ | ------ | ------ | ------ | ------ |
| nbody-c 50000000    | 3.268  | 3.165  | 18.894 | 6.494  | 9.811  |
| nbody-cpp 50000000  | 3.169  | 5.248  | 23.704 | 13.257 | 16.135 |
| fannkuch-redux-c 12 | 23.723 | 37.472 | 70.879 | 34.770 | 31.378 |
| mandelbrot-c 15000  | 9.436  | 10.362 | 29.171 | 12.088 | 18.081 |
| binary-trees-c 18   | 1.519  | 1.328  | 2.910  | 1.612  | 2.002  |
