#pragma once

namespace ClassGen
{
struct AssetInfo
    : public ClassGen::BaseInfo
{
    using This = AssetInfo;
    using Super = ClassGen::BaseInfo;
    ClassGen::TypeInfo BaseType = {};
    SortedMap<String, Serialization::Data> Values = {};

    virtual ~AssetInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["BaseType"] & BaseType;
        data["Values"] & Values;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
