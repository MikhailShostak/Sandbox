#pragma once

namespace Graphics
{
struct GraphicsContext
{
    using This = GraphicsContext;
    InplaceStorage<GraphicsContextPrivateData, 128, 8, false> Data;
    Map<Graphics::Mesh*, Array<SharedReference<Graphics::Material>>> Queue = {};
    Graphics::RenderBuffer CurrentRenderBuffer = {};
    GraphicsContext();
    GraphicsContext(GraphicsContext &&other);
    GraphicsContext &operator =(GraphicsContext &&other);

     ~GraphicsContext();
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual bool/*Result*/ Initialize(const Graphics::NativeWindow & NativeWindow, Graphics::SwapChain & SwapChain);
    virtual void CreateDrawBatch(Graphics::DrawBatchBase & Batch);
    virtual void CreateConstants(Graphics::ShaderMetatype & Constants);
    virtual void CreateMesh(Graphics::Mesh & Mesh);
    virtual void Create2DTexture(Graphics::Texture & Texture);
    virtual void CreateMaterial(Graphics::Material & Material);
    virtual void CreateRenderTarget(Graphics::RenderTarget & RenderTarget);
    virtual void ClearRenderBuffers(const hlslpp::float4 & Color);
    virtual void ClearDepthBuffer(float Value);
    virtual void ClearStencilBuffer(uint8_t Value);
    virtual void ClearDepthStencilBuffers(float DepthValue, uint8_t StencilValue);
    virtual void SetRenderBuffer(const Graphics::RenderBuffer & RenderBuffer);
    virtual void Upload(Graphics::DrawBatchBase & Batch);
    virtual void ApplyConstants(Graphics::ShaderMetatype & Constants);
    virtual void SetState(Graphics::PipelineState & State);
    virtual void Draw(Graphics::Mesh & Mesh, Graphics::DrawBatchBase & Batch);
    virtual void Render(Graphics::SwapChain & SwapChain);
    virtual void ApplyMaterial(Graphics::Material & Material);
    virtual void InvalidateMaterial(Graphics::Material & Material);

    void Initialize()
    {
    }
};
}
