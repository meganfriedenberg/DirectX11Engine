#pragma once

#include "engineMath.h"
#include "Graphics.h"

class AssetManager;
class Material;
class VertexBuffer;

class Mesh
{
public:
	Mesh(const VertexBuffer* vertexBuffer, Material* material);

	~Mesh();

	void Draw() const;

	bool Load(const WCHAR* fileName, AssetManager* pAssetManager);
	static Mesh* StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager);
	bool isSkinned() const { return mIsSkinned; }

protected:
	Material* mMaterial;
	const VertexBuffer* mVertexBuffer;
	bool mIsSkinned;
};