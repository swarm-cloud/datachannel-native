//
// Created by Piasy Xu on 2023/4/9.
//

#include "PeerConnectionImpl.h"
#include "DataChannelImpl.h"
#include "LibVersion.hpp"

#include "Configuration.hpp"

#include "SdpCallback.hpp"
#include "CandidateCallback.hpp"

#include "IceState.hpp"
#include "IceStateCallback.hpp"

#include "GatheringState.hpp"
#include "GatheringStateCallback.hpp"

#include "SignalingState.hpp"
#include "SignalingStateCallback.hpp"

#include "DataChannelInit.hpp"
#include "DcCallback.hpp"

#include "LogLevel.hpp"
#include "LogCallback.hpp"

namespace libdc {

static rtc::IceServer::Type toRtcIceServerType(IceServerType type) {
    switch (type) {
        case IceServerType::STUN:
            return rtc::IceServer::Type::Stun;
        case IceServerType::TURN:
        default:
            return rtc::IceServer::Type::Turn;
    }
}

static rtc::IceServer::RelayType toRtcIceServerRelayType(IceServerRelayType type) {
    switch (type) {
        case IceServerRelayType::TURNTCP:
            return rtc::IceServer::RelayType::TurnTcp;
        case IceServerRelayType::TURNTLS:
            return rtc::IceServer::RelayType::TurnTls;
        case IceServerRelayType::TURNUDP:
        default:
            return rtc::IceServer::RelayType::TurnUdp;
    }
}

static rtc::ProxyServer::Type toRtcProxyServerType(ProxyServerType type) {
    switch (type) {
        case ProxyServerType::SOCKS5:
            return rtc::ProxyServer::Type::Socks5;
        case ProxyServerType::HTTP:
        default:
            return rtc::ProxyServer::Type::Http;
    }
}

static rtc::CertificateType toRtcCertificateType(CertificateType type) {
    switch (type) {
        case CertificateType::ECDSA:
            return rtc::CertificateType::Ecdsa;
        case CertificateType::RSA:
            return rtc::CertificateType::Rsa;
        case CertificateType::DEFAULT:
        default:
            return rtc::CertificateType::Default;
    }
}

static rtc::TransportPolicy toRtcTransportPolicy(TransportPolicy type) {
    switch (type) {
        case TransportPolicy::RELAY:
            return rtc::TransportPolicy::Relay;
        case TransportPolicy::ALL:
        default:
            return rtc::TransportPolicy::All;
    }
}

static rtc::Configuration toRtcConfig(const Configuration& config) {
    rtc::Configuration rtcConfig;

    for (auto& server: config.iceServers) {
        if (server.url) {
            rtcConfig.iceServers.emplace_back(server.url.value());
        } else {
            rtc::IceServer iceServer(server.hostname, server.port);
            iceServer.type = toRtcIceServerType(server.type);
            iceServer.username = server.username;
            iceServer.password = server.password;
            iceServer.relayType = toRtcIceServerRelayType(server.relayType);

            rtcConfig.iceServers.emplace_back(iceServer);
        }
    }
    if (config.proxyServer) {
        rtcConfig.proxyServer = rtc::ProxyServer(toRtcProxyServerType(config.proxyServer->type),
                                                 config.proxyServer->hostname,
                                                 config.proxyServer->port);
    }
    rtcConfig.bindAddress = config.bindAddress;

    rtcConfig.certificateType = toRtcCertificateType(config.certificateType);
    rtcConfig.iceTransportPolicy = toRtcTransportPolicy(config.iceTransportPolicy);

    rtcConfig.enableIceTcp = config.enableIceTcp;
    rtcConfig.enableIceUdpMux = config.enableIceUdpMux;
    rtcConfig.disableAutoNegotiation = config.disableAutoNegotiation;
    rtcConfig.forceMediaTransport = config.forceMediaTransport;

    rtcConfig.portRangeBegin = config.portRangeBegin;
    rtcConfig.portRangeEnd = config.portRangeEnd;

    rtcConfig.mtu = config.mtu;
    rtcConfig.maxMessageSize = config.maxMessageSize;

    return rtcConfig;
}

static rtc::Reliability::Type toRtcReliabilityType(ReliabilityType type) {
    switch (type) {
        case ReliabilityType::REXMIT:
            return rtc::Reliability::Type::Rexmit;
        case ReliabilityType::TIMED:
            return rtc::Reliability::Type::Timed;
        case ReliabilityType::RELIABLE:
        default:
            return rtc::Reliability::Type::Reliable;
    }
}

static rtc::DataChannelInit toRtcDcInit(const DataChannelInit& init) {
    rtc::DataChannelInit rtcInit;

    rtcInit.reliability.type = toRtcReliabilityType(init.reliability.type);
    rtcInit.reliability.unordered = init.reliability.unordered;
    rtcInit.reliability.rexmit = std::chrono::milliseconds(init.reliability.rexmit_ms);

    rtcInit.negotiated = init.negotiated;
    rtcInit.id = init.id;
    rtcInit.protocol = init.protocol;

    return rtcInit;
}

static IceState fromRtcIceState(rtc::PeerConnection::State state) {
    switch (state) {
        case rtc::PeerConnection::State::Connecting:
            return IceState::CONNECTING;
        case rtc::PeerConnection::State::Connected:
            return IceState::CONNECTED;
        case rtc::PeerConnection::State::Disconnected:
            return IceState::DISCONNECTED;
        case rtc::PeerConnection::State::Failed:
            return IceState::FAILED;
        case rtc::PeerConnection::State::Closed:
            return IceState::CLOSED;
        case rtc::PeerConnection::State::New:
        default:
            return IceState::NEW;
    }
}

static GatheringState fromRtcGatheringState(rtc::PeerConnection::GatheringState state) {
    switch (state) {
        case rtc::PeerConnection::GatheringState::InProgress:
            return GatheringState::INPROGRESS;
        case rtc::PeerConnection::GatheringState::Complete:
            return GatheringState::COMPLETE;
        case rtc::PeerConnection::GatheringState::New:
        default:
            return GatheringState::NEW;
    }
}

static SignalingState fromRtcSignalingState(rtc::PeerConnection::SignalingState state) {
    switch (state) {
        case rtc::PeerConnection::SignalingState::HaveLocalOffer:
            return SignalingState::HAVELOCALOFFER;
        case rtc::PeerConnection::SignalingState::HaveRemoteOffer:
            return SignalingState::HAVEREMOTEOFFER;
        case rtc::PeerConnection::SignalingState::HaveLocalPranswer:
            return SignalingState::HAVELOCALPRANSWER;
        case rtc::PeerConnection::SignalingState::HaveRemotePranswer:
            return SignalingState::HAVEREMOTEPRANSWER;
        case rtc::PeerConnection::SignalingState::Stable:
        default:
            return SignalingState::STABLE;
    }
}

static rtc::LogLevel toRtcLogLevel(LogLevel level) {
    switch (level) {
        case LogLevel::FATAL:
            return rtc::LogLevel::Fatal;
        case LogLevel::ERROR:
            return rtc::LogLevel::Error;
        case LogLevel::WARNING:
            return rtc::LogLevel::Warning;
        case LogLevel::INFO:
            return rtc::LogLevel::Info;
        case LogLevel::DEBUG:
            return rtc::LogLevel::Debug;
        case LogLevel::VERBOSE:
            return rtc::LogLevel::Verbose;
        case LogLevel::NONE:
        default:
            return rtc::LogLevel::None;
    }
}

static inline LogLevel fromRtcLogLevel(rtc::LogLevel level) {
    switch (level) {
        case rtc::LogLevel::Fatal:
            return LogLevel::FATAL;
        case rtc::LogLevel::Error:
            return LogLevel::ERROR;
        case rtc::LogLevel::Warning:
            return LogLevel::WARNING;
        case rtc::LogLevel::Info:
            return LogLevel::INFO;
        case rtc::LogLevel::Debug:
            return LogLevel::DEBUG;
        case rtc::LogLevel::Verbose:
            return LogLevel::VERBOSE;
        case rtc::LogLevel::None:
        default:
            return LogLevel::NONE;
    }
}

std::shared_ptr<PeerConnection> PeerConnection::create(const Configuration& config) {
    return std::make_shared<PeerConnectionImpl>(config);
}

void PeerConnection::initLogger(LogLevel level, const std::shared_ptr<LogCallback>& callback) {
    rtc::InitLogger(toRtcLogLevel(level),
                    [callback](rtc::LogLevel l, const std::string& message) {
                        callback->onLog(fromRtcLogLevel(l), message);
                    });
}

PeerConnectionImpl::PeerConnectionImpl(const Configuration& config) : pc_(toRtcConfig(config)) {
}

void PeerConnectionImpl::close() {
    pc_.close();
}

void PeerConnectionImpl::setRemoteDescription(const std::string& sdp) {
    pc_.setRemoteDescription(rtc::Description(sdp));
}

void PeerConnectionImpl::addRemoteCandidate(const std::string& candidate, const std::string& mid) {
    pc_.addRemoteCandidate(rtc::Candidate(candidate, mid));
}

void PeerConnectionImpl::onLocalDescription(const std::shared_ptr<SdpCallback>& callback) {
    pc_.onLocalDescription([callback](const rtc::Description& sdp) {
        callback->onSdp(std::string(sdp));
    });
}

void PeerConnectionImpl::onLocalCandidate(const std::shared_ptr<CandidateCallback>& callback) {
    pc_.onLocalCandidate([callback](const rtc::Candidate& candidate) {
        callback->onCandidate(candidate.candidate(), candidate.mid());
    });
}

void PeerConnectionImpl::onStateChange(const std::shared_ptr<IceStateCallback>& callback) {
    pc_.onStateChange([callback](rtc::PeerConnection::State state) {
        callback->onStateChanged(fromRtcIceState(state));
    });
}

void PeerConnectionImpl::onGatheringStateChange(
        const std::shared_ptr<GatheringStateCallback>& callback) {
    pc_.onGatheringStateChange([callback](rtc::PeerConnection::GatheringState state) {
        callback->onStateChanged(fromRtcGatheringState(state));
    });
}

void PeerConnectionImpl::onSignalingStateChange(
        const std::shared_ptr<SignalingStateCallback>& callback) {
    pc_.onSignalingStateChange([callback](rtc::PeerConnection::SignalingState state) {
        callback->onStateChanged(fromRtcSignalingState(state));
    });
}

IceState PeerConnectionImpl::state() {
    return fromRtcIceState(pc_.state());
}

GatheringState PeerConnectionImpl::gatheringState() {
    return fromRtcGatheringState(pc_.gatheringState());
}

SignalingState PeerConnectionImpl::signalingState() {
    return fromRtcSignalingState(pc_.signalingState());
}

void PeerConnectionImpl::clearStats() {
    pc_.clearStats();
}

int32_t PeerConnectionImpl::bytesSent() {
    return pc_.bytesSent();
}

int32_t PeerConnectionImpl::bytesReceived() {
    return pc_.bytesReceived();
}

int64_t PeerConnectionImpl::rtt() {
    auto rtt = pc_.rtt();
    return rtt.has_value() ? rtt->count() : -1;
}

void PeerConnectionImpl::onDataChannel(const std::shared_ptr<DcCallback>& callback) {
    pc_.onDataChannel([callback](std::shared_ptr<rtc::DataChannel> incoming) {
        callback->onDataChannel(std::make_shared<DataChannelImpl>(incoming));
    });
}

std::shared_ptr<DataChannel> PeerConnectionImpl::createDataChannel(const std::string& label,
                                                                   const DataChannelInit& init) {
    return std::make_shared<DataChannelImpl>(pc_.createDataChannel(label, toRtcDcInit(init)));
}

std::string LibVersion::version() { return "1.0.8"; }

} // libdc
