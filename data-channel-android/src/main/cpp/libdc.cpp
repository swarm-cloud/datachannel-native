#include <jni.h>
#include <android/log.h>

#include <utility>
#include <vector>
#include <thread>
#include <chrono>
#include <unistd.h>

#include "rtc/rtc.hpp"

struct DcTest {
    void test() {
        rtc::Configuration config;

        g_pc1 = new rtc::PeerConnection(config);
        g_pc2 = new rtc::PeerConnection(config);

        g_pc1->onLocalDescription([this](rtc::Description sdp) {
            if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc1 onLocalDescription: %s", std::string(sdp).c_str());
            g_pc2->setRemoteDescription(std::move(sdp));
        });
        g_pc2->onLocalDescription([this](rtc::Description sdp) {
            if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc2 onLocalDescription: %s", std::string(sdp).c_str());
            g_pc1->setRemoteDescription(std::move(sdp));
        });

        g_pc1->onLocalCandidate([this](rtc::Candidate candidate) {
            if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc1 onLocalCandidate: %s", std::string(candidate).c_str());
            g_pc2->addRemoteCandidate(std::move(candidate));
        });
        g_pc2->onLocalCandidate([this](rtc::Candidate candidate) {
            if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc2 onLocalCandidate: %s", std::string(candidate).c_str());
            g_pc1->addRemoteCandidate(std::move(candidate));
        });

        g_pc1->onStateChange([this](rtc::PeerConnection::State state) {
            if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc1 onStateChange: %d", (int)state);
        });
        g_pc2->onStateChange([this](rtc::PeerConnection::State state) {
            if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc2 onStateChange: %d", (int)state);
        });

        g_pc1->onGatheringStateChange([this](rtc::PeerConnection::GatheringState state) {
            if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc1 onGatheringStateChange: %d", (int)state);
        });
        g_pc2->onGatheringStateChange([this](rtc::PeerConnection::GatheringState state) {
            if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc2 onGatheringStateChange: %d", (int)state);
        });

        g_pc2->onDataChannel([this](std::shared_ptr<rtc::DataChannel> incoming) {
            if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "pc2 onDataChannel");

            g_dc2 = std::move(incoming);
            //g_dc2->send("Hello world from DC2");
            g_dc2->onMessage([this](std::variant<rtc::binary, rtc::string> message) {
                if (std::holds_alternative<rtc::string>(message)) {
                    if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "DC2 onMessage: %s", get<rtc::string>(message).c_str());
                }
            });
        });


        auto dc1 = g_pc1->createDataChannel("test");
        dc1->onOpen([this, dc1]() {
            if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "DC1 onOpen");

            g_dc1 = dc1;
            //g_dc1->send("Hello world from DC1");
        });
        dc1->onMessage([this](std::variant<rtc::binary, rtc::string> message) {
            if (std::holds_alternative<rtc::string>(message)) {
                if (log) __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "DC1 onMessage: %s", get<rtc::string>(message).c_str());
            }
        });
    }

    bool log;
    int msg_count;

    rtc::PeerConnection* g_pc1;
    rtc::PeerConnection* g_pc2;

    std::shared_ptr<rtc::DataChannel> g_dc1;
    std::shared_ptr<rtc::DataChannel> g_dc2;
};

static void log_callback(rtc::LogLevel level, std::string message) {
    __android_log_print(ANDROID_LOG_ERROR, "XXPXX", "log_callback: %d %s", (int)level, message.c_str());
}

static uint64_t timeMillis() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

static void test_thread(std::vector<DcTest*>* test_dc) {
    bool running = true;
    while (running) {
        auto start = timeMillis();
        for (int i = 0; i < test_dc->size(); i++) {
            auto dc = test_dc->at(i);
            if (dc->msg_count < 0) {
                running = false;
                break;
            }

            if (dc->g_dc1 && dc->g_dc2) {
                std::string msg1 = "Hello world ";
                msg1.append(std::to_string(dc->msg_count))
                    .append(" from DC ")
                    .append(std::to_string(i))
                    .append(" 1");
                dc->g_dc1->send(msg1);

                std::string msg2 = "Hello world ";
                msg2.append(std::to_string(dc->msg_count))
                    .append(" from DC ")
                    .append(std::to_string(i))
                    .append(" 2");
                dc->g_dc2->send(msg2);

                dc->msg_count--;
            }
        }
        auto end = timeMillis();
        if (end - start < 30) {
            usleep((50 - (end - start)) * 1000);
        }
    }
}

extern "C" {

JNIEXPORT void JNICALL
Java_com_cdnbye_libdc_LibDC_00024Companion_test(JNIEnv* env, jobject thiz,
                                                jboolean log, jint pc_count, jint msg_count) {
    //rtc::InitLogger(rtc::LogLevel::Debug, log_callback);

    auto test_dc = new std::vector<DcTest*>();
    for (int i = 0; i < pc_count; i++) {
        auto dc = new DcTest();
        dc->msg_count = msg_count;
        dc->log = log;
        test_dc->push_back(dc);
        dc->test();
    }

    new std::thread(test_thread, test_dc);
}

}
