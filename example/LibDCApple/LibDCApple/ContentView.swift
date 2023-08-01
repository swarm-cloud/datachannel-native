//
//  ContentView.swift
//  libDCiOSExample
//
//  Created by Piasy Xu on 2023/7/2.
//

import SwiftUI
import datachannel_wrapper

struct ContentView: View {
    init() {
        DispatchQueue.global().async {
            DCPeerConnection.initLogger(DCLogLevel.debug) { level, message in
                NSLog("XXPXX %d %@", level.rawValue, message)
            }

            let config = DCLibDC.rtcConfiguration()

            let pc1 = DCPeerConnection.create(config)
            let pc2 = DCPeerConnection.create(config)

            pc1?.onLocalDescription { sdp in
                pc2?.setRemoteDescription(sdp)
            }
            pc2?.onLocalDescription { sdp in
                pc1?.setRemoteDescription(sdp)
            }

            pc1?.onLocalCandidate { candidate, mid in
                pc2?.addRemoteCandidate(candidate, mid: mid)
            }
            pc2?.onLocalCandidate { candidate, mid in
                pc1?.addRemoteCandidate(candidate, mid: mid)
            }

            var dc2: DCDataChannel? = nil
            pc2?.onDataChannel { dc in
                NSLog("pc2 onDataChannel")
                // this is important, we need save this dc object somewhere,
                // otherwise it will be destructed after this callback returns.
                dc2 = dc

                dc2?.onMessage(text: { msg in
                    NSLog("pc2 onText %@", msg)
                }, binary: { msg in
                    NSLog("pc2 onBinary")
                })
                dc2?.sendText(String(format: "Hello world from pc2 %@", DCLibDC.version()))
            }

            let dc1 = pc1?.createDataChannel("test")
            dc1?.onMessage(text: { msg in
                NSLog("pc1 onText %@", msg)
            }, binary: { msg in
                NSLog("pc1 onBinary")
            })

            dc1?.onOpen { event in
                NSLog("pc1 dc onOpen")
                dc1?.sendText(String(format: "Hello world from pc1 %@", DCLibDC.version()))
            }
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
