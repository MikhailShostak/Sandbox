#pragma once

namespace ClassGen
{
struct MaterialProperty
{
    using This = MaterialProperty;
    String Name = {};
    String Attribute = {};
    Float4 Value = {};
    bool UseInVertexShader = {};
    bool UseInPixelShader = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Name"] & Name;
        data["Attribute"] & Attribute;
        data["Value"] & Value;
        data["UseInVertexShader"] & UseInVertexShader;
        data["UseInPixelShader"] & UseInPixelShader;
    }

    void Initialize()
    {
    }
};
}
