//
// Created by Piasy Xu on 2023/4/9.
//

#include "DataChannelImpl.h"

#include "DcMessageCallback.hpp"
#include "DcEventCallback.hpp"
#include "DcErrorCallback.hpp"

namespace libdc {

DataChannelImpl::DataChannelImpl(std::shared_ptr<rtc::DataChannel> dc) : dc_(std::move(dc)) {
}

void DataChannelImpl::close() {
    if (dc_) {
        dc_->close();
    }
}

bool DataChannelImpl::sendText(const std::string& msg) {
    return dc_ && dc_->send(msg);
}

bool DataChannelImpl::sendBinary(const std::vector<uint8_t>& msg) {
    return dc_ && dc_->send(reinterpret_cast<const std::byte*>(msg.data()), msg.size());
}

bool DataChannelImpl::isOpen() {
    return dc_ && dc_->isOpen();
}

bool DataChannelImpl::isClosed() {
    return dc_ && dc_->isClosed();
}

int32_t DataChannelImpl::maxMessageSize() {
    return dc_ ? (int) (dc_->maxMessageSize()) : 0;
}

int32_t DataChannelImpl::bufferedAmount() {
    return dc_ ? (int) (dc_->bufferedAmount()) : 0;
}

void DataChannelImpl::onOpen(const std::shared_ptr<DcEventCallback>& callback) {
    if (dc_) {
        dc_->onOpen([callback]() {
            callback->onEvent();
        });
    }
}

void DataChannelImpl::onClosed(const std::shared_ptr<DcEventCallback>& callback) {
    if (dc_) {
        dc_->onClosed([callback]() {
            callback->onEvent();
        });
    }
}

void DataChannelImpl::onError(const std::shared_ptr<DcErrorCallback>& callback) {
    if (dc_) {
        dc_->onError([callback](const std::string& error) {
            callback->onError(error);
        });
    }
}

void DataChannelImpl::onMessage(const std::shared_ptr<DcMessageCallback>& callback) {
    if (dc_) {
        dc_->onMessage([callback](std::variant<rtc::binary, rtc::string> message) {
            if (std::holds_alternative<rtc::string>(message)) {
                callback->onText(get<rtc::string>(message));
            } else {
                auto& bin = get<rtc::binary>(message);
                std::vector<uint8_t> msg(bin.size());
                memcpy(msg.data(), bin.data(), bin.size());
                callback->onBinary(msg);
            }
        });
    }
}

void DataChannelImpl::onBufferedAmountLow(const std::shared_ptr<DcEventCallback>& callback) {
    if (dc_) {
        dc_->onBufferedAmountLow([callback]() {
            callback->onEvent();
        });
    }
}

void DataChannelImpl::setBufferedAmountLowThreshold(int32_t amount) {
    if (dc_) {
        dc_->setBufferedAmountLowThreshold(amount);
    }
}

} // libdc
