// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#include "NativeGatheringStateCallback.hpp"  // my header
#include "NativeGatheringState.hpp"

namespace djinni_generated {

NativeGatheringStateCallback::NativeGatheringStateCallback() : ::djinni::JniInterface<::libdc::GatheringStateCallback, NativeGatheringStateCallback>() {}

NativeGatheringStateCallback::~NativeGatheringStateCallback() = default;

NativeGatheringStateCallback::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativeGatheringStateCallback::JavaProxy::~JavaProxy() = default;

void NativeGatheringStateCallback::JavaProxy::onStateChanged(::libdc::GatheringState c_state) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeGatheringStateCallback>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_onStateChanged,
                           ::djinni::get(::djinni_generated::NativeGatheringState::fromCpp(jniEnv, c_state)));
    ::djinni::jniExceptionCheck(jniEnv);
}

} // namespace djinni_generated
