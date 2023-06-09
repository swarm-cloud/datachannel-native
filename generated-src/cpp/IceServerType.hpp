// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#pragma once

#include <functional>

namespace libdc {

enum class IceServerType : int {
    STUN = 0,
    TURN = 1,
};

constexpr const char* to_string(IceServerType e) noexcept {
    constexpr const char* names[] = {
        "Stun",
        "Turn",
    };
    return names[static_cast<int>(e)];
}

} // namespace libdc

namespace std {

template <>
struct hash<::libdc::IceServerType> {
    size_t operator()(::libdc::IceServerType type) const {
        return std::hash<int>()(static_cast<int>(type));
    }
};

} // namespace std
