#!/usr/bin/env bash

MODE=wasm
SSVMC=thirdparty/ssvm/build/tools/ssvm-aot/ssvmc
SSVMR=thirdparty/ssvm/build/tools/ssvm-aot/ssvmr
LUCETC=thirdparty/lucet/target/release/lucetc
LUCET_WASI=thirdparty/lucet/target/release/lucet-wasi
LUCET_BINDINGS=thirdparty/lucet/lucet-wasi/bindings.json
WAVM=thirdparty/wavm/build/bin/wavm
export WAVM_OBJECT_CACHE_DIR=benchmark/wavm/cache
TIMEFORMAT=%4R

NAME=(
    nop
    cat-sync
    nbody-c
    nbody-cpp
    fannkuch-redux-c
    mandelbrot-c
    binary-trees-c
)
ARGS=(
    0
    0
    50000000
    50000000
    12
    15000
    21
)

function prepare() {
    mkdir -p benchmark/native
    mkdir -p benchmark/ssvm
    mkdir -p benchmark/lucet
    mkdir -p benchmark/wavm
    mkdir -p benchmark/v8
    mkdir -p benchmark/docker
    mkdir -p $WAVM_OBJECT_CACHE_DIR
    dd if=/dev/urandom of=benchmark/random bs=4k count=4k
}

function compile() {
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        "$SSVMC" build/"$MODE"/"${NAME[i]}".wasm benchmark/ssvm/"${NAME[i]}".so || true
        "$LUCETC" build/"$MODE"/"${NAME[i]}".wasm --wasi_exe --opt-level speed --bindings "$LUCET_BINDINGS" -o benchmark/lucet/"${NAME[i]}".so || true
        "$WAVM" compile --format=precompiled-wasm build/"$MODE"/"${NAME[i]}".wasm benchmark/wavm/"${NAME[i]}".wasm || true
    done
}

function benchmark_native() {
    echo benchmark_native
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/native/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<10; ++j)); do
            time "build/native/${NAME[i]}" "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
    done
}

function benchmark_ssvm() {
    echo benchmark_ssvm
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/ssvm/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<10; ++j)); do
            time "$SSVMR" benchmark/ssvm/"${NAME[i]}".so "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
    done
}

function benchmark_lucet() {
    echo benchmark_lucet
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/lucet/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<10; ++j)); do
            time "$LUCET_WASI" benchmark/lucet/"${NAME[i]}".so "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
    done
}

function benchmark_wavm() {
    echo benchmark_wavm
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/wavm/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<10; ++j)); do
            time "$WAVM" run --precompiled --abi=wasi benchmark/wavm/"${NAME[i]}".wasm "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
    done
}

function benchmark_v8() {
    echo benchmark_v8
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/v8/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<10; ++j)); do
            time nodejs --experimental-wasi-unstable-preview1 --experimental-wasm-bigint v8/index.js build/"$MODE"/"${NAME[i]}".wasm "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
    done
}

function benchmark_docker() {
    echo benchmark_docker
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="benchmark/docker/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<10; ++j)); do
            time docker run --rm -a stdin -a stdout -a stderr wasm-benchmark/"${NAME[i]}" /root/"${NAME[i]}" "${ARGS[i]}" <benchmark/random >&/dev/null
        done 2> "$LOG"
    done
}

function print_result() {
    for name in "${NAME[@]}"; do
        echo -n ,"$name"
    done
    echo
    for type in native ssvm lucet wavm v8 docker; do
    #for type in ssvm; do
        echo -n "$type"
        for name in "${NAME[@]}"; do
            echo -n ,"$(awk '{total+=$0;++count}END{print total/count}' benchmark/"$type"/"$name".log)"
        done
        echo
    done
}

prepare
compile
benchmark_native
benchmark_ssvm
benchmark_lucet
benchmark_wavm
benchmark_v8
benchmark_docker
print_result
