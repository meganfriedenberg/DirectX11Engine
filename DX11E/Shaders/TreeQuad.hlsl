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
{ // should be 1 point, geometry shader expands it to 4
    // get it to compile, then get it to move vertices 100 units or something dumb, then get a single point into a whole tree
    VOut output;

    // Get the position from c_modeltoWorld

    float3 treePosition = mul(float4(0, 0, 0, 1), c_modelToWorld).xyz;

    float3 fromCameraToTree = treePosition - c_cameraPosition;
    fromCameraToTree.z = 0;

    float3 treeNormalized = normalize(fromCameraToTree);
    float4x4 lookAtMatrix;

    float3 eye = treePosition;
    float3 at = (treePosition + treeNormalized);
    float3 up = float3(0, 0, 1);

    float3 forward = normalize(at - eye) * 200;
    float3 left = normalize(cross(up, forward)) * 200;
    float3 newUp = normalize(cross(forward, left)) * 200;

    lookAtMatrix = float4x4(float4(left, 0), float4(newUp, 0), float4(forward, 0), float4(eye, 1));
    output.position = mul(float4(vIn.position, 1.0), lookAtMatrix); // modelToWorld applied to model gets world
    // transform position from world to projection space
    output.position = mul(output.position, c_viewProj);

    output.uv = vIn.uv;

    return output;
}


float4 PS(VOut pIn) : SV_TARGET
{
    float4 diffusedColor = DiffuseTexture.Sample(DefaultSampler, pIn.uv); // Sample DirectX docs, sampling the texture

    return diffusedColor;
    
}
