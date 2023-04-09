cmake_minimum_required(VERSION 3.22.1)

project("datachannel_jni")

set(PRJ_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../../")

add_subdirectory("${PRJ_ROOT}/libdatachannel" "libdatachannel")

file(GLOB_RECURSE djinni_src "${PRJ_ROOT}/djinni/support-lib/jni/*.cpp")
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
        datachannel
        )

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        EXPERIMENTAL_AUTO_CPP_THREAD_ATTACH
        )
