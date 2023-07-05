#! /usr/bin/env bash

set -e

VERSION=$(grep -E ".*LibVersion::version.*\"" src/cpp/PeerConnectionImpl.cpp)
VERSION=$(echo ${VERSION} | cut -d " " -f 5 | cut -d "\"" -f 2)

./gradlew clean :data-channel-android:assembleRelease

INSTALL_DIR=~/Downloads/libdc-Android-${VERSION}

mkdir -p ${INSTALL_DIR}

cp data-channel-android/build/outputs/aar/data-channel-android-release.aar \
    ${INSTALL_DIR}/

cp -r data-channel-android/build/intermediates/cmake/release/obj ${INSTALL_DIR}/symbols

pushd ~/Downloads/
zip -r ${INSTALL_DIR}.zip libdc-Android-${VERSION}
popd
rm -rf ${INSTALL_DIR}
