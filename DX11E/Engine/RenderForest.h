#pragma once
#include "VertexBuffer.h"
#include "engineMath.h"
#include "Material.h"
#include "Mesh.h"

class RenderForest
{

public:
	RenderForest();
	RenderForest(const VertexBuffer* vertexBuffer, const class Material* mMat);
	~RenderForest();

	virtual void Draw();

	const VertexBuffer* mBuffer;

	const class Material* mMaterial;



};

