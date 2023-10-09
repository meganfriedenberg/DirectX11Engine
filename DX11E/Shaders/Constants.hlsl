// We want to use row major matrices
#pragma pack_matrix(row_major)

cbuffer PerCameraConstants : register(b0)
{
    float4x4 c_viewProj;
    float3 c_cameraPosition;
};

cbuffer PerObjectConstants : register(b1)
{
    float4x4 c_modelToWorld;
};

cbuffer MaterialConstants : register(b2) // Lab05b
{
    float3 c_diffuseColor;
    float3 c_specularColor;
    float c_specularPower;
};
#define MAX_POINT_LIGHTS 8
struct PointLightData
{
    float3 lightColor;
    float3 position;
    float innerRadius;
    float outerRadius;
    bool isEnabled;
};
cbuffer LightingConstants : register(b3)
{
    float3 c_ambient;
    PointLightData c_pointLight[MAX_POINT_LIGHTS];
};
#define MAX_SKELETON_BONES 80 // Lab07
#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 150
cbuffer SkinConstants : register(b4)
{
    float4x4 c_skinMatrix[MAX_SKELETON_BONES];
};


SamplerState DefaultSampler : register(s0); // Lab 04 part 2
Texture2D DiffuseTexture : register(t0);
Texture2D TangentTexture : register(t1); // TextureSlot 1 for tangent
Texture2D NormalTexture : register(t2);
Texture2D PositionTexture : register(t3);

