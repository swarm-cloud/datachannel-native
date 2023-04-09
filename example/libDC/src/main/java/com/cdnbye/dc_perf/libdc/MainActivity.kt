package com.cdnbye.dc_perf.libdc

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
import com.cdnbye.libdc.DataChannel
import com.cdnbye.libdc.DcMessageCallback
import com.cdnbye.libdc.LibDC
import com.cdnbye.libdc.PeerConnection
import com.cdnbye.libdc.createDataChannel
import com.cdnbye.libdc.rtcConfiguration

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

    LibDC.initialize()
    val config = rtcConfiguration()
    pc1 = PeerConnection.create(config)
    pc2 = PeerConnection.create(config)

    pc1?.onLocalDescription {
      Log.e("XXPXX", "pc1 onLocalDescription $it")
      pc2?.setRemoteDescription(it)
    }
    pc2?.onLocalDescription {
      Log.e("XXPXX", "pc2 onLocalDescription $it")
      pc1?.setRemoteDescription(it)
    }

    pc1?.onLocalCandidate { candidate, mid ->
      Log.e("XXPXX", "pc1 onLocalCandidate $candidate $mid")
      pc2?.addRemoteCandidate(candidate, mid)
    }
    pc2?.onLocalCandidate { candidate, mid ->
      Log.e("XXPXX", "pc2 onLocalCandidate $candidate $mid")
      pc1?.addRemoteCandidate(candidate, mid)
    }

    pc1?.onStateChange {
      Log.e("XXPXX", "pc1 onStateChange $it")
    }
    pc2?.onStateChange {
      Log.e("XXPXX", "pc2 onStateChange $it")
    }

    pc1?.onGatheringStateChange {
      Log.e("XXPXX", "pc1 onGatheringStateChange $it")
    }
    pc2?.onGatheringStateChange {
      Log.e("XXPXX", "pc2 onGatheringStateChange $it")
    }

    pc2?.onDataChannel {
      Log.e("XXPXX", "pc2 onDataChannel $it")
      dc2 = it

      dc2?.onMessage(object : DcMessageCallback {
        override fun onText(msg: String) {
          Log.e("XXPXX", "pc2 onMessage $msg")
        }

        override fun onBinary(msg: ByteArray) {
          Log.e("XXPXX", "pc2 onBinary ${String(msg)}")
        }
      })
      dc2?.sendText("Hello world from dc2")
      dc2?.sendBinary("binary msg from dc2".toByteArray())
    }

    dc1 = pc1?.createDataChannel("test")
    dc1?.onOpen {
      Log.e("XXPXX", "pc1 onOpen")
      dc1?.sendText("Hello world from dc1")
      dc1?.sendBinary("binary msg from dc1".toByteArray())
    }
    dc1?.onMessage(object : DcMessageCallback {
      override fun onText(msg: String) {
        Log.e("XXPXX", "pc1 onMessage $msg")
      }

      override fun onBinary(msg: ByteArray) {
        Log.e("XXPXX", "pc1 onBinary ${String(msg)}")
      }
    })
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
