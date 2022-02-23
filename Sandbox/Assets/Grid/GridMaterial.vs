void main(in VSInput In, out PSInput Out)
{
    float4x4 t = transpose(MatrixFromRows(In.MtrxRow0, In.MtrxRow1, In.MtrxRow2, In.MtrxRow3));
    
    float2 uv = In.UV * ImageScale.xy + ImageOffset.xy;
    float4x4 mvp = mul(g_ViewProj, t);

    Out.Pos = mul(mvp, float4(In.Pos.xyz, 1.0));
    Out.WorldPos = mul(t, float4(In.Pos.xyz, 1.0));
    Out.Normal = In.Normal;
    Out.UV = uv;
}
