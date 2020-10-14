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

Runs on Intel(R) Xeon(R) CPU E5-2673 v4 @ 2.30GHz, beststeve-dev 5.4.0-1026-azure

| compile time        | ssvm   | lucet | WAVM  | WasmerSinglePass | WasmerCranelift | WasmerLLVM |
| ------------------- | -----: | ----: | ----: | ---------------: | --------------: | ---------: |
| nop 0               | 0.383  | 0.105 | 0.158 | 0.013            | 0.016           | 0.115      |
| cat-sync 0          | 0.488  | 0.151 | 0.209 | 0.014            | 0.018           | 0.129      |
| nbody-c 50000000    | 1.792  | 0.741 | 1.061 | 0.023            | 0.074           | 1.047      |
| nbody-cpp 50000000  | 34.610 | 2.400 | 4.273 | 0.042            | 0.130           | 1.243      |
| fannkuch-redux-c 12 | 2.079  | 0.739 | 1.025 | 0.027            | 0.075           | 1.015      |
| mandelbrot-c 15000  | 1.790  | 0.755 | 1.110 | 0.021            | 0.078           | 1.046      |
| binary-trees-c 21   | 1.710  | 0.734 | 1.067 | 0.022            | 0.076           | 1.043      |
| fasta 25000000      | 0.486  | 0.126 | 0.196 | 0.014            | 0.016           | 0.118      |

| execution time      | native | ssvm   | lucet  | WAVM   | WasmerSinglePass | WasmerCranelift | WasmerLLVM | WasmerJIT | node14 | docker |
| ------------------- | -----: | -----: | -----: | -----: | ---------------: | --------------: | ---------: | --------: | -----: | -----: |
| nop 0               | 0.001  | 0.006  | 0.006  | 0.032  | 0.007            | 0.006           | 0.007      | 0.007     | 0.062  | 0.667  |
| cat-sync 0          | 0.003  | 0.010  | 0.006  | 0.029  | 0.011            | 0.012           | 0.011      | 0.011     | 0.063  | 0.662  |
| nbody-c 50000000    | 3.266  | 3.721  | 4.628  | 3.680  | 13.234           | 5.183           | 6.838      | 5.182     | 3.332  | 3.902  |
| nbody-cpp 50000000  | 3.198  | 3.787  | 4.930  | 3.355  | 12.948           | 5.273           | 6.777      | 5.270     | 3.965  | 3.854  |
| fannkuch-redux-c 12 | 25.242 | 35.971 | 69.632 | 30.355 | 77.387           | 95.042          | 30.019     | 80.316    | 29.366 | 25.776 |
| mandelbrot-c 15000  | 9.275  | 12.465 | failed | 11.901 | 45.091           | 17.642          | 13.708     | 17.668    | 10.275 | 15.523 |
| binary-trees-c 21   | 16.279 | 11.683 | failed | 13.707 | 29.487           | 29.564          | 13.939     | 29.585    | 16.500 | 17.040 |
| fasta 25000000      | 1.653  | 2.387  | 12.068 | 2.127  | 5.935            | 5.667           | 2.282      | 5.662     | 4.249  | 25.317 |

Runs on ARM Neoverse N1, Linux 5.4.0-1020-aws

|                     | native |  ssvm  |  WAVM  | node14 | docker |
| ------------------- | -----: | -----: | -----: | -----: | -----: |
| nop 0               |  0.000 |  0.005 |  0.019 |  0.057 |  0.418 |
| cat-sync 0          |  0.003 |  0.009 |  0.023 |  0.061 |  0.435 |
| nbody-c 50000000    |  5.250 |  5.293 |  5.394 |  4.874 |  5.659 |
| nbody-cpp 50000000  |  5.438 |  5.572 |  5.415 |  5.557 |  5.866 |
| fannkuch-redux-c 12 | 32.743 | 33.804 | 33.774 | 54.213 | 33.167 |
| mandelbrot-c 15000  |  9.594 | 12.069 | 11.806 | 14.388 | 10.890 |
| binary-trees-c 21   | 24.048 | 16.273 | 17.445 | 26.081 | 24.569 |
| fasta 25000000      |  1.788 |  1.960 |  2.309 |  3.971 | 15.135 |

Runs on Intel(R) Xeon(R) Platinum 8175M CPU @ 2.50GHz Linnux 5.4.0-1021-aws

|                     | native |  ssvm  |  lucet |  WAVM  | node14 | docker |
| ------------------- | -----: | -----: | -----: | -----: | -----: | -----: |
| nop 0               |  0.001 |  0.013 | failed |  0.020 | failed |  0.441 |
| cat-sync 0          |  0.003 |  0.014 | failed |  0.020 | failed |  0.449 |
| nbody-c 50000000    |  3.406 |  3.846 | failed |  3.823 | failed |  3.864 |
| nbody-cpp 50000000  |  3.439 |  3.970 | failed |  3.780 | failed |  3.913 |
| fannkuch-redux-c 12 | 35.343 | 37.982 | failed | 36.095 | failed | 35.922 |
| mandelbrot-c 15000  |  9.670 | 10.747 | failed |  9.777 | failed | 10.962 |
| binary-trees-c 21   | 16.478 | 13.122 | failed | 14.906 | failed | 16.176 |
| fasta 25000000      |  1.925 |  2.628 | failed |  2.276 | failed | 15.417 |

Runs on AMD EPYC 7571 Linnux 5.4.0-1021-aws

|                     | native |  ssvm  |  lucet |  WAVM  | node14 | docker |
| ------------------- | -----: | -----: | -----: | -----: | -----: | -----: |
| nop 0               |  0.001 |  0.013 | failed |  0.021 | failed |  0.493 |
| cat-sync 0          |  0.003 |  0.015 | failed |  0.020 | failed |  0.472 |
| nbody-c 50000000    |  4.029 |  5.153 | failed |  5.177 | failed |  4.604 |
| nbody-cpp 50000000  |  4.166 |  4.985 | failed |  4.499 | failed |  4.713 |
| fannkuch-redux-c 12 | 35.639 | 39.349 | failed | 36.565 | failed | 36.238 |
| mandelbrot-c 15000  |  9.396 | 11.446 | failed | 10.521 | failed | 10.521 |
| binary-trees-c 21   | 21.094 | 16.052 | failed | 17.544 | failed | 17.544 |
| fasta 25000000      |  1.942 |  2.478 | failed |  2.354 | failed |  2.354 |
