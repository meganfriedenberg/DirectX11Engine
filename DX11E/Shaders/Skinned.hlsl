#include "Constants.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    uint4 bones : BONES0;
    float4 weights : WEIGHTS0;
    float2 uv : TEXTCOORD0; // Microsoft docs says to use a float2 and TEXTCOORD
};

struct VOut
{
    float4 position : SV_POSITION;
    float2 uv : TEXTCOORD0;
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

    // Transform the bone vertices from T-Pose to current pose
    float4 skinnedVertex1 = vIn.weights[0] * mul(float4(vIn.position, 1.0), c_skinMatrix[vIn.bones[0]]);
    float4 skinnedVertex2 = vIn.weights[1] * mul(float4(vIn.position, 1.0), c_skinMatrix[vIn.bones[1]]);
    float4 skinnedVertex3 = vIn.weights[2] * mul(float4(vIn.position, 1.0), c_skinMatrix[vIn.bones[2]]);
    float4 skinnedVertex4 = vIn.weights[3] * mul(float4(vIn.position, 1.0), c_skinMatrix[vIn.bones[3]]);
    output.position = skinnedVertex1 + skinnedVertex2 + skinnedVertex3 + skinnedVertex4;


    // Skin the normal
    float4 skinnedNormal1 = vIn.weights[0] * mul(float4(vIn.normal, 0.0), c_skinMatrix[vIn.bones[0]]);
    float4 skinnedNormal2 = vIn.weights[1] * mul(float4(vIn.normal, 0.0), c_skinMatrix[vIn.bones[1]]);
    float4 skinnedNormal3 = vIn.weights[2] * mul(float4(vIn.normal, 0.0), c_skinMatrix[vIn.bones[2]]);
    float4 skinnedNormal4 = vIn.weights[3] * mul(float4(vIn.normal, 0.0), c_skinMatrix[vIn.bones[3]]);
    output.normal = skinnedNormal1 + skinnedNormal2 + skinnedNormal3 + skinnedNormal4;

  //  output.position = vIn.position;
  // Transform input pos from model to world
    output.position = mul(output.position, c_modelToWorld); // modelToWorld applied to model gets world
    output.worldPos = output.position;
    // transform position from world to projection space
    output.position = mul(output.position, c_viewProj);

    output.uv = vIn.uv;

    // Transform the normals to world space 
    float4 tempPos = mul(float4(output.normal, 0.0f), c_modelToWorld);
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
    output.normal = float4(normal, 1.0f);
    output.position = float4(worldCasted, 1.0f);

    return output;

    
}
