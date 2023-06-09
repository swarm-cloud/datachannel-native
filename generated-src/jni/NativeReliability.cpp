// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#include "NativeReliability.hpp"  // my header
#include "Marshal.hpp"
#include "NativeReliabilityType.hpp"

namespace djinni_generated {

NativeReliability::NativeReliability() = default;

NativeReliability::~NativeReliability() = default;

auto NativeReliability::fromCpp(JNIEnv* jniEnv, const CppType& c) -> ::djinni::LocalRef<JniType> {
    const auto& data = ::djinni::JniClass<NativeReliability>::get();
    auto r = ::djinni::LocalRef<JniType>{jniEnv->NewObject(data.clazz.get(), data.jconstructor,
                                                           ::djinni::get(::djinni_generated::NativeReliabilityType::fromCpp(jniEnv, c.type)),
                                                           ::djinni::get(::djinni::Bool::fromCpp(jniEnv, c.unordered)),
                                                           ::djinni::get(::djinni::I64::fromCpp(jniEnv, c.rexmit_ms)))};
    ::djinni::jniExceptionCheck(jniEnv);
    return r;
}

auto NativeReliability::toCpp(JNIEnv* jniEnv, JniType j) -> CppType {
    ::djinni::JniLocalScope jscope(jniEnv, 4);
    assert(j != nullptr);
    const auto& data = ::djinni::JniClass<NativeReliability>::get();
    return {::djinni_generated::NativeReliabilityType::toCpp(jniEnv, jniEnv->GetObjectField(j, data.field_mType)),
            ::djinni::Bool::toCpp(jniEnv, jniEnv->GetBooleanField(j, data.field_mUnordered)),
            ::djinni::I64::toCpp(jniEnv, jniEnv->GetLongField(j, data.field_mRexmitMs))};
}

} // namespace djinni_generated
