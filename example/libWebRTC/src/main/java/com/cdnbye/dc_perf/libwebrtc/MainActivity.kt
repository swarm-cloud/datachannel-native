package com.cdnbye.dc_perf.libwebrtc

import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Shapes
import androidx.compose.material.Surface
import androidx.compose.material.Text
import androidx.compose.material.Typography
import androidx.compose.material.darkColors
import androidx.compose.material.lightColors
import androidx.compose.runtime.Composable
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
  private var pc1: PeerConnection? = null
  private var pc2: PeerConnection? = null

  private var dc1: DataChannel? = null
  private var dc2: DataChannel? = null

  private val pc1Candidates = ArrayList<IceCandidate>()
  private val pc2Candidates = ArrayList<IceCandidate>()

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)

    setContent {
      MyApplicationTheme {
        Surface(
          modifier = Modifier.fillMaxSize(),
          color = MaterialTheme.colors.background
        ) {
        }
      }
    }

    PeerConnectionFactory.initialize(
      InitializationOptions.builder(applicationContext)
        .createInitializationOptions()
    )

    val pcFactory = PeerConnectionFactory.builder()
      .createPeerConnectionFactory()
    val config = PeerConnection.RTCConfiguration(emptyList())

    pc1 = pcFactory.createPeerConnection(config, object : PeerConnection.Observer {
      override fun onSignalingChange(state: SignalingState?) {
      }

      override fun onIceConnectionChange(state: IceConnectionState?) {
        Log.e("XXPXX", "pc1 onIceConnectionChange $state")
      }

      override fun onIceConnectionReceivingChange(p0: Boolean) {
      }

      override fun onIceGatheringChange(state: IceGatheringState?) {
        Log.e("XXPXX", "pc1 onIceGatheringChange $state")
      }

      override fun onIceCandidate(candidate: IceCandidate?) {
        Log.e("XXPXX", "pc1 onIceCandidate $candidate")

        pc1Candidates.add(candidate!!)
        pc2?.addIceCandidate(candidate)
      }

      override fun onIceCandidatesRemoved(p0: Array<out IceCandidate>?) {
      }

      override fun onDataChannel(dc: DataChannel?) {
        Log.e("XXPXX", "pc1 onDataChannel $dc")
      }

      override fun onRenegotiationNeeded() {
      }
    })

    pc2 = pcFactory.createPeerConnection(config, object : PeerConnection.Observer {
      override fun onSignalingChange(state: SignalingState?) {
      }

      override fun onIceConnectionChange(state: IceConnectionState?) {
        Log.e("XXPXX", "pc2 onIceConnectionChange $state")
      }

      override fun onIceConnectionReceivingChange(p0: Boolean) {
      }

      override fun onIceGatheringChange(state: IceGatheringState?) {
        Log.e("XXPXX", "pc2 onIceGatheringChange $state")
      }

      override fun onIceCandidate(candidate: IceCandidate?) {
        Log.e("XXPXX", "pc2 onIceCandidate $candidate")

        pc2Candidates.add(candidate!!)
        pc1?.addIceCandidate(candidate)
      }

      override fun onIceCandidatesRemoved(p0: Array<out IceCandidate>?) {
      }

      override fun onDataChannel(dc: DataChannel?) {
        Log.e("XXPXX", "pc2 onDataChannel $dc")
        dc2 = dc
        dc2?.registerObserver(object : DataChannel.Observer {
          override fun onBufferedAmountChange(p0: Long) {
            Log.e("XXPXX", "dc2 onBufferedAmountChange $p0")
          }

          override fun onStateChange() {
            Log.e("XXPXX", "dc2 onStateChange ${dc2?.state()}")

            if (dc2?.state() == OPEN) {
              dc2?.send(Buffer(ByteBuffer.wrap("Hello world from dc2".toByteArray()), false))
              dc2?.send(Buffer(ByteBuffer.wrap("binary message from dc2".toByteArray()), true))
            }
          }

          override fun onMessage(buffer: Buffer?) {
            handleMessage("dc2", buffer)
          }
        })
      }

      override fun onRenegotiationNeeded() {
      }
    })

    val init = DataChannel.Init()
    dc1 = pc1?.createDataChannel("test", init)

    pc1?.createOffer(sdpObserver(false) {
      Log.e("XXPXX", "pc1 create offer success ${it?.description}")

      pc1?.setLocalDescription(sdpObserver(true) {
        Log.e("XXPXX", "pc1 set offer success")
      }, it)

      pc2?.setRemoteDescription(sdpObserver(true) {
        Log.e("XXPXX", "pc2 set offer success")

        pc2?.createAnswer(sdpObserver(false) { it2 ->
          Log.e("XXPXX", "pc2 create answer success")

          pc2?.setLocalDescription(sdpObserver(true) {
            Log.e("XXPXX", "pc2 set answer success")
            addIceCandidates(pc2!!, pc1Candidates)
          }, it2)

          pc1?.setRemoteDescription(sdpObserver(true) {
            Log.e("XXPXX", "pc1 set answer success")
            addIceCandidates(pc1!!, pc2Candidates)
          }, it2)
        }, MediaConstraints())
      }, it)
    }, MediaConstraints())

    dc1?.registerObserver(object : DataChannel.Observer {
      override fun onBufferedAmountChange(p0: Long) {
        Log.e("XXPXX", "dc1 onBufferedAmountChange $p0")
      }

      override fun onStateChange() {
        Log.e("XXPXX", "dc1 onStateChange ${dc1?.state()}")

        if (dc1?.state() == OPEN) {
          dc1?.send(Buffer(ByteBuffer.wrap("Hello world from dc1".toByteArray()), false))
          dc1?.send(Buffer(ByteBuffer.wrap("binary message from dc1".toByteArray()), true))
        }
      }

      override fun onMessage(buffer: Buffer?) {
        handleMessage("dc1", buffer)
      }
    })
  }

  private fun addIceCandidates(pc: PeerConnection, candidates: List<IceCandidate>) {
    for (candidate in candidates) {
      pc.addIceCandidate(candidate)
    }
  }

  private fun handleMessage(label: String, buffer: Buffer?) {
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
fun Greeting(text: String) {
  Text(text = text)
}

@Preview
@Composable
fun DefaultPreview() {
  MyApplicationTheme {
    Greeting("Hello, Android!")
  }
}
