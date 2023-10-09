#include "stdafx.h"
#include "assetManager.h"

AssetManager::AssetManager(): mAssetShader(this), mAssetMaterial(this),mAssetTexturer(this), 
	mAssetMesh(this), mAssetSkeleton(this), mAssetAnimation(this)
{
	
}

AssetManager::~AssetManager()
{
}

void AssetManager::Clear()
{
	mAssetShader.Clear();
}

Shader* AssetManager::GetShader(const std::wstring& shaderName)
{
	return mAssetShader.Get(shaderName);
}

void AssetManager::SetShader(const std::wstring& shaderName, Shader* pShader)
{
	mAssetShader.Cache(shaderName, pShader);
}

Texture* AssetManager::LoadTexture(const std::wstring& fileName)
{
	return mAssetTexturer.Load(fileName);
}

Material* AssetManager::LoadMaterial(const std::wstring& materialName)
{
	return mAssetMaterial.Load(materialName);
}

Mesh* AssetManager::LoadMesh(const std::wstring& fileName)
{
	return mAssetMesh.Load(fileName);
}

Skeleton* AssetManager::LoadSkeleton(const std::wstring& fileName)
{
	return mAssetSkeleton.Load(fileName);
}

Animation* AssetManager::LoadAnimation(const std::wstring& fileName)
{
	return mAssetAnimation.Load(fileName);
}