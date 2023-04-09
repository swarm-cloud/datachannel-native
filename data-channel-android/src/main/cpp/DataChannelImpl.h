//
// Created by Piasy Xu on 2023/4/9.
//

#pragma once

#include "DataChannel.hpp"
#include "rtc/rtc.hpp"

namespace libdc {

class DataChannelImpl : public DataChannel {
public:
    DataChannelImpl(std::shared_ptr<rtc::DataChannel> dc);

    ~DataChannelImpl() = default;

    void close() override;

    bool sendText(const std::string& msg) override;

    bool sendBinary(const std::vector<uint8_t>& msg) override;

    bool isOpen() override;

    bool isClosed() override;

    int32_t maxMessageSize() override;

    int32_t bufferedAmount() override;

    void onOpen(const std::shared_ptr<DcEventCallback>& callback) override;

    void onClosed(const std::shared_ptr<DcEventCallback>& callback) override;

    void onError(const std::shared_ptr<DcErrorCallback>& callback) override;

    void onMessage(const std::shared_ptr<DcMessageCallback>& callback) override;

    void onBufferedAmountLow(const std::shared_ptr<DcEventCallback>& callback) override;

    void setBufferedAmountLowThreshold(int32_t amount) override;

private:
    std::shared_ptr<rtc::DataChannel> dc_;
};

} // libdc
