void main(in VSInput In, out PSInput Out)
{
    float4x4 t = transpose(MatrixFromRows(In.MtrxRow0, In.MtrxRow1, In.MtrxRow2, In.MtrxRow3));
    
    float2 uv = In.UV * ImageScale.xy + ImageOffset.xy + fmod(g_Time * Speed.xy, 1);
    float4x4 mvp = mul(g_ViewProj, t);    
    
    float3 displacementScale = In.Normal.xyz * g_Displacement.Sample(g_Displacement_sampler, uv).r * Displacement.x;
    float3 displacementOffset = In.Normal.xyz * Displacement.y;

    float mask = g_SymbolMask.Sample(g_SymbolMask_sampler, uv / 3.0).x;
    
    float3 d = lerp(displacementScale + displacementOffset, 0.0, mask.xxx);

    Out.Pos = mul(mvp, float4(In.Pos.xyz + d, 1.0));
    Out.WorldPos = mul(t, float4(In.Pos.xyz, 1.0));
    Out.Normal = In.Normal;
    Out.UV = uv;
}
