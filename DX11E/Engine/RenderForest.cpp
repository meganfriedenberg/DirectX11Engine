#include "stdafx.h"
#include "Component.h"
#include "Graphics.h"
#include "RenderForest.h"
#include "Material.h"

RenderForest::RenderForest(const VertexBuffer* vertexBuffer, const Material* mMat)
{
	mBuffer = vertexBuffer;
	mMaterial = mMat;
}
RenderForest::~RenderForest()
{
	delete mBuffer;
	delete mMaterial;
}
void RenderForest::Draw()
{
	mBuffer->Draw();
}