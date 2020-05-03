#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

function check_cmake() {
    if ! cmake --version >/dev/null; then
        echo "cmake required!"
        exit 1
    fi
}

function check_clang() {
    if ! clang-9 --version >/dev/null; then
        echo "clang-9 required!"
        exit 1
    fi
    if ! clang++-9 --version >/dev/null; then
        echo "clang++-9 required!"
        exit 1
    fi
}

function check_git() {
    if ! git --version >/dev/null; then
        echo "git required!"
        exit 1
    fi
}

function check_rustup() {
    if ! rustup --version>/dev/null; then
        echo "rustup required!"
        exit 1
    fi
}

function prepare_emcc() {
    if [ -e thirdparty/emsdk/.git ]; then
        pushd thirdparty/emsdk
        git fetch -a
        git reset --hard origin/HEAD
        ./emsdk install latest
        ./emsdk activate latest
        popd
    else
        git clone --depth 1 https://github.com/emscripten-core/emsdk.git thirdparty/emsdk
        pushd thirdparty/emsdk
        ./emsdk install latest
        ./emsdk activate latest
        popd
    fi
}

function prepare_lucet() {
    if [ -e thirdparty/lucet/.git ]; then
        pushd thirdparty/lucet
        git fetch -a
        git reset --hard origin/HEAD
        git submodule update --init --recursive
        make build
        popd
    else
        git clone --depth 1 https://github.com/bytecodealliance/lucet.git thirdparty/lucet
        pushd thirdparty/lucet
        git submodule update --init --recursive
        make build
        popd
    fi
}

function prepare_wavm() {
    if [ -e thirdparty/wavm/.git ]; then
        pushd thirdparty/wavm
        git fetch -a
        git reset --hard origin/HEAD
        git submodule update --init --recursive
        cmake -B build . -DCMAKE_BUILD_TYPE=Release
        cmake --build build
        popd
    else
        git clone --depth 1 https://github.com/WAVM/WAVM.git thirdparty/wavm
        pushd thirdparty/wavm
        git submodule update --init --recursive
        cmake -B build . -DCMAKE_BUILD_TYPE=Release
        cmake --build build
        popd
    fi
}

function apply_emcc() {
    source thirdparty/emsdk/emsdk_env.sh
}

function invoke_cmake() {
    CC=clang-9 CXX=clang++-9 cmake -B build . -DCMAKE_BUILD_TYPE=Release
    cmake --build build
}

function sed_wasm_module() {
    for i in build/wasm/*.wasm; do
        wasm-dis "$i" -o "$i".wat
        sed -i -e 's@"env" "__wasi_@"wasi_snapshot_preview1" "@' "$i".wat
        wasm-as "$i".wat -g -o "$i"
        rm "$i".wat
    done
}

check_cmake
check_clang
check_git
check_rustup

prepare_lucet
prepare_emcc
prepare_wavm

apply_emcc
invoke_cmake
sed_wasm_module
