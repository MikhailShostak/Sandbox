#pragma once

namespace ClassGen
{
struct TextureSamplerInfo
{
    using This = TextureSamplerInfo;
    String SamplerName = {};
    String TextureName = {};
    bool UseInVertexShader = {};
    bool UseInPixelShader = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["SamplerName"] & SamplerName;
        data["TextureName"] & TextureName;
        data["UseInVertexShader"] & UseInVertexShader;
        data["UseInPixelShader"] & UseInPixelShader;
    }

    void Initialize()
    {
    }
};
}
