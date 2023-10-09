#include "Constants.hlsl"

struct VIn
{
    float3 position : POSITION0;
    //float3 normal : NORMAL0;
    float2 uv : TEXTCOORD0; // Microsoft docs says to use a float2 and TEXTCOORD
};

struct VOut
{
    float4 position : SV_POSITION;
    float2 uv : TEXTCOORD0;
    //float3 normal : NORMAL0;
    //float4 worldPos : WORLDPOS;
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

    float weights[5];
    weights[0] = 0.2270270270;
    weights[1] = 0.1945945946;
    weights[2] = 0.1216216216;
    weights[3] = 0.0540540541;
    weights[4] = 0.0162162162;
    float offset[5];
    offset[0] = 0.0;
    offset[1] = 1.0;
    offset[2] = 2.0;
    offset[3] = 3.0;
    offset[4] = 4.0;

    float4 diffusedColor = DiffuseTexture.Sample(DefaultSampler, pIn.uv) * weights[0];
    
    for (int i = 1; i < 5; i++)
    {
        diffusedColor += DiffuseTexture.Sample(DefaultSampler, (pIn.uv + float2(0.0, (offset[i] / SCREEN_HEIGHT)))) * weights[i];

        diffusedColor += DiffuseTexture.Sample(DefaultSampler, (pIn.uv - float2(0.0, (offset[i] / SCREEN_HEIGHT)))) * weights[i];
    }

    return diffusedColor; 

}
