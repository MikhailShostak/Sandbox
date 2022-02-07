void main(in VSInput In, out PSInput Out)
{
    // HLSL matrices are row-major while GLSL matrices are column-major. We will
    // use convenience function MatrixFromRows() appropriately defined by the engine
    float4x4 InstanceTransform = transpose(MatrixFromRows(In.MtrxRow0, In.MtrxRow1, In.MtrxRow2, In.MtrxRow3));
    
    // Apply instance transformation
    //float4 TransformedPos = mul(float4(In.Pos.xyz, 1.0), InstanceTransform);

    float4x4 mvp = mul(g_ViewProj, InstanceTransform);    
    
    float4 WorldNormal = mul(InstanceTransform, float4(g_Normals.Sample(g_Normals_sampler, In.UV.xy).xyz, 0.0));

    Out.Pos = mul(mvp, float4(In.Pos.xyz + WorldNormal.xyz * g_Displacement.Sample(g_Displacement_sampler, In.UV.xy).xxx, 1.0));
    Out.WorldPos = mul(InstanceTransform, float4(In.Pos.xyz, 1.0));
    Out.Normal = In.Normal.xyz;
    //Out.Pos = Out.Pos / Out.Pos.w;
    Out.UV  = In.UV.xy;
}
