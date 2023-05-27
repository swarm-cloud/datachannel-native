#! /usr/bin/env bash

pushd android-openssl-cmake
rm -rf prefix
BUILD_ARCHS="arm_32 arm_64 x86_32 x86_64" ./build-openssl.sh
popd
