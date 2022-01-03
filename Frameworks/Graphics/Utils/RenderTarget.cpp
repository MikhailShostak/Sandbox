#include <PrivateImplementation.hpp>

namespace Graphics
{

RenderTarget::RenderTarget() :
    IsCompiled(false)
{

}

std::tuple<Graphics::RenderBuffer/*RenderBuffer*/> RenderTarget::GetBuffer()
{
    Graphics::RenderBuffer buffer;
    buffer.Data->Size = Targets.size();
    size_t i = 0;
    for (auto &texture : Targets)
    {
        buffer.Data->RenderTargets[i++] = texture->Data->Handle->GetDefaultView(Diligent::TEXTURE_VIEW_RENDER_TARGET);
    }

    if (DepthStencil)
    {
        buffer.Data->DepthStencilBuffer = DepthStencil->Data->Handle->GetDefaultView(Diligent::TEXTURE_VIEW_DEPTH_STENCIL);
    }

    return { std::move(buffer) };
}

void RenderTarget::Resize(const hlslpp::int2 &Size)
{
    auto newSize = hlslpp::int3{ Size, 1 };
    for (auto &texture : Targets)
    {
        texture->Size = newSize;
        texture->Channels = 4;
    }
    if (DepthStencil)
    {
        DepthStencil->Size = newSize;
        DepthStencil->Channels = 4;
    }

    IsCompiled = false;
}

}
