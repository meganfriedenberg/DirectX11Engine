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
    float weights[3];
    weights[0] = 0.2270270270;
    weights[1] = 0.3162162162;
    weights[2] = 0.0702702703;

    float offset[3];
    offset[0] = 0.0;
    offset[1] = 1.3846153846;
    offset[2] = 3.2307692308;


    float4 diffusedColor = DiffuseTexture.Sample(DefaultSampler, pIn.uv) * weights[0]; // Multiply by Gaussian weight after sampling

    for (int i = 1; i < 3; i++)
    {
        diffusedColor += DiffuseTexture.Sample(DefaultSampler, (pIn.uv + float2((offset[i] / SCREEN_WIDTH), 0.0))) * weights[i];

        diffusedColor += DiffuseTexture.Sample(DefaultSampler, (pIn.uv - float2((offset[i] / SCREEN_WIDTH), 0.0))) * weights[i];
    }

    return diffusedColor;

}
