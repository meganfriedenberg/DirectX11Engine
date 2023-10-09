#include "Constants.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float3 normal : NORMAL0; 
    float3 tangent : TANGENT0;
    float2 uv : TEXTCOORD0;
};

struct VOut
{
    float4 position : SV_POSITION;
    float2 uv : TEXTCOORD0; // from Piazza post with Matt, we need a uv
    float3 normal : NORMAL0;
    float4 worldPos : WORLDPOS;
    float3 tangent : TANGENT0;
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
    output.position = mul(float4(vIn.position, 1.0), c_modelToWorld); // modelToWorld applied to model gets world
    output.worldPos = output.position;
    // transform position from world to projection space
    output.position = mul(output.position, c_viewProj);

    output.uv = vIn.uv;

    // Transform the normals to world space
    float4 tempPos = mul(float4(vIn.normal, 0.0f), c_modelToWorld);
    // Need to normalize the result, its a direction vector
    output.normal = normalize(float3(tempPos.x, tempPos.y, tempPos.z));
    // can't call Normalize() from enginemath.h, its not a vector3, its a float3

    output.tangent = (normalize(mul(float4(vIn.tangent, 0.0f), c_modelToWorld))).xyz;


    return output;
}

PS_OUT PS(VOut pIn)
{
    PS_OUT output;

    float4 diffusedColor = DiffuseTexture.Sample(DefaultSampler, pIn.uv); // Sample DirectX docs, sampling the texture
    diffusedColor = diffusedColor * float4(c_diffuseColor, 1.0);
    pIn.normal = normalize(pIn.normal); // Renormalize the normal
    pIn.tangent = normalize(pIn.tangent);

    //bi-tangent is the cross product of the normal x tangent
    
    float3 biTangent = normalize(cross(pIn.normal, pIn.tangent));

    //Read the normal from the normal map (texture slot 1) 
    float3 normalMapNormal = TangentTexture.Sample(DefaultSampler, pIn.uv);
    normalMapNormal = ((normalMapNormal) * 2) - 1; // Un-bias

    // Creating the matrix
    float3x3 tbnMatrix = float3x3(pIn.tangent.xyz, biTangent.xyz, pIn.normal.xyz);
    float3 normalMapCasted = normalMapNormal.xyz;

    // Transform
    float3 newNormal = mul(normalMapCasted, tbnMatrix);

    // similar to modified phong, return the normal and specular_power

    ///normalMapNormal = mul(normalMapNormal, c_modelToWorld);

    // Go through each of the lights, if enabled, use light to calculate
    float3 worldCasted = float3(pIn.worldPos.x, pIn.worldPos.y, pIn.worldPos.z); // Vector3 for calculations
    
    output.color = diffusedColor;
    output.normal = float4(newNormal, c_specularPower);
    output.position = float4(worldCasted, 1.0f);

    //return output.normal;

    return output;
    
}
