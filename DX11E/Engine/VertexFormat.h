#pragma once
#include "engineMath.h"
#include "Graphics.h"

struct VertexPosColor
{
    Vector3 pos;
    Vector3 normal;
    Graphics::Color4 color;
    Vector2 uv; // is this a vector2 or a 2Dtexture? 
};
struct VertexPos
{
    Vector3 pos;
    Vector3 normal;
    Vector2 uv;
};
struct VertexPosTangent
{
    Vector3 pos;
    Vector3 normal;
    Vector3 tangent;
    Vector2 uv;
};
struct VertexSkinned
{
    Vector3 pos;
    Vector3 normal;
    uint8_t bones[4];
    uint8_t weights[4];
    Vector2 uv;
};
struct VertexCopy
{
    Vector3 pos;
    Vector2 uv;
};
struct VertexTree
{
    Vector3 pos;
};



