void main(in VSInput In, out PSInput Out)
{
    float4x4 InstanceTransform = transpose(MatrixFromRows(In.MtrxRow0, In.MtrxRow1, In.MtrxRow2, In.MtrxRow3));
    Out.Pos = mul(InstanceTransform, float4(In.Pos.xyz, 1.0));
    Out.UV  = In.UV.xy;
}
