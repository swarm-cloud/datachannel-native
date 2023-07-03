if (NOT TARGET OpenSSL::Crypto)
    add_library(OpenSSL::Crypto STATIC IMPORTED)

    if (ANDROID OR "${OPENSSL_APPLE_OS_PREFIX}" STREQUAL "macOS")
        set_target_properties(OpenSSL::Crypto PROPERTIES
                IMPORTED_LOCATION "${OPENSSL_ROOT_DIR}/lib/libcrypto.a"
                INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_ROOT_DIR}/include"
                INTERFACE_LINK_LIBRARIES ""
                )
    else ()
        set_target_properties(OpenSSL::Crypto PROPERTIES
                IMPORTED_LOCATION "${OPENSSL_ROOT_DIR}/lib/libcrypto-${OPENSSL_APPLE_OS_PREFIX}.a"
                INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_ROOT_DIR}/include"
                INTERFACE_LINK_LIBRARIES ""
                )
    endif ()
endif ()

if (NOT TARGET OpenSSL::SSL)
    add_library(OpenSSL::SSL STATIC IMPORTED)

    if (ANDROID OR "${OPENSSL_APPLE_OS_PREFIX}" STREQUAL "macOS")
        set_target_properties(OpenSSL::SSL PROPERTIES
                IMPORTED_LOCATION "${OPENSSL_ROOT_DIR}/lib/libssl.a"
                INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_ROOT_DIR}/include"
                INTERFACE_LINK_LIBRARIES ""
                )
    else ()
        set_target_properties(OpenSSL::SSL PROPERTIES
                IMPORTED_LOCATION "${OPENSSL_ROOT_DIR}/lib/libssl-${OPENSSL_APPLE_OS_PREFIX}.a"
                INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_ROOT_DIR}/include"
                INTERFACE_LINK_LIBRARIES ""
                )
    endif ()
endif ()
