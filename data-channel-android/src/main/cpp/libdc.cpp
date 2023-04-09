#include <jni.h>
#include <android/log.h>

#include <utility>

#include "rtc/rtc.hpp"



extern "C" {

rtc::PeerConnection* g_pc1;
rtc::PeerConnection* g_pc2;

std::shared_ptr<rtc::DataChannel> g_dc1;
std::shared_ptr<rtc::DataChannel> g_dc2;

void log_callback(rtc::LogLevel level, std::string message) {
    __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "log_callback: %d %s", (int)level, message.c_str());
}

JNIEXPORT void JNICALL
Java_org_webrtc_PeerConnection_test(JNIEnv* env, jclass clazz) {
    rtc::InitLogger(rtc::LogLevel::Debug, log_callback);

    rtc::Configuration config;
    //config.iceServers.emplace_back("mystunserver.org:3478");

    g_pc1 = new rtc::PeerConnection(config);
    g_pc2 = new rtc::PeerConnection(config);

    g_pc1->onLocalDescription([](rtc::Description sdp) {
        __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc1 onLocalDescription: %s", std::string(sdp).c_str());
        g_pc2->setRemoteDescription(std::move(sdp));
    });
    g_pc2->onLocalDescription([](rtc::Description sdp) {
        __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc2 onLocalDescription: %s", std::string(sdp).c_str());
        g_pc1->setRemoteDescription(std::move(sdp));
    });

    g_pc1->onLocalCandidate([](rtc::Candidate candidate) {
        __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc1 onLocalCandidate: %s", std::string(candidate).c_str());
        g_pc2->addRemoteCandidate(std::move(candidate));
    });
    g_pc2->onLocalCandidate([](rtc::Candidate candidate) {
        __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc2 onLocalCandidate: %s", std::string(candidate).c_str());
        g_pc1->addRemoteCandidate(std::move(candidate));
    });

    g_pc1->onStateChange([](rtc::PeerConnection::State state) {
        __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc1 onStateChange: %d", (int)state);
    });
    g_pc2->onStateChange([](rtc::PeerConnection::State state) {
        __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc2 onStateChange: %d", (int)state);
    });

    g_pc1->onGatheringStateChange([](rtc::PeerConnection::GatheringState state) {
        __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc1 onGatheringStateChange: %d", (int)state);
    });
    g_pc2->onGatheringStateChange([](rtc::PeerConnection::GatheringState state) {
        __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc2 onGatheringStateChange: %d", (int)state);
    });

    g_pc2->onDataChannel([](std::shared_ptr<rtc::DataChannel> incoming) {
        __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc2 onDataChannel");

        g_dc2 = std::move(incoming);
        g_dc2->send("Hello world from DC2");
        g_dc2->onMessage([](std::variant<rtc::binary, rtc::string> message) {
            if (std::holds_alternative<rtc::string>(message)) {
                __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "DC2 onMessage: %s", get<rtc::string>(message).c_str());
            }
        });
    });


    g_dc1 = g_pc1->createDataChannel("test");
    g_dc1->onOpen([]() {
        __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "DC1 onOpen");

        g_dc1->send("Hello world from DC1");
    });
    g_dc1->onMessage([](std::variant<rtc::binary, rtc::string> message) {
        if (std::holds_alternative<rtc::string>(message)) {
            __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "DC1 onMessage: %s", get<rtc::string>(message).c_str());
        }
    });
}

}
