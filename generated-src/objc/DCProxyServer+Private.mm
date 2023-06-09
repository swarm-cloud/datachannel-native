// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#import "DCProxyServer+Private.h"
#import "DCProxyServerType+Private.h"
#import "DJIMarshal+Private.h"
#include <cassert>

namespace djinni_generated {

auto ProxyServer::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::Enum<::libdc::ProxyServerType, DCProxyServerType>::toCpp(obj.type),
            ::djinni::String::toCpp(obj.hostname),
            ::djinni::I16::toCpp(obj.port),
            ::djinni::Optional<std::optional, ::djinni::String>::toCpp(obj.username),
            ::djinni::Optional<std::optional, ::djinni::String>::toCpp(obj.password)};
}

auto ProxyServer::fromCpp(const CppType& cpp) -> ObjcType
{
    return [[DCProxyServer alloc] initWithType:(::djinni::Enum<::libdc::ProxyServerType, DCProxyServerType>::fromCpp(cpp.type))
                                      hostname:(::djinni::String::fromCpp(cpp.hostname))
                                          port:(::djinni::I16::fromCpp(cpp.port))
                                      username:(::djinni::Optional<std::optional, ::djinni::String>::fromCpp(cpp.username))
                                      password:(::djinni::Optional<std::optional, ::djinni::String>::fromCpp(cpp.password))];
}

} // namespace djinni_generated
