#include "PrivateImplementation.hpp"

namespace Graphics
{

SwapChain::SwapChain() = default;
SwapChain::SwapChain(SwapChain&& other) = default;
SwapChain& SwapChain::operator =(SwapChain&& other) = default;
SwapChain::~SwapChain() = default;

void SwapChain::Resize(const hlslpp::int2 &resolution)
{
    Data->Handle->Resize(resolution.x, resolution.y);
}

Graphics::RenderBuffer/*RenderBuffer*/ SwapChain::GetRenderBuffer()
{
    Graphics::RenderBuffer buffer;
    buffer.Data->RenderTargets[0] = ConstCast(Data->Handle)->GetCurrentBackBufferRTV();
    buffer.Data->DepthStencilBuffer = ConstCast(Data->Handle)->GetDepthBufferDSV();
    return buffer;
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
