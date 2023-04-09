// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from libdc.djinni

#pragma once

#include <memory>
#include <string>

namespace libdc {

class CandidateCallback;
class DataChannel;
class DcCallback;
class GatheringStateCallback;
class IceStateCallback;
class SdpCallback;
struct Configuration;
struct DataChannelInit;

class PeerConnection {
public:
    virtual ~PeerConnection() {}

    virtual void close() = 0;

    virtual void setRemoteDescription(const std::string & sdp) = 0;

    virtual void addRemoteCandidate(const std::string & candidate, const std::string & mid) = 0;

    virtual void onLocalDescription(const std::shared_ptr<SdpCallback> & callback) = 0;

    virtual void onLocalCandidate(const std::shared_ptr<CandidateCallback> & callback) = 0;

    virtual void onStateChange(const std::shared_ptr<IceStateCallback> & callback) = 0;

    virtual void onGatheringStateChange(const std::shared_ptr<GatheringStateCallback> & callback) = 0;

    virtual void onDataChannel(const std::shared_ptr<DcCallback> & callback) = 0;

    virtual std::shared_ptr<DataChannel> createDataChannel(const std::string & label, const DataChannelInit & init) = 0;

    static std::shared_ptr<PeerConnection> create(const Configuration & config);
};

}  // namespace libdc