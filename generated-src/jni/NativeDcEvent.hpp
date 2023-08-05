// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#pragma once

#include "DcEvent.hpp"
#include "djinni_support.hpp"

namespace djinni_generated {

class NativeDcEvent final : ::djinni::JniEnum {
public:
    using CppType = ::libdc::DcEvent;
    using JniType = jobject;

    using Boxed = NativeDcEvent;

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return static_cast<CppType>(::djinni::JniClass<NativeDcEvent>::get().ordinal(jniEnv, j)); }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, CppType c) { return ::djinni::JniClass<NativeDcEvent>::get().create(jniEnv, static_cast<jint>(c)); }

private:
    NativeDcEvent() : JniEnum("com/cdnbye/libdc/DcEvent") {}
    friend ::djinni::JniClass<NativeDcEvent>;
};

} // namespace djinni_generated