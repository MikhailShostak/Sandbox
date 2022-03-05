

inline DynamicAsset<Graphics::Material> GlowMaterialAsset = { "GlowMaterial", [](auto& instance) {
String Material =
R"(
Type: Material
PixelShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/PostProcess/Glow/GlowMaterial.ps
VertexShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/PostProcess/Glow/GlowMaterial.vs
Textures:
  - SamplerName: BaseColor
  - SamplerName: Emission
)";
    Serialization::FromString(Material, instance);
} };


namespace ECS
{

void GlowPostProcessStep::Render(EScene& Scene, const Graphics::RenderBuffer& RenderBuffer)
{
    auto graphics = ECS::FindSystem<ECS::GraphicsSystem>(Scene);
    Material->TextureSamplers[0].Texture = graphics->GBuffer.Targets[0];
    Material->TextureSamplers[1].Texture = graphics->GBuffer.Targets[3];
    Material->VertexShader.Constants.clear();

    Super::Render(Scene, RenderBuffer);
}

}
