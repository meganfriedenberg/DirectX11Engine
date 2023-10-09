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

    output.position = float4(vIn.position,1.0);

    output.uv = vIn.uv;

    return output;
}

float4 PS(VOut pIn) : SV_TARGET
{
    // sample the Diffuse Texture
    float4 diffusedColor = DiffuseTexture.Sample(DefaultSampler, pIn.uv); // Sample DirectX docs, sampling the texture
    

    // Multiply by texture sample, vertex color, and our calculated light
    return diffusedColor; 
    
}
