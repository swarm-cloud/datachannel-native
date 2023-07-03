#! /usr/bin/env bash

pushd OpenSSL-for-iPhone
rm -rf bin lib
./build-libssl.sh --targets="ios-sim-cross-x86_64 ios-sim-cross-arm64 ios-cross-arm64 tvos-sim-cross-x86_64 tvos-sim-cross-arm64 tvos-cross-arm64"
popd

pushd OpenSSL-for-macOS
rm -rf macosx
OPENSSL_VERSION="1.1.1t" ./scripts/build.sh
popd
