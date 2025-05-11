#! /usr/bin/env bash

set -e

VERSION=$(grep -E '#define[[:space:]]+LIB_VERSION[[:space:]]+[0-9.]+' src/cpp/PeerConnectionImpl.cpp | \
          sed -E 's/#define[[:space:]]+LIB_VERSION[[:space:]]+([0-9.]+).*/\1/')

#export DEVELOPER_DIR=/Applications/Xcode_14.1.app/Contents/Developer/

rm -rf build/iOS build/iOS-Sim build/tvOS build/tvOS-Sim build/macOS \
    libs/datachannel_wrapper.xcframework

cmake -S src -B build/iOS -G Xcode \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DOPENSSL_APPLE_OS_PREFIX=iOS \
    -DNO_WEBSOCKET=ON -DNO_MEDIA=ON -DNO_EXAMPLES=ON -DNO_TESTS=ON \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=13.0

xcodebuild -quiet -project build/iOS/datachannel_wrapper.xcodeproj \
    -configuration Release \
    -sdk iphoneos \
    -target datachannel_wrapper

cmake -S src -B build/iOS-Sim -G Xcode \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DOPENSSL_APPLE_OS_PREFIX=iOS-Sim \
    -DNO_WEBSOCKET=ON -DNO_MEDIA=ON -DNO_EXAMPLES=ON -DNO_TESTS=ON \
    -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=13.0

xcodebuild -quiet -project build/iOS-Sim/datachannel_wrapper.xcodeproj \
    -configuration Release \
    -sdk iphonesimulator \
    -target datachannel_wrapper

cmake -S src -B build/tvOS -G Xcode \
    -DCMAKE_SYSTEM_NAME=tvOS \
    -DOPENSSL_APPLE_OS_PREFIX=tvOS \
    -DNO_WEBSOCKET=ON -DNO_MEDIA=ON -DNO_EXAMPLES=ON -DNO_TESTS=ON \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=13.0

xcodebuild -quiet -project build/tvOS/datachannel_wrapper.xcodeproj \
    -configuration Release \
    -sdk appletvos \
    -target datachannel_wrapper

cmake -S src -B build/tvOS-Sim -G Xcode \
    -DCMAKE_SYSTEM_NAME=tvOS \
    -DOPENSSL_APPLE_OS_PREFIX=tvOS-Sim \
    -DNO_WEBSOCKET=ON -DNO_MEDIA=ON -DNO_EXAMPLES=ON -DNO_TESTS=ON \
    -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=13.0

xcodebuild -quiet -project build/tvOS-Sim/datachannel_wrapper.xcodeproj \
    -configuration Release \
    -sdk appletvsimulator \
    -target datachannel_wrapper

cmake -S src -B build/macOS -G Xcode \
    -DCMAKE_SYSTEM_NAME=Darwin \
    -DOPENSSL_APPLE_OS_PREFIX=macOS \
    -DNO_WEBSOCKET=ON -DNO_MEDIA=ON -DNO_EXAMPLES=ON -DNO_TESTS=ON \
    -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=10.13

xcodebuild -quiet -project build/macOS/datachannel_wrapper.xcodeproj \
    -configuration Release \
    -sdk macosx \
    -target datachannel_wrapper

xcodebuild -create-xcframework -framework build/iOS/Release-iphoneos/datachannel_wrapper.framework \
  -framework build/iOS-Sim/Release-iphonesimulator/datachannel_wrapper.framework \
  -framework build/tvOS/Release-appletvos/datachannel_wrapper.framework \
  -framework build/tvOS-Sim/Release-appletvsimulator/datachannel_wrapper.framework \
  -framework build/macOS/Release/datachannel_wrapper.framework \
  -output libs/datachannel_wrapper.xcframework

INSTALL_DIR=~/Downloads/libdc-Apple-${VERSION}

mkdir -p ${INSTALL_DIR}/symbols/iOS \
    ${INSTALL_DIR}/symbols/iOS-Sim \
    ${INSTALL_DIR}/symbols/tvOS \
    ${INSTALL_DIR}/symbols/tvOS-Sim \
    ${INSTALL_DIR}/symbols/macOS

cp -R libs/datachannel_wrapper.xcframework ${INSTALL_DIR}/

cp -R build/iOS/Release-iphoneos/datachannel_wrapper.framework.dSYM \
    ${INSTALL_DIR}/symbols/iOS/
cp -R build/iOS-Sim/Release-iphonesimulator/datachannel_wrapper.framework.dSYM \
    ${INSTALL_DIR}/symbols/iOS-Sim/
cp -R build/tvOS/Release-appletvos/datachannel_wrapper.framework.dSYM \
    ${INSTALL_DIR}/symbols/tvOS/
cp -R build/tvOS-Sim/Release-appletvsimulator/datachannel_wrapper.framework.dSYM \
    ${INSTALL_DIR}/symbols/tvOS-Sim/
cp -R build/macOS/Release/datachannel_wrapper.framework.dSYM \
    ${INSTALL_DIR}/symbols/macOS/

pushd ~/Downloads/
zip -ry ${INSTALL_DIR}.zip libdc-Apple-${VERSION}
popd
rm -rf ${INSTALL_DIR}
