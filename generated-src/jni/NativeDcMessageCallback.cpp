// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#include "NativeDcMessageCallback.hpp"  // my header
#include "Marshal.hpp"

namespace djinni_generated {

NativeDcMessageCallback::NativeDcMessageCallback() : ::djinni::JniInterface<::libdc::DcMessageCallback, NativeDcMessageCallback>() {}

NativeDcMessageCallback::~NativeDcMessageCallback() = default;

NativeDcMessageCallback::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativeDcMessageCallback::JavaProxy::~JavaProxy() = default;

void NativeDcMessageCallback::JavaProxy::onText(const std::string & c_msg) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeDcMessageCallback>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_onText,
                           ::djinni::get(::djinni::String::fromCpp(jniEnv, c_msg)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativeDcMessageCallback::JavaProxy::onBinary(const std::vector<uint8_t> & c_msg) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeDcMessageCallback>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_onBinary,
                           ::djinni::get(::djinni::Binary::fromCpp(jniEnv, c_msg)));
    ::djinni::jniExceptionCheck(jniEnv);
}

} // namespace djinni_generated
