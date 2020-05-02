#!/usr/bin/env bash

SSVMC=~/workspace/ssvm/build/tools/ssvm-aot/ssvmc
SSVMR=~/workspace/ssvm/build/tools/ssvm-aot/ssvmr
LUCETC=thirdparty/lucet/target/release/lucetc
LUCET_WASI=thirdparty/lucet/target/release/lucet-wasi
LUCET_BINDINGS=thirdparty/lucet/lucet-wasi/bindings.json
WAVM=thirdparty/wavm/build/bin/wavm
export WAVM_OBJECT_CACHE_DIR=benchmark/wavm/cache
TIMEFORMAT=%4R

NAME=(
    nbody-c
    nbody-cpp
    fannkuch-redux-c
    mandelbrot-c
    binary-trees-c
)
ARGS=(
    50000000
    50000000
    12
    15000
    18
)

function prepare() {
    mkdir -p benchmark/native
    mkdir -p benchmark/ssvm
    mkdir -p benchmark/lucet
    mkdir -p benchmark/wavm
    mkdir -p benchmark/v8
    mkdir -p $WAVM_OBJECT_CACHE_DIR
}

function compile() {
    for ((i=0; i<5; ++i)); do
        "$SSVMC" build/emcc/"${NAME[i]}".wasm benchmark/ssvm/"${NAME[i]}".so
        "$LUCETC" build/emcc/"${NAME[i]}".wasm --wasi_exe --opt-level speed --bindings "$LUCET_BINDINGS" -o benchmark/lucet/"${NAME[i]}".so
        "$WAVM" compile --format=precompiled-wasm build/emcc/"${NAME[i]}".wasm benchmark/wavm/"${NAME[i]}".wasm
    done
}

function benchmark_native() {
    for ((i=0; i<5; ++i)); do
        LOG="benchmark/native/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<10; ++j)); do
            time "build/native/${NAME[i]}" "${ARGS[i]}" >&/dev/null
        done 2> "$LOG"
    done
}

function benchmark_ssvm() {
    for ((i=0; i<5; ++i)); do
        LOG="benchmark/ssvm/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<10; ++j)); do
            time "$SSVMR" benchmark/ssvm/"${NAME[i]}".so "${ARGS[i]}" >&/dev/null
        done 2> "$LOG"
    done
}

function benchmark_lucet() {
    for ((i=0; i<5; ++i)); do
        LOG="benchmark/lucet/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<10; ++j)); do
            time "$LUCET_WASI" benchmark/lucet/"${NAME[i]}".so "${ARGS[i]}" >&/dev/null
        done 2> "$LOG"
    done
}

function benchmark_wavm() {
    for ((i=0; i<5; ++i)); do
        LOG="benchmark/wavm/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<10; ++j)); do
            time "$WAVM" run --precompiled --abi=wasi benchmark/wavm/"${NAME[i]}".wasm "${ARGS[i]}" >&/dev/null
        done 2> "$LOG"
    done
}

function benchmark_v8() {
    for ((i=0; i<5; ++i)); do
        LOG="benchmark/v8/"${NAME[i]}".log"
        rm -f "$LOG"
        touch "$LOG"
        for ((j=0; j<10; ++j)); do
            time nodejs --experimental-wasi-unstable-preview1 --experimental-wasm-bigint v8/index.js build/emcc/"${NAME[i]}".wasm "${ARGS[i]}" >&/dev/null
        done 2> "$LOG"
    done
}

function print_result() {
    for name in "${NAME[@]}"; do
        echo -n ,"$name"
    done
    echo
    for type in native ssvm lucet wavm v8; do
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
print_result
