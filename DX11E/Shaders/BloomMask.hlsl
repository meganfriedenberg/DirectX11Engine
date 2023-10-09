#include "Constants.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float2 uv : TEXTCOORD0;
};

struct VOut
{
    float4 position : SV_POSITION;
    float2 uv : TEXTCOORD0;

};

VOut VS(VIn vIn)
{
    VOut output;

    output.position = float4(vIn.position, 1.0);
    output.uv = vIn.uv;

    return output;
}

float4 PS(VOut pIn) : SV_TARGET
{
    float4 diffusedColor = DiffuseTexture.Sample(DefaultSampler, pIn.uv); // Sample DirectX docs, sampling the texture
    if (max(diffusedColor.x, max(diffusedColor.y, diffusedColor.z)) < 0.8)
    {
        return float4(0.0, 0.0, 0.0, 1.0);
    }

    return diffusedColor; 

}
