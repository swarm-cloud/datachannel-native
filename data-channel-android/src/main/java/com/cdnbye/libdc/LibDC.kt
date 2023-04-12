package com.cdnbye.libdc

import com.cdnbye.libdc.CertificateType.DEFAULT
import com.cdnbye.libdc.IceServerRelayType.TURNTCP
import com.cdnbye.libdc.IceServerType.STUN
import com.cdnbye.libdc.ReliabilityType.RELIABLE
import com.cdnbye.libdc.TransportPolicy.ALL

/**
 * Created by Piasy{github.com/Piasy} on 2023/4/9.
 */
class LibDC {
  companion object {
    fun initialize() {
      System.loadLibrary("datachannel")
      System.loadLibrary("datachannel_jni")
    }

    fun initLogger(level: LogLevel, callback: LogCallback) {
      // to workaround 'NoSuchMethodError' calling static interface method on pre-API-24,
      // ref: https://github.com/xamarin/xamarin-android/issues/6784#issuecomment-1091487256
      PeerConnection.CppProxy.initLogger(level, callback)
    }
  }
}

fun rtcIceServer(
  url: String? = null,
  hostname: String = "",
  port: Short = 0,
  type: IceServerType = STUN,
  username: String = "",
  password: String = "",
  relayType: IceServerRelayType = TURNTCP,
): IceServer {
  return IceServer(url, hostname, port, type, username, password, relayType)
}

fun rtcConfiguration(
  iceServers: List<IceServer> = emptyList(),
  proxyServer: ProxyServer? = null,
  bindAddress: String? = null,
  certificateType: CertificateType = DEFAULT,
  iceTransportPolicy: TransportPolicy = ALL,
  enableIceTcp: Boolean = false,
  enableIceUdpMux: Boolean = false,
  disableAutoNegotiation: Boolean = false,
  forceMediaTransport: Boolean = false,
  portRangeBegin: Int = 1024,
  portRangeEnd: Int = 65535,
  mtu: Int? = null,
  maxMessageSize: Int? = null
): Configuration {
  return Configuration(
    ArrayList(iceServers),
    proxyServer,
    bindAddress,
    certificateType,
    iceTransportPolicy,
    enableIceTcp,
    enableIceUdpMux,
    disableAutoNegotiation,
    forceMediaTransport,
    portRangeBegin,
    portRangeEnd,
    mtu,
    maxMessageSize
  )
}

// to workaround 'NoSuchMethodError' calling static interface method on pre-API-24,
// ref: https://github.com/xamarin/xamarin-android/issues/6784#issuecomment-1091487256
fun createPeerConnection(config: Configuration): PeerConnection? {
  return PeerConnection.CppProxy.create(config)
}

fun PeerConnection.createDataChannel(
  label: String,
  init: DataChannelInit? = null
): DataChannel? {
  return createDataChannel(
    label,
    init ?: DataChannelInit(Reliability(RELIABLE, false, 0), false, null, "")
  )
}
