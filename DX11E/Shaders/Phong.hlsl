#include "Constants.hlsl"

struct VIn // removed Normal for deferred rendering
{
    float3 position : POSITION0;
    float2 uv : TEXTCOORD0;
    float3 normal : NORMAL0;
};

struct VOut // not messing with vertex shader, messing with fragment shader
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
// first pass -> render to off screen buffer -> the vertex shader for this is Copy.hlsl, also look up position/normal/color (3 texture reads)
// lighting pass is a FULL SCREEN pass, email me @mfrieden@usc.edu to see code for one pass per light

VOut VS(VIn vIn)
{
    VOut output;

  // Transform input pos from model to world
    output.position = mul(float4(vIn.position, 1.0), c_modelToWorld); // modelToWorld applied to model gets world
    output.worldPos = output.position;
    // transform position from world to projection space
    output.position = mul(output.position, c_viewProj);

    output.uv = vIn.uv;

    // Transform the normals to world space
    float4 tempPos = mul(float4(vIn.normal, 0.0f), c_modelToWorld);
    // Need to normalize the result, its a direction vector
    output.normal = normalize(float3(tempPos.x, tempPos.y, tempPos.z));


    return output;
}

PS_OUT PS(VOut pIn)  // writes to the 3 render target textures for deferred rendering
{
    // sample the Diffuse Texture

    //from textures / buffers need to grab: worldPosition, normal, c_diffuseColor, c_specularPower

    float4 diffusedColor = DiffuseTexture.Sample(DefaultSampler, pIn.uv);

    float4 preCombinedDiffuse = diffusedColor * float4(c_diffuseColor, 1.0); // pre-multiplying the material and the texture

    //return diffusedColor; // uncomment this to individually test render passes

    pIn.normal = normalize(pIn.normal); // Renormalize the normal

    float4 normal = float4(pIn.normal, c_specularPower);

    float3 worldCasted = float3(pIn.worldPos.x, pIn.worldPos.y, pIn.worldPos.z); // World position, write out to a buffer
 

    // Creating PS_OUT
    PS_OUT output;
    output.color = preCombinedDiffuse;
    output.normal = normal; // also is storing c_specularPower
    output.position = float4(worldCasted, 1.0f);

    return output;

    
}
