// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from libdc.djinni

#pragma once

#include <string>

namespace libdc {

class CandidateCallback {
public:
    virtual ~CandidateCallback() {}

    virtual void onCandidate(const std::string & candidate, const std::string & mid) = 0;
};

}  // namespace libdc