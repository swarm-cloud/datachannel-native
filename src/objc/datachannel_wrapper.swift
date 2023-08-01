public class DCLibDC {
    public class func version() -> String {
        return DCLibVersion.version()
    }

    public class func rtcIceServer(url: String? = nil,
                             hostname: String = "",
                             port: Int16 = 0,
                             type: DCIceServerType = DCIceServerType.stun,
                             username: String = "",
                             password: String = "",
                             relayType: DCIceServerRelayType = DCIceServerRelayType.turnTcp) -> DCIceServer {
        return DCIceServer(url: url,
                           hostname: hostname,
                           port: port,
                           type: type,
                           username: username,
                           password: password,
                           relayType: relayType)
    }

    public class func rtcConfiguration(iceServers: [DCIceServer] = [],
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
}

private class DCClosureSdpCallback : NSObject, DCSdpCallback {
    let callback: (_ sdp: String) -> ()

    init(_ callback: @escaping (_ sdp: String) -> ()) {
        self.callback = callback
    }

    func onSdp(_ sdp: String) {
        callback(sdp)
    }
}

private class DCClosureCandidateCallback : NSObject, DCCandidateCallback {
    let callback: (_ candidate: String, _ mid: String) -> ()

    init(_ callback: @escaping (_ candidate: String, _ mid: String) -> ()) {
        self.callback = callback
    }

    func onCandidate(_ candidate: String, mid: String) {
        callback(candidate, mid)
    }
}

private class DCClosureDcCallback : NSObject, DCDcCallback {
    let callback: (_ dc: DCDataChannel?) -> ()

    init(_ callback: @escaping (_ dc: DCDataChannel?) -> ()) {
        self.callback = callback
    }

    func onDataChannel(_ dc: DCDataChannel?) {
        callback(dc)
    }
}

private class DCClosureLogCallback : NSObject, DCLogCallback {
    let callback: (_ level: DCLogLevel, _ message: String) -> ()

    init(_ callback: @escaping (_ level: DCLogLevel, _ message: String) -> ()) {
        self.callback = callback
    }

    func onLog(_ level: DCLogLevel, message: String) {
        callback(level, message)
    }
}

private class DCClosureIceStateCallback : NSObject, DCIceStateCallback {
    let callback: (_ state: DCIceState) -> ()

    init(_ callback: @escaping (_ state: DCIceState) -> ()) {
        self.callback = callback
    }

    func onStateChanged(_ state: DCIceState) {
        callback(state)
    }
}

private class DCClosureGatheringStateCallback : NSObject, DCGatheringStateCallback {
    let callback: (_ state: DCGatheringState) -> ()

    init(_ callback: @escaping (_ state: DCGatheringState) -> ()) {
        self.callback = callback
    }

    func onStateChanged(_ state: DCGatheringState) {
        callback(state)
    }
}

private class DCClosureSignalingStateCallback : NSObject, DCSignalingStateCallback {
    let callback: (_ state: DCSignalingState) -> ()

    init(_ callback: @escaping (_ state: DCSignalingState) -> ()) {
        self.callback = callback
    }

    func onStateChanged(_ state: DCSignalingState) {
        callback(state)
    }
}

public extension DCPeerConnection {
    class func initLogger(_ level: DCLogLevel, callback: @escaping (_ level: DCLogLevel, _ message: String) -> ()) {
        DCPeerConnection.initLogger(level, callback: DCClosureLogCallback(callback))
    }

    func onLocalDescription(_ callback: @escaping (_ sdp: String) -> ()) {
        onLocalDescription(DCClosureSdpCallback(callback))
    }

    func onLocalCandidate(_ callback: @escaping (_ candidate: String, _ mid: String) -> ()) {
        onLocalCandidate(DCClosureCandidateCallback(callback))
    }

    func onDataChannel(_ callback: @escaping (_ dc: DCDataChannel?) -> ()) {
        onDataChannel(DCClosureDcCallback(callback))
    }

    func onStateChange(_ callback: @escaping (_ state: DCIceState) -> ()) {
        onStateChange(DCClosureIceStateCallback(callback))
    }

    func onGatheringStateChange(_ callback: @escaping (_ state: DCGatheringState) -> ()) {
        onGatheringStateChange(DCClosureGatheringStateCallback(callback))
    }

    func onSignalingStateChange(_ callback: @escaping (_ state: DCSignalingState) -> ()) {
        onSignalingStateChange(DCClosureSignalingStateCallback(callback))
    }

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

private class DCClosureDcMessageCallback : NSObject, DCDcMessageCallback {
    let textCallback: (_ msg: String) -> ()
    let binaryCallback: (_ msg: Data) -> ()

    init(_ textCallback: @escaping (_ msg: String) -> (), _ binaryCallback: @escaping (_ msg: Data) -> ()) {
        self.textCallback = textCallback
        self.binaryCallback = binaryCallback
    }

    func onText(_ msg: String) {
        textCallback(msg)
    }

    func onBinary(_ msg: Data) {
        binaryCallback(msg)
    }
}

private class DCClosureDcEventCallback : NSObject, DCDcEventCallback {
    let callback: (_ event: DCDcEvent) -> ()

    init(_ callback: @escaping (_ event: DCDcEvent) -> ()) {
        self.callback = callback
    }

    func onEvent(_ event: DCDcEvent) {
        callback(event)
    }
}

private class DCClosureDcErrorCallback : NSObject, DCDcErrorCallback {
    let callback: (_ error: String) -> ()

    init(_ callback: @escaping (_ error: String) -> ()) {
        self.callback = callback
    }

    func onError(_ error: String) {
        callback(error)
    }
}

public extension DCDataChannel {
    func onOpen(_ callback: @escaping (_ event: DCDcEvent) -> ()) {
        onOpen(DCClosureDcEventCallback(callback))
    }

    func onClosed(_ callback: @escaping (_ event: DCDcEvent) -> ()) {
        onClosed(DCClosureDcEventCallback(callback))
    }

    func onError(_ callback: @escaping (_ error: String) -> ()) {
        onError(DCClosureDcErrorCallback(callback))
    }

    func onMessage(text: @escaping (_ msg: String) -> (), binary: @escaping (_ msg: Data) -> ()) {
        onMessage(DCClosureDcMessageCallback(text, binary))
    }

    func onBufferedAmountLow(_ callback: @escaping (_ event: DCDcEvent) -> ()) {
        onBufferedAmountLow(DCClosureDcEventCallback(callback))
    }
}
