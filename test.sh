#!/usr/bin/env bash

MODE=wasm
SSVMC=~/workspace/ssvm/build/tools/ssvm-aot/ssvmc
SSVMR=~/workspace/ssvm/build/tools/ssvm-aot/ssvmr
LUCETC=thirdparty/lucet/target/release/lucetc
LUCET_WASI=thirdparty/lucet/target/release/lucet-wasi
LUCET_BINDINGS=thirdparty/lucet/lucet-wasi/bindings.json
WAVM=thirdparty/wavm/build/bin/wavm
export WAVM_OBJECT_CACHE_DIR=test/wavm/cache
TIMEFORMAT=%4R

NAME=(
    f32
    f64
    i32
    i64
)

function prepare() {
    mkdir -p test/ssvm
    mkdir -p test/lucet
    mkdir -p test/wavm
    mkdir -p test/v8
    mkdir -p $WAVM_OBJECT_CACHE_DIR
}

function compile() {
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        "$SSVMC" build/"$MODE"/"${NAME[i]}".wasm test/ssvm/"${NAME[i]}".so
        "$LUCETC" build/"$MODE"/"${NAME[i]}".wasm --wasi_exe --opt-level speed --bindings "$LUCET_BINDINGS" -o test/lucet/"${NAME[i]}".so
        "$WAVM" compile --format=precompiled-wasm build/"$MODE"/"${NAME[i]}".wasm test/wavm/"${NAME[i]}".wasm
    done
}

function test_ssvm() {
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="test/ssvm/"${NAME[i]}".log"
        rm -f "$LOG"
        "$SSVMR" test/ssvm/"${NAME[i]}".so "${ARGS[i]}" >"$LOG"
    done
}

function test_lucet() {
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="test/lucet/"${NAME[i]}".log"
        rm -f "$LOG"
        "$LUCET_WASI" test/lucet/"${NAME[i]}".so "${ARGS[i]}" >"$LOG"
    done
}

function test_wavm() {
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="test/wavm/"${NAME[i]}".log"
        rm -f "$LOG"
        "$WAVM" run --precompiled --abi=wasi test/wavm/"${NAME[i]}".wasm "${ARGS[i]}" >"$LOG"
    done
}

function test_v8() {
    for ((i=0; i<"${#NAME[@]}"; ++i)); do
        LOG="test/v8/"${NAME[i]}".log"
        rm -f "$LOG"
        nodejs --experimental-wasi-unstable-preview1 --experimental-wasm-bigint v8/index.js build/"$MODE"/"${NAME[i]}".wasm "${ARGS[i]}" >"$LOG"
    done
}

prepare
compile
test_ssvm
test_lucet
test_wavm
test_v8
