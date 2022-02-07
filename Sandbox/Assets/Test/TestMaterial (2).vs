void main(in VSInput In, out PSInput Out)
{
    // HLSL matrices are row-major while GLSL matrices are column-major. We will
    // use convenience function MatrixFromRows() appropriately defined by the engine
    float4x4 InstanceTransform = transpose(MatrixFromRows(In.MtrxRow0, In.MtrxRow1, In.MtrxRow2, In.MtrxRow3));
    
    // Apply instance transformation
    //float4 TransformedPos = mul(float4(In.Pos.xyz, 1.0), InstanceTransform);
    
    float2 uv = (In.UV * ImageScale.xy) + ImageOffset.xy + fmod(g_Time * Speed.xy, 1);
    float4x4 mvp = mul(g_ViewProj, InstanceTransform);    
    
    float3 normal = In.Normal.xyz;
    float3 tangent = In.Data.xyz;
    float3 binormal = cross(normal, tangent);
    float3x3 TBN = float3x3(normalize(tangent), normalize(binormal), normalize(normal));
    TBN = transpose(TBN);

    float3 WorldNormal = mul(TBN, normal);

    Out.Pos = mul(mvp, float4(In.Pos.xyz + normal * g_Displacement.Sample(g_Displacement_sampler, uv.xy).xxx * DisplacementOffset.x + normal * DisplacementOffset.y, 1.0));
    Out.WorldPos = mul(InstanceTransform, float4(In.Pos.xyz, 1.0));
    Out.Normal = normal;
    //Out.Pos = Out.Pos / Out.Pos.w;
    Out.UV  = uv;
}
