#include "Constants.hlsl"

struct VIn
{
    float3 position : POSITION0;
};

struct VOut
{
    float4 position : SV_POSITION;
};

struct GSOut
{
    float4 position : SV_POSITION;
    float2 uv : TEXTCOORD0;
    float3 normal : NORMAL0;
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

    // Get the position from c_modeltoWorld

    float3 treePosition = vIn.position;

    output.position = float4(treePosition, 1.0);

    return output;
}

[maxvertexcount(6)]
void GS(point VOut pIn[1], inout TriangleStream<GSOut> output)
{
    GSOut v[6];
    float4 transformedPoint;

    float3 treePosition = pIn[0].position.xyz;

    float3 fromCameraToTree = normalize(treePosition - c_cameraPosition);
    fromCameraToTree.z = 0;


    float4x4 lookAtMatrix;
    float3 eye = treePosition;
    float3 at = (treePosition + fromCameraToTree);
    float3 up = float3(0, 0, 1);

    float3 forward = normalize(at - eye) * 200;
    float3 left = normalize(cross(up, forward)) * 200;
    float3 newUp = normalize(cross(forward, left)) * 200;

    lookAtMatrix = float4x4(float4(left, 0), float4(newUp, 0), float4(forward, 0), float4(eye, 1));


#if 0
    transformedPoint = mul(float4(treePosition, 1.0), lookAtMatrix); // modelToWorld applied to model gets world
    // transform position from world to projection space
    transformedPoint = mul(transformedPoint, c_viewProj);
#else
    transformedPoint = mul(float4(treePosition, 1.0), c_viewProj);
#endif

#if 1
    // note: newUp is upside-down... it's the newDown
    v[0].position = float4(treePosition + left + newUp, 1.0);
    v[0].position = mul(v[0].position, c_viewProj);
    v[0].uv = float2(0.0, 0.0); // bottom left
    v[0].normal = -forward / 200;

    v[1].position = float4(treePosition - left + newUp, 1.0);
    v[1].position = mul(v[1].position, c_viewProj);
    v[1].uv = float2(1.0, 0.0); // bottom right
    v[1].normal = -forward / 200;

    v[2].position = float4(treePosition - left - newUp, 1.0);
    v[2].position = mul(v[2].position, c_viewProj);
    v[2].uv = float2(1.0, 1.0); // top right
    v[2].normal = -forward / 200;

    // -- ^ first triangle -- \/ bottom triangle

    v[5].position = float4(treePosition - left - newUp, 1.0);
    v[5].position = mul(v[5].position, c_viewProj);
    v[5].uv = float2(1.0, 1.0); // top right
    v[5].normal = -forward / 200;

    v[4].position = float4(treePosition + left - newUp, 1.0);
    v[4].position = mul(v[4].position, c_viewProj);
    v[4].uv = float2(.0, 1.0); // top left
    v[4].normal = -forward / 200;

    v[3].position = float4(treePosition + left + newUp, 1.0);
    v[3].position = mul(v[3].position, c_viewProj);
    v[3].uv = float2(0.0, 0.0); // bottom left
    v[3].normal = -forward / 200;



#elif 1
    // Now we have just need to move and scale the point?
    v[2].position = transformedPoint / transformedPoint.w;
    v[2].position.y += 0.5;
    v[2].position.x -= 0.5;
    v[2].uv = float2(0.0, 1.0); // top left

    v[1].position = transformedPoint / transformedPoint.w;
    v[1].position.x += 1.0;
    v[1].uv = float2(1.0, 1.0); // top right

    v[0].position = transformedPoint / transformedPoint.w;
    v[0].position.y -= 1.0;
    v[0].uv = float2(1.0, 0.0); // bottom right
#else   // just prove that it works at all
    v[0].position = float4(-0.5, -0.5, 0.0f, 1.0f);
    v[0].uv = float2(0.0, 1.0); // top left
    v[1].position = float4(0.5, -0.5, 0.0f, 1.0f);
    v[1].uv = float2(1.0, 1.0); // top right
    v[2].position = float4(0.0, 0.5, 0.0f, 1.0f);
    v[2].uv = float2(1.0, 0.0); // bottom right
#endif


    output.Append(v[0]);
    output.Append(v[1]);
    output.Append(v[2]);
    output.Append(v[3]);
    output.Append(v[4]);
    output.Append(v[5]);
}


PS_OUT PS(GSOut pIn)
{
    PS_OUT output;

    float4 diffusedColor = DiffuseTexture.Sample(DefaultSampler, pIn.uv); // Sample DirectX docs, sampling the texture

    // first make it flat
    // 



    output.color = diffusedColor;
    output.normal = float4(pIn.normal, 1.0f);
    output.position = pIn.position;

    return output;
    
}
