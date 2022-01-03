#include "PrivateImplementation.hpp"

namespace Graphics
{

SwapChain::SwapChain()
{

}

SwapChain::~SwapChain()
{

}

void SwapChain::Resize(const hlslpp::int2 &resolution)
{
    Data->Handle->Resize(resolution.x, resolution.y);
}

std::tuple<Graphics::RenderBuffer/*RenderBuffer*/> SwapChain::GetRenderBuffer()
{
    Graphics::RenderBuffer buffer;
    buffer.Data->RenderTargets[0] = ConstCast(Data->Handle)->GetCurrentBackBufferRTV();
    buffer.Data->DepthStencilBuffer = ConstCast(Data->Handle)->GetDepthBufferDSV();
    return { buffer };
}

void SwapChain::Swap()
{
#if PLATFORM_MACOS
    //TODO: fix swap
    //glfwSwapBuffers(window);
#else
    if (Data->Handle)
    {
        Data->Handle->Present();
    }
#endif
}

}
