// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#import "DCConfiguration+Private.h"
#import "DCCertificateType+Private.h"
#import "DCIceServer+Private.h"
#import "DCProxyServer+Private.h"
#import "DCTransportPolicy+Private.h"
#import "DJIMarshal+Private.h"
#include <cassert>

namespace djinni_generated {

auto Configuration::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::List<::djinni_generated::IceServer>::toCpp(obj.iceServers),
            ::djinni::Optional<std::optional, ::djinni_generated::ProxyServer>::toCpp(obj.proxyServer),
            ::djinni::Optional<std::optional, ::djinni::String>::toCpp(obj.bindAddress),
            ::djinni::Enum<::libdc::CertificateType, DCCertificateType>::toCpp(obj.certificateType),
            ::djinni::Enum<::libdc::TransportPolicy, DCTransportPolicy>::toCpp(obj.iceTransportPolicy),
            ::djinni::Bool::toCpp(obj.enableIceTcp),
            ::djinni::Bool::toCpp(obj.enableIceUdpMux),
            ::djinni::Bool::toCpp(obj.disableAutoNegotiation),
            ::djinni::Bool::toCpp(obj.forceMediaTransport),
            ::djinni::I32::toCpp(obj.portRangeBegin),
            ::djinni::I32::toCpp(obj.portRangeEnd),
            ::djinni::Optional<std::optional, ::djinni::I32>::toCpp(obj.mtu),
            ::djinni::Optional<std::optional, ::djinni::I32>::toCpp(obj.maxMessageSize)};
}

auto Configuration::fromCpp(const CppType& cpp) -> ObjcType
{
    return [[DCConfiguration alloc] initWithIceServers:(::djinni::List<::djinni_generated::IceServer>::fromCpp(cpp.iceServers))
                                           proxyServer:(::djinni::Optional<std::optional, ::djinni_generated::ProxyServer>::fromCpp(cpp.proxyServer))
                                           bindAddress:(::djinni::Optional<std::optional, ::djinni::String>::fromCpp(cpp.bindAddress))
                                       certificateType:(::djinni::Enum<::libdc::CertificateType, DCCertificateType>::fromCpp(cpp.certificateType))
                                    iceTransportPolicy:(::djinni::Enum<::libdc::TransportPolicy, DCTransportPolicy>::fromCpp(cpp.iceTransportPolicy))
                                          enableIceTcp:(::djinni::Bool::fromCpp(cpp.enableIceTcp))
                                       enableIceUdpMux:(::djinni::Bool::fromCpp(cpp.enableIceUdpMux))
                                disableAutoNegotiation:(::djinni::Bool::fromCpp(cpp.disableAutoNegotiation))
                                   forceMediaTransport:(::djinni::Bool::fromCpp(cpp.forceMediaTransport))
                                        portRangeBegin:(::djinni::I32::fromCpp(cpp.portRangeBegin))
                                          portRangeEnd:(::djinni::I32::fromCpp(cpp.portRangeEnd))
                                                   mtu:(::djinni::Optional<std::optional, ::djinni::I32>::fromCpp(cpp.mtu))
                                        maxMessageSize:(::djinni::Optional<std::optional, ::djinni::I32>::fromCpp(cpp.maxMessageSize))];
}

} // namespace djinni_generated
