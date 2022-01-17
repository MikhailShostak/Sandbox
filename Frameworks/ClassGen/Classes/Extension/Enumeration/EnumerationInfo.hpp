#pragma once

namespace ClassGen
{
struct EnumerationInfo
    : public ClassGen::BaseInfo
{
    using This = EnumerationInfo;
    using Super = ClassGen::BaseInfo;
    Array<String> Values;

    virtual ~EnumerationInfo() {}

    template<typename T>
    void Serialize(T &&data)
    {
        data["Values"] & Values;
    }
};
}
