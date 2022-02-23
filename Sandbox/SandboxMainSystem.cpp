#include <PBR/PBRMaterial.hpp>

SharedReference<Graphics::Material> CreateSimpleMaterial(Graphics::GraphicsContext &context, const SharedReference<Graphics::Texture> &baseColorTexture, const Graphics::RenderBuffer &buffer)
{
    auto MaterialInstance = CreateShared<Graphics::Material>();

    Graphics::TextureSampler sampler;
    sampler.Name = "g_BaseColor";
    sampler.Texture = baseColorTexture;
    sampler.Flags = Graphics::ShaderFlags::UseInPixelShader;
    MaterialInstance->TextureSamplers.push_back(std::move(sampler));

    MaterialInstance->VertexShader.Constants.push_back(g_CameraConstants);
    MaterialInstance->VertexShader.InputLayout = CreateShared<VSInput>();
    MaterialInstance->VertexShader.OutputLayout = CreateShared<PSInput>();
    MaterialInstance->PixelShader.InputLayout = MaterialInstance->VertexShader.OutputLayout;
    MaterialInstance->PixelShader.OutputLayout = CreateShared<PSOutput>();

    MaterialInstance->VertexShader.SourceCode = R"(
    void main(in VSInput In, out PSInput Out)
    {
        float4x4 InstanceTransform = transpose(MatrixFromRows(In.MtrxRow0, In.MtrxRow1, In.MtrxRow2, In.MtrxRow3));        
        float4x4 mvp = mul(g_ViewProj, InstanceTransform);
        Out.Pos = mul(mvp, float4(In.Pos.xyz, 1.0));
        Out.WorldPos = mul(InstanceTransform, float4(In.Pos.xyz, 1.0));
        Out.Normal = In.Normal.xyz;
        Out.UV  = In.UV.xy;
    }
    )";

    MaterialInstance->PixelShader.SourceCode = R"(
    void main(in PSInput In, out PSOutput Out)
    {
        float4 c = g_BaseColor.Sample(g_BaseColor_sampler, In.UV);
        if (c.a < 0.1f)
        {
	        clip(-1);
            return;
        }

        Out.BaseColor = c;
    }
    )";

    MaterialInstance->RenderBuffer = buffer;

    return MaterialInstance;
}

SharedReference<Graphics::Material> CreateSimplePostEffect(Graphics::GraphicsContext& context, const SharedReference<Graphics::Texture>& baseColorTexture, const Graphics::RenderBuffer& buffer)
{
    auto MaterialInstance = CreateShared<Graphics::Material>();

    Graphics::TextureSampler sampler;
    sampler.Name = "g_BaseColor";
    sampler.Texture = baseColorTexture;
    sampler.Flags = Graphics::ShaderFlags::UseInPixelShader;
    MaterialInstance->TextureSamplers.push_back(std::move(sampler));
    MaterialInstance->Settings.DepthTestEnabled = false;
    MaterialInstance->Settings.DepthWriteEnabled = false;
    MaterialInstance->Settings.StencilEnabled = false;
    MaterialInstance->Settings.Cullback = false;

    MaterialInstance->VertexShader.InputLayout = CreateShared<VSInput>();
    MaterialInstance->VertexShader.OutputLayout = CreateShared<PSInput>();
    MaterialInstance->PixelShader.InputLayout = MaterialInstance->VertexShader.OutputLayout;
    MaterialInstance->PixelShader.OutputLayout = CreateShared<PSOutput>();

    MaterialInstance->VertexShader.SourceCode = R"(
    void main(in VSInput In, out PSInput Out)
    {
        float4x4 InstanceTransform = transpose(MatrixFromRows(In.MtrxRow0, In.MtrxRow1, In.MtrxRow2, In.MtrxRow3));
        Out.Pos = mul(InstanceTransform, float4(In.Pos.xyz, 1.0));
        Out.UV  = In.UV.xy;
    }
    )";

    MaterialInstance->PixelShader.SourceCode = R"(
    void main(in PSInput In, out PSOutput Out)
    {
        float Pi = 6.28318530718; // Pi*2
        float Directions = 16.0; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)
        float Quality = 3.0; // BLUR QUALITY (Default 4.0 - More is better but slower)
        float Radius = 0.01;
    
        float4 c = g_BaseColor.Sample(g_BaseColor_sampler, In.UV);
    
        // Blur calculations
        for(float d = 0.0; d < Pi; d += Pi / Directions)
        {
		    for(float i = 1.0 / Quality; i <= 1.0; i += 1.0 / Quality)
            {
			    c += g_BaseColor.Sample(g_BaseColor_sampler, In.UV + float2(cos(d), sin(d)) * Radius.xx * i );		
            }
        }
    
        // Output to screen
        c /= Quality * Directions - 15.0;

        Out.BaseColor = c;
    }
    )";

    MaterialInstance->RenderBuffer = buffer;

    return MaterialInstance;
}

void SandboxMainSystem::OnLoad(EScene &scene)
{
    auto graphics = ECS::FindSystem<ECS::GraphicsSystem>(scene);
    auto [cameraEntity, cameraComponent, movementComponent, pawnComponent] = ECS::CreateEntity<Graphics::Camera, ECS::MovementComponent, ECS::PawnComponent>(scene);
    //cameraComponent.Transform.Rotation = hlslpp::axisangle(Float3{ 1, 0, 0 }, 90 * (3.14 / 180));
    graphics->CurrentCamera = cameraEntity;

    pawnComponent.Speed = 1.0f;
    pawnComponent.Mobility = 0.2f;
    pawnComponent.RelativeInput = true;

    {
        auto [e, mesh, transform] = ECS::CreateEntity<ECS::MeshComponent, ECS::TransformComponent>(scene);
        mesh.Mesh = Graphics::AssetLoader::LoadMesh("C:/Assets/Sky.fbx", "Sky");
        mesh.Material = CreateSimpleMaterial(*m_GraphicsContext, Graphics::LoadTexture("C:/Assets/Sky.jpg"), graphics->GBuffer.GetBuffer());
    }

    {
        auto [e, mesh, target] = ECS::CreateEntity<ECS::MeshComponent, Graphics::RenderTarget>(scene);

        target.Targets = {
            CreateShared<Graphics::Texture>()
        };
        target.DepthStencil = CreateShared<Graphics::Texture>();
        target.Resize(m_Resolution);
        m_GraphicsContext->CreateRenderTarget(target);

        mesh.Mesh = Graphics::AssetLoader::LoadMesh("C:/Assets/EditorContent.fbx", "Z-Plane");
        mesh.Material = CreateSimplePostEffect(*m_GraphicsContext, graphics->GBuffer.Targets[0], target.GetBuffer());

        {
            auto [e2, view, image, root, hierarchy, input] = ECS::CreateEntity<ECS::UIViewComponent, ECS::UIImageComponent, ECS::RootComponent, ECS::HirerachyComponent, ECS::InputComponent>(scene);
            view.Size = m_Resolution;
            image.Texture = target.Targets[0];

            auto freeCamera = UniqueReference<FreeCameraInputHandler>(Create<FreeCameraInputHandler>());
            freeCamera->CurrentCamera = cameraEntity;
            freeCamera->Sensetivity = { 0.1 };
            input.Handlers.push_back(std::move(freeCamera));

            //auto graphics = ECS::FindSystem<ECS::GraphicsSystem>(scene);
            //CurrentCamera = graphics->CurrentCamera;
        }
    }
}
