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

Runs on Intel(R) Xeon(R) CPU E5-2673 v4 @ 2.30GHz, 5.4.0-1031-azure

| compile time      | ssvm  | lucet | WAVM  | WasmerSinglePass | WasmerCranelift | WasmerLLVM |
| ----------------- | ----: | ----: | ----: | ---------------: | --------------: | ---------: |
| nop               | 0.322 | 0.024 | 0.160 | 0.013            | 0.019           | 0.117      |
| cat-sync          | 0.395 | 0.027 | 0.218 | 0.013            | 0.016           | 0.133      |
| nbody-c           | 1.460 | 0.234 | 1.168 | 0.019            | 0.075           | 1.060      |
| nbody-cpp         | 5.927 | 0.273 | 4.309 | 0.042            | 0.145           | 1.380      |
| fannkuch-redux-c  | 1.707 | 0.225 | 1.170 | 0.019            | 0.074           | 1.053      |
| mandelbrot-c      | 1.469 | 0.222 | 1.138 | 0.019            | 0.073           | 1.071      |
| mandelbrot-simd-c | 1.507 | 0.003 | 1.123 | 0.012            | 0.080           | 1.068      |
| binary-trees-c    | 1.419 | 0.229 | 1.170 | 0.019            | 0.088           | 1.065      |
| fasta             | 0.401 | 0.026 | 0.206 | 0.012            | 0.016           | 0.129      |

| execution time          | native        | ssvm          | lucet         | WAVM          | WasmerSinglePass | WasmerCranelift | WasmerLLVM    | WasmerJIT     | node14        | docker        |
| ----------------------- | ------------: | ------------: | ------------: | ------------: | ---------------: | --------------: | ------------: | ------------: | ------------: | ------------: |
| nop 0                   | 0.001(0.000)  | 0.008(0.001)  | 0.005(0.001)  | 0.019(0.006)  | 0.005(0.001)     | 0.005(0.001)    | 0.005(0.000)  | 0.005(0.000)  | 0.061(0.005)  | 0.731(0.112)  |
| cat-sync 0              | 0.003(0.001)  | 0.010(0.001)  | 0.005(0.000)  | 0.020(0.001)  | 0.008(0.000)     | 0.008(0.001)    | 0.008(0.001)  | 0.008(0.001)  | 0.063(0.002)  | 0.688(0.032)  |
| nbody-c 50000000        | 3.426(0.124)  | 3.735(0.036)  | 4.624(0.011)  | 3.697(0.033)  | 13.313(0.043)    | 5.185(0.037)    | 6.835(0.041)  | 5.157(0.023)  | 3.348(0.027)  | 4.027(0.057)  |
| nbody-cpp 50000000      | 3.180(0.016)  | 3.754(0.024)  | 4.947(0.046)  | 3.361(0.030)  | 13.003(0.024)    | 5.287(0.046)    | 6.807(0.056)  | 5.283(0.028)  | 3.982(0.016)  | 3.877(0.081)  |
| fannkuch-redux-c 12     | 26.575(0.138) | 30.922(0.244) | 71.102(0.121) | 31.667(0.194) | 87.746(18.117)   | 93.823(18.911)  | 31.351(0.040) | 68.067(2.660) | 29.802(0.125) | 27.275(0.210) |
| mandelbrot-c 15000      | 7.794(0.037)  | 11.644(0.183) | failed        | 11.968(0.045) | 45.154(0.159)    | 17.873(0.066)   | 13.687(0.031) | 17.890(0.060) | 10.293(0.060) | 14.295(1.743) |
| mandelbrot-simd-c 15000 | 3.697(0.024)  | 5.176(0.023)  | failed        | failed        | failed           | 5.735(0.048)    | 13.259(0.048) | failed        | failed        | 10.545(0.469) |
| binary-trees-c 21       | 15.791(0.133) | 12.435(0.121) | failed        | 13.738(0.142) | 29.471(0.253)    | 30.345(0.293)   | 14.256(0.154) | 30.420(0.371) | 16.629(0.114) | 16.452(1.789) |
| fasta 25000000          | 1.572(0.017)  | 2.127(0.014)  | 12.251(0.047) | 2.198(0.055)  | 5.641(0.090)     | 5.756(0.026)    | 2.132(0.022)  | 5.755(0.023)  | 4.316(0.031)  | 27.551(5.257) |

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
