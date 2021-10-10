#!/bin/sh -ex

git clone -b release-1.10.0 https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake \
    -D CMAKE_BUILD_TYPE="Release" \
    -D CMAKE_INSTALL_PREFIX="$(pwd)/googletest/build/install" \
    -G "Unix Makefiles" \
    ..
cmake --build . --config "Release" -- -j $(nproc)
cmake --install . --config "Release"
