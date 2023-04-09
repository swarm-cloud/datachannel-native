// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from libdc.djinni

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace libdc {

class DcMessageCallback {
public:
    virtual ~DcMessageCallback() {}

    virtual void onText(const std::string & msg) = 0;

    virtual void onBinary(const std::vector<uint8_t> & msg) = 0;
};

}  // namespace libdc