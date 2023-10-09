#include "Constants.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float4 color : COLOR0;
    float2 uv : TEXTCOORD0; 
    float3 normal : NORMAL0; 
};

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
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

    output.position = mul(float4(vIn.position, 1.0), c_modelToWorld);
    output.worldPos = output.position;
    // transform position from world to projection space
    output.position = mul(output.position, c_viewProj);

    output.color = vIn.color;

    output.uv = vIn.uv;

    float4 tempPos = mul(float4(vIn.normal, 0.0f), c_modelToWorld);
    // Need to normalize the result, its a direction vector
    output.normal = normalize(float3(tempPos.x, tempPos.y, tempPos.z));
    // can't call Normalize() from enginemath.h, its not a vector3, its a float3

    return output;
}

float4 PS(VOut pIn) : SV_TARGET
{
    float4 diffusedColor = DiffuseTexture.Sample(DefaultSampler, pIn.uv); // Sample DirectX docs, sampling the texture
    pIn.normal = normalize(pIn.normal); // Renormalize the normal
    // Go through each of the lights, if enabled, use light to calculate
    float3 worldCasted = float3(pIn.worldPos.x, pIn.worldPos.y, pIn.worldPos.z);
    float3 result = c_ambient;
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        if (c_pointLight[i].isEnabled == true)
        {
            // Need the vector FROM surface TO light
            float3 surfaceToLight = normalize(c_pointLight[i].position - worldCasted);

            // Need the vector FROM surface TO camera
            float3 surfaceToCam = normalize(c_cameraPosition - worldCasted);

            // Calculating the reflected vector, PDF noted -lightvector
            float3 reflectedLightDirection = reflect(-surfaceToLight, pIn.normal);

            float3 diffuseLight = dot(pIn.normal, surfaceToLight);
            float3 specularLight = dot(reflectedLightDirection, surfaceToCam);
            diffuseLight = max(diffuseLight, 0.0f); // Use max to clamp dot prods
            specularLight = max(specularLight, 0.0f);

            diffuseLight = c_diffuseColor * diffuseLight; // combine the diffuse
            
            // Calculate specular power
            specularLight = pow(specularLight, c_specularPower);
            specularLight = c_specularColor * specularLight; // Combine the specular

             // Calculate distance falloff
            float distFalloff = 0.0f;
            float fromLighttoPixel = 0.0f;
            // Need to use world position, specified on Piazza by Matt
            fromLighttoPixel = distance(c_pointLight[i].position, worldCasted);
            // Linearly interpolate using smoothstep
            distFalloff = smoothstep(c_pointLight[i].innerRadius, c_pointLight[i].outerRadius, fromLighttoPixel);
            // "Returns 0 if x is less than min; 1 if x is greater than max; otherwise, a value between 0 and 1 if x is in the range [min, max]."
            // But we want: if the distance is >= outerRadius, you want 0.0
            distFalloff = 1 - distFalloff; // correct linear interpolation, now x < min does return 1

            diffuseLight = diffuseLight * distFalloff;
            specularLight = specularLight * distFalloff;


            float3 temp = diffuseLight + specularLight;
            temp = temp * c_pointLight[i].lightColor;
            result = result + temp;
        }
    }

    // Multiply by texture sample, vertex color, and our calculated light 
    return pIn.color * diffusedColor * float4(result, 1.0f); 
    
}
