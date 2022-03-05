#pragma once

#include "Classes/Extension/Graphics/MaterialGlobalConstants.hpp"

#include <PBR/PBRMaterial.hpp>

namespace ClassGen
{

struct MaterialProperties : public Graphics::ShaderMetatype
{
    StaticArray<Float4, 64> Data;

    MaterialProperties() :
        ShaderMetatype("cbuffer", "Properties", 0)
    {

    }

    void AddProperty(const String& name, const String& reg = String())
    {
        if (Variables.size() < Data.size())
        {
            Register<Float4>(Graphics::ShaderMapping<Float4>::n, name.data(), !reg.empty() ? reg.data() : nullptr);
            DataSize += sizeof(Float4);
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

SharedReference<Graphics::Material>/*Material*/ MaterialInfo::Load(Graphics::GraphicsContext& Context)
{
    if (MaterialInstance)
    {
        return MaterialInstance;
    }

    //MaterialInstance = Graphics::AssetLoader::LoadMaterial(Path, Name);
    MaterialInstance = CreateShared<Graphics::Material>();
    for (const auto &Texture : Textures)
    {
        auto FileInfo = FindClassByName(Texture.TextureName);
        if (auto TextureInfo = DynamicCast<ClassGen::TextureInfo>(FileInfo.Instance))
        {
            Graphics::TextureSampler sampler;
            sampler.Name = "g_" + Texture.SamplerName;
            sampler.Texture = TextureInfo->Load(*g_GraphicsContext);
            sampler.Flags = Texture.UseInVertexShader ? Graphics::ShaderFlags::UseInVertexShader : Graphics::ShaderFlags::UseInPixelShader;
            if (Texture.UseInPixelShader)
            {
                sampler.Flags = Graphics::ShaderFlags(sampler.Flags | Graphics::ShaderFlags::UseInPixelShader);
            }
            MaterialInstance->TextureSamplers.push_back(sampler);
        }
    }

    for (const auto& p : Properties)
    {
        if (p.UseInVertexShader)
        {
            MaterialInstance->VertexShader.Variables.push_back(CreateShared<MaterialProperties>());
            break;
        }
    }
    for (const auto& p : Properties)
    {
        if (p.UseInPixelShader)
        {
            MaterialInstance->PixelShader.Variables.push_back(CreateShared<MaterialProperties>());
            break;
        }
    }

    for (const auto& p : Properties)
    {
        if (p.UseInVertexShader)
        {
            auto vp = StaticCast<MaterialProperties>(MaterialInstance->VertexShader.Variables[0]);
            vp->AddProperty(p.Name, p.Attribute);
        }
        if (p.UseInPixelShader)
        {
            auto pp = StaticCast<MaterialProperties>(MaterialInstance->PixelShader.Variables[0]);
            pp->AddProperty(p.Name, p.Attribute);
        }
    }
    Update();

    MaterialInstance->VertexShader.Constants.push_back(g_CameraConstants);
    MaterialInstance->VertexShader.InputLayout = CreateShared<VSInput>();
    MaterialInstance->VertexShader.OutputLayout = CreateShared<PSInput>();
    MaterialInstance->VertexShader.Variables.push_back(g_GlobalConstants);
    MaterialInstance->PixelShader.InputLayout = MaterialInstance->VertexShader.OutputLayout;
    MaterialInstance->PixelShader.OutputLayout = CreateShared<PSOutput>();

    if (!VertexShader.empty())
    {
        std::ifstream file;
        file.open(VertexShader.generic_string());
        if (file.is_open())
        {
            std::ostringstream ss;
            ss << file.rdbuf();
            MaterialInstance->VertexShader.SourceCode = ss.str();
        }
    }
    else
    {
        MaterialInstance->VertexShader.SourceCode = R"(
    void main(in VSInput In, out PSInput Out)
    {
        // HLSL matrices are row-major while GLSL matrices are column-major. We will
        // use convenience function MatrixFromRows() appropriately defined by the engine
        float4x4 InstanceTransform = transpose(MatrixFromRows(In.MtrxRow0, In.MtrxRow1, In.MtrxRow2, In.MtrxRow3));
        
        // Apply instance transformation
        //float4 TransformedPos = mul(float4(In.Pos.xyz, 1.0), InstanceTransform);
        
        float4x4 mvp = mul(g_ViewProj, InstanceTransform);
        Out.Pos = mul(mvp, float4(In.Pos.xyz, 1.0));
        Out.WorldPos = mul(InstanceTransform, float4(In.Pos.xyz, 1.0));
        Out.Normal = In.Normal.xyz;
        //Out.Pos = Out.Pos / Out.Pos.w;
        Out.UV  = In.UV.xy;
    }
    )";
    }

    if (!PixelShader.empty())
    {
        std::ifstream file;
        file.open(PixelShader.generic_string());
        if (file.is_open())
        {
            std::ostringstream ss;
            ss << file.rdbuf();
            MaterialInstance->PixelShader.SourceCode = ss.str();
        }
    }
    else
    {
        MaterialInstance->PixelShader.SourceCode = R"(
    void main(in PSInput In, out PSOutput Out)
    {
        float2 uv = In.UV;

        Out.BaseColor = g_BaseColor.Sample(g_BaseColor_sampler, uv);
        if (Out.BaseColor.a < 0.1f)
        {
	        clip(-1);
            return;
        }

        float3 normal = In.Normal; //normalize(In.Normal + g_Normal.Sample(g_Normal_sampler, uv));

        float3 light_pos = float3(0.0f, 10.0f, -3.0f);
        float3 lightToPixelVec = light_pos - In.WorldPos;
        float d = length(lightToPixelVec);
        lightToPixelVec /= d;
        float intensity = saturate(dot(lightToPixelVec, normal));

        float3 ambient_light = float3(0.2f, 0.2f, 0.2f);

        Out.Position = float4(In.WorldPos.zzz, 1.0f);
        Out.Normal = float4(normal.xyz, 1.0f);
        Out.Data = float4(Out.BaseColor.rgb * (ambient_light + float3(intensity, intensity, intensity)), 1.0f);
    }
    )";
    }

    return MaterialInstance;
}

void MaterialInfo::Update()
{
    if (!MaterialInstance)
    {
        return;
    }

    for (const auto& p : Properties)
    {
        if (p.UseInVertexShader)
        {
            auto vp = StaticCast<MaterialProperties>(MaterialInstance->VertexShader.Variables[0]);
            vp->SetProperty(p.Name, p.Value);
        }
        if (p.UseInPixelShader)
        {
            auto pp = StaticCast<MaterialProperties>(MaterialInstance->PixelShader.Variables[0]);
            pp->SetProperty(p.Name, p.Value);
        }
    }
}

}
