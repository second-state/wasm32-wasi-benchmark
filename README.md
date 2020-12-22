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
| nop               | 0.312 | 0.025 | 0.183 | 0.018            | 0.017           | 0.143      |
| cat-sync          | 0.417 | 0.025 | 0.216 | 0.013            | 0.015           | 0.151      |
| nbody-c           | 1.450 | 0.219 | 1.121 | 0.019            | 0.075           | 1.264      |
| nbody-cpp         | 5.957 | 0.260 | 4.293 | 0.039            | 0.127           | 1.622      |
| fannkuch-redux-c  | 1.735 | 0.224 | 1.191 | 0.019            | 0.077           | 1.222      |
| mandelbrot-c      | 1.440 | 0.235 | 1.163 | 0.060            | 0.094           | 1.261      |
| mandelbrot-simd-c | 1.498 | 0.003 | 1.119 | 0.011            | 0.074           | 1.219      |
| binary-trees-c    | 1.464 | 0.220 | 1.143 | 0.019            | 0.083           | 1.267      |
| fasta             | 0.393 | 0.026 | 0.196 | 0.014            | 0.016           | 0.149      |

| execution time          | native        | ssvm          | lucet         | WAVM          | WasmerSinglePass | WasmerCranelift | WasmerLLVM    | WasmerJIT      | node14        | docker        |
| ----------------------- | ------------: | ------------: | ------------: | ------------: | ---------------: | --------------: | ------------: | ------------:  | ------------: | ------------: |
| nop                     | 0.001(0.000)  | 0.024(0.001)  | 0.005(0.001)  | 0.017(0.002)  | 0.005(0.000)     | 0.005(0.001)    | 0.005(0.001)  | 0.006(0.003)   | 0.059(0.002)  | 0.636(0.045)  |
| cat-sync                | 0.002(0.001)  | 0.031(0.001)  | 0.516(0.005)  | 0.021(0.001)  | 0.009(0.001)     | 0.008(0.001)    | 0.009(0.001)  | 0.009(0.003)   | 0.062(0.002)  | 0.654(0.019)  |
| nbody-c                 | 3.305(0.022)  | 3.758(0.028)  | 4.660(0.071)  | 3.696(0.034)  | 13.282(0.053)    | 5.184(0.038)    | 6.827(0.046)  | 5.189(0.057)   | 3.367(0.076)  | 3.966(0.039)  |
| nbody-cpp               | 3.174(0.029)  | 3.880(0.021)  | 4.926(0.017)  | 3.357(0.020)  | 13.022(0.116)    | 5.276(0.028)    | 6.796(0.058)  | 5.300(0.061)   | 3.987(0.021)  | 3.872(0.066)  |
| fannkuch-redux-c        | 26.376(0.164) | 30.951(0.213) | 71.827(0.253) | 29.988(0.193) | 87.801(18.016)   | 88.047(18.461)  | 37.642(0.190) | 87.789(20.509) | 29.894(0.441) | 27.208(0.158) |
| mandelbrot-c            | 7.734(0.037)  | 12.131(0.265) | failed        | 12.012(0.155) | 45.325(0.251)    | 17.913(0.122)   | 13.814(0.132) | 17.901(0.126)  | 10.314(0.118) | 14.587(1.307) |
| mandelbrot-simd-c       | 3.675(0.021)  | 4.868(0.086)  | failed        | 4.756(0.045)  | failed           | 5.710(0.024)    | 13.287(0.127) | failed         | failed        | 10.384(0.541) |
| binary-trees-c          | 15.706(0.122) | 12.532(0.261) | failed        | 14.419(0.158) | 29.458(0.291)    | 30.366(0.316)   | 14.674(0.223) | 30.790(0.285)  | 16.726(0.143) | 16.616(1.246) |
| fasta-c                 | 1.569(0.016)  | 2.191(0.027)  | 12.427(0.096) | 2.184(0.026)  | 5.602(0.112)     | 5.762(0.031)    | 2.898(0.016)  | 5.763(0.049)   | 4.293(0.032)  | 28.638(3.380) |

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
