// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#pragma once

#include "LogCallback.hpp"
#include "djinni_support.hpp"

namespace djinni_generated {

class NativeLogCallback final : ::djinni::JniInterface<::libdc::LogCallback, NativeLogCallback> {
public:
    using CppType = std::shared_ptr<::libdc::LogCallback>;
    using CppOptType = std::shared_ptr<::libdc::LogCallback>;
    using JniType = jobject;

    using Boxed = NativeLogCallback;

    ~NativeLogCallback();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeLogCallback>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeLogCallback>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeLogCallback();
    friend ::djinni::JniClass<NativeLogCallback>;
    friend ::djinni::JniInterface<::libdc::LogCallback, NativeLogCallback>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::libdc::LogCallback
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        void onLog(::libdc::LogLevel level, const std::string & message) override;

    private:
        friend ::djinni::JniInterface<::libdc::LogCallback, ::djinni_generated::NativeLogCallback>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("com/cdnbye/libdc/LogCallback") };
    const jmethodID method_onLog { ::djinni::jniGetMethodID(clazz.get(), "onLog", "(Lcom/cdnbye/libdc/LogLevel;Ljava/lang/String;)V") };
};

} // namespace djinni_generated