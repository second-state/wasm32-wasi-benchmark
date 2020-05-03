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
| nop 0               | 0.001  | 0.003  | 0.002  | 0.024  | 0.056  |
| cat-sync 0          | 0.003  | failed | 0.573  | 0.029  | 0.060  |
| nbody-c 50000000    | 3.278  | 3.716  | 4.611  | 3.753  | 3.408  |
| nbody-cpp 50000000  | 3.132  | 3.759  | 4.705  | 3.741  | 3.962  |
| fannkuch-redux-c 12 | 23.616 | 28.060 | 53.104 | 28.477 | 29.285 |
| mandelbrot-c 15000  | 9.391  | 10.347 | 28.970 | 12.072 | 18.062 |
| binary-trees-c 18   | 1.519  | 1.328  | 2.910  | 1.612  | 2.002  |
