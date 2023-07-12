//
//  ContentView.swift
//  libDCiOSExample
//
//  Created by Piasy Xu on 2023/7/2.
//

import SwiftUI
import datachannel_wrapper

class TestLogCallback : NSObject, DCLogCallback {
    func onLog(_ level: DCLogLevel, message: String) {
        NSLog("XXPXX %d %@", level.rawValue, message)
    }
}

class DcOpenCallback : NSObject, DCDcEventCallback {
    let dc: DCDataChannel
    let label: String

    init(_ dc: DCDataChannel, _ label: String) {
        self.dc = dc
        self.label = label
    }

    func onEvent() {
        NSLog("%@ dc onOpen", label)
        dc.sendText(String(format: "Hello world from %@ %@", label, DCLibDC.version()))
    }
}

class DcTest : NSObject, DCSdpCallback, DCCandidateCallback, DCDcCallback, DCDcMessageCallback {
    let otherPc: DCPeerConnection
    let label: String

    var dc: DCDataChannel? = nil

    init(_ otherPc: DCPeerConnection, _ label: String) {
        self.otherPc = otherPc
        self.label = label
    }

    func onSdp(_ sdp: String) {
        otherPc.setRemoteDescription(sdp)
    }

    func onCandidate(_ candidate: String, mid: String) {
        otherPc.addRemoteCandidate(candidate, mid: mid)
    }

    func onDataChannel(_ dc: DCDataChannel?) {
        NSLog("%@ onDataChannel", label)
        // this is important, we need save this dc object somewhere,
        // otherwise it will be destructed after this callback returns.
        self.dc = dc
        dc?.onMessage(self)
        dc?.sendText(String(format: "Hello world from %@ %@", label, DCLibDC.version()))
    }

    func onText(_ msg: String) {
        NSLog("%@ onText %@", label, msg)
    }

    func onBinary(_ msg: Data) {
        NSLog("%@ onBinary", label)
    }
}

struct ContentView: View {
    init() {
        DispatchQueue.global().async {
            DCPeerConnection.initLogger(DCLogLevel.debug, callback: TestLogCallback())

            let config = DCLibDC.rtcConfiguration()

            let pc1 = DCPeerConnection.create(config)
            let pc2 = DCPeerConnection.create(config)

            let test1 = DcTest(pc2!, "pc1")
            let test2 = DcTest(pc1!, "pc2")

            pc1?.onLocalDescription(test1)
            pc2?.onLocalDescription(test2)

            pc1?.onLocalCandidate(test1)
            pc2?.onLocalCandidate(test2)

            pc2?.onDataChannel(test2)

            let dc1 = pc1?.createDataChannel("test")
            dc1?.onMessage(test1)

            dc1?.onOpen(DcOpenCallback(dc1!, "pc1"))
        }
    }
    
    var body: some View {
        VStack {
            Image(systemName: "globe")
                .imageScale(.large)
                .foregroundColor(.accentColor)
            Text(String(format: "Hello world %@!", DCLibDC.version()))
        }
        .padding()
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
