#include "Constants.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float2 uv : TEXTCOORD0; // Microsoft docs says to use a float2 and TEXTCOORD
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
    // Phong for a single pass for lighting
    float4 diffusedColor = DiffuseTexture.Sample(DefaultSampler, pIn.uv); // Sample DirectX docs, sampling the texture
   

    float4 normal = NormalTexture.Sample(DefaultSampler, pIn.uv);

    float3 worldCasted = PositionTexture.Sample(DefaultSampler, pIn.uv).xyz;


    
    float3 result = c_ambient;
    for (int i = 0; i < MAX_POINT_LIGHTS; i++) // Here on out, fullscreen pass of deferred rendering(pass). 
    { // Should take as an input to the 2nd pass: worldCasted, normals, texture color,
        if (c_pointLight[i].isEnabled == true)
        {
            // Need the vector FROM surface TO light
            float3 surfaceToLight = normalize(c_pointLight[i].position - worldCasted);

            // Need the vector FROM surface TO camera
            float3 surfaceToCam = normalize(c_cameraPosition - worldCasted);

            // Calculating the reflected vector, PDF noted -lightvector
            float3 reflectedLightDirection = reflect(-surfaceToLight, normal.xyz);

            float3 diffuseLight = dot(normal.xyz, surfaceToLight);
            float3 specularLight = dot(reflectedLightDirection, surfaceToCam);
            diffuseLight = max(diffuseLight, 0.0f); // Use max to clamp dot prods
            specularLight = max(specularLight, 0.0f);

            diffuseLight = diffusedColor * diffuseLight; // combine the diffuse

            // ^^ just use the c_diffuseColor, the texture coloring, for the 2nd pass. 
            // Calculate specular power
            specularLight = pow(specularLight, normal.w); // specular power is crammed into W of normal
            specularLight = diffusedColor * specularLight; // Combine the specular

             // Calculate distance falloff
            float distFalloff = 0.0f;
            float fromLighttoPixel = 0.0f;
            fromLighttoPixel = distance(c_pointLight[i].position, worldCasted); // c_pointLight stays as a constant buffer
            // Linearly interpolate using smoothstep
            distFalloff = smoothstep(c_pointLight[i].innerRadius, c_pointLight[i].outerRadius, fromLighttoPixel);
            distFalloff = 1 - distFalloff; // correct linear interpolation, now x < min does return 1

            diffuseLight = diffuseLight * distFalloff;
            specularLight = specularLight * distFalloff;


            float3 temp = diffuseLight + specularLight;
            temp = temp * c_pointLight[i].lightColor;
            result = result + temp;
        }
    }

    return float4(result, 1.0f) * diffusedColor;
    
}
