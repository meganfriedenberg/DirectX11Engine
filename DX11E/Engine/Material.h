#pragma once
#include "engineMath.h"
#include "Graphics.h"


class Material
{
	struct MaterialConst // Lab05b
	{
		Vector3 c_diffuseColor;
		float padding;
		Vector3 c_specularColor;
		float c_specularPower;
	};

public:

	Material();
	~Material();
	void SetActive();
	void SetShader(const class Shader* shader);
	void SetTexture(int slot, const class Texture* texture);
	void SetDiffuseColor(const Vector3& color);
	void SetSpecularColor(const Vector3& color);
	void SetSpecularPower(float power);

	static Material* StaticLoad(const WCHAR* fileName, class AssetManager* pManager);
	bool Load(const WCHAR* fileName, AssetManager* pAssetManager);




	MaterialConst matConst; // public instance of MaterialConst structure
	ID3D11Buffer* matBuff;
	const Shader* materialShader;
	const Texture* textures[Graphics::TEXTURE_SLOT_TOTAL];
};