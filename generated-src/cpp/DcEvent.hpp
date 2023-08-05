// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#pragma once

#include <functional>

namespace libdc {

enum class DcEvent : int {
    OPEN = 0,
    CLOSED = 1,
    BUFFEREDAMOUNTLOW = 2,
};

constexpr const char* to_string(DcEvent e) noexcept {
    constexpr const char* names[] = {
        "Open",
        "Closed",
        "BufferedAmountLow",
    };
    return names[static_cast<int>(e)];
}

} // namespace libdc

namespace std {

template <>
struct hash<::libdc::DcEvent> {
    size_t operator()(::libdc::DcEvent type) const {
        return std::hash<int>()(static_cast<int>(type));
    }
};

} // namespace std