# wasm-benchmark

wasm32-wasi benchmarks

all benchmarking C/C++ source are comming from [The Computer Langeuage Benchmarks Game](https://benchmarksgame-team.pages.debian.net/benchmarksgame/index.html).

# Requirement

Use the `configure.sh` to install the following dependencies for this benchmark.
Or you can follow the installation intructions from these website to setup your working environment.

* [Clang 11](https://clang.llvm.org/)
* [LLD 11](https://lld.llvm.org/)
* [emscripten](https://github.com/emscripten-core/emsdk)
* [nodejs v14.3.0](https://nodejs.org/en/)
* [docker >v19.03.8](https://www.docker.com/)

# Recent Benchmark Results

Runs on Intel(R) Xeon(R) CPU E5-2673 v4 @ 2.30GHz, beststeve-dev 5.4.0-1026-azure

| compile time      | ssvm  | lucet | WAVM  | WasmerSinglePass | WasmerCranelift | WasmerLLVM |
| ----------------- | ----: | ----: | ----: | ---------------: | --------------: | ---------: |
| nop               | 0.302 | 0.025 | 0.162 | 0.012            | 0.016           | 0.119      |
| cat-sync          | 0.398 | 0.025 | 0.219 | 0.013            | 0.017           | 0.122      |
| nbody-c           | 1.510 | 0.214 | 1.152 | 0.020            | 0.080           | 1.033      |
| nbody-cpp         | 5.840 | 0.259 | 4.396 | 0.046            | 0.118           | 1.402      |
| fannkuch-redux-c  | 1.699 | 0.223 | 1.106 | 0.021            | 0.083           | 1.047      |
| mandelbrot-c      | 1.444 | 0.218 | 1.138 | 0.019            | 0.074           | 1.033      |
| mandelbrot-simd-c | 1.486 | 0.003 | 1.147 | 0.017            | 0.082           | 1.060      |
| binary-trees-c    | 1.458 | 0.216 | 1.153 | 0.020            | 0.078           | 1.090      |
| fasta             | 0.373 | 0.025 | 0.217 | 0.013            | 0.017           | 0.124      |

| execution time          | native | ssvm   | lucet  | WAVM   | WasmerSinglePass | WasmerCranelift | WasmerLLVM | WasmerJIT | node14 | docker |
| ----------------------- | -----: | -----: | -----: | -----: | ---------------: | --------------: | ---------: | --------: | -----: | -----: |
| nop 0                   | 0.001  | 0.007  | 0.006  | 0.017  | 0.005            | 0.005           | 0.005      | 0.006     | 0.060  | 0.698  |
| cat-sync 0              | 0.003  | 0.011  | 0.006  | 0.020  | 0.008            | 0.009           | 0.008      | 0.009     | 0.062  | 0.736  |
| nbody-c 50000000        | 3.318  | 3.752  | 4.629  | 3.670  | 13.212           | 5.163           | 6.838      | 5.166     | 3.345  | 4.004  |
| nbody-cpp 50000000      | 3.164  | 3.738  | 4.919  | 3.340  | 12.933           | 5.271           | 6.764      | 5.269     | 3.969  | 3.897  |
| fannkuch-redux-c 12     | 25.370 | 30.771 | 71.421 | 31.440 | 83.537           | 72.947          | 31.276     | 71.568    | 29.613 | 27.123 |
| mandelbrot-c 15000      | 7.753  | 11.567 | failed | 11.880 | 44.976           | 17.788          | 13.661     | 17.821    | 10.263 | 14.161 |
| mandelbrot-simd-c 15000 | 3.678  | 5.176  | failed | failed | failed           | 5.696           | 13.191     | failed    | failed | 10.619 |
| binary-trees-c 21       | 15.821 | 12.595 | failed | 13.700 | 29.325           | 30.010          | 14.282     | 30.416    | 16.567 | 16.515 |
| fasta 25000000          | 1.567  | 2.116  | 12.265 | 2.167  | 5.573            | 5.727           | 2.120      | 5.735     | 4.271  | 27.263 |

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
