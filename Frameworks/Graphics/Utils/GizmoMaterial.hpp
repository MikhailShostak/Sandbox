#pragma once

SHADER_BUFFER_BEGIN(GizmoCameraConstants)
SHADER_VARIABLE(hlslpp::float4x4, g_ViewProj)
SHADER_BUFFER_END()

SHADER_STRUCT_BEGIN(GizmoVSInput)
SHADER_LAYOUT_REG(hlslpp::float4, Pos, ATTRIB0)
SHADER_LAYOUT_REG(hlslpp::float4, Normal, ATTRIB1)
SHADER_LAYOUT_REG(hlslpp::float4, UV, ATTRIB2)
SHADER_LAYOUT_REG(hlslpp::float4, Data, ATTRIB3)

SHADER_LAYOUT_REG(hlslpp::float4, MtrxRow0, ATTRIB4)
SHADER_LAYOUT_REG(hlslpp::float4, MtrxRow1, ATTRIB5)
SHADER_LAYOUT_REG(hlslpp::float4, MtrxRow2, ATTRIB6)
SHADER_LAYOUT_REG(hlslpp::float4, MtrxRow3, ATTRIB7)
SHADER_STRUCT_END()

SHADER_STRUCT_BEGIN(GizmoPSInput)
SHADER_LAYOUT_REG(hlslpp::float4, Pos, SV_POSITION)
SHADER_LAYOUT(hlslpp::float4, Color)
SHADER_STRUCT_END()

SHADER_STRUCT_BEGIN(GizmoPSOutput)
SHADER_LAYOUT_REG(hlslpp::float4, Color, SV_TARGET)
SHADER_STRUCT_END()

inline SharedReference<GizmoCameraConstants> g_GizmoCameraConstants = CreateShared<GizmoCameraConstants>();

namespace Graphics
{

struct GizmoMaterial : public Graphics::Material
{
    GizmoMaterial()
    {
        VertexShader.Constants.push_back(g_GizmoCameraConstants);
        VertexShader.InputLayout = CreateShared<GizmoVSInput>();
        VertexShader.OutputLayout = CreateShared<GizmoPSInput>();
        PixelShader.InputLayout = VertexShader.OutputLayout;
        PixelShader.OutputLayout = CreateShared<GizmoPSOutput>();

        VertexShader.SourceCode = R"(
    void main(in GizmoVSInput In, out GizmoPSInput Out)
    {
        float4x4 InstanceTransform = transpose(MatrixFromRows(In.MtrxRow0, In.MtrxRow1, In.MtrxRow2, In.MtrxRow3));        
        float4x4 mvp = mul(g_ViewProj, InstanceTransform);
        Out.Pos = mul(mvp, float4(In.Pos.xyz, 1.0));
        Out.Color = In.Data;
    }
    )";

        PixelShader.SourceCode = R"(
    void main(in GizmoPSInput In, out GizmoPSOutput Out)
    {
        Out.Color = In.Color;
    }
    )";
    }
};

}
