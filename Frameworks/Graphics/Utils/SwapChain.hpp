#pragma once

namespace Graphics
{
struct SwapChain
{
    using This = SwapChain;
    InplaceStorage<SwapChainPrivateData, 8, 8> Data;
    Graphics::RenderBuffer RenderBuffer;
    SwapChain();
    ~SwapChain();

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Resize(const hlslpp::int2 & Resolution);
    virtual void Swap();
    virtual std::tuple<Graphics::RenderBuffer/*RenderBuffer*/> GetRenderBuffer();
};
}
