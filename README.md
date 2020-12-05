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
| nop               | 0.336 | 0.024 | 0.184 | 0.012            | 0.018           | 0.155      |
| cat-sync          | 0.458 | 0.025 | 0.222 | 0.016            | 0.020           | 0.148      |
| nbody-c           | 1.669 | 0.229 | 1.148 | 0.019            | 0.074           | 1.262      |
| nbody-cpp         | 6.361 | 0.273 | 4.357 | 0.037            | 0.106           | 1.645      |
| fannkuch-redux-c  | 1.873 | 0.228 | 1.137 | 0.018            | 0.080           | 1.188      |
| mandelbrot-c      | 1.649 | 0.221 | 1.155 | 0.020            | 0.080           | 1.236      |
| mandelbrot-simd-c | 1.690 | 0.003 | 1.137 | 0.018            | 0.075           | 1.276      |
| binary-trees-c    | 1.689 | 0.233 | 1.175 | 0.020            | 0.075           | 1.233      |
| fasta             | 0.412 | 0.027 | 0.208 | 0.012            | 0.016           | 0.151      |

| execution time          | native        | ssvm          | lucet         | WAVM          | WasmerSinglePass | WasmerCranelift | WasmerLLVM    | WasmerJIT      | node14        | docker        |
| ----------------------- | ------------: | ------------: | ------------: | ------------: | ---------------: | --------------: | ------------: | ------------:  | ------------: | ------------: |
| nop                     | 0.001(0.000)  | 0.007(0.001)  | 0.005(0.000)  | 0.016(0.001)  | 0.004(0.000)     | 0.005(0.001)    | 0.004(0.000)  | 0.005(0.001)   | 0.059(0.002)  | 0.694(0.049)  |
| cat-sync                | 0.002(0.001)  | 0.010(0.001)  | 0.005(0.000)  | 0.021(0.001)  | 0.008(0.001)     | 0.008(0.001)    | 0.007(0.001)  | 0.009(0.001)   | 0.064(0.004)  | 0.694(0.033)  |
| nbody-c                 | 3.328(0.030)  | 3.743(0.039)  | 4.644(0.026)  | 3.705(0.044)  | 13.303(0.064)    | 5.185(0.046)    | 6.888(0.111)  | 5.190(0.026)   | 3.343(0.024)  | 3.995(0.065)  |
| nbody-cpp               | 3.194(0.034)  | 3.757(0.040)  | 4.932(0.035)  | 3.366(0.051)  | 13.000(0.051)    | 5.291(0.042)    | 6.858(0.091)  | 5.294(0.044)   | 3.993(0.017)  | 3.877(0.056)  |
| fannkuch-redux-c        | 26.556(0.157) | 31.927(0.071) | 71.164(0.085) | 29.980(0.066) | 87.686(17.928)   | 90.138(18.333)  | 37.736(0.328) | 89.664(20.158) | 29.821(0.124) | 27.213(0.239) |
| mandelbrot-c            | 7.794(0.044)  | 12.486(0.064) | failed        | 11.943(0.058) | 45.236(0.104)    | 17.990(0.044)   | 13.748(0.043) | 17.913(0.111)  | 10.328(0.044) | 14.458(1.281) |
| mandelbrot-simd-c       | 3.706(0.020)  | 4.705(0.022)  | failed        | 4.748(0.032)  | failed           | 5.759(0.041)    | 13.276(0.047) | failed         | failed        | 10.943(0.325) |
| binary-trees-c          | 15.886(0.113) | 12.331(0.255) | failed        | 13.723(0.161) | 29.518(0.238)    | 30.389(0.182)   | 14.787(0.280) | 30.316(0.342)  | 16.685(0.179) | 16.093(1.089) |
| fasta-c                 | 1.571(0.022)  | 2.481(0.030)  | 12.450(0.046) | 2.183(0.016)  | 5.554(0.034)     | 5.787(0.027)    | 2.937(0.020)  | 5.773(0.045)   | 4.314(0.026)  | 28.678(3.433) |

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
