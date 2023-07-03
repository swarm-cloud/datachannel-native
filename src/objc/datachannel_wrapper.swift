public extension DCPeerConnection {
  func createDataChannel(_ label : String, _ conf: DCDataChannelInit? = nil) -> DCDataChannel? {
    if (conf == nil) {
      return createDataChannel(
        label,
        DCDataChannelInit(reliability: DCReliability(type: DCReliabilityType.reliable,
                                                     unordered: false, rexmitMs: 0),
                          negotiated: false, id: nil, protocol: ""))
    } else {
      return createDataChannel(label, init: conf!)
    }
  }
}

public func rtcIceServer(url: String? = nil,
                         hostname: String = "",
                         port: Int16 = 0,
                         type: DCIceServerType = DCIceServerType.stun,
                         username: String = "",
                         password: String = "",
                         relayType: DCIceServerRelayType = DCIceServerRelayType.turnTcp) -> DCIceServer {
    return DCIceServer(url: url, hostname: hostname, port: port, type: type, username: username, password: password, relayType: relayType)
}

public func rtcConfiguration(iceServers: [DCIceServer] = [],
                             proxyServer: DCProxyServer? = nil,
                             bindAddress: String? = nil,
                             certificateType: DCCertificateType = DCCertificateType.default,
                             iceTransportPolicy: DCTransportPolicy = DCTransportPolicy.all,
                             enableIceTcp: Bool = false,
                             enableIceUdpMux: Bool = false,
                             disableAutoNegotiation: Bool = false,
                             forceMediaTransport: Bool = false,
                             portRangeBegin: Int32 = 1024,
                             portRangeEnd: Int32 = 65535,
                             mtu: NSNumber? = nil,
                             maxMessageSize: NSNumber? = nil) -> DCConfiguration {
    return DCConfiguration(iceServers: iceServers,
                           proxyServer: proxyServer,
                           bindAddress: bindAddress,
                           certificateType: certificateType,
                           iceTransportPolicy: iceTransportPolicy,
                           enableIceTcp: enableIceTcp,
                           enableIceUdpMux: enableIceUdpMux,
                           disableAutoNegotiation: disableAutoNegotiation,
                           forceMediaTransport: forceMediaTransport,
                           portRangeBegin: portRangeBegin,
                           portRangeEnd: portRangeEnd,
                           mtu: mtu,
                           maxMessageSize: maxMessageSize)
}
