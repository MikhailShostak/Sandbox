#pragma once

namespace Graphics
{
struct MaterialRenderingSettings
{
    using This = MaterialRenderingSettings;
    uint8_t StencilReadMask = {};
    uint8_t StencilWriteMask = {};
    bool StencilEnabled = {};
    bool DepthTestEnabled = {};
    bool DepthWriteEnabled = {};
    bool Wireframe = {};
    bool Cullback = {};
    MaterialRenderingSettings();

    template<typename T>
    void Serialize(T &&data)
    {
        data["StencilReadMask"] & StencilReadMask;
        data["StencilWriteMask"] & StencilWriteMask;
        data["StencilEnabled"] & StencilEnabled;
        data["DepthTestEnabled"] & DepthTestEnabled;
        data["DepthWriteEnabled"] & DepthWriteEnabled;
        data["Wireframe"] & Wireframe;
        data["Cullback"] & Cullback;
    }

    void Initialize()
    {
    }
};
}
