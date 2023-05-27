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
      System.loadLibrary("datachannel_jni")
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

fun PeerConnection.createDataChannel(
  label: String,
  init: DataChannelInit? = null
): DataChannel? {
  return createDataChannel(
    label,
    init ?: DataChannelInit(Reliability(RELIABLE, false, 0), false, null, "")
  )
}
