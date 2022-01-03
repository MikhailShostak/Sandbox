#pragma once

namespace Graphics
{
struct RenderTarget
{
    using This = RenderTarget;
    Array<SharedReference<Graphics::Texture>> Targets;
    SharedReference<Graphics::Texture> DepthStencil;
    bool IsCompiled;
    RenderTarget();

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual std::tuple<Graphics::RenderBuffer/*RenderBuffer*/> GetBuffer();
    virtual void Resize(const hlslpp::int2 & Size);
};
}
