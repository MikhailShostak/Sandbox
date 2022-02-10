#pragma once

namespace Graphics
{
struct SwapChain
{
    using This = SwapChain;
    InplaceStorage<SwapChainPrivateData, 8, 8> Data;
    Graphics::RenderBuffer RenderBuffer = {};
    SwapChain();
    SwapChain(SwapChain &&other);
    SwapChain &operator =(SwapChain &&other);

     ~SwapChain();
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Resize(const Int2 & Resolution);
    virtual void Swap();
    virtual Graphics::RenderBuffer/*RenderBuffer*/ GetRenderBuffer();

    void Initialize()
    {
    }
};
}
