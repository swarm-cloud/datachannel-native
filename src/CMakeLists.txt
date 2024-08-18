cmake_minimum_required(VERSION 3.22.1)

project("datachannel_wrapper")

if (NOT ANDROID)
    enable_language(Swift)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

set(PRJ_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")

if (ANDROID)
    set(OPENSSL_ROOT_DIR ${PRJ_ROOT}/android-openssl-cmake/prefix/${CMAKE_ANDROID_ARCH_ABI})
elseif ("${OPENSSL_APPLE_OS_PREFIX}" STREQUAL "macOS")
    set(OPENSSL_ROOT_DIR ${PRJ_ROOT}/OpenSSL-for-macOS/macosx)
else ()
    set(OPENSSL_ROOT_DIR ${PRJ_ROOT}/OpenSSL-for-iPhone)
endif ()
list(APPEND CMAKE_MODULE_PATH ${PRJ_ROOT}/src)
find_package(OpenSSL REQUIRED)

add_subdirectory("${PRJ_ROOT}/libdatachannel" "libdatachannel")

set(sources
        cpp/PeerConnectionImpl.cpp
        cpp/DataChannelImpl.cpp)

if (ANDROID)
    #file(GLOB_RECURSE djinni_src "${PRJ_ROOT}/djinni/support-lib/jni/*.cpp")
    set(djinni_src
            "${PRJ_ROOT}/djinni/support-lib/jni/djinni_main.cpp"
            "${PRJ_ROOT}/djinni/support-lib/jni/djinni_support.cpp"
            )

    file(GLOB_RECURSE generated_src "${PRJ_ROOT}/generated-src/jni/*.cpp")

    list(APPEND sources
            ${djinni_src}
            ${generated_src})
else ()
    set(djinni_src
            "${PRJ_ROOT}/djinni/support-lib/objc/DJIError.mm"
            "${PRJ_ROOT}/djinni/support-lib/objc/DJIProxyCaches.mm"
            )

    file(GLOB_RECURSE generated_src
            "${PRJ_ROOT}/generated-src/objc/*.mm")

    file(GLOB public_headers
            "${PRJ_ROOT}/generated-src/objc/DCCandidateCallback.h"
            "${PRJ_ROOT}/generated-src/objc/DCCertificateType.h"
            "${PRJ_ROOT}/generated-src/objc/DCConfiguration.h"
            "${PRJ_ROOT}/generated-src/objc/DCDataChannel.h"
            "${PRJ_ROOT}/generated-src/objc/DCDataChannelInit.h"
            "${PRJ_ROOT}/generated-src/objc/DCDcCallback.h"
            "${PRJ_ROOT}/generated-src/objc/DCDcErrorCallback.h"
            "${PRJ_ROOT}/generated-src/objc/DCDcEvent.h"
            "${PRJ_ROOT}/generated-src/objc/DCDcEventCallback.h"
            "${PRJ_ROOT}/generated-src/objc/DCDcMessageCallback.h"
            "${PRJ_ROOT}/generated-src/objc/DCGatheringState.h"
            "${PRJ_ROOT}/generated-src/objc/DCGatheringStateCallback.h"
            "${PRJ_ROOT}/generated-src/objc/DCIceServer.h"
            "${PRJ_ROOT}/generated-src/objc/DCIceServerRelayType.h"
            "${PRJ_ROOT}/generated-src/objc/DCIceServerType.h"
            "${PRJ_ROOT}/generated-src/objc/DCIceState.h"
            "${PRJ_ROOT}/generated-src/objc/DCIceStateCallback.h"
            "${PRJ_ROOT}/generated-src/objc/DCLogCallback.h"
            "${PRJ_ROOT}/generated-src/objc/DCLogLevel.h"
            "${PRJ_ROOT}/generated-src/objc/DCPeerConnection.h"
            "${PRJ_ROOT}/generated-src/objc/DCProxyServer.h"
            "${PRJ_ROOT}/generated-src/objc/DCProxyServerType.h"
            "${PRJ_ROOT}/generated-src/objc/DCReliability.h"
            "${PRJ_ROOT}/generated-src/objc/DCReliabilityType.h"
            "${PRJ_ROOT}/generated-src/objc/DCSdpCallback.h"
            "${PRJ_ROOT}/generated-src/objc/DCSignalingState.h"
            "${PRJ_ROOT}/generated-src/objc/DCSignalingStateCallback.h"
            "${PRJ_ROOT}/generated-src/objc/DCTransportPolicy.h"
            "${PRJ_ROOT}/generated-src/objc/DCLibVersion.h"
            "${PRJ_ROOT}/src/objc/ObjCExceptions.h"
            "${PRJ_ROOT}/src/objc/datachannel_wrapper.h"
            )

    list(APPEND sources
            ${djinni_src}
            ${generated_src}
            ${public_headers}
            "${PRJ_ROOT}/src/objc/ObjCExceptions.m"
            "${PRJ_ROOT}/src/objc/datachannel_wrapper.swift")
endif ()

add_library(${CMAKE_PROJECT_NAME} SHARED ${sources})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        "${PRJ_ROOT}/generated-src/cpp"
        )
target_link_libraries(${CMAKE_PROJECT_NAME}
        OpenSSL::Crypto
        OpenSSL::SSL
        datachannel-static
        )

file(READ "cpp/PeerConnectionImpl.cpp" VER_FILE_CONTENT)
string(REGEX MATCH "\"[0-9]+.[0-9]+.[0-9]+.[0-9]+.*\"" VERSION_NUMBER ${VER_FILE_CONTENT})

if (ANDROID)
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
            "${PRJ_ROOT}/djinni/support-lib/jni"
            )

    target_link_libraries(${CMAKE_PROJECT_NAME}
            android
            log
            )
else ()
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
            FRAMEWORK TRUE
            MACOSX_FRAMEWORK_IDENTIFIER com.cdnbye.libdc
            MACOSX_FRAMEWORK_BUNDLE_VERSION "${VERSION_NUMBER}"
            MACOSX_FRAMEWORK_SHORT_VERSION_STRING "${VERSION_NUMBER}"
            PUBLIC_HEADER "${public_headers}"
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Apple Development"
            XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
            XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO"
            XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS "YES"
            XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC "YES"
            XCODE_ATTRIBUTE_BUILD_LIBRARY_FOR_DISTRIBUTION "YES"
            XCODE_ATTRIBUTE_DEFINES_MODULE "YES"
            XCODE_ATTRIBUTE_SWIFT_VERSION "5.0"
            XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym"
            XCODE_ATTRIBUTE_DYLIB_INSTALL_NAME_BASE "@rpath"
            INSTALL_RPATH "@executable_path/Frameworks;@loader_path/Frameworks"
            )

    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
            "${PRJ_ROOT}/djinni/support-lib/objc"
            )
endif ()
