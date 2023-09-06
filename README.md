# DataChannel Native

Native platform (Android/iOS/tvOS/macOS) wrapper for [paullouisageneau/libdatachannel](https://github.com/paullouisageneau/libdatachannel): C/C++ WebRTC network library.

## Android

### Add dependency

TODO

### Minimum example

```kotlin
import com.cdnbye.libdc.DataChannel
import com.cdnbye.libdc.DcMessageCallback
import com.cdnbye.libdc.LibDC
import com.cdnbye.libdc.LogLevel.DEBUG
import com.cdnbye.libdc.PeerConnection
import com.cdnbye.libdc.createDataChannel
import com.cdnbye.libdc.rtcConfiguration

// inject custom logger
PeerConnection.initLogger(DEBUG) { level, message ->
    // log the message
}

// create config and pc
val config = rtcConfiguration()
val pc1 = PeerConnection.create(config)
val pc2 = PeerConnection.create(config)

// observe local sdp, and set as remote sdp in other pc
pc1?.onLocalDescription {
    pc2?.setRemoteDescription(it)
}
pc2?.onLocalDescription {
    pc1?.setRemoteDescription(it)
}

// observe ICE candidate, and add to other pc
pc1?.onLocalCandidate { candidate, mid ->
    pc2?.addRemoteCandidate(candidate, mid)
}
pc2?.onLocalCandidate { candidate, mid ->
    pc1?.addRemoteCandidate(candidate, mid)
}

// observe ICE connection state
pc1?.onStateChange {
    // xxx
}
pc2?.onStateChange {
    // xxx
}

// observe ICE candidate gathering state
pc1?.onGatheringStateChange {
    // xxx
}
pc2?.onGatheringStateChange {
    // xxx
}

// observe incoming dc
pc2?.onDataChannel {
    // observe dc message
    it?.onMessage(object : DcMessageCallback {
        override fun onText(msg: String) {
            // xxx
        }

        override fun onBinary(msg: ByteArray) {
            // xxx
        }
    })

    // send message
    sendMsg(it!!, "pc2", msgCount)
}

// create dc
val dc1 = pc1?.createDataChannel("test")
// observe dc open event
dc1?.onOpen {
    // send message
    sendMsg(dc1, "pc1", msgCount)
}
// observe dc message
dc1?.onMessage(object : DcMessageCallback {
    override fun onText(msg: String) {
        // xxx
    }

    override fun onBinary(msg: ByteArray) {
        // xxx
    }
})
```

## Apple OS family

The API is almost the same as Android, the difference is just the difference between Kotlin and Swift.

## Development

Before start building, run commands below:

```bash
git submodule update --recursive --init
./run_djinni.sh

# for Android
./build_openssl_android.sh

# for Apple OS family
./build_openssl_apple.sh
```

For Android development, just open the root project as Android Studio project, then you can run and debug it.

For Apple OS family, run `./build_apple.sh` to build the xcframework.
