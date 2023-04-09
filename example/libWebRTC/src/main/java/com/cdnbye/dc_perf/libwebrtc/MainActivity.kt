package com.cdnbye.dc_perf.libwebrtc

import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.Button
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Shapes
import androidx.compose.material.Surface
import androidx.compose.material.Text
import androidx.compose.material.Typography
import androidx.compose.material.darkColors
import androidx.compose.material.lightColors
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontFamily
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import org.webrtc.DataChannel
import org.webrtc.DataChannel.Buffer
import org.webrtc.DataChannel.State.OPEN
import org.webrtc.IceCandidate
import org.webrtc.MediaConstraints
import org.webrtc.PeerConnection
import org.webrtc.PeerConnection.IceConnectionState
import org.webrtc.PeerConnection.IceGatheringState
import org.webrtc.PeerConnection.SignalingState
import org.webrtc.PeerConnectionFactory
import org.webrtc.PeerConnectionFactory.InitializationOptions
import org.webrtc.SdpObserver
import org.webrtc.SessionDescription
import java.nio.ByteBuffer

@Composable
fun MyApplicationTheme(
  darkTheme: Boolean = isSystemInDarkTheme(),
  content: @Composable () -> Unit
) {
  val colors = if (darkTheme) {
    darkColors(
      primary = Color(0xFFBB86FC),
      primaryVariant = Color(0xFF3700B3),
      secondary = Color(0xFF03DAC5)
    )
  } else {
    lightColors(
      primary = Color(0xFF6200EE),
      primaryVariant = Color(0xFF3700B3),
      secondary = Color(0xFF03DAC5)
    )
  }
  val typography = Typography(
    body1 = TextStyle(
      fontFamily = FontFamily.Default,
      fontWeight = FontWeight.Normal,
      fontSize = 16.sp
    )
  )
  val shapes = Shapes(
    small = RoundedCornerShape(4.dp),
    medium = RoundedCornerShape(4.dp),
    large = RoundedCornerShape(0.dp)
  )

  MaterialTheme(
    colors = colors,
    typography = typography,
    shapes = shapes,
    content = content
  )
}

class MainActivity : ComponentActivity() {
  private val handler = Handler(Looper.getMainLooper())

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)

    PeerConnectionFactory.initialize(
      InitializationOptions.builder(applicationContext)
        .createInitializationOptions()
    )

    val pcFactory = PeerConnectionFactory.builder()
      .createPeerConnectionFactory()

    setContent {
      MyApplicationTheme {
        Surface(
          modifier = Modifier.fillMaxSize(),
          color = MaterialTheme.colors.background
        ) {
          Column(
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.Center,
          ) {
            TestText(text = "libWebRTC")

            Button(onClick = {
              testDc(pcFactory)
            }) {
              TestText(text = "test")
            }

            Button(onClick = {
              perfDc(pcFactory)
            }) {
              TestText(text = "perf")
            }
          }
        }
      }
    }
  }

  private fun testDc(pcFactory: PeerConnectionFactory, log: Boolean = true, msgCount: Int = 1) {
    val config = PeerConnection.RTCConfiguration(emptyList())

    var pc1: PeerConnection? = null
    var pc2: PeerConnection? = null

    var dc1: DataChannel? = null
    var dc2: DataChannel? = null

    val pc1Candidates = ArrayList<IceCandidate>()
    val pc2Candidates = ArrayList<IceCandidate>()

    pc1 = pcFactory.createPeerConnection(config, object : PeerConnection.Observer {
      override fun onSignalingChange(state: SignalingState?) {
      }

      override fun onIceConnectionChange(state: IceConnectionState?) {
        if (log) Log.e("XXPXX", "pc1 onIceConnectionChange $state")
      }

      override fun onIceConnectionReceivingChange(p0: Boolean) {
      }

      override fun onIceGatheringChange(state: IceGatheringState?) {
        if (log) Log.e("XXPXX", "pc1 onIceGatheringChange $state")
      }

      override fun onIceCandidate(candidate: IceCandidate?) {
        if (log) Log.e("XXPXX", "pc1 onIceCandidate $candidate")

        pc1Candidates.add(candidate!!)
        pc2?.addIceCandidate(candidate)
      }

      override fun onIceCandidatesRemoved(p0: Array<out IceCandidate>?) {
      }

      override fun onDataChannel(dc: DataChannel?) {
        if (log) Log.e("XXPXX", "pc1 onDataChannel $dc")
      }

      override fun onRenegotiationNeeded() {
      }
    })

    pc2 = pcFactory.createPeerConnection(config, object : PeerConnection.Observer {
      override fun onSignalingChange(state: SignalingState?) {
      }

      override fun onIceConnectionChange(state: IceConnectionState?) {
        if (log) Log.e("XXPXX", "pc2 onIceConnectionChange $state")
      }

      override fun onIceConnectionReceivingChange(p0: Boolean) {
      }

      override fun onIceGatheringChange(state: IceGatheringState?) {
        if (log) Log.e("XXPXX", "pc2 onIceGatheringChange $state")
      }

      override fun onIceCandidate(candidate: IceCandidate?) {
        if (log) Log.e("XXPXX", "pc2 onIceCandidate $candidate")

        pc2Candidates.add(candidate!!)
        pc1?.addIceCandidate(candidate)
      }

      override fun onIceCandidatesRemoved(p0: Array<out IceCandidate>?) {
      }

      override fun onDataChannel(dc: DataChannel?) {
        if (log) Log.e("XXPXX", "pc2 onDataChannel $dc")
        dc2 = dc
        dc2?.registerObserver(object : DataChannel.Observer {
          override fun onBufferedAmountChange(p0: Long) {
            if (log) Log.e("XXPXX", "dc2 onBufferedAmountChange $p0")
          }

          override fun onStateChange() {
            if (log) Log.e("XXPXX", "dc2 onStateChange ${dc2?.state()}")

            if (dc2?.state() == OPEN) {
              sendMsg(dc2!!, "pc2", msgCount)
            }
          }

          override fun onMessage(buffer: Buffer?) {
            if (log) logMessage("dc2", buffer)
          }
        })
      }

      override fun onRenegotiationNeeded() {
      }
    })

    val init = DataChannel.Init()
    dc1 = pc1?.createDataChannel("test", init)

    pc1?.createOffer(sdpObserver(false) {
      if (log) Log.e("XXPXX", "pc1 create offer success ${it?.description}")

      pc1.setLocalDescription(sdpObserver(true) {
        if (log) Log.e("XXPXX", "pc1 set offer success")
      }, it)

      pc2?.setRemoteDescription(sdpObserver(true) {
        if (log) Log.e("XXPXX", "pc2 set offer success")

        pc2.createAnswer(sdpObserver(false) { it2 ->
          if (log) Log.e("XXPXX", "pc2 create answer success")

          pc2.setLocalDescription(sdpObserver(true) {
            if (log) Log.e("XXPXX", "pc2 set answer success")
            addIceCandidates(pc2, pc1Candidates)
          }, it2)

          pc1.setRemoteDescription(sdpObserver(true) {
            if (log) Log.e("XXPXX", "pc1 set answer success")
            addIceCandidates(pc1, pc2Candidates)
          }, it2)
        }, MediaConstraints())
      }, it)
    }, MediaConstraints())

    dc1?.registerObserver(object : DataChannel.Observer {
      override fun onBufferedAmountChange(p0: Long) {
        if (log) Log.e("XXPXX", "dc1 onBufferedAmountChange $p0")
      }

      override fun onStateChange() {
        if (log) Log.e("XXPXX", "dc1 onStateChange ${dc1.state()}")

        if (dc1.state() == OPEN) {
          sendMsg(dc1, "pc1", msgCount)
        }
      }

      override fun onMessage(buffer: Buffer?) {
        if (log) logMessage("dc1", buffer)
      }
    })
  }

  private fun sendMsg(dc: DataChannel, tag: String, i: Int) {
    if (i < 0) {
      return
    }

    dc.send(Buffer(ByteBuffer.wrap("Hello world $i from $tag".toByteArray()), false))
    dc.send(Buffer(ByteBuffer.wrap("binary message $i from $tag".toByteArray()), true))

    handler.postDelayed({
      sendMsg(dc, tag, i - 1)
    }, 50)
  }

  private fun perfDc(pcFactory: PeerConnectionFactory, pcCount: Int = 100) {
    for (i in 0..pcCount) {
      testDc(pcFactory, false, 100 * 100)
    }
  }

  private fun addIceCandidates(pc: PeerConnection, candidates: List<IceCandidate>) {
    for (candidate in candidates) {
      pc.addIceCandidate(candidate)
    }
  }

  private fun logMessage(label: String, buffer: Buffer?) {
    if (buffer == null) {
      return
    }

    val data = buffer.data
    val bytes = ByteArray(data.remaining())
    data.get(bytes)
    if (buffer.binary) {
      Log.e("XXPXX", "$label onBinary ${String(bytes)}")
    } else {
      Log.e("XXPXX", "$label onText ${String(bytes)}")
    }
  }

  private fun sdpObserver(set: Boolean, op: (sdp: SessionDescription?) -> Unit) =
    object : SdpObserver {
      override fun onCreateSuccess(sdp: SessionDescription?) {
        if (!set) {
          op(sdp)
        }
      }

      override fun onSetSuccess() {
        if (set) {
          op(null)
        }
      }

      override fun onCreateFailure(p0: String?) {
      }

      override fun onSetFailure(p0: String?) {
      }
    }
}

@Composable
fun TestText(text: String) {
  Text(text = text)
}

@Preview
@Composable
fun DefaultPreview() {
  MyApplicationTheme {
    TestText("test")
  }
}
