namespace ECS
{

void PostProcessStep::Render(EScene& Scene, const Graphics::RenderBuffer& RenderBuffer)
{
    auto graphics = ECS::FindSystem<ECS::GraphicsSystem>(Scene);

    static SharedReference<Graphics::Mesh> Mesh;
    static Graphics::DrawBatch<Matrix4> Transforms;
    if (!Mesh)
    {
        Mesh = AssetStorage::Load<Graphics::Mesh>("Z-PlainMesh");

        Transforms.MaxSize = 1;
        Transforms.Instances.resize(Transforms.MaxSize);
        Transforms.Instances[0] = Matrix4::identity();
        graphics->m_GraphicsContext->CreateDrawBatch(Transforms);
    }

    graphics->m_GraphicsContext->SetRenderBuffer(RenderBuffer);
    graphics->m_GraphicsContext->ClearRenderBuffers({ 0.0, 0.0, 0.0, 0.0 });
    //m_GraphicsContext->ClearDepthStencilBuffers(1.0f, 0);

    graphics->m_GraphicsContext->ApplyMaterial(*Material);
    graphics->m_GraphicsContext->Draw(*Mesh, Transforms);
}

}
