package com.cdnbye.dc_perf.libdc

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
import com.cdnbye.libdc.DataChannel
import com.cdnbye.libdc.DcMessageCallback
import com.cdnbye.libdc.LibDC
import com.cdnbye.libdc.LogLevel.DEBUG
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
  private val handler = Handler(Looper.getMainLooper())

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)

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
            TestText(text = "libDC")

            Button(onClick = {
              testDc()
            }) {
              TestText(text = "test")
            }

            Button(onClick = {
              perfDc()
            }) {
              TestText(text = "perf")
            }
          }
        }
      }
    }

    LibDC.initialize()
  }

  private fun testDc(log: Boolean = true, msgCount: Int = 1) {
    if (log) {
      LibDC.initLogger(DEBUG) { level, message ->
        Log.e("XXPXX", "$level $message")
      }
    }

    val config = rtcConfiguration()
    val pc1 = PeerConnection.create(config)
    val pc2 = PeerConnection.create(config)

    pc1?.onLocalDescription {
      if (log) Log.e("XXPXX", "pc1 onLocalDescription $it")
      pc2?.setRemoteDescription(it)
    }
    pc2?.onLocalDescription {
      if (log) Log.e("XXPXX", "pc2 onLocalDescription $it")
      pc1?.setRemoteDescription(it)
    }

    pc1?.onLocalCandidate { candidate, mid ->
      if (log) Log.e("XXPXX", "pc1 onLocalCandidate $candidate $mid")
      pc2?.addRemoteCandidate(candidate, mid)
    }
    pc2?.onLocalCandidate { candidate, mid ->
      if (log) Log.e("XXPXX", "pc2 onLocalCandidate $candidate $mid")
      pc1?.addRemoteCandidate(candidate, mid)
    }

    pc1?.onStateChange {
      if (log) Log.e("XXPXX", "pc1 onStateChange $it")
    }
    pc2?.onStateChange {
      if (log) Log.e("XXPXX", "pc2 onStateChange $it")
    }

    pc1?.onGatheringStateChange {
      if (log) Log.e("XXPXX", "pc1 onGatheringStateChange $it")
    }
    pc2?.onGatheringStateChange {
      if (log) Log.e("XXPXX", "pc2 onGatheringStateChange $it")
    }

    pc2?.onDataChannel {
      if (log) Log.e("XXPXX", "pc2 onDataChannel $it")

      it?.onMessage(object : DcMessageCallback {
        override fun onText(msg: String) {
          if (log) Log.e("XXPXX", "pc2 onMessage $msg")
        }

        override fun onBinary(msg: ByteArray) {
          if (log) Log.e("XXPXX", "pc2 onBinary ${String(msg)}")
        }
      })

      sendMsg(it!!, "pc2", msgCount)
    }

    val dc1 = pc1?.createDataChannel("test")
    dc1?.onOpen {
      if (log) Log.e("XXPXX", "dc1 onOpen ${dc1.isOpen} ${dc1.isClosed}")

      sendMsg(dc1, "pc1", msgCount)
    }
    dc1?.onMessage(object : DcMessageCallback {
      override fun onText(msg: String) {
        if (log) Log.e("XXPXX", "pc1 onMessage $msg")
      }

      override fun onBinary(msg: ByteArray) {
        if (log) Log.e("XXPXX", "pc1 onBinary ${String(msg)}")
      }
    })
  }

  private fun sendMsg(dc: DataChannel, tag: String, i: Int) {
    if (i < 0) {
      return
    }

    dc.sendText("Hello world $i from $tag")
    dc.sendBinary("binary msg $i from $tag".toByteArray())

    handler.postDelayed({
      sendMsg(dc, tag, i - 1)
    }, 50)
  }

  private fun perfDc(pcCount: Int = 100) {
    for (i in 0..pcCount) {
      testDc(false, 100 * 100)
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
