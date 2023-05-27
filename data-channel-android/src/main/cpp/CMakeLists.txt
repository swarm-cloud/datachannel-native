cmake_minimum_required(VERSION 3.22.1)

project("datachannel_jni")

set(PRJ_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../..")

set(OPENSSL_ROOT_DIR ${PRJ_ROOT}/android-openssl-cmake/prefix/${CMAKE_ANDROID_ARCH_ABI})
list(APPEND CMAKE_MODULE_PATH ${PRJ_ROOT}/android-openssl-cmake)
find_package(OpenSSL REQUIRED)
add_subdirectory("${PRJ_ROOT}/libdatachannel" "libdatachannel")

#file(GLOB_RECURSE djinni_src "${PRJ_ROOT}/djinni/support-lib/jni/*.cpp")
set(djinni_src
        "${PRJ_ROOT}/djinni/support-lib/jni/djinni_main.cpp"
        "${PRJ_ROOT}/djinni/support-lib/jni/djinni_support.cpp"
        )
file(GLOB_RECURSE generated_src "${PRJ_ROOT}/generated-src/jni/*.cpp")

add_library(${CMAKE_PROJECT_NAME} SHARED
        #libdc.cpp
        PeerConnectionImpl.cpp
        DataChannelImpl.cpp

        ${djinni_src}
        ${generated_src}
        )

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        "${PRJ_ROOT}/djinni/support-lib/jni"
        "${PRJ_ROOT}/generated-src/cpp"
        )

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        OpenSSL::Crypto
        OpenSSL::SSL
        datachannel-static
        )
