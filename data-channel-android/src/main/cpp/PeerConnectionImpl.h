//
// Created by Piasy Xu on 2023/4/9.
//

#pragma once

#include "PeerConnection.hpp"
#include "rtc/rtc.hpp"

namespace libdc {

class PeerConnectionImpl : public PeerConnection {
public:
    PeerConnectionImpl(const Configuration& config);

    ~PeerConnectionImpl() = default;

    void close() override;

    void setRemoteDescription(const std::string& sdp) override;

    void addRemoteCandidate(const std::string& candidate, const std::string& mid) override;

    void onLocalDescription(const std::shared_ptr<SdpCallback>& callback) override;

    void onLocalCandidate(const std::shared_ptr<CandidateCallback>& callback) override;

    void onStateChange(const std::shared_ptr<IceStateCallback>& callback) override;

    void onGatheringStateChange(const std::shared_ptr<GatheringStateCallback>& callback) override;

    void onSignalingStateChange(const std::shared_ptr<SignalingStateCallback>& callback) override;

    void onDataChannel(const std::shared_ptr<DcCallback>& callback) override;

    std::shared_ptr<DataChannel> createDataChannel(const std::string& label,
                                                   const DataChannelInit& init) override;

private:
    rtc::PeerConnection pc_;
};

} // libdc
