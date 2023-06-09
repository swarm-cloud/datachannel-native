// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#pragma once

#include <functional>

namespace libdc {

enum class TransportPolicy : int {
    ALL = 0,
    RELAY = 1,
};

constexpr const char* to_string(TransportPolicy e) noexcept {
    constexpr const char* names[] = {
        "All",
        "Relay",
    };
    return names[static_cast<int>(e)];
}

} // namespace libdc

namespace std {

template <>
struct hash<::libdc::TransportPolicy> {
    size_t operator()(::libdc::TransportPolicy type) const {
        return std::hash<int>()(static_cast<int>(type));
    }
};

} // namespace std
