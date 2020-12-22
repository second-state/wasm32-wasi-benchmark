#!/usr/bin/env bash

MODE=wasm
SSVMC=thirdparty/ssvm/build/tools/ssvm/ssvmc
SSVM=thirdparty/ssvm/build/tools/ssvm/ssvm
LUCETC=thirdparty/lucet/target/release/lucetc
LUCET_WASI=thirdparty/lucet/target/release/lucet-wasi
LUCET_BINDINGS=thirdparty/lucet/lucet-wasi/bindings.json
WAVM=thirdparty/wavm/build/bin/wavm
export WAVM_OBJECT_CACHE_DIR=benchmark/wavm/cache
TIMEFORMAT=%4R
COUNT=20

NAME=(
    nop
    cat-sync
    nbody-c
    nbody-cpp
    fannkuch-redux-c
    mandelbrot-c
    mandelbrot-simd-c
    binary-trees-c
    fasta-c
)
ARGS=(
    0
    0
    50000000
    50000000
    12
    15000
    15000
    21
    25000000
)

function prepare() {
    mkdir -p benchmark/native
    mkdir -p benchmark/ssvm
    mkdir -p benchmark/lucet
    mkdir -p benchmark/wavm
    mkdir -p benchmark/wasmer_singlepass
    mkdir -p benchmark/wasmer_cranelift
    mkdir -p benchmark/wasmer_llvm
    mkdir -p benchmark/wasmer_jit
    mkdir -p benchmark/v8
    mkdir -p benchmark/docker
    mkdir -p $WAVM_OBJECT_CACHE_DIR
    dd if=/dev/urandom of=benchmark/random bs=4k count=4k
}

function compile() {
    rm -f benchmark/ssvm/compile.time benchmark/lucet/compile.time benchmark/wavm/compile.time benchmark/wasmer_*/compile.time
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        (time "$SSVMC" --enable-simd build/"$MODE"/"${NAME[i]}".wasm benchmark/ssvm/"${NAME[i]}".so 2>&1) 2>> benchmark/ssvm/compile.time || true
        (time "$LUCETC" build/"$MODE"/"${NAME[i]}".wasm --wasi_exe --opt-level speed --bindings "$LUCET_BINDINGS" -o benchmark/lucet/"${NAME[i]}".so 2>&1) 2>> benchmark/lucet/compile.time || true
        (time "$WAVM" compile --enable simd --format=precompiled-wasm build/"$MODE"/"${NAME[i]}".wasm benchmark/wavm/"${NAME[i]}".wasm 2>&1) 2>> benchmark/wavm/compile.time || true
        (time wasmer compile --enable-simd --singlepass build/"$MODE"/"${NAME[i]}".wasm -o benchmark/wasmer_singlepass/"${NAME[i]}".wjit 2>&1) 2>> benchmark/wasmer_singlepass/compile.time || true
        (time wasmer compile --enable-simd --cranelift build/"$MODE"/"${NAME[i]}".wasm -o benchmark/wasmer_cranelift/"${NAME[i]}".wjit 2>&1) 2>> benchmark/wasmer_cranelift/compile.time || true
        (time wasmer compile --enable-simd --llvm build/"$MODE"/"${NAME[i]}".wasm -o benchmark/wasmer_llvm/"${NAME[i]}".wjit 2>&1) 2>> benchmark/wasmer_llvm/compile.time || true
    done
}

function benchmark_native() {
    echo benchmark_native
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/native/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<$COUNT; ++j)); do
            time "build/native/${NAME[i]}" "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
        /usr/bin/time -o "benchmark/native/"${NAME[i]}".time" --verbose "build/native/${NAME[i]}" "${ARGS[i]}" <benchmark/random >&/dev/null
    done
}

function benchmark_ssvm() {
    echo benchmark_ssvm
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/ssvm/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<$COUNT; ++j)); do
            time "$SSVM" --enable-simd benchmark/ssvm/"${NAME[i]}".so "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
        /usr/bin/time -o "benchmark/ssvm/"${NAME[i]}".time" --verbose "$SSVM" --enable-simd benchmark/ssvm/"${NAME[i]}".so "${ARGS[i]}" <benchmark/random >&/dev/null
    done
}

function benchmark_lucet() {
    echo benchmark_lucet
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/lucet/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<$COUNT; ++j)); do
            time "$LUCET_WASI" benchmark/lucet/"${NAME[i]}".so "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
        /usr/bin/time -o "benchmark/lucet/"${NAME[i]}".time" --verbose "$LUCET_WASI" benchmark/lucet/"${NAME[i]}".so "${ARGS[i]}" <benchmark/random >&/dev/null
    done
}

function benchmark_wavm() {
    echo benchmark_wavm
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/wavm/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<$COUNT; ++j)); do
            time "$WAVM" run --enable simd --precompiled --abi=wasi benchmark/wavm/"${NAME[i]}".wasm "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
        /usr/bin/time -o "benchmark/wavm/"${NAME[i]}".time" --verbose "$WAVM" run --precompiled --abi=wasi benchmark/wavm/"${NAME[i]}".wasm "${ARGS[i]}" <benchmark/random >&/dev/null
    done
}

function benchmark_wasmer_singlepass() {
    echo benchmark_wasmer_singlepass
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/wasmer_singlepass/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<$COUNT; ++j)); do
            time wasmer run benchmark/wasmer_singlepass/"${NAME[i]}".wjit "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
        /usr/bin/time -o "benchmark/wasmer_singlepass/"${NAME[i]}".time" --verbose wasmer run benchmark/wasmer_singlepass/"${NAME[i]}".wjit "${ARGS[i]}" <benchmark/random >&/dev/null
    done
}

function benchmark_wasmer_cranelift() {
    echo benchmark_wasmer_cranelift
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/wasmer_cranelift/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<$COUNT; ++j)); do
            time wasmer run benchmark/wasmer_cranelift/"${NAME[i]}".wjit "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
        /usr/bin/time -o "benchmark/wasmer_cranelift/"${NAME[i]}".time" --verbose wasmer run benchmark/wasmer_cranelift/"${NAME[i]}".wjit "${ARGS[i]}" <benchmark/random >&/dev/null
    done
}

function benchmark_wasmer_llvm() {
    echo benchmark_wasmer_llvm
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/wasmer_llvm/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<$COUNT; ++j)); do
            time wasmer run benchmark/wasmer_llvm/"${NAME[i]}".wjit "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
        /usr/bin/time -o "benchmark/wasmer_llvm/"${NAME[i]}".time" --verbose wasmer run benchmark/wasmer_llvm/"${NAME[i]}".wjit "${ARGS[i]}" <benchmark/random >&/dev/null
    done
}

function benchmark_wasmer_jit() {
    echo benchmark_wasmer_jit
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/wasmer_jit/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<$COUNT; ++j)); do
            time wasmer run --jit build/"$MODE"/"${NAME[i]}".wasm "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
        /usr/bin/time -o "benchmark/wasmer_jit/"${NAME[i]}".time" --verbose wasmer run --jit build/"$MODE"/"${NAME[i]}".wasm "${ARGS[i]}" <benchmark/random >&/dev/null
    done
}

function benchmark_v8() {
    echo benchmark_v8
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/v8/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<$COUNT; ++j)); do
            time nodejs --experimental-wasi-unstable-preview1 --experimental-wasm-bigint v8/index.js build/"$MODE"/"${NAME[i]}".wasm "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
        /usr/bin/time -o "benchmark/v8/"${NAME[i]}".time" --verbose nodejs --experimental-wasi-unstable-preview1 --experimental-wasm-bigint v8/index.js build/"$MODE"/"${NAME[i]}".wasm "${ARGS[i]}" <benchmark/random >&/dev/null
    done
}

function benchmark_docker() {
    echo benchmark_docker
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/docker/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<$COUNT; ++j)); do
            time docker run --rm -a stdin -a stdout -a stderr wasm-benchmark/"${NAME[i]}" /root/"${NAME[i]}" "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
        /usr/bin/time -o "benchmark/docker/"${NAME[i]}".time" --verbose docker run --rm -a stdin -a stdout -a stderr wasm-benchmark/"${NAME[i]}" /root/"${NAME[i]}" "${ARGS[i]}" <benchmark/random >&/dev/null
    done
}

function print_result() {
    for name in "${NAME[@]}"; do
        echo -n ,"$name"
    done
    echo
    for type in native ssvm lucet wavm wasmer_singlepass wasmer_cranelift wasmer_llvm wasmer_jit v8 docker; do
    #for type in ssvm; do
        echo -n "$type"
        for name in "${NAME[@]}"; do
            echo -n ,"$(awk 'function abs(x){return ((x < 0.0) ? -x : x)} {sum+=$0; sumsq+=($0)^2} END {mean = sum / NR; error = sqrt(abs(sumsq / NR - mean^2)); printf("%.3f(%.3f)", mean, error)}' benchmark/"$type"/"$name".log)"
        done
        echo
    done | tee result.csv
}

prepare
compile
benchmark_native
benchmark_ssvm
benchmark_lucet
benchmark_wavm
benchmark_wasmer_singlepass
benchmark_wasmer_cranelift
benchmark_wasmer_llvm
benchmark_wasmer_jit
benchmark_v8
benchmark_docker
print_result
