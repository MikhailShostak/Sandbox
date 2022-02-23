
#include <PBR/PBRMaterial.hpp>

DECLARE_FLAG_OPERATORS(Graphics::ShaderFlags)

inline DynamicAsset<Graphics::Texture> LavaColorTextureAsset = { "LavaColorTexture", [](auto& instance) { Graphics::LoadTexture(instance, "C:/Assets/Lava/Lava_COLOR.png"); } };
inline DynamicAsset<Graphics::Texture> LavaDispTextureAsset = { "LavaDispTexture", [](auto& instance) { Graphics::LoadTexture(instance, "C:/Assets/Lava/Lava_DISP.png"); } };
inline DynamicAsset<Graphics::Mesh> LavaMeshAsset = { "LavaMesh", [](auto& instance) { instance = std::move(*Graphics::AssetLoader::LoadMesh("C:/Assets/Sphere.fbx", "Sphere")); } };

inline DynamicAsset<Graphics::Texture> SkyTextureAsset = { "SkyTexture", [](auto& instance) { Graphics::LoadTexture(instance, "C:/Assets/Sky2.jpg"); } };
inline DynamicAsset<Graphics::Mesh> SkyMeshAsset = { "SkyMesh", [](auto& instance) { instance = std::move(*Graphics::AssetLoader::LoadMesh("C:/Assets/Sky.fbx", "Sky")); } };

inline DynamicAsset<Graphics::Texture> TableTextureAsset = { "TableTexture", [](auto& instance) { Graphics::LoadTexture(instance, "C:/Assets/Meshes/Table/table.png"); } };
inline DynamicAsset<Graphics::Mesh> TableMeshAsset = { "TableMesh", [](auto& instance) { instance = std::move(*Graphics::AssetLoader::LoadMesh("C:/Assets/Meshes/Table/table.fbx", "table")); } };

inline DynamicAsset<Graphics::Texture> ChairTextureAsset = { "ChairTexture", [](auto& instance) { Graphics::LoadTexture(instance, "C:/Assets/Meshes/Table/chair.tga"); } };
inline DynamicAsset<Graphics::Mesh> ChairMeshAsset = { "ChairMesh", [](auto& instance) { instance = std::move(*Graphics::AssetLoader::LoadMesh("C:/Assets/Meshes/Table/chair.fbx", "chair")); } };

inline DynamicAsset<Graphics::Texture> UVTextureAsset = { "UVTexture", [](auto& instance) { Graphics::LoadTexture(instance, "C:/Assets/UV.jpg"); } };
inline DynamicAsset<Graphics::Texture> FloorTextureAsset = { "FloorTexture", [](auto& instance) { Graphics::LoadTexture(instance, "C:/Assets/Meshes/Table/floor.jpg"); } };
inline DynamicAsset<Graphics::Texture> GridTextureAsset = { "GridTexture", [](auto& instance) { Graphics::LoadTexture(instance, "C:/Assets/Grid.png"); } };
inline DynamicAsset<Graphics::Mesh> CubeMesh = { "CubeMesh", [](auto& instance) { instance = std::move(*Graphics::AssetLoader::LoadMesh("C:/Assets/EditorContent.fbx", "Cube")); } };
inline DynamicAsset<Graphics::Mesh> ZPlainMeshAsset = { "Z-PlainMesh", [](auto& instance) { instance = std::move(*Graphics::AssetLoader::LoadMesh("C:/Assets/EditorContent.fbx", "Z-Plane")); } };

namespace Serialization
{

struct MaterialProperties : public Graphics::ShaderMetatype
{
    StaticArray<Float4, 64> Data;
    StaticArray<String, 64> Names;
    size_t size = 0;

    MaterialProperties() :
        ShaderMetatype("cbuffer", "Properties", 0)
    {

    }

    void AddProperty(const String& name, const String& reg = String())
    {
        if (Variables.size() < Data.size())
        {
            Names[size] = name;
            Register<Float4>(Graphics::ShaderMapping<Float4>::n, Names[size].data(), !reg.empty() ? reg.data() : nullptr);
            DataSize += sizeof(Float4);
            ++size;
        }
    }

    void SetProperty(const String& name, const Float4& value)
    {
        for (size_t i = 0; i < Data.size(); ++i)
        {
            if (Variables[i].Name == name)
            {
                Data[i] = value;
                break;
            }
        }
    }
};

template<>
struct ObjectSerializer<Graphics::Material>
{
    static String load(const System::Path &path)
    {
        std::ifstream file;
        file.open(path.generic_string());
        if (file.is_open())
        {
            std::ostringstream ss;
            ss << file.rdbuf();
            return ss.str();
        }

        return String();
    }

    template<typename DataType, typename ValueType>
    static void Serialize(DataType&& data, ValueType&& value)
    {
        System::Path VertexShaderPath;
        data["VertexShader"] & VertexShaderPath;
        value.VertexShader.SourceCode = load(VertexShaderPath);


        System::Path PixelShaderPath;
        data["PixelShader"] & PixelShaderPath;
        value.PixelShader.SourceCode = load(PixelShaderPath);

        value.VertexShader.Constants.push_back(g_CameraConstants);
        value.VertexShader.InputLayout = CreateShared<VSInput>();
        value.VertexShader.OutputLayout = CreateShared<PSInput>();
        value.PixelShader.InputLayout = value.VertexShader.OutputLayout;
        value.PixelShader.OutputLayout = CreateShared<PSOutput>();

        Array<::Map<String, Serialization::Data>> Textures;
        data["Textures"] & Textures;
        for (const auto& Texture : Textures)
        {
            Graphics::TextureSampler sampler;

            String samplerName = Serialization::Deserialize<String>(Texture.at("SamplerName"));
            sampler.Name = "g_" + samplerName;

            String textureName = Serialization::Deserialize<String>(Texture.at("TextureName"));
            sampler.Texture = AssetStorage::Load<Graphics::Texture>(textureName);

            bool UseInVertexShader = Serialization::Deserialize<bool>(Texture.at("UseInVertexShader"));
            if (UseInVertexShader)
            {
                sampler.Flags = Graphics::ShaderFlags::UseInVertexShader;
            }

            bool UseInPixelShader = Serialization::Deserialize<bool>(Texture.at("UseInPixelShader"));
            if (UseInPixelShader)
            {
                sampler.Flags |= Graphics::ShaderFlags::UseInPixelShader;
            }

            if (sampler.Flags == Graphics::ShaderFlags::None)
            {
                sampler.Flags |= Graphics::ShaderFlags::UseInPixelShader;
            }

            value.TextureSamplers.push_back(std::move(sampler));
        }

        Array<::Map<String, Serialization::Data>> Properties;
        data["Properties"] & Properties;

        for (const auto& p : Properties)
        {
            String name = Serialization::Deserialize<String>(p.at("Name"));
            if (Serialization::Deserialize<bool>(p.at("UseInVertexShader")))
            {
                if (value.VertexShader.Variables.empty())
                {
                    value.VertexShader.Variables.push_back(CreateShared<MaterialProperties>());
                }
                auto vp = StaticCast<MaterialProperties>(value.VertexShader.Variables[0]);
                vp->AddProperty(name);
            }
            if (Serialization::Deserialize<bool>(p.at("UseInPixelShader")))
            {
                if (value.PixelShader.Variables.empty())
                {
                    value.PixelShader.Variables.push_back(CreateShared<MaterialProperties>());
                }
                auto pp = StaticCast<MaterialProperties>(value.PixelShader.Variables[0]);
                pp->AddProperty(name);
            }
        }

        for (const auto& p : Properties)
        {
            String name = Serialization::Deserialize<String>(p.at("Name"));
            Float4 data = Serialization::Deserialize<Float4>(p.at("Value"));
            if (Serialization::Deserialize<bool>(p.at("UseInVertexShader")))
            {
                auto vp = StaticCast<MaterialProperties>(value.VertexShader.Variables[0]);
                vp->SetProperty(name, data);
            }
            if (Serialization::Deserialize<bool>(p.at("UseInPixelShader")))
            {
                auto pp = StaticCast<MaterialProperties>(value.PixelShader.Variables[0]);
                pp->SetProperty(name, data);
            }
        }
    }
};

}

inline DynamicAsset<Graphics::Material> GridMaterialAsset = { "GridMaterial", [](auto& instance) {
String Material =
R"(
Type: Material
PixelShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Grid/GridMaterial.ps
VertexShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Grid/GridMaterial.vs
Properties:
  - Name: Color
    UseInPixelShader: true
    UseInVertexShader: false
    Value:
      w: 1
      x: 0.5
      y: 0.5
      z: 0.5
  - Name: ImageOffset
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 0
      x: 0
      y: 0
      z: 0
  - Name: ImageScale
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 1
      x: 100
      y: 100
      z: 0
Textures:
  - SamplerName: BaseColor
    TextureName: GridTexture
    UseInPixelShader: false
    UseInVertexShader: false
)";
    Serialization::FromString(Material, instance);
} };

inline DynamicAsset<Graphics::Material> SkyMaterialAsset = { "SkyMaterial", [](auto& instance) {
String Material =
R"(
Type: Material
PixelShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Unlit/UnlitMaterial.ps
VertexShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Unlit/UnlitMaterial.vs
Properties:
  - Name: Color
    UseInPixelShader: true
    UseInVertexShader: false
    Value:
      w: 1
      x: 1
      y: 1
      z: 1
  - Name: ImageOffset
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 0
      x: 0
      y: 0
      z: 0
  - Name: ImageScale
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 1
      x: 1
      y: 1
      z: 0
Textures:
  - SamplerName: BaseColor
    TextureName: SkyTexture
    UseInPixelShader: false
    UseInVertexShader: false
)";
    Serialization::FromString(Material, instance);
} };

inline DynamicAsset<Graphics::Material> TableMaterialAsset = { "TableMaterial", [](auto& instance) {
String Material =
R"(
Type: Material
PixelShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Unlit/UnlitMaterial.ps
VertexShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Unlit/UnlitMaterial.vs
Properties:
  - Name: Color
    UseInPixelShader: true
    UseInVertexShader: false
    Value:
      w: 1
      x: 1
      y: 1
      z: 1
  - Name: ImageOffset
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 0
      x: 0
      y: 0
      z: 0
  - Name: ImageScale
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 1
      x: 1
      y: 1
      z: 0
Textures:
  - SamplerName: BaseColor
    TextureName: TableTexture
    UseInPixelShader: false
    UseInVertexShader: false
)";
    Serialization::FromString(Material, instance);
} };

inline DynamicAsset<Graphics::Material> ChairMaterialAsset = { "ChairMaterial", [](auto& instance) {
String Material =
R"(
Type: Material
PixelShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Unlit/UnlitMaterial.ps
VertexShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Unlit/UnlitMaterial.vs
Properties:
  - Name: Color
    UseInPixelShader: true
    UseInVertexShader: false
    Value:
      w: 1
      x: 1
      y: 1
      z: 1
  - Name: ImageOffset
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 0
      x: 0
      y: 0
      z: 0
  - Name: ImageScale
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 1
      x: 1
      y: 1
      z: 0
Textures:
  - SamplerName: BaseColor
    TextureName: ChairTexture
    UseInPixelShader: false
    UseInVertexShader: false
)";
    Serialization::FromString(Material, instance);
} };

inline DynamicAsset<Graphics::Material> FloorMaterialAsset = { "FloorMaterial", [](auto& instance) {
String Material =
R"(
Type: Material
PixelShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Unlit/UnlitMaterial.ps
VertexShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Unlit/UnlitMaterial.vs
Properties:
  - Name: Color
    UseInPixelShader: true
    UseInVertexShader: false
    Value:
      w: 1
      x: 1
      y: 1
      z: 1
  - Name: ImageOffset
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 0
      x: 0
      y: 0
      z: 0
  - Name: ImageScale
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 1
      x: 10
      y: 10
      z: 0
Textures:
  - SamplerName: BaseColor
    TextureName: FloorTexture
    UseInPixelShader: false
    UseInVertexShader: false
)";
    Serialization::FromString(Material, instance);
} };

inline DynamicAsset<Graphics::Material> UVMaterialAsset = { "UVMaterial", [](auto& instance) {
String Material =
R"(
Type: Material
PixelShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Unlit/UnlitMaterial.ps
VertexShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Unlit/UnlitMaterial.vs
Properties:
  - Name: Color
    UseInPixelShader: true
    UseInVertexShader: false
    Value:
      w: 1
      x: 1
      y: 1
      z: 1
  - Name: ImageOffset
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 0
      x: 0
      y: 0
      z: 0
  - Name: ImageScale
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 1
      x: 10
      y: 10
      z: 0
Textures:
  - SamplerName: BaseColor
    TextureName: UVTexture
    UseInPixelShader: false
    UseInVertexShader: false
)";
    Serialization::FromString(Material, instance);
} };

inline DynamicAsset<Graphics::Material> LavaMaterialAsset = { "LavaMaterial", [](auto& instance) {
String Material =
R"(
Type: Material
PixelShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Displacement/DisplacementMaterial.ps
VertexShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Displacement/DisplacementMaterial.vs
Properties:
  - Name: Color
    UseInPixelShader: true
    UseInVertexShader: false
    Value:
      w: 1
      x: 1
      y: 1
      z: 1
  - Name: ImageOffset
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 0
      x: 0
      y: 0
      z: 0
  - Name: ImageScale
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 1
      x: 3
      y: 3
      z: 0
  - Name: Displacement
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 0
      x: 0.1
      y: 0
      z: 0
Textures:
  - SamplerName: BaseColor
    TextureName: LavaColorTexture
    UseInPixelShader: false
    UseInVertexShader: false
  - SamplerName: DisplacementMap
    TextureName: LavaDispTexture
    UseInPixelShader: false
    UseInVertexShader: true
)";
    Serialization::FromString(Material, instance);
} };

inline DynamicAsset<Graphics::Material> LavaMaterial2Asset = { "LavaMaterial2", [](auto& instance) {
String Material =
R"(
Type: Material
PixelShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Displacement/DisplacementMaterial.ps
VertexShader: D:/Projects/CMake/Sandbox/Sandbox/Assets/Displacement/DisplacementMaterial.vs
Properties:
  - Name: Color
    UseInPixelShader: true
    UseInVertexShader: false
    Value:
      w: 1
      x: 1
      y: 1
      z: 1
  - Name: ImageOffset
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 0
      x: 0
      y: 0
      z: 0
  - Name: ImageScale
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 1
      x: 10
      y: 10
      z: 0
  - Name: Displacement
    UseInPixelShader: false
    UseInVertexShader: true
    Value:
      w: 0
      x: 0.4
      y: 0
      z: 0
Textures:
  - SamplerName: BaseColor
    TextureName: LavaColorTexture
    UseInPixelShader: false
    UseInVertexShader: false
  - SamplerName: DisplacementMap
    TextureName: LavaDispTexture
    UseInPixelShader: false
    UseInVertexShader: true
)";
    Serialization::FromString(Material, instance);
} };

SceneViewport::SceneViewport()
{
    g_DrawRequests.insert({ this, [&](auto& context)
        {
            ECS::Update(*ViewportScene);
        }
    });

    MSAAFactor = 2;

    ContentScene = CreateShared<EScene>();
}

SceneViewport::~SceneViewport()
{
    g_DrawRequests.erase(this);
    boost::remove_erase(g_SceneWindow->Scene.Scenes, ViewportScene);
}

void SceneViewport::Draw(const std::function<void()>& Toolbar)
{
    if (!ViewportScene)
    {
        ViewportScene = CreateShared<EScene>();
        g_SceneWindow->Scene.Scenes.push_back(ViewportScene);

        String SceneData =
R"(
Systems:
  - Type: ECS.UIInputSystem
  - Type: ECS.MovementSystem
  - Type: ECS.PawnSystem
  - Type: ECS.GraphicsSystem
    Values:
      CurrentCamera:
        Type: Camera$
  - Type: ECS.SceneSystem
Entities:
  - Name: Camera
    Components:
      - Type: ECS.CameraComponent
        Values:
          Camera:
            Transform:
              Position:
                y: 3.0
                z: 1.0
            Resolution:
              x: 1
              y: 1
            FarPlane: 1000
      - Type: ECS.MovementComponent
      - Type: ECS.PawnComponent
        Values:
          Speed: 2
          Mobility: 0.1
          RelativeInput: y
  - Name: Viewport
    Components:
      - Type: ECS.UIViewComponent 
      - Type: ECS.RootComponent 
      - Type: ECS.HirerachyComponent
      - Type: ECS.InputComponent
        Values:
          Handlers:
            - Type: FreeCameraInputHandler
              Values:
                CurrentCamera:
                  Type: Camera$
                Sensetivity:
                  x: 0.1
                  y: 0.1
  - Name: Grid
    Components:
      - Type: ECS.TransformComponent
        Values:
          Transform:
            Scale:
              x: 100
              y: 100
      - Type: ECS.MeshComponent
        Values:
          Mesh:
            Type: Z-PlainMesh
          Material:
            Type: GridMaterial
)";
        Serialization::FromString<EScene>(SceneData, *ViewportScene);

        for (auto& system : ViewportScene->Systems)
        {
            system->m_GraphicsContext = g_GraphicsContext;
            system->m_Resolution = { 1, 1 };
        }

        ECS::Load(*ViewportScene);

        auto graphics = ECS::FindSystem<ECS::GraphicsSystem>(*ViewportScene);
        ECS::FindSystem<ECS::SceneSystem>(*ViewportScene)->Scenes.push_back(ContentScene);
        Texture = graphics->GBuffer.Targets[0];
    }

    auto FindPersistentEntity = [](EScene& scene, const String& name) {
        std::tuple<ECS::Entity, ECS::PersistentComponent*> result{};
        auto v = scene.Registry.view<ECS::PersistentComponent>();
        for (const auto& [id, component] : v.each())
        {
            if (component.Name == name)
            {
                result = { { &scene, id }, &component };
            }
        }
        return result;
    };

    ImGui::Begin("Viewport");
    auto size = ImGui::GetContentRegionAvail();
    if (LastSize.x != size.x || LastSize.y != size.y)
    {
        Resize({ size.x, size.y });
    }
    ViewportScene->Registry.view<ECS::UIViewComponent>().each([&](auto& view)
    {
        view.GlobalPosition = { ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y, 0.0f };
        view.Size = { size.x, size.y };
    });

    auto cursorPostion = ImGui::GetCursorPos();
    ImGui::Image(ImGui::TexID(Texture), { (float)Texture->Size.x / MSAAFactor, (float)Texture->Size.y / MSAAFactor });
    if (ImGui::IsItemHovered())
    {
        ImGui::CaptureMouseFromApp(false);
    }
    ImGui::SetCursorPos(cursorPostion);
    if (Toolbar)
    {
        Toolbar();
    }
    ImGui::End();
}

void SceneViewport::Resize(const Int2& Size)
{
    for (auto& system : ViewportScene->Systems)
    {
        system->m_Resolution = Size;
    }
    LastSize = Size;
    auto graphics = ECS::FindSystem<ECS::GraphicsSystem>(*ViewportScene);
    graphics->GBuffer.Resize(Size * MSAAFactor);
    graphics->m_GraphicsContext->CreateRenderTarget(graphics->GBuffer);

    ViewportScene->Registry.view<Graphics::Camera>().each([&](auto &camera) {
        camera.Resolution = Size;
    });
}
