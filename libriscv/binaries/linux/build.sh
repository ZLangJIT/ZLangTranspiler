#!/bin/bash
set -e

RISCV_TC=$HOME/riscv
export PATH=$PATH:$RISCV_TC/bin
export CC=$RISCV_TC/bin/riscv32-unknown-linux-gnu-gcc
export CXX=$RISCV_TC/bin/riscv32-unknown-linux-gnu-g++

mkdir -p build
pushd build
cmake ..
make -j4
popd
