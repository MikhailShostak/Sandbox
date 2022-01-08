#pragma once

inline SharedReference<Graphics::Texture> g_WhitePlaceholder;
inline SharedReference<Graphics::Texture> g_BlackPlaceholder;
inline SharedReference<Graphics::Texture> g_NormalPlaceholder;

SHADER_BUFFER_BEGIN(CameraConstants)
SHADER_VARIABLE(hlslpp::float4x4, g_ViewProj)
SHADER_BUFFER_END()

SHADER_BUFFER_BEGIN(ImageDataConstants)
SHADER_VARIABLE(hlslpp::float4, Color)
SHADER_VARIABLE(hlslpp::float4, ImageOffset)
SHADER_VARIABLE(hlslpp::float4, ImageScale)
SHADER_BUFFER_END()

SHADER_STRUCT_BEGIN(VSInput)
SHADER_LAYOUT_REG(hlslpp::float4, Pos, ATTRIB0)
SHADER_LAYOUT_REG(hlslpp::float4, Normal, ATTRIB1)
SHADER_LAYOUT_REG(hlslpp::float4, UV, ATTRIB2)
SHADER_LAYOUT_REG(hlslpp::float4, Data, ATTRIB3)

SHADER_LAYOUT_REG(hlslpp::float4, MtrxRow0, ATTRIB4)
SHADER_LAYOUT_REG(hlslpp::float4, MtrxRow1, ATTRIB5)
SHADER_LAYOUT_REG(hlslpp::float4, MtrxRow2, ATTRIB6)
SHADER_LAYOUT_REG(hlslpp::float4, MtrxRow3, ATTRIB7)
SHADER_STRUCT_END()

SHADER_STRUCT_BEGIN(PSInput)
SHADER_LAYOUT_REG(hlslpp::float4, Pos, SV_POSITION)
SHADER_LAYOUT_REG(hlslpp::float2, UV, TEX_COORD)
SHADER_LAYOUT(hlslpp::float4, VertexColor)
SHADER_LAYOUT(hlslpp::float3, WorldPos)
SHADER_LAYOUT(hlslpp::float3, Normal)
SHADER_STRUCT_END()

SHADER_STRUCT_BEGIN(PSOutput)
SHADER_LAYOUT_REG(hlslpp::float4, BaseColor, SV_TARGET0)
SHADER_LAYOUT_REG(hlslpp::float4, Position, SV_TARGET1)
SHADER_LAYOUT_REG(hlslpp::float4, Normal, SV_TARGET2)
SHADER_LAYOUT_REG(hlslpp::float4, Data, SV_TARGET3)
SHADER_STRUCT_END()

inline SharedReference<CameraConstants> g_CameraConstants = CreateShared<CameraConstants>();

namespace Graphics
{

struct PBRMaterial : public Graphics::Material
{
    Graphics::TextureSampler BaseColor;
    Graphics::TextureSampler Normal;
    Graphics::TextureSampler Metallic;
    Graphics::TextureSampler Roughness;
    Graphics::TextureSampler AmbientOcclusion;
    Graphics::TextureSampler Displacement;
    Graphics::TextureSampler Emissive;

    SharedReference<ImageDataConstants> ImageSettings = CreateShared<ImageDataConstants>();

    PBRMaterial()
    {
        ImageSettings->Color = hlslpp::float4{ 1, 1, 1, 1 };
        ImageSettings->ImageOffset = hlslpp::float4{ 0, 0, 0, 0 };
        ImageSettings->ImageScale = hlslpp::float4{ 1, 1, 0, 0 };

        VertexShader.Constants.push_back(g_CameraConstants);
        VertexShader.InputLayout = CreateShared<VSInput>();
        VertexShader.OutputLayout = CreateShared<PSInput>();
        PixelShader.Variables.push_back(ImageSettings);
        PixelShader.InputLayout = VertexShader.OutputLayout;
        PixelShader.OutputLayout = CreateShared<PSOutput>();

        TextureSamplers.reserve(7);

        BaseColor.Name = "g_BaseColor";
        BaseColor.Texture = g_WhitePlaceholder;
        TextureSamplers.push_back(BaseColor);

        Normal.Name = "g_Normal";
        Normal.Texture = g_NormalPlaceholder;
        TextureSamplers.push_back(Normal);

        /*Metallic.Name = "g_Metallic";
        Emissive.Texture = g_WhitePlaceholder;
        TextureSamplers.push_back(&Metallic);

        Roughness.Name = "g_Roughness";
        Emissive.Texture = g_WhitePlaceholder;
        TextureSamplers.push_back(&Roughness);

        AmbientOcclusion.Name = "g_AmbientOcclusion";
        Emissive.Texture = g_WhitePlaceholder;
        TextureSamplers.push_back(&AmbientOcclusion);

        Emissive.Name = "g_Emissive";
        Emissive.Texture = g_BlackPlaceholder;
        TextureSamplers.push_back(&Emissive);

        Displacement.Name = "g_Displacement";
        Displacement.Texture = g_BlackPlaceholder;
        TextureSamplers.push_back(&Displacement);*/

        VertexShader.SourceCode = R"(
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

        PixelShader.SourceCode = R"(
    void main(in PSInput In, out PSOutput Out)
    {
        float2 uv = (In.UV * ImageScale.xy) + ImageOffset.xy;

        Out.BaseColor = Color * g_BaseColor.Sample(g_BaseColor_sampler, uv);
        if (Out.BaseColor.a < 0.1f)
        {
	        clip(-1);
            return;
        }

        float3 normal = normalize(In.Normal + g_Normal.Sample(g_Normal_sampler, uv));

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
};

}
