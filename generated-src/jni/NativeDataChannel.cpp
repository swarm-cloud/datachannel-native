// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#include "NativeDataChannel.hpp"  // my header
#include "Marshal.hpp"
#include "NativeDcErrorCallback.hpp"
#include "NativeDcEventCallback.hpp"
#include "NativeDcMessageCallback.hpp"

namespace djinni_generated {

NativeDataChannel::NativeDataChannel() : ::djinni::JniInterface<::libdc::DataChannel, NativeDataChannel>("com/cdnbye/libdc/DataChannel$CppProxy") {}

NativeDataChannel::~NativeDataChannel() = default;


CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        delete reinterpret_cast<::djinni::CppProxyHandle<::libdc::DataChannel>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1close(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        ref->close();
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jboolean JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1sendText(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_msg)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        auto r = ref->sendText(::djinni::String::toCpp(jniEnv, j_msg));
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1sendBinary(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_msg)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        auto r = ref->sendBinary(::djinni::Binary::toCpp(jniEnv, j_msg));
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1isOpen(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        auto r = ref->isOpen();
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1isClosed(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        auto r = ref->isClosed();
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jint JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1maxMessageSize(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        auto r = ref->maxMessageSize();
        return ::djinni::release(::djinni::I32::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jint JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1bufferedAmount(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        auto r = ref->bufferedAmount();
        return ::djinni::release(::djinni::I32::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1onOpen(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        ref->onOpen(::djinni_generated::NativeDcEventCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1onClosed(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        ref->onClosed(::djinni_generated::NativeDcEventCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1onError(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        ref->onError(::djinni_generated::NativeDcErrorCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1onMessage(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        ref->onMessage(::djinni_generated::NativeDcMessageCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1onBufferedAmountLow(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        ref->onBufferedAmountLow(::djinni_generated::NativeDcEventCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_DataChannel_00024CppProxy_native_1setBufferedAmountLowThreshold(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jint j_amount)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::DataChannel>(nativeRef);
        ref->setBufferedAmountLowThreshold(::djinni::I32::toCpp(jniEnv, j_amount));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

} // namespace djinni_generated
