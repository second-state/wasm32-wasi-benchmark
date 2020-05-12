# wasm-benchmark

wasm32-wasi benchmarks

all benchmarking C/C++ source are comming from [The Computer Langeuage Benchmarks Game](https://benchmarksgame-team.pages.debian.net/benchmarksgame/index.html).

# Requirement

* [Clang 9](https://clang.llvm.org/)
* [LLD 9](https://lld.llvm.org/)
* [emscripten](https://github.com/emscripten-core/emsdk)

# Recent Benchmark Results

Runs on Intel(R) Xeon(R) CPU E5-2673 v4 @ 2.30GHz, Linux 5.3.0-1016-azure

|                     | native | ssvm   | lucet  | WAVM   | node13 | docker |
| ------------------- | ------ | ------ | ------ | ------ | ------ | ------ |
| nop 0               | 0.001  | 0.003  | 0.005  | 0.042  | 0.063  | 0.849  |
| cat-sync 0          | 0.003  | 0.007  | 0.580  | 0.027  | 0.062  | 0.826  |
| nbody-c 50000000    | 3.260  | 3.733  | 4.609  | 3.768  | 3.418  | 4.128  |
| nbody-cpp 50000000  | 3.143  | 3.735  | 4.722  | 3.775  | 3.956  | 3.944  |
| fannkuch-redux-c 12 | 23.598 | 29.037 | 52.787 | 28.586 | 29.317 | 24.459 |
| mandelbrot-c 15000  |  9.419 | 11.850 | failed | 11.963 | 10.771 | 16.050 |
| binary-trees-c 21   | 16.292 | 12.977 | failed | 14.803 | 17.671 | 17.191 |
