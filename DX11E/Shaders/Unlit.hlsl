#include "Constants.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float2 uv : TEXTCOORD0; // Microsoft docs says to use a float2 and TEXTCOORD
    float3 normal : NORMAL0;
};

struct VOut
{
    float4 position : SV_POSITION;
    float2 uv : TEXTCOORD0; // from Piazza post with Matt, we need a uv
    float3 normal : NORMAL0;
    float4 worldPos : WORLDPOS;
};

struct PS_OUT // the 3 texture outputs for deferred rendering
{
    float4 color : SV_TARGET0;
    float4 normal : SV_TARGET1;
    float4 position : SV_TARGET2;
};

VOut VS(VIn vIn)
{
    VOut output;
    output.position = mul(float4(vIn.position, 1.0), c_modelToWorld);
    output.worldPos = output.position;
    // transform position from world to projection space
    output.position = mul(output.position, c_viewProj);

    output.uv = vIn.uv;
    float4 tempPos = mul(float4(vIn.normal, 0.0f), c_modelToWorld);
    // Need to normalize the result, its a direction vector
    output.normal = normalize(float3(tempPos.x, tempPos.y, tempPos.z));
    // can't call Normalize() from enginemath.h, its not a vector3, its a float3

    return output;
}

PS_OUT PS(VOut pIn)
{
    PS_OUT output;
    // sample the Diffuse Texture
    // not sure if float4 or float2 -> actually Sample docs said it defaults to 
    // the struct's color's size which is a float4
    float4 diffusedColor = DiffuseTexture.Sample(DefaultSampler, pIn.uv); // Sample DirectX docs, sampling the texture

    float3 normal = normalize(pIn.normal); // Renormalize the normal
    // Go through each of the lights, if enabled, use light to calculate
    float3 worldCasted = float3(pIn.worldPos.x, pIn.worldPos.y, pIn.worldPos.z); // Vector3 for calculations

    output.color = diffusedColor;
    output.normal = float4(-normal, 1.0f);
    output.position = float4(worldCasted, 1.0f);

    return output;

}
