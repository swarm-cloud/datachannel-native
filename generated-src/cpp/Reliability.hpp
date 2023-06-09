// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#pragma once

#include "ReliabilityType.hpp"
#include <cstdint>
#include <utility>

namespace libdc {

struct Reliability final {
    ReliabilityType type;
    bool unordered;
    int64_t rexmit_ms;

    Reliability(ReliabilityType type_,
                bool unordered_,
                int64_t rexmit_ms_)
    : type(std::move(type_))
    , unordered(std::move(unordered_))
    , rexmit_ms(std::move(rexmit_ms_))
    {}
};

} // namespace libdc
