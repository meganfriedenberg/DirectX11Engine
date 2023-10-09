#include "Constants.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float4 color : COLOR0;
};

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
};

VOut VS(VIn vIn)
{
    VOut output;

    //  output.position = vIn.position;
    // Transform input pos from model to world
    output.position = mul(float4(vIn.position, 1.0), c_modelToWorld);
    // transform position from world to projection space
    output.position = mul(output.position, c_viewProj);

    output.color = vIn.color;

    return output;
}

float4 PS(VOut pIn) : SV_TARGET
{
    return pIn.color;
}
