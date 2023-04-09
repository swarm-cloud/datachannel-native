//
// Created by Piasy Xu on 2023/4/9.
//

#include "PeerConnectionImpl.h"
#include "DataChannelImpl.h"

#include "IceState.hpp"
#include "GatheringState.hpp"
#include "Configuration.hpp"
#include "DataChannelInit.hpp"

#include "SdpCallback.hpp"
#include "CandidateCallback.hpp"
#include "IceStateCallback.hpp"
#include "GatheringStateCallback.hpp"
#include "DcCallback.hpp"

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
        rtc::IceServer iceServer(server.hostname, server.port);
        iceServer.type = toRtcIceServerType(server.type);
        iceServer.username = server.username;
        iceServer.password = server.password;
        iceServer.relayType = toRtcIceServerRelayType(server.relayType);

        rtcConfig.iceServers.emplace_back(iceServer);
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

std::shared_ptr<PeerConnection> PeerConnection::create(const Configuration& config) {
    return std::make_shared<PeerConnectionImpl>(config);
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

void PeerConnectionImpl::onDataChannel(const std::shared_ptr<DcCallback>& callback) {
    pc_.onDataChannel([callback](std::shared_ptr<rtc::DataChannel> incoming) {
        callback->onDataChannel(std::make_shared<DataChannelImpl>(incoming));
    });
}

std::shared_ptr<DataChannel>
PeerConnectionImpl::createDataChannel(const std::string& label, const DataChannelInit& init) {
    return std::make_shared<DataChannelImpl>(pc_.createDataChannel(label, toRtcDcInit(init)));
}

} // libdc