// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#include "NativePeerConnection.hpp"  // my header
#include "Marshal.hpp"
#include "NativeCandidateCallback.hpp"
#include "NativeConfiguration.hpp"
#include "NativeDataChannel.hpp"
#include "NativeDataChannelInit.hpp"
#include "NativeDcCallback.hpp"
#include "NativeGatheringState.hpp"
#include "NativeGatheringStateCallback.hpp"
#include "NativeIceState.hpp"
#include "NativeIceStateCallback.hpp"
#include "NativeLogCallback.hpp"
#include "NativeLogLevel.hpp"
#include "NativeSdpCallback.hpp"
#include "NativeSignalingState.hpp"
#include "NativeSignalingStateCallback.hpp"

namespace djinni_generated {

NativePeerConnection::NativePeerConnection() : ::djinni::JniInterface<::libdc::PeerConnection, NativePeerConnection>("com/cdnbye/libdc/PeerConnection$CppProxy") {}

NativePeerConnection::~NativePeerConnection() = default;


CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        delete reinterpret_cast<::djinni::CppProxyHandle<::libdc::PeerConnection>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1close(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        ref->close();
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1setRemoteDescription(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_sdp)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        ref->setRemoteDescription(::djinni::String::toCpp(jniEnv, j_sdp));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1addRemoteCandidate(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_candidate, jstring j_mid)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        ref->addRemoteCandidate(::djinni::String::toCpp(jniEnv, j_candidate),
                                ::djinni::String::toCpp(jniEnv, j_mid));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1onLocalDescription(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        ref->onLocalDescription(::djinni_generated::NativeSdpCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1onLocalCandidate(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        ref->onLocalCandidate(::djinni_generated::NativeCandidateCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1onStateChange(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        ref->onStateChange(::djinni_generated::NativeIceStateCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1onGatheringStateChange(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        ref->onGatheringStateChange(::djinni_generated::NativeGatheringStateCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1onSignalingStateChange(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        ref->onSignalingStateChange(::djinni_generated::NativeSignalingStateCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1state(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        auto r = ref->state();
        return ::djinni::release(::djinni_generated::NativeIceState::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1gatheringState(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        auto r = ref->gatheringState();
        return ::djinni::release(::djinni_generated::NativeGatheringState::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1signalingState(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        auto r = ref->signalingState();
        return ::djinni::release(::djinni_generated::NativeSignalingState::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1clearStats(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        ref->clearStats();
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jint JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1bytesSent(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        auto r = ref->bytesSent();
        return ::djinni::release(::djinni::I32::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jint JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1bytesReceived(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        auto r = ref->bytesReceived();
        return ::djinni::release(::djinni::I32::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jlong JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1rtt(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        auto r = ref->rtt();
        return ::djinni::release(::djinni::I64::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1onDataChannel(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        ref->onDataChannel(::djinni_generated::NativeDcCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_com_cdnbye_libdc_PeerConnection_00024CppProxy_native_1createDataChannel(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_label, jobject j_init)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::libdc::PeerConnection>(nativeRef);
        auto r = ref->createDataChannel(::djinni::String::toCpp(jniEnv, j_label),
                                        ::djinni_generated::NativeDataChannelInit::toCpp(jniEnv, j_init));
        return ::djinni::release(::djinni_generated::NativeDataChannel::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_com_cdnbye_libdc_PeerConnection_create(JNIEnv* jniEnv, jobject /*this*/, jobject j_config)
{
    try {
        auto r = ::libdc::PeerConnection::create(::djinni_generated::NativeConfiguration::toCpp(jniEnv, j_config));
        return ::djinni::release(::djinni_generated::NativePeerConnection::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_com_cdnbye_libdc_PeerConnection_initLogger(JNIEnv* jniEnv, jobject /*this*/, jobject j_level, jobject j_callback)
{
    try {
        ::libdc::PeerConnection::initLogger(::djinni_generated::NativeLogLevel::toCpp(jniEnv, j_level),
                                            ::djinni_generated::NativeLogCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

} // namespace djinni_generated
