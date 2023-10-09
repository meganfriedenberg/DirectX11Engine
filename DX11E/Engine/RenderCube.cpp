#include "stdafx.h"
#include "RenderCube.h"
#include <VertexFormat.h>

RenderCube::RenderCube(Material* material) : RenderObj(nullptr)
{
	static VertexPosColor cubeVertex[] =
	{
	{ Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(1,0)},// START FACE1,0
	{ Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f),Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(1,1)}, // 1
	{ Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f),Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(0,1), }, // 2
	{ Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f),Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(0,0), }, // END FACE1,3
	{ Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Graphics::Color4(0.0f, 1.0f, 1.0f, 1.0f), Vector2(1,0) }, // START FACE2,0  4
	{ Vector3(0.5f, 0.5f, -0.5f), Vector3(1.0f, 0.0f, 0.0f),Graphics::Color4(0.0f, 1.0f, 1.0f, 1.0f), Vector2(1,1) }, // 1  5
	{ Vector3(0.5f, -0.5f, -0.5f), Vector3(1.0f, 0.0f, 0.0f),Graphics::Color4(0.0f, 1.0f, 1.0f, 1.0f), Vector2(0,1) }, // 2  6
	{ Vector3(0.5f, -0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f),Graphics::Color4(0.0f, 1.0f, 1.0f, 1.0f), Vector2(0,0) },// END FACE2,3  7
	{ Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f), Vector2(1,0) }, // START FACE3,0  8
	{ Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 1.0f, 0.0f), Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f), Vector2(1,1) }, // 1  9
	{ Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 1.0f, 0.0f), Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f), Vector2(0,1) }, // 2  10
	{ Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f), Vector2(0,0) },// END FACE3,3  11
	{ Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, -1.0f, 0.0f), Graphics::Color4(1.0f, 1.0f, 1.0f, 0.0f), Vector2(1,0) }, // START FACE4,0  12
	{ Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, -1.0f, 0.0f), Graphics::Color4(1.0f, 1.0f, 1.0f, 0.0f), Vector2(1,1) }, // 1  13
	{ Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, -1.0f, 0.0f), Graphics::Color4(1.0f, 1.0f, 1.0f, 0.0f), Vector2(0,1) }, // 2  14
	{ Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, -1.0f, 0.0f), Graphics::Color4(1.0f, 1.0f, 1.0f, 0.0f), Vector2(0,0) },// END FACE4,3  15
	{ Vector3(-0.5f, -0.5f, 0.5f), Vector3(-1.0f, 0.0f, 0.0f) , Graphics::Color4(0.0f, 0.0f, 35.0f, 0.0f), Vector2(1,0)}, // START FACE5,0  16
	{ Vector3(-0.5f, -0.5f, -0.5f),  Vector3(-1.0f, 0.0f, 0.0f) ,Graphics::Color4(0.0f, 0.0f, 1.0f, 0.0f), Vector2(1,1) }, // 1  17
	{ Vector3(-0.5f, 0.5f, -0.5f),  Vector3(-1.0f, 0.0f, 0.0f) ,Graphics::Color4(0.0f, 0.0f, 1.0f, 0.0f), Vector2(0,1) }, // 2  18
	{ Vector3(-0.5f, 0.5f, 0.5f),  Vector3(-1.0f, 0.0f, 0.0f), Graphics::Color4(0.0f, 0.0f, 1.0f, 0.0f), Vector2(0,0) },// END FACE5,3  19
	{ Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Graphics::Color4(1.0f, 0.0f, 1.0f, 1.0f), Vector2(1,0) },// START FACE6,0  20
	{ Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f),Graphics::Color4(1.0f, 0.0f, 1.0f, 1.0f), Vector2(1,1) }, // 1  21
	{ Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f),Graphics::Color4(1.0f, 0.0f, 1.0f, 1.0f), Vector2(0,1) }, // 2   22
	{ Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f),Graphics::Color4(1.0f, 0.0f, 1.0f, 1.0f), Vector2(0,0) }, // END FACE6,3  23
	};
	static uint16_t cubeIndex[] =
	{
	2, 1, 0, // FACE1 TRI 1 red (fight on, no u fight on!)
	3, 2, 0, // FACE1 TRI 2 red
	4, 5, 6, // FACE2 TRI 1 light blue (bruin blue GROSS)
	4, 6, 7, // FACE2 TRI 2 light blue
	8, 9, 10, // FACE3 TRI 1 green
	8, 10, 11, // FACE3 TRI 2 green
	12, 13, 14, // FACE4 TRI 1 white
	12, 14, 15, // FACE4 TRI 2 white
	16, 17, 18, // FACE5 TRI 1 sanik blue
	16, 18, 19, // FACE5 TRI 2 sanik blue
	20, 21, 22, // FACE6 TRI 1 pink
	20, 22, 23, // FACE6 TRI 2 pink 

	};

	VertexBuffer* mBuffer = new VertexBuffer(cubeVertex, ARRAY_SIZE(cubeVertex), sizeof(VertexPosColor),
		cubeIndex, ARRAY_SIZE(cubeIndex), sizeof(uint16_t));

	Mesh* m = new Mesh(mBuffer, material);
	mMesh = m;

	Graphics* mGraphics = Graphics::Get();
	structPerObj.floatMatrix = Matrix4::CreateRotationZ(Math::ToRadians(45.0f));
	objectBuffer = mGraphics->CreateGraphicsBuffer(&structPerObj, sizeof(structPerObj), 
		D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);
}