// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from libdc.djinni

#include "DataChannel.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class DCDataChannel;

namespace djinni_generated {

class DataChannel
{
public:
    using CppType = std::shared_ptr<::libdc::DataChannel>;
    using CppOptType = std::shared_ptr<::libdc::DataChannel>;
    using ObjcType = DCDataChannel*;

    using Boxed = DataChannel;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated
