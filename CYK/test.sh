#!/bin/bash

git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
./TestSerialization
cd ..
rm -rf build
